#include "lib.h"
#include <cstring>
#include <string>
#include <iostream>


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








vector_t comma_str_to_vector_t(const char *str, size_t n){

	double x;
	double y;
	double z;

	// Allocate n size memory to prevent stack buffer overflow
	char temp_str[n];
	size_t temp_index = 0;
	short comma_count = 0;
	
	initStr(temp_str, 32);

	if (!charIsInt(str[0]) && (str[0] != '-')){

		vector_t ret_val(0.0, 0.0, 0.0);
		return ret_val;



	}

	for (size_t i = 0; i < n; i++){

		if(str[i] == ','){

			if (comma_count == 0){
				x = std::stod(temp_str);
				temp_index = 0;
				initStr(temp_str, 32);
			}

			if (comma_count == 1){
				y = std::stod(temp_str);
				temp_index = 0;
				initStr(temp_str, 32);
			}

			if (comma_count == 2){
				z = std::stod(temp_str);
				temp_index = 0;
				initStr(temp_str, 32);
				break;
			}

			comma_count++;
			continue;
		}


		temp_str[temp_index] = str[i];
		temp_index++;

	}


	vector_t ret_val(x, y, z);
	return ret_val;


}



