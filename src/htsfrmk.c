#include "cagi/cagi.h"
#include "core.h"
#include "auth.h"
#include <string.h>
#include "iniparser/iniparser.h"
#include "iniparser/dictionary.h"
#include "mongo/mongo.h"

char line[100];

int main(int argc, char** argv) {
	// initializes needed functions
	setlinebuf(stdout);
    setlinebuf(stdin);
    while (1) {
		fgets(line,100,stdin);
        if (strlen(line) <= 1) break;
    }
    
	// retrieves the configuration
    char* ini_name = "/home/agro/pbxwork/pbxframework/config.ini";
	dictionary* ini;

	ini = iniparser_load(ini_name);
	if(ini == NULL) {
		perror("The dictionary file name is null!");
		return -1;
	}
	
	// gets the database information
	char* dbtype = iniparser_getstring(ini, "db:dbdriver", "-1");
	if(strcmp(dbtype, "-1") == 0) {
		perror("Error in retrieving the database to use!");
		return -1;
	}

	if(strcmp(dbtype, "mysql") == 0) {
		char* host = iniparser_getstring(ini, "mysql:host", "-1");
		char* user = iniparser_getstring(ini, "mysql:user", "-1");
		char* pass = iniparser_getstring(ini, "mysql:pass", "-1");
		char* dbname = iniparser_getstring(ini, "mysql:dbname", "-1");
		int port = iniparser_getint(ini, "mysql:port", -1);
		
		// none of them can be wrong
		if(strcmp(host, "-1") == 0) {
			perror("The host wasn't able to be read!");
			return -1;
		}
		if(strcmp(host, "-1") == 0) {
			perror("The user wasn't able to be read!");
			return -1;
		}
		if(strcmp(host, "-1") == 0) {
			perror("The pass wasn't able to be read!");
			return -1;
		}
		if(strcmp(dbname, "-1") == 0) {
			perror("The dbname wasn't able to be read!");
			return -1;
		}
		if(port == -1) {
			perror("The port wasn't able to be read!");
			return -1;
		}
		
		if(auth_init_mysql(host, port, user, pass, dbname) == -1) {
			return -1;
		}
	} else if(strcmp(dbtype, "mongo") == 0) {
		char* host = iniparser_getstring(ini, "mongo:host", "-1");
		int port = iniparser_getint(ini, "mongo:port", -1);
		
		if(strcmp(host, "-1") != 0) {
			perror("The user wasn't able to be read!");
			return -1;
		}
		if(port == -1) {
			perror("The port wasn't able to be read!");
			return -1;
		}
		
		if(auth_init_mongo(host, port, "") == -1) {
			return -1;
		}
	}
    
	iniparser_freedict(ini);
	
	// starts the authentication
    
	//retrieves user id and pin
	stream_file("/home/agro/pbxwork/pbxframework/sounds/userid", "#", "");
	
	char* id = malloc(10);
	get_input(id);
	
	stream_file("/home/agro/pbxwork/pbxframework/sounds/pin", "#", "");
	char* pin = malloc(10);
	get_input(pin);
	
	// compares info with db info
	if(compare_uid(atoi(id), atoi(pin)) == 0) { // the user's info is valid
		stream_file("/home/agro/pbxwork/pbxframework/sounds/accepted", "#", "");
	} else { // the user's info is not valid
		stream_file("/home/agro/pbxwork/pbxframework/sounds/sorry", "#", "");
		hangup("");
	}
	
	// authentication is done and you can start the mission system
	
	start_mission_system();
	
	return 0;
}
