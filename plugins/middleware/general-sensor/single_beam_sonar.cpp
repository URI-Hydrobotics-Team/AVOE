#include "single_beam_sonar.h"
#include<string>
#include <random>

#include <ctime>

/*
void update_sbs()
{
    device.request(1211,90);
}
*/

int sensor_get_sbs_distance(sensor_t *obj)
{
    std::string str = obj->read(0);
    return std::stoi(str);
}


int sensor_get_sbs_confidence(sensor_t *obj)
{
    std::string str = obj->read(1);
    return std::stoi(str);
}

void  sensor_set_sbs_distance(sensor_t *obj)
{
    srand(time(NULL));
    int rand_val = rand()%1337;
    //TODO: The actual driver implemented
    //update_sbs();
    std::string str;
    str = std::to_string(rand_val);
    obj->write(str.c_str(),0,str.size());

}
void  sensor_set_sbs_confidence(sensor_t *obj)
{
    srand(time(NULL));
    int rand_val = rand()%69;
    //TODO: The actual driver implemented
    //update_sbs();
    std::string str;
    str = std::to_string(rand_val);
    obj->write(str.c_str(),1,str.size());

}