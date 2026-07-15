/*

	AVOE autonmous tasks
	URI Hydrbotics
	This file includes all hardcoded autonomous logic for your usecase

*/

#ifndef TASKS_H
#define TASKS_H

#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"


tardigrade_mission_basic_t qual_descend, qual_forward, qual_ascend, qual_style;
tardigrade_mission_basic_t* qualification_robosub_2026[4];
//qual_descend

void write_tasks_qualification(){

	//qual_descend
	qual_descend.duration = 1000 * 5;
	qual_descend.speed = 1.0;
	
	qual_descend.translational_movement.x = 0.0;
	qual_descend.translational_movement.y = 0.0;
	qual_descend.translational_movement.z = 1.0; //going down ...

	qual_descend.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_descend.maintain_pose = false;
	
	qual_descend.desired_yaw_offset = 0;
	qual_descend.desired_pitch_offset = 0;
	qual_descend.desired_roll_offset = 0;
	
	qual_descend.adjustment_threshold = 10;

	qual_descend.thruster_time_run = 100;
	qual_descend.thruster_time_adjust = 100;
	//qual_descend
	qual_forward.duration = 1000 * 20;
	qual_forward.speed = 0.5;
	
	qual_forward.translational_movement.x = 1.0; //going forward
	qual_forward.translational_movement.y = 0.0;
	qual_forward.translational_movement.z = 0.0; //going down ...

	qual_forward.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_forward.maintain_pose = false;
	
	qual_forward.desired_yaw_offset = 0;
	qual_forward.desired_pitch_offset = 0;
	qual_forward.desired_roll_offset = 0;
	
	qual_forward.adjustment_threshold = 10;

	qual_forward.thruster_time_run = 100;
	qual_forward.thruster_time_adjust = 100;

	//qual_ascend
	qual_ascend.duration = 1000 * 5;
	qual_ascend.speed = 0.3;
	
	qual_ascend.translational_movement.x = 0.0;
	qual_ascend.translational_movement.y = 0.0;
	qual_ascend.translational_movement.z = -1.0; //going up

	qual_ascend.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_ascend.maintain_pose = false;
	
	qual_ascend.desired_yaw_offset = 0;
	qual_ascend.desired_pitch_offset = 0;
	qual_ascend.desired_roll_offset = 0;
	
	qual_ascend.adjustment_threshold = 10;

	qual_ascend.thruster_time_run = 100;
	qual_ascend.thruster_time_adjust = 100;

	qualification_robosub_2026[0] = &qual_descend;
	qualification_robosub_2026[1] = &qual_forward;
	qualification_robosub_2026[2] = &qual_ascend;

	
}



tardigrade_mission_basic_t imu_test;
tardigrade_mission_basic_t *imu_test_task[1];

void write_tasks_imu_test(){

	imu_test.duration = 1000 * 10;
	imu_test.speed = 0.5;
	
	imu_test.translational_movement.x = 1.0;
	imu_test.translational_movement.y = 0.0;
	imu_test.translational_movement.z = 0.0; //going up

	imu_test.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	imu_test.maintain_pose = true;
	
	imu_test.desired_yaw_offset = 0;
	imu_test.desired_pitch_offset = 0;
	imu_test.desired_roll_offset = 0;
	
	imu_test.adjustment_threshold = 10;

	imu_test.thruster_time_run = 100;
	imu_test.thruster_time_adjust = 100;
	imu_test_task[0] = &imu_test;

}


tardigrade_mission_basic_t side_1, corner_1, side_2, corner_2, side_3, corner_3, side_4;
tardigrade_mission_basic_t* box_task[7];
//qual_descend


void write_tasks_box(){

	//side 1
	side_1.duration = 1000 * 5;
	side_1.speed = 0.5;
	
	side_1.translational_movement.x = 1.0;
	side_1.translational_movement.y = 0.0;
	side_1.translational_movement.z = 0.0; //going up

	side_1.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	side_1.maintain_pose = true;
	
	side_1.desired_yaw_offset = 0;
	side_1.desired_pitch_offset = 0;
	side_1.desired_roll_offset = 0;
	
	side_1.adjustment_threshold = 10;

	side_1.thruster_time_run = 100;
	side_1.thruster_time_adjust = 100;

//corner 1
	corner_1.duration = 1000 * 10;
	corner_1.speed = 0.5;
	
	corner_1.translational_movement.x = 0.0;
	corner_1.translational_movement.y = 0.0;
	corner_1.translational_movement.z = 0.0; //going up

	corner_1.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	corner_1.maintain_pose = true;
	
	corner_1.desired_yaw_offset = 90;
	corner_1.desired_pitch_offset = 0;
	corner_1.desired_roll_offset = 0;
	
	corner_1.adjustment_threshold = 10;

	corner_1.thruster_time_run = 100;
	corner_1.thruster_time_adjust = 100;






//side 2
	side_2.duration = 1000 * 5;
	side_2.speed = 0.5;
	
	side_2.translational_movement.x = 1.0;
	side_2.translational_movement.y = 0.0;
	side_2.translational_movement.z = 0.0; //going up

	side_2.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	side_2.maintain_pose = true;
	
	side_2.desired_yaw_offset = 0;
	side_2.desired_pitch_offset = 0;
	side_2.desired_roll_offset = 0;
	
	side_2.adjustment_threshold = 10;

	side_2.thruster_time_run = 100;
	side_2.thruster_time_adjust = 100;

//corner 2
	corner_2.duration = 1000 * 10;
	corner_2.speed = 0.5;
	
	corner_2.translational_movement.x = 0.0;
	corner_2.translational_movement.y = 0.0;
	corner_2.translational_movement.z = 0.0; //going up

	corner_2.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	corner_2.maintain_pose = true;
	
	corner_2.desired_yaw_offset = 90;
	corner_2.desired_pitch_offset = 0;
	corner_2.desired_roll_offset = 0;
	
	corner_2.adjustment_threshold = 10;

	corner_2.thruster_time_run = 100;
	corner_2.thruster_time_adjust = 100;



//side 3
	side_3.duration = 1000 * 5;
	side_3.speed = 0.5;
	
	side_3.translational_movement.x = 1.0;
	side_3.translational_movement.y = 0.0;
	side_3.translational_movement.z = 0.0; //going up

	side_3.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	side_3.maintain_pose = true;
	
	side_3.desired_yaw_offset = 0;
	side_3.desired_pitch_offset = 0;
	side_3.desired_roll_offset = 0;
	
	side_3.adjustment_threshold = 10;

	side_3.thruster_time_run = 100;
	side_3.thruster_time_adjust = 100;

//corner 3
	corner_3.duration = 1000 * 10;
	corner_3.speed = 0.5;
	
	corner_3.translational_movement.x = 0.0;
	corner_3.translational_movement.y = 0.0;
	corner_3.translational_movement.z = 0.0; //going up

	corner_3.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	corner_3.maintain_pose = true;
	
	corner_3.desired_yaw_offset = 90;
	corner_3.desired_pitch_offset = 0;
	corner_3.desired_roll_offset = 0;
	
	corner_3.adjustment_threshold = 10;

	corner_3.thruster_time_run = 100;
	corner_3.thruster_time_adjust = 100;




//side 4
	side_4.duration = 1000 * 5;
	side_4.speed = 0.5;
	
	side_4.translational_movement.x = 1.0;
	side_4.translational_movement.y = 0.0;
	side_4.translational_movement.z = 0.0; //going up

	side_4.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	side_4.maintain_pose = true;
	
	side_4.desired_yaw_offset = 0;
	side_4.desired_pitch_offset = 0;
	side_4.desired_roll_offset = 0;
	
	side_4.adjustment_threshold = 10;

	side_4.thruster_time_run = 100;
	side_4.thruster_time_adjust = 100;



	box_task[0] = &side_1;
	box_task[1] = &corner_1;
	box_task[2] = &side_2;
	box_task[3] = &corner_2;
	box_task[4] = &side_3;
	box_task[5] = &corner_3;
	box_task[6] = &side_4;
}


#endif
