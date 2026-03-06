# Controller implementation for Tardigrade

## Overview of tardigrade
The Tardigrade AUV has 6 thrusters. 


## Features
- Translational Movement
- Rotational Movement


## How it works
This "full" controller will take inputs from both a driver and a PID controller. The PID controller's attempts to maintain a pose defined by an `avoe_mission_t` object using the IMU. Any corrections the PID controller makes are sent to this controller which will handle the thrust output.
