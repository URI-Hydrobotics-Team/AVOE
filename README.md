# Autonomous Vehicle Operating Envronment (AVOE)

## Overview
AVOE is the replacement for most of the control code in the AUV repository including auv-hub. AVOE will reimplement the functionaly of auv-hub and its supporting components in a much cleaner and less centrilized/hardcoded fashion.

### New Features (promised)
- markup language to define sensors, thrusters, cameras, etc. in a seperate config file
- PID controller implementation
- more refined networking
- integrated logging
- overhauled frontends
- refined plugin structure
- major codebase cleanup
- zero dependency on hardcoded objects

### Carryovers
- C++ codebase
- similar module (plugin) approach
- UDP sockets for networking

### End Goal
Create a open source ROS alternative that is fast, minimal, highly modular, and flexible that can drive Tardigrade reliably in time for RoboSub 2026. Maybe we can even gather some outside interest in terms of code contributions.


### TODO
- finish motor_support
- PID controller
- build a reference frontend
- manifest parser

## Documentation
Check out the READMEs
## Quick start
At the moment, AVOE is in heavy development, but you can test some stuff. Check out the test() function in `core/main.cpp` for a simple reference. This section will expand as more development occurs.
