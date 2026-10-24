/*
   AVOE logging suite

*/


#include <cstring>
#include <string>
#include <time.h>
#include <cstdio>

#ifndef LOG_H
#define LOG_H

/// @brief Log class that logs to a file with a timestamp
class log_t{
	private:
		/// @brief Number of entries in the log file
		size_t entries;
		char working_file[64];
		FILE *fptr;
		time_t rawtime;
		struct tm * timeinfo;
		/// @brief writes the header the first time the thing gets ran
		bool firstRun = true;

	public:
		/// @deprecated 
		char* makeFileName(const char *);


		/// @brief Inits log and sets it to the path specified
		/// @details Generates a file by the following steps
		/// 1. Resets @ref entries count to 0
		/// 2. Gets the time formats it to timestamp
		/// 3. sets up directory dictated by #LOG_DIR
		/// 4. if a directory is not found then creates it
		void init();

		/// @brief Writes Timestamp and Logs output
		/// @param data Data to be logged in the timestamp
		
		void log(const char *data);
		/// @brief  
		/// @return  @ref working_file
		char* getName();
		void endLog();
};


#endif
