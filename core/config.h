/*
	URI Hydrobotics
	AVOE configuration file

	We will switch to a *.conf plain text configuration file scheme at some point
*/

#ifndef CONFIG_H
#define CONFIG_H


/* MISC */
#define IMU_OFFSETS_FILENAME "irvine.bin"
//#define IMU_OFFSETS_FILENAME "NULL" //no calibration


/* GENERAL */
#define LOG_DIR "log-temp"
#define DISPLAY_OUTPUT_INTERVAL 500

/* VEHICLE */
#define MAX_SENSOR_ENTRIES 16
#define MAX_PER_VEHICLE_SENSORS 8
#define MAX_PER_VEHICLE_CLOCKS 5
#define TARDIGRADE_SENSOR_UPDATE_INTERVAL 500

/* ROBOSUB */
#define TASK_TIMEOUT 1 //seconds



/* NETWORKING */
//#define IP_DECKBOX "127.0.0.1"
//#define IP_DECKBOX "172.20.218.138"
#define IP_DECKBOX "10.42.0.1"
#define PORT_DECKBOX_TELEMETRY 8110
#define PORT_DECKBOX_INPUT 8101
#define NETWORK_UPDATE_INTERVAL 10

#endif
