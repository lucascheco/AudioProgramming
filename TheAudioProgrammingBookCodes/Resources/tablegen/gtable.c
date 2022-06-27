#include <wave.h>
#include <gtable.h>

static void norm_gtable(GTABLE* gtable);

/* creation function for sinewave */
GTABLE* new_sine(unsigned long length)
{
    unsigned long i;
    double step;
    GTABLE* gtable = NULL;

    if (length == 0)
        return NULL;
    
    gtable = (GTABLE*) malloc(sizeof(GTABLE));

    if (gtable == NULL)
        return NULL;
    
    gtable->table = (double*) malloc((length + 1) * sizeof(double)); // + 1, for guard point

    if (gtable->table == NULL) 
    {
        free(gtable);
        return NULL;
    }

    gtable->length = length;
    step = TWOPI / length;  /* sine wave */
    
    for (int i = 0; i < length; ++i)
        gtable->table[i] = sin(step * i);
    
    gtable->table[i] = gtable->table[0]; // guard point
    
    return gtable;
}

/* Destruction function */
void gtable_free(GTABLE** gtable)
{
    if (gtable && *gtable && (*gtable)->table)
    {
        free((*gtable)->table);
        free(*gtable);
        *gtable = NULL;
    }
}

/* Creation function for OSCILT */
OSCILT* new_oscilt(double srate, const GTABLE* gtable, double phase)
{
    OSCILT* p_osc;

    if ((gtable == NULL) || (gtable->table == NULL) || gtable->length == 0)
        return NULL;

    p_osc = (OSCILT*) malloc(sizeof(OSCILT));

    if (p_osc == NULL)
        return NULL;

    /* init the oscillator */
    p_osc->osc.curfreq = 0.0;
    p_osc->osc.curphase = gtable->length * phase;
    p_osc->osc.incr = 0.0;

    /* then GTABLE */
    p_osc->gtable = gtable;
    p_osc->dtablen = (double) gtable->length;
    p_osc->sizeovrsr = p_osc->dtablen / (double) srate;

    return p_osc;
}

/* tick truncated */
double tabtick(OSCILT* p_osc, double freq)
{
    int index = (int) (p_osc->osc.curphase);
    double val;
    double dtablen = p_osc->dtablen;
    double curphase = p_osc->osc.curphase;
    double* table = p_osc->gtable->table;

    if (p_osc->osc.curfreq != freq)
    {
        p_osc->osc.freq = freq;
        p_osc->osc.incr = p_osc->sizeovrsr * p_osc->osc.curfreq;
    }

    curphase += p_osc->osc.incr;

    while (curphase >= dtablen)
        curphase -= dtablen;
    
    while (curphase < 0.0)
        curphase += dtablen;

    p_osc->osc.curphase = curphase;
    
    return table[index];
}

/* tick interpolated */
double tabitick(OSCILT* p_osc, double freq)
{
    int base_index = (int) p_osc->osc.curphase;
    unsigned long next_index = base_index + 1;
    double frac, slope, val;
    double dtablen = p_osc->dtablen;
    double curphase = p_osc->osc.curphase;
    double* table = p_osc->gtable->table;

    if (p_osc->osc.curfreq != freq) 
    {
        p_osc->osc.curfreq = freq;
        p_osc->osc.incr = p_osc->sizeovrsr * p_osc->osc.curfreq;
    }

    frac = curphase - base_index;
    val = table[base_index];
    slope = table[next_index] - val;
    val += (frac * slope);

    curphase += p_osc->osc.incr;
    while (curphase >= dtablen)
        curphase -= dtablen;
    
    while (curphase < 0.0)
        curphase += dtablen;
    
    p_osc->osc.curphase = curphase;

    return val;
}

/* Triangle wave */
GTABLE* new_triangle_(unsigned long length, unsigned long nharms) 
{
    unsigned long i, j;
    double step, amp, maxamp;
    double* table;
    unsigned long harmonic = 1;
    GTABLE* gtable = NULL;

    if (length == 0 || nharms == 0 || nharms >= (length / 2))
        return NULL;

    gtable = (GTABLE*) malloc(sizeof(GTABLE));
    if (gtable == NULL)
        return NULL;
    
    table = (double*) malloc((length + 1) * sizeof(double));
    if (table == NULL)
    {
        free(gtable);
        return NULL;
    }

    for (i = 0; i < length; ++i)
        table[i] = 0.0;

    step = TWOPI / length;

    /* generate triangle wave */
    for (i = 0; i < nharms; ++i)
    {
        amp = 1.0 / (harmonic * harmonic);
        for (j = 0; j < length; ++j)
            table[j] += amp * cos(step * harmonic * j);

        harmonic += 2;
    }

    /* normalize table */
    for (i = 0; i < length; ++i)
    {
        amp = fabs(table[i]);
        if (maxamp < amp)
            maxamp = amp;
    }

    maxamp = 1.0 / maxamp;

    for (i =0; i <length; ++i)
        table[i] *= maxamp;

    table[i] = table[0]; /* guarpoint */
    gtable->length = length;
    gtable->table = table;

    return gtable;
}

GTABLE* new_gtable(unsigned long length)
{   
    unsigned long i;
    GTABLE* gtable = NULL;

    if (length == 0)
        return NULL;
    
    gtable = (GTABLE*) malloc(sizeof(GTABLE));
    if (gtable == NULL)
        return NULL;

    gtable->table = (double*) malloc((length + 1) * sizeof(double));
    if (gtable->table == NULL)
    {
        free(gtable);
        return NULL;
    }

    gtable->length = length;
    for (i = 0; i <= length; ++i)
        gtable->table[i] = 0.0;

    return gtable;
}

GTABLE* new_triangle(unsigned long length, unsigned long nharms)
{
    unsigned long i, j;
    double step, amp;
    int harmonic = 1;
    GTABLE* gtable = NULL;

    if (length == 0 || nharms == 0 || nharms >= (length / 2))
        return NULL;

    gtable = new_gtable(length);
    if (gtable == NULL)
        return NULL;
    
    step = TWOPI / length;
    for (i = 0; i < nharms; ++i)
    {
        amp = 1.0 / (harmonic * harmonic);
        for (j = 0; j < length; ++j)
            gtable->table[j] += amp * cos(step * harmonic * j);

        harmonic += 2;
    }

    norm_gtable(gtable);

    return gtable;
}


GTABLE* new_square(unsigned long length, unsigned long nharms)
{
    unsigned long i, j;
    double step, amp;
    int harmonic = 1;
    GTABLE* gtable = NULL;

    if (length == 0 || nharms == 0 || nharms >= (length / 2))
        return NULL;

    gtable = new_gtable(length);
    if (gtable == NULL)
        return NULL;
    
    step = TWOPI / length;
    for (i = 0; i < nharms; ++i)
    {
        amp = 1.0 / harmonic;
        for (j = 0; j < length; ++j)
            gtable->table[j] += amp * sin(step * harmonic * j);

        harmonic += 2;
    }

    norm_gtable(gtable);

    return gtable;
}

GTABLE* new_saw(unsigned long length, unsigned long nharms, int up)
{
    unsigned long i, j;
    double step, val, amp = 1.0;
    int harmonic = 1;
    GTABLE* gtable = NULL;

    if (length == 0 || nharms == 0 || nharms >= (length / 2))
        return NULL;

    gtable = new_gtable(length);
    if (gtable == NULL)
        return NULL;
    
    step = TWOPI / length;
    if (up)
        amp = -1;
        
    for (i = 0; i < nharms; ++i)
    {
        val = amp / harmonic;
        for (j = 0; j < length; ++j)
            gtable->table[j] += val * sin(step * harmonic * j);

        harmonic++;
    }

    norm_gtable(gtable);

    return gtable;
}

static void norm_gtable(GTABLE* gtable)
{
    unsigned long i;
    double val, maxamp = 0.0;

    for (i = 0; i < gtable->length; ++i)
    {
        val = fabs(gtable->table[i]);
        if (maxamp < val)
            maxamp = val;
    }

    maxamp = 1.0 / maxamp;
    for (i = 0; i < gtable->length; ++i)
        gtable->table[i] *= maxamp;

    gtable->table[i] = gtable->table[0];
}