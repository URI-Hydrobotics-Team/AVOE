if [ "$1" == "deckbox" ]; then
	echo "Building deckbox-cli"
	#g++ main.cpp -o avoe-frontend-cli ../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp sensor.cpp


	if [ "$2" == "sixaxis" ]; then
		echo "Input Method: SIXAXIS"
		g++ main.cpp -o avoe-frontend-cli -DSIXAXIS ../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../lib/vt100.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp ../../lib/controller.cpp
	elif [ "$2" == "f710" ]; then
		echo "Input Method: F710"
		g++ main.cpp -o avoe-frontend-cli -DF710 ../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../lib/vt100.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp ../../lib/controller.cpp
	elif [ "$2" == "keyboard" ]; then
		echo "Input Method: Keyboard"
		g++ main.cpp -o avoe-frontend-cli -DKEYBOARD ../../lib/network.cpp ../../lib/clock.cpp ../../lib/lib.cpp ../../lib/vt100.cpp ../../core/io.cpp ../../core/sensor.cpp ../../core/log.cpp ../../core/motor.cpp ../../lib/controller.cpp
	else




		echo "You must specify an input method type: <sixaxis>, <f710>, or <keyboard>"
	fi

elif [ "$1" == "sensor-test" ]; then
	echo "Building sensor test"
	g++ -o sensor-test sensor_test.cpp sensor.cpp ../../core/sensor.cpp ../../lib/lib.cpp ../../core/log.cpp
else
	echo "You must specifiy a build type: ./build <type>"
	echo "Types: 'deckbox', 'sensor-test'"
fi

