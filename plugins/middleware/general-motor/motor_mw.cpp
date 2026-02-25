//#include "./core/motor.h"
// bph bsh sh y ps ss
#include<iostream>
#include "../../../plugins/drivers/motors/ppsti/driver.h"
#include <cmath>
#include "../../../core/motor.h"
/*
void set_TDG_Thurst(motor_t bph, motor_t bsh,motor_t sh,motor_t y,motor_t ps,motor_t ss)
{
    char* values[6];

    values[0] = bph.read(0);
    values[1] = bsh.read(0);
    values[2] = sh.read(0);
    values[3] = y.read(0);
    values[4] = ps.read(0);
    values[5] = ss.read(0);    
}
*/
int thrustmapper(float input)
{
    return avoe_ppsti::convertToPWM(input);
}


float getThrustData(motor_t* mtr)
{
    return strtof(mtr->read(0),NULL);
}

void set_ppsti_data(motor_t *bph,motor_t* bsh,motor_t* sh,
                    motor_t* y,  motor_t* ps, motor_t* ss)
{
    //TODO: get rid of arrays at some point
    int pwm_bph  =thrustmapper(getThrustData(bph));
    int pwm_bsh  =thrustmapper(getThrustData(bsh));
    int pwm_sh  = thrustmapper(getThrustData(sh));
    int pwm_y  =  thrustmapper(getThrustData(y));
    int pwm_ps  = thrustmapper(getThrustData(ps));
    int pwm_ss  = thrustmapper(getThrustData(ss));
    std::vector<int> moterz;
    moterz.push_back(pwm_bph);
    moterz.push_back(pwm_bsh);
    moterz.push_back(pwm_sh);
    moterz.push_back(pwm_y);
    moterz.push_back(pwm_ps);
    moterz.push_back(pwm_ss);
    avoe_ppsti::sendAndReceive (avoe_ppsti::encodeToCommand(moterz),"/dev/acm0");
}
