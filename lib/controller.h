/*
	AVOE linux joystick abstraction layer
	URI Hydrobtoics
	Christopher McRae


*/




#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <cstring>
#include <sys/socket.h>
#include <cstdint>


#define DEFAULT_CONTROLLER "/dev/input/js0"
#define CONTROLLER_TIMEOUT 10000

struct axis_state {
    	short x, y;
};






class controller_generic_profile{
	public:

		/* d-pad */
		int dp_up = 0;
		int dp_down = 0;
		int dp_left = 0;
		int dp_right = 0;

		/* face buttons */

		int fc_1 = 0;
		int fc_2 = 0;
		int fc_3 = 0;
		int fc_4 = 0;

		/* stick click*/
		
		int sc_left = 0;
		int sc_right = 0;
		
		/* triggers */
		int lt = 0;
		int rt = 0;
	
		
		/*other buttons */
		int start = 0;
		int select = 0;
		int super = 0; //xbox button, ps button, etc.		

		/* sticks (val: 0 - 1)*/ 
		double sll_x, sll_y; // stick_location_left_*
		double slr_x, slr_y; // stick_location_right_*

		/* analog triggers */
		double lt_a, rt_a;


		void resetButtons();
		
};

class controller_generic_raw{

	private:
		int button_id, button_value;
		long axis_x[4];
		long axis_y[4];

	public:
		void setButton(int id, int val);

		int getButtonId();
		int getButtonValue();
		void setAxisX(int i, long val);
		void setAxisY(int i, long val);
		long getAxisX(int i);
		long getAxisY(int i);
		void print();

};




class controller_t {


	private:
		char device[64];
    		int js;
    		struct js_event event;
    		size_t axis;

    		struct axis_state axes[3] = {0};
		
	public:


	int read_event();


	size_t get_axis_count();

	size_t get_button_count();
	size_t get_axis_state();
    
	void setDevice(const char *dev);
	void init();
	void poll(controller_generic_raw *gamepad);
	void closeFD();
	
};


void fillControllerBuffer(controller_generic_profile in, char *buffer, int len);


void printController(controller_generic_profile *deckbox_input);
