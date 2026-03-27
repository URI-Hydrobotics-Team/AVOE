#include "restore_offsets.h"
#include <cstdio>
#include <pigpio.h>


void display_sensor_status(Adafruit_BNO055 *imu){

	uint8_t system_status, self_test_results, system_error;
	system_status = self_test_results = system_error = 0;
	imu->getSystemStatus(&system_status, &self_test_results, &system_error);

	printf("SYSTEM STATUS\n");
	printf("\tsystem_status: %x\n", system_status);
	printf("\tself_test: %x\n", self_test_results);
	printf("\tsystem_error %x\n", system_error);

	//usleep(500*1000);	
}

void display_calibration_status(Adafruit_BNO055 *imu){




	uint8_t system, gyro, accel, mag;
	system = gyro = accel = mag = 0;


	imu->getCalibration(&system, &gyro, &accel, &mag);

	if (!system){
		printf("error\n");
		return;
	}

	printf("CALIBRATION_STATUS\n");
	printf("\tSystem: %d\n", system);
	printf("\tGyroscope: %d\n", gyro);
	printf("\tAccelerometer: %d\n", accel);
	printf("\tMagnetometer: %d\n", mag);

}



void display_sensor_offsets(const adafruit_bno055_offsets_t *calibData){



	printf("SENSOR OFFSETS\n");
	printf("\tACCELEROMETER: %d %d %d\n", calibData->accel_offset_x, calibData->accel_offset_y, calibData->accel_offset_z);
	printf("\tGYROSCOPE: %d %d %d\n", calibData->gyro_offset_x, calibData->gyro_offset_y, calibData->gyro_offset_z);
	printf("\tMAG: %d %d %d\n", calibData->mag_offset_x, calibData->mag_offset_y, calibData->mag_offset_z);
	printf("\tACCELERATION RADIUS: %d\n", calibData->accel_radius);
	printf("\tMAGNETOMOETER RADIUS: %d\n", calibData->mag_radius);

}

void write_calibration_data(FILE *fptr, adafruit_bno055_offsets_t *calibData){

	// we assume fptr has been setup for writing binary data

	int write_status = fwrite(calibData, sizeof(adafruit_bno055_offsets_t), 1, fptr);

	if(write_status == 0){
		printf("Write Erorr\n");
	}

	fclose(fptr);
	printf("Wrote calibration data\n");

	return;

}

void load_calibration_data(FILE *fptr, adafruit_bno055_offsets_t *calibData){


	int read_status = fread(calibData, sizeof(adafruit_bno055_offsets_t), 1, fptr);
	if (read_status == 0){
		printf("Read Erorr\n");
	}
	fclose(fptr);

	return;

}
