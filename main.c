/* This program is just for testing */
#include "wave.h"	//double quotation marks are used for user defined header.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "screen.h"
#include <signal.h>
#include <sys/wait.h>

//This program will open a wave file, and display WAV header info.
//This program will create a wave file.
int main(int argc, char *argv[]) {
	FILE *fp;
	WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int ret;
/*	if (argc != 2) {
		printf("Usage: %s wav_file\n", argv[0]);
		return -1;
	}
	fp =fopen(argv[1], "r");	//Try to open the wav file.
	if (fp == NULL) {
		printf("cannot find file %s\n", argv[1]);
		return -1;
	}
*/
	while(1) {
	gotoXY(1,1);
	ret = system("arecord -r16000 -c1 -d1 -f S16_LE data.wav");
	if (WIFSIGNALED(ret) && WTERMSIG(ret) == SIGINT) break;
	clearScreen();    //Make a clear screen.
	fp = fopen("data.wav", "r");
	fread(&myhdr, sizeof(myhdr), 1, fp); //read the wav header.
	displayWAVHDR(myhdr);		//display the wav headeinfo.
	fread(&sa, sizeof(short int), SAMPLE_RATE,fp);
	dispWAVdata(sa);
	fclose(fp);

	}
/*	int ans;
	printf("Do you want to genearate a test tone? (1:yes, 0:no)\n");
	scanf("%d", &answer);
	if (answer == 1) testTone(12500, 5);
*/
	return 0;
}

