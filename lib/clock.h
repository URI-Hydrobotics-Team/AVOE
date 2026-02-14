/*

	URI Hydrobotics
	AVOE clock class
	
	Clocks are important for timing certain events. Clocks should be associtaed with vehicle_t


*/

#include <time.h>

#ifndef AVOE_CLOCK_H
#define AVOE_CLOCK_H

class avoe_clock_t{


	private:

		clock_t timer;

	public:

		unsigned long getElaspedTimeMS();
		void reset();
		char* getTimeStr();
};
#endif
