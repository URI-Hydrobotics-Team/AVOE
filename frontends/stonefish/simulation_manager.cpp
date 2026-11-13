#include "simulation_manager.h"

#include <Stonefish/core/ScenarioParser.h>
#include <iostream>

// stonefish simulation objects
#include <Stonefish/entities/statics/Plane.h>
#include <Stonefish/entities/solids/Sphere.h>
#include <Stonefish/entities/forcefields/Ocean.h>
#include <Stonefish/entities/solids/Box.h>
#include <Stonefish/actuators/Propeller.h>
#include <Stonefish/actuators/Thruster.h>
#include <Stonefish/sensors/vision/Camera.h>
#include <Stonefish/sensors/scalar/Odometry.h>

//avoe
#include "vehicle_setup.h"
#include "vehicle_refresh.h""


avoe_sf_simulation_manager::avoe_sf_simulation_manager(sf::Scalar stepsPerSecond) : SimulationManager(stepsPerSecond){

}

void avoe_sf_simulation_manager::SimulationStepCompleted(sf::Scalar timeStep){
	//std::cout << "simulation step completed\n";

	//we will set get our stonefish objects defined in xml here


	sf::Actuator* test = getActuator(0); 
	std::string name = test->getName(); 

	avoe_shared_objects.motor_sh = static_cast<sf::Thruster*>(test);	

	std::cout << "loop back test: " << name << "" << '\n';


}



void avoe_sf_simulation_manager::BuildScenario(){


	sf::ScenarioParser parser(this);

     	bool parse_success = parser.Parse(scenario_filename);
 
        if(!parse_success){
       	        std::cout << "failed to parse\n";
        }

}
