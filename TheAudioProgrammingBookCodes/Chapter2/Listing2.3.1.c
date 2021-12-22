/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, Listing 2.3.1 .
    Date:        16/11/2021
************************************************************************************/

#include <portsf.h>

PANPOS thispos;
int framesread;
int ifd = -1, ofd = -1;
double position = 1.0;

thispos = simplepan(position);

while ( (framesread = psf_sndReadFloatFrames(ifd, inframe, nframes)) > 0 ) {
    int i, out_i;
    for ( i = 0, out_i = 0; i < framesread; i++ ) {
        outframe[out_i++] = (float)(inframe[i] * thispos.left);
        outframe[out_i++] = (float)(inframe[i] * thispos.right);
    }

    if ( psf_sndWriteFloatFrames(ofd, outframe, framesread) != framesread ) {
        printf("Error writing to outfile\n");
        error++;
        break;
    }
}
