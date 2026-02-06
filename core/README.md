# AVOE core components

## Overview
The core source for AVOE, and direct successor to auv-hub.


## Features (Not all implemented)
- robust message system (io.h)
- robust raw motor control (motor.h)
- felixbile sensor system (sensor.h)
- simple logging capability (log.h)
- simple but reliable control system (controller.h, vehicle.h)


## Important Files
### main.cpp
Includes all other header files and provides important functions for general vehicle control. The 'test()' function should be the only place where hardcoded elements are permitted. Also handles command line arguments. 




## Motors and Sensors
There are two classes `sensor_t` and `motor_t`, each of these classes contain properties and values for sensors and motors. They directly interface with the drivers through the `vehicle_setup.h` header file (formally `sensors.h` and `motors.h`). Ideally, sensors and motors are described in the Vehicle Description file and functions are written to translate these hardware specific drivers into universal `sensor_t` and `motor_t` objects automatically by avoe-tool. The `sensor_t` and `motor_t` objects then interface with other compontents such as the controller or the networking stack.
<br>
Sensor and Motor specific "middleware" exists in the `general-*` directories, however this middleware will be moved to the plugins directory.



### Sensor/Motor Properties
- Model
- Vendor/Manufacture
- Communication Protocol
- Type
- Relative Position
This may change as more implementation occurs. `motor_t` may have a property specifying output force, torque, etc.

## `vehicle_t`

Like the `sensor_t` and `motor_t` classes, `vehicle_t` is a class that contains properties for the target vehicle in a respective AVOE codebase. 
### Properties
- Name
- Version
- Type
- Sensor Count
- Motor Count 



## Skeleton


