#include "../../core/io.h"
#include "../../lib/lib.h"

#define PORT 9000
#define MAXIMUM_RX_BUFFER_SIZE 256
#define BUFFER_SIZE 128
#define SLEEP 1000 //us
/* a test to see if binding to the same port with tx and rx objects works */

int main(int argc, char** argv){
	if (argc != 5){
		printf("Improper amount of arguments: ./bidirectional <Destination IP> <TX Message> <TX Topic> <RX Topic>\n");
		return 0;

	}

	char rx_buffer[BUFFER_SIZE];
	char tx_buffer[BUFFER_SIZE];

	
	
	char host_ip[16];
	memset(host_ip, 0, 16);
	strncpy(host_ip, argv[1], 16);
		
	memset(tx_buffer, 0, BUFFER_SIZE);
	strncpy(tx_buffer, argv[2], BUFFER_SIZE);
	
	char tx_topic[32], rx_topic[32];

	memset(tx_topic, 0, 32);
	strncpy(tx_topic, argv[3], 32);
	
	memset(rx_topic, 0, 32);
	strncpy(rx_topic, argv[4], 32);
	

	avoe_comm_transmitter tx("generic", tx_topic, PORT, host_ip);
	avoe_comm_reciever rx("generic", rx_topic, PORT, MAXIMUM_RX_BUFFER_SIZE);



	rx.set_message(rx_buffer, BUFFER_SIZE);
	tx.set_message(tx_buffer, BUFFER_SIZE);
	rx.set_timer(10);
	tx.set_timer(10);

	while(1){
		
		usleep(SLEEP);
		rx.refresh();
		tx.refresh();
		printf("RX_BUFFER: %s\n", rx_buffer);
	}



	return 0;
}
