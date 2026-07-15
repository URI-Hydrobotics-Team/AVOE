#include <stdint.h>
#include "../../../lib/lib.h"
#include <sys/types.h>
#include "../../../core/sensor.h"
#include "../../../lib/clock.h"
#include "../../../lib/lib.h"

#ifndef MISSION_BASIC_H
#define MISSION_BASIC_H

#define MISSION_BASIC_NAME_LEN 32
#define MISSION_BASIC_LATERAL_ONLY 0
#define MISSION_BASIC_TRANSLATIONAL_ONLY 1

struct tardigrade_mission_basic_t{

	char name[MISSION_BASIC_NAME_LEN];
	uint32_t duration; //ms
	float speed; //rate
	vector_t translational_movement, lateral_movement;

	uint8_t movement_type;
	bool maintain_pose, maintain_pose_abs;
	//units: degrees
	int16_t desired_yaw_offset, desired_pitch_offset, desired_roll_offset; //read only
	int16_t desired_yaw_abs, desired_pitch_abs, desired_roll_abs; //read only
	int16_t initial_yaw, initial_pitch, initial_roll; //write 
	uint16_t adjustment_threshold; //degrees
	uint16_t thruster_time_run, thruster_time_adjust; // ms

	//thruster table overide
	bool thruster_table_overide;
	float *translation_thrust_table, *lateral_thrust_table;
	
};

#endif
