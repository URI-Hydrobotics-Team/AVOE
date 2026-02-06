#include <iostream>
#include <cstring>

#include "vehicle.h"


vehicle_t::vehicle_t (const char *n, const char *v, const char *t){

	sensor_count = 0;
	motor_count = 0;
	sensor_table = nullptr;
	name = new char[32];
	version = new char[16];
	type = new char[16];

	strncpy(name, n, 32);
	strncpy(version, v, 16);
	strncpy(type, t, 16);

}

vehicle_t::~vehicle_t(){
	delete[] name;
	delete[] version;
	delete[] type;

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

void vehicle_t::addSensor(sensor_t *sensor){

	if (sensor_count == 0){
		sensor_table = new sensor_t*[1];
		sensor_table[0] = sensor;
		sensor_count++;	
	}else{
		sensor_t **temp = new sensor_t*[sensor_count + 1];
		for (size_t i = 0; i < sensor_count; i++){
			temp[i] = sensor_table[i];
		}
		temp[sensor_count] = sensor;
		sensor_count++;

		delete[] sensor_table;
		sensor_table = temp;
	


	}

	std::cout << "sensor " << sensor->getModel() << " added\n"; 

}
void vehicle_t::addMotor(motor_t *motor){

	if (motor_count == 0){
		motor_table = new motor_t*[1];
		motor_table[0] = motor;
		motor_count++;	
	}else{
		motor_t **temp = new motor_t*[motor_count + 1];
		for (size_t i = 0; i < motor_count; i++){
			temp[i] = motor_table[i];
		}
		temp[motor_count] = motor;
		motor_count++;

		delete[] motor_table;
		motor_table = temp;
	

	}

	std::cout << "motor " << motor->getModel() << " added\n"; 

}

void vehicle_t::print(){
	//print vehicle information for debugging purposes
	std::cout << "vehicle_t print:\n";
	std::cout << "\tPrimary Information:\n";
	std::cout << "\t\tNAME: " << name << '\n';
	std::cout << "\t\tVERSION: " << version << '\n';
	std::cout << "\t\tTYPE: " << type << '\n';

	std::cout << "\t" << sensor_count << " sensor(s):\n";
	for (size_t i = 0; i < sensor_count; i++){
		sensor_table[i]->print();
	}
	std::cout << "\t" << motor_count << " motor(s):\n";
	for (size_t i = 0; i < motor_count; i++){
		motor_table[i]->print();
	}
}

