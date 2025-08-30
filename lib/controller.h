/*
	AVOE linux joystick abstraction layer
	URI Hydrobtoics
	Christopher McRae


*/




#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

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

		void resetButtons(){


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

		
};

class controller_generic_raw{

	private:
		int button_id, button_value;
		long axis_x[4];
		long axis_y[4];

	public:
		void setButton(int id, int val){
			button_id = id;
			button_value = val;
		}

		int getButtonId(){
			return button_id;
		}
		int getButtonValue(){
			return button_value;
		}

		void setAxisX(int i, long val){
			axis_x[i] = val;
		}

		void setAxisY(int i, long val){
			axis_y[i] = val;
		}

		long getAxisX(int i){
			return axis_x[i];

		}

		long getAxisY(int i){
			return axis_y[i];

		}

		void print(){
			std::cout << "Button: " << button_id << ' ' << button_value << '\n';

			for (int i = 0; i < 4; i++){
				std::cout << "Stick: " << i << "X, Y: " << axis_x[i] << ", " << axis_y[i] << '\n';
		
			}

		}


};




class controller_t {


	private:
		char device[64];
    		int js;
    		struct js_event event;
    		size_t axis;
	

    		struct axis_state axes[3] = {0};
		
	public:


	int read_event(){
    		ssize_t bytes;

    		bytes = read(js, &event, sizeof(event));

    		if (bytes == sizeof(event))
        		return 0;

    			/* Error, could not read full event. */
    			return -1;
	}


	size_t get_axis_count(){
    		__u8 axes;

    		if (ioctl(js, JSIOCGAXES, &axes) == -1){
        		return 0;
		}
   		 return axes;
	}


	size_t get_button_count(){
    		__u8 buttons;
    		if (ioctl(js, JSIOCGBUTTONS, &buttons) == -1){
        		return 0;
		}
    		return buttons;
	}

	size_t get_axis_state(){
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






	void setDevice(const char *dev){
		strncpy(device, dev, 64);
	}

	void init(){	
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


		struct timeval timeout={0,CONTROLLER_TIMEOUT};  //tv_sec, tv_usec
		setsockopt(js, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,sizeof(struct timeval));



	}

	void poll(controller_generic_raw *gamepad){
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



	void closeFD(){
		close(js);		
	}	
	
		




};


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


