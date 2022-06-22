/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, exercises 2.5.1.
    Date:        17/11/2021
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <breakpoints.h>

#define NFRAMES 100

enum {ARG_PROGNAME, ARG_INFILE, ARG_BRKFILE, ARG_OUTFILE, ARG_NARGS};

int main(int argc, char** argv) {
    int framesread;
    PSF_PROPS inprops, outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;
    double amp;

    /* init all resources vals to default states */
    int ifd = -1, ofd = -1;
    int error = 0;
    float* inframe  = NULL;

    /* Adding support to breakpoint file by the new struct BRKSTREM */
    unsigned long nbufs, outframes, remainder, nframes = NFRAMES;

    BRKSTREAM* envStream;
    FILE *fpEnv;
    unsigned long brkEnvSize = 0;
    double minVal, maxVal;

    if ( argc != ARG_NARGS ) {
        printf("Error: insufficient number of arguments.\n"
               "Usage: sfenv infile brkfile outfile\n"
               "       brkfile.brk is a breakpoint file\n"
               );

        return 1;
    }

    if ( psf_init() ) {
        printf("Error: unable to start portsf.\n");
        return 1;
    }

    if ( (ifd = psf_sndOpen(argv[ARG_INFILE], &inprops, 0)) < 0 ) {
        printf("Error: unable to open \"%s\"\n", argv[ARG_INFILE]);
        return 1;
    }

    if ( inprops.samptype == PSF_SAMP_8 ) {
        printf("Error: portsf does not support 8-bit soundfiles.\n");
        error++;
        goto exit;
    }

    if ( inprops.chans != 1 ) {
        printf("Error: infile must be mono.\n");
        error++;
        goto exit;
    }


    outprops = inprops;

    if ( (ofd = psf_sndCreate(argv[ARG_OUTFILE], &outprops, 0, 0, PSF_CREATE_RDWR)) < 0 ) {
        printf("Error: unable to create \"%s\"\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    if ( (outformat = psf_getFormatExt(argv[ARG_OUTFILE])) == PSF_FMT_UNKNOWN ) {
            printf("Outfile name \"%s\" has unknown format.\n"
                "Use any of .wav .aiff .aif .afc .aifc", argv[ARG_OUTFILE]
                );
            error++;
            goto exit;
    }

    // ============================>>>>>>>>>>>>>
    fpEnv = fopen(argv[ARG_BRKFILE], "r");
      if ( (fpEnv = fopen(argv[ARG_BRKFILE], "r")) == NULL ) {
        printf("Error: unable to open breakpoint file \"%s\"\n", argv[ARG_BRKFILE]);
        return 1;
    }

    envStream = bps_newstream(fpEnv, outprops.srate, &brkEnvSize);
    if (bps_getminmax(envStream, &minVal, &maxVal) != 0) {
        printf("Error: unable to read breakpoint file.\n");
        error++;
        goto exit;
    }
    if (minVal < 0.0 || minVal > 1.0 || maxVal < 0.0 || maxVal > 1.0) {
        printf("Error: amplitude values out of range in file %s: "
                "0.0 < amp <= 1.0\n", argv[ARG_BRKFILE]);
        error++;
        goto exit;
    }

    inframe = (float*)malloc(sizeof(float) * inprops.chans * NFRAMES);

    while ( (framesread = psf_sndReadFloatFrames(ifd, inframe, NFRAMES)) > 0 ) {
        int i;
        for ( i = 0; i < framesread; i++ ) {
            if (envStream)
                amp = bps_tick(envStream);
                
            inframe[i] = (float)(inframe[i] * amp);
        }

        if ( psf_sndWriteFloatFrames(ofd, inframe, framesread) != framesread ) {
            printf("Error writing to outfile.\n");
            error++;
            break;
        }
    }

    printf("Done.\n");

    exit:
    if (fpEnv)
        fclose(fpEnv);
    
    if (ifd)
        psf_sndClose(ifd);

    if (ofd)
        psf_sndClose(ofd);
    
    if (inframe)
        free(inframe);
    
    if (envStream) {
        bps_freepoints(envStream);
        free(envStream);
    }
    
    psf_finish();

    return error;
}
