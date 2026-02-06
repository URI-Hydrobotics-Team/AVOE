#include "lib.h"
#include <cstring>


bool charIsInt(char c){
	if (c > 47 && c < 58){
		return true;
		
	}

	return false;

}




void initStr(char *str, int len){
	/* initiate a string with a series of null terminators */
	for (int i = 0; i < len; i++){
		str[i] = 0;
	}
}


int countNonZero(char *str, int len){
	int count = 0;
	for (int i = 0; i < len; i++){
		if (str[i] > 0){
			count++;
		}
	}
	return count;
	
}


void appendStr(char *base, const char *addition, int index){

	int len = strlen(addition); //length of string to add
	int end = len + index; //where to end
	// end - index = where to end - where to start 


	int increment = 0;

	for (int i = 0; i < (end - index); i++){
		base[index + i + increment] = addition[i];
	}

}

int countChar(char *str, int key){
	//checks if single char. key is in str
	int count = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i] == key){

			count++;
		}
	}
	return count;

}

void strncmpExclude(char *dest, const char *src, int key, int len){
	int j = 0;
	for (int i = 0; i < len; i++){
		
		if (src[i] != key){
			dest[j] = src[i];
			j++;
		}
	}
}


void readLine(char *buffer, int len, FILE *fptr){

	/* assume start of line, read using fgetc until '\n' reached, stop there or when len */
	char c;
	for (int i = 0; i < len; i++){
		c = fgetc(fptr);	
		if (c == '\n' || i == len){
			//terminate and fuck off
			buffer[i] = 0;
			break;

		}

		buffer[i] = c;		
	}

}


vector_t::vector_t(double X, double Y, double Z){

	x = X;
	y = Y;
	z = Z;
	
}


vector_t::vector_t(){

	x = 0.0;
	y = 0.0;
	z = 0.0;
	
}
