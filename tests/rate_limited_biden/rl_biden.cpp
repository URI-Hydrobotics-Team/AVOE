#include "../../core/io.h"
#include "../../lib/lib.h"

#define PORT 9000
#define MAXIMUM_RX_BUFFER_SIZE 256
#define BUFFER_SIZE 128
#define SLEEP 1000 //us

#define TX_SLEEP 1000
#define TX_COUNT 3
#define TX 0
#define RX 1


/* 
	The purpose of this test is to see if the problem (same socket, same port bidirectional communication) is related to "oversaturating" the UDP buffer. So instead of continousily calling TX and pushing messages to the UDP socket, we only TX a small, finite, ammount of times (such as 3) and see how the receiver behaves. Unfornutely this, extremely simple test, still isn't reliable.

*/


int main(int argc, char** argv){
	if (argc != 6){
		printf("Improper amount of arguments: ./rl_biden_test <Destination IP> <TX Message> <TX Topic> <RX Topic> <tx or rx, depending on the punishment>\n");
		return 0;

	}

	char rx_buffer[BUFFER_SIZE];
	char tx_buffer[BUFFER_SIZE];

	memset(tx_buffer, 0, BUFFER_SIZE);
	memset(rx_buffer, 0, BUFFER_SIZE);
	
	
	char host_ip[16];
	memset(host_ip, 0, 16);
	strncpy(host_ip, argv[1], 16);
		
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

	while(1){
		
		usleep(SLEEP);
		
		
		if (mode == TX){
			for (int i = 0; i < TX_COUNT; i++){
				usleep(TX_SLEEP);
				tx.tx();
			}
			printf("DONE\n");
			return 0;
		}

		if (mode == RX){

			rx.refresh();
		}

		if (strlen(rx_buffer) > 0){
	
			printf("RX_BUFFER: %s\n", rx_buffer);
			return 0;

		}
	}



	return 0;
}
