#define KEYWORD_LEN 128
#include "lib.h"
#include <stdint.h>


struct mission_vppn{

	char keyword[KEYWORD_LEN];
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
