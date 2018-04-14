#ifndef SOURCES_DSP_H_
#define SOURCES_DSP_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"

typedef struct{
	uint16 sample;
	BOOL ready;
}newSample_Type;

void DSP_process();
BOOL DSP_buffAdd(float data);
float DSP_buffExtract(int index);

#endif /* SOURCES_DSP_H_ */
