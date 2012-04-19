#pragma once

#include "database.h"

union db d;

// initializes the authentication for mysql
int auth_init_mysql(const char* host, int port, const char* user, const char* pass, const char* dbname);

// ininitializes the authentication for mongo
int auth_init_mongo(const char* host, int port, const char* dbname);

// compares a user id and pin with the database
int compare_uid(int uid, int pin);

// cleans up any database connection
void auth_cleanup();
