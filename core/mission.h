/*

	URI Hydrobotics
	AVOE mission class

	
*/

#ifndef MISSION_H
#define MISSION_H
#include "vehicle.h"
#include "config.h"
#include "../lib/lib.h"
class auv_mission_t{

	private:

		// variables to hold: current pose, current position, target pose, target position

		vector_t current_posi, target_posi, current_pose, target_pose;

		bool is_active = true; //set to false when target position and target pose are reached
		unsigned int hold_pose_duration; //length to hold target pose and position duration in seconds

		vehicle_t *vehicle;

	public:
	
	
		//initialization and control loop functions;
		void init(vector_t cposi, vector_t tposi, vector_t cpose, vector_t tpose);
		void update(vector_t cposi, vector_t cpose);
		void abort();
};

#endif
