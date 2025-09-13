/*

	URI Hydrobotics
	AVOE

*/


#define SOCKET_SLEEP 1000
#define SOCKET_TIMEOUT 10000



/* system */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* AVOE specific*/
#include "../../lib/globals.h"
#include "../../lib/lib.h"
#include "../../lib/clock.h"
#include "../../lib/network.h"

int main(int argc, char *argv[]){

	std::cout << "AVOE network example\n";


	if (argc < 3){
		std::cout << "Usage: ./tx_test <IP> <PORT>\n";
		return 0;
	}

	char port_str[8];
	strncpy(port_str, argv[2], 8);
	int port = std::stoi(port_str);


	tx_socket sock;
	sock.init(argv[1], port);


	avoe_clock_t timer;

	timer.reset();

	std::cout << "IP: " << argv[1] << " Port: " << port << '\n';
	while(1){

		if(timer.getElaspedTimeMS() > 1000){

			std::cout << "Transmitting Test Message\n";
			sock.transmit("AVOE network test");
			timer.reset();
		}

	}
	

	return 0;

}

