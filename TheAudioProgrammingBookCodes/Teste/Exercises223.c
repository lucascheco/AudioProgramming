/*******************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.2.3 sfnorm doc.
    Date:        18/01/2021
********************************************************************************************/

/*
    This program applies gain based on the highest peak of the sound file and has the same 
    functionalities of the previous programs, you can loop how many times you want(N) in a 
    specific range(Limit).
    
    If you want just to apply gain, set limit and N to 0. If ampfac == -0dB, the highest
    peak would be 0.0dB and the rest will boost on the same ratio. 
*/