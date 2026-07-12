#include "mc.h"



void update_imu(){
	vector_t imu_read = sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(imu);
	imu_orientation.x = imu_read.x;
	imu_orientation.y = imu_read.y;
	imu_orientation.z = imu_read.z;

}


tardigrade_mc_basic_t::tardigrade_mc_basic_t();
~tardigrade_mc_basic_t::tardigrade_mc_basic_t();


void tardigrade_mc_basic_t::init(tardigrade_controller_t *controller_, sensor_t *imu_, tardigrade_mission_basic_t **missions, size_t mission_count){

	controller = controller_;
	imu = imu_;
	misson_ptr = mission;
	mission_size = mission_coint;
	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
	main_timer.reset();
	mission_timer.reset();
	
}


void tardigrade_mc_basic_t::refresh(){
	update_imu();

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
	if (state == TARDIGRADE_MC_BASIC_STOPPED){
		state = TARDIGRADE_MC_BASIC_STATE_RUNNING;
		update_imu();
		mission_ptr[mission_index].initial_yaw = imu_orientation.x;
		mission_ptr[mission_index].initial_pitch = imu_orientation.y;
		mission_ptr[mission_index].initial_roll = imu_orientation.z;

	}

}

void tardigrade_mc_basic_t::kill(){
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;


}

void tardigrade_mc_basic_t::reset(){

	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}
