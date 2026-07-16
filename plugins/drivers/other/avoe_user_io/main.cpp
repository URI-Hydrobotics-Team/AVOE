#include "driver.h"
#include <iostream>
#include <unistd.h>
#include "../../../../lib/clock.h"


#define LED0 20
#define LED1 21
#define LED2 12
#define LED3 16

int main(){

	avoe_clock_t timer;
	int counter = 0;
	int direction = 1;
	avoe_user_io tardigrade_leds;
	tardigrade_leds.init(false);

	tardigrade_leds.add_output(LED1, "one", 0);
	tardigrade_leds.add_output(LED2, "two", 0);
	tardigrade_leds.add_output(LED3, "three", 0);
	tardigrade_leds.add_output(LED0, "zero", 0);

		tardigrade_leds.write("zero", 0);
		tardigrade_leds.write("one", 0);
		tardigrade_leds.write("two", 0);
		tardigrade_leds.write("three", 0);


	timer.reset();

	while(1){
		usleep(1000);
		if (timer.getElaspedTimeMS() > 100){
		tardigrade_leds.write("zero", 0);
		tardigrade_leds.write("one", 0);
		tardigrade_leds.write("two", 0);
		tardigrade_leds.write("three", 0);
		switch(counter){
			case 0:
		tardigrade_leds.write("zero", 1);
				break;

			case 1:
		tardigrade_leds.write("one", 1);
				break;

			case 2:
		tardigrade_leds.write("two", 1);
				break;
			case 3:
		tardigrade_leds.write("three", 1);
				break;


		}
		if ((counter < 3 && direction == 1) ||(counter > 0 && direction == -1)){
			counter += direction;
			if (counter == 3 || counter == 0){
				direction *=-1;
			}
		}else{
			direction *= -1;
		}
			timer.reset();
		}
	
	}
    
}
