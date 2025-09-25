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

		char data[512];	
		/* positioning */

		vector_t offset; //position offset from center of vehicle in mm


	public:

	sensor_t(){

	}

	void init(const char *m, const char *v, const char *p, const char *t){

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

	char *read(){
		return data;

	}

	void init(){

		state = 0;
		//tells sensors.h that intilization is ready
		
	}

	int getState(){
		
		return state;

	}


	void write(char *input){
		strncpy(data, input, 512);
		
	}

	/*
	void log(log_t *log){
		//	automatically log all values to a log_t 
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

	*/
};
