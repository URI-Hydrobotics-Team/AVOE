/*
	AVOE keyboard backend
	URI Hydrobotics
	Christopher McRae

	gets raw keyboard input from /dev/input/event0
	not an ideal way of getting keyboard input but is functional

*/

#include <linux/input.h>



class keyboard_t{
	private:
		int fd;
		struct input_event ev;


	public:

		void init(){
			fd = open("/dev/input/event0", O_RDONLY);
			if (fd == -1){
				std::cout << "Error opening keyboard\n";
			}


			int flags = fcntl(fd, F_GETFL, 0);
			fcntl(fd, F_SETFL, flags | O_NONBLOCK);

		}	
	

		int getCode(){
  			ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
        		if (bytes == -1) {
            			//perror("Error reading event");
        		}

        		if (bytes == sizeof(struct input_event)) {
            			 //printf("type %d, code %d, value %d\n",ev.type, ev.code, ev.value);
				return ev.value;
			}else{
				return 0;
			}

		}

		int closefd(){
			close(fd);

		}

};

