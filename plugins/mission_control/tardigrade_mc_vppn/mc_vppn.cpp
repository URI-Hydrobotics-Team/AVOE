#include "mc_vppn.h"



tardigrade_mc_vppn_t::tardigrade_mc_vppn_t();
tardigrade_mc_vppn_t::~tardigrade_mc_vppn_t();


void tardigrade_mc_vppn_t::init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, vector_t *offset_, char *keyword_str_, vector_t *output_){


	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	vppn_main_object_len = vppn_main_object_len_;
	vppn_dr_object_len = vppn_dr_object_len_;
	keyword_str = keyword_str_;
	offset_vector = offset_;
	output_vector = output_;
	clock.reset();

}


void tardigrade_mc_vppn::sweep_and_scan(int angle){
	std::cout << "[TARDIGRADE MC VPPN] sweep and scan started for " << angle << " degrees"<< '\n';




}




void tardigrade_mc_vppn::reset(){
	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	global_state = 0;
	paused = false;
}



void tardigrade_mc_vppn::start(){
	global_state = 3; // scan initially

}
void tardigrade_mc_vppn::kill(){
	global_state = -1; //killed
	vector_t zero_vector(0,0,0);
	controller->send_lateral_vector(zero_vector);
	controller->send_translation_vector(zero_vector);
}


void tardigrade_mc_vppn::pause(){
	paused = true;
}
void tardigrade_mc_vppn::resume(){
	paused = false;

}



tardigrade_mc_vppn::refresh(){

	vector_t output_temp(0, 0, 0);

	/*
	   read from keyword
	   determine if keyword matches
	   adjust output vector as necessary

	   handle no match case

	 */

	//offset_vector.x and offset_vector.y define the pixel offsets RXed for CV


	//check timers

	if (adjustment_timer.getElaspedMS() > TARDIGRADE_MC_VPPN_ADJUST_TIME && local_state == 1){
		//done adjusting course, switch back to following course
		local_state = 0;


	}

	// determine if we should dead reckon
	bool dead_reckon = !(strncmp(keyword_str, vppn_main_object_ptr[vppn_main_object_index]->keyword, vppn_main_object_ptr[vppn_main_object_index]->keyword_len) == 0); //false if match, true if no
	dead_reckon = dead_reckon * (main_clock.getElaspedTimeMS > TARDIGRADE_MC_VPPN_DEAD_RECKON_DELAY) * !paused;

	if (!dead_reckon && global_state == 1){
		main_clock.reset(); // update clock everytime we check and get a match



		int cv_x_offset = offset->x;
		int cv_y_offset = offset->y;
		float speed = offset->speed;


		if (cv_x_offset > TARDIGRADE_MC_VPPN_PIXEL_BUFFER && local_state != 1){


			//scale lateral_adjusment vector memebrs
			vector_t adjustment;
			adjustment.x = lateral_adjustment.x * 1;
			adjustment.y = lateral_adjustment.y * 1;
			adjustment.z = lateral_adjustment.z * 1;
			controller->send_lateral_vector(adjustment);
			adjustment_timer.reset();
			local_state = 1;
		}

		if (local_state == 0){
			//following course

			vector_t course;
			//define course here
			controller->send_translation_vector(course);
			
		}

	
	}else if (global_state == 1){

		//dead reckon now
		
		/*
		get vars from dr object and send scan signal
		*/		


	
	}


	//determine if we should bump mission index for main and dr	



}






