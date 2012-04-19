#pragma once

#include <my_global.h>
#include <mysql.h>
#include "mongo/mongo.h"

// only mysql or mongo can be initialized at once
union db {
	MYSQL* mysql;
	mongo mngdb[1];
};

// initializes mysql
int init_mysql(MYSQL * conn,const char* host, int port, const char* user, const char* pass, const char* dbname);

// initializes mongo
int init_mongo(union db);
