#include "DSP.h"
#include "GPIO.h"


newSample_Type newSample = {0,0};		
float processedSample = 0;				
float volumeH = .5;
float volumeL = .5;
float h1[7] = {0.07840464525404556, 0.17707825519483075, 0.22014353249171387, 0.2759015644497544, 0.22014353249171387, 0.17707825519483075, 0.07840464525404556};
float h2[7] ={ -0.08857280384687653,0.20001387909943527,-0.13289448474069163,0.7755518089951376,-0.13289448474069163,-0.20001387909943527,-0.08857280384687653 };
float buffer[7] = {0,0,0,0,0,0,0};
float *bufferPtr = buffer;


void DSP_process(){
	if(newSample.ready){	
		DSP_buffAdd(newSample.sample);

		// Low-Pass Filter
		float processedSampleTemp = 0;
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(0)*h1[0]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(1)*h1[1]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(2)*h1[2]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(3)*h1[3]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(4)*h1[4]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(5)*h1[5]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(6)*h1[6]);
		processedSample = volumeL*processedSampleTemp;				

		// High-Pass Filter
		processedSampleTemp = 0;
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(0)*h2[0]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(1)*h2[1]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(2)*h2[2]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(3)*h2[3]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(4)*h2[4]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(5)*h2[5]);
		processedSampleTemp=processedSampleTemp+(DSP_buffExtract(6)*h2[6]);
		//processedSample =(uint16)(volumeH*processedSampleTemp);
		processedSample = ((processedSample +(volumeH*processedSampleTemp))/2) + 1.65;				


		newSample.ready = FALSE;			
		GPIO_clearPIN(GPIOC, 4);
	}
}

BOOL DSP_buffAdd(float data){
	if((int)bufferPtr<((int)buffer)+24){
		bufferPtr++;
	}else{
		bufferPtr = buffer;
	}
	*bufferPtr = data;
}
float DSP_buffExtract(int index){
	if(bufferPtr-index>=buffer){
		return *(bufferPtr-index);
	}else{
		return *(bufferPtr-index+7);
	}
}


