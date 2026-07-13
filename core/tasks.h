/*

	AVOE autonmous tasks
	URI Hydrbotics
	This file includes all hardcoded autonomous logic for your usecase

*/

#ifndef TASKS_H
#define TASKS_H

#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"


tardigrade_mission_basic_t qual_descend, qual_forward, qual_ascend;
tardigrade_mission_basic_t* qualification_robosub_2026[4];
//qual_descend

void write_tasks_qualification(){

	//qual_descend
	qual_descend.duration = 1000 * 10;
	qual_descend.speed = 0.5;
	
	qual_descend.translational_movement.x = 0.0;
	qual_descend.translational_movement.y = 0.0;
	qual_descend.translational_movement.z = 1.0; //going down ...

	qual_descend.movement_type = MISSION_BASIC_TRANSLATIONAL_ONLY;
	qual_descend.maintain_pose = true;
	
	qual_descend.desired_yaw_offset = 0;
	qual_descend.desired_pitch_offset = 0;
	qual_descend.desired_roll_offset = 0;
	
	qual_descend.adjustment_threshold = 5;
	qual_descend.adjustment_threshold = 500;

	qual_descend.thruster_time_run = 100;
	qual_descend.thruster_time_adjust = 100;


}


#endif
