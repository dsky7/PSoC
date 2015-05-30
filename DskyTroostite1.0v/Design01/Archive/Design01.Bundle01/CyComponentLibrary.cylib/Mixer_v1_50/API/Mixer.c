/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the MIXER Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_MIN_VDDA)
    #include "`$INSTANCE_NAME`_bst_clk.h"
#endif /* `$INSTANCE_NAME`_MIN_VDDA */

/* Fixed configuration of SC Block only performed once */
uint8 `$INSTANCE_NAME`_initVar = 0u;


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
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 tempCR2 = 0u;

    /* Configure SC Block based on selected Mixer type */
    if (`$INSTANCE_NAME`_MIXER_TYPE == `$INSTANCE_NAME`_CTMIXER) /* Continuous Time (up) mixer */
    {
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_DIV2_DISABLE |
                                `$INSTANCE_NAME`_GAIN_0DB);                                 

        /* SC Block CR2 */
        tempCR2 = (`$INSTANCE_NAME`_BIAS_LOW |
                   `$INSTANCE_NAME`_REDC_01 |
                   `$INSTANCE_NAME`_GNDVREF_DI);

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer 
        */
        if (`$INSTANCE_NAME`_LO_FREQ_FLAG == `$INSTANCE_NAME`_LO_LT_100K)
        {
            tempCR2 |= `$INSTANCE_NAME`_R20_40B_40K; 
        }
        else
        {
            tempCR2 |= `$INSTANCE_NAME`_R20_40B_20K;
        }
        `$INSTANCE_NAME`_CR2_REG = tempCR2;
    }
    else
    {   /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_DIV2_ENABLE |
                                `$INSTANCE_NAME`_GAIN_0DB);

        /* SC Block CR2 */
        tempCR2 = (`$INSTANCE_NAME`_BIAS_LOW |`$INSTANCE_NAME`_GNDVREF_DI);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode
        */
        if (`$INSTANCE_NAME`_LO_FREQ_FLAG == `$INSTANCE_NAME`_LO_LT_100K)
        {
            tempCR2 |= (`$INSTANCE_NAME`_R20_40B_40K | `$INSTANCE_NAME`_RVAL_40K); 
        }
        else
        {
            tempCR2 |= (`$INSTANCE_NAME`_R20_40B_20K | `$INSTANCE_NAME`_RVAL_20K);
        }
        `$INSTANCE_NAME`_CR2_REG = tempCR2; 
    }/* end if - Mixer Type */

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
*  Enables the Mixer block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* Enable power to SC block in active mode */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;

    /* Enable SC Block boost clock control for low Vdda operation */
    #if(`$INSTANCE_NAME`_MIN_VDDA)
        `$INSTANCE_NAME`_BSTCLK_REG |= `$INSTANCE_NAME`_BST_CLK_EN;  /* enable for Vdda < 2.7V */
        `$INSTANCE_NAME`_bst_clk_Enable();
    #endif /* `$INSTANCE_NAME`_MIN_VDDA */

    /* PSoC3 ES2 or early, PSoC5 ES1 */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    /* PSoC3 ES3 or later, PSoC5 ES2 or later */
    #elif (`$INSTANCE_NAME`_PSOC3_ES3 || `$INSTANCE_NAME`_PSOC5_ES2)
        /* Enable charge Pump clock for SC block */
        `$INSTANCE_NAME`_PUMP_CR1_REG |= `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL;
        /* Enable Pump only if voltage is below threshold */
        if (`$INSTANCE_NAME`_CYDEV_VDDA_MV < `$INSTANCE_NAME`_VDDA_THRESHOLD_MV)
        {
            `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
        }
    #endif /* `$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the SC block control registers based on the
*  Mixer type selected and and enables power to the SC block
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Global variables:
*  `$INSTANCE_NAME`_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  `$INSTANCE_NAME`_initVar is used indicate that the static configuration has 
*  been completed.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) 
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
*  Disables power to SC block.
*
* Parameters:  
*  void 
*
* Return: 
*  void 
*
* Reentrant: 
*  Yes
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
    #if(`$INSTANCE_NAME`_MIN_VDDA)
        `$INSTANCE_NAME`_BSTCLK_REG &= ~`$INSTANCE_NAME`_BST_CLK_EN;
        `$INSTANCE_NAME`_bst_clk_Disable();
    #endif /* `$INSTANCE_NAME`_MIN_VDDA */   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Set the drive power of the MIXER
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

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = `$INSTANCE_NAME`_CR1_REG & ~`$INSTANCE_NAME`_DRIVE_MASK;
    tmpCR |= (power & `$INSTANCE_NAME`_DRIVE_MASK);
    `$INSTANCE_NAME`_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
