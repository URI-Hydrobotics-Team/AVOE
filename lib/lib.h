/*
	URI Hydrobotics
	AVOE general library

	useful functions

*/
#ifndef AVOE_LIB_H
#define AVOE_LIB_H

#include <cstdio>


bool charIsInt(char c);
void initStr(char *str, int len);
int countNonZero(char *str, int len);
void appendStr(char *base, const char *addition, int index);
int countChar(char *str, int key);
void strncmpExclude(char *dest, const char *src, int key, int len);
void readLine(char *buffer, int len, FILE *fptr);


struct vector_t{
	//vector for 3d space
	double x;
	double y;
	double z;	
};

struct vector4_t{
	//vector for 4d space
	double x;
	double y;
	double z;	
	double i;	
};




#endif
