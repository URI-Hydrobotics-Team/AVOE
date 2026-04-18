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
#define INDEX_SIZE 64

/*
	message format:
	$AVOE:<channel_name>:<index>:<data>$



*/




// communication transmitter, send out info to other devices
class avoe_comm_transmitter{

	private:
		int port;
		char dest_ip[32];
		char channel_name[32];
		char index[INDEX_SIZE];
		short mode;
		/*
			-1	undefined
			0	generic string data
			1	sensor
			2	motor
			3	mixed
			4	vector	
		*/

		//timing
		unsigned int tx_period; //in ms
		avoe_clock_t clock;

		

		
		size_t sensor_count, motor_count, sensor_index, motor_index, vector_count, vector_index;
		size_t data_message_len; //length of string, 0 if no string
		char *data_message;
	
		sensor_t **sensor_table;
		motor_t **motor_table;
		vector_t **vector_table;
		tx_socket *socket;
	public:
		avoe_comm_transmitter(const char *channel, int port_in, const char *ip);
		void update_index();
		void set_timer(unsigned int period); 
		void set_message(char *mptr, size_t len);
		void add_sensor(sensor_t *sensor);
		void add_motor(motor_t *motor);
		void add_vector(vector_t *vector);
		
		// asynchronous transmit
		void tx();

		// continous transmit based on clock period
		void refresh();


};

class avoe_comm_reciever{

	private:
		int port;
		char channel_name[32];
		char type[32];
		char *data_message;
		size_t data_message_len;
		rx_socket *socket;
		avoe_clock_t clock;

		unsigned int rx_period; //in ms
	public:
		
		avoe_comm_reciever(const char *type, const char *channel, int port_in);
		void set_message(char *mptr, size_t len);
		void refresh(); // continous recieve based on clock period
		void rx();
		void rx_fields(char* sensor, char* motor, char* vector, char* msg); 
		void set_timer(unsigned int period); 
};



int avoe_comm_reciever_decode_message(char *destination, const char *message, size_t n);



#endif
