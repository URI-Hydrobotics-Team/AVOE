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
#include "../../lib/network.h"






int main(int argc, char *argv[]){

	std::cout << "AVOE Network RX example\n";

	if (argc < 2){
		std::cout << "Usage: ./rx_test <PORT>\n";
		return 0;
	}



	char port_str[8];
	strncpy(port_str, argv[1], 8);
	int port = std::stoi(port_str);

	rx_socket sock;
	sock.init(port);	

	while(1){
		usleep(1000);
		sock.rec(1);
		

	}





	return 0;

}

