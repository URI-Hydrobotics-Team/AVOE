/* functions for DEC VT100 escape codes */

#include <cstdio>

#ifndef VT100_H 
#define VT100_H

void vtClear();
void vtGoto(int x, int y);
#endif
