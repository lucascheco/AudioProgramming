/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 6, Subtractive Synth.
    Date:        07/04/2023
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <snd_defs.h>

/** subtractive synthesis program with envelopes.
 *    Generates a filtered sawtooth sound sound with amplitude
 *    and filter cf envelopes. This program also shows the use
 *    of interpolating oscillators.
 *
 *    envelope sndfile.wav amp freq(Hz) dur(secs)
 */

int main(int argc, char **argv)
{
  SNDFILE *psf;
  float *buffer;
  int smps, bytes = sizeof(float) * def_vsize, cnt1 = 0, cnt2 = 0;
  float dur, amp, freq, *wave, *comp, ndx = 0;

  if (argc == 5)
  {
    amp = (float)atof(argv[2]);
    freq = (float)atof(argv[3]);
    dur = (float)atof(argv[4]);
    smps = (int)(dur * def_cr);

    // allocate buffer, delay & table memory
    buffer = new float[def_vsize];
    comp = new float[def_vsize];
    float del[2] = {0.f, 0.f}, del1[2] = {0.f, 0.f};
    wave = saw_table(30);

    // now open the file
    if (!(psf = soundout_open(argv[1])))
    {
      printf("error opening output file\n");
      exit(-1);
    }

    for (int i = 0; i < smps; i++)
    {
      oscc(buffer, adsr(amp, dur, 0.05f, 0.1f, amp * 0.7f, 0.2f, &cnt1), freq, wave, &ndx);
      memcpy(comp, buffer, bytes);
      resonator(buffer, expon(freq * 8, dur, freq * 4, &cnt2), 50, del);
      balance(buffer, comp, del1);
      soundout(psf, buffer);
    }

    // close file & free memory
    soundout_close(psf);
    delete[] buffer;
    delete[] comp;
    delete[] wave;

    return 0;
  }
  else
  {
    printf("usage: filter sndfile.wav amp freq(Hz) dur(s)\n");
    return 1;
  }
}

// resonator
float resonator(float *sig, float freq, float bw, float *del, int vecsize, float sr)
{
  double r, rsq, rr, costh, scal;
  rr = 2 * (r = 1. - pi * (bw / sr));
  rsq = r * r;
  costh = (rr / (1. + rsq)) * cos(2 * pi * freq / sr);
  scal = (1 - rsq) * sin(acos(costh));

  for (int i = 0; i < vecsize; i++)
  {
    sig[i] = (float)(sig[i] * scal + rr * costh * del[0] - rsq * del[1]);
    del[1] = del[0];
    del[0] = sig[i];
  }

  return *sig;
}

// balance
float balance(float *sig, float *cmp, float *del, float freq, int vecsize, float sr)
{
  double costh, coef;
  costh = 2. - cos(2 * pi * freq / sr);
  coef = sqrt(costh * costh - 1.) - costh;

  for (int i = 0; i < vecsize; i++)
  {
    del[0] = (float)((sig[i] < 0 ? -sig[i] : sig[i]) * (1 + coef) - del[0] * coef);
    del[1] = (float)((cmp[i] < 0 ? -cmp[i] : cmp[i]) * (1 + coef) - del[1] * coef);
    sig[i] *= (float)(del[0] ? del[1] / del[0] : del[1]);
  }

  return *sig;
}