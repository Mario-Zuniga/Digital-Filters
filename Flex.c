#include "Flex.h"

uint16 FTM2_flag = 0;
void FTM2_IRQHandler(){
	static uint16 lastCV = 0;		/**A static variable used to store the las value */
	FTM_CnSC_REG(FTM_2,FTM_CH0) &= ~FTM_CnSC_CHF_MASK;		/**Cleares the overflow interrupt flag on FTM2_Ch0*/
	FTM2_flag = FTM_CnV_REG(FTM_2,FTM_CH0)-lastCV;			/**Stores in the flag the counts per period of the conected signal*/
	lastCV = FTM_CnV_REG(FTM_2,FTM_CH0);
}

void FTM_clearFlag(FTM_Type* flex){
	FTM_SC_REG(flex) &= ~FTM_TOF;		/**Cleares the flag of the FTM selected*/
}

void FTM_interruptEnable(FTM_Type * flex, FTM_INTERRUPT_TYPE ENABLE){
	if(FTM_INTERRUPT_ENABLE == ENABLE){
		FTM_SC_REG(flex) |= FTM_SC_TOIE_MASK;		/**Activates the interruption bit */
	}else{
		FTM_SC_REG(flex) &= ~((uint32)FTM_SC_TOIE_MASK);		/**Deactivates the interruption bit*/
	}
}
void FTM_PWMMode(FTM_Type * flex, FTM_PWM_TYPE pwm){
	if(PWM_UP_DOWN == pwm){
		FTM_SC_REG(flex) |= FTM_SC_CPWMS_MASK;		/**Activates up-down counting mode */
	}else{
		FTM_SC_REG(flex) &= ~((uint32)FTM_SC_CPWMS_MASK);		/**Activates up counting mode*/
	}
}
//This field is write protected. It can be written only when MODE[WPDIS] = 1.
void FTM_setClockSource(FTM_Type * flex, FTM_CLOCK_TYPE clock){
	FTM_SC_REG(flex) &= ~((uint32)FTM_SC_CLKS_MASK);		/**Clears both bits from CLKS*/
	FTM_SC_REG(flex) |= clock<<BIT3;						/**Asigns the value contained in 'clock' to the CLKS bits in SC register*/
}
void FTM_prescaleFactor(FTM_Type * flex, FTM_PRESCALER_TYPE pre){
	FTM_SC_REG(flex) &= ~((uint32)FTM_SC_PS_MASK);		/**Clears the bits from PS*/
	FTM_SC_REG(flex) |= pre;						/**Asigns the value contained in 'pre' to the PS bits in SC register*/
}

uint16 FTM_getCounterValue(FTM_Type * flex){
	return FTM_CNT_REG(flex); 		/**Returns the value contained in the flex timer counter selected*/
}
void FTM_setModValue(FTM_Type * flex, uint16 value){
	FTM_CNT_REG(flex) = 1;				/**Write a random value to CNT to restart the count and avoid an unwanted interruption*/
	FTM_MOD_REG(flex) = value;			/**Writes the overflow value to the MOD register*/
	delay(60000);

}
void FTM_setCountValue(FTM_Type * flex, uint8 channel, uint16 value){
	FTM_setClockSource(flex, FTM_NO_CLOCK);			/**Deactivated the clock source in order to apply the changes instantly*/
	FTM_CnV_REG(flex,channel) = value;				/**Stores the value in the CV register of the channel*/
	FTM_setClockSource(flex, FTM_SYSTEM_CLOCK);		/**Activates the clock source again*/
}
uint16 FTM_getCountValue(FTM_Type * flex, uint8 channel){
	return FTM_CnV_REG(flex,channel);		
}

void FTM_clearChannelFlag(FTM_Type * flex, uint8 channel){
	FTM_CnSC_REG(flex,channel) &= ~FTM_CnSC_CHF_MASK;			/**Writes a 0 to the flag in order to clear the flag*/
}
void FTM_channelInterruptEnable(FTM_Type * flex, uint8 channel, FTM_INTERRUPT_TYPE interrupt){
	if(FTM_INTERRUPT_ENABLE == interrupt){
		FTM_CnSC_REG(flex,channel) |= FTM_CnSC_CHIE_MASK;		/**Enables the interrupt*/
	}else{
		FTM_CnSC_REG(flex,channel) &= ~FTM_CnSC_CHIE_MASK;		/**Disables the interrupt*/
	}
}
void FTM_channelMode(FTM_Type * flex, uint8 channel, uint8 mode){
	FTM_CnSC_REG(flex,channel) &= ~FTM_MSB_MSA_ELSB_ELSA;		/**Clears MSB, MSA, ELSB and ELSA bits*/
	FTM_CnSC_REG(flex,channel) |= mode;							/**Writes the mode in the MSB, MSA, ELSB and ELSA bits*/
}

void FTM_initPWM(FTM_Type * flex, uint8 channel, uint16 MOD, uint16 CV){

	SIM_SCGC6 |= FTM_0_CLOCK_GATING;
	FTM_MODE_REG(flex) |= FTM_MODE_WPDIS_MASK;		/**Deactivate write protection*/
	FTM_setModValue(flex, MOD);				/**Writes the value that determines the period*/
	FTM_channelMode(flex, channel, FTM_EDGE_PWM_HIGH_TRUE);		/**Selects PWM mode */
	FTM_setCountValue(flex,channel,CV);		/**Writes the value that determines the duty cycle*/
	FTM_setClockSource(flex, FTM_SYSTEM_CLOCK);
	FTM_prescaleFactor(flex,FTM_BY_1);

}
void FTM_InitInputCompare(FTM_Type * flex, uint8 channel, uint16 MOD){
	SIM_SCGC6 |= FTM_2_CLOCK_GATING;
	FTM_MODE_REG(flex) |= FTM_MODE_WPDIS_MASK;		/**Deactivate write protection*/
	FTM_setModValue(flex, MOD);				/**Writes the value that determines the period*/
	FTM_channelMode(flex, channel, FTM_INPUT_CAPTURE_RISING);		/**Selects input capture mode */
	FTM_setClockSource(flex, FTM_SYSTEM_CLOCK);
	FTM_prescaleFactor(flex,FTM_BY_1);
	//FTM_interruptEnable(flex, FTM_INTERRUPT_ENABLE);
	FTM_channelInterruptEnable(flex, channel, FTM_INTERRUPT_ENABLE);
	NVIC_enableInterruptAndPriotity(FTM2_IRQ, PRIORITY_1);
}

