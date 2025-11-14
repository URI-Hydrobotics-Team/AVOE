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
		int entries = 0;
		std::string working_file = "";
		std::string time_str;
		//fstream file; //declare a file
		FILE *filePtr;
		time_t rawtime;
		struct tm * timeinfo;

	public:
		std::string makeFileName(std::string input);
		void init();
		void setTimeStr(std::string input);
		void log(std::string input);
		std::string getName();
		void endLog();
};


#endif
