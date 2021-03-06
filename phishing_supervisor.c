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

void init_connection(){
	load_config();

		if(0 != (int retval = db_connection_init(&db_context.db_conn, db_context.db_server_addr, db_context.db_username, db_context.db_pass, db_context.db_name))){
			PTRACE( INFO , CHRDC , "connection can not established!\n");
			return retval;
		}
		PTRACE(INFO, CHRDC, "connection initiate successfully!\n");
}


bool update_event_delete(){
	//delete events after period...
}

void update_events_db(){
	//update events a timestamp_sync 
}

void print_data_db(MYSQL_RES* total_res){
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(total_res);
	MYSQL_FIELD *field;

	if(NULL != total_res = _db_store_res(db_context.db_conn)){

		PTRACE(INFO, CHRDC, "store result of database...");

		while(row = mysql_fetch_row(total_res)){
			for(int i = 0; i < num_fields; i++){
				if (i == 0) {              
            		while(field = mysql_fetch_field(result)) {
                		printf("%s ", field->name);
             		}
             		printf("\n");
				}    
				printf("%s ", row[i] ? row[i] : "NULL");		
				}	
			}
		}
}

void func(ROBOT_PROCESS_EVENT_ST* process_event){

	char query[256];

	if(process_event.process_status == PHISHING_ROBOT_PROCESS_STATUS_PHISHING){
		
		init_connection();
		
		sprintf(query, "SELECT * FROM tblRobotResultPhishing_humanQueue WHERE EvenrId == %u", process_event.id);

		_db_query(db_context.db_conn, query);

		MYSQL_RES *result_robot_phishing;

		print_data_db(result_robot_phishing);

		db_free_result(result_robot_phishing);

		PTRACE(INFO, CHRDC, "printting from tblRobotResultPhishing_humanQueue is finished!");

	else if(process_event.process_status == PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING){
		
		init_connection();

		sprintf(query, "SELECT * FROM tblRobotResultNonPhishing WHERE EvenrId == %u", process_event.id);

		MYSQL_RES *result_robot_nonfishing;

		print_data_db(result_robot_nonfishing);

		db_free_result(result_robot_nonfishing);

		PTRACE(INFO, CHRDC, "printting from tblRobotResultNonPhishing is finished!");
	}

	else(process_event.process_status == PHISHING_ROBOT_PROCESS_STATUS_FAILUR){

	}

}
