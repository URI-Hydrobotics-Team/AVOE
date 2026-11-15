#include "sf_bridge.h"
#include <Stonefish/sensors/Sample.h>




void avoe_sf_imu(sensor_t *avoe_imu, sf::IMU *sf_imu){


	// IMU
	std::vector<sf::Scalar> data;

	sf::Sample sf_imu_data(data);
	sf_imu_data = sf_imu->getLastSample();


// based off of https://github.com/patrykcieslak/stonefish_ros2/blob/6cea16d0b0ca0448e8172758de9e8eaeb1f8d48f/src/stonefish_ros2/ROS2Interface.cpp#L147
	// this one was just a guess 
	double imu_absolute_orientation_euler_x = sf_imu_data.getValue(0);
	double imu_absolute_orientation_euler_y = sf_imu_data.getValue(1);
	double imu_absolute_orientation_euler_z = sf_imu_data.getValue(2);

	double imu_angular_velocity_x = sf_imu_data.getValue(3);
	double imu_angular_velocity_y = sf_imu_data.getValue(4);
	double imu_angular_velocity_z = sf_imu_data.getValue(5);

	double imu_linear_accelaration_x = sf_imu_data.getValue(6);
	double imu_linear_accelaration_y = sf_imu_data.getValue(7);
	double imu_linear_accelaration_z = sf_imu_data.getValue(8);

	sensor_set_imu_LINEAR_ACCELERATION(avoe_imu, imu_linear_accelaration_x, imu_linear_accelaration_y, imu_linear_accelaration_z);
	sensor_set_imu_VELOCITY(avoe_imu, imu_angular_velocity_x, imu_angular_velocity_y, imu_angular_velocity_z);
	sensor_set_imu_ABSOULUTE_ORIENTATION_EULER(avoe_imu, imu_absolute_orientation_euler_x, imu_absolute_orientation_euler_y, imu_absolute_orientation_euler_z);





}
