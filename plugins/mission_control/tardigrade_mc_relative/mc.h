/*
	AVOE
	Tardigrade Mission Control Basic

*/

#ifndef TARDIGRADE_MC_BASIC_H
#define TARDIGRADE_MC_BASIC_H

#include "mission.h"
#include "../controllers/tardigrade/controller.h"
#include "../middleware/general-sensor/imu.h"



class tardigrade_mc_basic_t{

	private:
		size_t mission_index;
		size_t mission_size;
		tardigrade_controller_t *controller;
		tardigrade_mission_basic_t **mission_ptr;


	public:

		tardigrade_mc_basic_t();
		~tardigrade_mc_basic_t();
		void init(tardigrade_controller_t *controller, tardigrade_mission_basic_t **missions, size_t mission_count);
		void refresh(); // update
		void start();
		void kill();
		void reset();

};




#endif
