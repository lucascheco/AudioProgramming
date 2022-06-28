/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, tabgen.
    Date:        27/06/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <breakpoints.h>
#include <math.h>
#include <gtable.h>
#include <time.h>

#define NFRAMES 100

enum {ARG_PROGNAME, ARG_OUTFILE, ARG_CHANS, ARG_SAMPTYPE, ARG_TYPE, ARG_DUR, ARG_SRATE, ARG_AMP, ARG_FREQ, ARG_NHARMS, ARG_NARGS};

enum {WAVE_TRIANGLE, WAVE_SQUARE, WAVE_SAWUP, WAVE_SAWDOWN, WAVE_NTYPES};

int main(int argc, char** argv) {

    /* { Stage 1 } - Define variables */
    PSF_PROPS outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;
    int chans = 1;
    int sampType = PSF_SAMP_16;

    /* init all resources vals to default states */
    int ofd = -1;
    int error = 0;
    float* outframe = NULL;

    double srate, amp, freq, dur;
    unsigned long nbufs, outframes, remainder, nframes = NFRAMES;

    PSF_CHPEAK* peaks = NULL;
    
    /* gtable */
    GTABLE* gtable = NULL;
    unsigned long tabsize = 1024;
    unsigned long nharms;

    OSCILT* p_osc;
    double phase = 0.0;
    int wavetype = WAVE_TRIANGLE;

    /* Adding support to amplitude and frequency breakpoints */
    BRKSTREAM* ampStream = NULL;
    FILE *fpAmp = NULL;
    unsigned long brkAmpSize = 0;
    double minVal, maxVal;

    BRKSTREAM* freqStream = NULL;
    FILE *fpFreq = NULL;
    unsigned long brkFreqSize = 0;
    double minFreq, maxFreq;
    
	double ampbuf[NFRAMES];
	double freqbuf[NFRAMES];

    /* Measuring Processing time */
    clock_t starttime, endtime;


    /* { Stage 2 } - Obtain and validate arguments from user. */

    if ( argc != ARG_NARGS ) {
        printf("Error: insufficient number of arguments.\n"
               "Usage: tabgen outfile nChannels samptype wavetype dur srate amp freq nharms\n"
               "where wavetype is one of:\n"
               "\t0 = triangle\n"
               "\t1 = square\n"
               "\t2 = sawtooth up\n"
               "\t3 = sawtooth down\n"
               "dur = duration in seconds\n"
               "srate = sampling rate in Hz\n"
               "amp = amplitude value or breakpoint file (0 < amp <= 1.0)\n"
               "freq = frequency in Hz or breakpoint file > 0\n"
               "nharms = number of harmonics\n"
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

    if ( (wavetype = atoi(argv[ARG_TYPE])) < 0 || wavetype >= WAVE_NTYPES ) {
    	printf("Error: wavetype must be between 0 and %d.\n"
               "use the enum list: WAVE_SINE, WAVE_TRIANGLE, WAVE_SQUARE, WAVE_SAWUP, WAVE_SAWDOWN\n", WAVE_NTYPES);
    	return 1;
    }

    chans = atoi(argv[ARG_CHANS]);   
    if (chans < 0 || chans > 8) {
        printf("Warning: The number of channels must be: 0 < chans < 8\n"
               "Setting default mono file...\n");
        chans = 1;
    }
    
    sampType = atoi(argv[ARG_SAMPTYPE]);
    if (sampType < PSF_SAMP_8 || sampType > PSF_SAMP_IEEE_FLOAT) {
        printf("Warning: The sample type must be a valid enum or number between 1 and 8\n"
               "Setting default (1)16-bit file...\n");
        sampType = PSF_SAMP_16;
    }

    /* define outfile format - this sets mono 16-bit format */
    outprops.srate = srate;
    outprops.chans = chans;
    outprops.samptype = (psf_stype)sampType; /* or whateveris required */
    outprops.chformat = STDWAVE;

    outframes = (unsigned long) (dur * outprops.srate + 0.5);
    nbufs     = outframes  / nframes;
    remainder = outframes - nbufs * nframes;

    if ( remainder > 0 )
	    nbufs++;

    fpAmp = fopen(argv[ARG_AMP], "r");
    if (fpAmp == NULL) {
        amp = strtod(argv[ARG_AMP], NULL);
        if (amp == 0) {
            printf("Error: Non-numeric value.\n");
            error++;
            goto exit;
        }

        if (amp < 0.0 || amp > 1.0) {
            printf("Error: Amplitude must be greater than 0 and less than 1.0.\n");
            error++;
            goto exit;
        }

        for(int i = 0; i < NFRAMES; ++i)
			ampbuf[i] = amp;
    } else {
        ampStream = bps_newstream(fpAmp, outprops.srate, &brkAmpSize);
        if (bps_getminmax(ampStream, &minVal, &maxVal)) {
            printf("Error readins range of breakpoint file %s.\n", argv[ARG_AMP]);
            error++;
            goto exit;
        }

        if (minVal < 0.0 || minVal > 1.0 || maxVal < 0.0 || maxVal > 1.0) {
            printf("Error: amplitude values out of range in file %s: "
                   "0.0 < amp <= 1.0\n", argv[ARG_AMP]);
            error++;
            goto exit;
        }
    }

    fpFreq = fopen(argv[ARG_FREQ], "r");
    if (fpFreq == NULL) {
        freq = atof(argv[ARG_FREQ]);
        if (freq <= 0.0) {
            printf("Error: Frequency must be greater than 0.0.\n");
            error++;
            goto exit;
        }
        
        for(int i = 0; i < NFRAMES; ++i)
			freqbuf[i] = freq;
    } else {
        freqStream = bps_newstream(fpFreq, outprops.srate, &brkFreqSize);
        if (bps_getminmax(freqStream, &minFreq, &maxFreq)) {
            printf("Error readins range of breakpoint file %s.\n", argv[ARG_FREQ]);
            error++;
            goto exit;
        }

        if (minFreq < 0.0 || maxFreq < 0.0) {
            printf("Error: frequency values out of range in file %s: "
                   "freq > 0.0\n", argv[ARG_FREQ]);
            error++;
            goto exit;
        }
    }

    nharms = atoi(argv[ARG_NHARMS]);
    if (nharms < 1) {
        printf("Error: number of harmonics must be at least 1.\n");
        error++;
        goto exit;
    }

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

    if ( (ofd = psf_sndCreate(argv[ARG_OUTFILE], &outprops, 0, 0, PSF_CREATE_RDWR)) < 0 ) {
        printf("Error: unable to create \"%s\"\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Constructing GTABLE */
    switch (wavetype)
    {
    case WAVE_SQUARE:
        gtable = new_square(tabsize, nharms);
        break;
    case WAVE_TRIANGLE:
        gtable = new_triangle(tabsize, nharms);
        break;
    case WAVE_SAWDOWN:
        gtable = new_saw(tabsize, nharms, 0);
        break;
    case WAVE_SAWUP:
        gtable = new_saw(tabsize, nharms, 1);   
        break;
    }

    p_osc = new_oscilt(srate, gtable, phase);
    if(p_osc == NULL){
        puts("no memory for oscillators\n");
        error++;
        goto exit;
    }


    /* { Stage 4 } - Perform main processing loop. */

    printf("processing....\n");
    starttime = clock();
    /* Loop right here */
    for ( int i = 0; i < nbufs; ++i ) {
    	if ( i == nbufs - 1 )
		    nframes = remainder;

	    for ( int j = 0; j < nframes; ++j ) {
            double val = 0.0;
            if (ampStream)
                amp = bps_tick(ampStream);
            if (freqStream)
                freq = bps_tick(freqStream);
            
            val = tabitick(p_osc, freq);
            for (long k = 0; k < chans; ++k) {
                outframe[j * outprops.chans + k] = (float)(val  * amp);
            }
        }

        if ( psf_sndWriteFloatFrames(ofd, outframe, nframes) != nframes ) {
			printf("Error writing to outfile\n");
		    error++;
		    break;
	    }

    }
    endtime = clock();
    printf("Elapsed time = %f secs\n", (endtime - starttime) / (double)CLOCKS_PER_SEC);


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

    if (ampStream) {
        bps_freepoints(ampStream);
        free(ampStream);
    }

    if (fpAmp)
        if (fclose(fpAmp))
            printf("Error closing amplitude breakpoint file %s\n", argv[ARG_AMP]);

    if (freqStream) {
        bps_freepoints(freqStream);
        free(freqStream);
    }

    if (fpFreq)
        if (fclose(fpFreq))
            printf("Error closing frequency breakpoint file %s\n", argv[ARG_FREQ]);
    if (gtable)
        gtable_free(&gtable);
        
    free(p_osc);

    psf_finish();

    return error;
}
