#include "core.h"
#include "iniparser/iniparser.h"
#include "iniparser/dictionary.h"
#include "cagi/cagi.h"
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// gets input from AGI
void get_input(char* c) {
	strcpy(c, "");
	while(1) {
		int i = wait_for_digit("-1");
		char* n = (char*) malloc(10 * sizeof(char));
		sprintf(n, "%d", i);
		
		if(i == 35) {
			break;
		} else if(i != 35 && i >= 0) {
			i-=48;
			n = (char*) malloc(10 * sizeof(char));
			sprintf(n, "%d", i);
			strcat(c, n);
		}
	}
}

// starts the mission system for a user
void start_mission_system() {
	int result = 0;
	int running = 1;
	
	char* ini_name = "/home/agro/pbxwork/pbxframework/missions.ini";
	dictionary * ini = iniparser_load(ini_name);
	
	char* mid, *fn, *predesc, *preloc, *description, *location;
	
	while(running) {
		stream_file("/home/agro/pbxwork/pbxframework/sounds/mission", "#", "");
	
		// gets the mission id
		mid = malloc(MAX_SIZE);
		get_input(mid);
		
		// crafts the mission name
		fn = malloc(MAX_SIZE);
		sprintf(fn, "mission%s", mid);

		predesc = malloc(MAX_SIZE);
		sprintf(predesc, "%s:description", fn);
		description = iniparser_getstring(ini, predesc, "-1");
		
		exec("FESTIVAL", description);
		
		preloc = malloc(MAX_SIZE);
		sprintf(preloc, "%s:location", fn);
		location = iniparser_getstring(ini, preloc, "-1");
		
		result = (system(location)) / 256;
	}
	
	iniparser_freedict(ini);
}
