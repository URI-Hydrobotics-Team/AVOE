/* functions for DEC VT100 escape codes */

void vtClear(){
	/* clear screen */
	printf("\033[H\033[J");

}


void vtGoto(int x, int y){
	printf("\033[%d;%dH", y, x);

}

