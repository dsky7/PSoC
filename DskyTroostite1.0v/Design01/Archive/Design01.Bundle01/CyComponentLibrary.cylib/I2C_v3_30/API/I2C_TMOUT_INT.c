/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TMOUT_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for timeout feature of I2C component.
*
*  Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START `$INSTANCE_NAME`_TMOUT_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimeoutReset
********************************************************************************
*
* Summary:
*  Restores configuration of timeout unit.
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
void `$INSTANCE_NAME`_TimeoutReset(void) `=ReentrantKeil($INSTANCE_NAME . "_TimeoutReset")`
{
    `$INSTANCE_NAME`_Stop();    /* Reset I2C */

    /* `#START `$INSTANCE_NAME`_TMOUT_ISR_BEFORE_BUF_RESET` */

    /* `#END` */

    #if(`$INSTANCE_NAME`_MODE_SLAVE_ENABLED)
        /* Reset status and buffer index */
        `$INSTANCE_NAME`_SlaveClearReadBuf();
        `$INSTANCE_NAME`_SlaveClearWriteBuf();
        (void) `$INSTANCE_NAME`_SlaveClearReadStatus();
        (void) `$INSTANCE_NAME`_SlaveClearWriteStatus();

    #endif /* (`$INSTANCE_NAME`_MODE_SLAVE_ENABLED) */

    #if(`$INSTANCE_NAME`_MODE_MASTER_ENABLED)
        /* Reset status and buffer index */
        `$INSTANCE_NAME`_MasterClearReadBuf();
        `$INSTANCE_NAME`_MasterClearWriteBuf();
        (void) `$INSTANCE_NAME`_MasterClearStatus();

    #endif /* (`$INSTANCE_NAME`_MODE_MASTER_ENABLED) */

    /* Enable component */
    `$INSTANCE_NAME`_Enable();
    `$INSTANCE_NAME`_EnableInt();
}


#if(`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TMOUT_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
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
    CY_ISR(`$INSTANCE_NAME`_TMOUT_ISR)
    {
        `$INSTANCE_NAME`_TimeoutReset();
    }
#endif /* (`$INSTANCE_NAME`_TIMEOUT_UDB_ENABLED) */


/* [] END OF FILE */
