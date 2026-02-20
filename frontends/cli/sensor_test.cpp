#include "sensor.h"



int main(){

	
	char test_message[] = "$AVOES:imu_message:sensor:IMU BNO055 dummy 8        -42.000000, 00000$";
	map_sensor_string(nullptr, test_message, 128);


	return 0;
}
