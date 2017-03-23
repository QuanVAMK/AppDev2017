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

void displayBar(int col, double rms) {
	int i;
	gotoXY(2,1);
	for (i=0;i<=80;i++)
		printf("*");
	for (i=80;i>=80-rms/50; i--) {
		gotoXY(i, col);
#ifdef UNICODE
		printf("%s", BAR);
#else
		printf("*");
#endif
	}
	fflush(stdout);
}
