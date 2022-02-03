/*******************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.3.4 .
    Date:        16/11/2021
********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <math.h>
#include <breakpoints.h>


int main(int argc, char** argv)
{
    PANPOS pos, pos2;
    int framesread;

    int error = 0;
    float* outbuffer = NULL;
    float* outbuffer2 = NULL;
    BREAKPOINT* points = NULL;
    
    points = (BREAKPOINT*)calloc(2, sizeof(BREAKPOINT));

    points[0].time = 0.0;
    points[1].time = 128.0;

    points[0].value = -1.0;
    points[1].value = 1.0;

    FILE *cp, *sp;
    cp = fopen("const_power_pan.txt", "w");
    sp = fopen("simple_pan.txt", "w");


    outbuffer = (float*)calloc(128, sizeof(float) * 2);
    outbuffer2 = (float*)calloc(128, sizeof(float) * 2);
    
    unsigned long pointnum = 1;
   
    int count = 0;
    int i, out_i, out_j, out_p, out_p2;
    int i_print, j_print;
    double stereopos;  
    double power, power2;

    i = 0;
    out_i = 0;
    out_j = 0;
    out_p = 0;
    out_p2 = 0;
    i_print = 0;
    j_print = 0;
    framesread = 1;
    
    while ( count < 128 ) {
            
        stereopos = val_at_brktime(points, 2, &pointnum, (float)count);
        pos       = constpower(stereopos);
	pos2	  = simplepan(stereopos);
        outbuffer[out_i++] = (float)(1.0 * pos.left);
        outbuffer[out_i++] = (float)(1.0 * pos.right);

	outbuffer2[out_j++] = (float)(1.0 * pos2.left);
	outbuffer2[out_j++] = (float)(1.0 * pos2.right);

	//fprintf(cp, "%lf %lf\n", outbuffer[i_print++], outbuffer[i_print++]);
        //fprintf(sp, "%lf %lf\n", outbuffer2[j_print++], outbuffer2[j_print++]);

	power = sqrt(pow(outbuffer[out_p++], 2) + pow(outbuffer[out_p++], 2));
	power2 = sqrt(pow(outbuffer2[out_p2++], 2) + pow(outbuffer2[out_p2++], 2));

	fprintf(cp, "%lf\n", power);
	fprintf(sp, "%lf\n", power2);


	count++;
    }

    printf("Done.\n");
    
    fclose(cp);
    fclose(sp);

    free(outbuffer);
    free(outbuffer2);
    free(points);

    return error;
}
