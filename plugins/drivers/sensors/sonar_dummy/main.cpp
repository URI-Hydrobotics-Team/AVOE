/***
 * BY ANDREW DAWSON
 * Good Luck Translating this shit
 */
#include <cstdio>
#include <iostream>
#include "../../../../Sonar/ping-cppcstred/src/device/ping-device-ping1d.h"

int main()
{



    Ping1d device = Ping1d();
    //
    device.request(5,30);
    bool isgood = true;
    while (isgood)
    {
        device.request(1211,90);
        std::cout <<"\nVersion:" << (int)device.protocol_version.version_major<< "." << (int)device.protocol_version.version_minor << "."<< (int)device.protocol_version.version_patch;
        std::cout << "\n" << "Distance:" <<   (int)device.distance_simple_data.distance;
        std::cout << "\n" << "CONF:" <<   (int)device.distance_simple_data.confidence;
        device.set_gain_setting(2);
        /* code */
    }
    



    return 0;
}
