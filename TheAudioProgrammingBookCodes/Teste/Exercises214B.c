/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.1.4 (b).
    Date:        14/01/2021
************************************************************************************/

/* sfprop.c: convert soundfile to floats */
/* Added 1 2 3 as stages to guide the reading better */
#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>

enum
{
    ARG_PROGNAME,
    ARG_INFILE,
    ARG_OUTFILE,
    ARG_BUFFERSIZE,
    ARG_LIMIT,
    ARG_NARGS
};

int main(int argc, char *argv[])
{
    PSF_PROPS props;
    long framesread, totalread;

    /* init all resource vars to default states */
    int ifd = -1, ofd = -1;
    int error = 0;

    psf_format outformat = PSF_FMT_UNKNOWN, informat = PSF_FMT_UNKNOWN;
    PSF_CHPEAK *peaks = NULL;
    float *frame = NULL;
    int buffer_size = atoi(argv[ARG_BUFFERSIZE]);

    int soundsize;
    int progress = 0;
    int limit = atoi(argv[ARG_LIMIT]);


/* (1) */
    printf("SFPROP: Display information about a soundfile.\n");
    /* Argument checking */
    if (argc < ARG_NARGS)
    {
        printf("insufficient arguments.\n"
               "usage:\n\tsfprop infile outfile buffer_size Limit\n");

        return 1;
    }

    /* startup portsf */
    if (psf_init())
    {
        printf("unable to start portsf\n");
        return 1;
    }

    /* open the input sound file */
    ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0);
    /* error checking */
    if (ifd < 0)
    {
        printf("Error: unable to open infile %s\n", argv[ARG_INFILE]);

        return 1;
    }

    /* Take the size in multi channel frames of the sound file */
    soundsize = psf_sndSize(ifd);
    /* bounderies checking of limit */
    /* Limit must be greater than buffer_size also */
    if (limit > soundsize || limit < buffer_size)
    {
        printf("Limit must be less than or equal to the length of the file.\n");

        /* if limit is invalid, we can set to the soundsize to run normally */
        limit = soundsize;
    }

    /* check infile extension is one we know about */
    outformat = psf_getFormatExt(argv[ARG_OUTFILE]);
    informat  = psf_getFormatExt(argv[ARG_INFILE]);

    if (outformat == PSF_FMT_UNKNOWN)
    {
        printf("outfile name %s has unknown format.\n"
               "Use any of .wav, .aiff, .aif, .afc, .aifc\n",
               argv[ARG_OUTFILE]);

        error++;
        goto exit;
    }

    /* create the out sound file */
    ofd = psf_sndCreate(argv[ARG_OUTFILE], &props, 0, 0, PSF_CREATE_RDWR);
    /* error checking */
    if (ofd < 0)
    {
        printf("Error: unable to create outfile %s\n", argv[ARG_INFILE]);

        error++;
        goto exit;
    }

    /* Remember is the user responsibility to supply a buffer of at least nFrames * props.chans * sizeof(floats) bytes */
    frame = (float *)malloc(props.chans * sizeof(float)* buffer_size);

    if (frame == NULL)
    {
        puts("No memory!\n");

        error++;
        goto exit;
    }
    /* and allocate space for PEAK info */
    peaks = (PSF_CHPEAK *)malloc(props.chans * sizeof(PSF_CHPEAK));

    if (peaks == NULL)
    {
        puts("No memory!\n");

        error++;
        goto exit;
    }
    
    printf("Sample Rate: %d\n", props.srate);
    printf("Channels: %d\n",    props.chans);

    printf("infile sample type: ");
    switch (props.samptype)
    {
        case PSF_SAMP_8:
            printf("8 bits\n");
            break;
        case PSF_SAMP_16:
            printf("16 bit\n");
            break;
        case PSF_SAMP_24:
            printf("24 bit\n");
            break;
        case PSF_SAMP_32:
            printf("32 bit float\n");
            break;
        case PSF_SAMP_IEEE_FLOAT:
            printf("IEEE float\n");
            break;
        default:
            printf("Unknown\n");
    }

    printf("infile format: ");
    switch (informat)
    {
	    case(PSF_STDWAVE):
            printf("STDWAVE\n");
            break;
        case(PSF_WAVE_EX):
            printf("WAVE\n");
            break;
	    case(PSF_AIFF):
            printf("AIFF\n");
            break;
        case(PSF_AIFC):
            printf("AIFC\n");
            break;
        default:
            printf("UNKNOWN\n");
	}

    printf("infile channel format: ");
    switch (props.chformat)
    {
	    case(STDWAVE):
            printf("STANDARD WAVE\n");
            break;
        case(MC_STD):
            printf("STANDARD\n");
            break;
	    case(MC_MONO):
            printf("MONO\n");
            break;
        case(MC_STEREO):
            printf("STEREO\n");
            break;
        case(MC_QUAD):
            printf("QUAD\n");
            break;
        case(MC_LCRS):
            printf("LCRS\n");
            break;
        case(MC_BFMT):
            printf("BFMT\n");
            break;
        case(MC_DOLBY_5_1):
            printf("DOLBY 5.1\n");
            break;
        case(MC_SURR_5_0):
            printf("SURROUND 5.0\n");
            break;
        case(MC_SURR_7_1):
            printf("SURROUND 7.1\n");
            break;
        case(MC_WAVE_EX):
            printf("WAVE EXTENDED\n");
            break;
        default:
            printf("UNKNOWN\n");
	}

  /* (2) */
    printf("copying...\n");

    /* multi-frame loop to do copy, report any errors */
    framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
    
    /* we force limit to be greater than buffer_size and now we can do this step */

    totalread = 0; /* running count of sample frames */

    while (framesread == buffer_size)
    {
        totalread += buffer_size;
        
        /* Loading Screen */
        printf("%3.1lf%%...\r", (totalread * 100) / (double)limit);

        if (psf_sndWriteFloatFrames(ofd, frame, buffer_size) != buffer_size)
        {
            printf("Error writing to outfile\n");

            error++;
            break;
        }

        /* <--- do any processing here! ---> */
        
        /* make sure the reading and writing is being done within the limit */ 
        if ((totalread + buffer_size) >= limit)
        {
            buffer_size = limit - totalread;
            printf("to limit: %d\n", buffer_size);
            framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
                         psf_sndWriteFloatFrames(ofd, frame, buffer_size);
            totalread += buffer_size;
            break;
        }
        
        framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
    }

    if (framesread < 0)
    {
        printf("Error reading infile. Outfile is incoplete.\n");
        error++;
    }
    else
        printf("Done. %ld sample frames copied to %s with a buffer of %s\n", totalread, argv[ARG_OUTFILE], argv[ARG_BUFFERSIZE]);

    /* report PEAK values to user */
    if (psf_sndReadPeaks(ofd, peaks, NULL) > 0)
    {
        long i;
        double peaktime;

        printf("PEAK information:\n");

        for (i = 0; i < props.chans; i++)
        {
            float decibel = log10(peaks[i].val) * 20.0f;
            peaktime = (double)peaks[i].pos / props.srate;
 
            printf("CH %ld:\t%.4fdB or %.4fAmpRaw at %.4f secs\n", i + 1, decibel, peaks[i].val, peaktime);
        }
    }

/* (3) */
/* do all cleanup */
exit:
    if (ifd >= 0)
        psf_sndClose(ifd);

    if (ofd >= 0)
        psf_sndClose(ofd);

    if (frame)
        free(frame);

    if (peaks)
        free(peaks);

    psf_finish();

    return error;
}