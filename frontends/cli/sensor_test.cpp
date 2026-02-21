#include "sensor.h"



int main(){
	
	vector_t dummyPosition;
	sensor_t tardigrade_imu(8);
	tardigrade_imu.init("BNO055_dummy", "Adafruit", "I2C", "IMU", dummyPosition, dummyPosition);
	
	
	char test_message[] = "$AVOES:imu_message:sensor:IMU BNO055_dummy 8        -42.000000, 00000$";
	map_sensor_string(&tardigrade_imu, test_message, 128);
	tardigrade_imu.print();
	

	return 0;
}
