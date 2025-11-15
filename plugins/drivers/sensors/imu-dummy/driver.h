#pragma once
//#include "../../lib/RPi_BNO055/RPi_Sensor.h"
//#include "../../lib/RPi_BNO055/RPi_BNO055.h"
#include "../../../../lib/lib.h"
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
    vector_t Euler_Orientation, Angular_Velocity, Acceleration_Vector, Magnetic_Field_Strength, 
    Linear_Acceleration, Gravity_Vector;

    // Quaterion Orientation 
    vector4_t Quaterion_Orientation;

    int8_t temperature;
  public:
    // Constructor
    //BNO055();
    // void init();
    // void cold_init();

    // void IMU_calibration();
    vector_t get_Euler_Orientation();
    vector4_t get_Quaterion_Orientation();
    vector_t get_Angular_Velocity();
    vector_t get_Acceleration_Vector();
    vector_t get_Magnetic_Field_Strength();
    vector_t get_Linear_Acceleration();
    vector_t get_Gravity_Vector();
    int8_t get_temperature();

    // get random testing data, min and max is the min and max range of random numbers generated
    xyz_val get_rand_data(int min, int max);
};
