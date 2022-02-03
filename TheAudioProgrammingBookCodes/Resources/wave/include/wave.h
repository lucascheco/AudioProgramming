#ifndef M_PI
#define M_PI (3.1415926535897932)
#endif
#define TWOPI (2.0 * M_PI)

typedef struct t_oscil {
	double twopiovrsr; /* to hold a constant value 2PI/sr */
	double curfreq;
	double curphase;
	double incr;
} OSCIL;

void oscil_init(OSCIL* osc, unsigned long srate);

OSCIL* oscil(void);

OSCIL* new_oscil(unsigned long srate);

double sinetick(OSCIL* p_osc, double freq);

