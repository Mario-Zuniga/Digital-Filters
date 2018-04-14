#include "PIT.h"
#include "GPIO.h"
#include "DSP.h"
#include "DAC.h"
#include "ADC.h"

 BOOL PIT0_Flag = FALSE;
 BOOL PIT1_Flag = TRUE;
 BOOL PIT2_Flag = FALSE;

 extern newSample_Type newSample;
 extern float processedSample;

void PIT0_IRQHandler(){
	newSample.sample = getValue(ADC0,A) - 1.65;	//Almacena el valor obtenido del ADC restandole el offset que se agrego de forma analógica para permitir la convolución
	newSample.ready = TRUE;
	DAC_setOutput((uint16)processedSample);			//Cambia la salida de DAC al valor resultante de procesar la muestra anterior.
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;		//Limpia la bandera de interrupción
	PIT_TCTRL0; 						//read control register to clear PIT flag, this is silicon bug
	GPIO_setPIN(GPIOC, 4);
}
void PIT1_IRQHandler(){
	PIT_stopTimer(PIT_1);
	PIT1_Flag = TRUE;
	PIT_TFLG1 |= PIT_TFLG_TIF_MASK;		/**Clears the timer 1 flag*/
	PIT_TCTRL1; //read control register to clear PIT flag, this is silicon bug

}


void PIT_enable(){
	SIM_SCGC6 |= PIT_CLOCK_GATING;
}

void PIT_module_Control_Register(PIT_module_Control_RegisterType config){
	PIT_MCR=config;
}

void PIT_timerControlRegister(PIT_TimerType pitTimer,PIT_timerControlRegisterType configuration){
	PIT_TCTRL(pitTimer)=configuration;
}

void PIT_stopTimer(PIT_TimerType pitTimer){
	PIT_TCTRL(pitTimer)=FALSE;   /**Disable the timer count*/

}

void PIT_timerStartValue(PIT_TimerType pitTimer,uint32 value){
	PIT_LDVAL(pitTimer)= value;   /**Update the value timer n is counting*/

}

void PIT_timerStartSeconds(PIT_TimerType pitTimer,float systemClock, float seconds){
	PIT_LDVAL(pitTimer)= (uint32)(seconds*systemClock);   /**Update the value timer n is counting*/

}

void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period){
	SIM_SCGC6 |= PIT_CLOCK_GATING;
	PIT_MCR=0x0;
	PIT_LDVAL(pitTimer)= (uint32)(period*systemClock);   /**Update the value timer one is counting*/
	PIT_TCTRL(pitTimer)=0x3;	/**Activates the interrupt and timer for the selected pit timer*/

}
