#include "../../../lib/lib.h"
#include <stdint.h>

#ifndef MISSION_CV_H
#define MISSION_CV_H

#define MISSION_CV_NAME_LEN 32


struct tardigrade_mission_cv_t{

	char name[MISSION_CV_NAME_LEN];
	uint16_t duration; //ms
	float speed;
	vector_t translational_movement, lateral_movement;
};

#endif