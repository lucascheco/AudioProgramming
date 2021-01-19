/****************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.2.1 sfpeak .
    Date:        14/01/2021
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

enum
{
    ARG_PROGNAME,
    ARG_INFILE,
    ARG_BUFFERSIZE, 
    ARG_NARGS
};

double maxsample(float* buf, unsigned long blocksize);

int main(int argc, char* argv[])
{
/*STAGE(1)*/
    PSF_PROPS props;
    long framesread;
    int ifd = -1;
    int error = 0;

    psf_format informat = PSF_FMT_UNKNOWN;
    
    PSF_CHPEAK *peaks = NULL;
    float *frame = NULL; 

    int buffer_size = atoi(argv[ARG_BUFFERSIZE]);
    int soundsize;
    double inpeak;

/*STAGE(2)*/
    printf("SFPEAK: report the maximum peak value.\n");

    if (argc < ARG_NARGS)
    {
        printf("insufficient arguments.\n"
               "usage:\n\tsfgain infile buffer_size\n");

        return 1;
    }
    
    if (psf_init())
    {
        printf("unable to start portsf\n");

        return 1;
    }

    if ((ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0)) < 0)
    {
        printf("Error: unable to open infile %s\n", argv[ARG_INFILE]);

        return 1;
    }

    soundsize = psf_sndSize(ifd);
    informat  = psf_getFormatExt(argv[ARG_INFILE]); 

    if (informat == PSF_FMT_UNKNOWN)
    {
        printf("outfile name %s has unknown format.\n"
               "Use any of .wav, .aiff, .aif, .afc\n", argv[ARG_INFILE]);

        error++;
        goto exit;
    }

    if ((frame = (float *)malloc(props.chans * sizeof(float) * buffer_size)) == NULL)
    {
        puts("No memory!\n");

        error++;
        goto exit;
    }

    if ((peaks = (PSF_CHPEAK *)malloc(props.chans * sizeof(PSF_CHPEAK))) == NULL)
    {
        puts("No memory!\n");

        error++;
        goto exit;
    }

    if (psf_sndReadPeaks(ifd, peaks, NULL) > 0)
    {
        long i;

        for (i = 0; i < props.chans; i++)
        {
            if (peaks[i].val > inpeak)  
                inpeak = peaks[i].val;
        }
    }
    else
    {
        framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);

        while (framesread == buffer_size)
        {
            double thispeak;
            unsigned long blocksize = props.chans * buffer_size;

            thispeak = maxsample(frame, blocksize);

            if (thispeak > inpeak)
                inpeak = thispeak;

            framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
        }

        if ((psf_sndSeek(ifd, 0, PSF_SEEK_SET)) < 0)
        {
            printf("Error: unable to rewind infile.\n");
            error++;
            goto exit;
        }
    }
    
    if (inpeak == 0.0)
    {
        printf("infile is silent! Outfile not created.\n");
        goto exit;
    }
    else
    {
        printf("infile is not silent!\n");
        
        printf("Maximum peak: %.2lfdB or %lf raw Value\n", 20.0 * log10(inpeak), inpeak);
    }

    exit:
        if (ifd >= 0)
            psf_sndClose(ifd);

        if (frame)
            free(frame);
        
        if (peaks)
            free(peaks);

        psf_finish();

        return error;

    return 0;
}

double maxsample(float* buf, unsigned long blocksize)
{
    double absval, peak = 0.0;
    unsigned long i;

    for (i = 0; i < blocksize; i++)  
    {
        absval = fabs(buf[i]);

        if (absval > peak)
            peak = absval;
    }

    return peak;
}