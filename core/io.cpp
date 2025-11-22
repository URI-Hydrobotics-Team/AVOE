#include <cstring>
#include "io.h"


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

			switch(mode){

				case 0:
					socket.transmit(data_message);
					break;
				default:
					break;
			}
		}		
		
		clock.reset();
	}



}

void avoe_comm_transmitter::set_message(char *mptr, size_t len){

	data_message_len = len;
	data_message = mptr;
	if (socket == nullptr){

		socket = new tx_socket(len);
		socket.init(dest_ip, port);
	}
	
	
}

void avoe_comm_transmitter::set_timer(unsigned int period){
	
	tx_period = period;
}
