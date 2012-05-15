/*
 *  Oscillator.h - audio oscillator, modified April 2009
 *  music
 *  
 *  Created by Marek Bereza on Sat Mar 01 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h>
//#ifndef PI
#define PI 3.1415927f
//#endif
#ifndef TWOPI
#define TWOPI 6.2831853f
#endif
#ifndef __OSCILLATOR__
#define __OSCILLATOR__


/*
#define OFF     0
#define SAW     1
#define SQUARE  2
#define TRI		3
*/

#define	kOSC_TYPE_SAW 0
#define	kOSC_TYPE_SQUARE 1
#define	kOSC_TYPE_TRIANGLE 2
#define kOSC_TYPE_SIN 3
#define kOSC_TYPE_REVERSE_SAW 4

class Oscillator {
public:
	Oscillator() {
		oscType = kOSC_TYPE_SAW;
		TWOPI_BY_SAMPLERATE = TWOPI/44100.f;
		
		// give the frequency a sensible
		// default value
		frequency = 200;
	}
	
	float frequency;
	float TWOPI_BY_SAMPLERATE;
	float getSample() {
		
		// if frequency is set to 0 or less, then
		// don't do anything and reset the counter and phase
		
		// wrap and increment phase
		phase += frequency*TWOPI_BY_SAMPLERATE;
		if(phase>=TWOPI) phase -= TWOPI;
		
		// choose an oscillator type
		switch(oscType) {
			case kOSC_TYPE_TRIANGLE: {
				if(phase<PI) return (-1.f + (2.f*phase/PI))*2.f;
				else return 2.f*(1.f - (2.f*(phase-PI)/PI));
			}
			
			case kOSC_TYPE_SAW: return ((phase/PI)-1.f)*0.5f;
			case kOSC_TYPE_REVERSE_SAW: return (1.f - (phase/PI))*0.5f;
			case kOSC_TYPE_SIN: return sin(phase);
			case kOSC_TYPE_SQUARE: {
				if(phase<PI) return 0.4f;
				else return -0.4f;
			}
			default: return 0;
		}
	}
	
	void setOscType(int oType, float _sampleRate) {
		TWOPI_BY_SAMPLERATE = TWOPI/_sampleRate;
		oscType = oType;
		sampleRate = _sampleRate;
	}
	
private:
	
	int oscType;
	bool noteOn;
	
	float phase; // current phase of oscillator
	float sampleRate;
};
#endif

