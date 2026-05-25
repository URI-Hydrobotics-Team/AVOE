#include "driver.h"
#include <pigpio.h>


avoe_user_io::avoe_user_io(){

	//init strings
	for (int i = 0; i < AVOE_USER_IO_DEVICES; i++){
		initStr(labels[i], AVOE_USER_IO_LABEL_SIZE);
	}
	entries = 0;

}

avoe_user_io::~avoe_user_io(){

}


void avoe_user_io::init(bool gpio_is_init){

	if (!gpio_is_init){
		gpioInitialise();
	}
}

void avoe_user_io::add_output(uint8_t pin, const char *label, int8_t pull){
	if (pull != -1 || pull != 0 || pull != 1){
		std::cout << "[USER IO] Invalid Pull Up/Down Value\n";
		return;
	}



	strncpy(labels[entries], label ,AVOE_USER_IO_LABEL_SIZE);
	pins[entries] = pin;
	pull_status[entries] = pull;

	gpioSetMode(pin, PI_OUTPUT);



	switch (pull){
		case -1:
			gpioSetPullUpDown(pin, PI_PUD_DOWN);
			break;

		case 0:
			gpioSetPullUpDown(pin, PI_PUD_OFF);
			break;

		case 1:
			gpioSetPullUpDown(pin, PI_PUD_UP);
			break;
	}


	entries++;

	std::cout << "[USER IO] Added output " << pin << " as " << label << '\n';
}

void avoe_user_io::add_input(uint8_t pin, const char *label, int8_t pull){
	if (pull != -1 || pull != 0 || pull != 1){
		std::cout << "[USER IO] Invalid Pull Up/Down Value\n";
		return;
	}



	strncpy(labels[entries], label ,AVOE_USER_IO_LABEL_SIZE);
	pins[entries] = pin;
	pull_status[entries] = pull;

	gpioSetMode(pin, PI_INPUT);



	switch (pull){
		case -1:
			gpioSetPullUpDown(pin, PI_PUD_DOWN);
			break;

		case 0:
			gpioSetPullUpDown(pin, PI_PUD_OFF);
			break;

		case 1:
			gpioSetPullUpDown(pin, PI_PUD_UP);
			break;
	}


	entries++;

	std::cout << "[USER IO] Added input " << pin << " as " << label << '\n';


}



uint8_t avoe_user_io::read(const char *label){

	for (int i = 0; i < entries; i++){
		if (strncmp(label,labels[i], AVOE_USER_IO_LABEL_SIZE) == 0){
			
			return gpioRead(pins[i]);
		}

	}

	std::cout << "[USER IO] No Output " << label << '\n';
	return 255;

}






void avoe_user_io::write(const char *label, uint8_t val){


	for (int i = 0; i < entries; i++){
		if (strncmp(label,labels[i], AVOE_USER_IO_LABEL_SIZE) == 0){
			
			gpioWrite(pins[i], val);
		}

	}

	std::cout << "[USER IO] No Input " << label << '\n';

}
