/*******************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.2.4 (b) .
    Date:        19/01/2021
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <math.h>
#include <string.h>

enum
{
    ARG_PROGNAME,
    ARG_INFILE,
    ARG_OUTFILE,
    ARG_BUFFERSIZE, 
    ARG_LIMIT,
    ARG_N, /* Number of repetitions, to make a loop */
    ARG_DB,
    ARG_SCL_TYPE, /* The type of scalefactor */
    ARG_NARGS
};

typedef int bool;

int main(int argc, char *argv[])
{
/************/
/**STAGE 1**/
/**********/
    PSF_PROPS props;
    long framesread, totalread, globalsize = 0;

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
    
    int repetitions = atoi(argv[ARG_N]), n = 0;

    int i;
    float ampfac;
    double dbval;

    float scalefactor;
    bool scltype = 1;
    
/************/
/**STAGE 2**/ /************/
/**********/  /**STAGE 3**/
              /**********/
    printf("SFGAIN: change level of soundfiIe\n");
    /* 
        we could make optional flags but for now just
            set buffer = 1
                limit  = 0
                N      = 1 or 0
        to only apply the ampfactor.
     */

    /* Argument checking */
    if (argc < ARG_NARGS)
    {
        printf("insufficient arguments.\n"
               "usage:\n\tsfgain infile outfile buffer_size Limit N dBLevel\n");

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

    switch(argv[ARG_SCL_TYPE][0])
    {
        case 'L':
        case 'l':   
            scltype = 1;
            break;

        case 'E':
        case 'e':
            scltype = 0;
            break;

        default:
            printf("Unvalid scale type. Try L for linear or E for exponential.\n");
            return 1;
    }

    dbval = atof(argv[ARG_DB]);

    if (dbval > 0.0)
    {
        printf("Warning: dbval cannot be positive. \n:->: %s < 0\n", argv[ARG_DB]);

        return 1;
    }
    
    ampfac = (float) pow(10.0, dbval / 20.0);
    /* Take ampfactor argument */

    /* check outfile and infile extension is one we know about */
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
    /* set the props format to the outformat*/ 
    props.format = outformat;

    /* create the out sound file */
    ofd = psf_sndCreate(argv[ARG_OUTFILE], &props, 0, 0, PSF_CREATE_RDWR);
    /* error checking */
    if (ofd < 0)
    {
        printf("Error: unable to create outfile %s\n", argv[ARG_OUTFILE]);

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


    printf("copying...\n");

    /* multi-frame loop to do copy, report any errors */
    framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
    
    /* we force limit to be greater than buffer_size and now we can do this step */

    totalread = 0; /* running count of sample frames */

    if (scltype)
    {
        scalefactor = ampfac;
    }
    else
    {
        scalefactor = (float) pow(10.0, dbval / 20.0);
    }
    

/************/
/**STAGE 4**/
/**********/
    do
    {
        while (framesread == buffer_size)
        {
            totalread += buffer_size;

            /* ampfac applied on each sample */
            for (i = 0; i < props.chans*buffer_size; i++)
            {
                frame[i] *= scalefactor;
            }


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
                /*printf("to limit: %d\n", buffer_size);*/
                framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
                            psf_sndWriteFloatFrames(ofd, frame, buffer_size);
                totalread += buffer_size;
                break;
            }
            
            framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);
        }

        buffer_size = atoi(argv[ARG_BUFFERSIZE]);
        globalsize += totalread;

        totalread = 0;

        if (psf_sndSeek(ifd, SEEK_SET, PSF_SEEK_SET))
        {
            printf("ERROR: Seeking ERROR.\n");
            goto exit;
        }

        framesread = psf_sndReadFloatFrames(ifd, frame, buffer_size);

    } while (++n < repetitions);
/************/
/**STAGE 5**/
/**********/
    if (framesread < 0)
    {
        printf("Error reading infile. Outfile is incoplete.\n");
        error++;
    }
    else
        printf("Done. %ld sample frames copied to %s with a buffer of %s\n", globalsize, argv[ARG_OUTFILE], argv[ARG_BUFFERSIZE]);

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
 
            printf("CH %ld:\t%.4fdB or %.4f AmpRaw at %.4f secs\n", i + 1, decibel, peaks[i].val, peaktime);
        }
    }

/************/
/**STAGE 6**/
/**********/
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