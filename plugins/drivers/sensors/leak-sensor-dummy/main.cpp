#include "driver.h"

int main() {
    leak_sensor sensor;
    sensor.init();
    int count = 0;

    while(true) {
        count += 1;

        int num = sensor.probe();
        std::cout << num << "\n";
        if(num == 1) {
            std::cout << count << " times printed\n";
            break;
        }
    }

    return 0;
}