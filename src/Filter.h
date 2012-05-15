/*
 */

#pragma once
#include <math.h>
#include "SinLUT.h"
class Filter {
public:

	Filter() {
		x = 0;
		y = 0;
		cutoff = 0;
		z = 2;
		c = 0;
		output = 0;
		sqrt2 = sqrt(2);
	
	}
	
// filter from here: https://github.com/micknoise/Maximilian/blob/master/maximilian.cpp
// awesome. cuttof is freq in hz. res is between 1 and whatever. Watch out!

	float lores(float input,float cutoff, float resonance) {

		//cutoff=cutoff1*0.5;
		//if (cutoff<10) cutoff=10;
		//if (cutoff>(SAMPLERATE*0.5)) cutoff = (SAMPLERATE*0.5);
		//if (resonance<1.) resonance = 1.;
		
		z=sinLut.fastCos(TWOPI*cutoff/SAMPLERATE);
		c=2-2*z;
		float z1 = z-1;
		if(z1==0) z1 = 0.0001;
		float r= (sqrt2*sqrt(-z1*z1*z1)+resonance*z1)/(resonance*z1);
		x=x+(input-y)*c;
		y=y+x;
		x=x*r;
		output=y;
		return(output);
		//return input;
	}
	
	float x;
	float y;
	float cutoff;
	float z;
	float c;
	float output;
	float sqrt2;
	SinLUT sinLut;
};