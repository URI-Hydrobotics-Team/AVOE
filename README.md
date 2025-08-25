# Autonomous Vehicle Operating Envronment (AVOE)

## Overview
AVOE is the replacement for most of the control code in the AUV repository including auv-hub. AVOE will reimplement the functionaly of auv-hub and its supporting components in a much cleaner and less centrilized/hardcoded fashion.

### New Features (promised)
- markup language to define sensors, thrusters, cameras, etc. in a seperate config file
- PID controller implementation
- overall refinement
- integrated logging
- overhauled frontends
- simulation capabilities
- plugins (in the form of class definitions in header files that are included at compile time)
- zero dependency on hardcoded class objects


### Carryovers
- C++ codebase
- similar module (plugin) approach
- UDP sockets for networking

### End Goal
Create a open source ROS alternative that is fast, minimal, highly modular, and flexible that can drive Tardigrade reliably in time for RoboSub 2026. Maybe we can even gather some outside interest in terms of code contributions.


### TODO
- implement controller support
- skeleton for Tardigrade
- PID controller
- build a refrence frontend
- manifest parser

## Documentation

## Quick start
