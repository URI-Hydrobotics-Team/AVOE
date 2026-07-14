/*

	AVOE autonmous tasks
	URI Hydrbotics
	This file includes all hardcoded autonomous logic for your usecase

*/

#ifndef TASKS_H
#define TASKS_H

#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"


tardigrade_mission_basic_t qual_descend, qual_forward, qual_ascend;
tardigrade_mission_basic_t* qualification_robosub_2026[3];
//qual_descend

void write_tasks_qualification(){

	//qual_descend
	qual_descend.duration = 1000 * 4;
	qual_descend.speed = 1.0;
	
	qual_descend.translational_movement.x = 0.0;
	qual_descend.translational_movement.y = 0.0;
	qual_descend.translational_movement.z = 1.0; //going down ...

	qual_descend.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_descend.maintain_pose = false;
	
	qual_descend.desired_yaw_offset = 0;
	qual_descend.desired_pitch_offset = 0;
	qual_descend.desired_roll_offset = 0;
	
	qual_descend.adjustment_threshold = 5;

	qual_descend.thruster_time_run = 100;
	qual_descend.thruster_time_adjust = 100;
	//qual_descend
	qual_forward.duration = 1000 * 30;
	qual_forward.speed = 1.0;
	
	qual_forward.translational_movement.x = 1.0; //going forward
	qual_forward.translational_movement.y = 0.0;
	qual_forward.translational_movement.z = 0.0; //going down ...

	qual_forward.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_forward.maintain_pose = false;
	
	qual_forward.desired_yaw_offset = 0;
	qual_forward.desired_pitch_offset = 0;
	qual_forward.desired_roll_offset = 0;
	
	qual_forward.adjustment_threshold = 5;

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
	
	qual_ascend.adjustment_threshold = 5;

	qual_ascend.thruster_time_run = 100;
	qual_ascend.thruster_time_adjust = 100;

	qualification_robosub_2026[0] = &qual_descend;
	qualification_robosub_2026[1] = &qual_forward;
	qualification_robosub_2026[2] = &qual_ascend;

	
}


#endif
