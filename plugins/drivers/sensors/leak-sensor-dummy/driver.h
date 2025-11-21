#include <iostream>
#include <random>
#include <ctime>

class leak_sensor {
    public:
        // function to set random seed for random value
        void init();

        // get the leak sensor data
        int probe();
};