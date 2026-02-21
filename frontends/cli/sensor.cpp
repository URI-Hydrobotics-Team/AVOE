#include <iostream>
#include "sensor.h"
#include "../../lib/lib.h"



int map_sensor_string(sensor_t *sensor, const char *message, size_t message_len){


	//std::cout << "operating on: " << message << '\n';

	char temp_str[32];
	size_t temp_index = 0;
	size_t index = 0;


	char channel_name[32];
	char channel_type[32];

	size_t channel_name_len;
	size_t channel_type_len;



	size_t field_count;
	char field_count_str[4];

	char model[32]; 
	char vendor[32];
	char label[32];
	char protocol[16];
	char type[32];


	initStr(model, 32);
	initStr(vendor, 32);
	initStr(label, 32);
	initStr(protocol, 32);
	initStr(type, 32);


	initStr(field_count_str, 4);

	initStr(channel_name, 32);
	initStr(channel_type, 32);

	
	
	
	/* basic checks */
	if (message[0] != '$'){
		return -1;
	}

	if (message[5] != 'S'){
		//check header for type (S = sensor)
		return -1; 
	}


	initStr(temp_str, 32);



	for (index = 7; index < message_len; index++){

		if (message[index] == ':'){
			break;
		}

		temp_str[temp_index] = message[index];

		temp_index++;

	}




	channel_name_len = temp_index;
	strncpy(channel_name, temp_str, channel_name_len);
	initStr(temp_str, 32);
	temp_index = 0;

	for (index < message_len; index++;){

		if (message[index] == ':'){
			break;
		}

		temp_str[temp_index] = message[index];


		temp_index++;
	}

	channel_type_len = temp_index;
	strncpy(channel_type, temp_str, channel_type_len);
	initStr(temp_str, 32);
	temp_index = 0;

	for (index < message_len; index++;){

		if (message[index] == ' '){
			break;
		}

		temp_str[temp_index] = message[index];


		temp_index++;
	}

	
	strncpy(type, temp_str, temp_index);
	initStr(temp_str, 32);
	temp_index = 0;

	for (index < message_len; index++;){

		if (message[index] == ' '){
			break;
		}

		temp_str[temp_index] = message[index];


		temp_index++;
	}

	
	strncpy(model, temp_str, temp_index);
	initStr(temp_str, 32);
	temp_index = 0;
	
	for (index < message_len; index++;){

		if (message[index] == ' '){
			break;
		}

		temp_str[temp_index] = message[index];


		temp_index++;
	}

	
	strncpy(field_count_str, temp_str, temp_index);
	initStr(temp_str, 32);
	temp_index = 0;

	/*
	std::cout << "DETECTED CHANNEL: " << channel_name << '\n';
	std::cout << "DETECTED CHANNEL TYPE: " << channel_type << '\n';
	std::cout << "DETECTED TYPE: " << type << '\n';
	std::cout << "DETECTED MODEL: " << model << '\n';
	std::cout << "DETECTED FIELDS: " << field_count_str << '\n';
	*/
	field_count = atoi(field_count_str);

	// match


	//std::cout << sensor->getModel() << ' ' << sensor->getType() << '\n';

	if (strncmp(sensor->getType(), type, 32) == 0 && strncmp(sensor->getModel(), model, 32) == 0){
		std::cout << "sensor_t match for \n";
	}else{
		return -1;
	} 


	char temp_field_str[128];
	initStr(temp_field_str, 128);

	
	for (size_t i = 0; i < field_count; i++){
		for (index < message_len; index++;){

			if (message[index] == ' '){
				break;
			}

			temp_field_str[temp_index] = message[index];
			temp_index++;
		}
		sensor->write(temp_field_str, i, temp_index);
		temp_index = 0;
		initStr(temp_field_str, 128);

	}


	
	// now we will now compare these values to sensor and update values accordingly


	return 1;

}
