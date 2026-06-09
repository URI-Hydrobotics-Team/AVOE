#include "mc_vppn.h"


		
tardigrade_mc_vppn_t::tardigrade_mc_vppn_t();
tardigrade_mc_vppn_t::~tardigrade_mc_vppn_t();


void tardigrade_mc_vppn_t::init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, vector_t *offset_, char *keyword_str_){


	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	vppn_main_object_len = vppn_main_object_len_;
	vppn_dr_object_len = vppn_dr_object_len_;
	keyword_str = keyword_str_;
	offset_vector = offset;

}

tardrigrade_mc_vppn_::reset(){
	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	

	
	
	
	
}

tardigrade_mc_vppn::refresh(){

	/*
		read form socket
		determine if keyword matches
		send commands to comntroller to make adjustments

	*/



	
}
		
		

		


