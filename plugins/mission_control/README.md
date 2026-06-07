# AVOE Mission Control Modules

## Overview
Mission Control (MC) modules enable autonmous movement. MC objects operate on an array of "Mission" objects or "frames". These frames define some sort of action (e.g. track an object, move an offset, etc.). The MC module interfaces with the controller and other objects such as PID controller to ensure desired movement is achieved. MC objects and mission frames should be setup and defined in `vehicle_setup.h` and their associated update functions should ultimately be called from the main loop in `main.cpp`.


## Realitve Mission Control 
Realtive mission control receives mission objects in a queue and attempts to satisfy the final position and pose by interfacing with a controller, sensor objects, and a PID controller. 


## Visual Point to Point Navigation (VPPN) Mission Control
Visual point to point navigation or VPPN schemes are soley based on computer vision. For Robosub 2026 we have opted to utilize this method.
