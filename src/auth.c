#include "auth.h"
#include <string.h>

union db d;

int auth_init_mysql(const char* host, int port, const char* user, const char* pass, const char* dbname) {
	d.mysql = mysql_init(NULL);

	init_mysql(d.mysql, host, port, user, pass, dbname);
	
	return 0;
}

int auth_init_mongo(const char* host, int port, const char* dbname) {
	mongo_init(d.mngdb);
	d.mysql = NULL;
	
	int status = mongo_connect(d.mngdb, host, port);
	
	if( status != MONGO_OK ) {
		switch ( d.mngdb->err ) {
			case MONGO_CONN_SUCCESS:     break;
			case MONGO_CONN_NO_SOCKET:   return -1;
			case MONGO_CONN_FAIL:        return -1;
			case MONGO_CONN_NOT_MASTER:  return -1;
			default: return -1;
		}
	}
	
	return 0;
}

void auth_cleanup() {
	// either one is initializes
	if(d.mysql != NULL)
		mysql_close(d.mysql);
	else if(d.mngdb != NULL)
		mongo_destroy(d.mngdb);
}

int compare_uid(int uid, int pin) {
	if(d.mysql != NULL) { // for mysql
		// initialize variables for MYSQL
		MYSQL_RES *result;
		MYSQL_ROW row;
		int num_fields;
		int i;
			
		// gets the pin value from the astpbx table for the given uid and queries it
		char* x = (char*)malloc(100);
		sprintf(x, "SELECT `pin` FROM astpbx WHERE `uid` = %d", uid);
		
		mysql_query(d.mysql, x);
		result = mysql_store_result(d.mysql);

		num_fields = mysql_num_fields(result);
		
		// loops thru results and compares it to the pin
		while ((row = mysql_fetch_row(result))) {
			for(i = 0; i < num_fields; i++) {
				if(atoi(row[i]) == pin) {
					return 0;
				}
			}
		}
	} else if(d.mngdb != NULL) {
		
	}

	return 1;
}
