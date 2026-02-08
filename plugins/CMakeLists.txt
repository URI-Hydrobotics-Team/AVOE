#compiles this shit into a lib ig

add_library(
plugins 
./middleware/general-sensor/imu.cpp
./drivers/sensors/imu-dummy/driver.cpp)