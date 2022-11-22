/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 5, Sine.
    Date:        18/11/2022
************************************************************************************/
#include <sndfile.h>
#include <math.h>
#include <time.h>

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

#define N 4410

int main() {
    SNDFILE *sfp;
    SF_INFO sfinfo;
    int i;
    int n;
    int channels = 2;
    short sig[N];
    float amp = 32767.f, freq = 440.f, sr = 44100.f;
    float phase = 0.75;
    double twopi = 2.0 * M_PI;
    
    float duration = 1;

    phase *= twopi;

    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.samplerate = sr;
    sfinfo.channels = channels;

    sfp = sf_open("sine.wav", SFM_WRITE, &sfinfo);
/*
    // for (i = 0; i < 44100/N; i++) {
    //     for (int k = 0; k < 2; k++) {
    //         for (n = 0; n < N; n++) 
    //             sig[n] = (short)(amp * cos( twopi * (n + i * N) * (freq/2)/sr +phase)) * 0.4;
    //         sf_write_short(sfp, sig, N);
    //     }
    // }

    // for (int j = 0; j < duration*10; j++) {
    //     for (int k = 0; k < channels; k++) {
    //         for (n = 0; n < N; n++) 
    //             sig[n] = (short)(amp * cos(twopi * n * (freq/channels)/sr +phase)) * 0.4;
    //         sf_writef_short(sfp, sig, N/2);
    //     }
    // }
*/
    for (int j = 0; j < duration*10; j++) {
        for (int k = 0; k < channels; k++) {
            for (n = 0; n < N; n++) {
                sig[n] = (short)(amp * cos(twopi * n * (freq/channels)/sr + phase));
            }
            sf_write_short(sfp, sig, N);
        }
    }
    
    sf_close(sfp);
}
