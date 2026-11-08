/*
 * Tardigrade Master PID Controller
*/

#ifndef TARDIGRADE_MASTER_CONTROLLER_H
#define TARDIGRADE_MASTER_CONTROLLER_H

#include "../../../core/vehicle.h"
#include "../../../core/sensor.h"
#include "../../../lib/lib.h"
#include "../../math/avoe_pid_controller/pid.h"

class tardigrade_master_controller_t{
    private:
        vehicle_t *vic; //Pull sensors from vehicle obj
        sensor_t sensorTable[4]; //Sensor obj storage
        vector_t setpointTable[2]; // 0 - lateral, 1 - rotational
        pid_t output;
        int8_t mode;
        vector_t mixerTable();
    public:
        tardigrade_master_controller_t();
        ~tardigrade_master_controller_t();
        void init(vehicle_t *vic_in);
        //Mode actions: 1-6, Each individual axis (X,Y,Z,R,P,Y) in that order
        //7, 3-DOF (X,Y,Z)
        //8, 3-DOF (R,P,Y)
        //9, 6-DOF (All axial controllers)
        void modeSelect(int8_t *mode);  
        void updateSetpoints(vector_t *lateral_desired, vector_t *rotational_desired);
        pid_t getPidOutput();
        void refresh(); //sensor data refresh method 
};

#endif

//Only used for output to actual controllers
struct pid_t{
    vector_t lateral_movement;
    vector_t rotational_movement;
};
