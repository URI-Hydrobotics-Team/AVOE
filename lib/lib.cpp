#include "lib.h"


void initStr(char *str, int len){
	// initiate a string with a series of null terminators 
	for (int i = 0; i < len; i++){
		str[i] = 0;
	}
}

