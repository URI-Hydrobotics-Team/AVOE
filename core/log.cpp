#include <iostream>
#include <cstring>
#include <cstdio>
#include "log.h"
#include "config.h"
#include "../lib/lib.h"


/*
std::string log_t::makeFileName(std::string input){
	// replace spaces with '_'
	std::string temp = "";
	for (int i = 0; i < (input.length() - 1); i++){
		if ((input[i] != ' ') && (input[i] != ':')){
			temp += input[i];
		}else {
			temp += '_';
		}

	}

	//temp[temp.length() - 1] = '_';
	return temp;
}
*/




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
	appendStr(working_file, new_time_str, strlen(working_file));
	appendStr(working_file, ".txt", strlen(working_file));


	// make a file
	fptr = fopen(working_file, "w");
	// write header
	fputs("AVOE LOG FILE: ", fptr);
	fputs(new_time_str, fptr);
	fputs("\n", fptr);
	std::cout << "header written for \"" << working_file << "\"\n";
	fclose(fptr);
}


void log_t::log(const char *data){
	// write timestamp and log input 
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



void log_t::endLog(){

	fclose(fptr);
}

