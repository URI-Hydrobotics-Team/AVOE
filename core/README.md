# AVOE core components

## Overview
The core source for AVOE, essentially the closest component to auv-hub.

## Motors and Sensors
There are two classes `sensor_t` and `motor_t`. These classes contain properties and values for sensor and motor drivers. The directly interface with these drivers through the `sensors.h` and `motors.h` header files. Ideally, sensors and motors are described in the Vhecile Description file and functions are written to translate these hardware specific drivers into universial `sensor_t` and `motor_t` objects automaticlly by avoe-tool. The `sensor_t` and `motor_t` objects then interface with the "skeleton", currently not formalized, which contains hardcoded functions for driving the robot.

### Sensor/Motor Properties
- Model
- Vendor/Manufacteur
- Communication Protocol
- Type
- Relative Position


## `vehicle_t`

Like the `sensor_t` and `motor_t` classes, `vehicle_t` is a class that contains properties for the target vehicle in a respective AVOE codebase. 
### Properties
- Name
- Version
- Type
- Sensor Count
- Motor Count 



## Skeleton


