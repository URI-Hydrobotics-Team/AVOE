/*

	URI Hydrobotics
	Christopher McRae
	
	AVOE core 

*/
/* system */
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
/* AVOE specific*/
#include "lib.h"
#include "config.h"
#include "log.h"
#include "vehicle.h"
#include "mission.h"
#include "../lib/network.h"

/* Robot specific*/
#include "sensors.h"
#include "motors.h"


/* global variables for main */
time_t global_time;
int verbose;
int control_mode;


/* sensor functions */

void initSensors(sensor_t sensors[], int sensor_count){

	for (int i = 0; i < sensor_count; i++){

		sensors[i].init();
	}

}

void printSensors(sensor_t sensors[], int sensor_count){

	for (int i = 0; i < sensor_count; i++){
		sensors[i].print();
	}

}


/* test function */


void test(){
	setupSensors();
	vehicle_t tardigrade("Tardigrade", "2", "AUV");
	tardigrade.updateSensorTable(tardigrade_sensors, 3);
	tardigrade.print();


	//printSensors(tardigrade_sensors, 3);
}





/* the main loop */


void run(){
	setupSensors();
	while (1){
		//"we call this, the loop"
		
	}
}

/* support functions for main */


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\trun\t(run)\n";
	std::cout << "\tverbose\t(run, but displays more debugging information)\n";
	std::cout << "\tlog\t(run with verbose and log to a file)\n";
	std::cout << "\ttest\t(run the test() function and quit)\n"; 
}




int main(int argc, char *argv[]){


	if (argv[1] == NULL){
		std::cout << "Must specify at least one argument. Try \"./avoe help\".\n";
		return 0;
	}

	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	}
	if (strncmp(argv[1], "test", 16) == 0){
		test();
		return 0;
	}







	return 0;

}
