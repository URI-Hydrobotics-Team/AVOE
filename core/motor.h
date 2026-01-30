/*

   URI Hydrdobotics
   AVOE motor class

   motor objects work very similary to sensor objects
*/

#ifndef MOTOR_H
#define MOTOR_H

#include "../lib/lib.h"
#include "log.h"

class motor_t{

	private:
		char *label;
		char *model;
		char *vendor;
		char *protocol;
		char *type; 
		char **data;
		size_t field_count; //generally one

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
		char *read(size_t field);
		void write(const char *input, size_t field, size_t n);
		void log(log_t *log);
		void print();
		size_t getFieldCount();
};

#endif
