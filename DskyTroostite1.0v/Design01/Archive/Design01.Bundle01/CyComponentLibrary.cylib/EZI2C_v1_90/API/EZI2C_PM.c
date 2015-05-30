/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the API for the proper switching to/from the low power
*  modes.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

       
`$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup =
{
    /* enable state - disabled */
    `$INSTANCE_NAME`_DISABLED,

    /* xcfg: wakeup disabled, enabled hardware addr detection */
    `$INSTANCE_NAME`_XCFG_HDWR_ADDR_EN,

    /* addr: default address (0x04) */
    `$INSTANCE_NAME`_DEFAULT_ADDR1,

    /* cfg: default bus speed - 100kHz, so write 0 (16 samples/bit) */
    0x00u,

    /* clkDiv1 */
    LO8(BCLK__BUS_CLK__KHZ / `$INSTANCE_NAME`_BUS_SPEED),

    /* clkDiv2 */
    HI8(BCLK__BUS_CLK__KHZ / `$INSTANCE_NAME`_BUS_SPEED)
};

#if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
    volatile uint8 `$INSTANCE_NAME`_wakeupSource;
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
    

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the EZI2C component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup - the non retention registers are saved to.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{

    #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
        uint8 interruptState;
    #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

    `$INSTANCE_NAME`_backup.xcfg = `$INSTANCE_NAME`_XCFG_REG;
    `$INSTANCE_NAME`_backup.adr  = `$INSTANCE_NAME`_ADDR_REG;
    `$INSTANCE_NAME`_backup.cfg  = `$INSTANCE_NAME`_CFG_REG;
    `$INSTANCE_NAME`_backup.clkDiv1  = `$INSTANCE_NAME`_CLKDIV1_REG;
    `$INSTANCE_NAME`_backup.clkDiv2  = `$INSTANCE_NAME`_CLKDIV2_REG;

    #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
        /* Enable the I2C backup regulator  */
        interruptState = CyEnterCriticalSection();
        `$INSTANCE_NAME`_PWRSYS_CR1_REG |= `$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP;
        CyExitCriticalSection(interruptState);

        /* Set force nack before putting the device to power off mode.
        *  It is cleared on wake up.
        */
        `$INSTANCE_NAME`_XCFG_REG |= `$INSTANCE_NAME`_XCFG_FORCE_NACK;
        while(0u == (`$INSTANCE_NAME`_XCFG_REG & `$INSTANCE_NAME`_XCFG_SLEEP_READY))
        {
            /* Waits for ongoing transaction to be completed. */
        }
        
         /* Setup wakeup interrupt */
        `$INSTANCE_NAME`_DisableInt();
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_WAKEUP_ISR);
        `$INSTANCE_NAME`_wakeupSource = 0u; /* Clear wakeup event */
        `$INSTANCE_NAME`_EnableInt();

        /* Leave interrupt enabled to wake up */
            
    #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the previously saved by `$INSTANCE_NAME`_SaveConfig() or 
*  `$INSTANCE_NAME`_Sleep() configuration of the EZI2C component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup - the non retention registers are restored from.
*
* Reentrant:
*  No
*
* Side Effects:
*  Calling this function before `$INSTANCE_NAME`_SaveConfig() or
*  `$INSTANCE_NAME`_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    uint8 enableInterrupts;

    /* Enabled if was in Sleep */
    if(0u != (`$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP & `$INSTANCE_NAME`_PWRSYS_CR1_REG))    
    {
        /* Disable back-up regulator */
        enableInterrupts = CyEnterCriticalSection();
        /* Disable the I2C regulator backup */
        `$INSTANCE_NAME`_PWRSYS_CR1_REG &= ((uint8) ~`$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP);
        CyExitCriticalSection(enableInterrupts);
        
        /* Re-enable Master */
        `$INSTANCE_NAME`_CFG_REG = `$INSTANCE_NAME`_backup.cfg;
    }
    else /* The I2C_REG_BACKUP was cleaned by PM API: it means Hibernate or wake-up not set */
    {
        #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
           /* Disable power to I2C block before register restore */
            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_PM_ACT_CFG_REG  &= ((uint8) ~`$INSTANCE_NAME`_ACT_PWR_EN);
            `$INSTANCE_NAME`_PM_STBY_CFG_REG &= ((uint8) ~`$INSTANCE_NAME`_STBY_PWR_EN);
            CyExitCriticalSection(enableInterrupts);

            /* Enable component after restore complete */
            `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
        #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

        /* Restore component registers: Hibernate disable power */
        `$INSTANCE_NAME`_CFG_REG = `$INSTANCE_NAME`_backup.cfg;    
        `$INSTANCE_NAME`_XCFG_REG = `$INSTANCE_NAME`_backup.xcfg;
        `$INSTANCE_NAME`_ADDR_REG = `$INSTANCE_NAME`_backup.adr;
        `$INSTANCE_NAME`_CLKDIV1_REG = `$INSTANCE_NAME`_backup.clkDiv1;
        `$INSTANCE_NAME`_CLKDIV2_REG = `$INSTANCE_NAME`_backup.clkDiv2;
    }

    #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
        /* Trigger I2C interrupt if wakeup interrupt was triggered before */
        `$INSTANCE_NAME`_DisableInt();
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);
        if(0u != `$INSTANCE_NAME`_wakeupSource)
        {
            (void) CyIntSetPending(`$INSTANCE_NAME`_ISR_NUMBER); /* Generate interrupt to release I2C bus */
        }
        `$INSTANCE_NAME`_EnableInt();
    #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Saves component enable state and configuration. Stops component operation.
*  Should be called just prior to entering sleep. If "Enable wakeup from the
*  Sleep mode" is properly configured and enabled, this function should not be
*  called.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup - the non retention registers are saved to. Changed
*  by `$INSTANCE_NAME`_SaveConfig() function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    
    #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
        /* The I2C block should be always enabled if used as wakeup source */
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
    #else
        
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_PM_ACT_CFG_REG, `$INSTANCE_NAME`_ACT_PWR_EN);

        if(`$INSTANCE_NAME`_IS_BIT_SET(`$INSTANCE_NAME`_PM_ACT_CFG_REG, `$INSTANCE_NAME`_ACT_PWR_EN))
        {
            
            `$INSTANCE_NAME`_Stop();
        }
    #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

    /* Save registers configuration */
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores component enable state and configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_backup - the non retention registers are restored from.
*
* Reentrant:
*  No
*
* Side Effects:
*  Calling this function before `$INSTANCE_NAME`_SaveConfig() or
*  `$INSTANCE_NAME`_Sleep() will lead to unpredictable results.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Restore registers values */
    `$INSTANCE_NAME`_RestoreConfig();
    
    if(`$INSTANCE_NAME`_DISABLED != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Enable component's operation */
        `$INSTANCE_NAME`_Enable();

    } /* Do nothing if component's block was disabled before */
}


/***************************************
*       Obsolete
***************************************/

/* Following APIs are OBSOLETE and must not be used */

#if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_ONE_ADDRESS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SlaveSetSleepMode
    ********************************************************************************
    *
    * Summary:
    *  Disables the run time I2C regulator and enables the sleep Slave I2C.
    *  Should be called just prior to entering sleep. This function is only
    *  provided if a single I2C address is used.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The I2C interrupt will be disabled if Wake up from Sleep mode option is
    *  enabled.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SlaveSetSleepMode(void) `=ReentrantKeil($INSTANCE_NAME . "_SlaveSetSleepMode")`
    {
        #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
            uint8 interruptState;

            /* Enable the I2C backup regulator  */
            interruptState = CyEnterCriticalSection();
            `$INSTANCE_NAME`_PWRSYS_CR1_REG |= `$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP;
            CyExitCriticalSection(interruptState);

            /* Set force nack before putting the device to power off mode.
            *  It is cleared on wake up.
            */
            `$INSTANCE_NAME`_XCFG_REG |= `$INSTANCE_NAME`_XCFG_FORCE_NACK;
            while(0u == (`$INSTANCE_NAME`_XCFG_REG & `$INSTANCE_NAME`_XCFG_SLEEP_READY))
            {
                /* Waits for ongoing transaction to be completed. */
            }
            
             /* Setup wakeup interrupt */
            `$INSTANCE_NAME`_DisableInt();
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_WAKEUP_ISR);
            `$INSTANCE_NAME`_wakeupSource = 0u; /* Clear wakeup event */
            `$INSTANCE_NAME`_EnableInt();

            /* Leave interrupt enabled to wake up */
            
        #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SlaveSetWakeMode
    ********************************************************************************
    *
    * Summary:
    *  Disables the sleep EzI2C slave and re-enables the run time I2C.  Should be
    *  called just after awaking from sleep.  Must preserve address to continue.
    *  This function is only provided if a single I2C address is used.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The I2C interrupt will be enabled if Wake up from Sleep mode option is
    *  enabled.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SlaveSetWakeMode(void) `=ReentrantKeil($INSTANCE_NAME . "_SlaveSetWakeMode")`
    {
        #if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
            uint8 interruptState;

            interruptState = CyEnterCriticalSection();
            /* Disable the I2C regulator backup */
            `$INSTANCE_NAME`_PWRSYS_CR1_REG &= ((uint8) ~`$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP);
            CyExitCriticalSection(interruptState);

            /* Trigger I2C interrupt if wakeup interrupt was triggered before */
            `$INSTANCE_NAME`_DisableInt();
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);
            if(0u != `$INSTANCE_NAME`_wakeupSource)
            {
                (void) CyIntSetPending(`$INSTANCE_NAME`_ISR_NUMBER); /* Generate interrupt to release I2C bus */
            }
            `$INSTANCE_NAME`_EnableInt();

        #endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */
    }

#endif /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_ONE_ADDRESS) */

/* [] END OF FILE */
