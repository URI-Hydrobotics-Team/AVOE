# AVOE core components

## Overview
AVOE's core functionality, and direct successor to auv-hub. `/core` does not contain any vehicle specific references in its implementation. `vehicle_setup.h` and `main.h` do contain Tardigrade specific code, for now at least. But this can be replaced with your own code


## Features
- robust message system (`io.h`)
- motor control (`motor.h`)
- sensor system (`sensor.h`)
- simple logging capability (`log.h`)



## Important Files
### main.cpp
Includes all other header files and provides important functions for general vehicle control. The 'test()' function should be the only place where hardcoded elements are permitted. Also handles command line arguments. 




## Motors and Sensors
There are two classes `sensor_t` and `motor_t`, each of these classes contain properties and values for sensors and motors. They directly interface with the drivers through the `vehicle_setup.h` header file (formally `sensors.h` and `motors.h`). The `sensor_t` and `motor_t` objects then interface with other compontents such as the controller or the networking stack.
<br>
Sensor and Motor specific "middleware" exists in the `/plugins/general-*` directory.

## Message system and networking
AVOE is a single executable so commuinication within the process is trivial. External communication is defined in `io.h`. The `avoe_comm_transmitter` and `avoe_comm_reciever` objects can be configured to send or receive `motor_t`, `sensor_t`, `vector_t`, and character strings over socket connections. 



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

