# AVOE Plugins

## Overview

AVOE's plugins are similar to the older "modules" aprroach, essentially each plugin is a class definition with implementation. Plugins should not call variables that are declared in avoe-main and should instead global variables should be passed into functins via functions.

### Math Objects
Plugins that do not interface with hardware directly. A PID controller is an example of a math object.

### Drivers
#### Motor Drivers
Motor drivers are responsible for devices that conduct movement (i.e. servos, thrusters, etc.)
#### Sensor Drivers
Senosr drivers are self explanatory
