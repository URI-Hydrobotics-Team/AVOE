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

		
		//external trigger variable?
		vector_t offset, pose1, pose2; //relative, not absolute
		vector_t heading; 

		bool is_active = true; //set to false when target position and target pose are reached
		enum mode {
			DEFINITE, 
			INDEFINITE
		};
		unsigned int hold_pose_duration; //length to hold target pose and position duration in seconds
		
		vehicle_t *vehicle;

	public:
	
	
		//initialization and control loop functions;
		void init(vector_t cposi, vector_t tposi, vector_t cpose, vector_t tpose);
		void update(vector_t cposi, vector_t cpose);
		void abort();
};

#endif
