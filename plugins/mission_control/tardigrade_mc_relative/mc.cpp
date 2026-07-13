#include "mc.h"



void tardigrade_mc_basic_t::update_imu(){
	vector_t imu_read = sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(imu);
	imu_orientation.x = imu_read.x;
	imu_orientation.y = imu_read.y;
	imu_orientation.z = imu_read.z;

	printf("[MC REN] IMU refreshed: %.2f, %.2f, %.2f\n", imu_orientation.x, imu_orientation.y, imu_orientation.z);
}


tardigrade_mc_basic_t::tardigrade_mc_basic_t(){

}
tardigrade_mc_basic_t::~tardigrade_mc_basic_t(){

}


void tardigrade_mc_basic_t::init(tardigrade_controller_t *controller_, sensor_t *imu_, tardigrade_mission_basic_t **missions, size_t mission_count, float adjustment_compensation_){

	controller = controller_;
	imu = imu_;
	mission_ptr = missions;
	mission_size = mission_count;
	adjustment_compensation = adjustment_compensation_;
	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
	run_mode = TARDIGRADE_MC_BASIC_RUN_DRIVING;
	main_timer.reset();
	mission_timer.reset();
	thruster_timer.reset();

}


void tardigrade_mc_basic_t::refresh(){
	update_imu();

	if (state == TARDIGRADE_MC_BASIC_STATE_RUNNING){

		if (mission_timer.getElaspedTimeMS() < mission_ptr[mission_index]->duration){

			//we are in a mission
			vector_t translational, lateral;

			translational.x = mission_ptr[mission_index]->translational_movement.x;
			translational.y = mission_ptr[mission_index]->translational_movement.y;
			translational.z = mission_ptr[mission_index]->translational_movement.z;

			lateral.x = mission_ptr[mission_index]->lateral_movement.x;
			lateral.y = mission_ptr[mission_index]->lateral_movement.y;
			lateral.z = mission_ptr[mission_index]->lateral_movement.z;


			// maintain pose, which is a lateral only type of movement
			run_mode = TARDIGRADE_MC_BASIC_RUN_DRIVING;
			if (mission_ptr[mission_index]->maintain_pose){
				//detect if we need to compensate for roll, pitch, yaw
				yaw_offset = mission_ptr[mission_index]->initial_yaw - imu_orientation.x;
				pitch_offset = mission_ptr[mission_index]->initial_pitch - imu_orientation.z;
				roll_offset = mission_ptr[mission_index]->initial_roll - imu_orientation.y;

				//compensate if needed

				if (abs(yaw_offset) > adjustment_compensation){
					printf("[MC REN] yaw compensation required\n");
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}

				if (abs(pitch_offset) > adjustment_compensation){
					printf("[MC REN] pitch compensation required\n");
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}
				if (abs(roll_offset) > adjustment_compensation){
					printf("[MC REN] roll compensation required\n");
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}


			}

			if (run_mode == TARDIGRADE_MC_BASIC_RUN_DRIVING){
				printf("[MC REN] run_mode = driving");


				if (thruster_timer.getElaspedTimeMS() > mission_ptr[mission_index]->thruster_time_run){	

					switch (mission_ptr[mission_index]->movement_type){

						case MISSION_BASIC_LATERAL_ONLY:
							controller->send_lateral_vector(lateral);
							break;
						case MISSION_BASIC_TRANSLATIONAL_ONLY:
							controller->send_translation_vector(translational);	
							break;
					}

					thruster_timer.reset();
				}
			}


			if (run_mode == TARDIGRADE_MC_BASIC_RUN_ADJUSTING){
				//adjust in order of which offset is greatest

				//throw all offsets into an array, sort it, and operate sequentially


				//just yaw for now
				lateral.zero();
				lateral.z = yaw_offset * adjustment_compensation * -1;
				if (thruster_timer.getElaspedTimeMS() > mission_ptr[mission_index]->thruster_time_adjust){	
					controller->send_lateral_vector(lateral);
				}


				thruster_timer.reset();

			}
			//running
		}else{
			mission_index++;
			if (mission_index < mission_size){
				// next mission
				update_imu();

				//initial stuff probably not needed
				mission_ptr[mission_index]->initial_yaw = imu_orientation.x;
				mission_ptr[mission_index]->initial_pitch = imu_orientation.y;
				mission_ptr[mission_index]->initial_roll = imu_orientation.z;



			}else{
				//end of missions
				state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
			}	





		}

	}else if(state == TARDIGRADE_MC_BASIC_STATE_HELD){

		// adjustments
	}

	//stopped



}

void tardigrade_mc_basic_t::start(){
	if (state == TARDIGRADE_MC_BASIC_STATE_STOPPED){
		state = TARDIGRADE_MC_BASIC_STATE_RUNNING;
		update_imu();
		mission_ptr[mission_index]->initial_yaw = imu_orientation.x;
		mission_ptr[mission_index]->initial_pitch = imu_orientation.y;
		mission_ptr[mission_index]->initial_roll = imu_orientation.z;

	}

}

void tardigrade_mc_basic_t::kill(){
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}

void tardigrade_mc_basic_t::reset(){

	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}
