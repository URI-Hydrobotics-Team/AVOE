#include <cstdio>
#include <cstring>
#include <iostream>

#include "mc.h"
#include "mission.h"
#include "../../../core/io.h"

/*
	* Point of this test file is to allow for a full test run of MC. It should printout (in readible format) 
	* each object that is sent through the MC obj array. 
	*
	* Structure:
	* Define and all MC objects in a seperate method from main, maybe define a list of names or in general a rand function
	* for all Mission objects fields (Name, Duration, Speed, translational movement, lateral movement (Vector_ts), 
	* maintain pose, designed pose, desired pitch, desired roll )

	* Have the main method send in the array passed back into MC. Also try and have all MC actions be printed out if possible.
*/



int main(int argc, char **argv){

	// create objects
	tardigrade_controller_t controller;
	sensor_t imu;
	tardigrade_mc_basic_t mc;	
	tardigrade_mission_basic_t mission_1, mission_2, mission_3, mission_4;	
	tardigrade_mission_basic_t* missions[4] = {&mission_1, &mission_2, &mission_3, &mission_4};
	
	mc.init(&controller, &imu, missions, 4, 0.05);



	return 0;
}
