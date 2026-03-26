/*
	Tardigrade Main Controller
*/

#ifndef TARDIGRADE_CONTROLLER_H
#define TARDIGRADE_CONTROLLER_H 



// these paths should be relative
#include "../../../core/motor.h"
#include "../../../core/vehicle.h"
#include "../../../lib/lib.h"

#define NAME_LEN 32


class tardigrade_controller_t{

	private:
		char *name; //name and version string (unimportant)
		vehicle_t *vehicle; //Pull Motors from Vehicle object
		float translation_thrust_table[6][3] = {
			{0.0, 0.0, 1.0},	//SH
			{0.0, 0.0, 0.5},	//BSH
			{0.0, 0.0, 0.5}, 	//BPH
			{0.0, 0.6, 0.0}, 	//Y
			{1, 0.4, 0.0}, //SS
			{1, -0.4, 0.0}	//PS
		};

		float lateral_thrust_table[6][3] = {
		//  roll,pitch,yaw
			{0.0, 1.0, 0},	//SH
			{0.0, 0.5, 0},	//BSH
			{0.0, 0.5, 0}, 	//BPH
			{0.0, 0, 0.6}, 	//Y
			{0, 0, 0.4}, //SS
			{0, 0, -0.4}	//PS
		};
		motor_t** motorTable;


	public:
		tardigrade_controller_t();
		tardigrade_controller_t(const char *n, vehicle_t *vehicle_in);
		~tardigrade_controller_t();
		void init(const char *n, vehicle_t *vehicle_in);
		void send_translation_vector(vector_t thrust_vector);
		void send_lateral_vector(vector_t thrust_vector);
};

#endif
