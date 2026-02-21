/*
	network implementation


*/

#define SOCKET_SLEEP 1000
#define SOCKET_TIMEOUT 10000



#include <cstring>
#include <iostream>


#include "network.h"
#include "lib.h"



tx_socket::tx_socket(size_t buffer_size){
	tx_buffer_len = buffer_size;
	tx_buffer = new char[buffer_size];

}

tx_socket::tx_socket(){	
	tx_buffer_len = NETWORK_BUFFER_SIZE;
	tx_buffer = new char[NETWORK_BUFFER_SIZE];
}


tx_socket::~tx_socket(){	
	delete[] tx_buffer;	
}




void tx_socket::init(const char *host, int port){
	strncpy(server, host, 32);
	/* socket used to broadcast to others */
	if ((fd=socket(AF_INET, SOCK_DGRAM, 0)) == - 1){
		std::cout << "Failed to create TX socket\n";
	}else{
		std::cout << "Created TX socket\n";
	}


	/* bind it to all local addresses and pick any port number */

	memset((char *)&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr(server);
	my_addr.sin_port = htons(0);


	int reuse = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0){
		perror("setsockopt(SO_REUSEADDR) failed");
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0){
		perror("setsockopt(SO_REUSEPORT) failed");
	}


	if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
		std::cout << "Failed to bind TX socket\n";
	}else{
		std::cout << "Bound TX socket\n";
	}       


	memset((char *) &remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(port);
	if (inet_aton(server, &remote_addr.sin_addr) == 0) {
		std::cout << "inet_aton() failed\n";
		exit(1);
	}


}
void tx_socket::transmit(const char *bufferIn){
	
	initStr(tx_buffer, tx_buffer_len); 
	strncpy(tx_buffer, bufferIn, tx_buffer_len);
	
	if (sendto(fd, tx_buffer, tx_buffer_len, 0, (struct sockaddr *)&remote_addr, slen) == -1){
		std::cout << "error sendto\n";
	}
	

}

void tx_socket::closefd(){
	close(fd);
}



rx_socket::rx_socket(size_t buffer_size){
	rx_buffer_len = buffer_size;
	rx_buffer = new char[buffer_size];

}

rx_socket::rx_socket(){	
	rx_buffer_len = NETWORK_BUFFER_SIZE;
	rx_buffer = new char[NETWORK_BUFFER_SIZE];
}


rx_socket::~rx_socket(){	
	delete[] rx_buffer;	
}


char* rx_socket::rec(int print){
	/* first check fd avaliabilty */



	recvlen = recvfrom(fd,rx_buffer, rx_buffer_len, 0, (struct sockaddr *)&remote_addr, &addrlen);

	if (recvlen > 0) {
		/* 
		   define how the message is handled 
		   we would like to have a "message box" in the interface where raw message data is put
		 */
		rx_buffer[recvlen] = 0;
		if (print == 1){
			printf("received %d bytes\n", recvlen);
			printf("received message: \"%s\"\n",rx_buffer);
		}
		shutdown(fd, 2);
		usleep(SOCKET_SLEEP); //sleep for 100ms or so

	}

	return rx_buffer;

}

int rx_socket::probe(){

	/* poll a socket and check for data */
	struct pollfd fds[1];
	fds[0].fd = fd;
	fds[0].events = POLLIN;	
	int ret = poll(fds, 1, 10); //almost instant timeout

	return ret;
	/* 
	   Return Values:
	   failure		< 0
	   no data		= 0
	   data avaliable	> 0

	 */

}


void rx_socket::init(int port){
	/* Initialize a socket */
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0){
		std::cout << "Failed to create RX socket\n";
	}
	//set fd to non blocking
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);


	//set socket timeout
	struct timeval timeout={0,SOCKET_TIMEOUT};  //tv_sec, tv_usec
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,sizeof(struct timeval));



	memset((char *)&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	//my_addr.sin_addr.s_addr = inet_addr(host);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(port);
	int reuse = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0){
		perror("setsockopt(SO_REUSEPORT) failed");
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0){
		perror("setsockopt(SO_REUSEADDR) failed");
	}

	/* bind the socket */

	if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
		//std::cout << "bind to " << host ":" << port << "failed\n";
		std::cout << "Failed to bind RX socket\n";
	}else{
		std::cout << "Bound RX socket\n";
	}

}


