/*

	URI Hydrdobotics
	AVOE sensor class

	Sensor drivers will interface with each sensor object. The vehicle class will hold sensor objects and provide an interface for accessing them.

*/





class sensor_t{

	private:
		char model[32];
		char vendor[32];
		char protocol[16];
		char type[32]; 
		int state = 0; //0 = uninit. , 1 = ready		

		char variable_names[MAX_SENSOR_ENTRIES][64];
		char values[MAX_SENSOR_ENTRIES][64];
	public:

	sensor_t(){

	}

	void init(char *m, char *v, char *p, char *t){

		strncpy(model, m, 32);
		strncpy(vendor, v, 32);
		strncpy(protocol, p, 16);
		strncpy(type, t, 16);

	}


	char *getModel(){
		return model;
	}

	char *getVendor(){
		return vendor;
	}

	char *getProtocol(){
		return protocol;
	}

	char *getType(){
		return type;
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

	void init(){

		state = 0;
		//tells sensors.h that intilization is ready
		
	}

	int getState(){
		
		return state;

	}

	void log(log_t *log){
		/* automatically log all values to a log_t */
		std::string entry = "";
		for (int i = 0; i < MAX_SENSOR_ENTRIES; i++){
			entry += variable_names[i];
			entry += ' ';
			entry += values[i];
			log->log(entry.c_str());
			entry = "";

		}
		
	}

	void print(){

		std::cout << "\t\tMODEL: " << model << '\n';
                std::cout << "\t\tVENDOR: " << vendor << '\n';
                std::cout << "\t\tPROTOCOL: " << protocol << '\n';


	}



};
