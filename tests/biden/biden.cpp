#include "../../core/io.h"
#include "../../lib/lib.h"

#define PORT 9000
#define MAXIMUM_RX_BUFFER_SIZE 256
#define BUFFER_SIZE 128
#define SLEEP 1000 //us



#define TX 0
#define RX 1


/* this program seemingly operates similar to the original io_test (use avoe_comm* to setup a bidirectional communication link and rx/tx on both sides, filling the other sides buffer).

	HOW IT WORKS
	
	each process initializes the same way (two avoe_comm_* rx and tx objects per)
	one process is run with explicit instruction to initiate communication
	the other is always listening 
	as soon as the listening process receives instruction, it stops listening and transmits a response
	everytime the initater transmits, it stops and waits for some response before txing again
	once the response is heard by the transmitter, the roles reverse 

*/


/* 
	VERDICT: it still doesn't really work becuase revfrom returns one packet from the UDP queue at a time

*/

int main(int argc, char** argv){
	if (argc != 6){
		printf("Improper amount of arguments: ./biden <Destination IP> <TX Message> <TX Topic> <RX Topic> <tx or rx, depending on the punishment>\n");
		return 0;

	}

	char rx_buffer[BUFFER_SIZE];
	char tx_buffer[BUFFER_SIZE];
	memset(rx_buffer, 0, BUFFER_SIZE);
	memset(tx_buffer, 0, BUFFER_SIZE);
	
	
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
	//drake


	//rx.refresh();
	while(1){
		
		usleep(SLEEP);
		
		
		if (mode == TX){
			

			tx.set_timer(1);
			rx.set_timer(10); //lets try 10ms
			
			tx.refresh();
			//usleep(TX_SLEEP);
			rx.refresh_probe();

			if (strlen(rx_buffer) > 0){

				printf("(TX MODE) RX_BUFFER: %s\n", rx_buffer);
				memset(rx_buffer, 0, BUFFER_SIZE);
				//we recieved a message
				mode = RX;
			}
		
		}

		if (mode == RX){

		
			rx.set_timer(1);
			tx.set_timer(10); //lets try 10ms


			rx.refresh_probe();
			tx.refresh();
			if (strlen(rx_buffer) > 0){

				printf("(RX MODE) RX_BUFFER: %s\n", rx_buffer);
				memset(rx_buffer, 0, BUFFER_SIZE);
				//we recieved a message
				mode = TX;
			}
		}

	}



	return 0;
}
