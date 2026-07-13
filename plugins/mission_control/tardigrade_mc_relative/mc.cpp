#include "mc.h"



void update_imu(){
	vector_t imu_read = sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(imu);
	imu_orientation.x = imu_read.x;
	imu_orientation.y = imu_read.y;
	imu_orientation.z = imu_read.z;

	printf("[MC REN] IMU refreshed: %.2f, %.2f, %.2f\n", imu_orientation.x, imu_orientation.y, imu_orientation.z);
}


tardigrade_mc_basic_t::tardigrade_mc_basic_t();
~tardigrade_mc_basic_t::tardigrade_mc_basic_t();


void tardigrade_mc_basic_t::init(tardigrade_controller_t *controller_, sensor_t *imu_, tardigrade_mission_basic_t **missions, size_t mission_count, float adjustment_compensation_){

	controller = controller_;
	imu = imu_;
	misson_ptr = mission;
	mission_size = mission_count;
	adjustment_compensation = adjustment_compensation_;
	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
	main_timer.reset();
	mission_timer.reset();
	
}


void tardigrade_mc_basic_t::refresh(){
	update_imu();

	if (state == TARDIGRADE_MC_BASIC_STATE_RUNNING){
		
		if (mission_timer.getElaspedTimeMS() , mission_ptr[mission_index].duration){

		// send base vectors
		controller->send_lateral_vector();
		controller->send_translational_vector();
		
		// maintain pose

		if (mission_ptr[mission_index].maintain_pose){
			uint16_t yaw_offset, pitch_offset, roll_offset;
			yaw_offset = desired_yaw - imu_orientation.x;
			pitch_offset = desired_yaw - imu_orientation.y;
			roll_offset = desired_roll - imu_orientation.z;
						
			//compensate if needed

			if (abs(yaw_offset) > adjustment_compensation){
				printf("[MC REN] yaw compensation required\n");
			}

			if (abs(pitch_offset) > adjustment_compensation){
				printf("[MC REN] pitch compensation required\n");
			}
			if (abs(roll_offset) > adjustment_compensation){
				printf("[MC REN] roll compensation required\n");
			}
 	
			
		}

			//running
		}else{
			mission_index++;
			if (mission_index != mission_size){
				// next mission
				update_imu();

				//initial stuff probably not needed
				mission_ptr[mission_index].initial_yaw = imu_orientation.x;
				mission_ptr[mission_index].initial_pitch = imu_orientation.y;
				mission_ptr[mission_index].initial_roll = imu_orientation.z;



			}else{
				//end of missions
				state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
			}	
		


	

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
