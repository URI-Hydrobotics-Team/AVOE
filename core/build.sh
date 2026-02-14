#if [[ $1 == "-d" ]]; then
#echo "Debug Mode Selected"
#g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp -g
#if [[ $1 == "-p" ]]; then #physical target
#g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp 
#else
g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp ../external/RPi_BNO055/RPi_BNO055.cpp -lpigpio 
#fi
