#include "clock.h"
#include <ctime>
#include <cstring>


unsigned long avoe_clock_t::getElaspedTimeMS(){

	struct timespec temp;
	clock_gettime(CLOCK_MONOTONIC, &temp);
	unsigned long before = (unsigned long) timer.tv_sec * 1000ULL + (unsigned long) timer.tv_nsec / 1000000ULL;
	unsigned long after = (unsigned long) temp.tv_sec * 1000ULL + (unsigned long) temp.tv_nsec / 1000000ULL;

	return after - before;

}


void avoe_clock_t::reset(){

	clock_gettime(CLOCK_MONOTONIC, &timer);

}

char* avoe_clock_t::getTimeStr(){

	//you cant do this
	char *time_str = ctime(&traditional_timer);

	time_str[strlen(time_str) - 1] = 0;
	return time_str;

}

