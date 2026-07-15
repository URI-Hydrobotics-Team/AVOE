#include <driver.h>
#include <AVOE_USER_IO>
#include <iostream>


#define LED0 1
#define LED1 0
#define LED2 2
#define LED3 3

void main(){


	

	avoe_user_io tardigrade_leds;
	tardigrade_leds.init(false);

	tardigrade_leds.add_output(LED1, "one", 0);
	tardigrade_leds.add_output(LED2, "two", 0);
	tardigrade_leds.add_output(LED3, "three", 0);
	tardigrade_leds.add_output(LED0, "zero", 0);



	tardigrade_leds.write("zero", 1);
	tardigrade_leds.write("one", 1);
	tardigrade_leds.write("two", 1);
	tardigrade_leds.write("three", 1);
	while(1){
		
		usleep(1000);
	}
    
{
