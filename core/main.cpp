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


/* 

	ROBOSUB TASKS
	This is the simplest way to implement task selection, essentially each task is it's own target. A better way would be to integrate this into a 'tardigrade_physical()' function that handles selecting tasks based on signals recieved from deckbox.
	


*/



void tardigrade_task_1(){
	printf("[MAIN] QUALIFICATION TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
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

	// INIT TASKS
	write_tasks_qualification();


	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	
	tardigrade_mc_basic_t mc_ren;
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	mc_ren.init(&controller_full, &tardigrade_imu, qualification_robosub_2026, 3, 0.1, false, false, false);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	mc_ren.start();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// AUTONOMY		
		mc_ren.refresh();
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}

void tardigrade_task_2(){

	printf("[MAIN] QUALIFICATION TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
#ifdef TARGET_TARDIGRADE
#endif

}

void tardigrade_task_3(){

	printf("[MAIN] QUALIFICATION TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
#ifdef TARGET_TARDIGRADE
#endif

}


void tardigrade_task_imu_test(){
	printf("[MAIN] IMU TEST TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
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

	// INIT TASKS
	write_tasks_imu_test();


	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	
	tardigrade_mc_basic_t mc_ren;
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	mc_ren.init(&controller_full, &tardigrade_imu, imu_test_task, 1, 0.015, true, false, false);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	mc_ren.start();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// AUTONOMY		
		mc_ren.refresh();
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}

void tardigrade_task_box(){
	printf("[MAIN] BOX TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
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

	// INIT TASKS
	write_tasks_box();


	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	
	tardigrade_mc_basic_t mc_ren;
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	mc_ren.init(&controller_full, &tardigrade_imu, box_task, 7, 0.015, true, false, false);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	mc_ren.start();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// AUTONOMY		
		mc_ren.refresh();
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}

void tardigrade_task_vertical_test(){
	printf("[MAIN] VERTICAL TEST TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
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

	// INIT TASKS
	write_tasks_vertical_test();


	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	
	tardigrade_mc_basic_t mc_ren;
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	mc_ren.init(&controller_full, &tardigrade_imu, vertical_test_task, 1, 0.015, false, false, false);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	mc_ren.start();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// AUTONOMY		
		mc_ren.refresh();
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}


void tardigrade_task_coin_flip(int angle){
	printf("[MAIN] COIN FLIP TASK STARTING FOR  %d DEGREES: %dS UNTIL START\n", angle, TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
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

	// INIT TASKS
	write_tasks_coin_flip(angle);


	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	/*
	need to initialize sensors first before use
	A buffer overflow and seg fault could happen
	when sensor_timer.getElaspedTimeMS() <= 100
	due to appendstr access allocated but uninitialized values
	*/
	
	tardigrade_mc_basic_t mc_ren;
	std::cout << "[MAIN] Delaying for IMU startup\n";
	usleep(1000 * 1000* 1);
	mc_ren.init(&controller_full, &tardigrade_imu, coin_flip_task, 3, 0.015, true, false, false);
	
	tardigrade_update_sensors_physical();
	tardigrade_update_sensors_physical();
	mc_ren.start();
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// AUTONOMY		
		mc_ren.refresh();
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}


/* OTHER STUFF*/

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
			tardigrade_update_sensors_physical();
			sensor_timer.reset();
		}
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();


		// DISPLAY

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			//set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade_imu.print();
			tel_timer.reset(); //always reset
		}
	}



#endif


}


void tardigrade_remote(){

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
	avoe_comm_transmitter tx_device("sensor", "telemetry", PORT_DECKBOX_TELEMETRY, IP_DECKBOX);	
	tx_device.add_sensor(&tardigrade_imu); //set source to imu
	tx_device.add_sensor(&tardigrade_pressure); //set source to imu
	tx_device.add_sensor(&tardigrade_leak); //set source to imu
	tx_device.add_motor(&thruster_SH);
	tx_device.add_motor(&thruster_BSH);
	tx_device.add_motor(&thruster_BPH);
	tx_device.add_motor(&thruster_Y);


	tx_device.set_timer(100); //set 100ms transmit interval
	

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
	tardigrade_update_sensors_physical();
	
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_physical();
			
			// send vectors to controller
			if (translational_vector.x == 0 && translational_vector.y == 0 && translational_vector.z == 0){


				controller_full.send_lateral_vector(rotational_vector);
			}

			if (rotational_vector.x == 0 && rotational_vector.y == 0 && rotational_vector.z == 0){ 
				controller_full.send_translation_vector(translational_vector);
			}

			//controller.send_vector(translational_vector);
			sensor_timer.reset();
		}
		
		// NETWORK REFRESH
		tx_device.refresh();
		rx_device.refresh();
		if (network_timer.getElaspedTimeMS() > NETWORK_UPDATE_INTERVAL){
			//manual network functions may be placed in here
			
			network_timer.reset();
		}
	

		// DISPLAY OUT AND SEND THRUSTERS

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			set_ppsti_data(&thruster_BPH, &thruster_BSH, &thruster_SH, &thruster_Y, &thruster_PS, &thruster_SS);

			//update, print and log every one second
			tardigrade.print();
			std::cout << "TRANSLATIONAL VECTOR " << translational_vector.x << " " << translational_vector.y << " " << translational_vector.z << '\n';

			std::cout << "ROTATIONAL VECTOR " << rotational_vector.x << " " << rotational_vector.y << " " << rotational_vector.z << '\n';
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

	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			tardigrade_update_sensors_dummy();
			controller_full.send_translation_vector(translational_vector);
			controller_full.send_lateral_vector(rotational_vector);

			//controller.send_vector(translational_vector);

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
			std::cout << "translational vector " << translational_vector.x << " " << translational_vector.y << " " << translational_vector.z << '\n';
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
	std::cout << "\ttardigrade_virtual\t(run tardigrade virtual configuration for testing)\n"; 
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

	/* Define arguments for custom configurations here */

	if (strncmp(argv[1], "tardigrade_virtual", 32) == 0){
		tardigrade_virtual();
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
