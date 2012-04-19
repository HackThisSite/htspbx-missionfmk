#include "database.h"

// initializes the mysql instance
int init_mysql(MYSQL * conn, const char* host, int port, const char* user, const char* pass, const char* dbname) {
	// if the instance wasn't able to initialize, return -1
	if (conn == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return -1;
	}
	
	// if the connection couldn't reach the databse, return -1
	if(mysql_real_connect(conn, host, user, pass, dbname, port, NULL, 0) == NULL) {
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return -1;	
	}
	
	return 0;
}

// initializes the mongo instance
int init_mongo(union db d) {
	
	return 0;
}
