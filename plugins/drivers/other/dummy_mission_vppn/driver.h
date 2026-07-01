#include "../../../../lib/lib.h"
#include <vector>
#include <iostream>
#include <chrono>

//Defined here to be easily changed for diff. resolution
#define X_OFFSET_MAX 1920
#define Y_OFFSET_MAX 1080
#define Z_DISTANCE 0 //Defined here as currently CV is not realiable for distance extrapolation

class dummy_mission_vppn{
    private:
    //Default data format: name|confidence|time stamp|screen x offset|screen y offset|actual distance in z
        char names[4][8] = {"Gate","Buoy","Marker","Wall"};
        char *name;
        float confidence;
        std::tm* timestamp;
        int xOffset;
        int yOffset;
        const int zDistance = 0;
        std::string data;
    public:
        void getRandData();
        std::string getData();
};