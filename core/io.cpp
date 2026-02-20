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


	//null ptrs
	data_sensor = nullptr;
	data_motor = nullptr;
	data_message = nullptr;	
	socket = nullptr;

	//type parsing
	mode = -1;
	if (strcmp(type, "message") == 0){
		mode = 0;
	}
	if (strcmp(type, "sensor") == 0){
		mode = 1;
	}
	if (strcmp(type, "motor") == 0){
		mode = 2;
	}	

}

void avoe_comm_transmitter::refresh(){
	//refresh based on timer
	if (tx_period == 0){
		return; //timer is off
	}

	if (clock.getElaspedTimeMS() >= tx_period){
		if (socket != nullptr){
			tx();
		}		

		clock.reset();
	}
}

void avoe_comm_transmitter::set_message(char *mptr, size_t len){
	// set mode (according to the design in the io.h file)
	mode = 0;

	// set message length and set the message to be sent
	data_message_len = len;
	data_message = mptr;

	// check socket is initialize
	if (socket == nullptr){
		socket = new tx_socket(data_message_len + 64); // add 64 to take care of header
		socket->init(dest_ip, port);
	}


}

void avoe_comm_transmitter::set_sensor(sensor_t *sensor){
	mode = 1;
	data_sensor = sensor;
	data_sensor_message_len = 128 * (data_sensor->getFieldCount() + 1); // + 1 just so we have room for a header
	if (socket == nullptr){
		socket = new tx_socket(data_sensor_message_len + 64);
		socket->init(dest_ip, port);
	}


}

void avoe_comm_transmitter::set_motor(motor_t *motor) {
	mode = 2;
	data_motor = motor;

	data_motor_message_len = 128 * (data_motor->getFieldCount() + 1);

	if (socket == nullptr){
		socket = new tx_socket(data_motor_message_len + 64);
		socket->init(dest_ip, port);
	}
}

void avoe_comm_transmitter::set_timer(unsigned int period){
	tx_period = period;
}

void avoe_comm_transmitter::tx() {
	size_t temp_size;
	char *temp_str, *data_n;
	// mode check
	switch(mode){
		//mode 0: send generic string data
		case 0:

			// allocate new char array
			temp_str = new char[data_message_len + 64]; //+ 64 for header stuff
			initStr(temp_str, data_message_len + 64);
			appendStr(temp_str, "$AVOEG:", 0); //'G' indicates generic message
			appendStr(temp_str, channel_name, strlen(temp_str));
			appendStr(temp_str, ":", strlen(temp_str));
			appendStr(temp_str, type, strlen(temp_str));
			appendStr(temp_str, ":", strlen(temp_str));
			appendStr(temp_str, data_message, strlen(temp_str));
			appendStr(temp_str, "$", strlen(temp_str));

			std::cout << "MODE 0 TRANSMIT: " << temp_str << '\n';

			socket->transmit(temp_str);
			
			delete[] temp_str;
			break;

		//mode 1: send sensor data fields
		case 1:

			temp_str = new char[data_sensor_message_len + 64]; //+ 64 for header stuff
			initStr(temp_str, data_message_len + 64);
			appendStr(temp_str, "$AVOES:", 0); //'S' indicates sensor
			appendStr(temp_str, channel_name, strlen(temp_str));
			appendStr(temp_str, ":", strlen(temp_str));
			appendStr(temp_str, type, strlen(temp_str));
			appendStr(temp_str, ":", strlen(temp_str));

			// format sensor_t data
			temp_size = 64 + data_sensor->getFieldCount() * 128;
			data_n = new char[temp_size]; 
			initStr(data_n, temp_size);

			appendStr(data_n, data_sensor->getType(), 0);
			appendStr(data_n, " ", strlen(data_n));
			appendStr(data_n, data_sensor->getModel(), strlen(data_n));
			appendStr(data_n, " ", strlen(data_n));

			appendStr(data_n, std::to_string(data_sensor->getFieldCount()).c_str(), strlen(data_n));	
			appendStr(data_n, " ", strlen(data_n));
			for (size_t i = 0; i < data_sensor->getFieldCount(); i++){
				appendStr(data_n, data_sensor->read(i), strlen(data_n));
				appendStr(data_n, " ", strlen(data_n));
			}

			//done
			appendStr(temp_str, data_n, strlen(temp_str)); //append sensor_t data to  temp_str
			appendStr(temp_str, "$", strlen(temp_str));

			std::cout << "MODE 1 TRANSMIT: " << temp_str << '\n';

			socket->transmit(temp_str);

			delete[] data_n;
			delete[] temp_str;
			break;
			
		default:
			break;
	}
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






