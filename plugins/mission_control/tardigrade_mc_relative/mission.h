#include <stdint.h>



#ifndef MISSION_BASIC_H
#define MISSION_BASIC_H

#define MISSION_BASIC_NAME_LEN 32


struct tardigrade_mission_basic_t{

	char name[MISSION_BASIC_NAME_LEN];
	uint16_t duration; //ms
	float speed;
	vector_t translational_movement, lateral_movement;

	bool maintain_pose;
	uint16_t desired_pose, desired_pitch, desired_roll;
};

#endif
