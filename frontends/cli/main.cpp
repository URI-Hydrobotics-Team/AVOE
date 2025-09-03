/*
	Reference CLI frontend for AVOE
	URI Hydrobotics
	
*/
#include <cstring>
#include <iostream>

/* AVOE specific includes */
#include "config.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../lib/controller.h"
#include "../../lib/keyboard.h"
/* network setup */




/* network helper functions */




void raw(){





}


void test(){




}


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	//std::cout << "Frontend Version " << AVOE_CLI_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe-backend-cli <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\traw\t(displays all telemtry in a crude output)\n";
	std::cout << "\ttest\t(run the test() function and quit)\n"; 


}


int main(int argc, char *argv[]){



	/* parse arguments */

	if (argc == 1){
		std::cout << "At least one arguments is required. Try ./avoe-frontend-cli help\n";
		return 0;

	}



	if (strncmp(argv[1], "help", 16) == 0){

		printHelp();
		return 0;
	

	}

}
