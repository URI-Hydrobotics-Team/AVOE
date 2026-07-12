#include "mc.h"



tardigrade_mc_basic_t::tardigrade_mc_basic_t();
~tardigrade_mc_basic_t::tardigrade_mc_basic_t();


void tardigrade_mc_basic_t::init(tardigrade_controller_t *controller_, tardigrade_mission_basic_t **missions, size_t mission_count){

	controller = controller_;
	misson_ptr = mission;
	mission_size = mission_coint;
	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
	main_timer.reset();
	mission_timer.reset();

}


void tardigrade_mc_basic_t::refresh(){

	if (state == TARDIGRADE_MC_BASIC_STATE_RUNNING){
		
		if (mission_timer.getElaspedTimeMS() != mission_ptr[mission_index].duration){
			//running
		}

	}else if(state == TARDIGRADE_MC_BASIC_STATE_HELD){

		// adjustments adjustments
	}

	//stopped
	


}

void tardigrade_mc_basic_t::start(){
	state = TARDIGRADE_MC_BASIC_STATE_RUNNING;


}

void tardigrade_mc_basic_t::kill(){
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;


}

void tardigrade_mc_basic_t::reset(){

	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}
