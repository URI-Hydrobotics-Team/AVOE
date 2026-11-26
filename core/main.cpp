/*

	URI Hydrobotics
	Christopher McRae
	
	AVOE core 

*/
/* system */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/* AVOE specific*/
#include "../lib/globals.h"
#include "../lib/vt100.h"
#include "config.h"
#include "log.h"
#include "io.h"
#include "task.h"


/* target specific*/
#include "vehicle_setup.h"
#include "tasks.h"

/* modes */

#include "tardigrade/imu_dump.h"
#include "tardigrade/imu_test.h"
#include "tardigrade/remote.h"
#include "tardigrade/simulation.h"
#include "tardigrade/task1.h"
#include "tardigrade/task2.h"
#include "tardigrade/task3.h"
#include "tardigrade/task_box.h"
#include "tardigrade/task_coin_flip.h"
#include "tardigrade/task_imu_test.h"
#include "tardigrade/task_vertical_test.h"
#include "tardigrade/template.h"
#include "tardigrade/virtual.h"


/* 
	MAIN.CPP
	Essentially, this is where you setup your vehicle and implement its behaviour. Assuming you have already defined your vehicle's objects in vehicle_setup.h, you can now
	write a function that sets up all of your vehicle and systm (loggers, timers, controllers, network channels, etc.) objects. Now you have an environment
	in which you can do stuff.

*/


// CORE MAIN FUNCTIONS //

//Support Functions for tardigrade Modes
void trackTransmissionTime(avoe_clock_t* timestamp){
	printf("trasmission loop time: %ld\n", timestamp->getElaspedTimeMS());
	timestamp->reset();
}




void parser_test(const char *filename){
	// a test function for avoe's parsing capabilities

	printf("[AVOE] Parser Test Starting\n");
	printf("Parsing file: \"%s\"\n", filename);


	FILE *fptr;
	fptr = fopen(filename, "r");	
	
	if (fptr == NULL){
		printf("[ERROR] could not open file\n");
		return;

	}

	char buffer[64];
	char token[64], field[64];
	

	//for (int i = 0; i < 10; i++){

	while(!feof(fptr)){
		memset(buffer, 0, 64);
		memset(field, 0, 64);
		memset(token, 0, 64);

		readLine(buffer, 64, fptr);
		printf("read from %s: %s\n", filename, buffer);
		avoe_parse_config_line(buffer, field, token);		
		printf("\textracted %s %s\n", field, token);


	
	}

	fclose(fptr);

	printf("[AVOE] Parser Test Done\n");
}




void avoe_standard(){

	/*
	SUPPORTS
		sensor
		motor
		vector_t
		log
		io
		
		drivers
			imu-dummy
			leak-sensor-dummy
			pressure-sensor-dummy
			sos-leak
			ppsti
			avoe_user_io?


		frotends
			cli


		controllers
			tardigrade
			tardigrade_basic

		mission_control
			tardigrade_mc_relative
	

	*/


	//parse .vehicle and create vehicle object
	//parse .network and create network objects
	//bind objects to network
	//parse .objects and bind vectors, controllers, etc.
	

	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE

	while (1){
		usleep(1000);

	}


}



void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\tstandard <vehicle setup file>\t(fully parsed AVOE, coming soon)\n";
	std::cout << "\tparser_test <filename>\t(parser test)\n";
	std::cout << "\ttardigrade_virtual\t(run the default tardigrade virtual configuration for testing)\n"; 
	std::cout << "\ttardigrade_simulation\t(run tardigrade simulation configuration for testing with stonefish)\n"; 
	std::cout << "\ttardigrade_remote\t(run remotely operable tardigrade configuration must be compiled with physical target)\n"; 
	std::cout << "\ttardigrade_task <task number>\t(place holder robosub task)\n"; 

}

int main(int argc, char *argv[]){

	std::cout << "[MAIN] AVOE STARTING UP\n";
	/* DEFAULT ARGUMENTS */
	if (argv[1] == NULL){
		std::cout << "Must specify at least one argument. Try \"./avoe help\".\n";
		return 0;
	}

	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	}

	if (strncmp(argv[1], "standard", 16) == 0){
		avoe_standard();
		return 0;
	}


	if (strncmp(argv[1], "parser_test", 16) == 0){
		parser_test(argv[2]);
		return 0;
	}

	/* Define arguments for custom configurations here */

	if (strncmp(argv[1], "tardigrade_virtual", 32) == 0){
		tardigrade_virtual();
		return 0;
	}

	if (strncmp(argv[1], "tardigrade_simulation", 32) == 0){
		tardigrade_simulation();
		return 0;
	}
	if (strncmp(argv[1], "tardigrade_remote", 32) == 0){
		tardigrade_remote();
		return 0;
	}

	if (strncmp(argv[1], "tardigrade_imu_dump", 32) == 0){
		tardigrade_imu_dump();
		return 0;
	}



	if (strncmp(argv[1], "tardigrade_task", 32) == 0){
		if (strncmp(argv[2], "qual", 16) == 0){
		
			tardigrade_task_1();
			return 0;
		}
		if (strncmp(argv[2], "two", 16) == 0){
		
			tardigrade_task_2();
			return 0;
		}

		if (strncmp(argv[2], "three", 16) == 0){
		
			tardigrade_task_3();
			return 0;
		}
		if (strncmp(argv[2], "imu_test", 16) == 0){
		
			tardigrade_task_imu_test();
			return 0;
		}


		if (strncmp(argv[2], "box", 16) == 0){
		
			tardigrade_task_box();
			return 0;
		}

		if (strncmp(argv[2], "vertical_test", 16) == 0){
		
			tardigrade_task_vertical_test();
			return 0;
		}
		if (strncmp(argv[2], "coin_flip", 16) == 0){
	
			if (argc != 4){
				printf("coin flip takes angle, aborting\n");
				return 0;
			}
			char coin_flip_angle_str[16];
			initStr(coin_flip_angle_str, 16);
			strncpy(coin_flip_angle_str, argv[3], 16);
			int coin_flip_angle = atoi(coin_flip_angle_str);

	
			tardigrade_task_coin_flip(coin_flip_angle);
			return 0;
		}




		std::cout << "Invalid Task. Try \"avoe help\"\n";

		return 0;
	}


	std::cout << "Invalid Argument. Try \"avoe help\"\n";

	return 0;

}
