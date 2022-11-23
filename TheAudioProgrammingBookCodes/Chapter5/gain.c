/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, gain.
    Date:        22/11/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#define N 1024

void usage_and_exit();

int main(int argc, char**argv) {
    SNDFILE *sfp, *sfpo;
    SF_INFO sfinfo;

    int count;
    int n;
    short sig[N], scaled[N];
    float gain;

    if (argc != 4) 
        usage_and_exit();

    sfp = sf_open(argv[1], SFM_READ, &sfinfo);

    if (sfp == NULL) 
        usage_and_exit();

    gain = atof(argv[3]);
    
    sfpo = sf_open(argv[2], SFM_WRITE, &sfinfo);

    do {
        count = sf_read_short(sfp, sig, N);
        for (n = 0; n < count; n++)
            scaled[n] = sig[n] * gain;
        sf_write_short(sfpo, scaled, count);
    } while (count);

    sf_close(sfpo);
    sf_close(sfp);
}

void usage_and_exit() {
    printf( "usage: gain input output scale\n"
            "where input is the input soundfile\n"
            "scale is the gain factor and output is the\n"
            "output filename \n"
	);
    exit(1);
}
