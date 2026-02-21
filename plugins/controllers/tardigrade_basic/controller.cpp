#include "controller.h"
#include <string>


tardigrade_basic_controller_t::tardigrade_basic_controller_t(const char *n, vehicle_t *vehicle_in){
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    vehicle = vehicle_in;
    motorTable = vehicle->getMotorTable();
}
tardigrade_basic_controller_t::~tardigrade_basic_controller_t(){
    delete[] name;
    delete[] vehicle;
}
void tardigrade_basic_controller_t::send_vector(vector_t thrust_vector){ //we assume pivot and orgin are about the center of the robot
    double x = thrust_vector.x;
    double y = thrust_vector.y;
    double z = thrust_vector.z;


    for(size_t i = 0; i < 6; ++i){
        //Sets motor values after calculating the x,y,z total
        double total = (x * thrust_table[i][0]) + (y * thrust_table[i][1]) + (z * thrust_table[i][2]);
        /*Gets motor from vehicle objects motor table and writes the intended value to it 
        (only works if motors in correct order of thrust_table)*/
        std::string str = std::to_string(total);
        char temp[str.length()];

        std::strncpy(temp, std::to_string(total).c_str(), sizeof(temp));
        motorTable[i]->write(temp,0,sizeof(temp));
    }
    
} 