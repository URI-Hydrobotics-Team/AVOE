#include <cstring>

#include "motor.h"



void motor_t::init(char *n, char *v, char *p){

	strncpy(name, n, 32);
	strncpy(vendor, v, 32);
	strncpy(protocol, p, 16);

}


char *motor_t::getName(){
	return name;
}

char *motor_t::getVendor(){
	return vendor;
}

char *motor_t::getProtocol(){
	return protocol;
}


char *motor_t::read(){

	return data;
}

void motor_t::write(const char *input){
	strncpy(data, input, 512);


}

