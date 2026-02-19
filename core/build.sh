#if [[ $1 == "-d" ]]; then
#echo "Debug Mode Selected"
#g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp -g

if [ "$1" == "virtual" ]; then
	echo "Building Virtual AVOE Target"
	g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp 
elif [ "$1" == "real" ]; then
	echo "Building Real AVOE Target"
	g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp ../external/RPi_BNO055/RPi_BNO055.cpp -lpigpio 
else
	echo "You must specifiy a build type ./build <type>"
	echo "Types: 'virtual', 'real'"
fi
