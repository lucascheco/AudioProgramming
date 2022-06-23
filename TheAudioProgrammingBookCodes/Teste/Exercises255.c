/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Exercise from "The Audio Programming Book", chapter 2, exercises 2.5.5.
    Date:        22/06/2022
************************************************************************************/

/* Macro updated on wave.h file */
#define UPDATE_FREQ(p_osc, freq) (p_osc->curfreq) != (freq) ? (p_osc->curfreq = freq), (p_osc->incr = ((freq)*p_osc->twopiovrsr)) : 1 
