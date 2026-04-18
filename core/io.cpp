#include <cstring>
#include <iostream>
#include "io.h"
#include "../lib/lib.h"

avoe_comm_transmitter::avoe_comm_transmitter(const char *channel, int port_in, const char *ip){
	// copy the type, channel, ip into class variable
	strncpy(channel_name, channel, 32);
	strncpy(dest_ip, ip, 32);

	// port on other device to send info to
	port = port_in;
	tx_period = 0; //default timer value;	
	sensor_count = 0;
	sensor_index = 0;
	data_message_len = 0;
	
	//null ptrs
	motor_table = nullptr;
	sensor_table = nullptr;
	vector_table = nullptr;
	data_message = nullptr;	
	socket = nullptr;

	
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
	// set mode (according to the design in the io.h file)
	mode = 0;

	// set message length and set the message to be sent
	data_message_len = len;
	data_message = mptr;

	/*
	// check socket is initialize
	if (socket == nullptr){
		socket = new tx_socket(data_message_len + 64); // add 64 to take care of header
		socket->init(dest_ip, port);
	}
	*/

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
	appendStr(index, data_message_len, strlen(index));

}


void avoe_comm_transmitter::tx() {
	size_t temp_size;
	char *header, temp_str, temp_buffer;

	temp_buffer = new char[128];
	// make header
	updateIndex();
	temp_str = new char[128];
	initStr(header, 128);
	appendStr(header, "$AVOE:", 0); 
	appendStr(header, channel_name, strlen(header));
	appendStr(header, ":", strlen(header));
	appendStr(header, index, strlen(header));
	appendStr(header, ":", strlen(header));

	// we need to determine the sizes of all associated data	
	temp_size += strlen(header);
	temp_size += data_message_len;
	for (size_t i = 0; i < sensor_count; i++){
		temp_size += sensor_table[i]->getBufferSize();
		
	}
	for (size_t i = 0; i < motor_count; i++){
		temp_size += motor_table[i]->getBufferSize();
		
	}
	temp_size += vector_count * sizeof(vector_t);

	// now we can allocate	
	temp_str = new char[temp_size];
	initStr(temp_str, temp_size);
	std::cout << "[IO] created tx buffer of length: " << temp_size << '\n';
	
	appendStr(temp_str, header, 0);
	// add sensors

	for (size_t i = 0; i < sensor_count; i++){

		initStr(temp_buffer, 128);
		sensor_table[i]->writeToBuffer(temp_buffer);
		appendStr(temp_str, temp_buffer, strlen(temp_str));
		appendStr(temp_str, "!", strlen(temp_str));

	}

	appendStr(temp_str, ":", strlen(temp_str));
	for (size_t i = 0; i < sensor_count; i++){
		initStr(temp_buffer, 128);
		sensor_table[i]->writeToBuffer(temp_buffer);
		appendStr(temp_str, temp_buffer, strlen(temp_str));
		appendStr(temp_str, "!", strlen(temp_str));

	}


	appendStr(temp_str, ":", strlen(temp_str));
	for (size_t i = 0; i < vector_count; i++){
		initStr(temp_buffer, 128);

		appendStr(temp_buffer, (std::to_string(tm_vector.x)).c_str(), 0);
		appendStr(temp_buffer, ",", strlen(temp_buffer));
		appendStr(temp_buffer, (std::to_string(tm_vector.y)).c_str(), strlen(t_vector_str));
		appendStr(temp_buffer, ",", strlen(temp_buffer));
		appendStr(temp_buffer, (std::to_string(tm_vector.z)).c_str(), strlen(t_vector_str));
		appendStr(temp_buffer, ",", strlen(temp_buffer));



		appendStr(temp_str, temp_buffer, strlen(temp_str));
		appendStr(temp_str, "!", strlen(temp_str));

	}

	appendStr(temp_str, ":", strlen(temp_str));
	// add generic data message

	if (data_message_len > 0){
		appendStr(temp_str, data_message, strlen(temp_str));

	}

		
	appendStr(temp_str, "$", strlen(temp_str)); //terminate with '$'

	

	delete temp_str[];
	delete temp_buffer[];


}



avoe_comm_reciever::avoe_comm_reciever(const char *type_in, const char *channel, int port_in){
	// copy the type, channel, ip into class variable
	strncpy(type, type_in, 32);
	strncpy(channel_name, channel, 32);

	// port on other device to send info to
	port = port_in;
	rx_period = 0; //default timer value;	

	data_message = nullptr;	
	socket = nullptr;

		

}


void avoe_comm_reciever::set_message(char *mptr, size_t len){

	data_message = mptr;
	data_message_len = len;
	socket = new rx_socket(len);
	socket->init(port);
	
	
}

void avoe_comm_reciever::refresh(){
	//refresh based on timer
	if (rx_period == 0){
		return; //timer is off
	}

	if (clock.getElaspedTimeMS() >= rx_period){
		if (socket != nullptr){
			//rx
			strncpy(data_message, socket->rec(0), data_message_len);
					
		}		

		clock.reset();
	}
}

void avoe_comm_reciever::set_timer(unsigned int period){
	rx_period = period;
}

void avoe_comm_reciever::rx(){

	strncpy(data_message, socket->rec(0), data_message_len);

}


int avoe_comm_reciever_decode_message(char *destination, const char *message, size_t n){

	// example:
	// $AVOEG:vector:message:1,1,1$


//std::cout << "operating on: " << message << '\n';

	size_t seperator_count = 0;
	size_t temp_index = 0;
	size_t index = 0;


	if (message[0] != '$'){
		return -1;
	}

	if (message[5] != 'G'){
		//check header for type (G = general message)
		return -1; 
	}


	initStr(destination, n);


	for (index = 7; index < n; index++){

		if (message[index] == ':'){
			seperator_count++;
			continue;
		}

		if (message[index] == '$'){
			//done;
			break;
		}


		if (seperator_count == 2){
			destination[temp_index] = message[index];
			temp_index++;
		}

	}

	return 1;
}



