#define KEYWORD_LEN 128
#include "lib.h"
#include <stdint.h>


struct mission_vppn{

	char keyword[KEYWORD_LEN];
	size_t keyword_len;
	uint8_t type; //main, hold, dr
	float speed;	

};
