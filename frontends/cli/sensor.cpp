#include <iostream>
#include "sensor.h"
#include "../../lib/lib.h"



int map_sensor_string(sensor_t *sensors, const char *message, size_t message_len){

	char temp_str[32];
	
	char channel_name[32];
	char channel_type[32];

	size_t temp_index = 0;

	/* basic checks */
	if (message[0] != '$'){
		return -1;
	}

	if (message[5] != 'S'){
		//check header for type (S = sensor)
		return -1; 
	}


	initStr(temp_str, 32);
	for (size_t i = 6; i < message_len; i++){

		if (message[i] == ':'){
			break;
		}

		temp_str[temp_index] = message[i];


		temp_index++;
	}


	std::cout << "DETECTED CHANNEL: " << temp_str << '\n';
	initStr(temp_str, 32);
	for (size_t i = 6; i < message_len; i++){

		if (message[i] == ':'){
			break;
		}

		temp_str[temp_index] = message[i];


		temp_index++;
	}

	std::cout << "DETECTED TYPE: " << temp_str << '\n';




}
