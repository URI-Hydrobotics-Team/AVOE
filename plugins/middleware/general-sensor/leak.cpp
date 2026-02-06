#include "leak.h"
#include <cstring>
#include <string>
#include <iostream>

bool getLEAK_STATUS(sensor_t *obj){
    //Pulls data from Data area 0
    bool leakVal;
    std::string str = obj->read(0);
    if(str == "true"){
        leakVal = true;
    }else {
        leakVal = false;
    }

    return leakVal;
}

void setLEAK_STATUS(sensor_t *obj, int leakVal){
    std::string str;
    if(leakVal == 1){
        str = "true";
    }else{
        str = "false";
    }

    obj->write(str.c_str(), 0, str.size());
}