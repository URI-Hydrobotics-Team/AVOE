#include <cstring>
#include <iostream>

#include "motor.h"


motor_t::motor_t(size_t fields){
	field_count = fields;
	model = new char[32];
	vendor = new char[32];
	label = new char[32];
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

motor_t::~motor_t(){
	delete[] model;
	delete[] vendor;
	delete[] protocol;
	delete[] type;
	delete[] label;
	delete[] data;

}


void motor_t::init(const char *l, const char *m, const char *v, const char *p, const char *t, vector_t pos, vector_t dir){

	strncpy(label, l, 32);
	strncpy(model, m, 32);
	strncpy(vendor, v, 32);
	strncpy(protocol, p, 16);
	strncpy(type, t, 32);
	
	position = pos;
	direction = dir;

}

char *motor_t::getLabel(){
	return label;
}

char *motor_t::getModel(){
	return model;
}

char *motor_t::getVendor(){
	return vendor;
}

char *motor_t::getProtocol(){
	return protocol;
}

char *motor_t::getType(){
	return type;
}

void *motor_t::read(size_t field){
	return data[field];

}




void motor_t::write(const char *input, size_t field, size_t n){
	initStr(data[field], 128);
	strncpy(data[field], input, n);
	//NOTE n should be 128 or less
}

void motor_t::writeToBuffer(char *data_n){

	char field_to_string[TO_STRING_SIZE];
	intiStr(field_to_string, TO_STRING_SIZE);

	char field_count_str[4];
	intiStr(field_count_str, 4);
	sprintf(field_count_str, "%d", field_count);


	//automatically log all values to a log_t object
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


size_t motor_t::getBufferSize(){
 
	return 64 + field_count * TO_STRING_SIZE;
 
}



void motor_t::log(log_t *log){

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



void motor_t::print(){

	std::cout << "START MOTOR_T PRINT\n";
	std::cout << "METADATA:\n";
	std::cout << "\tLABEL: " << label << '\n';
	std::cout << "\tMODEL: " << model << '\n';
	std::cout << "\tVENDOR: " << vendor << '\n';
	std::cout << "\tPROTOCOL: " << protocol << '\n';
	std::cout << "\tTYPE: " << type << '\n';
	std::cout << "DATA:\n";
	for (size_t i = 0; i < field_count; i++){
		std::cout << "\tFIELD " << i << ": " << data[i] << '\n';

	}
	std::cout << "END MOTOR_T PRINT\n";

}


size_t motor_t::getFieldCount(){
	return field_count;
}



