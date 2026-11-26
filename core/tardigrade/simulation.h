/*

	URI Hydrobotics
	TARDIGRADE SIMULATION

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


// TARDIGRADE SIMULATION CONFIGURATION //

void tardigrade_simulation(){
	/* This mode is used with stonefish  */
	

	// TIMERS
	avoe_clock_t tel_timer; //telemetry timer
	avoe_clock_t network_timer; //telemetry timer
	avoe_clock_t sensor_timer; //telemetry timer

	// LOGGING
	log_t test_log; // setup a logger
	test_log.init(); // initilize the logger

	// SENSOR SETUP CALLS
	tardigrade_setup_simulation(); //run the setup function in the vehicle_setup.h file

	// NETWORK SETUP
	avoe_comm_reciever simulation_in("sensor", "telemetry", PORT_SIM_SENSOR_IN, 2048);	
	avoe_comm_transmitter simulation_out("motor", "telemetry", PORT_SIM_MOTOR_OUT, IP_SIM);
	avoe_comm_transmitter telemetry("sensor", "telemetry", PORT_DECKBOX_TELEMETRY, IP_DECKBOX);	
	avoe_comm_reciever dekcbox_control("message", "vector", PORT_DECKBOX_INPUT, 2048);
		


	vector_t translational_vector, rotational_vector;

	//bind sensors and motors to network objects
	// order matters
	telemetry.add_sensor(&tardigrade_imu); //set source to imu
	telemetry.add_sensor(&tardigrade_pressure); //set source to imu
	telemetry.add_sensor(&tardigrade_leak); //set source to imu
	telemetry.add_motor(&thruster_SH);
	telemetry.add_motor(&thruster_BSH);
	telemetry.add_motor(&thruster_BPH);
	telemetry.add_motor(&thruster_Y);

	simulation_in.add_sensor(&tardigrade_imu); //set source to imu
	simulation_in.add_sensor(&tardigrade_pressure); //set source to imu
	simulation_in.add_sensor(&tardigrade_leak); //set source to imu

	simulation_out.add_motor(&thruster_SH);
	simulation_out.add_motor(&thruster_BSH);
	simulation_out.add_motor(&thruster_BPH);
	simulation_out.add_motor(&thruster_Y);
	simulation_out.add_motor(&thruster_PS);
	simulation_out.add_motor(&thruster_SS);
	
	dekcbox_control.add_vector(&translational_vector);
	dekcbox_control.add_vector(&rotational_vector);


	//setup network timer intervals
	simulation_out.set_timer(100);
	simulation_in.set_timer(100);
	telemetry.set_timer(100);
	dekcbox_control.set_timer(10);


	
	
	// RESET TIMERS
	tel_timer.reset(); 
	sensor_timer.reset();
	network_timer.reset();

	std::cout << "[MAIN] AVOE SETUP COMPLETE\n"; // DONE
	
	tardigrade_update_sensors_dummy();

	// sample vector
	translational_vector.x = 0.5;
	translational_vector.y = 0.5;
	translational_vector.z = 0.5;

	//jensen
	while (1){
		usleep(1000);
		//the loop

		// UPDATE YOUR SENSORS
		if (sensor_timer.getElaspedTimeMS() > TARDIGRADE_SENSOR_UPDATE_INTERVAL){
			//controller_full.send_translation_vector(translational_vector);
			//controller_full.send_lateral_vector(rotational_vector);
			
			// send vectors to controller
			if (translational_vector.x == 0 && translational_vector.y == 0 && translational_vector.z == 0){


				controller_full.send_lateral_vector(rotational_vector);
			}

			if (rotational_vector.x == 0 && rotational_vector.y == 0 && rotational_vector.z == 0){ 
				controller_full.send_translation_vector(translational_vector);
			}

			sensor_timer.reset();
		}
		
		// NETWORK REFRESH

		simulation_out.refresh();
		simulation_in.refresh();
		telemetry.refresh();
		dekcbox_control.refresh();

		if (network_timer.getElaspedTimeMS() > NETWORK_UPDATE_INTERVAL){
			//manual network functions may be placed in here
                        //trackTransmissionTime(&network_timer);
			
		}
	

		// DISPLAY OUTPUT AND LOGGING

		if (tel_timer.getElaspedTimeMS() > DISPLAY_OUTPUT_INTERVAL){
			vtClear();
			tardigrade.print();
			//std::cout << "translational vector " << translational_vector.x << " " << translational_vector.y << " " << translational_vector.z << '\n';
			//tardigrade_imu.log(&test_log); //log imu sensor data


			tel_timer.reset(); //always reset
		}
	}
}

