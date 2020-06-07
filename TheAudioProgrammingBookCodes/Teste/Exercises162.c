//Author: Lucas Pacheco.
//Description: Test exercise from "The Audio Programming Book", exercise 1.6.2 .
//Date: 04/06/2020.

/*
    (a) N = 19 / startval = 60
        ratio = 1.059 ...
        c5 = 261.625 ...
        c0 = 8.175 ...
        basefreq = 261.625 ...
        ratio = 1.037 ...

        intervals[0] = 261.625 ...
        intervals[1] = 271.346 ...
            .
            .
            .

        output:
            0:  1.000000    261.625565
            1:  1.037155    271.346275
                .
                .
                .
*/

/*
    (b) output:
            error: unrecognized option -

*/

/*
    (c) // I think that the compiler will try atoi(m), m has a ASCCI value of  109
        // So the error out of range will be triggered
            
            output:
                error: N out of range. Must be between 1 and  24.

*/

/*
    (d) // I think that the compiler will try atof(startval), probably return a negative value.
        
            output:
                error: frequency startval must be positive.
                
*/