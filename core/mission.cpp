#include "mission.h"

void auv_mission_t::init(vector_t cposi, vector_t tposi, vector_t cpose, vector_t tpose){

	/*	
	current_posi = cposi;
	current_pose = cpose;
	target_posi = tposi;
	target_pose = tpose;
	*/
}




void auv_mission_t::update(vector_t cposi, vector_t cpose){
	if (is_active){
		/*
		current_posi = cposi;
		current_pose = cpose;
		*/
	}

}

void auv_mission_t::abort(){
	is_active = false;
}

