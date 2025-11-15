#include <cstring>
#include <iostream>

#include "sensor.h"

sensor_t::sensor_t(size_t fields){
	field_count = fields;
	model = new char[32];
	vendor = new char[32];
	protocol = new char[16];
	type = new char[32];

	data = new char*[field_count];

	for (size_t i = 0; i < field_count; i++){
		data[i] = new char[128];

	}

}

sensor_t::~sensor_t(){
	delete[] model;
	delete[] vendor;
	delete[] protocol;
	delete[] type;

	for (size_t i = 0; i < field_count; i++){
		delete[] data[i];

	}

	delete[] data;

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

char *sensor_t::read(size_t field){
	return data[field];

}

void sensor_t::init(){

	state = 0;
	//tells sensors.h that intilization is ready

}

int sensor_t::getState(){

	return state;

}


void sensor_t::write(const char *input, size_t field, size_t n){
	strncpy(data[field], input, n);
	//NOTE n should be 128 or less
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
 */
void sensor_t::print(){

	std::cout << "START SENSOR_T PRINT\n";
	std::cout << "METADATA:\n";
	std::cout << "\tMODEL: " << model << '\n';
	std::cout << "\tVENDOR: " << vendor << '\n';
	std::cout << "\tPROTOCOL: " << protocol << '\n';
	std::cout << "DATA:\n";
	for (size_t i = 0; i < field_count; i++){
		std::cout << "\tFIELD " << i << ": " << data[i] << '\n';

	}
	std::cout << "END SENSOR_T PRINT\n";

}



