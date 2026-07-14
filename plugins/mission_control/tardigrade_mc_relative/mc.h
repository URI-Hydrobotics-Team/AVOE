/*
	AVOE
	Tardigrade Mission Control Basic

*/

#ifndef TARDIGRADE_MC_BASIC_H
#define TARDIGRADE_MC_BASIC_H


// global states
#define TARDIGRADE_MC_BASIC_STATE_STOPPED 0
#define TARDIGRADE_MC_BASIC_STATE_RUNNING 1
#define TARDIGRADE_MC_BASIC_STATE_HELD 2

// running modes
#define TARDIGRADE_MC_BASIC_RUN_DRIVING 0
#define TARDIGRADE_MC_BASIC_RUN_ADJUSTING 1

<<<<<<< HEAD

#define TARDIGRADE_MC_BASIC_ADJUSTMENT_NOT_STARTED 0
#define TARDIGRADE_MC_BASIC_ADJUSTMENT_STARTED 1

=======
>>>>>>> d3a58ce958d1221c03142a57a20e37599b5111cd
#include "math.h"
#include <cstdio>
#include <sys/types.h>
#include "mission.h"
#include "../../controllers/tardigrade/controller.h"
#include "../../middleware/general-sensor/imu.h"
#include "../../../core/sensor.h"
#include "../../../lib/clock.h"
#include "../../../lib/lib.h"




class tardigrade_mc_basic_t{

	private:
		size_t mission_index;
		size_t mission_size;
		tardigrade_controller_t *controller;
		tardigrade_mission_basic_t **mission_ptr;
		avoe_clock_t main_timer, mission_timer, thruster_timer, adjustment_timer;
		uint8_t state, run_mode;
		sensor_t *imu;
		vector_t imu_orientation;
		float adjustment_compensation;
		void update_imu();
		int16_t yaw_offset, pitch_offset, roll_offset;
		uint8_t adjustment_flag;
		
	public:

		tardigrade_mc_basic_t();
		~tardigrade_mc_basic_t();
		void init(tardigrade_controller_t *controller, sensor_t *imu_, tardigrade_mission_basic_t **missions, size_t mission_count, float adjustment_compensation_);
		void refresh(); // update
		void start(); //start / resume
		void stop(); // stop
		void hold(); //hold position
		void kill();
		void reset();
};




#endif
