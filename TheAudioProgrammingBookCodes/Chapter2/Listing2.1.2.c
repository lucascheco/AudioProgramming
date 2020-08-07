/*
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, Listing2.1.2 .
    Date:        07/08/2020
*/
#include <stdio.h>
#include "portsf.h"

int check_sampletype(psf_stype type)
{
    int accept = 1;

    printf("sample type ");

    switch (type)
    {
        case (PSF_SAMP_8):
            printf("8 bit \n");
            accept  = 0;       /* No 8-bit files! */
            break;
        case (PSF_SAMP_16):
            printf("16 bit \n");
            break;
        case (PSF_SAMP_24):
            printf("24 bit \n");
            break;
        case (PSF_SAMP_32):
            printf("32 bit (integer)\n");
            break;
        case (PSF_SAMP_IEEE_FLOAT):
            printf("32 bit floating point \n");
            break;
        default:
            printf("unknown\n");
            accept = 0;
    }

    return accept;
}