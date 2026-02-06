#ifndef AVOE_HELPER_LEAK_H
#define AVOE_HELPER_LEAK_H

#include "../../lib/lib.h"
#include "../sensor.h"

bool getLEAK_STATUS(sensor_t *obj);
void setLEAK_STATUS(sensor_t *obj, int leakVal);

#endif