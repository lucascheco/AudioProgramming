#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <wave.h>

void oscil_init(OSCIL* osc, unsigned long srate) {
	osc->twopiovrsr = TWOPI / (double) srate;
	osc->curfreq  = 0.0;
	osc->curphase = 0.0;
	osc->incr     = 0.0;
}

OSCIL* oscil(void) {
	OSCIL* osc = (OSCIL*)malloc(sizeof(OSCIL));
	if (osc == NULL)
		return NULL;
	return osc;
}

OSCIL* new_oscil(unsigned long srate) {
	OSCIL* p_osc = (OSCIL*)malloc(sizeof(OSCIL));
	if (p_osc == NULL)
		return NULL;
	p_osc->twopiovrsr = TWOPI / (double) srate;
	p_osc->curfreq  = 0.0;
	p_osc->curphase = 0.0;
	p_osc->incr     = 0.0;

	return p_osc;

}

double sinetick(OSCIL* p_osc, double freq) {
	double val;
	
	val = sin(p_osc->curphase);
	
	UPDATE_FREQ(p_osc, freq);

	p_osc->curphase += p_osc->incr;
	if ( p_osc->curphase >= TWOPI ) {
		p_osc->curphase -= TWOPI;
	}
	if ( p_osc->curphase < 0.0 ) {
		p_osc->curphase += TWOPI;
	}

	return val;
}

double sqttick (OSCIL* p_osc, double freq) {
    double val;

	UPDATE_FREQ(p_osc, freq);
    
    if ( p_osc->curphase <= M_PI ) { 
        val = 1.0;
    } else {
        val = -1.0;
    }

    p_osc->curphase += p_osc->incr;

    if ( p_osc->curphase >= TWOPI ) 
        p_osc->curphase -= TWOPI;

    if ( p_osc->curphase < 0.0 )
        p_osc->curphase += TWOPI;

    return val;
}

double sawdtick(OSCIL* p_osc, double freq) {
	double val;

	UPDATE_FREQ(p_osc, freq);

	val = 1.0 - 2.0 * (p_osc->curphase / TWOPI);

	p_osc->curphase += p_osc->incr;

	if ( p_osc->curphase >= TWOPI )
		p_osc->curphase -= TWOPI;
	
	if ( p_osc->curphase < 0.0 )
		p_osc->curphase += TWOPI;
	
	return val;
}

double sawutick(OSCIL* p_osc, double freq) {
	double val;

	UPDATE_FREQ(p_osc, freq);

	val = (2.0 * (p_osc->curphase / TWOPI)) - 1.0;

	p_osc->curphase += p_osc->incr;

	if ( p_osc->curphase >= TWOPI )
		p_osc->curphase -= TWOPI;
	
	if ( p_osc->curphase < 0.0 )
		p_osc->curphase += TWOPI;
	
	return val;
}

double tritick (OSCIL* p_osc, double freq) {
	double val;

	UPDATE_FREQ(p_osc, freq);

	val = (2.0 * (p_osc->curphase / TWOPI)) - 1.0;
	if (val < 0.0)
		val = -val;
	
	val = 2.0 * (val - 0.5);

	p_osc->curphase += p_osc->incr;

	if ( p_osc->curphase >= TWOPI )
		p_osc->curphase -= TWOPI;
	
	if ( p_osc->curphase < 0.0 )
		p_osc->curphase += TWOPI;
	
	return val;
}

double pmwtick (OSCIL* p_osc, double freq, double pwmod) {
    double val;

	UPDATE_FREQ(p_osc, freq);
    
    if ( p_osc->curphase <= M_PI * pwmod / 50.0 ) { 
        val = 1.0;
    } else {
        val = -1.0;
    }

    p_osc->curphase += p_osc->incr;

    if ( p_osc->curphase >= TWOPI ) 
        p_osc->curphase -= TWOPI;

    if ( p_osc->curphase < 0.0 )
        p_osc->curphase += TWOPI;

    return val;
}