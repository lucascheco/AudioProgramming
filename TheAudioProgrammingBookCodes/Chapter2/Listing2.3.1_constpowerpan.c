/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, sfpan.
    Date:        16/01/2021
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <breakpoints.h>

#define NFRAMES 100

enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_BRKFILE, ARG_NARGS};

int main(int argc, char** argv)
{
    PANPOS pos;
    int framesread;
    unsigned long size;
    PSF_PROPS inprops, outprops;
    psf_format outformat = PSF_FMT_UNKNOWN;
    double timeincr, sampletime;

    /* init all resources vals to default states */
    int ifd = -1, ofd = -1;
    int error = 0;
    float* inbuffer  = NULL;
    float* outbuffer = NULL;
    FILE* fp = NULL;
    BREAKPOINT* points = NULL;


    if (argc != ARG_NARGS)
    {
        printf("Error: insufficient number of arguments.\n"
               "Usage: sfpan infile outfile posfile.brk\n"
               "       posfile.brk is a breakpoint file\n"
               "       with values in range -1.0 <= pos <= 1.0\n"
               "       where -1.0 = Full Left, 0 = Center, +1.0 = Full Right.\n"
               );

        return 1;
    }

    /* read breakpoint file and verify it */
    if ((fp = fopen(argv[ARG_BRKFILE], "r")) == NULL)
    {
        printf("Error: unable to open breakpoint file \"%s\"\n", argv[ARG_BRKFILE]);
        return 1;
    }

    if ((points = get_breakpoints(fp, &size)) == NULL)
    {
        printf("Error: no breakpoints read.\n");
        error++;
        goto exit;
    }

    if (size < 2)
    {
        printf("Error: at least two breakpoints required.\n");
        error++;
        goto exit;
    }

    /* we require breakpoints to start from 0 */
    if (points[0].time != 0.0)
    {
        printf("Error in breakpoint data: first time must be 0.0\n");
        error++;
        goto exit;
    }

    /* check if breakpoint values are in range */
    if (!inrange(points, -1, 1, size))
    {
        printf("Error in breakpoint data: values out of range -1 to +1\n");
        error++;
        goto exit;
    }

    /* start up portsf */
    if (psf_init())
    {
        printf("Error: unable to start portsf.\n");
        return 1;
    }

    /* open infile */ 
    if ((ifd = psf_sndOpen(argv[ARG_INFILE], &inprops, 0)) < 0)
    {
        printf("Error: unable to open \"%s\"\n", argv[ARG_INFILE]);
        return 1;
    }

    /* 
        we have a resource, we use goto hereafter
        upon hitting any errors 
    */

    /* check if infile is 8-bit */
    if (inprops.samptype == PSF_SAMP_8)
    {
        printf("Error: portsf does not support 8-bit soundfiles.\n");
        error++;
        goto exit;
    }

    /* check if infile is in mono */
    if (inprops.chans != 1)
    {
        printf("Error: infile must be mono.\n");
        error++;
        goto exit;
    }

    /*
        properties of infile and outfile will be the same except infile
        is mono and outfile is stereo
    */
    outprops = inprops;
    outprops.chans = 2;

    if ((ofd = psf_sndCreate(argv[ARG_OUTFILE], &outprops, 0, 0, PSF_CREATE_RDWR)) < 0)
    {
        printf("Error: unable to create \"%s\"\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

   /* check if outfile extension is one we know about */
    if ((outformat = psf_getFormatExt(argv[ARG_OUTFILE])) == PSF_FMT_UNKNOWN)
    {
            printf("Outfile name \"%s\" has unknown format.\n"
                "Use any of .wav .aiff .aif .afc .aifc", argv[ARG_OUTFILE]
                );
            error++;
            goto exit;
    }

    /* allocate space for input and output frame buffer */
    inbuffer  = (float*)malloc(sizeof(float) * inprops.chans * NFRAMES);
    outbuffer = (float*)malloc(sizeof(float) * outprops.chans * NFRAMES);

    /* init time position counter for reading envelope */
    timeincr = 1.0 / inprops.srate;
    sampletime = 0.0;
    unsigned long pointnum = 1;

    while ((framesread = psf_sndReadFloatFrames(ifd, inbuffer, NFRAMES)) > 0)
    {
        int i, out_i;
        double stereopos;

        for (i = 0, out_i = 0; i < framesread; i++)
        {
            stereopos = val_at_brktime(points, size, &pointnum, sampletime);
            pos       = constpower(stereopos);
           
            outbuffer[out_i++] = (float)(inbuffer[i] * pos.left);
            outbuffer[out_i++] = (float)(inbuffer[i] * pos.right);

            sampletime += timeincr;
        }

        if (psf_sndWriteFloatFrames(ofd, outbuffer, framesread) != framesread)
        {
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
    
    if (inbuffer)
        free(inbuffer);
    
    if (outbuffer)
        free(outbuffer);

    psf_finish();

    return error;
}
