#include <iostream>
#include "controller.h"

void controller_generic_profile::resetButtons(){

	dp_up = 0;
	dp_down = 0;
	dp_left = 0;
	dp_right = 0;
	fc_1 = 0;
	fc_2 = 0;
	fc_3 = 0;
	fc_4 = 0;
	sc_left = 0;
	sc_right = 0;
	start = 0;
	select = 0;
	super = 0; //xbox button, ps button, etc.       
	lt = 0;
	rt = 0;


}



void controller_generic_raw::setButton(int id, int val){
	button_id = id;
	button_value = val;
}

int controller_generic_raw::getButtonId(){
	return button_id;
}
int controller_generic_raw::getButtonValue(){
	return button_value;
}

void controller_generic_raw::setAxisX(int i, long val){
	axis_x[i] = val;
}

void controller_generic_raw::setAxisY(int i, long val){
	axis_y[i] = val;
}

long controller_generic_raw::getAxisX(int i){
	return axis_x[i];

}

long controller_generic_raw::getAxisY(int i){
	return axis_y[i];

}



int controller_t::read_event(){
	ssize_t bytes;

	bytes = read(js, &event, sizeof(event));

	if (bytes == sizeof(event))
		return 0;

	/* Error, could not read full event. */
	return -1;
}


size_t controller_t::get_axis_count(){
	__u8 axes;

	if (ioctl(js, JSIOCGAXES, &axes) == -1){
		return 0;
	}
	return axes;
}


size_t controller_t::get_button_count(){
	__u8 buttons;
	if (ioctl(js, JSIOCGBUTTONS, &buttons) == -1){
		return 0;
	}
	return buttons;
}

size_t controller_t::get_axis_state(){
	size_t axis = event.number / 2;

	if (axis < 3){
		if (event.number % 2 == 0)
			axes[axis].x = event.value;
		else{
			axes[axis].y = event.value;
		}
	}
	return axis;
}






void controller_t::setDevice(const char *dev){
	strncpy(device, dev, 64);
}

void controller_t::init(){	
	/* open device */
	js = open(device, O_RDONLY);
	if (js == -1){
		std::cout << "failed to open " << device <<'\n';
	}else{
		std::cout << "Opened controller at " << device << '\n';
	}

	/* set flags */

	int flags = fcntl(js, F_GETFL, 0);
	fcntl(js, F_SETFL, flags | O_NONBLOCK);


	struct timeval timeout={0, CONTROLLER_TIMEOUT};  //tv_sec, tv_usec
	setsockopt(js, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,sizeof(struct timeval));



}

void controller_t::poll(controller_generic_raw *gamepad){
	//std::cout << "polling\n";
	read_event(); //read event
	switch (event.type){
		/* for testing*/
		case JS_EVENT_BUTTON:
			//printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
			gamepad->setButton((int) event.number,(int) event.value);
			break;
		case JS_EVENT_AXIS:
			axis = get_axis_state();
			if (axis < 3){
				//printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
				gamepad->setAxisX(axis, axes[axis].x);
				gamepad->setAxisY(axis, axes[axis].y);
			}
			break;
		default:
			break; //ignore
	}



}


void controller_t::closeFD(){
	close(js);		
}	




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


void fillControllerBuffer(controller_generic_profile in, char *buffer, int len){

	// needs to be reworked heavily	

	std::string str;
	/* buttons*/
	int button[15];
	
	button[0] = in.dp_up;
	button[1] = in.dp_down;
	button[2] = in.dp_left;
	button[3] = in.dp_right;
	button[4] = in.fc_1;
	button[5] = in.fc_2;
	button[6] = in.fc_3;
	button[7] = in.fc_4;
	button[8] = in.sc_left;
	button[9] = in.sc_right;
	button[10] = in.lt;
	button[11] = in.rt;
	button[12] = in.start;
	button[13] = in.select;
	button[14] = in.super;


	for (int i = 0; i < 15; i++){
		str += button[i] + 48; //turns base int into ASCII char

	}


	/* sticks */
	/*
     	double sll_x, sll_y; // stick_location_left_*
        double slr_x, slr_y; // stick_location_right_*  
        double lt_a, rt_a;
 

	


	*/
	str += ' '; // add space 

	std::string sll_x_str, sll_y_str, slr_x_str, slr_y_str, lt_a_str, rt_a_str;
	sll_x_str = std::to_string(in.sll_x);	
	sll_y_str = std::to_string(in.sll_y);
	slr_x_str = std::to_string(in.slr_x);
	slr_y_str = std::to_string(in.slr_y);
	lt_a_str = std::to_string(in.lt_a);
	rt_a_str = std::to_string(in.rt_a);

	str += sll_x_str; str += ' ';
	str += sll_y_str; str  += ' ';
	str += slr_x_str; str += ' ';	
	str += slr_y_str; str += ' ';	
	str += lt_a_str; str += ' ' ;
	str += rt_a_str; str += ' ' ;

	strncpy(buffer, str.c_str(), len);
	//std::cout << str << '\n';

	buffer[len - 1] = 0; //terminate the string
}

