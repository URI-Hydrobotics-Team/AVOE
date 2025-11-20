/*

   URI Hydrobotics
   AVOE core networking


*/

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h> //include fentanyl
#include <poll.h>


#ifndef AVOE_NETWORK_H
#define AVOE_NETWORK_H

#define NETWORK_BUFFER_SIZE 256

class tx_socket{

	private:
		char server[32];
		struct sockaddr_in my_addr, remote_addr;
		int port, fd, i, slen=sizeof(remote_addr);
		char tx_buffer[NETWORK_BUFFER_SIZE];

	public:
		void init(const char *host, int port);
		void transmit(const char *bufferIn);
		void closefd();


};



class rx_socket{
	private:
		struct sockaddr_in my_addr;	/* our address */
		struct sockaddr_in remote_addr;	/* remote address */
		socklen_t addrlen = sizeof(remote_addr);		/* length of addresses */
		int recvlen;			/* # bytes received */
		int fd;				/* the socket */
		char rx_buffer[NETWORK_BUFFER_SIZE];
	public:

		char* rec(int print);
		int probe();
		void init(int port);

};

#endif

