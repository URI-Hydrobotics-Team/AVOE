# Tardigrade's AVOE Implementation
## Physical Sensors and Motors
### Sensors
- IMU (Adafruit BNO055)
- Leak Sensor (BlueRobotics SOS Leak)
- Sonar (Ping 1D single beam)
- Pressure Sensor (BlueRobotics Bar30m)
### Thrusters (Motors)
- 4x Blue Robotics T100
- 2x Blue Robotics T200

## Overview
Tardigrade has two AVOE implementations, a production variant referred to as `physical` and a non production variant used for testing known as `virtual`. When compiling AVOE using the `build.sh` script, you can specifiy which target to build. The virtual target should compile on any Linux system while the physical target will only compile on the Raspberry Pi (as it has the necessary hardware and depenencies). All of the `sensor_t` and `motor_t` objects are declared inside the `vehicle_setup.h` file. Both the real and virtual targets share these sensor objects.


## Raspberry Pi Setup
### Initial Steps
- image an sdcard
- `sudo apt update` and `sudo apt upgrade`
- install some useful stuff: `sudo apt install vim git`

### Install pigpio
- `sudo apt install python-setuptools python3-setuptools`
- follow instructions here: https://abyz.me.uk/rpi/pigpio/download.html

### Build AVOE
Use the `build.sh` script under `core/` to build the `avoe` executable. 
- install dependencies: `sudo apt install gcc g++ libserialport-dev `
- `git clone https://github.com/URI-Hydrobotics-Team/AVOE`
- `cd AVOE core`
- configure network settings in config.h
- `./build.sh physical`

## Run AVOE
`sudo ./avoe tardigrade_<target>` 

## Calibrate IMU


### Setting up and compiling the frontend
At the moment, only the `cli` frontend is implemented. The frontend supports controller input via a PS3 controller connected via USB, the Logitech F710 is also supported but not configured. 



