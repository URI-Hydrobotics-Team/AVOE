/*

	URI Hydrobotics
	AVOE clock class
	
	Clocks are important for timing certain events. Clocks should be associtaed with vehicle_t


*/

#include <time.h>

class stopwatch_t{


	private:

		clock_t timer;

	public:




		float getElaspedTime(){
			clock_t t = clock() - timer;
			return ((float)t)/CLOCKS_PER_SEC;


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
