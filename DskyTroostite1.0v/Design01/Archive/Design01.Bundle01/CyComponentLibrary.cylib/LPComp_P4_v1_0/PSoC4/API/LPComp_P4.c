/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Low Power Comparator
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"

uint32 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the component is
*  initialized to the configuration from the customizer. When called to restart
*  the comparator following a `$INSTANCE_NAME`_Stop() call, the current
*  component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_initVar = 1u;
        `$INSTANCE_NAME`_Init();
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer settings.
*  It is not necessary to call LPComp_Init() because the
*  `$INSTANCE_NAME`_Start() API calls this function and is the preferred method
*  to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32 config;
    uint8 enableInterrupts;
    
    `$INSTANCE_NAME`_DFT_REG = 0u;
    
    enableInterrupts = CyEnterCriticalSection();
    config = ((`$INSTANCE_NAME`_CONFIG_REG & ((uint32)~((uint32)`$INSTANCE_NAME`_CONFIG_MASK <<
              `$INSTANCE_NAME`_CONFIG_REG_SHIFT))) | ((uint32)`$INSTANCE_NAME`_CONFIG_DEFAULT <<
              `$INSTANCE_NAME`_CONFIG_REG_SHIFT));
    `$INSTANCE_NAME`_CONFIG_REG = config;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call `$INSTANCE_NAME`_Enable() because the `$INSTANCE_NAME`_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_EN;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Turns off the LP Comparator.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  The function doesn't change component power settings.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_EN;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the drive power and speed to one of three settings.
*
* Parameters:
*  uint32 speed: Sets operation mode of the component:
*   `$INSTANCE_NAME`_SPEED_LOW      - Slow speed / Ultra low power
*   `$INSTANCE_NAME`_SPEED_MEDIUM   - Medium speed / Medium power
*   `$INSTANCE_NAME`_SPEED_HIGH     - High speed / High power
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint32 speed)
{
    uint32 config;
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    config = ((`$INSTANCE_NAME`_CONFIG_REG & (~(uint32)`$INSTANCE_NAME`_CONFIG_SPEED_MODE_MASK)) |
              ((uint32)((speed & `$INSTANCE_NAME`_SPEED_PARAM_MASK) << `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT) << \
              `$INSTANCE_NAME`_CONFIG_REG_SHIFT));
    `$INSTANCE_NAME`_CONFIG_REG = config;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt edge detect mode. This also controls the value provided
*  on the output.
*
* Parameters:
*  uint32 mode: Enumerated edge detect mode value:
*  `$INSTANCE_NAME`_INTR_DISABLE - Disable
*  `$INSTANCE_NAME`_INTR_RISING  - Rising edge detect
*  `$INSTANCE_NAME`_INTR_FALLING - Falling edge detect
*  `$INSTANCE_NAME`_INTR_BOTH    - Detect both edges
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint32 mode)
{
    uint32 config;
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    config = ((`$INSTANCE_NAME`_CONFIG_REG & (~(uint32)`$INSTANCE_NAME`_CONFIG_INTR_MASK)) | \
              ((uint32)((uint32)((mode & `$INSTANCE_NAME`_INTR_PARAM_MASK) << `$INSTANCE_NAME`_CONFIG_INTR_SHIFT) << \
                `$INSTANCE_NAME`_CONFIG_REG_SHIFT)));
    `$INSTANCE_NAME`_CONFIG_REG = config;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests. This function is for use when using the combined
*  interrupt signal from the global signal reference. This function from either
*  component instance can be used to determine the interrupt source for both the
*  interrupts combined.
*
* Parameters:
*  None
*
* Return:
*  uint32: Interrupt source. Each component instance has a mask value:
*  `$INSTANCE_NAME`_INTR.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptSource(void)
{
    return (`$INSTANCE_NAME`_INTR_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to clear either or both
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to clear. Each component instance
*  has a mask value: `$INSTANCE_NAME`_INTR.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTR_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to trigger either or both software
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to set. Each component instance has
*  a mask value: `$INSTANCE_NAME`_INTR.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTR_SET_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHysteresis
********************************************************************************
*
* Summary:
*  Enables or disables the hysteresis.
*
* Parameters:
*  hysteresis: (uint32) Enables or disables the hysteresis setting.
*  `$INSTANCE_NAME`_HYST_ENABLE     - Enable hysteresis
*  `$INSTANCE_NAME`_HYST_DISABLE    - Disable hysteresis
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    if(hysteresis == `$INSTANCE_NAME`_HYST_ENABLE)
    {
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_HYST;
    }
    else
    {
        `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_HYST;
    }
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFilter
********************************************************************************
*
* Summary:
*  Enables or disables the digital filter.
*
* Parameters:
*  uint32 filter: filter enable.
*  `$INSTANCE_NAME`_FILT_ENABLE  - Enable filter
*  `$INSTANCE_NAME`_FILT_DISABLE - Disable filter
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFilter(uint32 filter)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    if(filter == `$INSTANCE_NAME`_FILT_ENABLE)
    {
        `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_FILT;
    }
    else
    {
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_FILT;
    }
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a nonzero value when the voltage connected to the
*  positive input is greater than the negative input voltage.
*
* Parameters:
*  None
*
* Return:
*  (uint32) Comparator output state. This value is not impacted by the interrupt
*  edge detect setting:
*   0 - if positive input is less than negative one.
*   1 - if positive input greater than negative one.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return((uint32)((0u == (`$INSTANCE_NAME`_CONFIG_REG & `$INSTANCE_NAME`_CONFIG_OUT)) ? 0u : 1u));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ZeroCal
********************************************************************************
*
* Summary:
*  Performs custom calibration of the input offset to minimize error for a
*  specific set of conditions: comparator reference voltage, supply voltage,
*  and operating temperature. A reference voltage in the range at which the
*  comparator will be used must be applied to one of the inputs. The two inputs
*  will be shorted internally to perform the offset calibration.
*
* Parameters:
*  None
*
* Return:
*  The value from the comparator trim register after the offset calibration is
*  complete. This value has the same format as the input parameter for the
*  `$INSTANCE_NAME`_LoadTrim() API routine.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;

    `$INSTANCE_NAME`_DFT_REG |= `$INSTANCE_NAME`_DFT_CAL_EN;
    `$INSTANCE_NAME`_TRIMA_REG = 0u;
    `$INSTANCE_NAME`_TRIMB_REG = 0u;

    CyDelayUs(1u);

    cmpOut = `$INSTANCE_NAME`_GetCompare();

    if(cmpOut == 1u)
    {
        `$INSTANCE_NAME`_TRIMA_REG = ((uint32) 0x01u << `$INSTANCE_NAME`_TRIMA_SIGNBIT);
    }

    for(i = 0u; i <= `$INSTANCE_NAME`_TRIMA_MAX_VALUE; i++)
    {
        `$INSTANCE_NAME`_TRIMA_REG++;

        CyDelayUs(1u);

        if(cmpOut != `$INSTANCE_NAME`_GetCompare())
        {
            break;
        }
    }

    if(((uint32)(`$INSTANCE_NAME`_CONFIG_REG >> `$INSTANCE_NAME`_CONFIG_REG_SHIFT) &
        `$INSTANCE_NAME`_SPEED_PARAM_MASK) == `$INSTANCE_NAME`_MEDSPEED)
    {
        cmpOut = `$INSTANCE_NAME`_GetCompare();

        if(cmpOut == 0u)
        {
            `$INSTANCE_NAME`_TRIMB_REG = ((uint32)1u << `$INSTANCE_NAME`_TRIMB_SIGNBIT);
        }

        for(i = 0u; i <= `$INSTANCE_NAME`_TRIMB_MAX_VALUE; i++)
        {
            `$INSTANCE_NAME`_TRIMB_REG++;

            CyDelayUs(1u);

            if(cmpOut != `$INSTANCE_NAME`_GetCompare())
            {
                break;
            }
        }
    }

    `$INSTANCE_NAME`_DFT_REG &= ((uint32)~`$INSTANCE_NAME`_DFT_CAL_EN);

    return (`$INSTANCE_NAME`_TRIMA_REG | ((uint32)`$INSTANCE_NAME`_TRIMB_REG << `$INSTANCE_NAME`_TRIMB_SHIFT));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadTrim
********************************************************************************
*
* Summary:
*  This function writes a value into the comparator offset trim register.
*
* Parameters:
*  trimVal: Value to be stored in the comparator offset trim register. This
*  value has the same format as the parameter returned by the
*  `$INSTANCE_NAME`_ZeroCal() API routine.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadTrim(uint32 trimVal)
{
    `$INSTANCE_NAME`_TRIMA_REG = (trimVal & `$INSTANCE_NAME`_TRIMA_MASK);
    `$INSTANCE_NAME`_TRIMB_REG = ((trimVal >> `$INSTANCE_NAME`_TRIMB_SHIFT) & `$INSTANCE_NAME`_TRIMB_MASK);
}


/* [] END OF FILE */
