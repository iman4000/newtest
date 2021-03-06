#include <stdlib.h>
#include <stdio.h>
//#include "database_api.c"
#include "logger.h"
#include "phishing_supervisor.h"

#include "phishing_supervisor.c"
//temprary...
#include <unistd.h>
#include <time.h>
#include <string.h>

void insert_some_val(DB_CONTEXT_ST );
void produce_random_and_delete(DB_CONTEXT_ST *db_context , ROBOT_PROCESS_EVENT_ST *process_event);


void print_db(){
    init_connection();

        //sprintf(quer2, "SELECT * FROM tblRobotProcessQueue");
        PTRACE(0,0, "her222222222222");
        fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
        if(0 ==(_db_query(db_context.db_conn, "SELECT * FROM tblRobotProcessQueue"))){
            fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
            PTRACE(0,0, "h333333333333");
            MYSQL_RES* result; 
            MYSQL_ROW row;
        
            PTRACE(0,0, "here11111");

            if(NULL !=(result = _db_store_result(db_context.db_conn))){
                PTRACE(0,0, "here4454454545");

                int num_field = mysql_num_fields(result);
                PTRACE(0,0, "here2222222");
                for(int i = 0; i < num_field; i++){
                    while(row = mysql_fetch_row(result)){
                        PTRACE(0,0, "here56565656");
                        fprintf(stdout,"%s", (row[i] ? row[i] : "NULL"));
                    }
                }
                printf("\n");
                PTRACE(0,0, "show table in here");
            }
            db_free_result(result);
        }
        else{
            fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
    }


    mysql_close(db_context.db_conn);
    PTRACE(0, 0, "connection closed!");
}



int main(){

    extern DB_CONTEXT_ST db_context;
    ROBOT_PROCESS_EVENT_ST *process_event;
    init_connection();
    // insert_some_val(db_context);
    produce_random_and_delete( &db_context ,process_event);
    return 0;
}


void insert_some_val(DB_CONTEXT_ST db_context){
    char quer[256];
    int pid = getpid();
    int currentTime = (unsigned int)time(NULL);

    for(int i = 0; i < 10; i++){
        sprintf(quer, "INSERT INTO `tblRobotProcessQueue`(ProcessId,Protocol,SRC_IP,DST_IP,SRC_Port,DST_Port,`HostName`,`URL`,`Href`,DateAdd) VALUES(%d,%d,%d,%d,%d,%d,%s,%s,%s,%d )" ,pid*i, 6, 1234, 5345, 80, 44, "HostName", "URL", "Href", currentTime);
        PTRACE(0,0, "go insert assignment...\n");
        if(0 !=(_db_query(db_context.db_conn, quer))){
            printf("data added to database!");
        }
    }
}


void produce_random_and_delete(DB_CONTEXT_ST *db_context , ROBOT_PROCESS_EVENT_ST *process_event){
    char que[256];

    PTRACE(0, 0, "add data in database...");
    MYSQL_RES *tem_res;
    MYSQL_RES *res2;
    MYSQL_ROW tem_row;
    // MYSQL_ROW row2;

    // MYSQL_RES *tem_res2;
    // MYSQL_ROW tem_row2;
    
    srand(time(NULL));
    int n;
    unsigned long i , max=0;
    // unsigned long row_num;

    sprintf(que, "SELECT * FROM tblRobotProcessQueue where ProcessId >= 0");
    _db_query(db_context->db_conn, que);
    PTRACE(0,0,"jaaaaaaaaaalebe");
    
    if(NULL != (tem_res = _db_store_result(db_context->db_conn))){
        PTRACE(0,0, "res is ok#######################################################################################################");
        i = (unsigned long) mysql_num_rows(tem_res);////////number of rows
    }
    PTRACE(0,0,"jaaaaaaaaaalebe222222222");
    process_event = (ROBOT_PROCESS_EVENT_ST *) malloc(sizeof( ROBOT_PROCESS_EVENT_ST ));
    
    sprintf(que, "SELECT max(EventId) AS max_event FROM tblRobotProcessQueue");
    _db_query(db_context->db_conn, que);
    if(NULL != (res2 = _db_store_result(db_context->db_conn))){
        tem_row = mysql_fetch_row(res2);
        sscanf(tem_row[0],"%ld",&max);
        printf("------------------------------------max is %ld-------------------------------------",max);
    }
        while(tem_row = mysql_fetch_row(tem_res)){
            PTRACE(0,0, "#$^^&&*(()*^%%$#$#%%$^%%^&&*^&^^$%##%$#@here is %d", i);
        n = rand() % 2;
        if(n == 0){ /* phishing */
            process_event->id = max-i;
            process_event->process_status = PHISHING_ROBOT_PROCESS_STATUS_PHISHING;
            PTRACE(0,0,"phishing assignment is finished");
        }
        else{ /* non-phishing */
            process_event->id = max-i;
            process_event->process_status = PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING;
            PTRACE(0,0,"non-phishing assignment is finished");
        }
        func(process_event);
        PTRACE(0,0,"here10");
        i--;
    }
     process_event = NULL;
     free(process_event);
     PTRACE(0,0, "*******************************************END OF DELETE FUNC***********************************************");
    // PTRACE(0,0, ".............................................. %d", last_id);
}

