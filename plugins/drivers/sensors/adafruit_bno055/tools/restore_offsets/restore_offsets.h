/*

	loosely based off adafruits tool

*/

#include "../../driver.h" //include adafruit driver 
#include "../../utility/imumaths.h"
#include <cstdlib>

#ifndef CALIBRATION_RESTORE_H
#define CALIBRATION_RESTORE_H








void display_sensor_status(Adafruit_BNO055 *imu);
void display_calibration_status(Adafruit_BNO055 *imu);
void display_sensor_offsets(const adafruit_bno055_offsets_t *calibData);
void write_calibration_data(FILE *fptr, adafruit_bno055_offsets_t *calibData);
void load_calibration_data(FILE *fptr, adafruit_bno055_offsets_t *calibData);






#endif
