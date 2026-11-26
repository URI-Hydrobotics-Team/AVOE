/*

	URI Hydrobotics
	Template Mode

*/


/* system */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/* AVOE specific*/
#include "../../lib/globals.h"
#include "../../lib/vt100.h"
#include "../config.h"
#include "../log.h"
#include "../io.h"
#include "../task.h"



/* target specific*/
#include "../vehicle_setup.h"
#include "../tasks.h"

void tardigrade_imu_dump(){
	printf("[MAIN] IMU DUMP\n");
	//this is the tardigrade production routine	

	#ifdef TARGET_TARDIGRADE
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
	avoe_comm_transmitter tx_device("sensor", "telemetry", PORT_DECKBOX_TELEMETRY, IP_DECKBOX);	

	avoe_comm_reciever rx_device("message", "vector", PORT_DECKBOX_INPUT, 2048);

	tx_device.add_sensor(&tardigrade_imu); //set source to imu
	tx_device.add_sensor(&tardigrade_pressure); //set source to imu
	tx_device.add_sensor(&tardigrade_leak); //set source to imu
	tx_device.add_motor(&thruster_SH);
	tx_device.add_motor(&thruster_BSH);
	tx_device.add_motor(&thruster_BPH);
	tx_device.add_motor(&thruster_Y);


	tx_device.set_timer(100); //set 100ms transmit interval
	

	vector_t translational_vector, rotational_vector;	
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
	
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			//set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){

			
			//update, print and log every one second
			tardigrade_imu.print();
			tel_timer.reset(); //always reset
			vtClear();
		}
	}



#endif


}

