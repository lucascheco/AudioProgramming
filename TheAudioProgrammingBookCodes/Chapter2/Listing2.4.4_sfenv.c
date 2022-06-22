/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, sfenv.
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
    unsigned long  npoints;
    PSF_PROPS inprops, outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;
    double incr, sampletime;

    /* init all resources vals to default states */
    int ifd = -1, ofd = -1;
    int error = 0;
    float* inframe  = NULL;
    FILE* fp = NULL;
    BREAKPOINT* points = NULL;
    BREAKPOINT leftpoint, rightpoint;
    unsigned long ileft, iright;

    double frac, height, width, curpos;

    if ( argc != ARG_NARGS ) {
        printf("Error: insufficient number of arguments.\n"
               "Usage: sfenv infile brkfile outfile\n"
               "       brkfile.brk is a breakpoint file\n"
               );

        return 1;
    }

    /* read breakpoint file and verify it */
    if ( (fp = fopen(argv[ARG_BRKFILE], "r")) == NULL ) {
        printf("Error: unable to open breakpoint file \"%s\"\n", argv[ARG_BRKFILE]);
        return 1;
    }

    if ( (points = get_breakpoints(fp, &npoints)) == NULL ) {
        printf("Error: no breakpoints read.\n");
        error++;
        goto exit;
    }

    if ( npoints < 2 ) {
        printf("Error: at least two breakpoints required.\n");
        error++;
        goto exit;
    }

    /* we require breakpoints to start from 0 */
    if ( points[0].time != 0.0 ) {
        printf("Error in breakpoint data: first time must be 0.0\n");
        error++;
        goto exit;
    }

    /* check if breakpoint values are in range */
    if ( !inrange(points, 0.0, 1.0, npoints) ) {
        printf("Error in breakpoint data: values out of range 0 to 1\n");
        error++;
        goto exit;
    }

    /* start up portsf */
    if ( psf_init() ) {
        printf("Error: unable to start portsf.\n");
        return 1;
    }

    /* open infile */ 
    if ( (ifd = psf_sndOpen(argv[ARG_INFILE], &inprops, 0)) < 0 ) {
        printf("Error: unable to open \"%s\"\n", argv[ARG_INFILE]);
        return 1;
    }

    /* check if infile is 8-bit */
    if ( inprops.samptype == PSF_SAMP_8 ) {
        printf("Error: portsf does not support 8-bit soundfiles.\n");
        error++;
        goto exit;
    }

    /* check if infile is in mono */
    if ( inprops.chans != 1 ) {
        printf("Error: infile must be mono.\n");
        error++;
        goto exit;
    }

    /*
        properties of infile and outfile will be the same except infile
        is mono and outfile is stereo
    */
    outprops = inprops;

    if ( (ofd = psf_sndCreate(argv[ARG_OUTFILE], &outprops, 0, 0, PSF_CREATE_RDWR)) < 0 ) {
        printf("Error: unable to create \"%s\"\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

   /* check if outfile extension is one we know about */
    if ( (outformat = psf_getFormatExt(argv[ARG_OUTFILE])) == PSF_FMT_UNKNOWN ) {
            printf("Outfile name \"%s\" has unknown format.\n"
                "Use any of .wav .aiff .aif .afc .aifc", argv[ARG_OUTFILE]
                );
            error++;
            goto exit;
    }

    /* allocate space for input and output frame buffer */
    inframe = (float*)malloc(sizeof(float) * inprops.chans * NFRAMES);

    /* init time position counter for reading envelope */
    incr = 1.0 / inprops.srate;

    /* setup counters to track through the breakpoint data */
    curpos = 0.0;
    ileft = 0;
    iright = 1;

    /* setup firt span */
    leftpoint = points[ileft];
    rightpoint = points[iright];
    
    width = rightpoint.time - leftpoint.time;
    height = rightpoint.value - leftpoint.value;

    int more_points = 1;

    while ( (framesread = psf_sndReadFloatFrames(ifd, inframe, NFRAMES)) > 0 ) {
        int i;
	    double thisamp = rightpoint.value;
        for ( i = 0; i < framesread; i++ ) {
            if ( more_points ) {
                if ( width == 0 ) {
                    thisamp = rightpoint.value;
                } else {
                    /* not vertical: get interpolation value from this span */
                    frac = (curpos - leftpoint.time) / width;
                    thisamp = leftpoint.value + ( height * frac );
                }
                /* move up ready for next sample */
                curpos += incr;
                if ( curpos > rightpoint.time ) { /* go to the next span? */
                    ileft++;
                    iright++;

                    if (iright < npoints) { /* have another span, go */
                        leftpoint = points[ileft];
                        rightpoint = points[iright];
                        width = rightpoint.time - leftpoint.time;
                        height = rightpoint.value - leftpoint.value;
                    } else {
                        more_points = 0;
                    }
                }
            }    
                
            inframe[i] = (float)(inframe[i] * thisamp);
        }

        if ( psf_sndWriteFloatFrames(ofd, inframe, framesread) != framesread ) {
            printf("Error writing to outfile.\n");
            error++;
            break;
        }
    }

    printf("Done.\n");

    exit:
    if (fp)
        fclose(fp);
    
    if (points)
        free(points);
    
    if (ifd)
        psf_sndClose(ifd);

    if (ofd)
        psf_sndClose(ofd);
    
    if (inframe)
        free(inframe);
    
    psf_finish();

    return error;
}
