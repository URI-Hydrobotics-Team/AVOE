#include <iostream>
#include "vehicle_setup.h"
#include "vehicle_refresh.h"
#include "sf_bridge.h"
#include "../../plugins/middleware/general-sensor/imu.h"


#include <Stonefish/sensors/Sample.h>

/*
	This is where stonefish and AVOE objects are updated.


*/



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


void tardigrade_setup_avoe_objects(){

	vector_t dummyPosition(0.0, 0.0, 0.0);
	/* AVOE init */
	tardigrade_imu.init("imu_stonefish", "Adafruit", "I2C", "IMU", dummyPosition, dummyPosition);
	tardigrade_pressure.init("pressure_stonefish", "BlueRobotics", "I2C", "pressure", dummyPosition, dummyPosition);
	tardigrade_leak.init("leak_stonefish", "BlueRobotics", "GPIO", "leak", dummyPosition, dummyPosition);

	thruster_BPH.init("BPH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_BPH.init("BPH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_BSH.init("BSH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_SH.init("SH", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_Y.init("Y", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_PS.init("PS", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);
	thruster_SS.init("SS", "T200", "BlueRobotics", "PWM", "Thruster", dummyPosition, dummyPosition);

}

void tardigrade_setup_avoe(){

	tardigrade_setup_avoe_objects();
	std::cout << "[DEBUG] Sensor Setup Done\n";

	/* setup and initilizae all connections */	
	frontend_to_core.add_sensor(&tardigrade_imu);
	frontend_to_core.add_sensor(&tardigrade_pressure);
	frontend_to_core.add_sensor(&tardigrade_leak);

	core_to_frontend.add_motor(&thruster_SH);
	core_to_frontend.add_motor(&thruster_BSH);
	core_to_frontend.add_motor(&thruster_BPH);
	core_to_frontend.add_motor(&thruster_Y);
	core_to_frontend.add_motor(&thruster_PS);
	core_to_frontend.add_motor(&thruster_SS);
	core_to_frontend.set_timer(NETWORK_REFRESH_INTERVAL);
	frontend_to_core.set_timer(NETWORK_REFRESH_INTERVAL);

	
	network_timer.reset();
	ui_timer.reset();


}




void tardigrade_refresh_avoe(avoe_sf_tardigrade_t *sf){

	//called by stonefish
	//usleep(1000);

	core_to_frontend.refresh();
	frontend_to_core.refresh();


	// sensor mappings
	avoe_sf_imu(&tardigrade_imu, sf->sensor_imu);	

	if (ui_timer.getElaspedTimeMS() > UI_REFRESH){
		std::cout << "--AVOE Stonefish--\n";
		printf("SENSOR PRINT\n");
		tardigrade_imu.print();
		tardigrade_pressure.print();
		tardigrade_leak.print();
		printf("MOTOR PRINT");
		thruster_SH.print();
		thruster_PS.print();
		thruster_SS.print();
								

		//vtClear();
		ui_timer.reset();
	}

}
