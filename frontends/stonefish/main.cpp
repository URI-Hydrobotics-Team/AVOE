/*
	stonefish frontend for AVOE
	URI Hydrobotics
	
*/
#include <cstring>
#include <iostream>

/* AVOE specific includes */
#include "config.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../core/io.h"
#include "../../lib/vt100.h"
#include "../../lib/clock.h"
#include "vehicle_setup.h"

/*

	How it works
	stonefish provides a callback in the form of a method apart sf::SimulationManager: SimulationStepCompleted(Scalar timeStep), this method can be overrided. 

	All setup will be done in main.
	The SimulationStepCompleted override will point to the main avoe-frontend loop.
	the avoe-frontend loop will contain the usual AVOE stuff along with any middleware calls	



*/




void tardigrade_simulation(){

	printf("[AVOE] Tardigrade Stonefish Starting\n");

	tardigrade_setup_sensors_virtual();
	std::cout << "[DEBUG] Sensor Setup Done\n";

	/* setup and initilizae all connections */	
	frontend_to_core.add_sensor(&tardigrade_imu);
	frontend_to_core.add_sensor(&tardigrade_pressure);
	frontend_to_core.add_sensor(&tardigrade_leak);

	core_to_frontend.add_motor(&thruster_SH);
	core_to_frontend.add_motor(&thruster_BSH);
	core_to_frontend.add_motor(&thruster_BPH);
	core_to_frontend.add_motor(&thruster_Y);
	core_to_frontend.add_motor(&thruster_PS);
	core_to_frontend.add_motor(&thruster_SS);


	core_to_frontend.set_timer(NETWORK_REFRESH_INTERVAL);
	frontend_to_core.set_timer(NETWORK_REFRESH_INTERVAL);

	
	network_timer.reset();
	ui_timer.reset();
	while(1){
		usleep(1000);

		core_to_frontend.refresh();
		frontend_to_core.refresh();


		if (ui_timer.getElaspedTimeMS() > UI_REFRESH){
			std::cout << "--AVOE Stonefish--\n";
			printf("SENSOR PRINT\n");
			tardigrade_imu.print();
			tardigrade_pressure.print();
			tardigrade_leak.print();
			printf("MOTOR PRINT");
			thruster_SH.print();
			thruster_PS.print();
			thruster_SS.print();
									

			//vtClear();
			ui_timer.reset();
		}

	}

}


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe_frontend_stonefish <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\ttardigrade\t(tardigrade target)\n"; 


}

int main(int argc, char **argv){


	/* parse arguments */

	if (argc == 1){
		std::cout << "At least one arguments is required. Try ./avoe-frontend-stonefish help\n";
		return 0;

	}

	if (strncmp(argv[1], "tardigrade", 16) == 0){
		tardigrade_simulation();
		return 0;
	
	}

	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	
	}




	return 0;
}
