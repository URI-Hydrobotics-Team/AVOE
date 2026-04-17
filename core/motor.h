/*

   URI Hydrdobotics
   AVOE motor class

   motor objects work very similary to sensor objects
*/

#ifndef MOTOR_H
#define MOTOR_H
#define TO_STRING_SIZE 32


#include "../lib/lib.h"
#include "log.h"

class motor_t{

	private:
		char *label;
		char *model;
		char *vendor;
		char *protocol;
		char *type; 
		void *data;
		size_t field_count; //generally one
		enum data_type {
			UINT8,
			INT32,
			INT64,
			FLOAT,
			DOUBLE
		};

		vector_t position;
		vector_t direction;		
		//float *force_func;
		//force direction



	public:

		motor_t(size_t fields);
		~motor_t();
		void init(const char *l, const char *m, const char *v, const char *p, const char *t, vector_t pos, vector_t dir);
		char *getModel();
		char *getLabel();
		char *getVendor();
		char *getProtocol();
		char *getType();
		void *read(size_t field);
		void write(const char *input, size_t field, size_t n);
		void log(log_t *log);
		void print();
		size_t getFieldCount();
		size_t getBufferSize();
		void writeToBuffer(char *buffer);
};

#endif
