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
	Essentially, this is where you setup your vehicle. Assuming you have already defined your vehicle's devices in vehicle_setup.h, you can now
	write a function to that sets up all of your devices and other components (loggers, timers, controllers, network channels, etc.). Now you can do stuff
	(by calling another functions or by doing everything in here, say in a while(1) loop).

*/

/* test function */


void test_physical(){

#ifdef TARGET_TARDIGRADE


	//This is a reference setup / configuration

	avoe_clock_t tel_timer; //telemetry timer
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	//tardigrade_setup_sensors_virtual(); //run the setup function in the vehicle_setup.h file
	tardigrade_setup_physical(); //run the setup function in the vehicle_setup.h file

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

#endif


}

void test_virtual(){
	/* This is a reference setup / configuration */
	

	// TIMERS
	avoe_clock_t tel_timer; //telemetry timer
	avoe_clock_t network_timer; //telemetry timer
	avoe_clock_t sensor_timer; //telemetry timer

	// LOGGING
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	// SENSOR SETUP CALLS
	tardigrade_setup_virtual(); //run the setup function in the vehicle_setup.h file

	// NETWORK SETUP
	avoe_comm_transmitter tx_device1("sensor", "imu_message", 8101, "127.0.0.1");	
	tx_device1.add_sensor(&tardigrade_imu); //set source to imu
	tx_device1.add_sensor(&tardigrade_pressure); //set source to imu
	tx_device1.add_sensor(&tardigrade_leak); //set source to imu

	tx_device1.set_timer(100); //set 100ms transmit interval


	char vector_str_decoded[64];
	char vector_str[64];
	initStr(vector_str, 64);
	vector_t translational_vector;
	avoe_comm_reciever rx_device1("message", "vector", 8110);
	rx_device1.set_timer(10);
	rx_device1.set_message(vector_str, 64);
	
	
	char message[] = "look here look listen";
	avoe_comm_transmitter tx_device4("message", "test_message", 8200, "127.0.0.1");	
	tx_device4.set_message(message, 32); //set source to message
	tx_device4.set_timer(200); //set 200ms transmit interval

	// RESET TIMERS
	tel_timer.reset(); 
	sensor_timer.reset();
	network_timer.reset();

	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE

	while (1){ 
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > 100){
			tardigrade_update_sensors_dummy();
			// send vectors to controller

			avoe_comm_reciever_decode_message(vector_str_decoded, vector_str, 64);
			translational_vector = comma_str_to_vector_t(vector_str_decoded, 64);
			//std::cout << translational_vector.x << ' ' << translational_vector.y << ' ' << translational_vector.z << '\n';
			controller.send_vector(translational_vector);
		
			sensor_timer.reset();
		}
		
		// NETWORK REFRESH
		tx_device1.refresh();
		rx_device1.refresh();

		if (network_timer.getElaspedTimeMS() > 10){
			//manual network functions may be placed in here
			
			network_timer.reset();
		}
	

		// DISPLAY OUTPUT AND LOGGING

		if (tel_timer.getElaspedTimeMS() > 1000){
			std::cout << "[MAIN] vector_str from frontend: " << vector_str << '\n';
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
