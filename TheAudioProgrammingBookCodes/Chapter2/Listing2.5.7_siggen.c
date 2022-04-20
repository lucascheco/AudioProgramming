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

    /* { Stage 1 } - Define variables */
    PSF_PROPS outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;

    /* init all resources vals to default states */
    int ofd = -1;
    int error = 0;
    float* outframe = NULL;

    double srate, amp, freq, dur;
    unsigned long nbufs, outframes, remainder, nframes = NFRAMES;

    /* Missing variables */
    PSF_CHPEAK* peaks = NULL;
    OSCIL* p_osc = NULL;


    /* { Stage 2 } - Obtain and validate arguments from user. */

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

    /* define outfile format - this sets mono 16-bit format */
    outprops.srate = srate;
    outprops.chans = 1;
    outprops.samptype = (psf_stype)PSF_SAMP_16; /* or whateveris required */
    outprops.chformat = STDWAVE;

    outframes = (unsigned long) (dur * outprops.srate + 0.5);
    nbufs     = outframes  / nframes;
    remainder = outframes - nbufs * nframes;

    if ( remainder > 0 )
	    nbufs++;


    /* start up portsf */
    if ( psf_init() ) {
        printf("Error: unable to start portsf.\n");
        return 1;
    }

    /* check if outfile extension is one we know about */
    if ( (outformat = psf_getFormatExt(argv[ARG_OUTFILE])) == PSF_FMT_UNKNOWN ) {
            printf("Outfile name \"%s\" has unknown format.\n"
                "Use any of .wav .aiff .aif .afc .aifc", argv[ARG_OUTFILE]
                );
            error++;
            goto exit;
    }
    outprops.format = outformat;


    /* { Stage 3 } - Allocate memory, open outfile. */

    if ((outframe = (float*) malloc(nframes * outprops.chans * sizeof(float))) == NULL) {
	    puts("No memory!\n");
	    error++;
	    goto exit;
    }

    /* Peak Chunk */
    if ( (peaks = (PSF_CHPEAK*)malloc(outprops.chans * sizeof(PSF_CHPEAK))) == NULL ) {
        puts("No memory!");
        error++;
        goto exit;
    }

    /* Oscilator allocation */
    if ( (p_osc = new_oscil(outprops.srate)) == NULL ) {
        puts("No memory for oscillator\n");
        error++;
        goto exit;
    }

    if ( (ofd = psf_sndCreate(argv[ARG_OUTFILE], &outprops, 0, 0, PSF_CREATE_RDWR)) < 0 ) {
        printf("Error: unable to create \"%s\"\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }


    /* { Stage 4 } - Perform main processing loop. */

    /* Loop right here */
    for ( int i = 0; i < nbufs; ++i ) {
    	if ( i == nbufs - 1 )
		    nframes = remainder;

	    for ( int j = 0; j < nframes; ++j ) {
		    outframe[j] = (float) (amp * tritick(p_osc, freq));
        }

        if ( psf_sndWriteFloatFrames(ofd, outframe, nframes) != nframes ) {
			printf("Error writing to outfile\n");
		    error++;
		    break;
	    }

    }


    /* { Stage 5 } - Report to the user */

    printf("Done.\n");

    /* Report peak values to the user */
    if ( psf_sndReadPeaks(ofd, peaks, NULL) > 0 ) {
        long i;
        double peaktime;
        printf("PEAK information:\n");
        for (i = 0; i < outprops.chans; i++) {
            peaktime = (double) peaks[i].pos / (double) outprops.srate;
            printf("CH %d:\t%.4f at %.4f secs\n", i+1, peaks[i].val, peaktime);
        }
    }


    /* { Stage 6 } - Close files, free memory. */

    exit:

    if (ofd >= 0)
        if ( psf_sndClose(ofd) )
            printf("Error closing outfile %s\n", argv[ARG_OUTFILE]);

    if (outframe)
        free(outframe);

    if (peaks)
        free(peaks);

    if (p_osc)
        free(p_osc);

    psf_finish();

    return error;
}
