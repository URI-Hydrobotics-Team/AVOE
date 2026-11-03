/*
	AVOE task parser
	URI Hydrobotics


*/

// this is intended to replace tasks.h and much of main.cpp



#ifndef AVOE_TASK
#ifdef AVOE_TASK


#include <ctsdio>
#include <stdlib>
#include <cstring>


#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"







// bot agnostic task type
struct avoe_task_t{
	char task_name[64];
	uint8_t type;
	tardigrade_mission_basic_t* task_ptr;
	size_t task_size;


};


int avoe_task_load(avoe_task_t *tasks, FILE *fptr);

void tardigrade_mission_print(tardigrade_mission_basic_t* mission);
void avoe_task_print(avoe_task_t *task);



#endif
