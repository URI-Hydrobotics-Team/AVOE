# AVOE Documentation
## Contents
- Overview
- Introduction
- Installation
- Sensors
- Motors
- Networking
- Vehicle Setup and main.cpp
- Front ends and Game Pads 

## Overview
The Autonomous Vehicle Operating Environment is a project headed by the University of Rhode Island Hydrobotics team that aims to be a minimalist robotics middleware suite for AUVs. AVOE is designed to run on Linux but is not distribution specific, in fact, its requirements are quite minimal and it should run under any modern Linux distribution.

## Introduction
AVOE should be considered as a set of libraries that will help you build control software for an AUV. At the core, AVOE provides generalized components for managing sensors and motors, and an underlying subsystem that supports networking, logging, an autonomoy framework and the tools to build a ground interface (deckbox), plus reference components in the form of "plugins" for extended functionality. While our codebase contains drivers and other code for our use cases, primarily our "Tardigrade" AUV, these drivers should not be considered core to AVOE, hence why they are in `plugins/`.

AVOE addresses many of the issues with `auv-hub`, an earlier project which controlled Tardigrade. `auv-hub` was very basic, poorly written, and not flexible. Our goal is for AVOE to be a general soultion for building AUV control software that can be employed for Tardigrade and future AUVs.

AVOE is written in C++, however some may call it "C-style C++" as there is a preference for implementing things in purely C whenever possible. We may even consider full C rewrite at some point.

In AVOE, "vehicle" refers to your AUV, "sensors" are sensors, and "motors" are actuators.

### Directory Structure
```
AVOE/
	core/
	docs/
	frontends/
	lib/
	plugins/
	tests/

```

#### `core/`

`core/` contains the very core of AVOE. It also acts as a working directory for your AVOE implementation as it is where you setup your AUV. Some notable files that implement core functionality include `io.h`, `log.h`, `motor.h`, `sensor.h` and `vehicle.h`. There is a build script that compiles AVOE (`build.sh`), however we are working to setup a proper build system using CMake. 

The files `vehicle_setup.h` and `main.cpp` are where you are expected to setup your "vehicle". `main.cpp` is essential and should at least contain some kind of bootstrap function for starting your control routines. Declaring and setting up your sensors and motors in `vehicle_setup` is not essential but is recommended. Really, you are free to structure your AVOE implementation however you want, for example, you could make a file called `connections.h` for declaring an initializing your network objects. This is explained in more detail in the "Vehicle Setup and main.cpp" section

#### `frontends/`
#### `lib/`
#### `plugins/`
#### `test/`
## Installation

### Dependency List for Debian Based Systems
- gcc/g++
- make and cmake (for cmake build option)
- libc6-dev
- linux-headers

### Clone the repo
`git clone https://github.com/URI-Hydrobotics-Team/AVOE`

### Building AVOE using build script
`cd core`

`./build.sh <target>`

The executable should be titled `avoe` in the `core` folder
#### Building AVOE's reference CLI frontend (formerly deckbox-cli)
`cd frontends/cli`

`./build.sh deckbox`


### Building AVOE using CMake
`To be done in future, TODO`

## Sensors
AVOE features support for a multitude of sensors using base drivers written/rewritten into C/C++.

The base drivers for these are within plugins/general-sensor, This will be the directory where any sensors you plan on using will have it's drivers put in. With this, the actual vehicle runtime can grab these drivers for use in data collection and logic functions. 

Included within the directory is some examples of rewritten drivers that have been used in actual vehicles for development reference.

## Motors
AVOE also supports PWM enabled Thrusters. We use our own middleware for BlueRobotics thrusters. Currently we use a Microcontroller that interfaces with PPSTI. We plan on changing PPSTI to be supported on a Jetson Nano in the future.

## Networking
Chris do this stuff

## Vehicle Setup and main.cpp
Vehicle Setup is done within "Vehicle_Setup.h" . This allows for a simplified setup process when creating different parameters for vehicles. This may at a future time be changed to a single config file to allow for a single place for all parameters to be changed. This file should be treated as a configuration file for your specific vehicle. This is where most Vehicle specific methods should be called when you have your own implementation of AVOE. 

Main.cpp is the heart of all of AVOE's components. This is where most of AVOE's important objects are instantied and will either be given data at compile time or run time depending on the nature of the object. Objects include communication objects, motor objects, sensor objects, etc. The main purpose of this is to define behavior that you want to run depending on what is needed. This allows for a single place to change that behavior along with testing it. 

Main.cpp is split into two areas. Physical and Virtual, Physical is self explanitory as this is what you will run when actually running a AUV on AVOE. Virtual is your testing platform that can be used to test methods with random values that you would expect actual sensors to give you.

Virtual will work with the base repository with the included plugins for sensors and motors. There is dedicated virtual drivers for each sensor and motor object included within the plugins section of AVOE. Without these dedicated virtual drivers, any run of virtual with your own sensors/motors will not produced any data though should compile and run fine outside of data. 

## Front Ends and Game Pads 
Frontends refer to what was formarly known as "DeckboxCLI". DeckboxCLI (refered to past this point as Deckbox) is the main interface you will have for live data coming from your AUV. This also allows for controller input for manual control of thrusters. Deckbox can be programmed to display any data that you believe would be pertinent while also updating you with data live. The current deckbox included with AVOE displays all thrust vectors being input at a single time to all thrusters while also displaying all sensor within AVOE directly to deckbox.

Gamepads are another part of AVOE which at the time of writting we have 2 controllers implemented to some degree. The logitech F710 and any six-axis controller. There is drivers as references contained within the controller plugin directory. These are extremely useful for manual testing of the thrusters and getting movements down for seperate axis's for control logic. 



