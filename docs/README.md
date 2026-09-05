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

`frontends/` refers to programs that provide an interface to view telemetry from the "vehicle" and sending control data, such as gamepad inputs, to the "vehicle". Telemetry includes but is not limited to Motors (raw thruster values in a float representation), Sensors (Output for parsed sensor info fields). We provide a "CLI" refrecne version which is used for our Tardigrade AUV. Our CLI interface is configured in the `config.h` file. This is mainly settings such as Controller timeout and IP address info to reach the AUV.

Currently our frontend CLI program and the core AVOE itself are configured through a header file `config.h`, however future plans are to implement a plain text config system that can be parsed on startup to prevent the user to constantly recompile for configuration changes.

#### `lib/`

`lib/` is our primary directory for commonly used components of AVOE, the files that are currently maintained is `lib.h/.cpp` and `clock.h/.cpp`. `lib.h/.cpp` contains helper methods such as `appendstr`, `initstr`, and `vector_t` struts for data storage of 3D-4D Vector objects. `clock.h/.cpp` contains a timer implementation for semi-percise timing events. `network.h` provides core I/O for UDP network sockets. `controller.h` and `keyboard.h` provide easy to use functions for getting gamepad and keyboard input from Linux. `globals.h` stores global macros, such as AVOE version.
#### `plugins/`

`plugins/` is the location of files that are not part of the core of AVOE, but are needed for Navigation, Control, and Sensor/Motor Middleware. Each folder has it's own purpose which is explained below for each.

- `Controllers`
	- Main controllers for Vector output for motor movement through thrust tables.
	
- `Drivers` 
	- This houses mainly the Sensor/Motor drivers for communication to both and incoming data from each set. There is also Dummy setup files for Virtual vehicle testing. The files here handle getting data directly from the sensor you call. These values should then be fed into `motor_t` or `sensor_t` objects to be sent back in telemetry and ease of pulling data. 
	
- `Gamepad Maps`
	- Explains itself, Gamepad Mapping for two different Gamepads (F710, Logitech) or (Six-Axis, Generic).
	
- `Math`
	- Mainly holds an old testing version of our PID software. It is completely Virtual for output and is not established for actual testing params.
	
- `Middleware`
	- The middleware folder holds both the Motor and Sensor General middleware.
 	- Motor Middleware houses PPSTI (Pi Pico Serial Thruster Interface) which handles PPSTI calls to convert Vectors to PWM values. PPSTI also is able to pull raw thruster data directly from the motor.
 	- The Sensor Middleware handles pulling data from `sensor_t` objects and into the actual data type. This was setup in this fashion for ease of transferring data to and from the bot without having to hard program a part in the network transmission for each sensor. Through this format, you are able to just define a sensor_t object within your vehicle setup that will be transmitted and recieved through your network connection.
	
- `Mission Control`
  	- This folder contains the two different versions of Mission Control, or MC. MC_Relative is mission control that uses only the IMU for navigation, MC_VPPN operates solely on CV. The version of Mission Control we want in the end is both of these combined into each other for max error correction. 

#### `test/`
`test/` holds various test files that virtually test out different aspects of AVOE to check functionality. There is not many tests here as most changes made during the creation of AVOE were tested Physically due to time constraints and time needed to get AVOE into a zero error state. 
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


### Building AVOE using Make
`To be done in future, TODO`

## Sensors
AVOE has our sensors setup in a flexible high level sensor abstraction, what this means is that you can create a sensor using our `sensor_t` object and pull telemetry data easily from your bot, all that is needed to implement this is a driver that can be integrated/rewritten into AVOE (C/C++ drivers are only supported, you can rewrite drivers from Python to C/C++, this is what we did for our driver integration).

We ship AVOE with some example drivers from our own implementation that can be used for a reference for your own implementation. You can also view how we setup our `sensor_t` objects within `vehicle_setup.h`. At a point in the future, the Core directory will be given a Method layout diagram for easy viewing of all the methods and the purpose of each file for ease of viewing.

## Motors
AVOE allows you to implement any thruster telemetry, as long as you have a plugin to handle the conversion of Input to Output for thrusters. With our current use of AVOE, we have a plugin titled `PPSTI (Pi Pico Serial Thruster Interface)` that handles conversion of vectors to PWM values which is used by our ESC's to drive thrusters. Our implementation as of writing has some manual config work needed to be done to allow for different Motor setups, but you would be able to realistically this with some effort. 

## Networking
Wizard Magic (To be done at a later time)

## Vehicle Setup and main.cpp
Vehicle Setup is done within "Vehicle_Setup.h" . This allows for a simplified setup process when creating different parameters for vehicles. This may at a future time be changed to a single config file to allow for a single place for all parameters to be changed. This file should be treated as a configuration file for your specific vehicle. This is where most Vehicle specific methods should be called when you have your own implementation of AVOE. 

Main.cpp is the heart of all of AVOE's components. This is where most of AVOE's important objects are instantied and will either be given data at compile time or run time depending on the nature of the object. Objects include communication objects, motor objects, sensor objects, etc. The main purpose of this is to define behavior that you want to run depending on what is needed. This allows for a single place to change that behavior along with testing it. 

Main.cpp is split into two areas. Physical and Virtual, Physical is self explanatory as this is what you will run when actually running a AUV on AVOE. Virtual is your testing platform that can be used to test methods with random values that you would expect actual sensors to give you.

Virtual will work with the base repository with the included plugins for sensors and motors. There is dedicated virtual drivers for each sensor and motor object included within the plugins section of AVOE. Without these dedicated virtual drivers, any run of virtual with your own sensors/motors will not produced any data though should compile and run fine outside of data. 

## Front Ends and Game Pads 
Frontends refer to what was formarly known as "DeckboxCLI". DeckboxCLI (refered to past this point as Deckbox) is the main interface you will have for live data coming from your AUV. This also allows for controller input for manual control of thrusters. Deckbox can be programmed to display any data that you believe would be pertinent while also updating you with data live. The current deckbox included with AVOE displays all thrust vectors being input at a single time to all thrusters while also displaying all sensor within AVOE directly to deckbox.

Gamepads are another part of AVOE which at the time of writting we have 2 controllers implemented to some degree. The logitech F710 and any six-axis controller. There is drivers as references contained within the controller plugin directory. These are extremely useful for manual testing of the thrusters and getting movements down for seperate axis's for control logic. 



