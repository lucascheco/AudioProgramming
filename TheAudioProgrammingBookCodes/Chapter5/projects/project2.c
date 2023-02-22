/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, mix signals improved.
    Date:        23/11/2022
************************************************************************************/

/* TODO:
    2 - Provide a way of offsetting the start of one of the files
    
    3 - Make sure the mixed output duration is the result of the 
        largest maximum soundfile duration plus any offstes (at
        the moment, the output duration is set by the 1st input)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

#define N 1024

void usage_and_exit();

int formats_equal(SF_INFO a, SF_INFO b);
void argument_decode(int argc, char** argv);

float gain1 = 1.f, gain2 = 1.f;

int main(int argc, char** argv) {
    SNDFILE *in1, *in2, *out;
    SF_INFO info1, info2, info_out;

    argument_decode(argc, argv);

    if (argc < 4)  
        usage_and_exit();

    in1 = sf_open(argv[1], SFM_READ, &info1);
    in2 = sf_open(argv[2], SFM_READ, &info2);

    if (in1 == NULL || in2 == NULL)
        usage_and_exit();

    if (formats_equal(info1, info2)) {
        int count, n;
        short sig1[N], sig2[N], mix[N];

        info_out.channels = info1.channels;
        info_out.samplerate = info1.samplerate;
        info_out.format = info1.format;
        
        out = sf_open(argv[3], SFM_WRITE, &info_out);

        do {
            count = sf_read_short(in1, sig1, N);
            sf_read_short(in2, sig2, N);
            
            for (n = 0; n < count; n++) 
                mix[n] = sig1[n] * gain1 + sig2[n] * gain2;
            
            sf_write_short(out, mix, count);
        } while (count);

        sf_close(out);
    }
    sf_close(in1);
    sf_close(in2);
}

void usage_and_exit() {
    printf("\nusage: mix input1 input2 output [-g gain1 gain2]\n"
           "\twhere input1 & input2 are soundfiles\n"
           "\twith the same format and output is the\n"
           "\tmixed filename \n"
           "\tgain1 and gain2 are floats\n\n"
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

char first_char_of(char* a) {
    return a[0];
}

char arg_char(char* a) {
    return a[1];
}

void argument_decode(int argc, char** argv) {
    int i = 1;
    while (--argc) {
        char* arg = argv[i]; 
        if (first_char_of(arg) == '-') {
            switch (arg_char(arg))
            {
            case 'g':
                if (argc == 0) {
                    printf("error: no gains argument.\n"); usage_and_exit();
                }
                gain1 = atof(argv[i + 1]);
                if(argv[i + 2] != NULL) {
                    gain2 = atof(argv[i + 2]);
                    argc--;
                    i++;
                }

                argc--;
                i += 2;
                break;
            }
        } 
        i++;
    }
}