#include "../core/sensor.h"
#include "../core/motor.h"
#include "../core/io.h"
#include "../core/log.h"
#include "clock.h"



struct avoe_network_timer_t{

	avoe_clock_t *clock_object;

	avoe_comm_reciever **rx_object_table;
	avoe_comm_transmitter **tx_object_table;
	



};



struct avoe_mode_t{

	char name[128];
	


};




