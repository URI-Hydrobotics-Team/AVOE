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


void tardigrade_physical(){

#ifdef TARGET_TARDIGRADE

	//this is the tardigrade production routine	

	// TIMERS
	avoe_clock_t tel_timer; //telemetry timer
	avoe_clock_t network_timer; //telemetry timer
	avoe_clock_t sensor_timer; //telemetry timer

	// LOGGING
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	// SENSOR SETUP CALLS
	tardigrade_setup_physical(); //run the setup function in the vehicle_setup.h file

	// NETWORK SETUP
	avoe_comm_transmitter tx_device1("sensor", "imu_message", PORT_DECKBOX_TELEMETRY, IP_DECKBOX);	
	tx_device1.add_sensor(&tardigrade_imu); //set source to imu
	tx_device1.add_sensor(&tardigrade_pressure); //set source to imu
	tx_device1.add_sensor(&tardigrade_leak); //set source to imu



	tx_device1.set_timer(100); //set 100ms transmit interval


	char t_vector_str[64];
	char t_vector_str_decoded[64];
	initStr(t_vector_str, 64);

	char r_vector_str[64];
	char r_vector_str_decoded[64];
	initStr(r_vector_str, 64);


	vector_t translational_vector, rotational_vector;	
	avoe_comm_reciever rx_device1("message", "vector", PORT_DECKBOX_INPUT, 2048);
	rx_device1.set_timer(10);
	rx_device1.set_message(vector_str, 64);
	

	avoe_comm_reciever rx_device2("message", "vector", 8112, 2048);
	rx_device2.set_timer(10);
	rx_device2.set_message(r_vector_str, 64);
	
	// RESET TIMERS
	tel_timer.reset(); 
	sensor_timer.reset();
	network_timer.reset();

	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	tardigrade_update_sensors_physical();
	
	int count = 0;
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			// send vectors to controller

			avoe_comm_reciever_decode_message(t_vector_str_decoded, t_vector_str, 64); //latteral (lower half)
			avoe_comm_reciever_decode_message(r_vector_str_decoded, r_vector_str, 64); //latteral (lower half)
			
			
			translational_vector = comma_str_to_vector_t(t_vector_str_decoded, 64);
			rotational_vector = comma_str_to_vector_t(r_vector_str_decoded, 64); //second half
			
			controller_full.send_translation_vector(translational_vector);
			controller_full.send_lateral_vector(rotational_vector);
			sensor_timer.reset();
;
		}
		
		// NETWORK REFRESH
		tx_device1.refresh();
		rx_device1.refresh();
		rx_device2.refresh();
		if (network_timer.getElaspedTimeMS() > NETWORK_UPDATE_INTERVAL){
			//manual network functions may be placed in here
			
			network_timer.reset();
		}
	

		// DISPLAY OUT AND SEND THRUSTERS

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			std::cout << "[MAIN] t_vector_str from frontend: " << t_vector_str << '\n';
			std::cout << "[MAIN] r_vector_str from frontend: " << r_vector_str << '\n';
			//test_log.log(imu.read(7)); //data field 7 (8th field) is temp for imu sensor
			tardigrade_imu.log(&test_log); //log imu sensor data
			tel_timer.reset(); //always reset
		}
	}




#endif


}

void tardigrade_virtual(){
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
	avoe_comm_transmitter tx_device1("sensor", "telemetry", PORT_DECKBOX_TELEMETRY, IP_DECKBOX);	
	tx_device1.add_sensor(&tardigrade_imu); //set source to imu
	tx_device1.add_sensor(&tardigrade_pressure); //set source to imu
	tx_device1.add_sensor(&tardigrade_leak); //set source to imu
	tx_device1.add_motor(&thruster_SH);
	tx_device1.add_motor(&thruster_BSH);
	tx_device1.add_motor(&thruster_BPH);
	tx_device1.add_motor(&thruster_Y);



	tx_device1.set_timer(100); //set 100ms transmit interval
	vector_t translational_vector, rotational_vector;
	avoe_comm_reciever rx_device("message", "vector", PORT_DECKBOX_INPUT, 2048);
	rx_device.set_timer(10);
	rx_device.add_vector(&translational_vector);
	rx_device.add_vector(&rotational_vector);
	
	
	// RESET TIMERS
	tel_timer.reset(); 
	sensor_timer.reset();
	network_timer.reset();

	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	tardigrade_update_sensors_dummy();

	int count = 0;

	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_dummy();
			controller_full.send_translation_vector(translational_vector);
			controller_full.send_lateral_vector(rotational_vector);
			sensor_timer.reset();
		}
		
		// NETWORK REFRESH
		tx_device1.refresh();
		rx_device.refresh();

		if (network_timer.getElaspedTimeMS() > NETWORK_UPDATE_INTERVAL){
			//manual network functions may be placed in here
			
			network_timer.reset();
		}
	

		// DISPLAY OUTPUT AND LOGGING

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			//update, print and log every one second
			tardigrade.print();
			//test_log.log(imu.read(7)); //data field 7 (8th field) is temp for imu sensor
			tardigrade_imu.log(&test_log); //log imu sensor data
			tel_timer.reset(); //always reset
		}
	}
}

/* Support functions for main */


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\ttardigrade_virtual\t(run the tardigrade_virtual() function and quit)\n"; 
	std::cout << "\ttardigrade_physical\t(run the tardigrade_physical() function and quit)\n"; 
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

	if (strncmp(argv[1], "tardigrade_virtual", 32) == 0){
		tardigrade_virtual(); //points to a test config
		return 0;
	}
	if (strncmp(argv[1], "tardigrade_physical", 32) == 0){
		tardigrade_physical(); //points to a test config
		return 0;
	}
	std::cout << "Invalid Argument. Try \"avoe help\"\n";

	return 0;

}
