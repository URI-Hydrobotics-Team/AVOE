/*

	URI Hydrobotics
	AVOE vehicle specification class (definition and implementation)


*/


#include "sensor.h"
#include "motor.h"
#include "clock.h"
class vehicle_t{


	private:

		char name[32];
		char version[16];
		char type[16];
		
		int sensors_in_use;
		int motors_in_use;
		sensor_t sensors[MAX_PER_VEHICLE_SENSORS];
		motor_t motors[MAX_PER_VEHICLE_SENSORS];

		stopwatch_t clocks[MAX_PER_VEHICLE_CLOCKS];


	public:


	vehicle_t (char *n, char *v, char *t){

		strncpy(name, n, 32);
		strncpy(version, v, 16);
		strncpy(type, t, 16);

	}


	char *getName(){
		return name;
	}

	char *getVersion(){
		return version;
	}

	char *getType(){

		return type;
	}

	void update(){
		//update values and clocks


	}

	

	void initSensors(){

		for (int i = 0; i < sensors_in_use; i++){

			sensors[i].init();
		}

	}






};
