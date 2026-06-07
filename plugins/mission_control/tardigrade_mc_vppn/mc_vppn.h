#include "mission_vppn.h"

/*
	URI HYDROBOTICS
	Tardigrade Mission Control Visual Point-To-Point Navigation Controller

*/

class tardigrade_mc_vppn_t{



	private:
		vppn_mission_t *vppn_main_object_ptr;
		vppn_mission_t *vppn_dr_object_ptr;
		size_t vppn_main_object_len;
		size_t vppn_dr_object_len;

		size_t vppn_main_object_index;
		size_t vppn_dr_object_index;
		targrade_controller_t *controller;
		char *keyword_str;
		size_t keyword_len

	public:
		
		tardigrade_mc_vppn_t;
		~tardigrade_mc_vppn_t;
		void init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, targrade_controller_t *controller_, char *keyword_str_, size_t keyword_len_);
		void reset();
		void refresh();
		
		

		


};
