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
//#include "../lib/lib.h"
#include "config.h"
#include "log.h"
#include "vehicle.h"
#include "controller.h"
#include "../lib/network.h"


/* Robot specific*/
#include "sensors.h"
#include "motors.h"
#include "tasks.h"

/* global variables for main */
avoe_clock_t system_time;
int verbose;


/* 
	verbose values: 
	0 - no verbose
	1 - full verbose
	(subject to change)	



*/

int control_mode;




/* test function */


void test(){

	/* this is a reference setup */

	avoe_clock_t tel_timer; //telemetry timer
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	tardigrade_setup_sensors(); //run the setup function in the sensors.h file
	

	while (1){ //the loop
		
		if (tel_timer.getElaspedTimeMS() > 1000){
			//update, print and log every one second
			tardigrade_update_sensors();
			tardigrade.print();
			test_log.log(imu.read(7)); //data field 7 (8th field) is temp for imu sensor

			tel_timer.reset(); //always reset
		}
	}
}

/* networking functions */

void transmitTelemetry(tx_socket socket, const char *header, const char *data, int time_stamp){
	/*
		transmit telemetry, such as sensor data to a reciever
		header string should adhere to a standard

	*/
	
	std::string str = "$VT "; // VEHICLE TELEMETRY 
	str += header; 
	str += ' ';
	if (time_stamp != 0){
		str += system_time.getTimeStr();
		str += ' ';
	
	}
	
	str += data;
	str += '$'; //Terminating character


	socket.transmit(str.c_str()); 

	if (verbose > 0){	
		std::cout << "[MAIN] transmitTelemtry Message: " << str.c_str() << '\n';;
	}
}


/* logging functions */

void logTelemetry(log_t log, const char *in, int arguments){
	/*
		log telemetry data

	*/


}




/* this could be your main loop for deployment*/
void run(){
	while (1){
		//"we call this the loop -LTG"
		
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
