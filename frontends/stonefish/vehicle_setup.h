#include "../../core/sensor.h"
#include "../../core/motor.h"

#include "config.h"

#ifndef VEHICLE_SETUP_H
#define VEHICLE_SETUP_H


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


	//networking setup
avoe_comm_transmitter frontend_to_core("sensor", "telemetry", PORT_CORE_SENSOR, IP_CORE);
avoe_comm_reciever core_to_frontend("motor", "telemetry", PORT_CORE_MOTOR, 2048);

avoe_clock_t ui_timer;
avoe_clock_t network_timer;


#endif
