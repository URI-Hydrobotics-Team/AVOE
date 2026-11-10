#include <Stonefish/sensors/scalar/IMU.h>
#include <Stonefish/sensors/scalar/Pressure.h>
#include <Stonefish/actuators/Thruster.h>



//custom object which contains all relevant sensors and actuators where data will be exchanged between stonefish and AVOE

struct avoe_sf_tardigrade_t {
	
	//sensors
	sf::IMU* sensor_imu;
	sf::Pressure* sensor_pressure;


	//motors
	sf::Thruster* motor_sh;	
	sf::Thruster* motor_bsh;	
	sf::Thruster* motor_bph;	
	sf::Thruster* motor_ss;	
	sf::Thruster* motor_y;	
	sf::Thruster* motor_ps;	

};
