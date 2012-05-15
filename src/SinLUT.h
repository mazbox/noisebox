
/** 
 * Lookup table for sin/cos
 */
#pragma once

#define DEFAULT_SIN_LUT_SIZE 4096
#ifndef TWO_PI
#define TWO_PI 6.283185307179586f
#endif
#ifndef PI_BY_TWO
#define PI_BY_TWO 1.570796326794897f
#endif
class SinLUT {
public:

	
	SinLUT() {
		SIN_LUT_SIZE = 0;
		sinLUT = NULL;
	}
	
	~SinLUT() {
		if(sinLUT!=NULL) {
			delete [] sinLUT;
		}
	}
	
	void initSinLUT(int size) {
		
		SIN_LUT_SIZE = size;
		
		if(sinLUT!=NULL) {
			delete [] sinLUT;
		}
		
		sinLUT = new float[SIN_LUT_SIZE];
		
		for(int i = 0; i < SIN_LUT_SIZE; i++) {
			float phase = (float)i/(float)SIN_LUT_SIZE; 
			phase *= PI*2.f;
			sinLUT[i] = sin(phase);
		}
		multiplier = (float)SIN_LUT_SIZE/(float)TWO_PI;
	}
	
	float fastSin(float phase) {
		//return sin(phase);
		if(SIN_LUT_SIZE==0) {
			initSinLUT(DEFAULT_SIN_LUT_SIZE);
		}
		//return sin(phase);
		phase *= multiplier;
		while(phase>=SIN_LUT_SIZE) phase -= SIN_LUT_SIZE;
		if (phase<0) phase = 0;
		return sinLUT[(int)phase];
	}
	
	float fastCos(float phase) {
		return fastSin(phase + PI_BY_TWO);
	}
private:
	float multiplier;
	float *sinLUT;
	int SIN_LUT_SIZE;
};
