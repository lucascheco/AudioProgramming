/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 3, 'player'.
    Date:        04/07/2022
************************************************************************************/

#include <stdio.h>
#include "../Resources/tinyaudiolib/include/tinyAudioLib.h"
#include "portsf.h"

#define FRAME_BLOCK_LEN 512

enum {ARG_PLAYER, ARG_FILENAME, N_ARGS};

void main(int argc, char **argv)
{
    float buf[FRAME_BLOCK_LEN * 2]; /* buffer space for stereo and mono */
    int sfd;                        /* audio file descriptor */
    PSF_PROPS props;                /* struct filled by psf_sndOpen(), containing audio file info */
    long nread;                     /* number of frames actually read */

    if (argc != 2) /* needs a command line argument */
    {
        printf("error: bad command line. Syntax is: \n\n"
               " player filename\n");
        return;
    }

    psf_init();                                       /* initialize portsf library */
    sfd = psf_sndOpen(argv[ARG_FILENAME], &props, 0); /* open an audio file using portsf lib */
    if (sfd < 0)
    {
        printf("error: error ocurred opening file\n");
        goto end;
    }

    if (props.chans > 2)
    {
        printf("Invalid number of channels in audio file.\n");
        goto end;
    }

    /* ------ ENGINE START ------ */
    do 
    {
        nread = psf_sndReadFloatFrames(sfd, buf, FRAME_BLOCK_LEN);
        if (props.chans == 2)
            outBlockInterleaved(buf, FRAME_BLOCK_LEN);
        else    
            outBlockMono(buf, FRAME_BLOCK_LEN);
        

    } while (nread == FRAME_BLOCK_LEN);
    /* ------ ENGINE END ------ */

    end:
        psf_sndClose(sfd);
        psf_finish();
        printf("finished!\n");
}