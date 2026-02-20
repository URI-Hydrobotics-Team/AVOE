if [ "$1" == "deckbox" ]; then
	echo "Building deckbox-cli"
	g++ main.cpp -o avoe-frontend-cli ../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp
elif [ "$1" == "sensor-test" ]; then
	echo "Building sensor test"
	g++ -o sensor-test sensor_test.cpp sensor.cpp ../../core/sensor.cpp ../../lib/lib.cpp ../../core/log.cpp
else
	echo "You must specifiy a build type: ./build <type>"
	echo "Types: 'deckbox', 'sensor-test'"
fi

