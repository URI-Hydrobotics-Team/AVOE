/*
   AVOE logging suite

*/

#include <cstring>
#include <string>
#include <time.h>
#include <cstdio>

#ifndef LOG_H
#define LOG_H

class log_t{
	private:
		size_t entries;
		char working_file[64];
		FILE *fptr;
		time_t rawtime;
		struct tm * timeinfo;

	public:
		char* makeFileName(const char *);
		void init();
		void log(const char *data);
		char* getName();
		void endLog();
};


#endif
