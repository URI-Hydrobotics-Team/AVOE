/* 
	AVOE definitions for Sony's SIXAXIS controller 
	URI Hydrobotics
*/

/*
observations

D-PAD
	UP	B13
	DOWN	B14
	LEFT	B15
	RIGHT	B16
	
FACE-BUTTONS
	T	B2
	S	B3
	C	B1
	X	B0

TRIGGERS
	L1	B4
	L2	A1/B6
	R1	B5
	R2	A2/B7

STICKS
	LCLICK	B11
	L	A0
	RCLICK	B12
	R	A1/A2

OTHER
	PS	B10
	SELECT	B8
	START	B9

*/



void convertToSixaxis(controller_generic_profile *out, controller_generic_raw in){
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
			out->lt_a = 1;
			break;
	
		case 7:
			out->rt_a = 1;
			break;

		case 8:

			out->select = 1;
			break;
		case 9:

			out->start = 1;
			break;
		case 10:
			out->super = 1;
			break;

		case 11:
			out->sc_left = 1;
			break;

		case 12:
			out->sc_right = 1;
			break;
		case 13:
			out->dp_up = 1;
			break;
		case 14:
			out->dp_down = 1;
			break;

		case 15:
			out->dp_left = 1;
			break;
		case 16:
			out->dp_right = 1;
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

