#include "imu.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>


/* getting */
vector_t sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(sensor_t *obj){
	//data field 0

	std::string str = obj->read(0);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_ABSOLUTE_ORIENTAION_QUATERNION(sensor_t *obj){
	//data field 1

	std::string str = obj->read(1);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_VELOCITY(sensor_t *obj){
	//data field 2

	std::string str = obj->read(2);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_ANGULAR_VELOCITY(sensor_t *obj){
	//data field 3

	std::string str = obj->read(3);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_GRAVITY(sensor_t *obj){
	//data field 4

	std::string str = obj->read(4);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_LINEAR_ACCELERATION(sensor_t *obj){
	//data field 5

	std::string str = obj->read(5);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
vector_t sensor_get_imu_MAGNETIC_FIELD_STRENGTH(sensor_t *obj){
	//data field 6

	std::string str = obj->read(6);
	double x,y,z;
	std::vector<double> vals = {x,y,z};
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			++valsIndex;
			continue;
		}else{
			vals[valsIndex] += val;
		}
	}
	return vector_t(vals[0],vals[1],vals[2]);
}
double sensor_get_imu_TEMPERATURE(sensor_t *obj){
	//data field 7

	std::string str = obj->read(7);
	double temp;
	size_t valsIndex = 0;

	for(size_t i = 0; i < str.size(); i++){
		double val = str[i];
		if(val == ','){
			break;
		}else{
			temp += val;
		}
	}
	return temp;
}


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

void sensor_set_imu_VELOCITY(sensor_t *obj, double &x, double &y, double &z){

	//data field 2
	std::string str;
	str += std::to_string(x); str += ',';
	str += std::to_string(z); str += ',';
	str += std::to_string(y); str += ';';

	if (str.size() < 128){
		obj->write(str.c_str(), 2, str.size());
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

