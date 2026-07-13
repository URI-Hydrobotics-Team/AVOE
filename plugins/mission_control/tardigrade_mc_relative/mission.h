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
	
	//units: degrees
	uint16_t desired_yaw, desired_pitch, desired_roll; //read only
	uint16_t initial_yaw, initial_pitch, initial_roll; //write 
	uint16_t adjustment_threshold;
};

#endif
