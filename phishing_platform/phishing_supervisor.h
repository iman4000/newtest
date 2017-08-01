#ifndef PHISH_SUP_H_
#define PHISH_SUP_H_


#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <stdint.h>

#define PHISHING_MINER_EVENT_TYPE_NON_PHISHING_ADD			0
#define PHISHING_MINER_EVENT_TYPE_NON_PHISHING_DEL			1

#define PHISHING_ROBOT_PROCESS_STATUS_PHISHING		0
#define PHISHING_ROBOT_PROCESS_STATUS_NON_PHISHING	1
#define PHISHING_ROBOT_PROCESS_STATUS_FAILUR		2
#define DELETE_PERIOD 10

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