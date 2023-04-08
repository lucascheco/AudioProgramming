/***********************************************************************************
    Author:      Lucas Pacheco.
    Description: Chapter 6, Convolution.
    Date:        07/04/2023
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <snd_defs.h>

/** convolution program.
 * Convolves an input sound with an impulse response.
 * conv infile.* impulse.* outfile.wav gain
 */

int main(int argc, char **argv)
{
  SNDFILE *psfo, *psfi[2];
  float *buffer, gain;
  int chans, i, j = 0, cnt = 0, pt = 0, size;
  float sr, *imp, *del;

  if (argc == 5)
  {
    // allocate buffer, delay & table memory
    buffer = new float[def_vsize];
    gain = (float)atof(argv[4]);

    // now we open the files
    if (!(psfi[0] = soundin_open(argv[1], &chans, &sr)))
    {
      printf("error opening input file\n");
      exit(-1);
    }

    if (chans > 1 || sr != def_sr)
    {
      printf("unsupported channels or sr\n");
      exit(-1);
    }

    if (!(psfi[1] = soundin_open(argv[2], &chans, &sr)))
    {
      printf("error opening impulse file\n");
      exit(-1);
    }

    if (chans > 1 || sr != def_sr)
    {
      printf("unsupported channels or sr\n");
      exit(-1);
    }

    if (!(psfo = soundout_open(argv[3])))
    {
      printf("error opening output file.\n");
      exit(-1);
    }

    size = dataframes(psfi[1]);
    del = new float[size];
    imp = new float[size];
    memset(del, 0, size * sizeof(float));

    // copy impulse response to table
    do
    {
      cnt = soundin(psfi[1], buffer);
      for (i = 0; i < cnt; i++, j++)
        imp[j] = buffer[i];
    } while (cnt);

    printf("processing (this might take a while)...\n");

    // process
    j = 0;

    do
    {
      cnt = soundin(psfi[0], buffer);
      fir(buffer, imp, del, size, &pt);

      for (i = 0; i < def_vsize; i++)
        buffer[i] *= gain;

      soundout(psfo, buffer);
      memset(buffer, 0, def_vsize * sizeof(float));

      if (j % (def_vsize * 50) == 0)
        printf("%.3f secs...\n", (float)j / def_sr);

      j += def_vsize;
    } while (cnt);

    // tail (last N-1 samples)
    cnt = size - 1;
    do
    {
      fir(buffer, imp, del, size, &pt);
      for (i = 0; i < def_vsize; i++)
        buffer[i] *= gain;
      soundout(psfo, buffer);
      memset(buffer, 0, def_vsize * sizeof(float));
      cnt -= def_vsize;
    } while (cnt >= 0);

    // close file & free memory
    soundin_close(psfi[0]);
    soundin_close(psfi[1]);
    soundout_close(psfo);
    delete[] buffer;
    delete[] imp;
    delete[] del;

    printf("done.\n");
    return 0;
  }
  else
  {
    printf("usage: conv infile.* impulse.* outfile.wav gain\n");
    return 1;
  }
}

// fir
float fir(float *sig, float *imp, float *del, int length, int *p, int vecsize, float sr)
{
  float out = 0.f;
  int rp;

  for (int i = 0; i < vecsize; i++)
  {
    del[*p] = sig[i];
    *p = (*p != length - 1) ? *p + 1 : 0;

    for (int j = 0; j < length; j++)
    {
      rp = (*p + j);
      rp = (rp < length) ? rp : rp - length;
      out += (del[rp] * imp[length - 1 - j]);
    }

    sig[i] = out;
    out = 0.f;
  }

  return *sig;
}