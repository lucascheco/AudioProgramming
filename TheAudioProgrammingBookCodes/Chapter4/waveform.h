/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 4, 'waveform.h'.
    Date:        05/11/2022
************************************************************************************/
#include <stdio.h>

enum FORMULAE { SINE, COSINE };
typedef enum FORMULAE FORMULA;

typedef struct Waveform {
    int size;
    double samples[1];
} WAVE;
typedef WAVE *WAVEFORM;

typedef char *FILE_HANDLE;

typedef double SPEED;

typedef int OUTPUT;

#define sr (44100)

WAVEFORM readform(FILE_HANDLE);
WAVEFORM createformula(FORMULA);
void copywaveform(WAVEFORM, SPEED, OUTPUT, double);

OUTPUT initialize_sound(char *name, int srate);
int output_sample(OUTPUT out, double sample);
int close_sound(OUTPUT out);
