/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, FMsynth.
    Date:        22/11/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>


#define N 4410
#define TWOPI (2.0 * M_PI)

void usage_and_exit();

int main(int argc, char**argv) {
    SNDFILE *sfp;
    SF_INFO sfinfo;
    int i;
    int n , count = 0;
    short sig[N];

    float amp, fc, fm, ndx, sr = 44100.f;
    float phase = 0.75;
    double twopioversr = (double) TWOPI/sr;
    double pha = 0.0;

    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.samplerate = sr;
    sfinfo.channels = 1;

    if(argc != 6) 
        usage_and_exit();

    amp = atof(argv[2]);
    fc = atof(argv[3]);
    fm = atof(argv[4]);
    ndx = atof(argv[5]); 

    sfp = sf_open(argv[1], SFM_WRITE, &sfinfo);
    for(i = 0; i < 44100/N; i++){                     
        for(n = 0; n < N; n++){              
            sig[n] = (short)(amp * cos(pha));
            pha += twopioversr * (fc + ndx * fm * sin(twopioversr * count * fm));
            count++;     
        }
        sf_write_short(sfp, sig, N);        
    }
  
    sf_close(sfp);                                        
}

void usage_and_exit() {
    printf("usage: fmsynth outfile.wav amp fc fm index\n"
            "where amp: amplitude (0-32767)\n"
            "fc: carrier frequency (Hz)\n"
            "fm: mod frequency (Hz)\n"
            "index: index of modulation\n"
        );
    exit(1);
}