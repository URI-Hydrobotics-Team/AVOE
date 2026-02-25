# Autonomous Vehicle Operating Envronment (AVOE)

## Overview
AVOE is the replacement for most of the control code in the AUV repository including auv-hub. AVOE will reimplement the functionaly of auv-hub and its supporting components in a much cleaner and less centrilized/hardcoded fashion.

### New Features
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
- PID controller
- manifest parser

## Documentation
Check out the READMEs
## Quick start
At the moment, AVOE is in heavy development, but you can test some stuff. Check out the test_* functions in `core/main.cpp` for a simple reference.

### Dependency List for Debian Based Systems
- gcc/g++
- make and cmake (for cmake build option)
- libc6-dev
- linux-headers


## Building the Core Program
### With CMake
`mkdir build`

`cd build`

`cmake ..`

`make`

>[!TIP]
> you really only need to run the `cmake ..` once if you make changes to the code locally without moving any of the files you simply can just run 
`make`.

The executable should be titled `avoe` inside of the `build` folder that was created
### With Bash
#### Building AVOE
`cd core`

`./build.sh virtual`
#### Building AVOE for debugging
`./build.sh virtual_g`

The executable should be titled `avoe` in the `core` folder
#### Building AVOE's reference CLI frontend (formerly deckbox-cli)
`cd frontends/cli`

`./build.sh deckbox`





