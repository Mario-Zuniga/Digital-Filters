/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"
#include "ADC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#include "DAC.h"
#include "DSP.h"
#include "DataTypeDefinitions.h"
static int i = 0;

extern uint8 frecuencia;

int main(void)
{
	//GPIO botones
	GPIO_clockGating(GPIOC);
	GPIO_pinControlRegisterType pinControlRegisterPullDown = GPIO_MUX1 + GPIO_PE + GPIO_INTERRUPT_FALLING;		/**Configures as gpio for push buttons*/
	GPIO_pinControlRegister(GPIOC,BIT0,&pinControlRegisterPullDown);
	GPIO_pinControlRegister(GPIOC,BIT1,&pinControlRegisterPullDown);
	GPIO_pinControlRegister(GPIOC,BIT2,&pinControlRegisterPullDown);
	GPIO_pinControlRegister(GPIOC,BIT3,&pinControlRegisterPullDown);
	GPIO_pinControlRegister(GPIOC,BIT5,&pinControlRegisterPullDown);
	GPIO_pinControlRegister(GPIOC,BIT7,&pinControlRegisterPullDown);
	NVIC_EnableIRQ(PORTC_IRQ);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_8);

	GPIO_pinControlRegisterType pinControlRegisterOut = GPIO_MUX1;
	GPIO_pinControlRegister(GPIOC,BIT4,&pinControlRegisterOut);
	GPIO_dataDirectionPIN(GPIOC,GPIO_OUTPUT,BIT4);



	// ADC configured for 12 bits and 32 samples
	clockGatingADC(ADC0);
	averageEnable(ADC0, ENABLE);
	averageSelect(ADC0, SAMPLES_32);
	conversionMode(ADC0, MODE_12_13);
	continuesConversion(ADC0, ENABLE);
	channelSelect(ADC0, A, CHANNEL0);

	
	// Activates 2 PITS, one of sampling frequency and other for the debouncer of the push buttons
	NVIC_EnableIRQ(PIT_CH0_IRQ);
	NVIC_EnableIRQ(PIT_CH1_IRQ);
	PIT_delay(PIT_0,SYSTEMCLOCK,.001/frecuencia);

	// Activation of DAC
	DAC_enable();


	EnableInterrupts;

    for (;;) {
    	DSP_process();		// Main function for the signal
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
