#include "clock.h"
#include <ctime>
#include <cstring>


unsigned long avoe_clock_t::getElaspedTimeMS(){
	clock_t t = clock() - timer;
	//return (t * 100000 / CLOCKS_PER_SEC);

	return (t * 1000 / CLOCKS_PER_SEC);

}


void avoe_clock_t::reset(){

	timer = clock();
}

char* avoe_clock_t::getTimeStr(){

	char *time_str = ctime(&timer);

	time_str[strlen(time_str) - 1] = 0;
	return time_str;

}

