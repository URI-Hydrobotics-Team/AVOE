/*

	URI Hydrobotics
	AVOE clock class
	
	Clocks are important for timing certain events. Clocks should be associtaed with vehicle_t


*/

#include <time.h>

class avoe_clock_t{


	private:

		clock_t timer;

	public:




		int getElaspedTimeMS(){
			clock_t t = clock() - timer;
			return (t * 100000 / CLOCKS_PER_SEC);


		}


		void reset(){

			timer = clock();
		}

		char* getTimeStr(){

			char *time_str = ctime(&timer);
			time_str[strlen(time_str) - 1] = 0;
			return time_str;

		}


};
