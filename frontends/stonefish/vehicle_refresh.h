/*
	This is where stonefish and AVOE objects are updated.


*/

#include <Stonefish/core/SimulationManager.h>

#include "../../core/sensor.h"
#include "../../core/motor.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../core/io.h"
#include "../../lib/vt100.h"
#include "../../lib/clock.h"





#include "vehicle_setup.h"

void tardigrade_refresh_avoe();
void tardigrade_setup_avoe();
void tardigrade_setup_avoe_objects();
