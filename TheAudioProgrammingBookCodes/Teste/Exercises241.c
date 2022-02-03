/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Code  from "The Audio Programming Book", chapter 2, exercises 2.4.1.
    Date:        30/12/2021
************************************************************************************/

/* In the case of only two breakpoints supplied, necessarily they both has time 0.0, 
   and while I was writing the code, I set 'thisamp' to take the last rightpoint value when
   there are not more points. If we do not add this code, the compiler will problably assume
   a value, in my case 0, and the soundfile will be muted.
      
*/
