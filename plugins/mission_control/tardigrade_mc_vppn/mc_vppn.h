#include "mission_vppn.h"

/*
	URI HYDROBOTICS
	Tardigrade Mission Control Visual Point-To-Point Navigation Controller

*/

#define TARDIGRADE_MC_VPPN_YAW_RATE 0.1
#define TARDIGRADE_MC_VPPN_PIXEL_BUFFER 10
#define TARDIGRADE_MC_VPPN_DEAD_RECKON_DELAY 2000 //ms
#define TARDIGRADE_MC_VPPN_ADJUST_TIME 100 //ms

class tardigrade_mc_vppn_t{



	private:
		vppn_mission_t *vppn_main_object_ptr;
		vppn_mission_t *vppn_dr_object_ptr;
		size_t vppn_main_object_len;
		size_t vppn_dr_object_len;
		vector_t *output_vector;
		size_t vppn_main_object_index;
		size_t vppn_dr_object_index;
		targrade_controller_t *controller;
		char *keyword_str;
		avoe_time_t adjustment_timer, main_clock, scan_timer;
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
		
		tardigrade_mc_vppn_t;
		~tardigrade_mc_vppn_t;
		void init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, char *keyword_str_, vector_t *output_);
		
		void sweep_and_scan(int angle);
		//the signals
		void reset(); // reset to intial state
		void refresh(); //continous update call
		void start(); // start from reset state
		void kill(); //send 0 vector
		void hold(); //stop movement and hold position
		void resume(); //resume from hold or kill
		

		


};
