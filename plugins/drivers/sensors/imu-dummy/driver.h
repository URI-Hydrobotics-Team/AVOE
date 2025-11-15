#pragma once
#include "../../lib/RPi_BNO055/RPi_Sensor.h"
#include "../../lib/RPi_BNO055/RPi_BNO055.h"
#include <vector>
#include <iostream>

#define BNO055_addr 0x28

// struct to hold the x y z values of different vectors
struct xyz_val
{
    double x;
    double y;
    double z;
};


class Dummy_BNO055{
  private:
    // The IMU object
    // Adafruit_BNO055 IMU;

    // Vectors for the different data
    imu::Vector<3> Euler_Orientation, Angular_Velocity, Acceleration_Vector, Magnetic_Field_Strength, 
    Linear_Acceleration, Gravity_Vector;

    // Quaterion Orientation 
    imu::Quaternion Quaterion_Orientation;

    int8_t temperature;
  public:
    // Constructor
    //BNO055();
    // void init();
    // void cold_init();

    // void IMU_calibration();
    imu::Vector<3> get_Euler_Orientation();
    imu::Quaternion get_Quaterion_Orientation();
    imu::Vector<3> get_Angular_Velocity();
    imu::Vector<3> get_Acceleration_Vector();
    imu::Vector<3> get_Magnetic_Field_Strength();
    imu::Vector<3> get_Linear_Acceleration();
    imu::Vector<3> get_Gravity_Vector();
    int8_t get_temperature();

    // get random testing data, min and max is the min and max range of random numbers generated
    xyz_val get_rand_data(int min, int max);
};