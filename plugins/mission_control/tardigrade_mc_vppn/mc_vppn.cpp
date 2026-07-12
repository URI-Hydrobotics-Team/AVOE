#include "mc_vppn.h"



//tardigrade_mc_vppn_t::tardigrade_mc_vppn_t();
//tardigrade_mc_vppn_t::~tardigrade_mc_vppn_t();


void tardigrade_mc_vppn_t::init(vppn_mission_t *vppn_main_object, vppn_mission_t *vppn_dr_object, size_t vppn_main_object_len_, size_t vppn_dr_object_len_, char *keyword_str_raw_, size_t keyword_str_raw_len_, vector_t *output_translational_vector_, vector_t *output_lateral_vector_){

	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	vppn_main_object_len = vppn_main_object_len_;
	vppn_dr_object_len = vppn_dr_object_len_;
	keyword_str_raw = keyword_str_raw_;
	keyword_str_raw_len = keyword_str_raw_len_;
	output_translational_vector = output_translational_vector_;
	output_lateral_vector = output_lateral_vector_;
	main_clock.reset();
	adjustment_timer.reset();
	scan_timer.reset();
}


void tardigrade_mc_vppn_t::sweep_and_scan(int angle){
	std::cout << "[TARDIGRADE MC VPPN] sweep and scan started for " << angle << " degrees"<< '\n';




}




void tardigrade_mc_vppn_t::reset(){
	vppn_main_object_index = 0;
	vppn_dr_object_index = 0;
	global_state = TARDIGRADE_MC_VPPN_GLOBAL_STATE_RESET;
	paused = false;
}



void tardigrade_mc_vppn_t::start(){
	global_state = TARDIGRADE_MC_VPPN_GLOBAL_STATE_SCAN; // scan initially

}
void tardigrade_mc_vppn_t::kill(){
	global_state = TARDIGRADE_MC_VPPN_GLOBAL_STATE_STOP; //killed
	vector_t zero_vector(0,0,0);
	controller->send_lateral_vector(zero_vector);
	controller->send_translation_vector(zero_vector);

	paused = true;
}


void tardigrade_mc_vppn_t::resume(){
	paused = false;

}



void tardigrade_mc_vppn_t::refresh(){

	vector_t output_temp(0, 0, 0);

	/*
	   read from keyword
	   determine if keyword matches
	   adjust output vector as necessary

	   handle no match case

	 */

	//offset_vector.x and offset_vector.y define the pixel offsets RXed from CV


	//check timers

	if (adjustment_timer.getElaspedTimeMS() > TARDIGRADE_MC_VPPN_ADJUST_TIME && local_state == TARDIGRADE_MC_VPPN_LOCAL_STATE_ADJUSTING){
		//done adjusting course, switch back to following course
		local_state = TARDIGRADE_MC_VPPN_LOCAL_STATE_FOLLOWING;


	}

	//extract offset from keyword
	int cv_x_offset;
	int cv_y_offset;
	// determine if we should dead reckon
	bool dead_reckon = !(strncmp(keyword_str_raw, vppn_main_object_ptr[vppn_main_object_index].keyword, vppn_main_object_ptr[vppn_main_object_index].keyword_len) == 0);
	//this comparison is too simple
	//false if match, true if no
	

	dead_reckon = dead_reckon * (main_clock.getElaspedTimeMS() > TARDIGRADE_MC_VPPN_DEAD_RECKON_DELAY) * !paused;

	if (!dead_reckon && global_state == TARDIGRADE_MC_VPPN_GLOBAL_STATE_RUNNING){
		
		main_clock.reset(); // update clock everytime we check and get a match




		float speed = vppn_main_object_ptr[vppn_main_object_index].speed;


		if (cv_x_offset > TARDIGRADE_MC_VPPN_PIXEL_BUFFER && local_state != TARDIGRADE_MC_VPPN_LOCAL_STATE_ADJUSTING){

			

			float yaw_adjustment = 1.0 * cv_x_offset / TARDIGRADE_MC_VPPN_CV_RESOLUTION_X;
			vector_t adjustment;
			adjustment.x = 0;
			adjustment.y = 0 ;
			adjustment.z =  yaw_adjustment; //YAW

			controller->send_lateral_vector(adjustment);
	
			adjustment_timer.reset();
			local_state = TARDIGRADE_MC_VPPN_LOCAL_STATE_ADJUSTING;
		}

		if (local_state == TARDIGRADE_MC_VPPN_LOCAL_STATE_FOLLOWING){
			//following course

			vector_t course;
			//define course here
			course.x = 0;
			course.y = speed;
			course.z = 0;

			controller->send_translation_vector(course);
			
		}

	
	}else if (global_state == TARDIGRADE_MC_VPPN_GLOBAL_STATE_RUNNING){

		//dead reckon now
		
		/*
		get vars from dr object and send scan signal
		*/	


	
	}


	//determine if we should bump mission index for main and dr	



}

/*

void CVTranslation(const char* CVData, size_t mode){
	char temp_str[strlen(CVData)];
	if(mode == 1){
		//Virtual
		size_t objCounter = 0;
		size_t barCount = 0;
		size_t temp_index = 0;

		char name[32];
		uint16_t duration;
		float speed;
		vector_t translation_vector, lateral_movement;

		for(size_t i = 0; i < strlen(CVData); i++){
			initStr(temp_str,32);
			if(objCounter == 0 || CVData[i] == ':'){
				if (barCount == 0){
					name = std::stod(temp_str);
					temp_index = 0;
					initStr(temp_str, 32);
				}

				if (barCount == 1){
					y = std::stod(temp_str);
					temp_index = 0;
					initStr(temp_str, 32);
				}

				if (barCount == 2){
					z = std::stod(temp_str);
					temp_index = 0;
					initStr(temp_str, 32);
				break;
				}
				objCounter++;
				temp_str[temp_index] = str[i];
				temp_index++;
			}
		}
	}else if (mode == 2){
		//Physical
	}else{
		fprintf(stderr,"Please enter a correct mode (1(Virtual),2(Physical))\n");
	}
}

*/