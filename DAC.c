#include "DAC.h"

void DAC_enable(){
	SIM_SCGC2 = 0x1000;
	DAC0_C0 = 0xc0;
}

void DAC_setOutput(uint16 value){
	DAC0_DAT0L = value;
	DAC0_DAT0H = value>>8;
}
