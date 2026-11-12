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

	int len = strlen(addition); //length of string to add;
	int end = len + index; //where to end
	// end - index = where to end - where to start 


	int increment = 0;
	for (int i = 0; i < (end - index); i++){
		base[index + i + increment] = addition[i];
	}

	base[end] = '\0';
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

void vector_t::zero(){

	x = 0.0;
	y = 0.0;
	z = 0.0;

}



int avoe_parse_config_line(const char *input, char *field_, char *token_){
	
	char field[FIELD_SIZE];
	char token[FIELD_SIZE];
	memset(field, 0, FIELD_SIZE);
	memset(token, 0, FIELD_SIZE);

	size_t index = 0;
	size_t temp_index = 0;

	char c;
	
	c = input[index];

	int field_token = 0;
	while (c != ';'){
		//printf("%c ", c);	
		if (c == ' '){
			//space detected, throw error

			printf("space detected\n");
			return -1;
		}
		
		if (c == '#'){
			//comment
			return -1;
		}

		if (c == '='){
			field_token = 1;
			temp_index = 0;	
			index++;
			c = input[index];
			continue;

		}

		if (field_token == 0){
			field[temp_index] = c;
		}

		if (field_token == 1){
			token[temp_index] = c;
		}
		
		if (temp_index > FIELD_SIZE){
			// error
			return -1;
		}

	


		temp_index++;
		index++;
		c = input[index];
	}


	strncpy(field_, field, FIELD_SIZE);
	strncpy(token_, token, FIELD_SIZE);
	return 0; //GOOD
}

