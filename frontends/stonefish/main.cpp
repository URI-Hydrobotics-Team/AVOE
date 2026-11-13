/*
	stonefish frontend for AVOE
	URI Hydrobotics
	
*/
#include <cstring>
#include <iostream>

//stonefish includes
#include "simulation_manager.h"
#include <Stonefish/core/GraphicalSimulationApp.h>


/* AVOE specific includes */
#include "config.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../core/io.h"
#include "../../lib/vt100.h"
#include "../../lib/clock.h"

#include "vehicle_setup.h"
#include "vehicle_refresh.h"
/*

	How it works
	stonefish provides a callback in the form of a method apart sf::SimulationManager: SimulationStepCompleted(Scalar timeStep), this method can be overrided. 

	All setup will be done in main.
	The SimulationStepCompleted override will point to the main avoe-frontend loop.
	the avoe-frontend loop will contain the usual AVOE stuff along with any middleware calls	



*/




void tardigrade_simulations(const char *scenario_filename){

	/* simulation setup */

	printf("[AVOE] Tardigrade Stonefish Starting\n");

	//setup tardigrade AVOE side
	tardigrade_setup_avoe();
	tardigrade_setup_avoe_objects();

	//setup stonefish simulation manager

	avoe_sf_simulation_manager manager(100.0);
	strncpy(manager.scenario_filename, scenario_filename, 64);

	sf::RenderSettings s;
    	sf::HelperSettings h;
    	sf::GraphicalSimulationApp app("AVOE with Stonefish", "", s, h, &manager);


    	app.Run();
	


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

		if (argv[2] == NULL){
			std::cout << "must specify scenario file\n";
		}

		tardigrade_simulation(argv[2]);
		return 0;
	
	}

	if (strncmp(argv[1], "help", 16) == 0){
		printHelp();
		return 0;
	
	}




	return 0;
}
