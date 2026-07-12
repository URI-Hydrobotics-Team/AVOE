/*
	AVOE
	Tardigrade Mission Control Basic

*/

#ifndef TARDIGRADE_MC_BASIC_H
#define TARDIGRADE_MC_BASIC_H


#define TARDIGRADE_MC_BASIC_STATE_STOPPED 0
#define TARDIGRADE_MC_BASIC_STATE_RUNNING 1
#define TARDIGRADE_MC_BASIC_STATE_HELD 2





#include <types.h>
#include "mission.h"
#include "../controllers/tardigrade/controller.h"
#include "../middleware/general-sensor/imu.h"
#include "../../lib/clock.h"


class tardigrade_mc_basic_t{

	private:
		size_t mission_index;
		size_t mission_size;
		tarsigrade_controller_t *controller;
		tardigrade_mission_basic_t **mission_ptr;
		avoe_clock_t main_timer, mission_timer;
		uint8_t state;


	public:

		mission_control_tardigrade_t();
		~mission_control_tardigrade_t();
		void init(tardigrade_controller_t *controller, tardigrade_mission_basic_t **missions, size_t mission_count);
		void refresh(); // update
		void start(); //start / resume
		void stop(); // stop
		void hold(); //hold position
		void reset();
};




#endif
