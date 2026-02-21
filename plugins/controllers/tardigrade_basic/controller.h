/*
	Tardigrade Basic Controller
*/

/* define thruster weights */

#ifndef TARDIGRADE_BASIC_CONTROLLER_H
#define TARDIGRADE_BASIC_CONTROLLER_H 


// these paths should be relative
#include "../../../core/motor.h"
#include "../../../core/vehicle.h"
#include "../../../lib/lib.h"


class tardigrade_basic_controller_t{

	private:
		char *name; //name and version string (unimportant)
		vehicle_t *vehicle; //Pull Motors from Vehicle object
		float thrust_table[6][3] = {
			{0.0, 0.0, 1.0},	//SH
			{0.0, 0.0, 1.0},	//BSH
			{0.0, 0.0, 1.0}, 	//BPH
			{0.0, 1, 0.0}, 	//Y
			{1, -0.5, 0.0}, //SS
			{1, 0.5, 0.0}	//PS
		};
		motor_t** motorTable;
	public:

		tardigrade_basic_controller_t(const char *n, vehicle_t *vehicle_in);
		~tardigrade_basic_controller_t();
		void send_vector(vector_t thrust_vector); //we assume pivot and orgin are about the center of the robot
};

#endif