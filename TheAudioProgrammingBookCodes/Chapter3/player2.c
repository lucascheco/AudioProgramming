/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 3, 'player2'.
    Date:        04/07/2022
************************************************************************************/

#include <stdio.h>
#include <math.h>
#include "../Resources/tinyaudiolib/include/tinyAudioLib.h"
#include "portsf.h"

#define FRAME_BLOCK_LEN 512

enum {ARG_PLAYER, ARG_FILENAME, N_ARGS};

void SYNTAX()
{
    printf("syntax is: \n player2 [-tTime] [-dDUR] filename\n");
}

void main(int argc, char **argv)
{
    float buf[FRAME_BLOCK_LEN * 2]; /* buffer space for stereo and mono */
    int sfd;                        /* audio file descriptor */
    int opened = 0;                 /* flag telling if audio file has been opened */
    PSF_PROPS props;                /* struct filled by psf_sndOpen(), containing audio file info */
    long counter;                   /* counter of frames read */
    long length;                    /* length of file in frames */
    long endpoint;                  /* end point of playing */
    extern int arg_index;           /* from crack.c */
    extern char *arg_option;        /* from crack.c */
    extern int crack(int argc, char **argv, char *flags, int ign);
    int flag, timflag = 0, durflag = 0; /* flags */
    long nread;                     /* number of frames actually read */
    double starttime, dur;

    while (flag = crack(argc, argv, "t|d|T|D", 0))
    {
        switch (flag)
        {
        case 't':
        case 'T':
            if (*arg_option)
            {
                timflag = 1;
                starttime = atof(arg_option);
            }
            else
            {
                printf("error: -t flag set without specifying a start time in seconds.\n");
                SYNTAX();
                return;
            }
            break;
        case 'd':
        case 'D':
            if (*arg_option)
            {
                durflag = 1;
                dur = atof(arg_option);
            }
            else
            {
                printf("error: -d flag set without specifying a duration time in seconds.\n");
                SYNTAX();
                return;
            }
            break;
        default:
            break;
        }
    }

    if (argc < 2) /* needs a command line argument */
    {
        printf("error: bad command line. Syntax is: \n\n");
        SYNTAX();
        return;
    }

    psf_init();                                       /* initialize portsf library */
    sfd = psf_sndOpen(argv[arg_index], &props, 0); /* open an audio file using portsf lib */
    if (sfd < 0)
    {
        printf("error: error ocurred opening file\n");
        goto end;
    }

    printf("file \'%s\' opened. . .\n", argv[arg_index]);
    printf("sampling rate: %d\n", props.srate);
    printf("number of chans: %d\n", props.chans);
    length = psf_sndSize(sfd);
    printf("duration: %f\n", (float) length / (float) props.srate);

    if (timflag)
        counter = (long) (starttime * props.srate); /* length in frames */
    else
        counter = 0;

    if (durflag)
    {
        endpoint = (long) (dur * props.srate + counter);
        endpoint = (endpoint < length) ? endpoint : length;
    }
    else
    {
        endpoint = length;
        dur = (double) (endpoint - counter) / (double) props.srate;
    }

    if (props.chans > 2)
    {
        printf("Invalid number of channels in audio file. Max 2 channels\n");
        goto end;
    }

    psf_sndSeek(sfd, counter, PSF_SEEK_SET); /* begin position at the appropriate point */
    printf("Playing the file from time position %0.3lf for %0.3lf seconds. . .\n", starttime, dur);

    /* ------ ENGINE START ------ */
    do 
    {
        nread = psf_sndReadFloatFrames(sfd, buf, FRAME_BLOCK_LEN);
        if (props.chans == 2)
            outBlockInterleaved(buf, FRAME_BLOCK_LEN);
        else    
            outBlockMono(buf, FRAME_BLOCK_LEN);
        
        counter += FRAME_BLOCK_LEN;
    } while (counter < endpoint);
    /* ------ ENGINE END ------ */

    end:
        psf_sndClose(sfd);
        psf_finish();
        printf("finished!\n");
}