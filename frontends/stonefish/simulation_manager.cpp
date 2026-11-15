#include "simulation_manager.h"

#include <Stonefish/core/ScenarioParser.h>
#include <iostream>

/*
// stonefish simulation objects
#include <Stonefish/entities/statics/Plane.h>
#include <Stonefish/entities/solids/Sphere.h>
#include <Stonefish/entities/forcefields/Ocean.h>
#include <Stonefish/entities/solids/Box.h>
#include <Stonefish/actuators/Propeller.h>
#include <Stonefish/actuators/Thruster.h>
#include <Stonefish/sensors/vision/Camera.h>
#include <Stonefish/sensors/scalar/Odometry.h>
#include <Stonefish/joints/Joint.h>
*/

//avoe
#include "vehicle_setup.h"
#include "vehicle_refresh.h"

#include "../../lib/globals.h"
avoe_sf_simulation_manager::avoe_sf_simulation_manager(sf::Scalar stepsPerSecond) : SimulationManager(stepsPerSecond){

}

void avoe_sf_simulation_manager::SimulationStepCompleted(sf::Scalar timeStep){
	//std::cout << "simulation step completed\n";

	//we will set get our stonefish objects defined in xml here

	//std::string name = test->getName(); 
	sf::Actuator* thruster;
	sf::Sensor* imu;


	thruster = getActuator("SimpleVehicle/BowPortHeave"); 
	avoe_shared_objects.motor_bph = static_cast<sf::Thruster*>(thruster);

	thruster = getActuator("SimpleVehicle/BowStarboardHeave"); 
	avoe_shared_objects.motor_bsh = static_cast<sf::Thruster*>(thruster);

	thruster = getActuator("SimpleVehicle/SternHeave"); 
	avoe_shared_objects.motor_sh = static_cast<sf::Thruster*>(thruster);

	thruster = getActuator("SimpleVehicle/Yaw"); 
	avoe_shared_objects.motor_y = static_cast<sf::Thruster*>(thruster);

	thruster = getActuator("SimpleVehicle/PortSurge"); 
	avoe_shared_objects.motor_ps = static_cast<sf::Thruster*>(thruster);

	thruster = getActuator("SimpleVehicle/StarboardSurge"); 
	avoe_shared_objects.motor_ss = static_cast<sf::Thruster*>(thruster);

	
	imu = getSensor("SimpleVehicle/IMU");
	avoe_shared_objects.sensor_imu = static_cast<sf::IMU*>(imu);




	//std::cout << "loop back test: " << name << "" << '\n';
	tardigrade_refresh_avoe(&avoe_shared_objects);

}



void avoe_sf_simulation_manager::BuildScenario(){


	sf::ScenarioParser parser(this);

     	bool parse_success = parser.Parse(scenario_filename);
 
        if(!parse_success){
       	        std::cout << "failed to parse\n";
        }

}
