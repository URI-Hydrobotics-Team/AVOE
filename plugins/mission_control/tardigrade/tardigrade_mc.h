/*
	AVOE
	Tardigrade Mission Control

*/

#ifndef TARDIGRADE_MC
#define TARDIGRADE_MC

#include "../../core/mission.h"
#include "../../core/sensor.h"
#include "../../core/vehicle.h"
#include "../../core/motor.h"
#include "../controlers/tardigrade/controller.h"
#include "../math/avoe_pid_controller/pid.h"
#include "../middleware/general-sensor/imu.h"



class mission_control_tardigrade_t{

	private:
		size_t mission_index;
		size_t mission_size;
		tarsigrade_controller_t *controller;
		auv_mission_t **mission;


	public:

		mission_control_tardigrade_t();
		~mission_control_tardigrade_t();
		init(tardigrade_controller_t *controller, auv_mission_t **missions, size_t mission_count);
		refresh(); // update
		stop();
		resume();
		select(size_t mission_index); // set mission index and stop
		reset();

};




#endif
