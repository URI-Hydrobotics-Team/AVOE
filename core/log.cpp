#include <iostream>
#include <cstring>
#include <cstdio>
#include "log.h"
#include "config.h"
#include "../lib/lib.h"
#include "dirent.h"

void log_t::init(){
	entries = 0;

	/* generate filename */
	//get current time for filename
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char new_time_str[32]; 
	asctime_r(timeinfo, new_time_str);
		
	//remove \n from new_time_str
	size_t temp_len = strlen(new_time_str);
	new_time_str[temp_len - 1] = 0;
	
	
	
	initStr(working_file, 64);
	strncpy(working_file, LOG_DIR, 64);
	
	appendStr(working_file, "/", strlen(working_file));
	DIR* dir = opendir(working_file);
	if(!dir)
	{
		char mkdirtoken[7] = "mkdir ";
		strcat(mkdirtoken,working_file);
		printf("%s",mkdirtoken);
		int newfdr = system(mkdirtoken);
	}


}

void log_t::log(const char *data){
	// write timestamp and log input 

/**
 * I moved this here instead of the init function 
 * it writes the header file here it should only once;
 */
	if (firstRun == true)
	{	char new_time_str[32]; 
		asctime_r(timeinfo, new_time_str);
		fptr = fopen(working_file,"w+");
		appendStr(working_file, new_time_str, strlen(working_file));
		appendStr(working_file, ".txt", strlen(working_file));
		// make a file
		fptr = fopen(working_file, "w+");
		if (fptr==NULL)
		{
			perror("ERROR OPENING FILE");
		}
		fputs("AVOE LOG FILE: ", fptr);
		fputs(new_time_str, fptr);
		fputs("\n", fptr);
		std::cout << "header written for \"" << working_file << "\"\n";
		firstRun = false;
		fclose(fptr);
	}
	

	fptr = fopen(working_file, "a");
	entries++;
	//get time
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char new_time_str[32]; 
	asctime_r(timeinfo, new_time_str);

	char entry_str[8];
	sprintf(entry_str, "%d", entries);

	fputs(entry_str, fptr); //write entry number
	fputs(" ", fptr); //space
	fputs(new_time_str, fptr); // write time
	fputs(data, fptr); //write log
	fputs("\n", fptr); // new line char

	fclose(fptr);



}

char* log_t::getName(){
	return working_file;
}


