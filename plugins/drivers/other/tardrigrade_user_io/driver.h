#include <cstring.h>
#include "lib.h"



#ifndef AVOE_USER_IO
#define AVOE_USER_IO

#define AVOE_USER_IO_DEVICES 64
#define AVOE_USER_IO_LABEL_SIZE 32


class avoe_user_io{


	private:
		size_t entries;		
		char labels[AVOE_USER_IO_DEVICES][AVOE_USER_IO_LABEL_SIZE];
		uint8_t pins[AVOE_USER_IO_DEVICES];
		int8_t pull_status[AVOE_USER_IO_DEVICES];
		


	public:

		user_io;
		~user_io;
		void init(bool gpio_is_init);
		void add_output(uint8_t pin, const char *label, int8_t pull);
		void add_input(uint8_t pin, const char *label, int8_t pull);
		uint8_t read(const char *label);
		void write(const char *label, uint8_t val);

		


};


#endif
