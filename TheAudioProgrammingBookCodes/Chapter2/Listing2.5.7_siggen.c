/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, siggen.
    Date:        24/01/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <breakpoints.h>
#include <math.h>
#include <wave.h>

#define NFRAMES 100

enum {ARG_PROGNAME, ARG_OUTFILE, ARG_DUR, ARG_SRATE, ARG_AMP, ARG_FREQ, ARG_NARGS};

int main(int argc, char** argv) {
    PSF_PROPS outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;

    /* init all resources vals to default states */
    int ofd = -1;
    int error = 0;
    float outframe = NULL;

    double srate, amp, freq, dur;
    unsigned long nbufs, outframes, remainder, nframes = NFRAMES;

    if ( argc != ARG_NARGS ) {
        printf("Error: insufficient number of arguments.\n"
               "Usage: siggen outfile dur srate amp freq\n"
               );

        return 1;
    }

    if ( (srate = atof(argv[ARG_SRATE])) < 0.0 ) {
    	printf("Error: Must sample rate must be greater than 0. .\n");
    	return 1;
    }
 
    if ( (dur = atof(argv[ARG_DUR])) < 0.0 ) {
    	printf("Error: Must duration must be greater than 0. .\n");
    	return 1;
    }
 
    if ( (amp = atof(argv[ARG_AMP])) < 0.0 ) {
    	printf("Error: Must amp must be greater than 0. .\n");
    	return 1;
    }
 
    if ( (freq = atof(argv[ARG_FREQ])) < 0.0 ) {
    	printf("Error: Must frequency must be greater than 0. .\n");
    	return 1;
    }

    /* start up portsf */
    if ( psf_init() ) {
        printf("Error: unable to start portsf.\n");
        return 1;
    }

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

    if ((outframe = (float) malloc(nframes * outprops.chans * sizeof(float)) == NULL) {
	puts("No memory!\n");
	error++;
	goto exit;	
    }

    
    /* define outfile format - this sets mono 16-bit format */
    outprops.srate = srate;
    outprops.chans = 1;
    outprops.samptype = PSF_SAMP_16; /* or whateveris required */
    outprops.chformat = STDWAVE;

    outframes = (unsigned long) (dur * outprops.srate + 0.5);
    nbufs     = outframes  / nframes;
    remainder = outframes - nbufs * nframes;

    if ( remainder > 0 ) 
	    nbufs++;

    /* Loop right here */
    for ( int i = 0; i < nbufs; ++i ) {
    	if ( i == nbufs - 1 )
		nframes = remainder;

	for ( int j = 0; j < nframes; ++j ) {
		outframe[j] = (float) (amp * sinetick(p_osc, freq));

		if ( psf_sndWriteFloatFrames(ofd, outframe, nframes) != nframes ) {
			printf("Error writing to outfile\n");
			error++;
			break;
		}
	}
    }

    printf("Done.\n");

    exit:
    
    if (ofd)
        psf_sndClose(ofd);
    
    psf_finish();

    return error;
}
