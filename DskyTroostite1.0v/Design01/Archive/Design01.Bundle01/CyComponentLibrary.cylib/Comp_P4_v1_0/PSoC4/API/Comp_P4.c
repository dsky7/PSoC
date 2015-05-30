/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Comparator component
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


uint32 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
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
    /* Enable comparator block */
    `$INSTANCE_NAME`_CTB_CTRL_REG = ((uint32)1u << `$INSTANCE_NAME`_OA_CTB_EN_SHIFT);
    
    `$INSTANCE_NAME`_OA_CTRL_REG  = ((uint32)1u << `$INSTANCE_NAME`_OA_COMP_EN_SHIFT) | 
        ((uint32)1u << `$INSTANCE_NAME`_OA_BYPASS_SHIFT);

    /* Set selected Hysteresis option */
    #if(0 != `$INSTANCE_NAME`_HYSTERESIS)
        `$INSTANCE_NAME`_OA_CTRL_REG |= ((uint32) 1u << `$INSTANCE_NAME`_OA_HYST_EN_SHIFT);
    #endif /* 0 != `$INSTANCE_NAME`_HYSTERESIS */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enable the Comparator
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
    `$INSTANCE_NAME`_OA_CTRL_REG &= (~(uint32)(`$INSTANCE_NAME`_OA_PWR_MODE_HIGH));
    `$INSTANCE_NAME`_OA_CTRL_REG |= `$INSTANCE_NAME`_POWER | ((uint32) 1u << `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Comparator with the default values.
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
    `$INSTANCE_NAME`_OA_CTRL_REG &= (~(uint32)(`$INSTANCE_NAME`_OA_PWR_MODE_HIGH | 
        ((uint32) 1u << `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT)));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  This function sets the speed of the Analog Comparator. The faster the speed
*  the more power that is used.
*
* Parameters:
*  speed: (uint32) Sets operation mode of Comparator
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint32 speed)
{
    `$INSTANCE_NAME`_OA_CTRL_REG &= (~(uint32)`$INSTANCE_NAME`_OA_PWR_MODE_MASK);
    `$INSTANCE_NAME`_OA_CTRL_REG |= (speed & `$INSTANCE_NAME`_OA_PWR_MODE_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ZeroCal
********************************************************************************
*
* Summary:
*  This function calibrates the offset of the Analog Comparator.
*  Before calling this API Vplus input of the component should be disconnected
*  from source and connected to Vminus terminal of the component.
*  Use analog multiplexer component for it.
*
* Parameters:
*  None
*
* Return:
*  (uint32)  value written in trim register when calibration complete.
*
*
* Side Effects:
*  Routine clears analog routing associated with the comparator positive input.
*  This may affect routing of signals from other components that are connected
*  to the positive input of the comparator.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;
    
    /* Clear trim registers before trimming */
    `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG       = 0u;
    `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG = 0u;
    
    /* Checking the comparator's output state */
    cmpOut = `$INSTANCE_NAME`_GetCompare();
    
    /* 
     Connect the outputs of trim IDACs to the positive
     output leg of the folded cascode 
     */
    if(cmpOut == 0u)
    {
        `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG       = ((uint32) 1u << (uint32)`$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT);
        `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG = ((uint32) 1u << (uint32)`$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT);
    }
    else
    {
        /* 
        Do nothing. Outputs of trim IDACs are connected 
        to the negative output leg of the folded cascode 
         */
    }
    
    /* 
     Searching the offset trim setting, 
     that flips the output of the comparator 
     */
    for(i = 0u; i < `$INSTANCE_NAME`_COMP_TRIM_MAX_VALUE; i++)
    {
        `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG++;
        CyDelayUs(10u);
        if(cmpOut != `$INSTANCE_NAME`_GetCompare())
        {
            break;
        }
    }
    
    /* return offset trim value */
    return (`$INSTANCE_NAME`_OA_OFFSET_TRIM_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadTrim
********************************************************************************
*
* Summary:
*  This function stores a value in the Analog Comparator trim register.
*
* Parameters:
*  uint32 trimVal - trim value.  This value is the same format as the value
*  returned by the _ZeroCal routine.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadTrim(uint32 trimVal)
{
    `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG = trimVal;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  This function returns the comparator output value.
*
* Parameters:
*   None
*
* Return:
*  (uint32)  0  if Pos_Input less than Neg_input
*            1  if Pos_Input greater than Neg_input.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return ((uint32)(`$INSTANCE_NAME`_OA_COMPSTAT_REG >> `$INSTANCE_NAME`_OA_COMPSHIFT) & 1u);
}

/* [] END OF FILE */
