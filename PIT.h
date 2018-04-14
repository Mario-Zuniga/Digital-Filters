#ifndef PIT_H_
#define PIT_H_


#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "GPIO.h"

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_TimerType;

/** Constant that represent the clock enable for pit */
#define PIT_CLOCK_GATING 0x00800000

/**Constants to configure the timer control register*/
#define PIT_timerEnable 0x1
#define PIT_timerInterruptEnable 0x2
#define PIT_chainMode 0x4

/*! This data type is used to configure the timer control register*/
typedef const uint32 PIT_timerControlRegisterType;
typedef const uint32 PIT_module_Control_RegisterType;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is the interrupt vector for the timer 0.
 	 Internally it clears the timer 0 interrupt and set a flag for the timer 0

 	 \return void
 */
void PIT0_IRQHandler();
void PIT1_IRQHandler();
void PIT2_IRQHandler();
void PIT_enable();
void PIT_module_Control_Register(PIT_module_Control_RegisterType config);
void PIT_timerControlRegister(PIT_TimerType pitTimer,PIT_timerControlRegisterType configuration);
void PIT_stopTimer(PIT_TimerType pitTimer);
void PIT_timerStartValue(PIT_TimerType pitTimer,uint32 value);
void PIT_timerStartSeconds(PIT_TimerType pitTimer,float systemClock, float seconds);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 Internally it configures the clock gating and enables the PIT module.
 	 It is important to note that this strictly is not device driver since everything is 
 	 contained in a single function, but in general you have to avoid this practices, this only
 	 for the propose of the homework
 	 	  	 	 
 	 \param[in]  portName Port to be configured.
 	 \return void
 */
void PIT_delay(PIT_TimerType pitTimer,float systemClock ,float period);

#endif /* PIT_H_ */
