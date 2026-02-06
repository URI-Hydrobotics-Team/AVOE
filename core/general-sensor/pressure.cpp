#include "pressure.h"
#include <cstring>
#include <string>
#include <iostream>

//Getting
float sensor_get_pres_get_pressure(sensor_t *obj){
    //Pulls data from Data area 1
    std::string str =  obj->read(1);
    return std::stof(str);
}
float sensor_get_pres_get_temperature(sensor_t *obj){
    //Pulls data from Data area 2
    std::string str =  obj->read(2);
    return std::stof(str);
}
float sensor_get_pres_get_depth(sensor_t *obj){
    //Pulls data from Data area 3
    std::string str =  obj->read(3);
    return std::stof(str);
}

//Setting
//Data areas listed in each function
void sensor_set_pres_set_pressure(sensor_t *obj, float pressure){
    //Data area 1
    //Converts pressure float value to String
    std::string str;
    str = std::to_string(pressure);
    obj->write(str.c_str(), 1, str.size());
}
void sensor_set_pres_set_temperature(sensor_t *obj, float temp){
    //Data area 2
    //Converts temperature float value to String

    std::string str;
    str = std::to_string(temp);
    obj->write(str.c_str(), 2, str.size());
}
void sensor_set_pres_set_depth(sensor_t *obj, float depth){
    //Data area 3
    //Converts depth float value to String

    std::string str;
    str = std::to_string(depth);
    obj->write(str.c_str(), 3, str.size());
}