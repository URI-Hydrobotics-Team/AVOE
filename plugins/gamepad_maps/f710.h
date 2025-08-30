/* 

	AVOE
	URI Hydrobotics
	definitions for Logitech's F710 controller 


*/
	

/*
observations

D-PAD (no bindings)
	UP		
	DOWN	
	LEFT	
	RIGHT	
	
FACE-BUTTONS
	A	B0
	B	B1
	X	B2
	Y	B3

TRIGGERS
	L1	B4
	L2	A1
	R1	B5
	R2	A2

STICKS
	LCLICK	B9
	L	A0
	RCLICK	B10
	R	A1/A2

OTHER
	SUPER	B8
	SELECT	B6
	START	B7

*/



void convertToF710(controller_generic_profile *out, controller_generic_raw in){
	out->resetButtons();
	/* button */

	if (in.getButtonValue() == 1){
	switch (in.getButtonId()){
		case 0:
			out->fc_1 = 1;
			break;
		case 1:
			out->fc_2 = 1;
			break;
		case 2:
			out->fc_3 = 1;
			break;
	
		case 3:
			out->fc_4 = 1;
			break;
		case 4:
			out->lt = 1;
			break;

		case 5:
			out->rt = 1;
			break;
		case 6:
			out->select = 1;
			break;
	
		case 7:
			out->start = 1;
			break;

		case 8:

			out->super = 1;
			break;
		case 9:

			out->sc_left = 1;
			break;
		case 10:
			out->sc_right = 1;
			break;

	
		}

	
	}
	/* set sticks */
	out->sll_x = (0.0 + in.getAxisX(0)) / 32767;
	out->sll_y = (0.0 + in.getAxisY(0)) / 32767;
	
	out->slr_x = (0.0 + in.getAxisY(1)) / 32767;
	out->slr_y = (0.0 + in.getAxisX(2)) / 32767;
	
	/* analog triggers */
	out ->lt_a =  (0.0 + in.getAxisX(1)) / 32767;
	out ->rt_a =  (0.0 + in.getAxisY(2)) / 32767;

}


