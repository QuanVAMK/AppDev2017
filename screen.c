#include "screen.h"
#include <stdio.h>

//function definitions.
void clearScreen(void) {
	printf("\033[2J");
	fflush(stdout);
}
void setFGcolor(int fg) {	//fg is a value between 30 and 37
	printf("\033[%d;1m", fg);
	fflush(stdout);		//send out the esc sequence to terminal.
}

void resetColors(void) {
	printf("\033[0m");
	fflush(stdout);
}

void gotoXY(int row, int col) {
	// row number should be 1-30, col should be 1-80
	printf("\033[%d;%dH", row, col);
	fflush(stdout);
}

void displayBar(double rms, int col){
	int i;
	rms = (rms)*3/sizeof(short int);
	if (70-rms/100<0) {setFGcolor(RED);} //If value exceeds the terminal screen, red color will be shown.
	for (i=70;i>70-rms/100;i--){
		if (i<2) break;
		gotoXY(i+2,col);
#ifndef UNICODE
		printf("%c",);
#else
		printf("%s",BAR);
#endif
	}
	fflush(stdout);
}
