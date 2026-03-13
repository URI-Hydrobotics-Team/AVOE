# Autonomous Vehicle Operating Envronment (AVOE)

## Overview
AVOE is a minimalist robotics middleware suite for AUVs.

### Features
- fast performance
- easy to understand C++ codebase
- logging
- networking
- minimal and highly modular

### End Goal
Create a open source ROS alternative that is fast, minimal, highly modular, and flexible that can drive Tardigrade reliably in time for RoboSub 2026. 

## Documentation
Check out `docs`
## Quick start
AVOE ships with reference code for our Tardigrade AUV. Check out `docs/tardigrade.md`. Following the instructions below will get you started.

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

