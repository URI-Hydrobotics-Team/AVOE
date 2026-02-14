/*
	Tardigrade Basic Controller
*/

/* define thruster weights */






#ifndef TARDIGRADE_BASIC_CONTROLLER_H
#define TARDIGRADE_BASIC_CONTROLLER_H 


// these paths aren't relative
#include "motor.h"
#include "vehicle.h"
#include "lib.h"


class tardigrade_basic_controller_t{

	private:
		char name[32]; //name and version string (unimportant)
		vehicle_t *vehcile;
		float thrust_table[3][6] = {
		0.0, 0.0, 1.0, 	//SH
		0.0, 0.0, 1.0, 	//BSH
		0.0, 0.0, 1.0, 	//BPH
		1.0, 0.0, 0.0, 	//Y
		-0.5, 0.0, 0.0, //SS
		0.5, 0.0, 0.0	//PS
		};
		


	public:

		tardigrade_basic_controller_t(const char *n, vehicle_t *vehicle_in);
		~tardigrade_basic_controller_t();
		void send_vector(vector_t thrust_vector); //we assume pivot and orgin are about the center of the robot


};

#endif
