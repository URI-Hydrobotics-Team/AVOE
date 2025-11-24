#include <cstring>
#include <iostream>
#include "io.h"
#include "../lib/lib.h"

avoe_comm_transmitter::avoe_comm_transmitter(const char *type_in, const char *channel, int port_in, const char *ip){

	strncpy(type, type_in, 32);
	strncpy(channel_name, channel, 32);
	port = port_in;
	strncpy(dest_ip, ip, 32);
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
			char *temp_str, *data_n;
			size_t temp_size;
			switch(mode){
				//mode 0: send generic string data
				case 0:
					temp_str = new char[data_message_len + 64]; //+ 64 for header stuff
					initStr(temp_str, data_message_len + 64);
					appendStr(temp_str, "$AVOE:", 0);
					appendStr(temp_str, channel_name, strlen(temp_str));
					appendStr(temp_str, ":", strlen(temp_str));
					appendStr(temp_str, type, strlen(temp_str));
					appendStr(temp_str, ":", strlen(temp_str));
					appendStr(temp_str, data_message, strlen(temp_str));
					appendStr(temp_str, "$", strlen(temp_str));

					std::cout << "MODE 0 TRANSMIT: " << temp_str << '\n';

					//socket.transmit(temp_str);
					delete[] temp_str;
					break;
					//mode 1: send sensor data fields
				case 1:

					temp_str = new char[data_sensor_message_len + 64]; //+ 64 for header stuff
					initStr(temp_str, data_message_len + 64);
					appendStr(temp_str, "$AVOE:", 0);
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

					//socket.transmit(temp_str);
					delete[] data_n;
					delete[] temp_str;
					break;
				default:
					break;
			}
		}		

		clock.reset();
	}



}





void avoe_comm_transmitter::set_message(char *mptr, size_t len){
	mode = 0;
	data_message_len = len;
	data_message = mptr;
	if (socket == nullptr){

		socket = new tx_socket(data_message_len + 64);
		socket->init(dest_ip, port);
	}


}

void avoe_comm_transmitter::set_sensor(sensor_t *sensor){
	mode = 1;
	data_sensor = sensor;
	data_sensor_message_len = 128 * (data_sensor->getFieldCount() + 1); // + 1 just so we have room a header
	if (socket == nullptr){
		socket = new tx_socket(data_message_len + 64);
		socket->init(dest_ip, port);
	}


}
void avoe_comm_transmitter::set_timer(unsigned int period){

	tx_period = period;
}
