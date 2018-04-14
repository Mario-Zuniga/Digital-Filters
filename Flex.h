#ifndef SOURCES_FLEX_H_
#define SOURCES_FLEX_H_

#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"

/**Flex timers*/
#define FTM_0 FTM0
#define FTM_1 FTM1
#define FTM_2 FTM2


/**Flex channels*/
#define FTM_CH0 0
#define FTM_CH1 1
#define FTM_CH2 2
#define FTM_CH3 3
#define FTM_CH4 4
#define FTM_CH5 5
#define FTM_CH6 6
#define FTM_CH7 7

/**Bit masks*/
#define FTM_TOF 0b10000000
#define FTM_0_CLOCK_GATING 0x1000000
#define FTM_1_CLOCK_GATING 0x2000000
#define FTM_2_CLOCK_GATING 0x4000000

/**Constants for FTM mode selection*/
#define FTM_MSB_MSA_ELSB_ELSA 0b111100
#define FTM_INPUT_CAPTURE_RISING 0b000100
#define FTM_INPUT_CAPTURE_FALLING 0b001000
#define FTM_INPUT_CAPTURE_RISING_OR_FALLING 0b001100
#define FTM_OUTPUT_COMPARE_TOGGLE 0b010100
#define FTM_OUTPUT_COMPARE_CLEAR 0b011000
#define FTM_OUTPUT_COMPARE_SET 0b011100
#define FTM_EDGE_PWM_HIGH_TRUE 0b101000
#define FTM_EDGE_PWM_LOW_TRUE 0b100100

/** These definition is used to enable or disable the interruption for the channel or the FTM*/
typedef enum{FTM_INTERRUPT_DISABLE,
	FTM_INTERRUPT_ENABLE
}FTM_INTERRUPT_TYPE;

/** These definition is used to configure the pwm in up mode or up-down mode*/
typedef enum{PWM_UP,
	PWM_UP_DOWN
}FTM_PWM_TYPE;

/**These definition is used toselect the clock source to use*/
typedef enum{FTM_NO_CLOCK,
	FTM_SYSTEM_CLOCK,
	FTM_FIXED_FREQUENCY_CLOCK,
	FTM_EXTERNAL_CLOCK
}FTM_CLOCK_TYPE;

/** These definition is used to select the preescaler used for the clock source*/
typedef enum{FTM_BY_1,
	FTM_BY_2,
	FTM_BY_4,
	FTM_BY_8,
	FTM_BY_16,
	FTM_BY_32,
	FTM_BY_64,
	FTM_BY_128,
}FTM_PRESCALER_TYPE;

void FTM2_IRQHandler();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This clears the interrupt flag from the Flex timer send in the argument.
 	 \param[in] flex Is the flex timer you want to clear the interrupt for.
 */
void FTM_clearFlag(FTM_Type* flex);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function enable the interrupt for the overflow of the selected Flex timer.
 	 \param[in] flex Is the flex timer you want to enable the interruption for.
 	 \param[in] ENABLE Is used to either activate or deactivate the interruption.
 */
void FTM_interruptEnable(FTM_Type * flex, FTM_INTERRUPT_TYPE ENABLE);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function selects the mode of operation for the PWM on the selected Flex timer.
 	 \param[in] flex Is the flex timer you want to change the pwm mode for.
 	 \param[in] pwm The mode of operation for the PWM.
 */
void FTM_PWMMode(FTM_Type * flex, FTM_PWM_TYPE pwm);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function changes the source clock for the Flex timer.
 	 \param[in] flex Is the flex timer you want to change the clock for.
 	 \param[in] clock Is used to select the source clock to apply to the FTM.
 */
void FTM_setClockSource(FTM_Type * flex, FTM_CLOCK_TYPE clock);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function changes the preescater for the source clock.
 	 \param[in] flex Is the flex timer you want to change the preescaler for.
 	 \param[in] pre Is used to select the prescaler to apply to the FTM.
 */
void FTM_prescaleFactor(FTM_Type * flex, FTM_PRESCALER_TYPE pre);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function returns the current count of the counter.
 	 \param[in] flex Is the flex timer you want to get the counter from.
 */
uint16 FTM_getCounterValue(FTM_Type * flex);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function changes the value at wich the counter overflows.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] value Is a 16 bit value at wich the timer will overflow and activate the timer overflow flag.
 */
void FTM_setModValue(FTM_Type * flex, uint16 value);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function changes the CV register of the channel, its used in the pwm mode to define a duty cicle.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 	 \param[in] value Is a 16 bit value you want to store in the CnV value.
 */
void FTM_setCountValue(FTM_Type * flex, uint8 channel, uint16 value);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function returns the CV register value os the channel.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 */
uint16 FTM_getCountValue(FTM_Type * flex, uint8 channel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function clears the overflow flag for the selected channel.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 */
void FTM_clearChannelFlag(FTM_Type * flex, uint8 channel); 

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function is used to activate or deactivate the interruption for the selected channel.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 	 \param[in] interrupt Is either FTM_INTERRUPT_ENABLE or FTM_INTERRUPT_DISABLE.
 */
void FTM_channelInterruptEnable(FTM_Type * flex, uint8 channel, FTM_INTERRUPT_TYPE interrupt);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function is used to configure the mode at wich the selected channel will be used.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 	 \param[in] mode Is the mode you want ELSA, ELSB, MSA, MSB to be configured.
 */
void FTM_channelMode(FTM_Type * flex, uint8 channel, uint8 mode);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function is used to initialize a desired FTM and channel to work as a PWM.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 	 \param[in] MOD Is value at wich you want the timer to overflow.
 	 \param[in] CV Is value at wich you want the output to be toggled.
 */
void FTM_initPWM(FTM_Type * flex, uint8 channel, uint16 MOD, uint16 CV);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This function is used to initialize a desired FTM and channel to work in input compare mode.
 	 \param[in] flex Is the flex timer you want to modify.
 	 \param[in] channel Is the flex timer channel you want to modify.
 	 \param[in] MOD Is value at wich you want the timer to overflow.
 */
void FTM_InitInputCompare(FTM_Type * flex, uint8 channel, uint16 MOD);

#endif /* SOURCES_FLEX_H_ */
