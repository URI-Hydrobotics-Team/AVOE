#include <cstdio>
#include <cstring>
#include <iostream>

#include "mc_vppn.h"
#include "mission_vppn.h"
#include "../../drivers/other/dummy_mission_vppn/driver.h"
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

	return 0;
}


