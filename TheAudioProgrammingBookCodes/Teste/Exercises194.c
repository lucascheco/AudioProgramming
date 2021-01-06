/*********************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise1.9.4 .
    Date:        02/08/2020
**********************************************************************************/

/* tforkraw.c gen raw sfile with native endiannes */
/* based on tfork2.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif // !M_PI#define M_PI (3.141592654)

enum          {ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, ARG_SR, ARG_AMP, ARG_TYPE, ARG_NARGS};
enum samptype {RAWSAMP_SHORT, RAWSAMP_FLOAT};

/* thanks to the SNDAN for this */
/* return 0 for big-endian machine, 1 for little-endian machine */

int byte_order()
{
    int one = 1;
    char *endptr = (char *)&one;

    return (*endptr);
}

const char *endinness[2] = {"big_endian", "little_endian"};

int main(int argc, char **argv)
{
    unsigned int i, nsamps;                         /* Contador(i) ** Número de Samples(nsamps) */
    unsigned int maxframe = 0;                      
    unsigned int samptype, endian, bitreverse;      /* On the if statement(samptype) ** To receive the return of byteOrder function(endian) ** (bitreverse) */
    double       samp, dur, freq, srate, amp, step; /* Handle samples values(samp) ** To take duration argument(dur) ** To take frequency argument(freq) ** To take sample rate argument(srate) ** To take amp argument(amp) ** (step) */
    double       start, end, fac, maxsamp;          
    double       twopi = 2.0 * M_PI;                /* To calculate 2PI */
    double       angleincr;                     
    FILE        *fp = NULL;                         
    float        fsamp;                             
    short        ssamp;                             

    if (argc != ARG_NARGS)
    {
        printf("Usage:  tforkraw outsfile.raw dur freq srate amp isfloat\n");
        return 1;
    }

    dur      = atof(argv[ARG_DUR]);
    freq     = atof(argv[ARG_HZ]);
    srate    = atof(argv[ARG_SR]);
    amp      = atof(argv[ARG_AMP]);
    samptype = (unsigned int)atoi(argv[ARG_TYPE]);

    if (samptype >  1) 
    {
        printf("error: sampletype can be only 0 or 1\n");
        return 1;
    }

    /* create binary file: not all systems require the 'b' */
    fp = fopen(argv[ARG_OUTFILE], "wb");

    if (fp == NULL)
    {
        fprintf(stderr, "Error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    nsamps = (int)(dur * srate);
    angleincr = twopi * freq / srate;
    step = dur / nsamps;

    /* normalized range always - just scale by amp */
    start = 1.0;
    end = 1.0e-4;
    maxsamp = 0.0;
    fac = pow(end / start, 1.0 / nsamps);
    endian = byte_order();

    if (0 > printf("Writing %d %s samples\n", nsamps, endinness[endian]))
    {
        fprintf(stderr, "error: unable to print on STDOUT stream.\n");
        return 1;
    }

    /* run the loop for this samptype */
    if (samptype == RAWSAMP_SHORT)
    {
        for (i = 0; i < nsamps; i++)
        {
            samp = amp * cos(angleincr * i);
            samp *= start;
            start *= fac;
            
            /* use 32767 to avoid overflow problem */
            ssamp = (short)(samp * 32767.0);

            if (fwrite(&ssamp, sizeof(short), 1, fp) != 1)
            {
                printf("Error writing data to file\n");
                return 1;
            }

            if (fabs(samp) > maxsamp)
            {
                maxsamp = fabs(samp);
                maxframe = i;
            }
        }
    }
    else
    {
        for (i = 0; i < nsamps; i++)
        {
            samp = amp * cos(angleincr * i);
            samp *= start;
            start *= fac;
            fsamp = (float)samp;

            if (fwrite(&fsamp, sizeof(float), 1, fp) != 1)
            {
                printf("Error writing data to file\n");
                return 1;
            }

            if (fabs(samp) > maxsamp)
            {
                maxsamp = fabs(samp);
                maxframe = i;
            }
        }        
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "error: unable to close the FILE stream\n");
        return 1;
    }

    printf("done. Maximum sample value = %.8lf at frame %d\n", maxsamp, maxframe);
    
    return 0;
}
/* 
    sin function
                       *
                    *  *  * 
                 *  *  *  *  *
              *  *  *  *  *  *  *
           *  *  *  *  *  *  *  *  *
        *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
                                         *  *  *  *  *  *  *  *  *          
                                            *  *  *  *  *  *  *  
                                               *  *  *  *  *  
                                                  *  *  *
                                                     *  
            
*/

/* 
    cos function
        *                                                           *
        *  *                                                     *  *
        *  *  *                                               *  *  *
        *  *  *  *                                         *  *  *  *                   
        *  *  *  *  *                                   *  *  *  *  *
        *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
                          *  *  *  *  *  *  *  *  *     
                             *  *  *  *  *  *  *   
                                *  *  *  *  *      
                                   *  *  *           
                                      *              
            
*/