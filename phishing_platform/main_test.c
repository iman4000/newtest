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


void print_db(){
    init_connection();

        //sprintf(quer2, "SELECT * FROM tblRobotProcessQueue");
        PTRACE(0,0, "her222222222222");
        fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
        if(0 !=(_db_query(db_context.db_conn, "SELECT * FROM tblRobotProcessQueue"))){
            fprintf(stderr, "%s\n", mysql_error(db_context.db_conn));
            PTRACE(0,0, "h333333333333");
            MYSQL_RES* result; 
            MYSQL_ROW row;
        
            PTRACE(0,0, "here11111");

            if(result = _db_store_result(db_context.db_conn)){
                PTRACE(0,0, "here11111");

                int num_field = mysql_num_fields(result);
                PTRACE(0,0, "here11111");
                while(row = mysql_fetch_row(result)){
                    PTRACE(0,0, "here11111");
                    for(int i = 0; i < num_field; i++)
                        printf("%s", row[i] ? row[i] : "NULL");
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

    char quer[256];
    //char quer2[256];
    init_connection();

    printf("user name is : %s\n", db_context.db_username );

    PTRACE(0, 0, "add data in database...");

    int pid = getpid();
    int currentTime = (unsigned int)time(NULL);

    for(int i = 0; i < 10; i++){

        sprintf(quer, "INSERT INTO tblRobotProcessQueue(ProcessId,Protocol,SRC_IP,DST_IP,SRC_Port,DST_Port,HostName,URL,Href,DateAdd) VALUES(%d,%d,%d,%d,%d,%d,%s,%s,%s,%d )" ,pid*i, 6, 1234, 5345, 80, 44, "HostName", "URL", "Href", currentTime);
        if(0 !=(_db_query(db_context.db_conn, quer)))
            printf("data added to database!");
    }

    //////////////
    func(process_event);


mysql_close(db_context.db_conn);


print_db();
    return 0;
}