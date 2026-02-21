#include "../../core/sensor.h"
/*

	AVOE frontend sensor handling functions
	once implemented for cli, this should be moved to /frontends/lib/
*/

#ifndef AVOE_IO_SENSOR_H
#define AVOE_IO_SENSOR_H
int map_sensor_string(sensor_t *sensor, const char *message, size_t message_len); //return 1 on success, return -1 on fail

#endif
