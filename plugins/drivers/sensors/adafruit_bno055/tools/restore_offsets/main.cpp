#include "restore_offsets.h"
#include <cstdio>
#include <cstring>


int main(int argc, char** argv){

	//SETUP
	
	Adafruit_BNO055 imu = Adafruit_BNO055(55, 0x28);
	if (gpioInitialise() < 0){
		printf("Initialisation error of the GPIO \n");
		return 0;
	}

	// Initialize the I2C communication
	imu->_HandleBNO = i2cOpen(imu->_i2cChannel, BNO055_addr, 0);
	if (!imu.begin()){
		printf("error setting up imu\n");
		return 0;
	}


	gpioSleep(PI_TIME_RELATIVE, 0, 500000);

	// Set the IMU to use the external crystal for more accurate result
	IMU->setExtCrystalUse(false);

	long bnoID;
    	bool foundCalib = false;

	adafruit_bno055_offsets_t calibrationData;



	// ARGUMENT PARSING

	char filename[128];

	if (argc == 1){
		printf("Must Specficy and Argument\n");	
		return 0;
	}


	if (strncmp(argv[1], "disp", 32) == 0){


	}

	//CALIBRATE AND SAVE ROUTINE
	if (strncmp(argv[1], "save", 16) == 0){
		strncpy(filename, argv[2], 128);
		

	}

	//RESTORE CALIBRATION ROUTINE
	if (strncmp(argv[1], "restore", 16) == 0){
		strncpy(filename, argv[2], 128);
		

	}

	//VIEW CALIBRATION DATA
	if (strncmp(argv[1], "view", 16) == 0){
		strncpy(filename, argv[2], 128);
		

	}










	return 0;
}
