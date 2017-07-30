#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <stdio.h>
#include <stdlib.h>
#include "database_api.c"

#define PHISHING_MINER_EVENT_TYPE_NON_PHISHING_ADD			0
#define PHISHING_MINER_EVENT_TYPE_NON_PHISHING_DEL			1

#define PHISHING_ROBOT_PROCESS_STATUS_PHISHING		0
#define PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING	1
#define PHISHING_ROBOT_PROCESS_STATUS_FAILUR		2
#define DELETE_PERIOD 10

#define SECOND_INTERVAL(__TIME_COUNTER__, __SECOND__) ((__TIME_COUNTER__ % (__SECOND__)) == 0 ? 1 : 0)


static char query[256];

typedef struct{
	uint64_t id;
	uint8_t process_status;

}ROBOT_PROCESS_EVENT_ST;


typedef struct{
	char db_server_addr[16];
	char db_username[128];
	char db_pass[128];
	char db_name[128];
	MYSQL* db_conn;
}DB_CONTEXT_ST;

static DB_CONTEXT_ST db_context;

static bool load_config(){
	strncpy(db_context.db_server_addr, "127.0.0.1", sizeof(db_context.db_server_addr));
	strncpy(db_context.db_username, "root", sizeof(db_context.db_username));
	strncpy(db_context.db_pass, "iman3000", sizeof(db_context.db_pass));
	strncpy(db_context.db_name, "SAMPLE", sizeof(db_context.db_name));
}

int init_connection(){
	load_config();
	int retval;

		if(0 != (retval = db_connection_init(&db_context.db_conn, db_context.db_server_addr, db_context.db_username, db_context.db_pass, db_context.db_name))){
			PTRACE( 0 , 0 , "connection can not established!\n");
			return retval;
		}
		PTRACE(0, 0, "connection initiate successfully!\n");
}


bool update_event_delete(const char *tblname, MYSQL_ROW to_be_delete_rows){
	
	sprintf(query, "DELETE FROM %s WHERE AddDate =%d",tblname, to_be_delete_rows);
	_db_query(db_context.db_conn, query);

}

void print_data_db(MYSQL_RES* total_res){
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(total_res);
	MYSQL_FIELD *field;

		PTRACE(0, 0, "store result of database...");

		while(row = mysql_fetch_row(total_res)){
			for(int i = 0; i < num_fields; i++){
				if (i == 0) {              
            		while(field = mysql_fetch_field(total_res)) {
                		printf("%s ", field->name);
             		}
             		printf("\n");
				}    
				printf("%s ", row[i] ? row[i] : "NULL");		
				}	
			}
}

void func(ROBOT_PROCESS_EVENT_ST* process_event){

	if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_PHISHING){
		
		if(0 == init_connection()){
		
		sprintf(query, "SELECT * FROM tblRobotResultPhishing_humanQueue WHERE EventId == %u", process_event->id);

		_db_query(db_context.db_conn, query);

		MYSQL_RES* result_robot_phishing;
		if(NULL !=(result_robot_phishing = _db_store_result(db_context.db_conn))){
			PTRACE(0, 0, "printting from tblRobotResultPhishing_humanQueue is starting!");

			print_data_db(result_robot_phishing);
			db_free_result(result_robot_phishing);

			PTRACE(0, 0, "printting from tblRobotResultPhishing_humanQueue is finished!");
		}
		}
	}
	else if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING){
		
		if(0 == init_connection()){

			sprintf(query, "SELECT * FROM tblRobotResultNonPhishing WHERE EventId == %u", process_event->id);

			MYSQL_RES *result_robot_nonfishing;
			if(NULL != (result_robot_nonfishing = _db_store_result(db_context.db_conn))){
				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is starting!");

				print_data_db(result_robot_nonfishing);
				db_free_result(result_robot_nonfishing);

				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is finished!");
			}
		}
	}

	else if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_FAILUR){
		if(0 == init_connection()){

			sprintf(query, "SELECT * FROM tblRobotProcessFailur WHERE EventId == %u", process_event->id);

			MYSQL_RES *result_robot_failur;
			if(NULL != (result_robot_failur = _db_store_result(db_context.db_conn))){
				PTRACE(0, 0, "printting from tblRobotProcessFailur is starting!");

				print_data_db(result_robot_failur);
				db_free_result(result_robot_failur);

				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is finished!");
			}
		}
	}
}

void general_update_db(const char *tblname){

	MYSQL_RES *res_for_time;
	MYSQL_ROW row_of_time;

	sprintf(query, "SELECT DateAdd from %s", tblname);
	_db_query(db_context.db_conn , query);

	if(NULL !=(res_for_time = _db_store_result(db_context.db_conn))){


		while(1){
			while(row_of_time = mysql_fetch_row(res_for_time)){
				long int time_container;
				time_container = strtoul(row_of_time[0], NULL,0);
				if(SECOND_INTERVAL(time_container,DELETE_PERIOD)){
					PTRACE(0, 0, "deleting old data is stating...");
					if(update_event_delete(tblname, row_of_time))
						PTRACE(0, 0, "delete old data is finished!");
				}
			}
		}
		db_free_result(res_for_time);
	}
}