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
#include "config.h"
#include "log.h"
#include "control.h"
#include "io.h"

/* target specific*/
#include "vehicle_setup.h"
#include "tasks.h"

/* 
	MAIN.CPP
	Essentially, this is where you setup your vehicle. Assuming you have already defined your vehicle's devices in sensors.h and motors.h, you can now
	write a function to that sets up all of your devices and other components (loggers, timers, controllers, network channels, etc.). Now you can do stuff
	(by calling another functions or by doing everything in here, say in a while(1) loop).

*/

/* test function */


void test_physical(){
/*
	//This is a reference setup / configuration

	avoe_clock_t tel_timer; //telemetry timer
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	//tardigrade_setup_sensors_virtual(); //run the setup function in the vehicle_setup.h file
	tardigrade_setup_sensors_physical(); //run the setup function in the vehicle_setup.h file
	tardigrade_setup_motors(); //run the setup function in the vehicle_setup.h file

	//transmit sensor data over network
	avoe_comm_transmitter tx_device1("sensor", "imu_message", 8101, "127.0.0.1");	
	tx_device1.set_sensor(&tardigrade_imu); //set source to imu
	tx_device1.set_timer(100); //set 500ms transmit interval
	//transmit char array over network
	char message[] = "look here look listen";
	avoe_comm_transmitter tx_device2("message", "test_message", 8200, "127.0.0.1");	
	tx_device2.set_message(message, 32); //set source to message
	tx_device2.set_timer(200); //set 200ms transmit interval


	while (1){ //the loop
	
		//tx_device1.refresh();
		tx_device2.refresh();
		//basic 1 second telemetry loop

		//std::cout << tel_timer.getElaspedTimeMS() << '\n';
		
		if (tel_timer.getElaspedTimeMS() > 1000){
			tardigrade_update_sensors_physical();
			//update, print and log every one second
			tardigrade.print();
			//test_log.log(imu.read(7)); //data field 7 (8th field) is temp for imu sensor
			tardigrade_imu.log(&test_log); //log imu sensor data
			tel_timer.reset(); //always reset
		}

		
	}

*/
}

void test_virtual(){

	/* This is a reference setup / configuration */

	avoe_clock_t tel_timer; //telemetry timer
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	tardigrade_setup_sensors_virtual(); //run the setup function in the vehicle_setup.h file
	tardigrade_setup_motors(); //run the setup function in the vehicle_setup.h file

	//transmit sensor data over network
	avoe_comm_transmitter tx_device1("sensor", "imu_message", 8101, "127.0.0.1");	
	tx_device1.set_sensor(&tardigrade_imu); //set source to imu
	tx_device1.set_timer(100); //set 500ms transmit interval
	//transmit char array over network
	char message[] = "look here look listen";
	avoe_comm_transmitter tx_device2("message", "test_message", 8200, "127.0.0.1");	
	tx_device2.set_message(message, 32); //set source to message
	tx_device2.set_timer(200); //set 200ms transmit interval

	std::cout << "setup complete\n";

	while (1){ //the loop
	
		tardigrade_update_sensors_dummy();
		//tx_device1.refresh();
		tx_device2.refresh();
		//basic 1 second telemetry loop
		if (tel_timer.getElaspedTimeMS() > 1000){
			//update, print and log every one second
			tardigrade.print();
			//test_log.log(imu.read(7)); //data field 7 (8th field) is temp for imu sensor
			tardigrade_imu.log(&test_log); //log imu sensor data
			tel_timer.reset(); //always reset
		}
	}
}


/* This could be your main loop for deployment*/
void run(){
	while (1){
		//"we call this the loop -LTG"
		
	}
}

/* Support functions for main */


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\trun\t(run)\n";
	std::cout << "\tverbose\t(run, but displays more debugging information)\n";
	std::cout << "\tlog\t(run with verbose and log to a file)\n";
	std::cout << "\ttest_virtual\t(run the test_virtual() function and quit)\n"; 
	std::cout << "\ttest_physical\t(run the test_physical() function and quit)\n"; 
}


int main(int argc, char *argv[]){

	/* DEFAULT ARGUMENTS */
	if (argv[1] == NULL){
		std::cout << "Must specify at least one argument. Try \"./avoe help\".\n";
		return 0;
	}

	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	}

	/* Define arguments for custom configurations here */

	if (strncmp(argv[1], "test_virtual", 16) == 0){
		test_virtual(); //points to a test config
		return 0;
	}
	if (strncmp(argv[1], "test_physical", 16) == 0){
		test_physical(); //points to a test config
		return 0;
	}
	return 0;

}
