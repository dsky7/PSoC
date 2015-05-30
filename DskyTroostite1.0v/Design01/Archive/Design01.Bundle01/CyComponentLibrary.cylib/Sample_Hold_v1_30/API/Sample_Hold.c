/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SAMPLE/TRACK AND HOLD 
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

/* static `$INSTANCE_NAME`_backupStruct  `$INSTANCE_NAME`_backup; */
#if (CY_PSOC5A)
    static `$INSTANCE_NAME`_LOWPOWER_BACKUP_STRUCT  `$INSTANCE_NAME`_lowPowerBackup;
#endif /* CY_PSOC5A */

/* Variable to decide whether or not to restore the control registers
   in the Enable API. This is valid only for PSOC5A silicon */
#if (CY_PSOC5A)
    uint8 `$INSTANCE_NAME`_restoreReg = 0u;
#endif /* CY_PSOC5A */


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
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 tempCR2 = 0u;
    
    /* Configure SC Block based on selected Sample/Track type */
    if (`$INSTANCE_NAME`_SAMPLE_TRACK_MODE == `$INSTANCE_NAME`_SAMPLEANDHOLD) /* Sample and hold mode */
    {
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_SAMPLEANDHOLD;
        
        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_GAIN_0DB);
        if(`$INSTANCE_NAME`_SAMPLE_CLOCK_EDGE == `$INSTANCE_NAME`_EDGE_POSITIVENEGATIVE)
        {
            `$INSTANCE_NAME`_CR1_REG =  `$INSTANCE_NAME`_CR1_REG  | `$INSTANCE_NAME`_DIV2_DISABLE ;
        }
        else
        {
            `$INSTANCE_NAME`_CR1_REG =  `$INSTANCE_NAME`_CR1_REG  | `$INSTANCE_NAME`_DIV2_ENABLE ;
        }

        /* SC Block CR2 */
        tempCR2 = (`$INSTANCE_NAME`_BIAS_LOW |
                   `$INSTANCE_NAME`_REDC_00 );
                   
        if(`$INSTANCE_NAME`_VREF_TYPE == `$INSTANCE_NAME`_EXTERNAL)
        {
            tempCR2 = tempCR2 | `$INSTANCE_NAME`_GNDVREF_DI;
        }
        else
        {
            tempCR2 = tempCR2 | `$INSTANCE_NAME`_GNDVREF_E;
        }
        `$INSTANCE_NAME`_CR2_REG = tempCR2;
    }
    else
    {   /* Track and Hold Mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_TRACKANDHOLD; 
        
        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_DIV2_ENABLE |
                                `$INSTANCE_NAME`_GAIN_0DB);
                                
        /* SC Block CR2 */
        tempCR2 = (`$INSTANCE_NAME`_BIAS_LOW |
                   `$INSTANCE_NAME`_REDC_00 |
                   `$INSTANCE_NAME`_GNDVREF_E);
                   
        `$INSTANCE_NAME`_CR2_REG = tempCR2;
    }/* end if - Sample/Track Type */
    
    /* Enable SC Block clocking */
    `$INSTANCE_NAME`_CLK_REG |= `$INSTANCE_NAME`_CLK_EN;
    
    /* Set default power */
    `$INSTANCE_NAME`_SetPower(`$INSTANCE_NAME`_INIT_POWER);
}


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the Sample/Track and Hold block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* Enable power to SC block in active mode */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;
    
    /* Enable power to SC block in Alternative active mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;

    /* This is to restore the value of register CR1 and CR2 which is saved 
    in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(`$INSTANCE_NAME`_restoreReg == 1u)
        {
            `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_lowPowerBackup.CR1_REG;
            `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_lowPowerBackup.CR2_REG;

            /* Clear the flag */
            `$INSTANCE_NAME`_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable SC Block boost clock control for low Vdda operation */
    /* enable for Vdda < 2.7V */
    #if(`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        `$INSTANCE_NAME`_BSTCLK_REG |= `$INSTANCE_NAME`_BST_CLK_EN | CyScBoostClk__INDEX;
    #endif /* `$INSTANCE_NAME`_MIN_VDDA */
    
    /* PSoC5A */
    #if (CY_PSOC5A)
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    /* PSoC3, PSOC5LP or later */
    #elif (CY_PSOC3 || CY_PSOC5LP)
        /* Enable charge Pump clock for SC block */
        `$INSTANCE_NAME`_PUMP_CR1_REG |= `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL;
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Sample and Hold with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not Initialized then initialize all required hardware and software */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
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
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Disable pumps only if only one SC block is in use */
    if (`$INSTANCE_NAME`_PM_ACT_CFG_REG == `$INSTANCE_NAME`_ACT_PWR_EN)
    {
        `$INSTANCE_NAME`_SC_MISC_REG &= ~`$INSTANCE_NAME`_PUMP_FORCE;
    }
    
    /* Disble power to the Amp in Active mode template */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG &= ~`$INSTANCE_NAME`_ACT_PWR_EN;

    /* Disble power to the Amp in Alternative Active mode template */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= ~`$INSTANCE_NAME`_STBY_PWR_EN;
    
    /* Disable SC Block boost clk control, if used (MinVdda < 2.7V) */
    #if(`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV)
        `$INSTANCE_NAME`_BSTCLK_REG &= ~`$INSTANCE_NAME`_BST_CLK_EN;
    #endif /* `$INSTANCE_NAME`_MIN_VDDA */
 
    /* To save SC.CR1 and SC.CR2 registers and to zero out these regisers
       for PSoC5A */
    #if (CY_PSOC5A)
         /* Set the flag which decides whether or not to restore the
            CR1 and CR2 in Enable() API */
        `$INSTANCE_NAME`_restoreReg = 1u;

        /* Save the registers before clearing them */
        `$INSTANCE_NAME`_lowPowerBackup.CR1_REG = `$INSTANCE_NAME`_CR1_REG;
        `$INSTANCE_NAME`_lowPowerBackup.CR2_REG = `$INSTANCE_NAME`_CR2_REG;

        `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_REG_NULL;
        `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_REG_NULL;
    #endif /* CY_PSOC5A */

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the Sample/Track and Hold.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint8 power) `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */
    tmpCR = `$INSTANCE_NAME`_CR1_REG & ~`$INSTANCE_NAME`_DRIVE_MASK;
    tmpCR |= (power & `$INSTANCE_NAME`_DRIVE_MASK);
    `$INSTANCE_NAME`_CR1_REG = tmpCR;
}


/* [] END OF FILE */
