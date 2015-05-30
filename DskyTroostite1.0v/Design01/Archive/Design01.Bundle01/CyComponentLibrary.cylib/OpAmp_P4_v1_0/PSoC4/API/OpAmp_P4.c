/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include <CyLib.h>

uint32 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  `$INSTANCE_NAME`_Start().
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
    /* Enable STB */
    `$INSTANCE_NAME`_OA_CTRL |= ((uint32)1u << `$INSTANCE_NAME`_OA_CTB_EN_SHIFT);
    `$INSTANCE_NAME`_OA_RES_CTRL = 0u;
    `$INSTANCE_NAME`_OA_COMP_TRIM_REG = `$INSTANCE_NAME`_OA_COMP_TRIM_VALUE;
    #if(0u != `$INSTANCE_NAME`_OUTPUT_CURRENT)
        /* 10 mA current */
        `$INSTANCE_NAME`_OA_RES_CTRL |= `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X;
    #endif /* 0u != `$INSTANCE_NAME`_OUTPUT_CURRENT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
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
    `$INSTANCE_NAME`_OA_RES_CTRL &= (~(uint32)`$INSTANCE_NAME`_OA_PWR_MODE_MASK);
    `$INSTANCE_NAME`_OA_RES_CTRL |= `$INSTANCE_NAME`_POWER | ((uint32)1u << `$INSTANCE_NAME`_OA_PUMP_CTRL_SHIFT);
}


/*******************************************************************************
* Function Name:   `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and
*  sets the power to the given level. A power level of 0, is same as
*  executing the stop function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
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
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_OA_RES_CTRL &= (~(uint32)(`$INSTANCE_NAME`_OA_PWR_MODE_MASK |
        ((uint32)1u << `$INSTANCE_NAME`_OA_PUMP_CTRL_SHIFT)));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters:
*  power: Sets power level between low (1) and high power (3).
*
* Return:
*  None
*
**********************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint32 power)
{
    `$INSTANCE_NAME`_OA_RES_CTRL &= (~(uint32)`$INSTANCE_NAME`_OA_PWR_MODE_MASK);
    `$INSTANCE_NAME`_OA_RES_CTRL |= (power & `$INSTANCE_NAME`_OA_PWR_MODE_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PumpControl
********************************************************************************
*
* Summary:
*  Turns the boost pump on or off.
*
* Parameters:
*  onOff: `$INSTANCE_NAME`_PUMPON, `$INSTANCE_NAME`_PUMPOFF.
*
* Return:
*  None
*
**********************************************************************************/
void `$INSTANCE_NAME`_PumpControl(uint32 onOff)
{
    `$INSTANCE_NAME`_OA_RES_CTRL &= (~(uint32)`$INSTANCE_NAME`_OA_PUMP_EN_MASK);
    `$INSTANCE_NAME`_OA_RES_CTRL |= ((onOff & `$INSTANCE_NAME`_PUMP_PROTECT_MASK)
        << `$INSTANCE_NAME`_OA_PUMP_CTRL_SHIFT);
}


/* [] END OF FILE */
