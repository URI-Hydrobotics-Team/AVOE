#include <iostream>
#include "mission_vppn.h"
#include "../../../lib/lib.h"
#include "../../../lib/clock.h"
#include "../../controllers/tardigrade/controller.h"


#ifndef TARDIGRADE_MC_VPPN
#define TARDIGRADE_MC_VPPN

/*
	URI HYDROBOTICS
	Tardigrade Mission Control Visual Point-To-Point Navigation Controller

*/

#define TARDIGRADE_MC_VPPN_YAW_RATE 0.1
#define TARDIGRADE_MC_VPPN_PIXEL_BUFFER 10
#define TARDIGRADE_MC_VPPN_DEAD_RECKON_DELAY 2000 //ms
#define TARDIGRADE_MC_VPPN_ADJUST_TIME 100 //ms

#define TARDIGRADE_MC_VPPN_GLOBAL_STATE_STOP -1
#define TARDIGRADE_MC_VPPN_GLOBAL_STATE_RESET 0
#define TARDIGRADE_MC_VPPN_GLOBAL_STATE_RUNNING 1
#define TARDIGRAEE_MC_VPPN_GLOBAL_STATE_HOLD 2
#define TARDIGRADE_MC_VPPN_GLOBAL_STATE_SCAN 3

#define TARDIGRADE_MC_VPPN_LOCAL_STATE_FOLLOWING 0
#define TARDIGRADE_MC_VPPN_LOCAL_STATE_ADJUSTING 1
#define TARDIGRADE_MC_VPPN_CV_RESOLUTION_X 1280



class tardigrade_mc_vppn_t{



	private:
		vppn_mission_t *vppn_main_object_ptr;
		vppn_mission_t *vppn_dr_object_ptr;
		size_t vppn_main_object_len;
		size_t vppn_dr_object_len;
		size_t vppn_main_object_index;
		size_t vppn_dr_object_index;
		tardigrade_controller_t *controller;
		
		//from CV (input)
		char *keyword_str_raw;
		size_t keyword_str_raw_len;

		//to controller (output)
		vector_t *output_translational_vector, *output_lateral_vector;

		avoe_clock_t adjustment_timer, main_clock, scan_timer;
		short global_state, local_state;
		bool paused;
		/*
		global_state
			-1 	stop
			0	reset
			1	running	
			2	hold
			3	scan

		local_state
			0	following
			1	adjusting course
		*/

	public:
		
		tardigrade_mc_vppn_t();
		~tardigrade_mc_vppn_t();
		void init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, char *keyword_str_raw_, size_t keyword_str_raw_len_, vector_t *output_translational_vector_, vector_t *output_lateral_vector_);
		
		void sweep_and_scan(int angle);
		//the signals
		void reset(); // reset to intial state
		void refresh(); //continous update call
		void start(); // start from reset state
		void kill(); //send 0 vector
		void hold(); //stop movement and hold position
		void resume(); //resume from hold or kill
		//void CVTranslation(const char* CVData, size_t mode);

		


};

#endif
