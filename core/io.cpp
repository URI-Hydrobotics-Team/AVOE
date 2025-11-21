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

		

}


void avoe_comm_transmitter::set_message(char *mptr, size_t len){

	data_message_len = len;
	data_message = mptr;
	if (socket == nullptr){

		socket = new tx_socket(len);
	}
	
	
}

void avoe_comm_transmitter::set_timer(unsigned int period){
	
	tx_period = period;
}
