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

tardigrade_mc_vppn_::reset(){
	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	

	
	
	
	
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

	// get our stuff

	
	bool dead_reckon = !(strncmp(keyword_str, mission->keyword, mission->keyword_len) == 0); //false if match, true if no
	if (!dead_reckon){
		clock.reset(); // update clock everytime we check and get a match
	}	


	int cv_x_offset = offset->x;
	int cv_y_offset = offset->y;
	float speed = offset->speed;


	if (cv_x_offset > TARDIGRADE_MC_VPPN_PIXEL_BUFFER && !dead_reckon){

		//make adjust

	}


	if (dead_reckon && clock.getElaspedTimeMS() > TARDIGRADE_MC_VPPN_DEAD_RECKON_DELAY){

		//dead reckon now

	}
	
	
	


	
}
		
		

		


