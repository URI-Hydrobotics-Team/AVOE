#include "controller.h"
#include <string>



tardigrade_controller_t::tardigrade_controller_t(){
	name = nullptr;
	vehicle = nullptr;
	motorTable = nullptr;
}

tardigrade_controller_t::~tardigrade_controller_t(){
    delete[] name;
    delete[] vehicle;
}

void tardigrade_controller_t::init(const char *n, vehicle_t *vehicle_in){
    name = new char[NAME_LEN]; //default is 32
    strncpy(name, n, NAME_LEN);
    vehicle = vehicle_in;
    motorTable = vehicle->getMotorTable();
}

void tardigrade_controller_t::send_translation_vector(vector_t thrust_vector){ //we assume pivot and orgin are about the center of the robot
    double x = thrust_vector.x;
    double y = thrust_vector.y;
    double z = thrust_vector.z;

	
    for(size_t i = 0; i < 6; ++i){
        //Sets motor values after calculating the x,y,z total
        double total = (x * translation_thrust_table[i][0]) + (y * translation_thrust_table[i][1]) + (z * translation_thrust_table[i][2]);
        // Gets motor from vehicle objects motor table and writes the intended value to it 
        // (only works if motors in correct order of thrust_table)
        std::string str = std::to_string(total);
        char temp[str.length()];

        std::strncpy(temp, std::to_string(total).c_str(), sizeof(temp));
        motorTable[i]->write(temp,0,sizeof(temp));
    }
}
void tardigrade_controller_t::send_lateral_vector(vector_t thrust_vector){
    //Rotational movement vectors
    double rx = thrust_vector.x;
    double ry = thrust_vector.y;
    double rz = thrust_vector.z;


    for(size_t i = 0; i < 6; ++i){
        //Sets motor values after calculating the rx,ry,rz total
        double total = (rx * lateral_thrust_table[i][0]) + (ry * lateral_thrust_table[i][1]) + (rz * lateral_thrust_table[i][2]);
        // Gets motor from vehicle objects motor table and writes the intended value to it 
        // (only works if motors in correct order of thrust_table)
        std::string str = std::to_string(total);
        char temp[str.length()];

        std::strncpy(temp, std::to_string(total).c_str(), sizeof(temp));
        motorTable[i]->write(temp,0,sizeof(temp));
    }
}
