@page "Vehicle Setup"
@brief Information on vehicle_setup.h


# About

This header file combines the sensors and vehicle information to make it easily accessible to the AVOE powered robot

# Recommend Setup


## Include files

Include the files in the following method

### Include the main core components
```

#include "config.h"
#include <ctime>
#include "sensor.h"
#include "motor.h"
#include "vehicle.h"

```

### Include the Middleware 

```

#include "../plugins/middleware/general-sensor/imu.h"
#include "../plugins/middleware/general-sensor/leak.h"
#include "../plugins/middleware/general-sensor/pressure.h"

```

### Include Dummy Drivers (If Using)
```
#include "../plugins/drivers/sensors/imu-dummy/driver.h"
#include "../plugins/drivers/sensors/pressure-sensor-dummy/driver.h"
#include "../plugins/drivers/sensors/leak-sensor-dummy/driver.h"
```


### Include Autonomy
```
#include "../plugins/mission_control/tardigrade_mc_relative/mission.h"
#include "../plugins/mission_control/tardigrade_mc_relative/mc.h"
```


### Include Physical Drivers
@note Use 

```
#include "../plugins/drivers/sensors/bar30m/driver.h"
#include "../plugins/drivers/sensors/bnO055/driver.h"
#include "../plugins/drivers/motors/ppsti/driver.h"
#include "../plugins/middleware/general-motor/ppsti_middleware/motor_mw.h" 
#include "../plugins/drivers/other/avoe_user_io/driver.h"
```

## Device Setup
#
