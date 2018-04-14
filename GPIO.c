/**
	\file 
	\brief 
		This is the source file for the GPIO device driver for Kinetis K64. 
		It contains all the implementation for configuration functions and runtime functions. 
		i.e., this is the application programming interface (API) for the GPIO peripheral. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API.
 */
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "PIT.h"

extern  BOOL PIT1_Flag;
extern float volumeH;
extern float volumeL;

GPIO_portCType Flag_GPIOC ={.allBits=0};
uint8 frecuencia = 40;

void PORTC_IRQHandler(){
	static uint8 tempVolumeH = 50;
	static uint8 tempVolumeL = 50;
	if(!PIT1_Flag){
		GPIO_clearInterrupt(GPIOC);
		return;
	}
	Flag_GPIOC.allBits = PORTC_ISFR;
	if(Flag_GPIOC.bitField.pb0){
		if(frecuencia>10)
			frecuencia -=10;
		PIT_timerStartSeconds(PIT_0,SYSTEMCLOCK, .001/frecuencia);
	}	else if(Flag_GPIOC.bitField.pb1){
		if(frecuencia<60)
			frecuencia +=10;
		PIT_timerStartSeconds(PIT_0,SYSTEMCLOCK, .001/frecuencia);
	}	else if(Flag_GPIOC.bitField.pb2){
		if(tempVolumeH>0){
			tempVolumeH -= 10;
			volumeH = tempVolumeH/100.0;
		}
	}	else if(Flag_GPIOC.bitField.pb3){
		if(tempVolumeH<100){
			tempVolumeH += 10;
			volumeH = tempVolumeH/100.0;
		}
	}else if(Flag_GPIOC.bitField.pb5){
		if(tempVolumeL>0){
			tempVolumeL -= 10;
			volumeL = tempVolumeL/100.0;
		}
	}
	else if(Flag_GPIOC.bitField.pb7){
		if(tempVolumeL<100){
			tempVolumeL += 10;
			volumeL = tempVolumeL/100.0;
		}
	}
	PIT1_Flag = FALSE;
	PIT_delay(PIT_1,SYSTEMCLOCK ,.3);
}

void GPIO_clearInterrupt(GPIO_portNameType portName){
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIOA: /** GPIO A is selected*/
			PORTA_ISFR=0xFFFFFFFF;
			break;
		case GPIOB: /** GPIO B is selected*/
			PORTB_ISFR=0xFFFFFFFF;
			break;
		case GPIOC: /** GPIO C is selected*/
			PORTC_ISFR = 0xFFFFFFFF;
			break;
		case GPIOD: /** GPIO D is selected*/
			PORTD_ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE_ISFR=0xFFFFFFFF;
			break;
	}// end switch
}
void GPIO_clockGating(GPIO_portNameType portName){
	switch(portName)/** Selecting the GPIO for clock enabling*/
		{
			case GPIOA: /** GPIO A is selected*/
				SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
				break;
			case GPIOB: /** GPIO B is selected*/
				SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
				break;
			case GPIOC: /** GPIO C is selected*/
				SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
				break;
			case GPIOD: /** GPIO D is selected*/
				SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
				break;
			case GPIOE: /** GPIO E is selected*/
				SIM_SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
				break;
			default: /**If doesn't exist the option*/
			break;
		}// end switch
}
void GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister){
	switch(portName)
		{
		case GPIOA:/** GPIO A is selected*/
			PORTA_PCR(pin)= *pinControlRegister;
			break;
		case GPIOB:/** GPIO B is selected*/
			PORTB_PCR(pin)= *pinControlRegister;
			break;
		case GPIOC:/** GPIO C is selected*/
			PORTC_PCR(pin)= *pinControlRegister;
			break;
		case GPIOD:/** GPIO D is selected*/
			PORTD_PCR(pin)= *pinControlRegister;
			break;
		case GPIOE: /** GPIO E is selected*/
			PORTE_PCR(pin)= *pinControlRegister;
		default:/**If doesn't exist the option*/
		break;
		}
}
void GPIO_writePORT(GPIO_portNameType portName, uint32 data ){
	switch (portName){
		case GPIOA:/** GPIO A is selected*/
			GPIOA_PDOR = data;
		break;
		case GPIOB:/** GPIO B is selected*/
			GPIOB_PDOR = data;
		break;
		case GPIOC:/** GPIO C is selected*/
			GPIOC_PDOR = data;
		break;
		case GPIOD:/** GPIO D is selected*/
			GPIOD_PDOR = data;
		break;
		case GPIOE:/** GPIO E is selected*/
			GPIOE_PDOR = data;
		break;
		default:
		break;
	}
}

uint32 GPIO_readPORT(GPIO_portNameType portName){
	uint32 inputValue=0;
	switch (portName){
		case GPIOA:/** GPIO A is selected*/
			inputValue=GPIOA_PDIR;
		break;
		case GPIOB:/** GPIO B is selected*/
			inputValue=GPIOB_PDIR;
		break;
		case GPIOC:/** GPIO C is selected*/
			inputValue=GPIOC_PDIR;
		break;
		case GPIOD:/** GPIO D is selected*/
			inputValue=GPIOD_PDIR;
		break;
		case GPIOE:/** GPIO E is selected*/
			inputValue=GPIOE_PDIR;
		break;
		default:
		break;
	}
	return inputValue;
}
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	uint32 inputValue;
	inputValue= GPIO_readPORT(portName);
	uint32 inputBit=0x1<<pin;
	inputBit=(inputBit&inputValue)?1:0;
	return inputBit;
}
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){
	uint32 inputBit=0x1<<pin;
	switch (portName){
			case GPIOA:/** GPIO A is selected*/
				GPIOA_PSOR = inputBit;
			break;
			case GPIOB:/** GPIO B is selected*/
				GPIOB_PSOR = inputBit;
			break;
			case GPIOC:/** GPIO C is selected*/
				GPIOC_PSOR = inputBit;
			break;
			case GPIOD:/** GPIO D is selected*/
				GPIOD_PSOR = inputBit;
			break;
			case GPIOE:/** GPIO E is selected*/
				GPIOE_PSOR = inputBit;
			break;
			default:
			break;
		}
}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){
	uint32 inputBit=0x1<<pin;
		switch (portName){
				case GPIOA:/** GPIO A is selected*/
					GPIOA_PCOR = inputBit;
				break;
				case GPIOB:/** GPIO B is selected*/
					GPIOB_PCOR = inputBit;
				break;
				case GPIOC:/** GPIO C is selected*/
					GPIOC_PCOR = inputBit;
				break;
				case GPIOD:/** GPIO D is selected*/
					GPIOD_PCOR = inputBit;
				break;
				case GPIOE:/** GPIO E is selected*/
					GPIOE_PCOR = inputBit;
				break;
				default:
				break;
			}
}
void GPIO_changePIN(GPIO_portNameType portName, uint8 pin, uint8 value){
	uint32 inputBit=0x1<<pin;
	switch (portName){
			case GPIOA:/** GPIO A is selected*/
				if(value) GPIOA_PSOR = inputBit; else GPIOA_PCOR = inputBit;
			break;
			case GPIOB:/** GPIO B is selected*/
				if(value) GPIOB_PSOR = inputBit; else GPIOB_PCOR = inputBit;
			break;
			case GPIOC:/** GPIO C is selected*/
				if(value) GPIOC_PSOR = inputBit; else GPIOC_PCOR = inputBit;
			break;
			case GPIOD:/** GPIO D is selected*/
				if(value) GPIOD_PSOR = inputBit; else GPIOD_PCOR = inputBit;
			break;
			case GPIOE:/** GPIO E is selected*/
				if(value) GPIOE_PSOR = inputBit; else GPIOE_PCOR = inputBit;
			break;
			default:
			break;
		}
}
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	uint32 inputBit=0x1<<pin;
		switch (portName){
				case GPIOA:/** GPIO A is selected*/
					GPIOA_PTOR = inputBit;
				break;
				case GPIOB:/** GPIO B is selected*/
					GPIOB_PTOR = inputBit;
				break;
				case GPIOC:/** GPIO C is selected*/
					GPIOC_PTOR = inputBit;
				break;
				case GPIOD:/** GPIO D is selected*/
					GPIOD_PTOR = inputBit;
				break;
				case GPIOE:/** GPIO E is selected*/
					GPIOE_PTOR = inputBit;
				break;
				default:
				break;
			}
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch (portName){
		case GPIOA:/** GPIO A is selected*/
			GPIOA_PDDR=0xFFFFFFFF;
		break;
		case GPIOB:/** GPIO B is selected*/
			GPIOB_PDDR=0xFFFFFFFF;
		break;
		case GPIOC:/** GPIO C is selected*/
			GPIOC_PDDR=0xFFFFFFFF;
		break;
		case GPIOD:/** GPIO D is selected*/
			GPIOD_PDDR=0xFFFFFFFF;
		break;
		case GPIOE:/** GPIO E is selected*/
			GPIOE_PDDR=0xFFFFFFFF;
		break;
		default:
		break;
	}
}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	uint32 inputBit=0x1<<pin;
			switch (portName){
					case GPIOA:/** GPIO A is selected*/
						GPIOA_PDDR |= inputBit;
					break;
					case GPIOB:/** GPIO B is selected*/
						GPIOB_PDDR |= inputBit;
					break;
					case GPIOC:/** GPIO C is selected*/
						GPIOC_PDDR |= inputBit;
					break;
					case GPIOD:/** GPIO D is selected*/
						GPIOD_PDDR |= inputBit;
					break;
					case GPIOE:/** GPIO E is selected*/
						GPIOE_PDDR |= inputBit;
					break;
					default:
					break;
				}
}





