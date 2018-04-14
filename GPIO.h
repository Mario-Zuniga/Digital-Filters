/**
	\file 
	\brief 
		This is the header file for the GPIO device driver for Kinetis K64. 
		It contains all configuration functions and runtime functions. 
		i.e., this is the application programming interface (API) for the GPIO peripheral. 
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not included in this API.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"


/** Constant that represent the clock enable for GPIO A */
#define GPIO_CLOCK_GATING_PORTA 0x00000200 
/** Constant that represent the clock enable for GPIO B */
#define GPIO_CLOCK_GATING_PORTB 0x00000400 
/** Constant that represent the clock enable for GPIO C */
#define GPIO_CLOCK_GATING_PORTC 0x00000800 
/** Constant that represent the clock enable for GPIO D  */
#define GPIO_CLOCK_GATING_PORTD 0x00001000 
/** Constant that represent the clock enable for GPIO E */
#define GPIO_CLOCK_GATING_PORTE 0x00002000 


/** Selects a pullup resistor */
#define GPIO_PS    0x00000001 
/** Enables the pulldown or pullup resistors*/
#define GPIO_PE    0x00000002 
/** Selects slow or fast slew rate */
#define GPIO_SRE   0x00000004 
/** Enables the passive filter */
#define GPIO_PFE   0x00000010 
/** Enables the open drain  */
#define GPIO_ODE   0x00000020  
/** Selects between low drive strength and high drive strength */
#define GPIO_DSE   0x00000040 
/** Selects alternative function 1 (GPIO) */
#define GPIO_MUX1  0x00000100 
/** Selects alternative function 2 */
#define GPIO_MUX2  0x00000200
/** Selects alternative function 3 */
#define GPIO_MUX3  0x00000300
/** Selects alternative function 4 */
#define GPIO_MUX4  0x00000400 
/** Selects alternative function 5 */
#define GPIO_MUX5  0x00000500 
/** Selects alternative function 6 */
#define GPIO_MUX6  0x00000600 
/** Selects alternative function 7 */
#define GPIO_MUX7  0x00000700 
/**Selects the interruption on falling-edge*/
#define GPIO_INTERRUPT_FALLING  0xA0000
/**Selects the interruption on RISING-edge*/
#define GPIO_INTERRUPT_RISING  0x90000
/**Selects the interruption on either-edge*/
#define GPIO_INTERRUPT_EITHER  0xB0000
/**Selects the interruption on logic 0*/
#define GPIO_INTERRUPT_ZERO  0x80000
/**Selects the interruption on logic 1*/
#define GPIO_INTERRUPT_ONE  0xC0000

#define GPIO_PIN_INTERRUPT_MASK 0x01000000

/*! This definition is used to configure whether a pin is an input or an output*/
typedef enum {GPIO_INPUT,/*!< Definition to configure a pin as input */
			  GPIO_OUTPUT /*!< Definition to configure a pin as output */
			 }GPIO_PIN_CONFIG; 
/*! These definition is used to select an specific port in the different API functions*/
typedef enum{
	GPIOA, /*!< Definition to select GPIO A */
	 GPIOB, /*!< Definition to select GPIO B */
	 GPIOC, /*!< Definition to select GPIO C */
	 GPIOD, /*!< Definition to select GPIO D */
	 GPIOE /*!< Definition to select GPIO E */
} GPIO_portNameType;

/*! This data type is used to configure the pin control register*/
typedef const uint32 GPIO_pinControlRegisterType;

/** This data type is used to store which push button caused the interruption*/
typedef union{
		uint8 allBits;
		uint8 pbs:6;
		struct{
			uint8 pb0 :1;
			uint8 pb1 :1;
			uint8 pb2 :1;
			uint8 pb3 :1;
			uint8 pb4 :1;
			uint8 pb5 :1;
			uint8 pb6 :1;
			uint8 pb7 :1;
		}bitField;
} GPIO_portCType;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function clears the interruption bit of the specified port
 	 \param[in]  portName Port interruption to be cleared.

 */
void GPIO_clearInterrupt(GPIO_portNameType portName);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit 
 	 	 and register in the System Clock Gating Control Register
 	 \param[in]  portName Port to be configured.
 	
 */
void GPIO_clockGating(GPIO_portNameType portName);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 This function configure different characteristics in an specific GPIO:
 	 	 pullup or pulldown resitor,slew rate, drive strength, passive filter,open drain pin,alternative functions in the GPIO
 	 \param[in] portName Port to be configured.
 	 \param[in]  pin Specific pin to be configured.
 	 \param[in]  pinControlRegister Pointer to a constant configuration value.
 */
void GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,GPIO_pinControlRegisterType* pinControlRegister);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
 	 	 This function configure all the GPIO port as input when 1 logic is written or output when 0 logic is written.
 	 \param[in] portName Port to configure
 	 \param[in] direction Input value to specify the port as input or output.

 */
void GPIO_dataDirectionPORT(GPIO_portNameType portName, uint32 direction);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief  This function configure specific pins of a GPIO port as input when 1 logic is written or output when 0 logic is written.
 	 \param[in] portName Port to configure.
 	 \param[in] state Value to specify if the pin behaves as input or output.
 	 \param[in] pin Input value to specify the pin number.
 */
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 state, uint8 pin);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function reads all the GPIO port.
 	 \param[in] portName Port to be read.
 	 \return  It is the value read from a GPIO. It is a 32-bit value.
 	
 */
uint32 GPIO_readPORT(GPIO_portNameType portName);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function reads a specific GPIO pin.
	 \param[in] portName Port to be read.
 	 \param[in] pin Pin to be read.
 	 \return This function return 0 if the value of the pin is 0 logic or 1 is the value the pin is 1 logic.
 */
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function writes all the GPIO port.
 	 \param[in] portName Port to be written.
 	 \param[in] data Value to be written.
 */
void GPIO_writePORT(GPIO_portNameType portName, uint32 data);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	\brief This set an specific pin in a GPIO port.
 	\param[in] portName Port to be selected.
 	\param[in] pin Pin to be set.
 */
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This clear an specific pin in a GPIO port.
 	 \param[in] portName Selected Port.
 	 \param[in] pin Pin to be clear.
 */
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin);

void GPIO_changePIN(GPIO_portNameType portName, uint8 pin, uint8 value);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This toggle the value of a specific pin in a GPIO port.
 	 \param[in] portName Selected Port.
 	 \param[in] pin Pin to be toggled.
 */
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin);


#endif /* GPIO_H_ */
