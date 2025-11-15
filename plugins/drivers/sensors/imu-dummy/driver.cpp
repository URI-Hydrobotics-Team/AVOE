#include "driver.h"
#include <unistd.h>

xyz_val Dummy_BNO055::get_rand_data(int min, int max) {
    // srand(static_cast<unsigned int>(seed));
    
    // create xyz values and a random number used for division
    double x = 0;
    double y = 0;
    double z = 0;
    int rand_div = rand() % 5 + 1;

    // get random x y z values
    x = double(rand() % (max - min + 1) + min) / rand_div;
    y = double(rand() % (max - min + 1) + min) / rand_div;
    z = double(rand() % (max - min + 1) + min) / rand_div;

    // create xyz_val object 
    xyz_val rand_vec;
    rand_vec.x = x;
    rand_vec.y = y;
    rand_vec.z = z;

    return rand_vec;
}

// Return the Euler orientation of the IMU
vector_t Dummy_BNO055::get_Euler_Orientation(){
    xyz_val test_euler_orientation = get_rand_data(0, 360);

    Euler_Orientation.x = test_euler_orientation.x;
    Euler_Orientation.y = test_euler_orientation.y;
    Euler_Orientation.z = test_euler_orientation.z;

    return Euler_Orientation;
}

// Return the quaternions orientation
vector4_t Dummy_BNO055::get_Quaterion_Orientation(){
    xyz_val test_quat_orientation = get_rand_data(0, 360);
    int rand_w = rand() % 100;

    vector4_t quat;
    quat.i = double(rand_w); 
    quat.x = test_quat_orientation.x; 
    quat.y = test_quat_orientation.y;
    quat.z = test_quat_orientation.z;

    return quat;
}

// Return the angular velocity
vector_t Dummy_BNO055::get_Angular_Velocity(){
    xyz_val test_Angular_Velocity = get_rand_data(0, 500);

    Angular_Velocity.x = test_Angular_Velocity.x;
    Angular_Velocity.y = test_Angular_Velocity.y;
    Angular_Velocity.z = test_Angular_Velocity.z;

    return Angular_Velocity;
}

// Return the acceleration vector
vector_t Dummy_BNO055::get_Acceleration_Vector(){
    xyz_val test_Acceleration_Vector = get_rand_data(0, 700);

    Acceleration_Vector.x = test_Acceleration_Vector.x;
    Acceleration_Vector.y = test_Acceleration_Vector.y;
    Acceleration_Vector.z = test_Acceleration_Vector.z;

    return Acceleration_Vector;
}

// Return the magnetic field strength
vector_t Dummy_BNO055::get_Magnetic_Field_Strength(){
    xyz_val test_Magnetic_Field_Strength = get_rand_data(0, 100);

    Magnetic_Field_Strength.x = test_Magnetic_Field_Strength.x;
    Magnetic_Field_Strength.y = test_Magnetic_Field_Strength.y;
    Magnetic_Field_Strength.z = test_Magnetic_Field_Strength.z;

    return Magnetic_Field_Strength;
}

// Return the linear acceleration
vector_t Dummy_BNO055::get_Linear_Acceleration(){
    xyz_val test_Linear_Acceleration = get_rand_data(0, 230);

    Linear_Acceleration.x = test_Linear_Acceleration.x;
    Linear_Acceleration.y = test_Linear_Acceleration.y;
    Linear_Acceleration.z = test_Linear_Acceleration.z;

    return Linear_Acceleration;
}

// Return the gravity vector
vector_t Dummy_BNO055::get_Gravity_Vector(){
    xyz_val test_gravity = get_rand_data(0, 10);

    Gravity_Vector.x = test_gravity.x;
    Gravity_Vector.y = test_gravity.y;
    Gravity_Vector.z = test_gravity.z;

    return Gravity_Vector;
}

// Return the temperature
int8_t Dummy_BNO055::get_temperature(){
    temperature = -50 + rand() % 101;
    return temperature;
}
