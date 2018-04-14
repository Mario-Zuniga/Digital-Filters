#ifndef SOURCES_ADC_H_
#define SOURCES_ADC_H_

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
/*! These definition is used to select software of hardware functions of the ADC*/
typedef enum{
	A,/*!< Definition to select SCIA*/
	B/*!< Definition to select SCIB*/
}SCIn;
/*! These definition is used to enable or disable: COCO, differential mode, low power mode, compare mode, continues conversion and average mode*/
typedef enum{
	DISABLE,/*!< Definition to Disable*/
	ENABLE	/*!< Definition to Enable*/
}INTERRUPT_ENABLE,
DIFF,
LOW_POWER,
COMPARE_FUNCTION,
CONTINUOUS_CONVERSION,
AVERAGE_ENABLE;
/*! These definition is used to select the channel used in the ADC*/
typedef enum{
	CHANNEL0,	/*!< Definition to select channel 0*/
	CHANNEL1 	/*!< Definition to select channel 1*/
}CHANNEL;
/*! These definition is used to select the division of the clock*/
typedef enum{
	CLOCK_1,	/*!< Definition to select clock/1*/
	CLOCK_2,	/*!< Definition to select clock/2*/
	CLOCK_4,	/*!< Definition to select clock/4*/
	CLOCK_8 	/*!< Definition to select clock/8*/
}CLOCK_DIVIDE;
/*! These definition is used to select the time of a sample*/
typedef enum{
	SHORT,		/*!< Definition to select short time*/
	LONG  		/*!< Definition to select long time*/
}SAMPLE_TIME;
/*! These definition is used to select the number of bits used in the conversion*/
typedef enum{
	MODE_8_9,	/*!< Definition to select 8 bits on regular mode and 9 on differential mode*/
	MODE_12_13,	/*!< Definition to select 12 bits on regular mode and 13 on differential mode*/
	MODE_10_11,	/*!< Definition to select 10 bits on regular mode and 11 on differential mode*/
	MODE_16_16	/*!< Definition to select 16 bits on regular mode and 16 on differential mode*/
}MODE;
/*! These definition is used to select the source of the clock*/
typedef enum{
	BUS_CLOCK,	/*!< Definition to select bus clock*/
	ALTCLK2,	/*!< Definition to select altclk2*/
	ALTCLK,		/*!< Definition to select altclk*/
	ADACK		/*!< Definition to select adack*/
}CLOCK;
/*! These definition is used to select where the trigger comes from*/
typedef enum{
	SOFTWARE,	/*!< Definition to select software trigger*/
	HARDWARE	/*!< Definition to select hardware trigger*/
}TRIGGER;
/*! These definition is used to select the source of the reference voltage*/
typedef enum{
	DEFAULT_VOLTAGE,	/*!< Definition to select the kinetis voltage*/
	ALTERNATE_REFERENCE	/*!< Definition to select an alternate reference*/
}VOLTAGE_REFERENCE;
/*! These definition is used to select the source of the number of samples to average*/
typedef enum{
	SAMPLES_4,	/*!< Definition to select the 4 samples*/
	SAMPLES_8,	/*!< Definition to select the 8 samples*/
	SAMPLES_16,	/*!< Definition to select the 16 samples*/
	SAMPLES_32	/*!< Definition to select the 32 samples*/
}AVERAGE;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables and specified ADC
 	 \param[in]  ADC_x ADC to activate.
 */
void clockGatingADC(ADC_Type* ADC_x);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns the value of COCO
 	 \param[in]  ADC_x ADC to read its COCO flag.
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \return This function returns 1 if the conversion is complete, 0 if it isn't.
 */
uint8 conversionComplete(ADC_Type* ADC_x, SCIn n);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the COCO flag
 	 \param[in]  ADC_x ADC to enable its COCO.
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \param[in]  ED Enable or disable value to set in AIEN.
 */
void interruptEnable(ADC_Type* ADC_x, SCIn n,INTERRUPT_ENABLE ED);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the differential mode
 	 \param[in]  ADC_x ADC to enable its differential mode.
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \param[in]  ED Enable or disable value to set in DIFF.
 */
void diferentialEnable(ADC_Type* ADC_x, SCIn n, DIFF ED);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function selects a channel
 	 \param[in]  ADC_x Active ADC
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \param[in]  channel Channel to use in the selected ADC.
 */
void channelSelect(ADC_Type* ADC_x, SCIn n, CHANNEL channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configures the SC1 register of and specified ADC
 	 \param[in]  ADC_x Selected ADC.
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \param[in]  ED0 Enable or disable value to set in AIEN.
 	 \param[in]  ED1 Enable or disable value to set in DIFF.
 	 \param[in]  channel Channel to use in the selected ADC.
 */
void ADCx_SC1(ADC_Type* ADC_x, SCIn n, INTERRUPT_ENABLE ED0, DIFF ED1, CHANNEL channel);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the low power mode
 	 \param[in]  ADC_x ADC to enable its low power mode.
 	 \param[in]  ED Enable or disable low power mode.
 */
void lowPower(ADC_Type* ADC_x, LOW_POWER ED);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sets the number to divide the clock
 	 \param[in]  ADC_x ADC to set it´s clock divider.
 	 \param[in]  clk Number to divide the source clock.
 */
void clockDivide(ADC_Type* ADC_x, CLOCK_DIVIDE clk);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sets sample time to short or long
 	 \param[in]  ADC_x ADC to enable its low.
 	 \param[in]  time Sets the sample time to short or long.
 */
void sampleTime(ADC_Type* ADC_x, SAMPLE_TIME time);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sets the number of bits to write in ADC_R
 	 \param[in]  ADC_x ADC to set it´s mode.
 	 \param[in]  mode Number of bits to use.
 */
void conversionMode(ADC_Type* ADC_x, MODE mode);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sets source of the clock
 	 \param[in]  ADC_x ADC to set it´s clock source.
 	 \param[in]  clk Source of the clock.
 */
void inputClock(ADC_Type* ADC_x, CLOCK clk);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sets CFG1
 	 \param[in]  ADC_x ADC to enable its low.
 	 \param[in]  ED Enable or disable low power mode.
 	 \param[in]  clk0 Number to divide the source clock.
 	 \param[in]  time Sets the sample time to short or long.
 	 \param[in]  mode Number of bits to use.
 	 \param[in]  clk1 Source of the clock.
 */
void ADCx_CFG1(ADC_Type* ADC_x, LOW_POWER ED, CLOCK_DIVIDE clk0, SAMPLE_TIME time, MODE mode, CLOCK clk1);
/*!
 	 \brief	 This function returns the value the conversion
 	 \param[in]  ADC_x ADC to read its value.
 	 \param[in]  n A for use in hardware or software, B for software only.
 	 \return This function returns the value of the conversion.
 */
uint16 getValue(ADC_Type* ADC_x, SCIn n);
/*!
 	 \brief	 This function returns the value of ADACT
 	 \param[in]  ADC_x ADC to read its ADACT value.
 	 \return This function returns 1 if there is a conversion in progress.
 */
uint8 conversionActive(ADC_Type* ADC_x);
/*!
 	 \brief	 This function sets the type of trigger
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  SH Type of trigger.
 */
void conversionTrigger(ADC_Type* ADC_x, TRIGGER SH);
/*!
 	 \brief	 This function enables or disables the compare mode
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  ED Enable or disable compare mode.
 */
void compareFunction(ADC_Type* ADC_x, COMPARE_FUNCTION ED);
/*!
 	 \brief	 This function selects the voltage reference
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  reference Source of the reference
 */
void voltageReference(ADC_Type* ADC_x, VOLTAGE_REFERENCE reference);
/*!
 	 \brief	 This function sets the SC2 register
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  SH Type of trigger.
 	 \param[in]  ED Enable or disable compare mode.
 	 \param[in]  reference Source of the reference
 */
void ADCx_SC2(ADC_Type* ADC_x, TRIGGER SH, COMPARE_FUNCTION ED, VOLTAGE_REFERENCE reference);
/*!
 	 \brief	 This function enables or disables the continues conversion mode
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  ED Enable or disable continues conversion mode.
 */
void continuesConversion(ADC_Type* ADC_x, CONTINUOUS_CONVERSION ED);
/*!
 	 \brief	 This function enables or disables the average mode
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  ED Enable or disable average mode.
 */
void averageEnable(ADC_Type* ADC_x, AVERAGE_ENABLE ED);
/*!
 	 \brief	 This function sets the number of samples for the average mode
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  average Number of samples.
 */
void averageSelect(ADC_Type* ADC_x, AVERAGE average);
/*!
 	 \brief	 This function sets the SC3 register
 	 \param[in]  ADC_x selected ADC.
 	 \param[in]  ED0 Enable or disable continues conversion mode.
 	 \param[in]  ED1 Enable or disable average mode.
 	 \param[in]  average Number of samples.
 */
void ADCx_SC3(ADC_Type* ADC_x, CONTINUOUS_CONVERSION ED0, AVERAGE_ENABLE ED1, AVERAGE average);

#endif /* SOURCES_ADC_H_ */
