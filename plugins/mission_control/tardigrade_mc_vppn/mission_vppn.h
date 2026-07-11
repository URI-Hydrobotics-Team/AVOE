#include "../../../lib/lib.h"
#include <stdint.h>

#ifndef MISSION_VPPN_H
#define MISSION_VPPN_H

#define MISSION_VPPN_KEYWORD_LEN 128
struct vppn_mission_t{

	char keyword[MISSION_VPPN_KEYWORD_LEN];
	size_t keyword_len;
	uint8_t type;
	/*
		0 	main
		1 	dead reckon
	*/
	uint16_t scan_interval; // scan interval for type 1
	uint16_t scan_radius; // in degrees
	float speed;	

};

#endif
