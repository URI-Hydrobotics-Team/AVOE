#pragma once
#include <random>
#include <ctime>

class pressure_driver {
    public:
        void init();
		float getPressure(float conversion = 1.0f);
        float getTemperature();
		float getDepth();
		float getAltitude();
};