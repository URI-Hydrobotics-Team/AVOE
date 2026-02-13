/*
	AVOE Reference Controller
*/


// these paths aren;t relative
#include "motor.h"
#include "vehicle.h"
#include "lib.h"


class avoe_reference_controller_t{

	private:
		char name[32]; //name and version string (unimportant)
		vehicle_t *vehcile;
		


	public:

		avoe_reference_controller_t(const char *n, vehicle_t *vehicle_in);
		~avoe_reference_controller_t();
		void send_vector(vector_t thrust_vector, vector_t thrust_point, vector_t pivot_point);


};

