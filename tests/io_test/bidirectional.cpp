#include "../../core/io.h"
#include "../../lib/lib.h"

#define PORT 9000
#define MAXIMUM_RX_BUFFER_SIZE 256
#define BUFFER_SIZE 128
#define SLEEP 1000000 //us


#define TX 0
#define RX 1


/* a test to see if binding to the same port with tx and rx objects works */

/* 
	verdict: it doesn't work becuase when a socket is read from the buffer, the buffer is cleared. So when two processes are bound to the same ip and port, they use the same socket internally

*/

int main(int argc, char** argv){
	if (argc != 6){
		printf("Improper amount of arguments: ./bidirectional <Destination IP> <TX Message> <TX Topic> <RX Topic> <tx or rx, depending on the punishment>\n");
		return 0;

	}

	char rx_buffer[BUFFER_SIZE];
	char tx_buffer[BUFFER_SIZE];

	
	
	char host_ip[16];
	memset(host_ip, 0, 16);
	strncpy(host_ip, argv[1], 16);
		
	memset(tx_buffer, 0, BUFFER_SIZE);
	strncpy(tx_buffer, argv[2], BUFFER_SIZE);
	
	char tx_topic[32], rx_topic[32], mode_str[32];

	memset(tx_topic, 0, 32);
	strncpy(tx_topic, argv[3], 32);
	
	memset(rx_topic, 0, 32);
	strncpy(rx_topic, argv[4], 32);
	
	memset(mode_str, 0, 32);
	strncpy(mode_str, argv[5], 32);

	int mode;
	if (strncmp(mode_str, "rx", 32) == 0){

		mode = RX;
	}
	if (strncmp(mode_str, "tx", 32) == 0){

		mode = TX;
	}	


	avoe_comm_transmitter tx("generic", tx_topic, PORT, host_ip);
	avoe_comm_reciever rx("generic", rx_topic, PORT, MAXIMUM_RX_BUFFER_SIZE);



	rx.set_message(rx_buffer, BUFFER_SIZE);
	tx.set_message(tx_buffer, BUFFER_SIZE);
	rx.set_timer(10);
	tx.set_timer(10);

	//drake


	rx.refresh();
	while(1){
		
		usleep(SLEEP);
		
		
		if (mode == TX){

			tx.refresh();
			printf("DONE\n");
			return 0;
		}

		if (mode == RX){

			rx.refresh();
		}


	
		printf("RX_BUFFER: %s\n", rx_buffer);
	}



	return 0;
}
