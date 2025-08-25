#include "driver.h"
#include <unistd.h>
/* an example use case for driver.h */
/* driver.h will be a dependency for AUV HUB */

void test(){
	std::cout << "BNO055 Demo\n";
	BNO055 imu_module;
	imu_module.cold_init();
	int8_t temp = imu_module.get_temperature();
	std::cout << (int)temp << '\n';
	

	imu::Vector<3> orient = imu_module.get_Euler_Orientation();

	while (1){
		usleep(500000);

		orient = imu_module.get_Euler_Orientation();
		std::cout << " X: " << orient.x() << " Y: " << orient.y() << " Z: " << orient.z() << '\n';
	}
}



int main(){

	test();
	return 0;
}
