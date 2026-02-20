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



void sensor_t::init(const char *m, const char *v, const char *p, const char *t, vector_t off, vector_t face){

	strncpy(model, m, 32);
	strncpy(vendor, v, 32);
	strncpy(protocol, p, 16);
	strncpy(type, t, 16);
	offset = off;
	facing = face;
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
	initStr(data[field], 128);
	strncpy(data[field], input, n);
	//NOTE n should be 128 or less
}


void sensor_t::log(log_t *log){
	//automatically log all values to a log_t object
	char *data_n = new char[64 + field_count * 130]; //130 just to add some extra room for other chars
	initStr(data_n, 64 + field_count *130);
	appendStr(data_n, type, 0);
	appendStr(data_n, ":", strlen(data_n));
	appendStr(data_n, model, strlen(data_n));
	appendStr(data_n, " ", strlen(data_n));
	
	appendStr(data_n, std::to_string(field_count).c_str(), strlen(data_n));	
	appendStr(data_n, " fields: ", strlen(data_n));
	for (size_t i = 0; i < field_count; i++){
		appendStr(data_n, data[i], strlen(data_n));
		appendStr(data_n, " ", strlen(data_n));
	}

	log->log(data_n);	
	delete[] data_n;

}
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


size_t sensor_t::getFieldCount(){
	return field_count;
}


