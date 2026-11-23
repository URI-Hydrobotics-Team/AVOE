#include "vt100.h"


void vtClear(){
	/* clear screen */
	printf("\033[H\033[J");

}


void vtGoto(int x, int y){
	//printf("\033[%d;%dH", y, x);
	printf("%c[%d;%df",0x1B,y,x);


}
