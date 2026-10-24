/**
 * 	@file config.h
	@authors URI Hydrobotics
	@brief AVOE configuration file
	@note As AVOE evolves this will change heavily
*/

#ifndef CONFIG_H
#define CONFIG_H



// --- OLD STUFF ---
/* MISC */
///@name Miscellaneous
#define IMU_OFFSETS_FILENAME "irvine.bin"
//#define IMU_OFFSETS_FILENAME "NULL" //no calibration


/* GENERAL */
///@name General 
///@{
#define LOG_DIR "log-temp" ///< File name for log files
#define DISPLAY_OUTPUT_INTERVAL 100 ///< How often it gets updated in MS
///@}

///@name Vehicle

/* VEHICLE */
#define MAX_SENSOR_ENTRIES 16 
#define MAX_PER_VEHICLE_SENSORS 8
#define MAX_PER_VEHICLE_CLOCKS 5
#define TARDIGRADE_SENSOR_UPDATE_INTERVAL 500

/// @name Leds
#define LED0 20 ///<GPIO Pin
#define LED1 21 
#define LED2 12 
#define LED3 16

/// @name RoboSub
#define TASK_TIMEOUT 1 ///<seconds


/// @name Networking
/* NETWORKING */
#define IP_DECKBOX "127.0.0.1"
//#define IP_DECKBOX "172.20.218.138"
//#define IP_DECKBOX "10.42.0.1"
#define PORT_DECKBOX_TELEMETRY 8110
#define PORT_DECKBOX_INPUT 8101
#define NETWORK_UPDATE_INTERVAL 100


// --- NEW STUFF ---
#define AVOE_USER_PORT 2760 ///< Your "user" program will talk to AVOE on this port
#define AVOE_SENSOR_PORT 7447 




#endif
