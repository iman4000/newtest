
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include <mysql/mysql.h>

//#include "client_def.h"
//#include "../server_share/include/clients_def.h"
//#include "database_api.h"

//#include "https_process_print_statistics.c"

#define DAY_INTERVAL(__SEC_TIME_COUNTER__,__DAY__) ((__SEC_TIME_COUNTER__%(__DAY__*24*60*60))==0?1:0)
#define HOUR_INTERVAL(__SEC_TIME_COUNTER__,__HOUR__) ((__SEC_TIME_COUNTER__%(__HOUR__*60*60))==0?1:0)
#define MINUTE_INTERVAL(__SEC_TIME_COUNTER__,__MINUTE__) ((__SEC_TIME_COUNTER__%(__MINUTE__*60))==0?1:0)
#define SECOND_INTERVAL(__SEC_TIME_COUNTER__,__SECOND__) ((__SEC_TIME_COUNTER__%(__SECOND__))==0?1:0)

typedef struct{
	char db_server_addr[16];
	char db_username[128];
	char db_pass[128];
	char db_name[128];

	MYSQL* db_conn;
}TLS_FP_DB_CONTEXT_ST;

static TLS_FP_DB_CONTEXT_ST db_context;

typedef struct{
	char sql_query[2048];
	uint32_t local_rules_update_timestamp;
}DB_SERVICE_GLOBAL_VAR_ST;
static DB_SERVICE_GLOBAL_VAR_ST db_service_global_var;


static bool load_config(){
	strncpy(db_context.db_server_addr, "/*ip*/", sizeof(db_context.db_server_addr));
	strncpy(db_context.db_username, "traffic_analysis", sizeof(db_context.db_username));
	strncpy(db_context.db_pass, "traffic_analysisshah", sizeof(db_context.db_pass));
	strncpy(db_context.db_name, "policyruledb", sizeof(db_context.db_name));

}


static void tls_fp_bulk_rules_fetch(){

	
	MYSQL_RES *finger_print_default_rule_tlb_result;
	MYSQL_ROW mysql_rows;
	uint32_t i;
	uint32_t flat_cat_id=0;
	uint32_t pre_rule_cat_id;
	

	sprintf(db_service_global_var.sql_query, "SELECT * FROM policyruledb.tblTLSFingerprintsDefaultRules "
		"LEFT JOIN policyruledb.tblTLSFingerprintsDefaultRulesCategory ON tblTLSFingerprintsDefaultRules.TLSFingerprintDefaultRulesCategoryId= tblTLSFingerprintsDefaultRulesCategory.Id "
		"ORDER BY tblTLSFingerprintsDefaultRules.TLSFingerprintDefaultRulesCategoryId ASC "
		"LIMIT %u", MAX_FP_RULE_COUNT);

	_db_query( db_context.db_conn, db_service_global_var.sql_query);
	
	if ( NULL != (finger_print_default_rule_tlb_result = _db_store_result( db_context.db_conn) ) ) {

		tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count=0;

		while ((mysql_rows = mysql_fetch_row(finger_print_default_rule_tlb_result))) {
			sscanf(mysql_rows[0],"%u",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].rule_id);
			sscanf(mysql_rows[1],"%u",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].rule_cat_id);
			sscanf(mysql_rows[2],"%s",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].desc);
			sscanf(mysql_rows[3],"%hx",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].record_tls_version);
			sscanf(mysql_rows[4],"%hx",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].tls_version);
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ciphersuite_length = strlen(mysql_rows[5]);
			for(i = 0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ciphersuite_length ; i+=2)
				sscanf(&mysql_rows[5][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ciphersuite[i/2]);			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ciphersuite_length /= 2;
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].compression_length = strlen(mysql_rows[6]);
			for(i =0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].compression_length; i+=2)
				sscanf(&mysql_rows[6][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].compression[i/2]);	
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].compression_length /= 2;
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].extensions_length = strlen(mysql_rows[7]);
			for(i =0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].extensions_length; i+=2)
				sscanf(&mysql_rows[7][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].extensions[i/2]);	
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].extensions_length /= 2;
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].curves_length = strlen(mysql_rows[8]);
			for(i =0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].curves_length; i+=2)
				sscanf(&mysql_rows[8][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].curves[i/2]);	
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].curves_length /= 2;
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].sig_alg_length = strlen(mysql_rows[9]);
			for(i =0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].sig_alg_length; i+=2)
				sscanf(&mysql_rows[9][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].sig_alg[i/2]);	
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].sig_alg_length /= 2;
			
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ec_point_fmt_length = strlen(mysql_rows[10]);
			for(i =0; i < tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ec_point_fmt_length; i+=2)
				sscanf(&mysql_rows[10][i],"%02X",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ec_point_fmt[i/2]);	
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].ec_point_fmt_length /= 2;
			
			//sscanf(mysql_rows[11],"%hhu",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].rule_isDisable);
			//sscanf(mysql_rows[14],"%s",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].cat_name);
			//fprintf(stderr, "rule cat id : %s\n", tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].cat_name);
			//sscanf(mysql_rows[14],"%hhu",&tls_fp_traffic_mon_proc_policy.bulk_rules.rules_bank[tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count].rule_cat_isDisable);	
													
			tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count++;
			
			//print_tls_fp_traffic_mon_proc_shared_data();

		}

	}
	
	db_free_result(finger_print_default_rule_tlb_result);
	
	return 0;
}

static void tls_fp_bulk_update_events_fetch(){
	
	MYSQL_RES *fingerprint_update_event_tlb_result;
	MYSQL_ROW mysql_rows;
	
	sprintf(db_service_global_var.sql_query, "SELECT TLSFingerprintDefaultRuleId,TLSFingerprintDefaultRuleCategoryId,EventType,EventDate "
		"FROM policyruledb.tblTLSFingerprintsDefaultRulesUpdateEvents "
		"ORDER BY tblTLSFingerprintsDefaultRulesUpdateEvents.TLSFingerprintDefaultRuleCategoryId ASC "
		"LIMIT %u", MAX_FP_RULE_COUNT*2);
	_db_query( db_context.db_conn, db_service_global_var.sql_query);
	
	if ( NULL != (fingerprint_update_event_tlb_result = _db_store_result( db_context.db_conn) ) ) {

		tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count=0;
		while ((mysql_rows = mysql_fetch_row(fingerprint_update_event_tlb_result))) {	
			
			sscanf(mysql_rows[0],"%u",&tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].rule_id);
			sscanf(mysql_rows[1],"%u",&tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].rule_cat_id);
			sscanf(mysql_rows[2],"%hu",&tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].event_type);
			sscanf(mysql_rows[3],"%u",&tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].event_date);
			
			PTRACE( INFO , CHRDC , "TLS fingerprint monitor clinet, db service, Fetch event:  %u   %hu   %u   %u\n",
				tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].rule_id,
				tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].rule_cat_id,
				tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].event_type,
				tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count].event_date); 
			
			tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count++;
		}
		
	}
	
	db_free_result(fingerprint_update_event_tlb_result);

}

static bool tls_fp_bulk_update_events_remove(){

	MYSQL_ROW mysql_rows;
	uint32_t event_iter;
	
	for(event_iter =0; event_iter < tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count; event_iter++){
		sprintf(db_service_global_var.sql_query, "DELETE FROM policyruledb.tblTLSFingerprintsDefaultRulesUpdateEvents WHERE TLSFingerprintDefaultRuleId=%u"
		, tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.tls_fp_rule_update_events[event_iter].rule_id);
		_db_query( db_context.db_conn, db_service_global_var.sql_query);

	}
	
	tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count = 0;

}

static void db_update_timestamp_sync(){
	
	sprintf(db_service_global_var.sql_query, "UPDATE tblPolicyRuleConfig SET TLSFingerprintDefaultRulesUpdateTimeStamp=UNIX_TIMESTAMP()");
	_db_query( db_context.db_conn, db_service_global_var.sql_query);
	
}

static uint32_t tls_fp_db_rules_commit_timestamp_fetch(){
	
	MYSQL_RES *fingerprint_rule_commit_timestamp_result;
	MYSQL_ROW mysql_rows;
	
	uint32_t commit_timestamp;

	sprintf(db_service_global_var.sql_query, "SELECT TLSFingerprintDefaultRulesCommitTimeStamp FROM policyruledb.tblPolicyRuleConfig");
	_db_query( db_context.db_conn, db_service_global_var.sql_query);
	 if ( NULL != (fingerprint_rule_commit_timestamp_result = _db_store_result( db_context.db_conn) ) ) {

	 	while ((mysql_rows = mysql_fetch_row(fingerprint_rule_commit_timestamp_result))) {	
	 		sscanf(mysql_rows[0],"%u", &commit_timestamp);
			
	 	}
		
	 }

	 if(fingerprint_rule_commit_timestamp_result != NULL)
		db_free_result(fingerprint_rule_commit_timestamp_result);	

	return commit_timestamp;


}


int init_database_service(){

	int retval;

	load_config();

	if(0 != (retval = db_connection_init(&db_context.db_conn, db_context.db_server_addr, db_context.db_username, db_context.db_pass, db_context.db_name))){
		PTRACE( INFO , CHRDC , "TLS fingerprint monitor clinet, Init db connection error\n");
		return retval;
	}

	PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, Init db service, successful\n");

	return 0;

}

void database_service_thread(){

	uint64_t time_counter=0;
	uint32_t rules_db_commit_timestamp;
	
	db_service_global_var.local_rules_update_timestamp = 0;
	tls_fp_traffic_mon_proc_policy.rules_db_update_timestamp = 0;

	client_gconf.db_service_status = SERVICE_STATUS_ACTIVE;

	while(1){
	
		//set policy update 
		if(SECOND_INTERVAL(time_counter,15)){
			rules_db_commit_timestamp = tls_fp_db_rules_commit_timestamp_fetch();
			if(tls_fp_traffic_mon_proc_policy.rules_db_commit_timestamp != rules_db_commit_timestamp){
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, Rules Fetch, started\n");
				tls_fp_bulk_rules_fetch();
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, %u  Rules Fetched\n"
					,tls_fp_traffic_mon_proc_policy.bulk_rules.rules_count);
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, Events Fetch, started\n");
				tls_fp_bulk_update_events_fetch();
				tls_fp_traffic_mon_proc_policy.rules_db_commit_timestamp = rules_db_commit_timestamp;
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, %u  Events Fetched\n"
					,tls_fp_traffic_mon_proc_policy.bulk_rules_update_events.curr_rule_update_event_count);
			}
		}else if(SECOND_INTERVAL(time_counter,1)){
			//get policy update 
			if(db_service_global_var.local_rules_update_timestamp != tls_fp_traffic_mon_proc_policy.rules_db_update_timestamp){
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, update timestamp update, started\n");
				db_update_timestamp_sync();
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, update timestamp updated at => %u\n", time(NULL));
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, Events removed, started\n");
				db_service_global_var.local_rules_update_timestamp = tls_fp_traffic_mon_proc_policy.rules_db_update_timestamp;
				tls_fp_bulk_update_events_remove();
				PTRACE( INFO , CHRDC , "TLS fingerprint monitor client, Events removed\n");
			}
			
		}
			
		time_counter++;
		sleep(1);	

		if(client_gconf.client_event == CLIENT_EXIT_EVENT){
			client_gconf.db_service_status = SERVICE_STATUS_WAIT_FOR_EXIT;
			wait_for_exit();
		}
	}

}





