#include "driver.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>

void dummy_mission_vppn::getRandData(){
    srand(static_cast<unsigned>(time(nullptr)));

    int whichName = rand() % 4;
    name = names[whichName];

    confidence = static_cast<float>(rand() % 101) / 100.0f;

    //Curr time point as time_t
    std::time_t now = std::time(nullptr);
    timestamp = std::localtime(&now);

    xOffset = rand() % X_OFFSET_MAX;
    yOffset = rand() % Y_OFFSET_MAX;
} 

std::string tm_to_string(const std::tm& tm){
    std::string str;
    str.resize(sizeof(std::tm));

    std::memcpy(&str[0], &tm, sizeof(std::tm));
    return str;
}

std::string dummy_mission_vppn::getData(size_t amountOfMsgs){
    if(amountOfMsgs < 1){
        std::cout << "Parameter needs to be 1 or more" << std::endl;
    }
    std::string output = "";
    for(size_t i = 0; i < amountOfMsgs; i++){
        getRandData();
        output += std::string(name) + "|" + std::to_string(confidence) + "|" + tm_to_string(*timestamp) + 
        "|" + std::to_string(xOffset) + std::to_string(yOffset) + std::to_string(zDistance) + "\n";
    }
    return output;
}