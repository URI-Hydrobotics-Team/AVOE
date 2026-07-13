/*

	AVOE autonmous tasks
	URI Hydrbotics
	This file includes all hardcoded AI logic for your usecase

*/

#ifndef TASKS_H
#define TASKS_H

#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"


tardigrade_mission_basic_t qual_descend, qual_forward, qual_ascend;

//qual_descend
qual_descend.duration = 1000 * 10;
qual_descend.speed = 0.5;



tardigrade_mission_basic_t qualification_robosub_2026[4] = {};




#endif
