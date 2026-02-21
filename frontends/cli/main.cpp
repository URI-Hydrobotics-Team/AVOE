/*
	Reference CLI frontend for AVOE
	URI Hydrobotics
	
*/
#include <cstring>
#include <iostream>

/* AVOE specific includes */
#include "config.h"
#include "../../lib/lib.h"
#include "../../lib/globals.h"
#include "../../lib/network.h"
#include "../../core/io.h"
#include "../../lib/controller.h"
#include "../../lib/keyboard.h"
#include "../../lib/vt100.h"
#include "../../lib/clock.h"
#include "../../plugins/gamepad_maps/sixaxis.h"
#include "setup.h"
#include "sensor.h"
/* system setup */



//controller



controller_t raw_controller; //raw device
controller_generic_raw sixaxis; //virtual raw device
controller_generic_profile deckbox_input; //virtual "refined" device
// clocks





/* network helper functions */





void printController(controller_generic_profile *deckbox_input){

std::cout << "--- INPUT STAUS ---\n";
	
	/* controller input*/
	std::cout << "\tButtons:\n";
	std::cout << "\t\tButton 1: " << deckbox_input->fc_1 << '\n';
	std::cout << "\t\tButton 2: " << deckbox_input->fc_2 << '\n';
	std::cout << "\t\tButton 3: " << deckbox_input->fc_3 << '\n';
	std::cout << "\t\tButton 4: " << deckbox_input->fc_4 << '\n';

	std::cout << "\t\tD-Pad Up: " << deckbox_input->dp_up << '\n';	
	std::cout << "\t\tD-Pad Down: " << deckbox_input->dp_down << '\n';
	std::cout << "\t\tD-Pad Left: " << deckbox_input->dp_left << '\n';
	std::cout << "\t\tD-Pad Right: " << deckbox_input->dp_right << '\n';

	std::cout << "\t\tLT1: " << deckbox_input->lt << '\n';
	std::cout << "\t\tRT1: " << deckbox_input->rt << '\n';

	std::cout << "\t\tLT2: " << deckbox_input->lt_a << '\n';
	std::cout << "\t\tRT2: " << deckbox_input->rt_a << '\n';

	std::cout << "\t\tStart: " << deckbox_input->start << '\n';
	std::cout << "\t\tSelect: " << deckbox_input->select << '\n';
	std::cout << "\t\tSuper: " << deckbox_input->super << '\n';

	std::cout << "\tSticks:\n";

	std::cout << "\t\tLeft Click: " << deckbox_input->sc_left << '\n';
	std::cout << "\t\tRight Click: " << deckbox_input->sc_right << '\n';

	std::cout << "\t\tLeft: " << deckbox_input->sll_x << ' ' << deckbox_input->sll_y << '\n';
	std::cout << "\t\tRight: " << deckbox_input->slr_x << ' ' << deckbox_input->slr_y << '\n';
}


void setup(){

	
	//controller
	raw_controller.setDevice("/dev/input/js0");
	raw_controller.init();
	
	tardigrade_setup_sensors_virtual();
	std::cout << "[DEBUG] Setup Done\n";

}



void raw(){





}


void test(){

	char message[32] = "look here look listen";
	char rx_message[1024]; //big buffer

	//networking setup
	avoe_comm_transmitter frontend_to_core("message", "general", CORE_PORT_TX, CORE_IP);
	avoe_comm_reciever core_to_frontend("sensor", "sensors", 8101);

	/* setup and initilizae all connections */	
	frontend_to_core.set_message(message, 32);
	frontend_to_core.set_timer(1000);	
	core_to_frontend.set_message(rx_message, 1024);


	std::cout << "AVOE Frontend CLI Test Mode\n";
	setup();
	avoe_clock_t ui_timer;
	avoe_clock_t network_timer;
	
	network_timer.reset();
	ui_timer.reset();
	while(1){
		//frontend_to_core.refresh();
	
		if (network_timer.getElaspedTimeMS() > 10){
			core_to_frontend.rx();
			network_timer.reset();
		}

		//std::cout << test_timer.getElaspedTimeMS() << '\n'; 
		if (ui_timer.getElaspedTimeMS() > 1000){
			map_sensor_string(&tardigrade_imu, rx_message, 1024);
			map_sensor_string(&tardigrade_pressure, rx_message, 1024);
			map_sensor_string(&tardigrade_leak, rx_message, 1024);
			std::cout << "Message from core: " << rx_message << '\n';
			//std::cout << "Message to core: " << message << '\n';
			tardigrade_imu.print();
			tardigrade_pressure.print();
			tardigrade_leak.print();
				
	
			//do something every second
			//sixaxis.print();
			
			//printController(&deckbox_input);

			vtClear();
			ui_timer.reset();
		}



		//raw_controller.poll(&sixaxis);
		//usleep(10);
		//convertToSixaxis(&deckbox_input, sixaxis);



	}


}


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	//std::cout << "Frontend Version " << AVOE_CLI_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe-backend-cli <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\traw\t(displays all telemtry in a crude output)\n";
	std::cout << "\ttest\t(run the test() function and quit)\n"; 


}


int main(int argc, char *argv[]){



	/* parse arguments */

	if (argc == 1){
		std::cout << "At least one arguments is required. Try ./avoe-frontend-cli help\n";
		return 0;

	}



	if (strncmp(argv[1], "help", 16) == 0){

		printHelp();
		return 0;
	

	}


	if (strncmp(argv[1], "test", 16) == 0){

		test();
		return 0;
	

	}

}
