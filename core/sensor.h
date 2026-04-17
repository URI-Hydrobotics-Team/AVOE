/*

   URI Hydrdobotics
   AVOE sensor class

   Sensor drivers will interface with each sensor object. The vehicle class will hold sensor objects and provide an interface for accessing them.

*/


#ifndef SENSOR_H
#define SENSOR_H


#define TO_STRING_SIZE 32

#include "log.h"
#include "../lib/lib.h"


class sensor_t{

	private:
		char *model, *vendor, *protocol, *type;
		void *data;
		int state = 0; //0 = uninit. , 1 = ready		
		size_t field_count;
		enum data_type {
			UINT8,
			INT32,
			INT64,
			FLOAT,
			DOUBLE
		};
		//size_t data_type_digits; // maximum number of digits required for each data type, useful for logging

		/* positioning */

		vector_t offset; //position offset from center of vehicle in mm
		vector_t facing; //direction the sensor is pointed torwads if applicable

	public:

		sensor_t(size_t fields, enum type);
		~sensor_t();
		void init(const char *m, const char *v, const char *p, const char *t, vector_t off, vector_t face);
		void local_update(const char *t, const char* model);
		char *getModel();
		char *getVendor();
		char *getProtocol();
		char *getType();
		void *read(size_t field);
		void init();
		int getState();
		void write(const void input, size_t field);
		void log(log_t *log);
		void print();
		size_t getFieldCount();
		size_t getBufferSize(); //used for io.h
		void writeToBuffer(char *data_n); // used for io.h 
};

#endif
