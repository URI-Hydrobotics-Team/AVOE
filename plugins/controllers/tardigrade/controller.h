/*
	Tardigrade Controller
*/

/* define thruster weights */






#ifndef TARDIGRADE_CONTROLLER_H
#define TARDIGRADE_CONTROLLER_H 


// these paths aren't relative
#include "motor.h"
#include "vehicle.h"
#include "lib.h"


class tardigrade_controller_t{

	private:
		char name[32]; //name and version string (unimportant)
		vehicle_t *vehcile;
		


	public:

		tardigrade_controller_t(const char *n, vehicle_t *vehicle_in);
		~tardigrade__controller_t();
		void send_vector(vector_t thrust_vector, vector_t thrust_point, vector_t pivot_point);


};

#endif
