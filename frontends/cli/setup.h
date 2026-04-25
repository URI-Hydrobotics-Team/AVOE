/* very similar to vehicle setup.h */


vector_t dummyPosition(0.0, 0.0, 0.0);

motor_t thruster_BPH(1);
motor_t thruster_BSH(1);
motor_t thruster_SH(1);
motor_t thruster_Y(1);
motor_t thruster_PS(1);
motor_t thruster_SS(1);

sensor_t tardigrade_imu(8); 	
sensor_t tardigrade_pressure(4);
sensor_t tardigrade_leak(1);




void tardigrade_setup_sensors_virtual(){

	vector_t dummyPosition(0.0, 0.0, 0.0);
	/* AVOE init */
	tardigrade_imu.init("BNO055_dummy", "Adafruit", "I2C", "IMU", dummyPosition, dummyPosition);
	tardigrade_pressure.init("Bar_30m", "BlueRobotics", "I2C", "pressure", dummyPosition, dummyPosition);
	tardigrade_leak.init("SOS_Leak", "BlueRobotics", "GPIO", "leak", dummyPosition, dummyPosition);



	thruster_BPH.init("BPH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_BPH.init("BPH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_BSH.init("BSH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_SH.init("SH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_Y.init("Y", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_PS.init("PS", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_SS.init("SS", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);




}
