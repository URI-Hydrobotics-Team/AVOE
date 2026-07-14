#include "mc.h"



void tardigrade_mc_basic_t::update_imu(){
	vector_t imu_read = sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(imu);
	imu_orientation.x = imu_read.x;
	imu_orientation.y = imu_read.y;
	imu_orientation.z = imu_read.z;

	printf("[MC REN] IMU refreshed: %f, %f, %f\n", imu_orientation.x, imu_orientation.y, imu_orientation.z);
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

	uint16_t adjustment_threshold = mission_ptr[mission_index]->adjustment_threshold; 
	if (state == TARDIGRADE_MC_BASIC_STATE_RUNNING){

		if (mission_timer.getElaspedTimeMS() < mission_ptr[mission_index]->duration){
			printf("[MC REN] running mission %d\n", mission_index);
			//we are in a mission
			vector_t translational, lateral;

			translational.x = mission_ptr[mission_index]->translational_movement.x * mission_ptr[mission_index]->speed;
			translational.y = mission_ptr[mission_index]->translational_movement.y *  mission_ptr[mission_index]->speed;
			translational.z = mission_ptr[mission_index]->translational_movement.z *  mission_ptr[mission_index]->speed;

			lateral.x = mission_ptr[mission_index]->lateral_movement.x *  mission_ptr[mission_index]->speed;
			lateral.y = mission_ptr[mission_index]->lateral_movement.y *  mission_ptr[mission_index]->speed;
			lateral.z = mission_ptr[mission_index]->lateral_movement.z * mission_ptr[mission_index]->speed;


			// maintain pose, which is a lateral only type of movement
			run_mode = TARDIGRADE_MC_BASIC_RUN_DRIVING;
			if (mission_ptr[mission_index]->maintain_pose){
				//detect if we need to compensate for roll, pitch, yaw
				yaw_offset = mission_ptr[mission_index]->initial_yaw - floor(imu_orientation.x);
				pitch_offset = mission_ptr[mission_index]->initial_pitch - floor(imu_orientation.z);
				roll_offset = mission_ptr[mission_index]->initial_roll - floor(imu_orientation.y);

				printf("initial %d, %d, %d\n", mission_ptr[mission_index]->initial_yaw, mission_ptr[mission_index]->initial_roll, mission_ptr[mission_index]->initial_pitch);
				//compensate if needed

				if (abs(yaw_offset) > adjustment_threshold){
					printf("[MC REN] yaw compensation required %d\n", yaw_offset);
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}

				if (abs(pitch_offset) > adjustment_threshold){
					printf("[MC REN] pitch compensation required %d\n", pitch_offset);
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}
				if (abs(roll_offset) > adjustment_threshold){
					printf("[MC REN] roll compensation required %d\n",roll_offset );
					run_mode = TARDIGRADE_MC_BASIC_RUN_ADJUSTING;
				}


			}

			if (run_mode == TARDIGRADE_MC_BASIC_RUN_DRIVING){
				printf("[MC REN] driving\n");


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

				printf("[MC REN] adjusting\n");

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
			printf("[MC REN] next mission\n");
			mission_timer.reset();
			if (mission_index < mission_size - 1){
				// next mission
				update_imu();

				mission_index++;
				//initial stuff probably not needed
				mission_ptr[mission_index]->initial_yaw = (int)imu_orientation.x;
				mission_ptr[mission_index]->initial_pitch = (int)imu_orientation.z;
				mission_ptr[mission_index]->initial_roll = (int)imu_orientation.y;



			}else{
				printf("[MC REN] MISSION COMPLETE");
				//end of missions
				state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
					
				vector_t zero_vector(0,0,0);
				controller->send_translation_vector(zero_vector);	
				controller->send_lateral_vector(zero_vector);	
			}	





		}

	}
	if(state == TARDIGRADE_MC_BASIC_STATE_HELD){

		// adjustments
	}
	if(state == TARDIGRADE_MC_BASIC_STATE_STOPPED){
		printf("[MC REN] MISSION STOPPED\n");
		// adjustments
	}
	//stopped



}

void tardigrade_mc_basic_t::start(){

	printf("[MC REN] Start Called\n");
	if (state == TARDIGRADE_MC_BASIC_STATE_STOPPED){
		printf("[MC REN] MISSION STARTED\n");
		state = TARDIGRADE_MC_BASIC_STATE_RUNNING;
		update_imu();
	
		printf("%f, %f, %f\n", imu_orientation.x,imu_orientation.y,imu_orientation.z);	
		mission_ptr[mission_index]->initial_yaw = (int)floor(imu_orientation.x);
		mission_ptr[mission_index]->initial_pitch = (int)(imu_orientation.z);
		mission_ptr[mission_index]->initial_roll = (int)(imu_orientation.y);

	}

}

void tardigrade_mc_basic_t::kill(){
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}

void tardigrade_mc_basic_t::reset(){

	mission_index = 0;
	state = TARDIGRADE_MC_BASIC_STATE_STOPPED;
}
