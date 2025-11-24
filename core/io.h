/*
	URI Hydrobotics
	AVOE core input and output functions



*/
#ifndef AVOE_COMM_T
#define AVOE_COMM_T

#include "sensor.h"
#include "motor.h"
#include "../lib/network.h"
#include "../lib/clock.h"

#define PER_FIELD_BUFFER_LEN 128


/*
	message format:
	$AVOE:<channel_name>:<type>:<data>$
	"$AVOE:<channel_name>:<type>:" is the header and can be up to 64 chars long

*/





class avoe_comm_transmitter{

	private:
		int port;
		char dest_ip[32];
		char channel_name[32];
		char type[32];
		short mode;
		/*
			-1	undefined
			0	generic string data
			1	sensor
			2	motor	
		*/
		//timing
		unsigned int tx_period; //in ms
		avoe_clock_t clock;

		//data fields
		size_t data_message_len;
		char *data_message; //pointer to character array
		
		size_t data_sensor_message_len;
		size_t data_motor_message_len;
		sensor_t *data_sensor;
		motor_t *data_motor;

		tx_socket *socket;
	public:
		avoe_comm_transmitter(const char *type_in, const char *channel, int port_in, const char *ip);

		void set_timer(unsigned int period); 
		void set_message(char *mptr, size_t len);
		void set_sensor(sensor_t *sensor);
		void set_motor(motor_t *motor);
		void tx();
		void refresh();

		//methods for clock stuff

};

class avoe_comm_reciever{

	private:
		int port;
		char channel_name[32];
		char type[32];
		char *data_message;
		size_t data_message_len;

	public:
		
		avoe_comm_reciever(const char *type, const char *channel, int port_in);
		void set_message(char *mptr, size_t len);
		void refresh();
		//methods for clock stuff
};


#endif
