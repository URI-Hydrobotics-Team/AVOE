#include <iostream>
#include <cstring>

#include "vehicle.h"


vehicle_t::vehicle_t (const char *n, const char *v, const char *t){

	strncpy(name, n, 32);
	strncpy(version, v, 16);
	strncpy(type, t, 16);

}


char *vehicle_t::getName(){
	return name;
}

char *vehicle_t::getVersion(){
	return version;
}

char *vehicle_t::getType(){

	return type;
}

void vehicle_t::update(int m){
	//update values and clocks
	control_mode = m;

}

void vehicle_t::updateSensorTable(sensor_t sensors[], int count){
	sensors_count = count;
	for (int i = 0; i < sensors_count; i++){
		initStr(sensor_table[i], 16);
		strncpy(sensor_table[i], sensors[i].getType(), 16);

	}
}


void vehicle_t::print(){
	//print vehicle information for debugging purposes
	std::cout << "vehicle_t print:\n";
	std::cout << "\tPrimary Information:\n";
	std::cout << "\t\tNAME: " << name << '\n';
	std::cout << "\t\tVERSION: " << version << '\n';
	std::cout << "\t\tTYPE: " << type << '\n';

	std::cout << "\tSensor List:\n";
	for (int i = 0; i < sensors_count; i++){
		std::cout << "\t\t" << sensor_table[i] << '\n';
	}
}

