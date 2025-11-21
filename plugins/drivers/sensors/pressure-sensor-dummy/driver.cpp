#include "driver.h"

void pressure_driver::init() {
    srand(time(NULL));
}

float pressure_driver::getPressure(float conversion) {
    int rand_p = rand() % 31 + 1;
    int rand_div = rand() % 31 + 1;

    return rand_p / rand_div;
}

float pressure_driver::getTemperature() {
    int rand_val = rand() % 106 + 1;
    int rand_div = rand() % 100 + 1;

    return rand_val / float(rand_div);
}

float pressure_driver::getDepth() {
    int rand_val = rand() % 296 + 1;

    return float(rand_val);
}

float pressure_driver::getAltitude() {
    int rand_val = rand() % 1000 + 1;

    return float(rand_val);
}
