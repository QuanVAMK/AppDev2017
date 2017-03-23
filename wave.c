/* This program is just for testing */
#include "wave.h"	//double quotation marks are used for user defined header.
#include <stdio.h>
#include "comm.h"
#include <math.h>
#include "screen.h"

void testTone(int freq, double d) {
	FILE *fp;
	int i;
	WAVHDR h;
	short int sample;
	fp = fopen("testtone.wav", "w");
	fillID("RIFF", h.ChunkID);
	//Chunksize will be calculated later.
	fillID("WAVE", h.Format);
	fillID("fmt ", h.Subchunk1ID);
	h.Subchunk1Size =16;
	h.AudioFormat = 1;
	h.NumChannels = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = SAMPLE_RATE * h.NumChannels * (h.BitsPerSample/8);
	h.BlockAlign = h.NumChannels * (h.BitsPerSample/8);
	fillID("data", h.Subchunk2ID);
	h.Subchunk2Size = (int)h.ByteRate * d;
	h.ChunkSize =h.Subchunk2Size + 36;
	fwrite(&h, sizeof(h), 1, fp);
	for (i=0;i<d*SAMPLE_RATE;i++) {
		sample=32768* sin(2*PI*freq*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);
}

void displayWAVHDR(WAVHDR hdr) {
	double duration;
	duration = (double)hdr.Subchunk2Size/hdr.ByteRate;

#ifdef DEBUG
	printf("Chunk ID: "); printID(hdr.ChunkID);
	printf("Chunk Size: %d\n", hdr.ChunkSize);
	printf("Format: ");printID(hdr.Format);
	printf("Subchunk1 ID: "); printID(hdr.Subchunk1ID);
	printf("Subchunk1 Size: %d\n", hdr.Subchunk1Size);
	printf("Audio format: %d\n", hdr.AudioFormat);
	printf("Number of channels: %d\n", hdr.NumChannels);
	printf("Sample rate: %d\n", hdr.SampleRate);
	printf("Byte rate: %d\n", hdr.ByteRate);
	printf("Block align: %d\n", hdr.BlockAlign);
	printf("Bits per sample: %d\n", hdr.BitsPerSample);
	printf("Subchunk 2 ID: "); printID(hdr.Subchunk2ID);
	printf("Subchunk 2 Size: %d\n", hdr.Subchunk2Size);
	printf("Duration of Audio %.3f sec\n", duration);
#else
	gotoXY(2,1); setFGcolor(RED); printf("%.2f", duration);
	gotoXY(2,10); setFGcolor(CYAN); printf("%d bits/s", hdr.BitsPerSample);
	gotoXY(2,20); setFGcolor(YELLOW); printf("%d sps", hdr.SampleRate);
	resetColors();
	fflush(stdout);
#endif
}

void printID (char id[]) {
	int i;
	for (i=0; i<4; i++) putchar(id[i]);
	printf("\n");
}

void fillID(const char *s, char d[]) {
	int i;
	for (i=0; i<4; i++) {
		d[i] = *s++;
	}
}

//This function calculates 1-sec samples into 80 pieces
//of RMS values, each is calculated from 16000/80=200
//pieces of samples
//However, only 8 pieces of RMS data are sent to the server as Fast mode
//of sound level meter(SLM)
void dispWAVdata(short int s[]) {
	int i,j;
	//Following variables are used to calculate RMS200
	double sum200, rms200, max200 = 0.0, min200 = 20000.0;
	//Following variables are used to calculate RMS2000 (fast Leq values)
	double Leqf[8], sum2000 = 0.0;

	for (i=0;i<80;i++) {
		sum200 = 0.0;
		for (j=0;j<SAMPLE_RATE/80; j++) {
			sum200 += (*s) * (*s);
			s++;
		}
		sum2000 += sum200;
		if  (i%10 == 9) {	//For every 10 pieces of rms200, we get a rms2000
			Leqf[i/10] = sqrt(sum2000/SAMPLE_RATE/8);
			sum2000 = 0.0;	//Reset sum2000.
		}
		rms200 = sqrt(sum200/(SAMPLE_RATE/80));

		rms200 = 20*log10(rms200);

		if (max200 < rms200) max200 = rms200;
		if (min200 > rms200) min200 = rms200;
#ifdef DEBUG
	printf("%2d: %10.2f\n", i, rms200);
#else
	// display vertical bars
	displayBar(i+1 , rms200);
#endif
	}

#ifdef DEBUG
	printf("min = %.2f, max = %.2f\n", min200, max200);
#endif
#ifdef COMM	//only in the case COMM is defined, send data to server.
	send_data_curl(Leqf);
#endif
}
