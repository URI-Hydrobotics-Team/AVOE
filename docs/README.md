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
AVOE should be considered as a set of libraries that will help you build control software for an AUV. At the core, AVOE provides generalized components for managing sensors and motors along with an underlying subsystem that provides networking, logging, tools to build a ground interface (deckbox), and reference components in the form of "plugins" for extended functionality. While our codebase contains drivers and other code for our use cases, primarily our "Tardigrade" AUV, these drivers should not be considered core to AVOE, hence why they are in `plugins/`.

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
	tools/

```

#### `core/`

`core/` contains the very core of AVOE. It also acts as a working directory for your AVOE implementation as it is where you setup your AUV. Some notable files that implement core functionality include `io.h`, `log.h`, `motor.h`, `sensor.h` and `vehicle.h`. There is a build script that compiles AVOE (`build.sh`), however we are working to setup a proper build system using CMake. 

The files `vehicle_setup.h` and `main.cpp` are where you are expected to setup your "vehicle". `main.cpp` is essential and should at least contain some kind of bootstrap function for starting your control routines. Declaring and setting up your sensors and motors in `vehicle_setup` is not essential but is recommended. Really, you are free to structure your AVOE implementation however you want, for example, you could make a file called `connections.h` for declaring an initializing your network objects. This is explained in more detail in the "Vehicle Setup and main.cpp" section

#### `frontends/`
#### `lib/`
#### `plugins/`
#### `test/`
#### `tools/`
Originally AVOE was planned to have a program called `auto-tool` that would parse some kind of formatted text file (called the "manifest") containing a definition for a vehicle, essentially a list of all vehicle properties including sensors and motors. This tool would have lived under `tools/`. As of right now `auto-tool` is not implemented and there is no immediate plan to do so.

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
`TODO`

## Sensors
## Motors
## Networking
## Vehicle Setup and main.cpp
## Front Ends and Game Pads 




