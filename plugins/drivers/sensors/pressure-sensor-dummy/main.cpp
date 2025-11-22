#include "driver.h"
#include <iostream>


int main() {
    pressure_driver sensor;
    sensor.init();

    while(true) {
        std::cout << "pressure: " << sensor.getPressure() << " temp: " << sensor.getTemperature() << " depth: " << sensor.getDepth() << " altitude: " << sensor.getAltitude() << "\n";
    }


    return 0;
}