//Author: Lucas Pacheco.
//Description: A tes exercise from "The Audio Programming Book", chapter 1, modifying Listing 1.2 to print sounding length.
//Date: 11/05/2020.

/* listing 1.2. Calculate frequency of a MIDI Note number */
#include <stdio.h>
#include <math.h>
#include <string.h>

// int main()
// {
//     double length; /* . . . which we want to find, */
//     /* 
//         (a)ANSWER:
//         OBS: I'm not sure about the answer.
//     */

//     for (int i = 0; i <= 12; i++)
//     {
//         length = 660.0 * (12.0 * (1.0 / (12.0 + (double)i)));
//         printf("%lf\n", length);
//     }

//     /* (b)ANSWER: Loops. */
 
//     return 0;
// }

/*
    OUTPUT SAMPLE:
        660.000000
        609.230769
        565.714286
        528.000000
        495.000000
        465.882353
        440.000000
        416.842105
        396.000000
        377.142857
        360.000000
        344.347826
        330.000000
        
        Wrong Answer
*/

/* 
    I think, after a review, that's the right answer.
    I decide to make this exercise for all notes.
*/
int main()
{
    char notes[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    double semitone_ratio;
    double c0;        /* for frequency of MIDI Note 0 */
    double c4;        /* for frequency of Middle C */
    double frequency; /* . . . which we want to find, */
    int midinote;     /* . . . given this note. */
    double waveLength;
    int octave = -1;
    double soundVelocity;

    /* calculate required numbers */
    semitone_ratio = pow(2.0, 1 / 12.0); /* approx. 1.0594631 */

    /* find Middle C, three semitones above low A = 220 */
    c4 = 220.0 * pow(semitone_ratio, 3.0);

    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c4 * pow(0.5, 5.0);

    soundVelocity = 660.0 * c4;

    for (int i = 0; i <= 127; i++)
    {
        if (!strcmp("C", notes[i % 12]))
        {
            printf("\n");
            octave++;
        }

        frequency = c0 * pow(semitone_ratio, (double)i);

        waveLength = soundVelocity / frequency;

        if (i > 20)
            printf("Midi = %3d | Note = %4s%2d | WvLenth = %lfcm | Freq = %.5lf\n", i, notes[i % 12], octave - 1, waveLength, frequency);
        else
            printf("Midi = %3d |---------------|-------------------------| Freq = %.5lf\n", i, frequency);

    }

    return 0;
}


/*
    OUTPUSAMPLE:
    Midi =   0 |---------------|-------------------------| Freq = 8.17580
    Midi =   1 |---------------|-------------------------| Freq = 8.66196
    Midi =   2 |---------------|-------------------------| Freq = 9.17702
    Midi =   3 |---------------|-------------------------| Freq = 9.72272
    Midi =   4 |---------------|-------------------------| Freq = 10.30086
    Midi =   5 |---------------|-------------------------| Freq = 10.91338
    Midi =   6 |---------------|-------------------------| Freq = 11.56233
    Midi =   7 |---------------|-------------------------| Freq = 12.24986
    Midi =   8 |---------------|-------------------------| Freq = 12.97827
    Midi =   9 |---------------|-------------------------| Freq = 13.75000
    Midi =  10 |---------------|-------------------------| Freq = 14.56762
    Midi =  11 |---------------|-------------------------| Freq = 15.43385

    Midi =  12 |---------------|-------------------------| Freq = 16.35160
    Midi =  13 |---------------|-------------------------| Freq = 17.32391
    Midi =  14 |---------------|-------------------------| Freq = 18.35405
    Midi =  15 |---------------|-------------------------| Freq = 19.44544
    Midi =  16 |---------------|-------------------------| Freq = 20.60172
    Midi =  17 |---------------|-------------------------| Freq = 21.82676
    Midi =  18 |---------------|-------------------------| Freq = 23.12465
    Midi =  19 |---------------|-------------------------| Freq = 24.49971
    Midi =  20 |---------------|-------------------------| Freq = 25.95654
    Midi =  21 | Note =    A 0 | WvLenth = 6279.013567cm | Freq = 27.50000
    Midi =  22 | Note =   A# 0 | WvLenth = 5926.599615cm | Freq = 29.13524
    Midi =  23 | Note =    B 0 | WvLenth = 5593.965138cm | Freq = 30.86771

    Midi =  24 | Note =    C 1 | WvLenth = 5280.000000cm | Freq = 32.70320
    Midi =  25 | Note =   C# 1 | WvLenth = 4983.656371cm | Freq = 34.64783
    Midi =  26 | Note =    D 1 | WvLenth = 4703.945232cm | Freq = 36.70810
    Midi =  27 | Note =   D# 1 | WvLenth = 4439.933073cm | Freq = 38.89087
    Midi =  28 | Note =    E 1 | WvLenth = 4190.738777cm | Freq = 41.20344
    Midi =  29 | Note =    F 1 | WvLenth = 3955.530683cm | Freq = 43.65353
    Midi =  30 | Note =   F# 1 | WvLenth = 3733.523805cm | Freq = 46.24930
    Midi =  31 | Note =    G 1 | WvLenth = 3523.977215cm | Freq = 48.99943
    Midi =  32 | Note =   G# 1 | WvLenth = 3326.191572cm | Freq = 51.91309
    Midi =  33 | Note =    A 1 | WvLenth = 3139.506784cm | Freq = 55.00000
    Midi =  34 | Note =   A# 1 | WvLenth = 2963.299808cm | Freq = 58.27047
    Midi =  35 | Note =    B 1 | WvLenth = 2796.982569cm | Freq = 61.73541

    Midi =  36 | Note =    C 2 | WvLenth = 2640.000000cm | Freq = 65.40639
    Midi =  37 | Note =   C# 2 | WvLenth = 2491.828185cm | Freq = 69.29566
    Midi =  38 | Note =    D 2 | WvLenth = 2351.972616cm | Freq = 73.41619
    Midi =  39 | Note =   D# 2 | WvLenth = 2219.966536cm | Freq = 77.78175
    Midi =  40 | Note =    E 2 | WvLenth = 2095.369389cm | Freq = 82.40689
    Midi =  41 | Note =    F 2 | WvLenth = 1977.765341cm | Freq = 87.30706
    Midi =  42 | Note =   F# 2 | WvLenth = 1866.761902cm | Freq = 92.49861
    Midi =  43 | Note =    G 2 | WvLenth = 1761.988608cm | Freq = 97.99886
    Midi =  44 | Note =   G# 2 | WvLenth = 1663.095786cm | Freq = 103.82617
    Midi =  45 | Note =    A 2 | WvLenth = 1569.753392cm | Freq = 110.00000
    Midi =  46 | Note =   A# 2 | WvLenth = 1481.649904cm | Freq = 116.54094
    Midi =  47 | Note =    B 2 | WvLenth = 1398.491285cm | Freq = 123.47083

    Midi =  48 | Note =    C 3 | WvLenth = 1320.000000cm | Freq = 130.81278
    Midi =  49 | Note =   C# 3 | WvLenth = 1245.914093cm | Freq = 138.59132
    Midi =  50 | Note =    D 3 | WvLenth = 1175.986308cm | Freq = 146.83238
    Midi =  51 | Note =   D# 3 | WvLenth = 1109.983268cm | Freq = 155.56349
    Midi =  52 | Note =    E 3 | WvLenth = 1047.684694cm | Freq = 164.81378
    Midi =  53 | Note =    F 3 | WvLenth = 988.882671cm | Freq = 174.61412
    Midi =  54 | Note =   F# 3 | WvLenth = 933.380951cm | Freq = 184.99721
    Midi =  55 | Note =    G 3 | WvLenth = 880.994304cm | Freq = 195.99772
    Midi =  56 | Note =   G# 3 | WvLenth = 831.547893cm | Freq = 207.65235
    Midi =  57 | Note =    A 3 | WvLenth = 784.876696cm | Freq = 220.00000
    Midi =  58 | Note =   A# 3 | WvLenth = 740.824952cm | Freq = 233.08188
    Midi =  59 | Note =    B 3 | WvLenth = 699.245642cm | Freq = 246.94165

    Midi =  60 | Note =    C 4 | WvLenth = 660.000000cm | Freq = 261.62557
    Midi =  61 | Note =   C# 4 | WvLenth = 622.957046cm | Freq = 277.18263
    Midi =  62 | Note =    D 4 | WvLenth = 587.993154cm | Freq = 293.66477
    Midi =  63 | Note =   D# 4 | WvLenth = 554.991634cm | Freq = 311.12698
    Midi =  64 | Note =    E 4 | WvLenth = 523.842347cm | Freq = 329.62756
    Midi =  65 | Note =    F 4 | WvLenth = 494.441335cm | Freq = 349.22823
    Midi =  66 | Note =   F# 4 | WvLenth = 466.690476cm | Freq = 369.99442
    Midi =  67 | Note =    G 4 | WvLenth = 440.497152cm | Freq = 391.99544
    Midi =  68 | Note =   G# 4 | WvLenth = 415.773946cm | Freq = 415.30470
    Midi =  69 | Note =    A 4 | WvLenth = 392.438348cm | Freq = 440.00000
    Midi =  70 | Note =   A# 4 | WvLenth = 370.412476cm | Freq = 466.16376
    Midi =  71 | Note =    B 4 | WvLenth = 349.622821cm | Freq = 493.88330

    Midi =  72 | Note =    C 5 | WvLenth = 330.000000cm | Freq = 523.25113
    Midi =  73 | Note =   C# 5 | WvLenth = 311.478523cm | Freq = 554.36526
    Midi =  74 | Note =    D 5 | WvLenth = 293.996577cm | Freq = 587.32954
    Midi =  75 | Note =   D# 5 | WvLenth = 277.495817cm | Freq = 622.25397
    Midi =  76 | Note =    E 5 | WvLenth = 261.921174cm | Freq = 659.25511
    Midi =  77 | Note =    F 5 | WvLenth = 247.220668cm | Freq = 698.45646
    Midi =  78 | Note =   F# 5 | WvLenth = 233.345238cm | Freq = 739.98885
    Midi =  79 | Note =    G 5 | WvLenth = 220.248576cm | Freq = 783.99087
    Midi =  80 | Note =   G# 5 | WvLenth = 207.886973cm | Freq = 830.60940
    Midi =  81 | Note =    A 5 | WvLenth = 196.219174cm | Freq = 880.00000
    Midi =  82 | Note =   A# 5 | WvLenth = 185.206238cm | Freq = 932.32752
    Midi =  83 | Note =    B 5 | WvLenth = 174.811411cm | Freq = 987.76660

    Midi =  84 | Note =    C 6 | WvLenth = 165.000000cm | Freq = 1046.50226
    Midi =  85 | Note =   C# 6 | WvLenth = 155.739262cm | Freq = 1108.73052
    Midi =  86 | Note =    D 6 | WvLenth = 146.998288cm | Freq = 1174.65907
    Midi =  87 | Note =   D# 6 | WvLenth = 138.747909cm | Freq = 1244.50793
    Midi =  88 | Note =    E 6 | WvLenth = 130.960587cm | Freq = 1318.51023
    Midi =  89 | Note =    F 6 | WvLenth = 123.610334cm | Freq = 1396.91293
    Midi =  90 | Note =   F# 6 | WvLenth = 116.672619cm | Freq = 1479.97769
    Midi =  91 | Note =    G 6 | WvLenth = 110.124288cm | Freq = 1567.98174
    Midi =  92 | Note =   G# 6 | WvLenth = 103.943487cm | Freq = 1661.21879
    Midi =  93 | Note =    A 6 | WvLenth = 98.109587cm | Freq = 1760.00000
    Midi =  94 | Note =   A# 6 | WvLenth = 92.603119cm | Freq = 1864.65505
    Midi =  95 | Note =    B 6 | WvLenth = 87.405705cm | Freq = 1975.53321

    Midi =  96 | Note =    C 7 | WvLenth = 82.500000cm | Freq = 2093.00452
    Midi =  97 | Note =   C# 7 | WvLenth = 77.869631cm | Freq = 2217.46105
    Midi =  98 | Note =    D 7 | WvLenth = 73.499144cm | Freq = 2349.31814
    Midi =  99 | Note =   D# 7 | WvLenth = 69.373954cm | Freq = 2489.01587
    Midi = 100 | Note =    E 7 | WvLenth = 65.480293cm | Freq = 2637.02046
    Midi = 101 | Note =    F 7 | WvLenth = 61.805167cm | Freq = 2793.82585
    Midi = 102 | Note =   F# 7 | WvLenth = 58.336309cm | Freq = 2959.95538
    Midi = 103 | Note =    G 7 | WvLenth = 55.062144cm | Freq = 3135.96349
    Midi = 104 | Note =   G# 7 | WvLenth = 51.971743cm | Freq = 3322.43758
    Midi = 105 | Note =    A 7 | WvLenth = 49.054793cm | Freq = 3520.00000
    Midi = 106 | Note =   A# 7 | WvLenth = 46.301559cm | Freq = 3729.31009
    Midi = 107 | Note =    B 7 | WvLenth = 43.702853cm | Freq = 3951.06641

    Midi = 108 | Note =    C 8 | WvLenth = 41.250000cm | Freq = 4186.00904
    Midi = 109 | Note =   C# 8 | WvLenth = 38.934815cm | Freq = 4434.92210
    Midi = 110 | Note =    D 8 | WvLenth = 36.749572cm | Freq = 4698.63629
    Midi = 111 | Note =   D# 8 | WvLenth = 34.686977cm | Freq = 4978.03174
    Midi = 112 | Note =    E 8 | WvLenth = 32.740147cm | Freq = 5274.04091
    Midi = 113 | Note =    F 8 | WvLenth = 30.902583cm | Freq = 5587.65170
    Midi = 114 | Note =   F# 8 | WvLenth = 29.168155cm | Freq = 5919.91076
    Midi = 115 | Note =    G 8 | WvLenth = 27.531072cm | Freq = 6271.92698
    Midi = 116 | Note =   G# 8 | WvLenth = 25.985872cm | Freq = 6644.87516
    Midi = 117 | Note =    A 8 | WvLenth = 24.527397cm | Freq = 7040.00000
    Midi = 118 | Note =   A# 8 | WvLenth = 23.150780cm | Freq = 7458.62018
    Midi = 119 | Note =    B 8 | WvLenth = 21.851426cm | Freq = 7902.13282

    Midi = 120 | Note =    C 9 | WvLenth = 20.625000cm | Freq = 8372.01809
    Midi = 121 | Note =   C# 9 | WvLenth = 19.467408cm | Freq = 8869.84419
    Midi = 122 | Note =    D 9 | WvLenth = 18.374786cm | Freq = 9397.27257
    Midi = 123 | Note =   D# 9 | WvLenth = 17.343489cm | Freq = 9956.06348
    Midi = 124 | Note =    E 9 | WvLenth = 16.370073cm | Freq = 10548.08182
    Midi = 125 | Note =    F 9 | WvLenth = 15.451292cm | Freq = 11175.30341
    Midi = 126 | Note =   F# 9 | WvLenth = 14.584077cm | Freq = 11839.82153
    Midi = 127 | Note =    G 9 | WvLenth = 13.765536cm | Freq = 12543.85395
*/
