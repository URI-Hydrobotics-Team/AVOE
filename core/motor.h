/*

   URI Hydrdobotics
   AVOE motor class

   motor objects work very similary to sensor objects
*/

#ifndef MOTOR_H
#define MOTOR_H

#include "../lib/lib.h"

class motor_t{

	private:
		char name[32];
		char vendor[32];
		char protocol[16];
		int type; 


		vector_t position;
		vector_t direction;		
		float *force_func;

		char data[512];			

	public:

		motor_t();
		void init(char *n, char *v, char *p);
		char *getName();
		char *getVendor();
		char *getProtocol();
		char *read();
		void write(const char *input);


};

#endif
