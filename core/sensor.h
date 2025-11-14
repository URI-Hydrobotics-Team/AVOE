/*

   URI Hydrdobotics
   AVOE sensor class

   Sensor drivers will interface with each sensor object. The vehicle class will hold sensor objects and provide an interface for accessing them.

*/


#ifndef SENSOR_H
#define SENSOR_H

#include "log.h"
#include "../lib/lib.h"


class sensor_t{

	private:
		char *model, *vendor, *protocol, *type, **data;
		int state = 0; //0 = uninit. , 1 = ready		
		size_t field_count;
		/* positioning */

		vector_t offset; //position offset from center of vehicle in mm


	public:

		sensor_t(size_t fields);
		~sensor_t();
		void init(const char *m, const char *v, const char *p, const char *t);
		char *getModel();
		char *getVendor();
		char *getProtocol();
		char *getType();
		char *read(size_t field);
		void init();
		int getState();
		void write(const char *input, size_t field, size_t n);
		void log(log_t *log);
		void print();

};

#endif
