/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 4, 'rd'.
    Date:        05/11/2022
************************************************************************************/

#include "waveform.h"

#include <math.h>

WAVEFORM getnewform(int);
int readfile(WAVEFORM, FILE_HANDLE);
void put_val(WAVEFORM, int, double);
WAVEFORM getnewform(int);

enum ERRORS {
    ERR_NO_FILE = 100,
    ERR_NO_COUNT,
    ERR_NO_DATA,
    ERR_NO_FORMULA,
    ERR_NO_MEMORY
};

void errormsg(char *format, enum ERRORS err)
{
    fprintf(stderr, format, (int)err);
    switch (err) {
        case ERR_NO_FILE:
            printf("\nfile not found.\n");
            return;
        case ERR_NO_COUNT:
            printf("\nno count not found.\n");
            return;
        case ERR_NO_DATA:
            printf("\ndata malformed.\n");
            return;
        case ERR_NO_FORMULA:
            printf("\nfnot a valid formula.\n");
            return;
        case ERR_NO_MEMORY:
            return;

    }
}

int lengthoffile(FILE_HANDLE file) 
{
    WAVEFORM *ff = fopen(file, "r");
    int count;

    if (ff == NULL)
        return 0;
    
    if (fscanf(ff, "%d", &count) != 1) {
        fclose(ff);
        return 0;
    }
    
    fclose(ff);
    return count;
}

WAVEFORM readform(FILE_HANDLE file)
{
    WAVEFORM xx;
    int err;

    xx = getnewform(lengthoffile(file));
    if ((err=readfile(xx, file)) != 0) 
        return xx;

    error("Failed to read wave form for reason %d", err);

    return NULL;  
}

int readfile(WAVEFORM xx, FILE_HANDLE file) 
{
    int count, i;
    double val;
    FILE *ff = fopen(file, "r");

    if (ff==NULL)
        return ERR_NO_FILE;
    
    if (fscanf(ff, "%d", &count) != 1)
        return ERR_NO_COUNT;

    for (i = 0; i < count; i++) {
        if (fscanf(ff, "%f", &val) != 1)
            return ERR_NO_DATA;
        
        put_val(xx, i, val);
    }
    
    fclose(ff);
    return 0;
}

#define TRIG_SIZE (4096)
#define TWOPIBYSIZE (6.28318530718/(double)TRIG_SIZE)

WAVEFORM createformula(FORMULA trig) 
{
    WAVEFORM xx = getnewform(TRIG_SIZE);
    int i;
    double val;

    for (i = 0; i < TRIG_SIZE; i++) {
        if (trig == SINE)
            val = sin((double) i*TWOPIBYSIZE);
        else 
        if (trig == COSINE)
            val = cos((double) i*TWOPIBYSIZE);
        else
            return NULL;
        
        put_val(xx, i, val);
    }
    
    return xx;
}

WAVEFORM getnewform(int size) 
{
    WAVEFORM xx = (WAVEFORM)malloc((size-1) * sizeof(double) + sizeof(WAVE));

    if (xx == NULL) {
        error("Failed to allocate memory\n");
        exit(1);
    }
    
    xx->size = size;
    return xx;
}

void put_val(WAVEFORM xx, int i, double val)
{
    xx->samples[i] = val;
}