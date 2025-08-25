/* Devin's leak sensor code implemented as a header file that can be included into other projects */
#include <iostream>
#include <pigpio.h>
#define LEAK_PIN 17 // Use the actual GPIO pin you connected to


class leak_sensor_t{

	private:
		


	public:

		void fullInit(){
		
			if(gpioInitialise() == PI_INIT_FAILED){
				std::cout << "Failed to init pigpio\n";
				return false;
			}

			init();
		}

		void init(){
			gpioSetMode(LEAK_PIN, PI_INPUT); // Set the leak sensor pin as input
			gpioSetPullDown(LEAK_PIN, PI_PUD_DOWN); // Enable pull-down resistor


		}		

		int probe(){
			//probe the sensor
			if (gpioRead(LEAK_PIN) > 0){
				return 1;
			}else{
				return 0;
			}
	
		}



};
