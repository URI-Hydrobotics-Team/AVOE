#include "imu.h"
#include <cstring>
#include <string>
#include <iostream>


/* getting */
vector_t sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(sensor_t *obj);
vector_t sensor_get_imu_ABSOLUTE_ORIENTAION_QUATERNION(sensor_t *obj);
vector_t sensor_get_imu_ANGULAR_VELOCITY(sensor_t *obj);
vector_t sensor_get_imu_GRAVITY(sensor_t *obj);
vector_t sensor_get_imu_LINEAR_ACCELERATION(sensor_t *obj);
vector_t sensor_get_imu_MAGNETIC_FIELD_STRENGTH(sensor_t *obj);
double sensor_get_imu_TEMPERATURE(sensor_t *obj);


/* setting */
void sensor_set_imu_ABSOULUTE_ORIENTATION_EULER(sensor_t *obj, double &x, double &y, double&z){

	//data field 0


	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 0, str.size());
	}else{
		std::cout << "string too big\n";
	}

}



void sensor_set_imu_ABSOLUTE_ORIENTAION_QUATERNION(sensor_t *obj, double &x, double &y, double &z){

	//data field 1
	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 1, str.size());
	}else{
		std::cout << "string too big\n";
	}
}
void sensor_set_imu_ANGULAR_VELOCITY(sensor_t *obj, double &x, double &y, double &z){

	//data field 3

	

	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 3, str.size());
	}else{
		std::cout << "string too big\n";
	}

}


void sensor_set_imu_GRAVITY(sensor_t *obj, double &x, double &y, double &z){


	//data field 4


	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 4, str.size());
	}else{
		std::cout << "string too big\n";
	}




}
void sensor_set_imu_LINEAR_ACCELERATION(sensor_t *obj, double &x, double &y, double &z){


	//data field 5


	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 5, str.size());
	}else{
		std::cout << "string too big\n";
	}



}
void sensor_set_imu_MAGNETIC_FIELD_STRENGTH(sensor_t *obj, double &x, double &y, double &z){


	//data field 6


	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 6, str.size());
	}else{
		std::cout << "string too big\n";
	}




}
void sensor_set_imu_TEMPERATURE(sensor_t *obj, double &temp){
	//data field 7
	std::string str;
	str += std::to_string(temp); str += ',';

	if (str.size() < 128){
		obj->write(str.c_str(), 7, str.size());
	}else{
		std::cout << "string too big\n";
	}


}

