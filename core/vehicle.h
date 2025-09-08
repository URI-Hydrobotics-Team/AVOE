/*

	URI Hydrobotics
	AVOE vehicle specification class (definition and implementation)


*/


#include "sensor.h"
#include "motor.h"
#include "../lib/clock.h"
class vehicle_t{


	private:

		char name[32];
		char version[16];
		char type[16];

		int control_mode = 0;
		
		int sensors_count;
		int motor_count;

		avoe_clock_t clocks[MAX_PER_VEHICLE_CLOCKS];
		
		char sensor_table[MAX_PER_VEHICLE_SENSORS][16];


	public:


	vehicle_t (const char *n, const char *v, const char *t){

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

	void update(int m){
		//update values and clocks
		control_mode = m;

	}

	void updateSensorTable(sensor_t sensors[], int count){
		sensors_count = count;
		for (int i = 0; i < sensors_count; i++){
			initStr(sensor_table[i], 16);
			strncpy(sensor_table[i], sensors[i].getType(), 16);
			
		}
	}


	void print(){
		//print vehicle information for debugging purposes
		std::cout << "vehicle_t print:\n";
		std::cout << "\tPrimary Information:\n";
		std::cout << "\t\tNAME: " << name << '\n';
		std::cout << "\t\tVERSION: " << version << '\n';
		std::cout << "\t\tTYPE: " << type << '\n';
		
		std::cout << "\tSensor List:\n";
		for (int i = 0; i < sensors_count; i++){
			std::cout << "\t\t" << sensor_table[i] << '\n';
		}
	
	}

	



};
