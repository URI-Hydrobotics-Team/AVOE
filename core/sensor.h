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
		char model[32];
		char vendor[32];
		char protocol[16];
		char type[32]; 
		int state = 0; //0 = uninit. , 1 = ready		

		char data[512];	
		/* positioning */

		vector_t offset; //position offset from center of vehicle in mm


	public:

		sensor_t();
		void init(const char *m, const char *v, const char *p, const char *t);
		char *getModel();
		char *getVendor();
		char *getProtocol();
		char *getType();
		char *read();
		void init();
		int getState();
		void write(char *input);
		void log(log_t *log);
		void print();

};

#endif
