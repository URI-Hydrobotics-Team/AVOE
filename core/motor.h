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
	
		char variable_names[MAX_SENSOR_ENTRIES][64];
		char values[MAX_SENSOR_ENTRIES][64];
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


	int setValue(char *name, char *value){
		int index;

		for (int i = 0; i < MAX_SENSOR_ENTRIES; i++){
			if (strncmp(name, variable_names[i], 64) == 0){
				// found name
				index = i;
			}else{
				return 0; //error
				
			}
			//clear value first
			strncpy(values[index], value, 64);

			return 1;
		}

	}




};
