/*

   URI Hydrobotics
   AVOE vehicle specification class (definition and implementation)


*/

#ifndef VEHICLE_H
#define VEHICLE_H

#include "config.h"

#include "sensor.h"
#include "motor.h"
#include "../lib/clock.h"
#include "../lib/lib.h"



class vehicle_t{


	private:

		char name[32];
		char version[16];
		char type[16];

		int control_mode = 0;

		int sensors_count;
		int motor_count;

		avoe_clock_t clocks[MAX_PER_VEHICLE_CLOCKS];

		char sensor_table[MAX_PER_VEHICLE_SENSORS][16];


	public:


		vehicle_t (const char *n, const char *v, const char *t);
		char *getName();
		char *getVersion();
		char *getType();
		void update(int m);
		void updateSensorTable(sensor_t sensors[], int count);
		void print();

};

#endif
