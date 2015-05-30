/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the inverting PGA 
*  Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
    #include "`$INSTANCE_NAME`_ScBoostClk.h"
#endif /* `$INSTANCE_NAME`_ACLK_ENABLE */

#ifndef CY_PSOC3
#error Component `$CY_COMPONENT_NAME` requires cy_boot v2.30 or later
#endif /* CY_PSOC3 */

/* Constant array for gain settings */
const uint8 `$INSTANCE_NAME`_GainArray[9] = { 
    (`$INSTANCE_NAME`_PGA_INV_GAIN_01 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-1  */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_03 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-3  */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_07 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-7  */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_15 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-15 */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_22 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-22 */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_24 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-24 */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_31 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-31 */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_47 | `$INSTANCE_NAME`_BIAS_LOW), /* G=-47 */
    (`$INSTANCE_NAME`_PGA_INV_GAIN_49 | `$INSTANCE_NAME`_BIAS_LOW)  /* G=-49 */
};

/* Constant array for gain compenstion settings */
const uint8 `$INSTANCE_NAME`_GainComp[9] = { 
    ( `$INSTANCE_NAME`_COMP_4P35PF  | ( `$INSTANCE_NAME`_REDC_00 >> 2 )), /* G=-1  */
    ( `$INSTANCE_NAME`_COMP_4P35PF  | ( `$INSTANCE_NAME`_REDC_01 >> 2 )), /* G=-3  */
    ( `$INSTANCE_NAME`_COMP_3P0PF   | ( `$INSTANCE_NAME`_REDC_01 >> 2 )), /* G=-7  */
    ( `$INSTANCE_NAME`_COMP_3P0PF   | ( `$INSTANCE_NAME`_REDC_01 >> 2 )), /* G=-15 */
    ( `$INSTANCE_NAME`_COMP_3P6PF   | ( `$INSTANCE_NAME`_REDC_01 >> 2 )), /* G=-22 */
    ( `$INSTANCE_NAME`_COMP_3P0PF   | ( `$INSTANCE_NAME`_REDC_10 >> 2 )), /* G=-24 */
    ( `$INSTANCE_NAME`_COMP_3P6PF   | ( `$INSTANCE_NAME`_REDC_11 >> 2 )), /* G=-31 */
    ( `$INSTANCE_NAME`_COMP_3P6PF   | ( `$INSTANCE_NAME`_REDC_00 >> 2 )), /* G=-47 */
    ( `$INSTANCE_NAME`_COMP_3P6PF   | ( `$INSTANCE_NAME`_REDC_00 >> 2 ))  /* G=-49 */
};

uint8 `$INSTANCE_NAME`_initVar = 0u;

#if (CY_PSOC5_ES1)
uint8 `$INSTANCE_NAME`_restoreVal = 0u;
#endif /* (CY_PSOC5_ES1) */

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;


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
*  void
*
* Return:
*  void
*
* Reentrant:
*  No
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* Set PGA mode */
    `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_PGA;  

    /* Set inverting PGA mode  and reference mode */
    `$INSTANCE_NAME`_CR1_REG &= ~`$INSTANCE_NAME`_PGA_INV;  

    /* Set gain and compensation */
    `$INSTANCE_NAME`_SetGain(`$INSTANCE_NAME`_DEFAULT_GAIN);

    /* Set power */
    `$INSTANCE_NAME`_SetPower(`$INSTANCE_NAME`_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the inverting PGA block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
* Reentrant:
*  No
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* If a boost clock is required  */
    #if(`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        `$INSTANCE_NAME`_ACLK_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACLK_ACT_PWR_EN;
        `$INSTANCE_NAME`_ACLK_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_ACLK_STBY_PWR_EN;
        `$INSTANCE_NAME`_ScBoostClk_Enable();  /* turn on boost pump */
        `$INSTANCE_NAME`_BST_REG |= 0x08;
    #endif /* `$INSTANCE_NAME`_ACLK_ENABLE */
    
    /* PSoC3 ES2 or early, PSoC5 ES1 */
    #if (CY_PSOC3_ES2 || CY_PSOC5_ES1)
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    /* PSoC3 ES3 or later, PSoC5 ES2 or later */
    #elif (CY_PSOC3_ES3 || CY_PSOC5_ES2)
        /* Enable charge Pump clock for SC block */
        `$INSTANCE_NAME`_PUMP_CR1_REG |= `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL;
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    #endif /* `$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1 */

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */
    #if (CY_PSOC5_ES1)
    if(`$INSTANCE_NAME`_restoreVal == 1u)
    {
        `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_backup.scCr1Reg;
        `$INSTANCE_NAME`_CR2_REG =`$INSTANCE_NAME`_backup.scCr2Reg;
        `$INSTANCE_NAME`_restoreVal = 0u;
    }
    #endif /* CY_PSOC5_ES1 */

    /* Enable power to the Amp in Active mode */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative active mode  */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the inverting PGA with the default values,
*  and sets  the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Theory:
*  This function modifies the global variable `$INSTANCE_NAME`_initVar: which 
*  defines where component's configuration are taken from the customizer 
*  (equals 0) or parameters changed by API will be used instead (equals 1).
*
* Reentrant: 
*  No
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
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Disble power to the Amp in Active mode*/
    `$INSTANCE_NAME`_PM_ACT_CFG_REG &= ~`$INSTANCE_NAME`_ACT_PWR_EN;

    /* Disble power to the Amp in Alternative active mode*/
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= ~`$INSTANCE_NAME`_STBY_PWR_EN;

    /* If a boost clock is required  */
    /* Disable and power down boost clock */
    #if(`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        `$INSTANCE_NAME`_ACLK_PM_ACT_CFG_REG &= ~`$INSTANCE_NAME`_ACLK_ACT_PWR_EN;
        `$INSTANCE_NAME`_ACLK_PM_STBY_CFG_REG &= ~`$INSTANCE_NAME`_ACLK_STBY_PWR_EN;
        `$INSTANCE_NAME`_ScBoostClk_Disable();  
    #endif /* `$INSTANCE_NAME`_ACLK_ENABLE */
    
    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5_ES1)
        `$INSTANCE_NAME`_backup.scCr1Reg = `$INSTANCE_NAME`_CR1_REG;
        `$INSTANCE_NAME`_backup.scCr2Reg = `$INSTANCE_NAME`_CR2_REG;
        `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_SC_REG_CLR;
        `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_SC_REG_CLR;
        `$INSTANCE_NAME`_restoreVal = 1u;
    #endif /* CY_PSOC5_ES1 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the inverting PGA
*
* Parameters:  
*  power:  Sets power level between (0) and (3) high power
*
* Return: 
*  void 
*
* Reentrant: 
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint8 power) `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`
{
    uint8 tmpCR;

    tmpCR = `$INSTANCE_NAME`_CR1_REG & ~`$INSTANCE_NAME`_DRIVE_MASK;
    tmpCR |= (power & `$INSTANCE_NAME`_DRIVE_MASK);
    `$INSTANCE_NAME`_CR1_REG = tmpCR;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
********************************************************************************
*
* Summary:
*  This function sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* Parameters:  
*  gain:  Sets gain of amplifier.     
*
* Return: 
*  void
*
* Reentrant: 
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(uint8 gain) `=ReentrantKeil($INSTANCE_NAME . "_SetGain")`
{
    /* Only set new gain if it is a valid gain */
    if( gain <= `$INSTANCE_NAME`_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        `$INSTANCE_NAME`_CR2_REG &= ~(`$INSTANCE_NAME`_RVAL_MASK | `$INSTANCE_NAME`_R20_40B_MASK | 
                                `$INSTANCE_NAME`_REDC_MASK | `$INSTANCE_NAME`_BIAS_MASK );

        /* Set gain value resistors, redc comp, and bias */
        `$INSTANCE_NAME`_CR2_REG |= (`$INSTANCE_NAME`_GainArray[gain] |
                                ( (`$INSTANCE_NAME`_GainComp[gain] << 2 ) & `$INSTANCE_NAME`_REDC_MASK) );

        /* Clear sc_comp  */
        `$INSTANCE_NAME`_CR1_REG &= ~`$INSTANCE_NAME`_COMP_MASK;

        /* Set sc_comp  */
        `$INSTANCE_NAME`_CR1_REG |= ( `$INSTANCE_NAME`_GainComp[gain] | `$INSTANCE_NAME`_COMP_MASK );
    }
}

/* [] END OF FILE */
