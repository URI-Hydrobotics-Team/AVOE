/* very similar to vehicle setup.h */




sensor_t tardigrade_imu(8); 	
sensor_t tardigrade_pressure(4);
sensor_t tardigrade_leak(1);

void tardigrade_setup_sensors_virtual(){

	vector_t dummyPosition(0.0, 0.0, 0.0);
	/* AVOE init */
	tardigrade_imu.init("BNO055_dummy", "Adafruit", "I2C", "IMU", dummyPosition, dummyPosition);
	tardigrade_pressure.init("Bar 30m", "BlueRobotics", "I2C", "pressure", dummyPosition, dummyPosition);
	tardigrade_leak.init("SOS Leak", "BlueRobotics", "GPIO", "leak", dummyPosition, dummyPosition);






}
