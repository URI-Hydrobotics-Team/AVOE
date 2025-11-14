/*

	URI Hydrobotics
	AVOE mission class

	
*/

#ifndef MISSION_H
#define MISSION_H

#include "vehicle.h"
#include "config.h"
class auv_mission_t{

	private:

		// variables to hold: current pose, current position, target pose, target position

		double curr_pose_r, curr_pose_p, curr_pose_y;
		double target_pose_r, target_pose_p, target_pose_y;
		double curr_x, curr_y, curr_z;
		double target_x, target_y, target_z;
		

		bool is_active = true; //set to false when target position and target pose are reached
		int hold_pose_duration; //length to hold pose duration in seconds

		vehicle_t *vehicle;

	public:
	
	
		//initialization and control loop functions;
		void init(vehicle_t *v, vector_t curr_pose, vector_t curr_posi, vector_t target_pose, vector_t target_posi);
		void update();
		void stop();
};

#endif
