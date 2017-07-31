#ifndef PHISH_SUP_H_
#define PHISH_SUP_H_


#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <stdint.h>

typedef struct{
	char db_server_addr[16];
	char db_username[128];
	char db_pass[128];
	char db_name[128];
	MYSQL* db_conn;
}DB_CONTEXT_ST;

typedef struct{
	uint64_t id;
	uint8_t process_status;
}ROBOT_PROCESS_EVENT_ST;


#endif