//#include "./core/motor.h"
// bph bsh sh y ps ss
#include<iostream>
#include "../../../plugins/drivers/motors/ppsti/driver.h"
#include <cmath>
#include "../../../core/motor.h"

int thrustmapper(float input);
float getThrustData(motor_t* mtr);
void set_ppsti_data(motor_t *bph,motor_t* bsh,motor_t* sh, motor_t* y, motor_t* ps, motor_t* ss);
