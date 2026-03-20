/*
	URI Hydrobotics
	AVOE configuration file

*/

#ifndef CONFIG_H
#define CONFIG_H


/* general */
#define LOG_DIR "log-temp"
#define DISPLAY_OUTPUT_INTERVAL 500

/* vehicle */
#define MAX_SENSOR_ENTRIES 16
#define MAX_PER_VEHICLE_SENSORS 8
#define MAX_PER_VEHICLE_CLOCKS 5

#define TARDIGRADE_SENSOR_UPDATE_INTERVAL 500


/* networking */
#define IP_DECKBOX "172.20.218.138"
//#define IP_DECKBOX "10.42.0.1"
#define PORT_DECKBOX_TELEMETRY 8110
#define PORT_DECKBOX_INPUT 8101
#define NETWORK_UPDATE_INTERVAL 10



#define SOCKET_SLEEP 1000
#define SOCKET_TIMEOUT 10000

#endif
