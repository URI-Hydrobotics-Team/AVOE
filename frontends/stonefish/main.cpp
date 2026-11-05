/*
	stonefish frontend for AVOE
	URI Hydrobotics
	
*/
#include <cstring>
#include <iostream>

/* AVOE specific includes */
#include "config.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../core/io.h"
#include "../../lib/vt100.h"
#include "../../lib/clock.h"
#include "vehicle_setup.h"

void tardigrade_simulation(){






}


int main(int argc, char **argv){


	/* parse arguments */

	if (argc == 1){
		std::cout << "At least one arguments is required. Try ./avoe-stonefish help\n";
		return 0;

	}



	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	
	}




	return 0;
}
