#ifndef MOTOR_MW
#define MOTOR_MW
// bph bsh sh y ps ss
#include<iostream>
#include "../../../drivers/motors/ppsti/driver.h"
#include <cmath>
#include "../../../../core/motor.h"
#define PICO_SERIAL_PORT "/dev/ttyACM0"


int thrustmapper(float input);
float getThrustData(motor_t* mtr);
void set_ppsti_data(motor_t *bph,motor_t* bsh,motor_t* sh, motor_t* y, motor_t* ps, motor_t* ss);
#endif
