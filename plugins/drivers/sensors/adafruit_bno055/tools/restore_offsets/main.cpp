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
	FILE *fptr;


	if (argc == 1){
		printf("Must Specficy and Argument\n");	
		return 0;
	}


	if (strncmp(argv[1], "disp", 32) == 0){


	}

	//CALIBRATE AND SAVE ROUTINE
	if (strncmp(argv[1], "save", 16) == 0){
		printf("CALIBRATE AND SAVE\n");
		strncpy(filename, argv[2], 128);
		fptr = fopen(filename, "wb");
		if (!file) {
			printf("Error Opening File %s\n", filename);
			return 0;
		}

		while (!imu.isFullyCalibrated()){
			display_calibration_status(&imu);
			usleep(50*1000); //delay 50s
		}

		printf("Calibration complete\n");
		
		imu.getSensorOffsets(calibrationData);
		display_sensor_offsets(&calibrationData);

		printf("Saving to %s\n", filename);


		write_calibration_data(fptr, &calibrationData);

		return 0;
	}

	//RESTORE CALIBRATION ROUTINE
	if (strncmp(argv[1], "restore", 16) == 0){
		printf("RESTORE CALIBRATION DATA\n");
		strncpy(filename, argv[2], 128);

		fptr = fopen(filename, "rb");
		if (!file) {
			printf("Error Opening File %s\n", filename);
			return 0;
		}
		load_calibration_data(fptr, &calibration_data);
		display_sensor_offsets(&calibrationData);
	
		imu.setSensorOffsets(calibrationData);
		printf("Restored Calibration Data\n");

		return 0;
	}

	//VIEW CALIBRATION DATA
	if (strncmp(argv[1], "view", 16) == 0){
		printf("VIEW CALIBRATION DATA\n");
		strncpy(filename, argv[2], 128);

		fptr = fopen(filename, "rb");
		if (!file) {
			printf("Error Opening File %s\n", filename);
			return 0;
		}
		load_calibration_data(fptr, &calibration_data);
		display_sensor_offsets(&calibrationData);
		
		return 0;

	}


	return 0;
}
