#include "../../core/io.h"
#include "../../lib/lib.h"

#define PORT_DECKBOX_TELEMETRY 8110

int main(int argc, char** argv){


	 avoe_comm_reciever rx_device1("sensor", "imu_message", PORT_DECKBOX_TELEMETRY, 2048);


	while(1){
		
		usleep(100000);
		rx_device1.rx();
		

	}



	return 0;
}
