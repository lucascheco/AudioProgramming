/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, ring modulation.
    Date:        22/11/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#define N 1024

void usage_and_exit();
int formats_equal(SF_INFO a, SF_INFO b);

int main(int argc, char**argv) {
    SNDFILE *sfp1, *sfp2, *sfpo;
    SF_INFO sfinfo1, sfinfo2;

    int count;
    int n;
    short sig1[N], sig2[N], ring[N];

    if (argc != 4) 
        usage_and_exit();

    sfp1 = sf_open(argv[1], SFM_READ, &sfinfo1);
    sfp2 = sf_open(argv[2], SFM_READ, &sfinfo2);

    if (sfp1 == NULL || sfp2 == NULL) 
        usage_and_exit();

    if (formats_equal(sfinfo1, sfinfo2)) { 
        sfpo = sf_open(argv[3], SFM_WRITE, &sfinfo1);
    
        do {
            count = sf_read_short(sfp1, sig1, N);
            sf_read_short(sfp2, sig2, N);
            for (n = 0; n < count; n++)
                ring[n] = sig1[n] * sig2[n];
            sf_write_short(sfpo, ring, count);
        } while (count);

        sf_close(sfpo);
    }
    sf_close(sfp1);
    sf_close(sfp2);
}

void usage_and_exit() {
    printf("usage: ring input1 input2 output\n"
           "where input1 & input2  are soundfiles\n"
           "with the same format and output is the\n"
           "ring-modulated filename \n"
	 );
     exit(1);
}

int formats_equal(SF_INFO a, SF_INFO b) {
    if( a.format == b.format && 
        a.samplerate == b.samplerate && 
        a.channels == b.channels )
        return 1;
    else 
        return 0;
}