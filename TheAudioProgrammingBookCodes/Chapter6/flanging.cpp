/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 6, Flanging.
    Date:        07/04/2023
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <snd_defs.h>

/** flanging program with envelopes.
 *  Flanges an input sound with a delay time envelope.
 *
 * delay infile.* outfile.* maxdelay(s) env_dur(s)
 */

int main(int argc, char **argv)
{
  SNDFILE *psfo, *psfi;
  float *buffer;
  int chans, bytes = sizeof(float) * def_vsize, cnt = 0, pt = 0, ts = 0;
  float sr, dur, dtime, *comp, *del, del1[2] = {0.f, 0.f};

  if (argc == 5)
  {
    dtime = (float)atof(argv[3]);
    dur = (float)atof(argv[4]);

    // allocate buffer and delay memory
    buffer = new float[def_vsize];
    comp = new float[def_vsize];
    del = new float[(int)(dtime * def_sr)];

    // now we open the files
    if (!(psfi = soundin_open(argv[1], &chans, &sr)))
    {
      printf("error opening input file\n");
      exit(-1);
    }

    if (chans > 1 || sr != def_sr)
    {
      printf("unsupported channels or sr\n");
      exit(-1);
    }

    if (!(psfo = soundout_open(argv[2])))
    {
      printf("error opening output file.\n");
      exit(-1);
    }

    do
    {
      cnt = soundin(psfi, buffer);
      memcpy(comp, buffer, bytes);
      flanger(buffer, line(.0001f, dur, dtime, &ts), 0.8f, dtime, del, &pt);
      balance(buffer, comp, del1);
      soundout(psfo, buffer, cnt);
    } while (cnt);

    // close file & free memory
    soundin_close(psfi);
    soundout_close(psfo);
    delete[] buffer;
    delete[] comp;
    delete[] del;

    return 0;
  }
  else
  {
    printf("usage: flanger infile.* outfile.wav maxdelay(s) env_dur(s)\n");
    return 1;
  }
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

// flanger
float flanger(float *sig, float vdtime, float fdb, float maxdel, float *delay, int *p, int vecsize, float sr)
{
  int mdt, rpi;
  float out, rp, vdt, frac, next;
  vdt = vdtime * sr;
  mdt = (int)(maxdel * sr);

  if (vdt > mdt)
    vdt = (float)mdt;

  for (int i = 0; i < vecsize; i++)
  {
    rp = *p - vdt;
    rp = (rp >= 0 ? (rp < mdt ? rp : rp - mdt) : rp + mdt);
    rpi = (int)rp;
    frac = rp - rpi;
    next = (rpi != mdt - 1 ? delay[rpi + 1] : delay[0]);
    out = delay[rpi] + frac * (next - delay[rpi]);
    delay[*p] = sig[i] + out * fdb;
    sig[i] = out;
    *p = (*p != mdt - 1 ? *p + 1 : 0);
  }

  return *sig;
}