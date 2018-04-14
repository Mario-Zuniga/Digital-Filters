#include "GlobalFunctions.h"

void delay(uint16 delay) {
	volatile int counter, counter2;
	
	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--); 

	}
}

float cToF(float c){
	float f= c*9/5 + 32;
	return f;
}

float fToC(float f){
	float c = (f-32)*5/9;
	return c;
}
