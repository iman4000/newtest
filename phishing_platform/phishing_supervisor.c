#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <stdio.h>
#include <stdlib.h>
#include "database_api.c"
#include "phishing_supervisor.h"



#define SECOND_INTERVAL(__TIME_COUNTER__, __SECOND__) ((__TIME_COUNTER__ % (__SECOND__)) == 0 ? 1 : 0)


static char query[256];


DB_CONTEXT_ST db_context;
ROBOT_PROCESS_EVENT_ST* process_event;

static bool load_config(){
	strncpy(db_context.db_server_addr, "127.0.0.1", sizeof(db_context.db_server_addr));
	strncpy(db_context.db_username, "root", sizeof(db_context.db_username));
	strncpy(db_context.db_pass, "iman3000", sizeof(db_context.db_pass));
	strncpy(db_context.db_name, "SAMPLE", sizeof(db_context.db_name));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int init_connection(){
	load_config();
	int retval;
		if(0 != (retval = db_connection_init(&db_context.db_conn, db_context.db_server_addr, db_context.db_username, db_context.db_pass, db_context.db_name))){
			PTRACE( 0 , 0 , "connection can not established!\n");
			return retval;
		}
		PTRACE(0, 0, "connection initiate successfully!\n");
		printf( "retval is : %d\n", retval);
		return retval;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool update_event_delete(const char *tblname, MYSQL_ROW to_be_delete_rows){
	
	sprintf(query, "DELETE FROM %s WHERE AddDate =%d",tblname, to_be_delete_rows);
	if(_db_query(db_context.db_conn, query))
		return TRUE;
	else
		return FALSE;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_data_db(MYSQL_RES* total_res){
	MYSQL_ROW row;
	int num_fields = mysql_num_fields(total_res);
	MYSQL_FIELD *field;
		printf("num fields = %d\n", num_fields);
		PTRACE(0, 0, "store result of database...");

// for(int i = 0; i < num_fields; i++){
// 				PTRACE(0,0,"print database 2");
// 				// if (i == 0) {
// 				// 	PTRACE(0,0,"print database 3");
//             	// 	while(field = mysql_fetch_field(total_res)) {
//                 // 		printf("%s ", field->name);
//              	// 	}
//              	// 	printf("\n");
// 				// }    
// 				//printf("%s ", row[i] ? row[i] : "NULL");		
// 				}	

		while(row = mysql_fetch_row(total_res)){
			PTRACE(0,0,"print database 1");
			for(int i = 0; i < num_fields; i++){
				PTRACE(0,0,"print database 2");
				if (i == 0) {
					PTRACE(0,0,"print database 3");
            		while(field = mysql_fetch_field(total_res)) {
                		printf("%s ", field->name);
             		}
             		printf("\n");
				}else    
				printf("%s ", row[i] ? row[i] : "NULL");		
				}	
			}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void func(ROBOT_PROCESS_EVENT_ST* process_event){
	int bib;
	

	if(0 == (bib = init_connection())){
	
	// printf("///////////////  status is: %d\n",process_event->process_status );
	// printf("/////////////// total status is: %d\n", PHISHING_ROBOT_PROCESS_STATUS_PHISHING);

	if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_PHISHING){

			sprintf(query, "INSERT INTO tblRobotResultPhishing_humanQueue SELECT * FROM tblRobotProcessQueue WHERE EventId = %d", process_event->id);
			PTRACE(0,0,"inja3");
			if(_db_query(db_context.db_conn, query))
				PTRACE(0,0, "phishing data added to phishing table\n");
			else{
				fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
				PTRACE(0,0,"inja chetor?");
			}

			PTRACE(0,0,"inja4");
			sprintf(query, "SELECT * FROM tblRobotResultPhishing_humanQueue WHERE EventId = %u", process_event->id);

			if(_db_query(db_context.db_conn, query))
				PTRACE(0,0, "start printing phishing table...\n");

			MYSQL_RES* result_robot_phishing;
			if(NULL !=(result_robot_phishing = _db_store_result(db_context.db_conn))){
				PTRACE(0, 0, "printting from tblRobotResultPhishing_humanQueue is starting!");

				print_data_db(result_robot_phishing);
				db_free_result(result_robot_phishing);

				PTRACE(0, 0, "printting from tblRobotResultPhishing_humanQueue is finished!");
			}
		mysql_close(db_context.db_conn);
	}
	/*else if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING){
		PTRACE(0,0,"non-inja1");
		//if(0 == init_connection()){
			PTRACE(0,0,"non-inja2");
			sprintf(query, "INSERT INTO tblRobotResultNonPhishing SELECT * FROM tblRobotProcessQueue WHERE EventId = %d", process_event->id);
			PTRACE(0,0,"non-inja3");
			if(_db_query(db_context.db_conn, query))
				PTRACE(0,0, "phishing data added to phishing table\n");


			sprintf(query, "SELECT * FROM tblRobotResultNonPhishing WHERE EventId = %u", process_event->id);

			MYSQL_RES *result_robot_nonfishing;
			if(NULL != (result_robot_nonfishing = _db_store_result(db_context.db_conn))){
				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is starting!");

				print_data_db(result_robot_nonfishing);
				db_free_result(result_robot_nonfishing);

				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is finished!");
			}
			mysql_close(db_context.db_conn);
		}*/

	else if(process_event->process_status == PHISHING_ROBOT_PROCESS_STATUS_FAILUR){
		//if(0 == init_connection()){

			sprintf(query, "INSERT INTO tblRobotProcessFailur SELECT * FROM tblRobotProcessQueue WHERE EventId = %d", process_event->id);
			if(_db_query(db_context.db_conn, query))
				PTRACE(0,0, "phishing data added to phishing table\n");


			sprintf(query, "SELECT * FROM tblRobotProcessFailur WHERE EventId = %u", process_event->id);

			MYSQL_RES *result_robot_failur;
			if(NULL != (result_robot_failur = _db_store_result(db_context.db_conn))){
				PTRACE(0, 0, "printting from tblRobotProcessFailur is starting!");

				print_data_db(result_robot_failur);
				db_free_result(result_robot_failur);

				PTRACE(0, 0, "printting from tblRobotResultNonPhishing is finished!");
			}
				mysql_close(db_context.db_conn);	
		}
		
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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