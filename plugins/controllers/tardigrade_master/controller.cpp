#include "controller.h"

tardigrade_master_controller_t::tardigrade_master_controller_t(){
    vic = nullptr;
    sensorTable = nullptr;
    setpointTable = nullptr;
    outputTable = nullptr;
    output = nullptr;
}

tardigrade_master_controller_t::~tardigrade_master_controller_t(){
    delete[] vic;
    delete[] sensorTable;
    delete[] setpointTable;
    delete[] outputTable;
    delete[] output;
}

void tardigrade_master_controller_t::init(vehicle_t *vic_in){
    vic = *vic_in
    sensor_t tempSensorTable = vic->getSensorTable();

    for(size_t i = 0; i < vic->getSensorCount(); i++){
        if(tempSensorTable[i]->type == "imu"){
            sensorTable[0] = tempSensorTable[i];
        }
    }
}
void tardigrade_master_controller_t::modeSelect(int8_t *modeSelection){
    mode = modeSelection;
}
void tardigrade_master_controller_t::updateSetpoints(vector_t *lateral_desired, vector_t *rotational_desired){
    setpointTable[0] = lateral_desired;
    setpointTable[1] = rotational_desired;
}
pid_t tardigrade_master_controller_t::getPidOutput(){

}
void tardigrade_master_controller_t::refresh(){

}
void tardigrade_master_controller_t::mixerTable(){

}
