/*

	URI Hydrobotics
	AVOE vehicle specification class (definition and implementation)


*/


#include "sensor.h"

class vehicle_t{


	private:

		char name[32];
		char version[16];
		char type[16];
		

		sensor_t sensors[MAX_PER_VEHICLE_SENSORS];


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

	





};
