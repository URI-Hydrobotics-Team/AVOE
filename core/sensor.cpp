#include <cstring>
#include <iostream>

#include "sensor.h"

sensor_t::sensor_t(){

}

void sensor_t::init(const char *m, const char *v, const char *p, const char *t){

	strncpy(model, m, 32);
	strncpy(vendor, v, 32);
	strncpy(protocol, p, 16);
	strncpy(type, t, 16);

}


char *sensor_t::getModel(){
	return model;
}

char *sensor_t::getVendor(){
	return vendor;
}

char *sensor_t::getProtocol(){
	return protocol;
}

char *sensor_t::getType(){
	return type;
}

char *sensor_t::read(){
	return data;

}

void sensor_t::init(){

	state = 0;
	//tells sensors.h that intilization is ready

}

int sensor_t::getState(){

	return state;

}


void sensor_t::write(char *input){
	strncpy(data, input, 512);

}

/*
   void log(log_t *log){
//	automatically log all values to a log_t 
std::string entry = "";
for (int i = 0; i < MAX_SENSOR_ENTRIES; i++){
entry += variable_names[i];
entry += ' ';
entry += values[i];
log->log(entry.c_str());
entry = "";

}

}

void print(){

std::cout << "\t\tMODEL: " << model << '\n';
std::cout << "\t\tVENDOR: " << vendor << '\n';
std::cout << "\t\tPROTOCOL: " << protocol << '\n';


}
*/



