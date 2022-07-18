/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 3, 'hello ring'.
    Date:        09/07/2022
************************************************************************************/

#include <stdio.h>
#include <math.h>

#include "portaudio.h"

#define FRAME_BLOCK_LEN 256
#define SAMPLING_RATE 44100
#define TWO_PI (3.14159265f * 2.0f)

PaStream *audioStream;
double si = 0; /* sample increment */

int audio_callback(const void *inputBuffer, 
                   void *outputBuffer, 
                   unsigned long framesPerBuffer, 
                   const PaStreamCallbackTimeInfo* timeInfo,
                   PaStreamCallbackFlags statusFlags,
                   void *userData)
{
    float *in = (float*) inputBuffer, *out = (float*)outputBuffer;
    static double phase = 0;
    unsigned long i;

    for (i = 0; i < framesPerBuffer; i++)
    {
        float sine = sin(phase);
        *out++ = *in++ * sine;  /* left channel */
        *out++ = *in++ * sine;  /* right channel */
        phase += si;
    }

    return paContinue;
}

void init_stuff()
{
    float frequency;
    int i, id;
    const PaDeviceInfo *info;
    const PaHostApiInfo *hostapi;
    PaStreamParameters outputParameters, inputParameters;

    printf("Type the modulator frequency in Hertz: ");
    scanf("%f", &frequency); /* get the ring modulator frequency */

    si = TWO_PI * frequency / SAMPLING_RATE; /* calculate sampling increment */

    printf("Initializing Portaudio. Please wait. . .\n");
    Pa_Initialize(); /* initialize portaudio */
    for (i = 0; i < Pa_GetDeviceCount(); i++)
    {
        info    = Pa_GetDeviceInfo(i);              /* get information from current device */
        hostapi = Pa_GetHostApiInfo(info->hostApi); /* get information from current host API */

        if (info->maxOutputChannels > 0)            /*if current device supports output */
            printf("%d: [%s] %s (output)\n", i, hostapi->name, info->name);
        
    }

    printf("\nType AUDIO output device number: ");
    scanf("%d", &id); /* get the output device id from the user */

    info = Pa_GetDeviceInfo(id);                /* get chosen device information structure */
    hostapi = Pa_GetHostApiInfo(info->hostApi); /* get host API struct */
    printf("Openning AUDIO output device [%s] %s\n", hostapi->name, info->name);

    outputParameters.device = id;                                      /* chosen device id */
    outputParameters.channelCount = 2;                                 /* stereo output */
    outputParameters.sampleFormat = paFloat32;                         /* 32 bit float output */
    outputParameters.suggestedLatency = info->defaultLowOutputLatency; /* set default */
    outputParameters.hostApiSpecificStreamInfo = NULL;                 /* no specific information */

    for (i = 0; i < Pa_GetDeviceCount(); i++)
    {
        info    = Pa_GetDeviceInfo(i);              /* get information from current device */
        hostapi = Pa_GetHostApiInfo(info->hostApi); /* info from host API */

        if (info->maxInputChannels > 0) /* if current supports input */
            printf("%d: [%s] %s (input)\n", i, hostapi->name, info->name);
            
    }

    printf("Opening AUDIO input device number: ");
    scanf("%d", &id); /* get the input device id from the user */
    
    info = Pa_GetDeviceInfo(id);                /* get chosen device information structure */
    hostapi = Pa_GetHostApiInfo(info->hostApi); /* get host API struct */
    printf("Openning AUDIO input device [%s] %s\n", hostapi->name, info->name);

    inputParameters.device = id;                                     /* chosen device id */
    inputParameters.channelCount = 2;                                /* stereo output */
    inputParameters.sampleFormat = paFloat32;                        /* 32 bit float output */
    inputParameters.suggestedLatency = info->defaultLowInputLatency; /* set default */
    inputParameters.hostApiSpecificStreamInfo = NULL;                /* no specific information */

    Pa_OpenStream(                   /* open the PaStream object */
                  &audioStream,
                  &inputParameters,  /* provide output parameters */
                  &outputParameters, /* provide input parameters */
                  SAMPLING_RATE,     /* set sampling rate */
                  FRAME_BLOCK_LEN,   /* set frames per buffer */
                  paClipOff,         /* set no clip */
                  audio_callback,    /* callback function address */
                  NULL);             /* provide no data for the callback */
    
    Pa_StartStream(audioStream); /* start the callback mechanism */
    printf("running. . . press space bar and enter to exit\n");
}

void terminate_stuff()
{
    Pa_StopStream(audioStream);  /* stop the callback mechanism */
    Pa_CloseStream(audioStream); /* destroy the audio stream object */

    Pa_Terminate();              /* terminate portaudio */
}

int main()
{
    init_stuff();
    while (getchar() != ' ') Pa_Sleep(100);
    terminate_stuff();
    
    return 0;
}