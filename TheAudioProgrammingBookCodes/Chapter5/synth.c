/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, Synth.
    Date:        22/11/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include <string.h>

#define N      4410
#define TWOPI (2.0 * M_PI)

float* sawtooth(int harms, int length);
float* square(int harms, int length);
float* fourier_table(int harms, float *amps, int length, float phase);
void normalise_table(float *table, int length);

void usage_and_exit();

int main(int argc, char**argv) {
    SNDFILE *sfp;
    SF_INFO sfinfo;
    int i;
    int n;
    short sig[N];
    float amp, freq, sr = 44100.f;
    double index = 0.0, incr;
    int tablen = 16384;
    float *tab;

    if (argc != 6)
        usage_and_exit();

    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.samplerate = sr;
    sfinfo.channels = 1;

    sfp = sf_open(argv[1], SFM_WRITE, &sfinfo);

    if (atoi(argv[4]) == 0) {
        tab = sawtooth(atoi(argv[5]), tablen);
        printf("sawtooth\n");
    } else {
        tab = square(atoi(argv[5]), tablen);
    }

    freq = atof(argv[3]);
    amp = atof(argv[2]);

    incr = freq * tablen/sr;

    for (i = 0; i < 44100/N; i++) {
        for (n = 0; n < N; n++) {
            sig[n] = (short)(amp * tab[(int)index]);
            index += incr;
            
            while (index >= tablen)
                index -= tablen;
            
            while (index < 0)
                index += tablen;
        }
        sf_write_short(sfp, sig, N);
    }

    sf_close(sfp);
    free(tab);
}

float* sawtooth(int harms, int length) {
    int i;
    float *amps = (float *) malloc(harms * sizeof(float));
    for (i = 0; i < harms; i++)
        amps[i] = 1.0 / (i + 1.0);
    
    return fourier_table(harms, amps, length, 0.75);
}

float* square(int harms, int length) {
    int i;
    float *amps = (float *) malloc(harms * sizeof(float));

    memset(amps, 0, harms * sizeof(float));

    for (i = 0; i < harms; i+=2)
        amps[i] = 1.0 / (i + 1.0);
    
    return fourier_table(harms, amps, length, 0.75);  
}

float* fourier_table(int harms, float *amps, int length, float phase) {
    int i, n;
    float a;
    double w;
    float *table = (float *) malloc(length * sizeof(float));
    phase *= (float) TWOPI;

    memset(table, 0, (length) * sizeof(float));

    for (i = 0; i < harms; i++) {
        for (n = 0; n < length; n++) {
            a = amps ? amps[i] : 1.f;
            w = (i + 1) *  (n * TWOPI/length);
            table[n] += (float) (a * cos(w + phase));
        }
    }

    normalise_table(table, length);
    return table;
}

void normalise_table(float *table, int length) {
    int n;
    float max = 0.f;
    
    for (n = 0; n < length; n++) 
        max= table[n] > max ? table[n] : max;
    
    if (max)
        for (n = 0; n < length; n++)
            table[n] /= max;
}



void usage_and_exit() {
    printf("usage: synth outfile.wav amp freq wtype harms\n"
           "where amp: amplitude (0-32767)\n"
           "freq: frequency (Hz)\n"
           "wtype: wave type, 0=saw, 1=square\n"
           "harms: highest harmonic number\n"
	 );
     exit(1);
}