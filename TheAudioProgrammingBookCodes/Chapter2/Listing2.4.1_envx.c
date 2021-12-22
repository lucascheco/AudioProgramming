/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, envx .
    Date:        16/11/2021
************************************************************************************/
/* envx:
         extract amplitude envelope from mono soundfile */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

#define DEFAULT_WINDOW_MSECS (15)

enum { ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_NARGS };

double maxsample(float* buf, unsigned long blocksize);

int main(int argc, char* argv[]) {
    PSF_PROPS inprops;
    int ifd;
    float *inframe = NULL;
    long framesread;

    FILE *fp = NULL;

    double windur = DEFAULT_WINDOW_MSECS;  /* duration of the window in msecs */
    
    unsigned long winsize;                 /* windur converted in secs */

    double brktime = 0.0;                        /* holds the time for the current breakpoint time */

    unsigned long npoints;
    int error = 0;
        
    printf("ENVX: extract amplitude envelope"
           "from mono soundfile.\n");


    /* Implementation of the -wN flag */
    if ( argc > 1 ) {
        char flag;
        while ( argv[1][0] == '-' ) {
            flag = argv[1][1];
            
            switch ( flag )
            {
                /* TODO: handle any flag arguments here */
            case '\0':
                printf("ERROR: missing flag name\n");
                return 1;
                
            case 'w':
                windur = atof(&argv[1][2]);
                if ( windur <= 0.0 ) {
                    printf("bad value for Window Duration."
                           "Must be positive.\n");
                    return 1;
                }
                break;
            default:
                break;
            }
            
            argc--;
            argv++;
        }
    }
    /* Standard error handling */
    if ( argc < ARG_NARGS ) {
        printf("insufficient arguments.\n"
               "usage:\n\tenvx [-wN] insndfile outfile.brk\n"
               "                -wN: set extraction window size to N msecs\n"
               "                     (default: 15)\n");
        return 1;
    }

    /* API init function */
    if ( psf_init() ) {
        printf("ERROR: unable to start portsf.\n");
        return 1;
    }

    /* Open sound file and handle error */
    ifd = psf_sndOpen(argv[ARG_INFILE], &inprops, 0);
    if ( ifd < 0 ) {
        printf("ERROR: unable to open infile \"%s\"\n", argv[ARG_INFILE]);
        return 1;
    }

    /* verify infile format for this application */
    if ( inprops.chans > 1 ) { 
        printf("ERROR: infile has %d channels: "
               "must be mono.\n", inprops.chans);
        error++;
        goto exit;
    }

    /* create output breakpoint file */
    fp = fopen(argv[ARG_OUTFILE], "w");
    if ( fp == NULL ) {
        printf("envx: unable to create breakpoint file %s\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    /* set buffersize to the required envelope window size */
    windur /= 1000.0;        /* Convert to seconds */
    winsize = (unsigned long)(windur * inprops.srate);

    inframe = (float*)malloc(winsize * sizeof(float));
    if ( inframe == NULL ) {
        puts("No memory!\n");
        error++;
        goto exit;
    }

/* Main processing loop */
    while ( (framesread = psf_sndReadFloatFrames(ifd, inframe, winsize)) > 0 ) {
        double amp;
        amp = maxsamp(inframe, framesread);

        /* store brktime and amp as a breakpoint */
        if ( fprintf(fp, "%f\t%f\n", brktime, amp) < 2 ) {
            printf("Failed to write to breakpoint file %s\n", argv[ARG_OUTFILE]);
            error++;
            break;
        }

        npoints++;
        brktime += winsize;
    }

    if ( framesread < 0 ) {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    } else {
        printf("Done: %d errors\n", error);
        printf("%ld breakpoints written to %s\n", npoints, argv[ARG_OUTFILE]);
    }

/* clean up */
    exit:
        if (ifd >= 0)
            psf_sndClose(ifd);

        if ( fp )
            if ( fclose(fp) )
                printf("envx: failed to close output file %s\n", argv[ARG_OUTFILE]);
    
    psf_finish();

    return 0;
}


double maxsample(float* buf, unsigned long blocksize) {
    double absval, peak = 0.0;
    unsigned long i;

    for ( i = 0; i < blocksize; i++ ) {
        absval = fabs(buf[i]);

        if (absval > peak)
            peak = absval;
    }

    return peak;
}