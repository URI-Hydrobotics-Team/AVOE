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

#define INDEX_SIZE 64
#define PER_FIELD_BUFFER_LEN 128


/*
	message format:
	$AVOE:<channel_name>:<type>:<data>$
	"$AVOE:<channel_name>:<type>:" is the header and can be up to 64 chars long

*/




// communication transmitter, send out info to other devices
class avoe_comm_transmitter{

	private:
		int port;
		char dest_ip[32];
		char channel_name[32];
		char type[32];
		char index[INDEX_SIZE];
		//timing
		unsigned int tx_period; //in ms
		avoe_clock_t clock;

		//data fields
		// length of data message
		size_t data_message_len;
		char *data_message; //pointer to character array
		
		size_t data_sensor_message_len, data_motor_message_len;
		size_t sensor_count, motor_count, sensor_index, motor_index, vector_count, vector_index;
		sensor_t **sensor_table;
		motor_t **motor_table;
		vector_t **vector_table;

		tx_socket *socket;
	public:
		avoe_comm_transmitter(const char *type_in, const char *channel, int port_in, const char *ip);


		void update_index();
		void set_timer(unsigned int period); 
		void set_message(char *mptr, size_t len);
		void add_sensor(sensor_t *sensor);
		void add_motor(motor_t *motor);
		void add_vector(vector_t *vector);

		void tx();

		// continous transmit based on clock period
		void refresh();


};

class avoe_comm_reciever{

	private:
		int port;
		char channel_name[32];
		char type[32];

		char index[INDEX_SIZE];
		char *data_message;
		size_t data_message_len;
		rx_socket *socket;
	
		size_t sensor_count, vector_count, motor_count;
		size_t rx_buffer_len;
		sensor_t **sensor_table;
		motor_t **motor_table;
		vector_t **vector_table;

		avoe_clock_t clock;
		unsigned int rx_period; //in ms
	public:
		
		avoe_comm_reciever(const char *type, const char *channel, int port_in, size_t len);
		void set_message(char *mptr, size_t len);
		void refresh(); // continous recieve based on clock period
		void rx();
		void set_timer(unsigned int period); 
		void add_sensor(sensor_t *sensor);
		void add_motor(motor_t *motor);
		void add_vector(vector_t *vector);
		void update_index();

			



};

#endif
