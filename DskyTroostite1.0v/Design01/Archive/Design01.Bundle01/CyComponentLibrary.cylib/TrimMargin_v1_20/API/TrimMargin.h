/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes and constants available to the TrimMargin
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/
#define `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS       (`$NumConverters`u)
#define `$INSTANCE_NAME`_PWM_RESOLUTION             (`$PWMResolution`u)


#include "`$INSTANCE_NAME`_TrimPWM_1.h"
#include "`$INSTANCE_NAME`_Control_En_Reg.h"
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 3)
    #include "`$INSTANCE_NAME`_TrimPWM_2.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 5)
    #include "`$INSTANCE_NAME`_TrimPWM_3.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 7)
    #include "`$INSTANCE_NAME`_TrimPWM_4.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 9)
    #include "`$INSTANCE_NAME`_TrimPWM_5.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 11)
    #include "`$INSTANCE_NAME`_TrimPWM_6.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 13)
    #include "`$INSTANCE_NAME`_TrimPWM_7.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 15)
    #include "`$INSTANCE_NAME`_TrimPWM_8.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 17)
    #include "`$INSTANCE_NAME`_TrimPWM_9.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 19)
    #include "`$INSTANCE_NAME`_TrimPWM_10.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 21)
    #include "`$INSTANCE_NAME`_TrimPWM_11.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */
#if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS >= 23)
    #include "`$INSTANCE_NAME`_TrimPWM_12.h"
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS */


/***************************************
*      Data Struct Definition
***************************************/
typedef struct
{
    uint8 above;        /* Cumulative ADC readings ABOVE rawMax     */
    uint8 below;        /* Cumulative ADC readings BELOW rawMin     */
} `$INSTANCE_NAME`_TRIMCTL_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
`$DutyCycleTypeReplacementString` `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(uint8 converterNum, uint16 desiredVoltage)
                                    `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToDutyCycle")`;
`$DutyCycleTypeReplacementString`
    `$INSTANCE_NAME`_ConvertVoltageToPreRunDutyCycle(uint8 converterNum, uint16 desiredVoltage)
                                    `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToPreRunDutyCycle")`;
void `$INSTANCE_NAME`_SetMarginHighVoltage(uint8 converterNum, uint16 marginHiVoltage)
                                    `=ReentrantKeil($INSTANCE_NAME . "_SetMarginHighVoltage")`;
uint16 `$INSTANCE_NAME`_GetMarginHighVoltage(uint8 converterNum)
                                    `=ReentrantKeil($INSTANCE_NAME . "_GetMarginHighVoltage")`;
void `$INSTANCE_NAME`_SetMarginLowVoltage(uint8 converterNum, uint16 marginLoVoltage)
                                    `=ReentrantKeil($INSTANCE_NAME . "_SetMarginLowVoltage")`;
uint16 `$INSTANCE_NAME`_GetMarginLowVoltage(uint8 converterNum)
                                    `=ReentrantKeil($INSTANCE_NAME . "_GetMarginLowVoltage")`;
void `$INSTANCE_NAME`_ActiveTrim(uint8 converterNum, uint16 actualVoltage, uint16 desiredVoltage)
                                    `=ReentrantKeil($INSTANCE_NAME . "_ActiveTrim")`;
void `$INSTANCE_NAME`_SetDutyCycle(uint8 converterNum, `$DutyCycleTypeReplacementString` dutyCycle)
                                    `=ReentrantKeil($INSTANCE_NAME . "_SetDutyCycle")`;
`$DutyCycleTypeReplacementString` `$INSTANCE_NAME`_GetDutyCycle(uint8 converterNum)
                                    `=ReentrantKeil($INSTANCE_NAME . "_GetDutyCycle")`;
`$AlertSourceTypeReplacementString` `$INSTANCE_NAME`_GetAlertSource(void)
                                    `=ReentrantKeil($INSTANCE_NAME . "_GetAlertSource")`;



/***************************************
* External identifier
***************************************/
extern uint8 `$INSTANCE_NAME`_initVar;
extern `$AlertSourceTypeReplacementString` `$INSTANCE_NAME`_alertSource;
extern `$DutyCycleTypeReplacementString` `$INSTANCE_NAME`_vMarginHighDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern `$DutyCycleTypeReplacementString` `$INSTANCE_NAME`_vMarginLowDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE `$INSTANCE_NAME`_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE
                                    `$INSTANCE_NAME`_PRE_RUN_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_VNOMINAL[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE
                                    `$INSTANCE_NAME`_STARTUP_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE
                                    `$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16 `$INSTANCE_NAME`_vMarginLow[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16 `$INSTANCE_NAME`_vMarginHigh[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern `$INSTANCE_NAME`_TRIMCTL_STRUCT `$INSTANCE_NAME`_trimCtl[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

extern const uint16 CYCODE `$INSTANCE_NAME`_VMARGIN_LOW[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_VMARGIN_HIGH[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_VDELTA[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_DUTYCYCLES_PER_VOLT[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE
                                    `$INSTANCE_NAME`_VMARGIN_LOW_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const `$DutyCycleTypeReplacementString` CYCODE
                                    `$INSTANCE_NAME`_VMARGIN_HIGH_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_PRE_COEF[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_VMAX[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_VMIN[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_MarginHigh/`$INSTANCE_NAME`_MarginLow
********************************************************************************
*
* Summary:
*  Sets the selected power converter output voltage to the desired Margin Low
*  setting as specified in the Voltages Tab of the customizer or as per the
*  `$INSTANCE_NAME`_SetMarginLowVoltage() API.
*
* Parameters:
*  uint8 converterNum: Specifies the power converter number
*                      Valid range: 1..24
*
* Return:
*  void
*
*******************************************************************************/
#define `$INSTANCE_NAME`_MarginHigh(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_vMarginHighDutyCycle[(n) - 1u])
#define `$INSTANCE_NAME`_MarginLow(n)  `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_vMarginLowDutyCycle[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_SetNominal
********************************************************************************
*
* Summary:
*  Sets the selected power converter output voltage to the Nominal Voltage
*  setting as specified in the Voltages Tab of the customizer.
*
* Parameters:
*  uint8 converterNum: Specifies the power converter number
*                      Valid range: 1..24
*
* Return:
*  void
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetNominal(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_SetPreRun
********************************************************************************
*
* Summary:
*  Sets the pre-charge PWM duty cycle required to achieve nominal voltage
*  before the power converter is enabled with the assumption that R1 is
*  grounded in parallel with R2.
*
* Parameters:
*  uint8 converterNum: Specifies the power converter number
*                      Valid range: 1..24
*
* Return:
*  void
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetPreRun(n)  `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_PRE_RUN_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_SetStartup
********************************************************************************
*
* Summary:
*  Sets the selected power converter output voltage to the Startup Voltage
*  setting as specified in the Voltages Tab of the customizer.
*
* Parameters:
*  uint8 converterNum: Specifies the power converter number
*                      Valid range: 1..24
*
* Return:
*  void
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetStartup(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_STARTUP_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_SetStartupPreRun
********************************************************************************
*
* Summary:
*  Sets the pre-charge PWM duty cycle required to achieve the Startup Voltage
*  before the power converter is enabled with the assumption that R1 is
*  grounded in parallel with R2.
*
* Parameters:
*  uint8 converterNum: Specifies the power converter number
*                      Valid range: 1..24
*
* Return:
*  void
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetStartupPreRun(n) \
                                `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[(n) - 1u])


/***************************************
*          API Constants
***************************************/
#define `$INSTANCE_NAME`_MAX_NUMBER_OF_CONVERTERS       (24u)
#define `$INSTANCE_NAME`_PWM_MIN                        (0u)
#define `$INSTANCE_NAME`_PWM_MAX                        (0xFFFFu >> (16u - `$INSTANCE_NAME`_PWM_RESOLUTION))

#define `$INSTANCE_NAME`_POLARITY_POSITIVE              (0u)
#define `$INSTANCE_NAME`_POLARITY_NEGATIVE              (1u)

#define `$INSTANCE_NAME`_FALSE                          (0u)
#define `$INSTANCE_NAME`_TRUE                           (1u)


/*******************************************************************************
*
* `$INSTANCE_NAME`_TRIM_SLOW_PERIOD - # of ADC samples before trim PWM
*  adjustment.
*
*  This slows-down the trim process, such that it compensates initial and
*  long-term regulator drift and associated component drift.  This should be
*  long enough to avoid interacting with the regulator's high-speed transient
*  response to dynamic changes in Vin and Iout.
*
*  Units: ADC sample counts
*  (typically 1 to 3 mS per count, depends on ADC cycle scan rate and rail qty)
*******************************************************************************/
#define `$INSTANCE_NAME`_TRIM_SLOW_PERIOD               (20u)


/*******************************************************************************
*
* `$INSTANCE_NAME`_MIN_DELTA -
*  The minimum delta between difference in quantity of measurements that are
*  ABOVE and BELOW the ideal nominal rail voltage before decide to adjust the
*  PWM trim.
*
*  If a rail is noisy, the quantity of measurements ABOVE and BELOW each be
*  large, yet have a similar magnitude and neither will "dominate" (i.e. exceed
*  MIN_DELTA), so no adjustment would made.
*******************************************************************************/
/* A 25% (0.25) majority seems like a reasonable decisive majority  */
#define `$INSTANCE_NAME`_TRIM_MIN_DELTA_FACTOR         (0.25f)         /* Ratio (e.g. 0.25 is 25%)  */
#define `$INSTANCE_NAME`_MIN_DELTA                     ((uint8)(`$INSTANCE_NAME`_TRIM_MIN_DELTA_FACTOR * \
                                                        (float32)`$INSTANCE_NAME`_TRIM_SLOW_PERIOD))


/***************************************
*       Register Constants
***************************************/

/* Control Enable Register Bit Masks */
#define `$INSTANCE_NAME`_CTRL_ENABLE                (0x01u)
#define `$INSTANCE_NAME`_CTRL_ALERT                 (0x02u)

#endif  /* `$INSTANCE_NAME`_H */


/* [] END OF FILE */
