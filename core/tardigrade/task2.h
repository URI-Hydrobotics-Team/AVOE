/*

	URI Hydrobotics
	Template Mode

*/


/* system */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/* AVOE specific*/
#include "../../lib/globals.h"
#include "../../lib/vt100.h"
#include "../config.h"
#include "../log.h"
#include "../io.h"
#include "../task.h"



/* target specific*/
#include "../vehicle_setup.h"
#include "../tasks.h"


void tardigrade_task_2(){

	printf("[MAIN] QUALIFICATION TASK STARTING: %dS UNTIL START\n", TASK_TIMEOUT);
	usleep(1000 * 1000 * TASK_TIMEOUT);
#ifdef TARGET_TARDIGRADE
#endif

}

