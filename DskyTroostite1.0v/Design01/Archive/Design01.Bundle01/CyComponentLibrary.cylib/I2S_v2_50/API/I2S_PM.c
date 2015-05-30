/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup =
{
    /* Generation of WS and SCK is disabled */
    `$INSTANCE_NAME`_DISABLED,

    /* RX and/or TX directions are disabled */
    `$INSTANCE_NAME`_DISABLED,

    #if(CY_UDB_V0)
        /* WS Period */
        `$INSTANCE_NAME`_DEFAULT_WS_PERIOD,

        #if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_DEFAULT_TX_INT_SOURCE,
        #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
       
        #if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_DEFAULT_RX_INT_SOURCE
        #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */

    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves I2S configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    /* Saves CTL_REG bits to define what direction was enabled */
    `$INSTANCE_NAME`_backup.CtrlReg = `$INSTANCE_NAME`_CONTROL_REG;

    /* Saves CNT7 and STATUSI MSK/PER for UDB array version 0 */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_backup.Cnt7Period = `$INSTANCE_NAME`_CNT7_PERIOD_REG;

        #if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_backup.TxIntMask = `$INSTANCE_NAME`_TX_STATUS_MASK_REG;
        #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
        
        #if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_backup.RxIntMask = `$INSTANCE_NAME`_RX_STATUS_MASK_REG;
        #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */

    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores I2S configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    /* Restores CNT7 and STATUSI MSK/PER registers for UDB array version 0 */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_CNT7_PERIOD_REG = `$INSTANCE_NAME`_backup.Cnt7Period;

        #if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_TX_STATUS_MASK_REG = `$INSTANCE_NAME`_backup.TxIntMask;
        #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
        
        #if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
            `$INSTANCE_NAME`_RX_STATUS_MASK_REG = `$INSTANCE_NAME`_backup.RxIntMask;
        #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepares I2S goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`
{
    /* Get component state */
    `$INSTANCE_NAME`_backup.enableState = ((uint8) `$INSTANCE_NAME`_IS_ENABLE);

    /* Save registers configuration */
    `$INSTANCE_NAME`_SaveConfig();

    /* Stop component */
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Prepares I2S to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used when non-retention registers are restored.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Restore registers values */
    `$INSTANCE_NAME`_RestoreConfig();

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Enable component's operation */
        `$INSTANCE_NAME`_Enable();

        /* Enable Tx/Rx direction if they were enabled before sleep */
        #if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
            if(0u != (`$INSTANCE_NAME`_backup.CtrlReg & `$INSTANCE_NAME`_TX_EN))
            {
                `$INSTANCE_NAME`_EnableTx();
            }
        #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
        
        #if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
            if(0u != (`$INSTANCE_NAME`_backup.CtrlReg & `$INSTANCE_NAME`_RX_EN))
            {
                `$INSTANCE_NAME`_EnableRx();
            }
        #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */
    }
}


/* [] END OF FILE */
