typedef struct t_gtable
{
    double* table; /* Array containing the waveform */
    unsigned long length; /* Excluding guard point */
} GTABLE;

typedef struct t_tab_oscil
{
    OSCIL osc;
    const GTABLE* gtable;
    double dtablen;
    double sizeovrsr;
} OSCILT;

GTABLE* new_sine(unsigned long length);
void gtable_free(GTABLE** gtable);

OSCILT* new_oscilt(double srate, const GTABLE* gtable, double phase);

double tabtick (OSCILT* p_osc, double freq);
double tabitick(OSCILT* p_osc, double freq);

GTABLE* new_gtable(unsigned long length);
GTABLE* new_triangle(unsigned long length, unsigned long nharms);
GTABLE* new_square(unsigned long length, unsigned long nharms);
GTABLE* new_saw(unsigned long length, unsigned long nharms, int up);
