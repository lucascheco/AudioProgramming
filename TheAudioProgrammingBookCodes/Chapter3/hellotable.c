/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 3, 'hello table'.
    Date:        30/06/2022
************************************************************************************/

#include <stdio.h>
#include <math.h>

#ifdef REALTIME
#include "tinyAudioLib.h"
#elif defined(BINARY_RAW_FILE)
FILE* file;
#elif defined(WAVE_FILE)
#include "portsf.h"
PSF_PROPS props;
int ofd;
#endif

#define SAMPLING_RATE 44100
#define PI 3.14159265

#define TABLE_LEN 512
#define SINE     0
#define SQUARE   1
#define SAW      2
#define TRIANGLE 3

float table[TABLE_LEN]; /* array to be filled with a waveform */

void fill_sine();
void fill_square();
void fill_saw();
void fill_triangle();


void outSample(float sample);
void init();
void cleanup();

void main()
{
    int waveform;
    const float frequency, duration;
   
    printf("Type the frequency of the wave to output in Hz, and press ENTER: ");
    scanf("%f", &frequency);

    printf("\nType the duration of tone in seconds, and press ENTER: ");
    scanf("%f", &duration);

    wrong_waveform:
    printf("\nType a number from 0 to 3 corresponding to the waveform you intended to choose\n");
    printf("(0 = sine, 1 = square, 2 = saw and 3 = triangle), and press ENTER: ");
    scanf("%d", &waveform);
    if (waveform < 0 || waveform > 3)
    {
        printf("\nwrong number for waverform, try again!\n");
        goto wrong_waveform;
    }

    /* ------ FILL THE TABLE ------*/
    switch (waveform)
    {
        case SINE:
            printf("\nYou've chosen a sine wave\n");
            fill_sine();
            break;

        case SQUARE:
            printf("\nYou've chosen a square wave\n");
            fill_square();
            break;

        case SAW:
            printf("\nYou've chosen a saw wave\n");
            fill_saw();
            break;

        case TRIANGLE:
            printf("\nYou've chosen a triangle wave\n");
            fill_triangle();
            break;

        default:
            printf("\nwrong wave! Ending program ...\n");
            return;
    }

    init();

    /* ------ SYNTHESIS ENGINE START ------ */
    {
        int j;
        double sample_increment = frequency * TABLE_LEN / SAMPLING_RATE;
        double phase = 0.0;
        float sample;

        for (j = 0; j < duration * SAMPLING_RATE; j++)
        {
            sample = table[(long) phase];
            outSample(sample);
            phase += sample_increment;
            
            if (phase > TABLE_LEN)
                phase -= TABLE_LEN;
        }
    }
    /* ------ SYNTHESIS ENGINE END ------ */
    cleanup();
    printf("End of process\n");
}


void fill_sine()
{
    for (int j = 0; j < TABLE_LEN; j++)
        table[j] = (float) sin(2 * PI * j / TABLE_LEN);
}

void fill_square()
{
    int j;
    for (j = 0; j < TABLE_LEN / 2; j++)
        table[j] = 1;
    
    for (j = TABLE_LEN / 2; j < TABLE_LEN; j++)
        table[j] = -1;
}

void fill_saw()
{
    for (int j = 0; j < TABLE_LEN; j++)
        table[j] = 1 - (2 * (float)j / (float)TABLE_LEN);
}

void fill_triangle()
{
    int j;
    for (j = 0; j < TABLE_LEN / 2; j++)
        table[j] = 2 * (float) j / (float)(TABLE_LEN / 2) - 1;
    
    for (j = TABLE_LEN / 2; j < TABLE_LEN; j++)
        table[j] = 1 - (2 * (float)(j - TABLE_LEN / 2) / (float)(TABLE_LEN / 2));
}

void outSample(float sample)
{
#ifdef REALTIME
    outSampleMono(sample);

#elif defined(BINARY_RAW_FILE)
    short isample = (short)(sample * 32000);
    fwrite(&isample, sizeof(short), 1, file);

#elif defined(WAVE_FILE)
    psf_sndWriteFloatFrames(ofd, &sample, 1);
#else
    printf("%f\n", sample);
#endif
}

void init()
{
#ifdef REALTIME
    tinyInit();
#elif defined(BINARY_RAW_FILE)
    file = fopen("hellotable.raw", "wb");
#elif defined(WAVE_FILE)
    props.srate = 44100;
    props.chans = 1;
    props.samptype = PSF_SAMP_16;
    props.format = PSF_STDWAVE;
    props.chformat = STDWAVE;

    psf_init();
    odf = psf_sndCreate("hellotable.wav", &props, 0, 0, PSF_CREATE_RDWR);

#else
    printf("\n . . . Nothing to initialize . . .\n");
#endif    
}

void cleanup()
{
    printf("cleaning up. . . \n");
#ifdef REALTIME
    tinyExit();
#elif defined(BINARY_RAW_FILE)
    fclose(file);
#elif defined(WAVE_FILE)
    {
        int err1, err2;
        err1 = psf_sndClose(ofd);
        err2 = psf_finish();

        if (err1 || err2)
            printf("\nWarning! An error occurred writing WAVE_FILE file.\n");
    }
#else
    printf("Nothing to clean up. . .\n");
#endif
}