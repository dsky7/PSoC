/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TMOUT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of APIs for the tiemout feature of
* I2C component.
*
* Note:
*
*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutInit
********************************************************************************
*
* Summary:
*  Initialize timout timer hardware.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutInit(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutInit")`
{
    #if(`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)

        uint8 enableInterrupts;

        /* Setup `$INSTANCE_NAME`_TMOUT_ISR */
        CyIntDisable    (`$INSTANCE_NAME`_TMOUT_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER, `$INSTANCE_NAME`_TMOUT_ISR_PRIORITY);
        #if(`$INSTANCE_NAME`_INTERN_TMOUT_INTR_HANDLER)
            (void) CyIntSetVector(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER, &`$INSTANCE_NAME`_TMOUT_ISR);
        #endif /* (`$INSTANCE_NAME`_INTERN_TMOUT_INTR_HANDLER) */

        `$INSTANCE_NAME`_TimeoutSetIntrMode(`$INSTANCE_NAME`_DEFAULT_TMOUT_INTR_MASK);

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_TMOUT_INTR_ENABLE_REG |= `$INSTANCE_NAME`_TMOUT_ENABLE_INTR; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SCL_ADDER_REG = `$INSTANCE_NAME`_DEFAULT_TMOUT_ADDER; /* d0 */

            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TMOUT_SCL_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_FIFO_SINGLE_REG;  /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */


        #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SDA_ADDER_REG = `$INSTANCE_NAME`_DEFAULT_TMOUT_ADDER;

            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TMOUT_SDA_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_FIFO_SINGLE_REG; /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);
        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED) */


        #if(`$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED)
            `$INSTANCE_NAME`_TimeoutSetPrescalerPeriod(`$INSTANCE_NAME`_DEFAULT_TMOUT_PRESCALER_PRD);

            enableInterrupts = CyEnterCriticalSection();
            #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
                `$INSTANCE_NAME`_SCL_PRESCALER_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_PRESCALER_CNT7_EN; /* aux_ctl */
            #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

            #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
                `$INSTANCE_NAME`_SDA_PRESCALER_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_PRESCALER_CNT7_EN; /* aux_ctl */
            #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED) */
            CyExitCriticalSection(enableInterrupts);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED)  */
    #endif     /* (`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)        */

    /* Set default parameters */
    `$INSTANCE_NAME`_TimeoutSetPeriod(`$INSTANCE_NAME`_DEFAULT_TMOUT_PERIOD);
    `$INSTANCE_NAME`_TimeoutSetIntrMode(`$INSTANCE_NAME`_DEFAULT_TMOUT_INTR_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutEnable
********************************************************************************
*
* Summary:
*  Enable temiout interrrupt and timer. The timeout timer starts opearation
*  depends on bus event.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutEnable")`
{
    #if(`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)
        `$INSTANCE_NAME`_TMOUT_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_CTRL_ENABLE;
    #endif /* (`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED) */

    `$INSTANCE_NAME`_TimeoutEnableInt();    /* Enable interrupt on Timeout event */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutStop
********************************************************************************
*
* Summary:
*   Disable timout timer hardware. Disable interrupt and clear pending if exist.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutStop(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutStop")`
{
    `$INSTANCE_NAME`_TimeoutDisableInt();
    `$INSTANCE_NAME`_TimeoutClearPendingInt();

    /* Re-arm timeout */
    #if(`$INSTANCE_NAME`_TIMEOUT_FF_ENABLED)
        `$INSTANCE_NAME`_TimeoutClearStatus(`$INSTANCE_NAME`_TMOUT_SR_PINS_TMOUT_MASK);
    #else
        `$INSTANCE_NAME`_TMOUT_CTRL_REG &= ((uint8) ~`$INSTANCE_NAME`_TMOUT_CTRL_ENABLE);
    #endif /* (`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutSetPeriod
********************************************************************************
*
* Summary:
*  Sets period of scl and sda timeout counters.
*
* Parameters:
*  period : period of scl and sda timeout. This number depends on bus_clk for
*           FF implementation on PSOC5LP and on input clock (16*DataRate) for
*           UDB impementation.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutSetPeriod(uint16 period) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutSetPeriod")`
{
    #if(`$INSTANCE_NAME`_TIMEOUT_FF_ENABLED)
        `$INSTANCE_NAME`_TMOUT_CFG0_REG = LO8(period);
        `$INSTANCE_NAME`_TMOUT_CFG1_REG = HI8(period);

    #else

        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SCL_PRD0_REG = LO8(period);
            `$INSTANCE_NAME`_TMOUT_SCL_PRD1_REG = HI8(period);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

        #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SDA_PRD0_REG = LO8(period);
            `$INSTANCE_NAME`_TMOUT_SDA_PRD1_REG = HI8(period);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)  */
    #endif     /* (`$INSTANCE_NAME`_FF_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutSetPeriod
********************************************************************************
*
* Summary:
*  Returns period of scl and sda timeout counters.
*
* Parameters:
*  None
*
* Return:
*  Return period of scl and sda timeout.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_TimeoutGetPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutGetPeriod")`
{
    uint16 period;

    #if(`$INSTANCE_NAME`_TIMEOUT_FF_ENABLED)
        period = (((uint16) `$INSTANCE_NAME`_TMOUT_CFG1_REG << 8u) |
                            `$INSTANCE_NAME`_TMOUT_CFG0_REG);

    #else

        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            period = (((uint16) `$INSTANCE_NAME`_TMOUT_SCL_PRD1_REG << 8u) |
                                `$INSTANCE_NAME`_TMOUT_SCL_PRD0_REG);
        #else
            period = (((uint16) `$INSTANCE_NAME`_TMOUT_SDA_PRD1_REG << 8u) | \
                                `$INSTANCE_NAME`_TMOUT_SDA_PRD0_REG);
        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED) */
    #endif     /* (`$INSTANCE_NAME`_FF_TIMEOUT_ENABLED) */

    return(period);
}


#if(`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED && `$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TimeoutSetPrescalerPeriod
    ********************************************************************************
    *
    * Summary:
    *  Sets prescaler value to increase divider possibility for UDB timeout feature.
    *
    * Parameters:
    *  period - prescaler period value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_TimeoutSetPrescalerPeriod(uint8 period)
                                                    `=ReentrantKeil($INSTANCE_NAME . "_TimeoutSetPrescalerPeriod")`
    {
        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            `$INSTANCE_NAME`_SCL_PRESCALER_PRD_REG = period;
        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

        #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
            `$INSTANCE_NAME`_SDA_PRESCALER_PRD_REG = period;
        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TimeoutGetPrescalerPeriod
    ********************************************************************************
    *
    * Summary:
    *  Returns prescaler value.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns prescaler value.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_TimeoutGetPrescalerPeriod(void)
                                                    `=ReentrantKeil($INSTANCE_NAME . "_TimeoutGetPrescalerPeriod")`
    {
        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            return (`$INSTANCE_NAME`_SCL_PRESCALER_PRD_REG);
        #else
            return (`$INSTANCE_NAME`_SDA_PRESCALER_PRD_REG);
        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */
    }
#endif /* (`$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutSaveConfig
********************************************************************************
*
* Summary:
*  Saves configuration of timeout timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutSaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutSaveConfig")`
{
    `$INSTANCE_NAME`_backup.tmoutCfg  = `$INSTANCE_NAME`_TimeoutGetPeriod();
    `$INSTANCE_NAME`_backup.tmoutIntr = `$INSTANCE_NAME`_TimeoutGetIntrMode();

    #if(CY_UDB_V0 && `$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED && `$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)
        `$INSTANCE_NAME`_backup.tmoutPrd = `$INSTANCE_NAME`_TimeoutGetPrescalerPeriod();
    #endif /* (CY_UDB_V0 && `$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutRestoreConfig
********************************************************************************
*
* Summary:
*  Restores configuration of timeout timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimeoutRestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutRestoreConfig")`
{
    #if(CY_UDB_V0 && `$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)

        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_TMOUT_INTR_ENABLE_REG |= `$INSTANCE_NAME`_TMOUT_ENABLE_INTR; /* aux_ctl */
        CyExitCriticalSection(enableInterrupts);

        #if(`$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED)
            `$INSTANCE_NAME`_TimeoutSetPrescalerPeriod(`$INSTANCE_NAME`_backup.tmoutPrd);

            enableInterrupts = CyEnterCriticalSection();
            #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
                `$INSTANCE_NAME`_SCL_PRESCALER_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_PRESCALER_CNT7_EN; /* aux_ctl */
            #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

            #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
                `$INSTANCE_NAME`_SDA_PRESCALER_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_PRESCALER_CNT7_EN; /* aux_ctl */
            #endif /* (`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED) */
            CyExitCriticalSection(enableInterrupts);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_PRESCALER_ENABLED) */

        #if(`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SCL_ADDER_REG = `$INSTANCE_NAME`_DEFAULT_TMOUT_ADDER; /* d0 */

            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TMOUT_SCL_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_FIFO_SINGLE_REG;  /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

        #if(`$INSTANCE_NAME`_TIMEOUT_SDA_TMOUT_ENABLED)
            `$INSTANCE_NAME`_TMOUT_SDA_ADDER_REG = `$INSTANCE_NAME`_DEFAULT_TMOUT_ADDER; /* d0 */

            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TMOUT_SDA_AUX_CTRL_REG |= `$INSTANCE_NAME`_TMOUT_FIFO_SINGLE_REG;  /* aux_ctl */
            CyExitCriticalSection(enableInterrupts);

        #endif /* (`$INSTANCE_NAME`_TIMEOUT_SCL_TMOUT_ENABLED) */

    #endif     /* (CY_UDB_V0 && `$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED) */

    `$INSTANCE_NAME`_TimeoutSetPeriod(`$INSTANCE_NAME`_backup.tmoutCfg);    /* cfg0, cfg1 or f0, f1 */
    `$INSTANCE_NAME`_TimeoutSetIntrMode(`$INSTANCE_NAME`_backup.tmoutIntr); /* ctrl_mask */
}


/* [] END OF FILE */
