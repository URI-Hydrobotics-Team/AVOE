# Stonefish Interface for AVOE
This is AVOE's equivalent of `stonefish_ros` and operates very similairly to the standard cli frontend. This frontend creates a minimal stonefish instance, pulls virtual sensor data and stores into equivalent local `sensor_t` objects (defined very similary as in the cli frontend), and writes `motor_t` values to actuators in stonefish. All AVOE objects are exchanged over the network between itself and an unmodified `avoe` instance which operates like normal. 

## Compilation
The `build.sh` script is not functional, use `cmake`.

```
mkdir build
cd build
cmake ..
make
./avoe-frontend-stonefish tardigrade ../tardigrade.scn

```
