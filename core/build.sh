
if [[ $1 == "-d" ]]; then
echo "Debug Mode Selected"
g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp -g
else
g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp 
fi