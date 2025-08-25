/* Devin's leak sensor code implemented as a header file that can be included into other projects */
#include <iostream>
#include <wiringPi.h>
#define LEAK_PIN 17 // Use the actual GPIO pin you connected to


class leak_sensor_t{

	private:
		


	public:

		void cold_init(){
		
			wiringPiSetupGpio();
			pinMode(LEAK_PIN, INPUT); // Set the leak sensor pin as input
    			pullUpDnControl(LEAK_PIN, PUD_DOWN); // Enable pull-down resistor

		}

		void init(){
			pinMode(LEAK_PIN, INPUT); // Set the leak sensor pin as input
			pullUpDnControl(LEAK_PIN, PUD_DOWN); // Enable pull-down resistor


		}		

		int probe(){
			//probe the sensor
			if (digitalRead(LEAK_PIN) == HIGH){
				return 1;
			}else{
				return 0;
			}
	
		}







};
