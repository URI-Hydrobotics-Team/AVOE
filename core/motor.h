/*

	URI Hydrdobotics
	AVOE motor class

	motor objects work very similary to sensor objects
*/





class motor_t{

	private:
		char name[32];
		char vendor[32];
		char protocol[16];
		int type; 


		vector_t position;
		vector_t direction;		
		float *force_func;

		char data[512];			
	
	public:

	motor_t(){

	}

	void init(char *n, char *v, char *p){

		strncpy(name, n, 32);
		strncpy(vendor, v, 32);
		strncpy(protocol, p, 16);

	}


	char *getName(){
		return name;
	}

	char *getVendor(){
		return vendor;
	}

	char *getProtocol(){
		return protocol;
	}


	char *read(){

		return data;
	}

	void write(const char *input){
		strncpy(data, input, 512);


	}



};
