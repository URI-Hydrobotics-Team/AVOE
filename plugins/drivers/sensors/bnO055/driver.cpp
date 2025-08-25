#include "driver.h"
#include <unistd.h>
//BNO055::BNO055(){ 

void BNO055::cold_init(){ 
    // Set up the IMU 
    IMU = Adafruit_BNO055(55, BNO055_addr);

    //IMU = Adafruit_BNO055();
    //gpioInitialise();

    if (gpioInitialise() <0){
		std::cout <<"Initialisation error of the GPIO \n Closing program..."<< std::endl;
     }
	
    // Initialize the I2C communication
    IMU._HandleBNO = i2cOpen(IMU._i2cChannel, BNO055_addr, 0);

    // Start up the IMU and check if it is set up correctly
    if(!IMU.begin()){
        std::cout << "Something is wrong when setting up the IMU\n";
    }
    // Wait some time to let the IMU to begin
    //usleep(1000000);
    gpioSleep(PI_TIME_RELATIVE, 0, 1000);

    // Set the IMU to use the external crystal for more accurate result
    IMU.setExtCrystalUse(false);
}

void BNO055::init(){
    // Set up the IMU 
    IMU = Adafruit_BNO055(55, BNO055_addr);
	
    // Initialize the I2C communication
    IMU._HandleBNO = i2cOpen(IMU._i2cChannel, BNO055_addr, 0);

    // Start up the IMU and check if it is set up correctly
    if(!IMU.begin()){
        std::cout << "Something is wrong when setting up the IMU\n";
    }
    // Wait some time to let the IMU to begin
    //usleep(1000000);
    gpioSleep(PI_TIME_RELATIVE, 0, 1000);

    // Set the IMU to use the external crystal for more accurate result
    IMU.setExtCrystalUse(false);

}



void BNO055::IMU_calibration(){
    uint8_t system, gyro, accel, magnetic;

    while(!IMU.isFullyCalibrated()){
        IMU.getCalibration(&system, &gyro, &accel, &magnetic);
        std::cout << "System calibration: " << system << " Gyroscope calibration: " << gyro << " Accelerometer calibration: "<< accel <<
        " Magnetometer: " << magnetic << "\n";
    }
}

// Return the Euler orientation of the IMU
imu::Vector<3> BNO055::get_Euler_Orientation(){
    Euler_Orientation = IMU.getVector(Adafruit_BNO055::VECTOR_EULER);
    return Euler_Orientation;
}

// Return the quaternions orientation
imu::Quaternion BNO055::get_Quaterion_Orientation(){
    Quaterion_Orientation = IMU.getQuat();
    return Quaterion_Orientation;
}

// Return the angular velocity
imu::Vector<3> BNO055::get_Angular_Velocity(){
    Angular_Velocity = IMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    return Angular_Velocity;
}

// Return the acceleration vector
imu::Vector<3> BNO055::get_Acceleration_Vector(){
    Acceleration_Vector = IMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return Acceleration_Vector;
}

// Return the magnetic field strength
imu::Vector<3> BNO055::get_Magnetic_Field_Strength(){
    Magnetic_Field_Strength = IMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return Magnetic_Field_Strength;
}

// Return the linear acceleration
imu::Vector<3> BNO055::get_Linear_Acceleration(){
    Linear_Acceleration = IMU.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    return Linear_Acceleration;
}

// Return the gravity vector
imu::Vector<3> BNO055::get_Gravity_Vector(){
    Gravity_Vector = IMU.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    return Gravity_Vector;
}

// Return the temperature
int8_t BNO055::get_temperature(){
    temperature = IMU.getTemp();
    return temperature;
}

