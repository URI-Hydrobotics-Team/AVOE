#include <cstring>
#include <iostream>
#include "io.h"
#include "../lib/lib.h"

avoe_comm_transmitter::avoe_comm_transmitter(const char *type_in, const char *channel, int port_in, const char *ip){
	// copy the type, channel, ip into class variable
	strncpy(type, type_in, 32);
	strncpy(channel_name, channel, 32);
	strncpy(dest_ip, ip, 32);

	// port on other device to send info to
	port = port_in;
	tx_period = 0; //default timer value;	
	sensor_count = 0;
	sensor_index = 0;
	vector_index = 0;
	vector_count = 0;
	motor_index = 0;
	motor_count = 0;
	data_message_len = 0;
	//null ptrs
	motor_table = nullptr;
	sensor_table = nullptr;
	vector_table = nullptr;
	data_message = nullptr;	


	// setup socket

	socket = new tx_socket; // add 64 to take care of header
	socket->init(dest_ip, port);



}

void avoe_comm_transmitter::refresh(){
	//refresh based on timer
	if (tx_period == 0){
		return; //timer is off
	}

	if (clock.getElaspedTimeMS() >= tx_period){
		tx();
		clock.reset();
	}
}

void avoe_comm_transmitter::set_message(char *mptr, size_t len){

	// set message length and set the message to be sent
	data_message_len = len;
	data_message = mptr;

}

void avoe_comm_transmitter::add_sensor(sensor_t *sensor){


	if (sensor_count == 0){
		sensor_table = new sensor_t*[1];
		sensor_table[0] = sensor;
		sensor_count++;	
	}else{
		sensor_t **temp = new sensor_t*[sensor_count + 1];
		for (size_t i = 0; i < sensor_count; i++){
			temp[i] = sensor_table[i];
		}
		temp[sensor_count] = sensor;
		sensor_count++;

		delete[] sensor_table;
		sensor_table = temp;
	


	}
	std::cout << "[IO] sensor " << sensor->getModel() << " added to " << channel_name << '\n'; 


}

void avoe_comm_transmitter::add_motor(motor_t *motor) {


	if (motor_count == 0){
		motor_table = new motor_t*[1];
		motor_table[0] = motor;
		motor_count++;	
	}else{
		motor_t **temp = new motor_t*[motor_count + 1];
		for (size_t i = 0; i < motor_count; i++){
			temp[i] = motor_table[i];
		}
		temp[motor_count] = motor;
		motor_count++;

		delete[] motor_table;
		motor_table = temp;
	

	}

	std::cout << "[IO] motor " << motor->getModel() << " added to " << channel_name << '\n'; 
}


void avoe_comm_transmitter::add_vector(vector_t *vector){

	if (vector_count == 0){
		vector_table = new vector_t*[1];
		vector_table[0] = vector;
		vector_count++;	
	}else{
		vector_t** temp = new vector_t*[vector_count + 1];
		for (size_t i = 0; i < vector_count; i++){
			temp[i] = vector_table[i];
		}
		temp[vector_count] = vector;
		vector_count++;

		delete[] vector_table;
		vector_table = temp;
	


	}
	std::cout << "[IO] vector added to " << channel_name << '\n'; 


}



void avoe_comm_transmitter::set_timer(unsigned int period){
	tx_period = period;
}

void avoe_comm_transmitter::update_index(){

	char sensor_count_str[4];
	char motor_count_str[4];
	char vector_count_str[4];
	char data_message_len_str[16];

	initStr(sensor_count_str, 4);
	initStr(motor_count_str, 4);
	initStr(vector_count_str, 4);
	initStr(data_message_len_str, 16);

	sprintf(sensor_count_str, "%d", sensor_count);
	sprintf(motor_count_str, "%d", motor_count);
	sprintf(vector_count_str, "%d", vector_count);
	sprintf(data_message_len_str, "%d", data_message_len);

	initStr(index, INDEX_SIZE);

	appendStr(index, "S", 0);
	appendStr(index, sensor_count_str, strlen(index));
	appendStr(index, "M", strlen(index));
	appendStr(index, motor_count_str, strlen(index));
	appendStr(index, "V", strlen(index));
	appendStr(index, vector_count_str, strlen(index));
	appendStr(index, "C", strlen(index));
	appendStr(index, data_message_len_str, strlen(index));

}



void avoe_comm_transmitter::tx() {

	/*
		message structure
		$<header>%<sensors>%<motors>%<vectors>%<string>$

		$	start and end of message
		%	start of new section
		*	start of object
		:	internal seperators

	*/


	size_t temp_size = 0;
	char *header, *temp_str, *temp_buffer;

	header = new char[128];
	// make header
	update_index();
	initStr(header, 128);
	appendStr(header, "$AVOE:", 0); 
	appendStr(header, channel_name, strlen(header));
	appendStr(header, ":", strlen(header));
	appendStr(header, index, strlen(header));
	appendStr(header, "%", strlen(header));

	// we need to determine the sizes of all associated data	
	temp_size += strlen(header);
	temp_size += data_message_len;
	for (size_t i = 0; i < sensor_count; i++){
		temp_size += sensor_table[i]->getFieldCount() * 128;
		
	}
	for (size_t i = 0; i < motor_count; i++){
		temp_size += motor_table[i]->getFieldCount() * 128;
		
	}
	temp_size += vector_count * 128;


	// now we can allocate	
	temp_str = new char[temp_size];
	initStr(temp_str, temp_size);
	std::cout << "[IO] created tx buffer of length: " << temp_size << '\n';
	
	appendStr(temp_str, header, 0);
	delete[] header;
	// add sensors

	

	
	for (size_t i = 0; i < sensor_count; i++){
		appendStr(temp_str, "*", strlen(temp_str));
		size_t sensor_buffer_size = sensor_table[i]->getBufferSize();
		temp_buffer = new char[sensor_buffer_size];
		initStr(temp_buffer, sensor_buffer_size);
		sensor_table[i]->writeToBuffer(temp_buffer);	
		appendStr(temp_str, temp_buffer, strlen(temp_str));

		delete[] temp_buffer;
		
	}

	appendStr(temp_str, "%", strlen(temp_str));
	for (size_t i = 0; i < motor_count; i++){
		appendStr(temp_str, "*", strlen(temp_str));
		size_t motor_buffer_size = motor_table[i]->getBufferSize();
		temp_buffer = new char[motor_buffer_size];
		initStr(temp_buffer, motor_buffer_size);
		motor_table[i]->writeToBuffer(temp_buffer);	
		appendStr(temp_str, temp_buffer, strlen(temp_str));

		delete[] temp_buffer;

	}

	appendStr(temp_str, "%", strlen(temp_str));



	for (size_t i = 0; i < vector_count; i++){
		appendStr(temp_str, "*", strlen(temp_str));
		temp_buffer = new char[128];
		initStr(temp_buffer, 128);

		appendStr(temp_buffer, (std::to_string(vector_table[i]->x)).c_str(), 0);
		appendStr(temp_buffer, ",", strlen(temp_buffer));
		appendStr(temp_buffer, (std::to_string(vector_table[i]->y)).c_str(), strlen(temp_buffer));
		appendStr(temp_buffer, ",", strlen(temp_buffer));
		appendStr(temp_buffer, (std::to_string(vector_table[i]->z)).c_str(), strlen(temp_buffer));
		appendStr(temp_buffer, ",", strlen(temp_buffer));


		appendStr(temp_str, temp_buffer, strlen(temp_str));
		delete[] temp_buffer;
	
	}

	appendStr(temp_str, "%", strlen(temp_str));
	// add generic data message

	if (data_message_len > 0){
		appendStr(temp_str, data_message, strlen(temp_str));

	}

		
	appendStr(temp_str, "$", strlen(temp_str)); //terminate with '$'

	//std::cout << temp_str << '\n';
	socket->transmit(temp_str, strlen(temp_str));	

	delete[] temp_str;

}



avoe_comm_reciever::avoe_comm_reciever(const char *type_in, const char *channel, int port_in, size_t len){
	rx_buffer_len = len;
	// copy the type, channel, ip into class variable
	strncpy(type, type_in, 32);
	strncpy(channel_name, channel, 32);

	// port on other device to send info to
	port = port_in;
	rx_period = 0; //default timer value;	
	sensor_count = 0;
	vector_count = 0;
	motor_count = 0;
	data_message_len = 0;
	//null ptrs
	motor_table = nullptr;
	sensor_table = nullptr;
	vector_table = nullptr;
	data_message = nullptr;	


	// setup socket

	socket = new rx_socket; // add 64 to take care of header
	socket->init(port);



}

void avoe_comm_reciever::refresh(){
	if (rx_period == 0){
		return; //timer is off
	}
	if (clock.getElaspedTimeMS() >= rx_period){
		if (socket != nullptr){
			rx();	
		}		

		clock.reset();
	}
}

void avoe_comm_reciever::set_message(char *mptr, size_t len){

	// set message length and set the message to be sent
	data_message_len = len;
	data_message = mptr;

}

void avoe_comm_reciever::add_sensor(sensor_t *sensor){


	if (sensor_count == 0){
		sensor_table = new sensor_t*[1];
		sensor_table[0] = sensor;
		sensor_count++;	
	}else{
		sensor_t **temp = new sensor_t*[sensor_count + 1];
		for (size_t i = 0; i < sensor_count; i++){
			temp[i] = sensor_table[i];
		}
		temp[sensor_count] = sensor;
		sensor_count++;

		delete[] sensor_table;
		sensor_table = temp;
	


	}
	std::cout << "[IO] sensor " << sensor->getModel() << " added to " << channel_name << '\n'; 


}

void avoe_comm_reciever::add_motor(motor_t *motor) {


	if (motor_count == 0){
		motor_table = new motor_t*[1];
		motor_table[0] = motor;
		motor_count++;	
	}else{
		motor_t **temp = new motor_t*[motor_count + 1];
		for (size_t i = 0; i < motor_count; i++){
			temp[i] = motor_table[i];
		}
		temp[motor_count] = motor;
		motor_count++;

		delete[] motor_table;
		motor_table = temp;
	

	}

	std::cout << "[IO] motor " << motor->getModel() << " added to " << channel_name << '\n'; 
}


void avoe_comm_reciever::add_vector(vector_t *vector){

	if (vector_count == 0){
		vector_table = new vector_t*[1];
		vector_table[0] = vector;
		vector_count++;	
	}else{
		vector_t** temp = new vector_t*[vector_count + 1];
		for (size_t i = 0; i < vector_count; i++){
			temp[i] = vector_table[i];
		}
		temp[vector_count] = vector;
		vector_count++;

		delete[] vector_table;
		vector_table = temp;
	


	}
	std::cout << "[IO] vector added to " << channel_name << '\n'; 


}


void avoe_comm_reciever::set_timer(unsigned int period){
	rx_period = period;
}

void avoe_comm_reciever::update_index(){

	char sensor_count_str[4];
	char motor_count_str[4];
	char vector_count_str[4];
	char data_message_len_str[16];

	initStr(sensor_count_str, 4);
	initStr(motor_count_str, 4);
	initStr(vector_count_str, 4);
	initStr(data_message_len_str, 16);

	sprintf(sensor_count_str, "%d", sensor_count);
	sprintf(motor_count_str, "%d", motor_count);
	sprintf(vector_count_str, "%d", vector_count);
	sprintf(data_message_len_str, "%d", data_message_len);

	initStr(index, INDEX_SIZE);

	appendStr(index, "S", 0);
	appendStr(index, sensor_count_str, strlen(index));
	appendStr(index, "M", strlen(index));
	appendStr(index, motor_count_str, strlen(index));
	appendStr(index, "V", strlen(index));
	appendStr(index, vector_count_str, strlen(index));
	appendStr(index, "C", strlen(index));
	appendStr(index, data_message_len_str, strlen(index));

}
	/*
		message structure
		$<header>%<sensors>%<motors>%<vectors>%<string>$

		$	start and end of message
		%	start of new section
		*	start of object
		:	internal seperators

	*/




int map_sensor(sensor_t *sensor, const char *message, size_t message_len){

	// *message should point to the start of the sensor_t object's contens

	// structure <type>:<model>:<field count>:DATA:<field 1>:<field 2>:...%

	// create some temp strings for the mapping


	char temp_str[32];
	size_t index, temp_index;



	size_t field_count;
	char field_count_str[4];
	char model[32]; 
	char type[32];

	initStr(model, 32);
	initStr(type, 32);


	initStr(field_count_str, 4);


	initStr(temp_str, 32);

	// start parsing
	index = 0; temp_index = 0;

	for (index < message_len; index++;){

		if (message[index] == ':'){
			break;
		}
		temp_str[temp_index] = message[index];
		temp_index++;
	}

	
	strncpy(model, temp_str, temp_index);
	initStr(temp_str, 32);
	temp_index = 0;
	
	for (index < message_len; index++;){

		if (message[index] == ':'){
			break;
		}
		temp_str[temp_index] = message[index];
		temp_index++;
	}
	
	strncpy(field_count_str, temp_str, temp_index);
	initStr(temp_str, 32);
	temp_index = 0;

	std::cout << "DETECTED TYPE: " << type << '\n';
	std::cout << "DETECTED MODEL: " << model << '\n';
	std::cout << "DETECTED FIELDS: " << field_count_str << '\n';
	
	field_count = atoi(field_count_str);

	// match

	if (strncmp(sensor->getType(), type, 32) == 0 && strncmp(sensor->getModel(), model, 32) == 0){
		//std::cout << "sensor_t match for \n";
	}else{
		return -1;
	} 


	char temp_field_str[128];
	initStr(temp_field_str, 128);
	
	for (size_t i = 0; i < field_count; i++){
		for (index < message_len; index++;){

			if (message[index] == ':'){
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



void avoe_comm_reciever::rx(){
	// first we recieve via the socket


	char *rx_buffer = new char[rx_buffer_len];

	socket->rec(0, rx_buffer, rx_buffer_len); //recieve the data

	size_t rx_message_len = strlen(rx_buffer);

	if (rx_message_len > 0){

		std::cout << "[IO] Recevied Message of Length " << rx_message_len << '\n';
	}else{
		// no message
		return;
	}
	
	// construct a local version of the header 
	char local_header[128];

	update_index();
	initStr(local_header, 128);
	appendStr(local_header, "$AVOE:", 0); 
	appendStr(local_header, channel_name, strlen(local_header));
	appendStr(local_header, ":", strlen(local_header));
	appendStr(local_header, index, strlen(local_header));
	appendStr(local_header, "%", strlen(local_header));

	size_t header_len = strlen(local_header);

	// do the header check

	//std::cout << "header len: " << header_len << '\n';	
	if (strncmp(local_header, rx_buffer, header_len) != 0){
		std::cout << "[IO] RX Header Mismatch. Local: \"" << local_header << "\" Recevied: \"" <<  rx_buffer << "\"\n";
		return;
	}


	//std::cout << "header match\n";
	//extract all fields

	size_t index;

	size_t section_index = 0;
	size_t sensor_index = 0;
	size_t motor_index = 0;
	size_t vector_index = 0;


	for (index = 0; index < rx_message_len; index++){

		switch (rx_buffer[index]){
			case '%':
				section_index++;
				break;
			case '*':
				if (section_index == 1){
					map_sensor(sensor_table[sensor_index], rx_buffer + index - 1, rx_buffer_len);
					sensor_index++;
				}
				if (section_index == 2){
					//map_motor(sensor_table[sensor_index], rx_buffer[index], rx_buffer_len);
					motor_index++;
				}	
				if (section_index == 3){
					//map_vector(sensor_table[sensor_index], rx_buffer[index], rx_buffer_len);
					
					std::cout << "process some vectors\n";
					vector_index++;
				}
				if (section_index == 4){
					//extract string

				}

		
				break;

			case '$':
				//exit
				break;
		}

	}

	delete[] rx_buffer;
}
