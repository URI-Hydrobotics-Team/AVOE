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

		struct timespec timer;
		clock_t traditional_timer;

	public:

		unsigned long getElaspedTimeMS();
		void reset();
		char* getTimeStr();
};
#endif
