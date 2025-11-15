/*
	URI Hydrobotics
	AVOE general library

	useful functions

*/
#ifndef AVOE_LIB_H
#define AVOE_LIB_H


void initStr(char *str, int len);


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
