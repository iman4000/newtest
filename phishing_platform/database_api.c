/*
 * database_api.c
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <syslog.h>

#include <mysql/mysql.h>

#include "logger.h"
//#include "../server_share/include/clients_def.h"


int db_connection_init(MYSQL **p_mysql_conn, const char *server, const char *username, const char *password, const char *database){
	
	uint32_t reconnect = 1;
	if ( NULL == ( *p_mysql_conn = mysql_init( NULL ) ) ) {
		PTRACE( 0 , 0 , "Mysql Init error %s", mysql_error( *p_mysql_conn ) );
		
		return 1;
	}
	if ( 0 != mysql_options(*p_mysql_conn, MYSQL_OPT_RECONNECT, &reconnect ) ) {
		PTRACE( 0 , 0 , "Mysql Set Options error %s", mysql_error( *p_mysql_conn ) );

		return 1;
	}
	if ( mysql_real_connect( *p_mysql_conn , server, username, password , database , 0, NULL, 0) == NULL) {
		PTRACE( 0 , 0 , "Mysql real connect error %s" , mysql_error( *p_mysql_conn ) );

		return 1;
	}
	if ( 0 != mysql_options(*p_mysql_conn, MYSQL_OPT_RECONNECT, &reconnect ) ) {
		PTRACE( 0 , 0 , "Mysql Set Options error %s", mysql_error( *p_mysql_conn ) );

		return 1;
	}


	return 0;

}

/*int db_connection_pool_init(MYSQL *p_mysql_conn[], u_int8_t max_connection_num, const char *server, const char *username, const char *password, const char *database){
	u_int8_t connection_num;
	uint32_t reconnect = 1;
	for ( connection_num = 0 ; 	connection_num < max_connection_num ; connection_num++ ) {
		if ( NULL == ( p_mysql_conn[ connection_num ] = mysql_init( NULL ) ) ) {
			//PTRACE( 0 , 0 , "Mysql Init(%u)  error %s" , connection_num , mysql_error( p_mysql_conn[ connection_num ] ) );
			return 1;
		}
		if ( 0 != mysql_options(p_mysql_conn[ connection_num ], MYSQL_OPT_RECONNECT, &reconnect ) ) {
			//PTRACE( 0 , 0 , "Mysql Set Options(%u)  error %s" , connection_num , mysql_error( p_mysql_conn[ connection_num ] ) );
			return 1;
		}
		if ( mysql_real_connect( p_mysql_conn[ connection_num ] , server, username, password , database , 0, NULL, 0) == NULL) {
			//PTRACE( 0 , 0 , "Mysql real connect(%u) error %s" , connection_num , mysql_error( p_mysql_conn[ connection_num ] ) );
			return 1;
		}
		if ( 0 != mysql_options(p_mysql_conn[ connection_num ], MYSQL_OPT_RECONNECT, &reconnect ) ) {
			//PTRACE( 0 , 0 , "Mysql Set Options(%u)  error %s" , connection_num , mysql_error( p_mysql_conn[ connection_num ] ) );
			return 1;
		}
	}
	return 0;
}
*/

int _db_query(MYSQL *mysql_conn, char* sql ) {
	int ret = 0;
	
	if ( 0 == ( ret = mysql_ping( mysql_conn ) ) ) {

		PTRACE(0,0, "can you hear me?");

		ret = mysql_query( mysql_conn , sql );

		//fprintf(stderr, "%s\n", mysql_error(mysql_conn));
		printf("ret is : %d\n", ret);

		//syslog ( LOG_INFO , "db_query( %u , [%s] )" , connection_id , sql );
		if(NULL != mysql_error(mysql_conn)){

		   PTRACE(0,0, "_db_query has a error\n");
			//fprintf(stderr, "%s\n", mysql_error(mysql_conn));
		}
		if ( 0 != ret && NULL != mysql_error( mysql_conn ) ) {
			
			syslog ( LOG_INFO , "Mysql query connection %s", mysql_error( mysql_conn ) );
			PTRACE(0,0, "FAIL HERE IN _DB_QUERY");
		}

	} else {
		PTRACE( 0 , 0 , "Mysql Ping Error connection %s" ,mysql_error( mysql_conn ) );
	
	}
	PTRACE(0,0, "reach to return ret...\n");
	return ret;
}

/*int db_query(MYSQL *mysql_conn[], u_int8_t connection_id , char* sql ) {
	int ret = 0;
	if ( 0 == ( ret = mysql_ping( mysql_conn[ connection_id ] ) ) ) {
		ret = mysql_query( mysql_conn[ connection_id ] , sql );
		//syslog ( LOG_INFO , "db_query( %u , [%s] )" , connection_id , sql );
		if ( 0 != ret && NULL != mysql_error( mysql_conn[ connection_id ] ) ) {
			PTRACE( 0 , 0 , "Mysql connection(%u) query error %s query:%s" , connection_id , mysql_error( mysql_conn[ connection_id ] ) , sql );
			//syslog ( LOG_INFO , "Mysql query connection(%u) %s" , connection_id , mysql_error( mysql_conn[ connection_id ] ) );
		}
	} else {
		PTRACE( 0 , 0 , "Mysql Ping Error connection(%u) %s" , connection_id , mysql_error( mysql_conn[ connection_id ] ) );

	}
	return ret;
}
*/

MYSQL_RES* _db_store_result(MYSQL *mysql_conn) {
	MYSQL_RES *res = mysql_store_result( mysql_conn );
	//syslog ( LOG_INFO , "db_store_result( %u )" , connection_id );
	if ( NULL == res && NULL != mysql_error( mysql_conn ) ) {
		PTRACE( 0 , 0 ,"Mysql Resualt connection(%u) %s" , mysql_error( mysql_conn ) );
	}
	return res;
}

/*MYSQL_RES* db_store_result(MYSQL *mysql_conn[], u_int8_t connection_id ) {
	MYSQL_RES *res = mysql_store_result( mysql_conn[ connection_id ] );
	//syslog ( LOG_INFO , "db_store_result( %u )" , connection_id );
	if ( NULL == res && NULL != mysql_error( mysql_conn[ connection_id ] ) ) {
		PTRACE( 0 , 0 ,"Mysql Resualt connection(%u) %s" , connection_id , mysql_error( mysql_conn[ connection_id ] ) );
	}
	return res;
}
*/

void db_free_result( MYSQL_RES *result ) {
	mysql_free_result( result );
	//syslog ( LOG_INFO , "db_free_result()" );
}

