#ifndef M_PI
#define M_PI (3.1415926535897932)
#endif
#define TWOPI (2.0 * M_PI)
#define UPDATE_FREQ(p_osc, freq) (p_osc->curfreq) != (freq) ? (p_osc->curfreq = freq), (p_osc->incr = ((freq)*p_osc->twopiovrsr)) : 1 

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
double sqttick (OSCIL* p_osc, double freq);
double sawdtick(OSCIL* p_osc, double freq);
double sawutick(OSCIL* p_osc, double freq);
double tritick (OSCIL* p_osc, double freq);
double pmwtick (OSCIL* p_osc, double freq, double pwmod);

typedef double (*tickfunc)(OSCIL* p_osc, double freq);
typedef double (*tickfuncpwd)(OSCIL* p_osc, double freq, double pwmod);