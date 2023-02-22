/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, Sine improved.
    Date:        22/11/2022
************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>

#define TWOPI (2 * M_PI)
#define BLOCK 2205          // 2205 minimum block size to represent one cycle of a 20hz sine wave
#define SAMPLERATE 44100

float amp = 32767.f/2;
float sr = (float) SAMPLERATE;
float freq = 440.f;
float m2PI = (float) TWOPI;
float p = 0.f;
short wave[BLOCK];
char *path = "../sounds/sine_improved.wav";
FILE *fp;
char *textfile = "sine.txt";
float duration = 1;


void print_sinfo(char* path_to_file, SF_INFO info, float amp, float freq, float p, int block_size, float duration);

char first_char_of(char* a);
char arg_char(char* a);
void usage_message();
void argument_decode(int argc, char** argv);

int main(int argc, char** argv) {

    SNDFILE *sfp;
    SF_INFO info;

    /*  w = 2pif
        s[x] = a * sin(w/sr + p)  */
    usage_message();
    argument_decode(argc,argv);

    // we need to fill basic structure to the soundfile
    info.channels = 1;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.samplerate = sr;
    sfp = sf_open(path, SFM_WRITE, &info);
    
    for (int d = 0; d < 20 * duration; d++) {
        for (int i = 0; i < BLOCK; i++) 
            wave[i] = amp * sin((m2PI * freq *  (i + d * BLOCK))/sr + p);
        sf_write_short(sfp, wave, BLOCK);
    }

    if (fp)
        for (int d = 0; d < 20 * duration; d++)
            for (int i = 0; i < BLOCK; i++) 
                fprintf(fp, "%d\n", wave[i]);

    print_sinfo(path, info, amp, freq, p, BLOCK, duration);

    sf_close(sfp);
    if (fp)
        fclose(fp);
}

void print_sinfo(char* path_to_file, SF_INFO info, float amp, float freq, float p, int block_size, float duration) {
    printf("\n\nSound information:\n"
           "\tpath: %s\n"
           "\tchannels: %d\n"
           "\tsamplerate: %d\n"
           "\tamplitude: %f\n"
           "\tfrequency: %f\n"
           "\tphase: %f\n"
           "\tblock size: %d\n"
           "\tduration: %f\n\n", path_to_file, info.channels, info.samplerate, amp, freq, p, block_size, duration);
}

void usage_message() {
    printf("\n\nproject1 [-n filename] [-s samplerate] [-a amp] [-f freq] [-p phase] [-t textfile.txt]\n"
           "ex: project1 -n filename.wav -s 44100 -a 32767 -f 220.0 -p 0.0 -t sine.txt\n\n");
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
            case 'n':
                if (argc == 0) {
                    printf("error: no filename argument.\n"); usage_message();
                    exit(1);
                }
                path = argv[i + 1];
                argc--;
                i += 2;
                break;

            case 's':
                if (argc == 0) {
                    printf("error: no samplerate argument.\n"); usage_message();
                    exit(1);
                }
                sr = atoi(argv[i + 1]);
                argc--;
                i += 2;
                break;
                
            case 'a':
                if (argc == 0) {
                    printf("error: no amp argument.\n"); usage_message();
                    exit(1);
                }
                amp = atof(argv[i + 1]);
                argc--;
                i += 2;
                break;

            case 'f':
                if (argc == 0) {
                    printf("error: no frequency argument.\n"); usage_message();
                    exit(1);
                }
                freq = atof(argv[i + 1]);
                argc--;
                i += 2;
                break;

            case 'p':
                if (argc == 0) {
                    printf("error: no phase argument.\n"); usage_message();
                    exit(1);
                }
                p = atof(argv[i + 1]);
                argc--;
                i += 2;
                break;
            case 't':
                if (argc == 0) {
                    printf("error: no text filename argument.\n"); usage_message();
                    exit(1);
                }
                textfile = argv[i + 1];
                fp = fopen(textfile, "w");
                
                break;
            
            case 'd':
                if (argc == 0) {
                    printf("error: no duration argument.\n"); usage_message();
                    exit(1);
                }
                duration = atof(argv[i + 1]);
                argc--;
                i += 2;

                break;
            default:
                break;
            }
        } else {
            printf("No tag found.\n");
            exit(1);
        }
    }
}