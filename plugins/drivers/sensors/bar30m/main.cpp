
#include <iostream>
#include "driver.h"
#include <unistd.h>
#define MS5837_ADDR 0x76

void test(){

	MS5837 sensor;
	sensor.fullInit();

	while(1){

		sensor.read();
		std::cout << sensor.getPressure() << " mbar\n";
		std::cout << sensor.getTemperature() << " deg C\n";
		std::cout << sensor.getDepth() << " m\n";
		std::cout << sensor.getAltitude() << " m above mean sea level\n";
		usleep(1000000);
	}
}


int main(){

	test();

	return 0;
}
