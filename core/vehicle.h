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

		char *name; //32
		char *version; //16
		char *type; //16

		int control_mode = 0;

		size_t sensor_count, motor_count;

		avoe_clock_t clocks[MAX_PER_VEHICLE_CLOCKS];
		sensor_t **sensor_table;
		motor_t **motor_table;

	public:
		vehicle_t (const char *n, const char *v, const char *t);
		~vehicle_t();
		char *getName();
		char *getVersion();
		char *getType();
		void update(int m);
		void addSensor(sensor_t *sensor);
		void addMotor(motor_t *motor);
		void print();

};

#endif
