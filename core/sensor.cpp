#include <cstring>
#include <iostream>
#include <cstdint>


#include "sensor.h"

sensor_t::sensor_t(size_t fields, enum type){
	field_count = fields;
	model = new char[32];
	vendor = new char[32];
	protocol = new char[16];
	type = new char[32];

	switch (type){
		case UINT8:
			data = new uint8_t*[field_count];
			break;
		case INT32:
			data = new int32_t*[field_count];				
			break;
		case INT64:
			data = new int64_t*[field_count];
			break;
		case FLOAT:
			data = new float*[field_count];
			break;
	}
}

sensor_t::~sensor_t(){
	delete[] model;
	delete[] vendor;
	delete[] protocol;
	delete[] type;
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

void *sensor_t::read(size_t field){
	return data[field];

}

void sensor_t::init(){

	state = 0;
	//tells sensors.h that intilization is ready

}

int sensor_t::getState(){

	return state;

}


void sensor_t::write(const void input, size_t field){

	data[i] = input;
}


void sensor_t::log(log_t *log){
	char field_to_string[TO_STRING_SIZE];
	intiStr(field_to_string, TO_STRING_SIZE);

	char field_count_str[4];
	intiStr(field_count_str, 4);
	sprintf(field_count_str, "%d", field_count);


	//automatically log all values to a log_t object
	char *data_n = new char[64 + field_count * TO_STRING_SIZE];
	initStr(data_n, 64 + field_count * TO_STRING_SIZE);
	appendStr(data_n, type, 0);
	appendStr(data_n, ":", strlen(data_n));
	appendStr(data_n, model, strlen(data_n));
	appendStr(data_n, " ", strlen(data_n));
	
	appendStr(data_n, field_count_str, strlen(data_n));	
	appendStr(data_n, " fields: ", strlen(data_n));
	for (size_t i = 0; i < field_count; i++){

		switch (type){
		case UINT8:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case INT32:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case INT64:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case FLOAT:
			sprintf(field_to_string, "%.3f", data[i]);
			break;
	}

		appendStr(data_n, " ", strlen(data_n));
	}

	log->log(data_n);	
	delete[] data_n;

}



size_t sensor_t::getBufferSize(){

	return 64 + field_count * TO_STRING_SIZE;

}

void sensor_t::writeToBuffer(char *data_n){
	char field_to_string[TO_STRING_SIZE];
	intiStr(field_to_string, TO_STRING_SIZE);

	char field_count_str[4];
	intiStr(field_count_str, 4);
	sprintf(field_count_str, "%d", field_count);


	initStr(data_n, 64 + field_count * TO_STRING_SIZE);
	appendStr(data_n, type, 0);
	appendStr(data_n, ":", strlen(data_n));
	appendStr(data_n, model, strlen(data_n));
	appendStr(data_n, " ", strlen(data_n));
	
	appendStr(data_n, field_count_str, strlen(data_n));	
	appendStr(data_n, " fields: ", strlen(data_n));
	for (size_t i = 0; i < field_count; i++){

		switch (type){
		case UINT8:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case INT32:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case INT64:
			sprintf(field_to_string, "%d", data[i]);
			break;
		case FLOAT:
			sprintf(field_to_string, "%.3f", data[i]);
			break;
	}

		appendStr(data_n, " ", strlen(data_n));
	}


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


void sensor_t::local_update(const char *t, const char* m){

	strncpy(type, t, 32);
	strncpy(model, m, 32);

}


