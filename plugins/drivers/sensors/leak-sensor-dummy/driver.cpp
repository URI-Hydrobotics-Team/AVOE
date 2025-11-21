#include "driver.h"

void leak_sensor::init() {
    srand(time(NULL));
}

int leak_sensor::probe() {
    int rand_val = rand() % 101;

    if(rand_val < 100) {
        return 0;
    }

    return 1;
}