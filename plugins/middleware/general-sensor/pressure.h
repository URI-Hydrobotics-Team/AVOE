/*
    AVOE Pressure Helper Methods
*/
#ifndef AVOE_HELPER_PRES_H
#define AVOE_HELPER_PRES_H

#include "../../lib/lib.h"
#include "../sensor.h"

//Getting
float sensor_get_pres_get_pressure(sensor_t *obj);
float sensor_get_pres_get_temperature(sensor_t *obj);
float sensor_get_pres_get_depth(sensor_t *obj);

//Setting
void sensor_set_pres_set_pressure(sensor_t *obj, float pressure);
void sensor_set_pres_set_temperature(sensor_t *obj, float temp);
void sensor_set_pres_set_depth(sensor_t *obj, float temp);

#endif