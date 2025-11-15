#include "driver.h"
#include <ctime>


int main(){
    srand(time(NULL));
    Dummy_BNO055 hi;
    while(true){
       imu::Vector<3> acceleration_vec = hi.get_Acceleration_Vector();
       std::cout << "Acceleration Vector: " << acceleration_vec.x() << " " << acceleration_vec.y() << " " << acceleration_vec.z() << "\n";

       imu::Vector<3> angular_vec = hi.get_Angular_Velocity();
       std::cout << "Angular Velocity: " << angular_vec.x() << " " << angular_vec.y() << " " << angular_vec.z() << "\n";

       imu::Vector<3> euler_orientation = hi.get_Euler_Orientation();
       std::cout << "Euler Orientation: " << euler_orientation.x() << " " << euler_orientation.y() << " " << euler_orientation.z() << "\n";

       imu::Vector<3> gravity_vec = hi.get_Gravity_Vector();
       std::cout << "Gravity Vector: " << gravity_vec.x() << " " << gravity_vec.y() << " " << gravity_vec.z() << "\n";

       imu::Vector<3> linear_acceleration = hi.get_Linear_Acceleration();
       std::cout << "Linear Acceleration: " << linear_acceleration.x() << " " << linear_acceleration.y() << " " << linear_acceleration.z() << "\n";

       imu::Vector<3> magnetic_field = hi.get_Magnetic_Field_Strength();
       std::cout << "Magnetic Field Strength: " << magnetic_field.x() << " " << magnetic_field.y() << " " << magnetic_field.z() << "\n";

       imu::Quaternion quat_orientation = hi.get_Quaterion_Orientation();
       std::cout << "Quaterion Orientation: " << quat_orientation.w() << " " << quat_orientation.x() << " " << quat_orientation.y() << " " << quat_orientation.z() << "\n";

       int8_t temp = hi.get_temperature();
       std::cout << "temp: " << int(temp) << "\n";
       std::cout << "\n";
    }
    return 0;
}