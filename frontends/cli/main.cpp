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
#include "../../plugins/gamepad_maps/f710.h"
#include "setup.h"



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


void raw(){





}

void tardigrade_manual_control(controller_generic_profile *input, vector_t *t_vector, vector_t *r_vector, float scale){
		bool no_input = true;
		t_vector->x = 0; t_vector->y = 0; t_vector->z = 0;
		r_vector->x = 0; r_vector->y = 0; r_vector->z = 0;
		#ifdef SIXAXIS

		// translational
		if (input->dp_up){
			t_vector->x += scale;
			no_input = false;
		} 
		if (input->dp_down){
			t_vector->x -= scale;
			no_input = false;
		} 	

		if (input->dp_left){
			t_vector->y -= scale;
			no_input = false;
		} 
		if (input->dp_right){
			t_vector->y += scale;
			no_input = false;
		} 
		#endif

		#ifdef F710
		// translational
		if (input->fc_2){
			t_vector->x += scale;
			no_input = false;
		} 
		if (input->fc_3){
			t_vector->x -= scale;
			no_input = false;
		} 	

		if (input->fc_1){
			t_vector->y -= scale;
			no_input = false;
		} 
		if (input->fc_4){
			t_vector->y += scale;
			no_input = false;
		}
		//rotational	
		if (input->lt_a == 1){
			r_vector->x += scale;
			no_input = false;
		}
		if (input->rt_a == 1){
			r_vector->x -= scale;
			no_input = false;
		}
		if (input->sll_x == -1){
			r_vector->y -= scale;
			no_input = false;
		}
		if (input->sll_x == 1){
			r_vector->y += scale;
			no_input = false;
		}

		#endif 


		// ascent and descent
		if (input->lt){
			t_vector->z += scale;
			no_input = false;
		} 
		if (input->rt){
			t_vector->z -= scale;
			no_input = false;
		}


		if (no_input){

			t_vector->x = 0; t_vector->y = 0; t_vector->z = 0;
		}

}
void tardigrade_raw(){



	tardigrade_setup_sensors_virtual();
	std::cout << "[DEBUG] Setup Done\n";




	//networking setup
	avoe_comm_reciever core_to_frontend("sensor", "sensors", PORT_CORE_TELEMETRY, 2000);

	core_to_frontend.add_sensor(&tardigrade_imu);
	core_to_frontend.add_sensor(&tardigrade_pressure);
	core_to_frontend.add_sensor(&tardigrade_leak);

	core_to_frontend.set_timer(NETWORK_REFRESH_INTERVAL);
	std::cout << "AVOE Frontend CLI Test Mode\n";
	avoe_clock_t ui_timer;
	avoe_clock_t network_timer;
	
	network_timer.reset();
	ui_timer.reset();
	while(1){
		usleep(1000);
	
		core_to_frontend.refresh();

		if (ui_timer.getElaspedTimeMS() > UI_REFRESH){
			std::cout << "--AVOE deckbox-cli--\n";
			tardigrade_imu.print();
			tardigrade_pressure.print();
			tardigrade_leak.print();
				
			vtClear();
			ui_timer.reset();
		}
	}

}

void tardigrade(){
	//setup controller
	controller_t raw_controller; //raw device
	controller_generic_raw sixaxis; //virtual raw device
	controller_generic_raw f710; //virtual raw device

	controller_generic_profile deckbox_input; //virtual "refined" device

	raw_controller.setDevice(DEFAULT_CONTROLLER);
	raw_controller.init();

	tardigrade_setup_sensors_virtual();
	std::cout << "[DEBUG] Setup Done\n";


	//vector stuff

	vector_t tm_vector; //translational movement vector
	vector_t rt_vector; //rotational movement vector
	tm_vector.x = 0; tm_vector.y = 0; tm_vector.z = 0;
	rt_vector.x = 0; rt_vector.y = 0; rt_vector.z = 0;

	float movement_scale = 0.5; //default 0.5



	//networking setup
	avoe_comm_transmitter frontend_to_core("message", "vector", PORT_CORE_INPUT, IP_CORE);

	avoe_comm_reciever core_to_frontend("sensor", "telemetry", PORT_CORE_TELEMETRY, 2000);


	/* setup and initilizae all connections */	
	core_to_frontend.add_sensor(&tardigrade_imu);
	core_to_frontend.add_sensor(&tardigrade_pressure);
	core_to_frontend.add_sensor(&tardigrade_leak);
	core_to_frontend.add_motor(&thruster_SH);
	core_to_frontend.add_motor(&thruster_BSH);
	core_to_frontend.add_motor(&thruster_BPH);
	core_to_frontend.add_motor(&thruster_Y);

	

	frontend_to_core.add_vector(&tm_vector);
	frontend_to_core.add_vector(&rt_vector);
	
	core_to_frontend.set_timer(NETWORK_REFRESH_INTERVAL);
	frontend_to_core.set_timer(NETWORK_REFRESH_INTERVAL);




	std::cout << "AVOE Frontend CLI Test Mode\n";
	avoe_clock_t ui_timer;
	avoe_clock_t network_timer;
	
	network_timer.reset();
	ui_timer.reset();
	while(1){
		usleep(1000);

		core_to_frontend.refresh();
		frontend_to_core.refresh();
		// convert controller input into movement vector

		tardigrade_manual_control(&deckbox_input, &tm_vector, &rt_vector, movement_scale);

		if (ui_timer.getElaspedTimeMS() > UI_REFRESH){
			std::cout << "--AVOE deckbox-cli--\n";
			tardigrade_imu.print();
			tardigrade_pressure.print();
			tardigrade_leak.print();
				
	
			//sixaxis.print();
			//f710.print();

				
			//printController(&deckbox_input);


			std::cout << "TRANSLATIONAL MOVEMENT VECTOR: " << tm_vector.x << ' ' << tm_vector.y << ' ' << tm_vector.z << '\n';			
			std::cout << "ROTATIONAL MOVEMENT VECTOR: " << rt_vector.x << ' ' << rt_vector.y << ' ' << rt_vector.z << '\n';			
			//vtClear();
			ui_timer.reset();
		}

		//convertToSixaxis(&deckbox_input, sixaxis);
		#ifdef F710
		raw_controller.poll(&f710);
		convertToF710(&deckbox_input, f710);
		#endif

		#ifdef SIXAXIS
		raw_controller.poll(&sixaxis);
		convertToF710(&deckbox_input, sixaxis);
		#endif

	}


}


void printHelp(){

	std::cout << "AVOE version: " << AVOE_VERSION << '\n';
	//std::cout << "Frontend Version " << AVOE_CLI_VERSION << '\n';
	std::cout << "\nUSAGE:\n";
	std::cout << "\tavoe-backend-cli <mode> <arguments>\n";

	std::cout << "\nMODES:\n";
	std::cout << "\thelp\t(displays this)\n";
	std::cout << "\ttardigrade_raw\t(displays tardigrade_telemetry only)\n";
	std::cout << "\ttardigrade\t(tardigrade with full manual control)\n"; 


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
	if (strncmp(argv[1], "tardigrade_raw", 16) == 0){

		tardigrade_raw();
		return 0;
	

	}

	if (strncmp(argv[1], "tardigrade", 16) == 0){
		
		tardigrade();
		//tardigrade(argv[2]);
		return 0;
	

	}

}
