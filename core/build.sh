#if [[ $1 == "-d" ]]; then
#echo "Debug Mode Selected"
#g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/drivers/sensors/bnO055/driver.cpp -g

if [ "$1" == "virtual" ]; then
	echo "Building Virtual AVOE Target"
	g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/middleware/general-sensor/pressure.cpp ../plugins/drivers/sensors/pressure-sensor-dummy/driver.cpp ../plugins/middleware/general-sensor/leak.cpp ../plugins/drivers/sensors/leak-sensor-dummy/driver.cpp ../plugins/controllers/tardigrade_basic/controller.cpp


elif [ "$1" == "virtual_g" ]; then
	echo "Building Virtual AVOE Target with Address Sanitizer"
	g++ -o avoe main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/middleware/general-sensor/pressure.cpp ../plugins/drivers/sensors/pressure-sensor-dummy/driver.cpp ../plugins/middleware/general-sensor/leak.cpp ../plugins/drivers/sensors/leak-sensor-dummy/driver.cpp ../plugins/controllers/tardigrade_basic/controller.cpp -g -fsanitize=address




elif [ "$1" == "physical" ]; then
	echo "Building Physical AVOE Target"
	g++ -o avoe -DTARGET_TARDIGRADE main.cpp mission.cpp motor.cpp sensor.cpp vehicle.cpp log.cpp io.cpp ../lib/network.cpp ../lib/lib.cpp ../lib/clock.cpp ../plugins/middleware/general-sensor/imu.cpp ../plugins/drivers/sensors/imu-dummy/driver.cpp ../plugins/middleware/general-sensor/pressure.cpp ../plugins/drivers/sensors/pressure-sensor-dummy/driver.cpp ../plugins/middleware/general-sensor/leak.cpp ../plugins/drivers/sensors/leak-sensor-dummy/driver.cpp ../plugins/controllers/tardigrade_basic/controller.cpp ../plugins/drivers/sensors/bnO055/driver.cpp ../plugins/drivers/sensors/adafruit_bno055/driver.cpp ../plugins/drivers/sensors/adafruit_bno055/tools/restore_offsets/restore_offsets.cpp ../plugins/middleware/general-motor/ppsti_middleware/motor_mw.cpp ../plugins/drivers/motors/ppsti/driver.cpp  ../plugins/drivers/sensors/bar30m/driver.cpp -lpigpio $(pkg-config --cflags --libs libserialport)
else
	echo "You must specifiy a build type ./build <type>"
	echo "Types: 'virtual', 'physical'"
fi
