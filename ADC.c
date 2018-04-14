#include "ADC.h"

void clockGatingADC(ADC_Type* ADC_x){
	if(ADC0==ADC_x)/**Activates ADC0*/
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	if (ADC1==ADC_x)/**Activates ADC1*/
		SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
}

uint8 conversionComplete(ADC_Type* ADC_x, SCIn n){
	uint32 COCO = (ADC_SC1_REG(ADC_x,n) & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT;/**Reads COCO flag*/
	return (uint8)COCO;
}

void interruptEnable(ADC_Type* ADC_x, SCIn n,INTERRUPT_ENABLE ED){
	if (ENABLE==ED)/**Enables or disables COCO flag*/
		ADC_SC1_REG(ADC_x,n) |= ADC_SC1_AIEN_MASK;/**Enables*/
	else
		ADC_SC1_REG(ADC_x,n) &= ~ADC_SC1_AIEN_MASK;/**Disables*/
}

void diferentialEnable(ADC_Type* ADC_x, SCIn n, DIFF ED){
	if (ENABLE==ED)/**Enables or disables differential mode*/
		ADC_SC1_REG(ADC_x,n) |= ADC_SC1_DIFF_MASK;/**Enables*/
	else
		ADC_SC1_REG(ADC_x,n) &= ~ADC_SC1_DIFF_MASK;/**Disables*/
}

void channelSelect(ADC_Type* ADC_x, SCIn n, CHANNEL channel){
	ADC_SC1_REG(ADC_x,n) &= ~ADC_SC1_ADCH_MASK;/**Cleans the selected channel*/
	ADC_SC1_REG(ADC_x,n) |= ADC_SC1_ADCH(channel);/**Sets the new channel*/
}

void ADCx_SC1(ADC_Type* ADC_x, SCIn n, INTERRUPT_ENABLE ED0, DIFF ED1, CHANNEL channel){
	interruptEnable(ADC_x, n, ED0);
	diferentialEnable(ADC_x, n, ED1);
	channelSelect(ADC_x, n, channel);
}

void lowPower(ADC_Type* ADC_x, LOW_POWER ED){
	if (ENABLE==ED)/**Enables or disables los power mode*/
		ADC_CFG1_REG(ADC_x) |= ADC_CFG1_ADLPC_MASK;/**Enables*/
	else
		ADC_CFG1_REG(ADC_x) &= ~ADC_CFG1_ADLPC_MASK;/**Disables*/
}

void clockDivide(ADC_Type* ADC_x, CLOCK_DIVIDE clk){
	ADC_CFG1_REG(ADC_x) &= ~ADC_CFG1_ADIV_MASK;/**Cleans the selected clock divider*/
	ADC_CFG1_REG(ADC_x) |= ADC_CFG1_ADIV(clk);/**Sets the new clock divider*/
}

void sampleTime(ADC_Type* ADC_x, SAMPLE_TIME time){
	if (LONG==time)
		ADC_CFG1_REG(ADC_x) |= ADC_CFG1_ADLSMP_MASK;/**Sets sample time to long*/
	else
		ADC_CFG1_REG(ADC_x) &= ~ADC_CFG1_ADLSMP_MASK;/**Sets sample time to short*/
}

void conversionMode(ADC_Type* ADC_x, MODE mode){
	ADC_CFG1_REG(ADC_x) &= ~ADC_CFG1_MODE_MASK ;/**Cleans the selected mode*/
	ADC_CFG1_REG(ADC_x) |= ADC_CFG1_MODE(mode) ;/**Sets the new mode*/
}

void inputClock(ADC_Type* ADC_x, CLOCK clk){
	ADC_CFG1_REG(ADC_x) &= ~ADC_CFG1_ADICLK_MASK  ;/**Cleans the selected clock source*/
	ADC_CFG1_REG(ADC_x) |= ADC_CFG1_ADICLK(clk);/**Sets the new clock source*/
}

void ADCx_CFG1(ADC_Type* ADC_x, LOW_POWER ED, CLOCK_DIVIDE clk0, SAMPLE_TIME time, MODE mode, CLOCK clk1){
	lowPower(ADC_x, ED);
	clockDivide(ADC_x, clk0);
	sampleTime(ADC_x, time);
	conversionMode(ADC_x, mode);
	inputClock(ADC_x, clk1);
}

uint16 getValue(ADC_Type* ADC_x, SCIn n){
	while (FALSE==conversionComplete(ADC_x,n));/**Waits for COCO to turn on*/
	uint32 result = ADC_R_REG(ADC_x,n);/**Reads the value of the conversion*/
	return (uint16)result;
}

uint8 conversionActive(ADC_Type* ADC_x){
	uint32 ADACT = (ADC_SC2_REG(ADC_x) & ADC_SC2_ADACT_MASK)>>ADC_SC2_ADACT_SHIFT;/**Reads ADACT*/
	return (uint8)ADACT;
}

void conversionTrigger(ADC_Type* ADC_x,TRIGGER SH){
	if (HARDWARE==SH)
		ADC_SC2_REG(ADC_x)|=ADC_SC2_ADTRG_MASK;/**Sets the trigger to software trigger*/
	else
		ADC_SC2_REG(ADC_x) &=~ADC_SC2_ADTRG_MASK;/**Sets the trigger to hardware trigger*/
}

void compareFunction(ADC_Type* ADC_x, COMPARE_FUNCTION ED){
	if (ENABLE==ED)/**Enables or disables compare mode*/
		ADC_SC2_REG(ADC_x)|=ADC_SC2_ACFE_MASK;/**Enables*/
	else
		ADC_SC2_REG(ADC_x) &=~ADC_SC2_ACFE_MASK;/**Disables*/
}

void voltageReference(ADC_Type* ADC_x, VOLTAGE_REFERENCE reference){
	ADC_SC2_REG(ADC_x) &= ~ADC_SC2_REFSEL_MASK;/**Cleans the selected voltage reference*/
	ADC_SC2_REG(ADC_x)=ADC_SC2_REFSEL(reference);/**Sets the new voltage source*/
}

void ADCx_SC2(ADC_Type* ADC_x, TRIGGER SH, COMPARE_FUNCTION ED, VOLTAGE_REFERENCE reference){
	conversionTrigger(ADC_x, SH);
	compareFunction(ADC_x, ED);
	voltageReference(ADC_x, reference);
}

void continuesConversion(ADC_Type* ADC_x, CONTINUOUS_CONVERSION ED){
	if (ENABLE==ED)/**Enables or disables continues conversion mode*/
		ADC_SC3_REG(ADC_x)|= ADC_SC3_ADCO_MASK;/**Enables*/
	else
		ADC_SC3_REG(ADC_x) &=~ ADC_SC3_ADCO_MASK;/**Disables*/
}

void averageEnable(ADC_Type* ADC_x, AVERAGE_ENABLE ED){
	if (ENABLE==ED)/**Enables or disables average mode*/
		ADC_SC3_REG(ADC_x)|= ADC_SC3_AVGE_MASK  ;/**Enables*/
	else
		ADC_SC3_REG(ADC_x) &=~ ADC_SC3_AVGE_MASK  ;/**Disables*/
}

void averageSelect(ADC_Type* ADC_x, AVERAGE average){
	ADC_SC3_REG(ADC_x)&=~ADC_SC3_AVGE_MASK;/**Cleans the selected number of samples*/
	ADC_SC3_REG(ADC_x)=ADC_SC3_AVGE(average);/**Sets the new number of samples*/
}

void ADCx_SC3(ADC_Type* ADC_x, CONTINUOUS_CONVERSION ED0, AVERAGE_ENABLE ED1, AVERAGE average){
	continuesConversion(ADC_x, ED0);
	averageEnable(ADC_x, ED1);
	averageSelect(ADC_x, average);
}
