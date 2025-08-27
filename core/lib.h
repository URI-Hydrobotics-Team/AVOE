/*
	URI Hydrobotics
	AVOE general library

	useful functions

*/


void initStr(char *str, int len){
	/* initiate a string with a series of null terminators */
	for (int i = 0; i < len; i++){
		str[i] = 0;
	}
}



class vector_t{
	//vector for 3d space
	public:
		double x;
		double y;
		double z;	

};

