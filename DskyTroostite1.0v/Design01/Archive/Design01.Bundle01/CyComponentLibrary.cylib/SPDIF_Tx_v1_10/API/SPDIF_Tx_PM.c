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
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if (0u != `$INSTANCE_NAME`_MANAGED_DMA)
    extern void `$INSTANCE_NAME`_CstDmaInit(void);
#endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */ 

#if(CY_UDB_V0)
    static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup = 
    {
        /* By default the interrupt will be generated only for errors */
        `$INSTANCE_NAME`_DEFAULT_INT_SRC
    };
#endif /* (CY_UDB_V0) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPDIF_Tx configuration.
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
void `$INSTANCE_NAME`_SaveConfig(void)
{
    /* UDB array version 0 */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_backup.interruptMask = `$INSTANCE_NAME`_STATUS_MASK_REG;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPDIF_Tx configuration.
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
    /* UDB array version 0 */    
    #if(CY_UDB_V0)   
        uint8 enableInterrupts;    
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFOs in the Single Buffer Mode */
        `$INSTANCE_NAME`_FCNT_AUX_CTL_REG    |= `$INSTANCE_NAME`_FX_CLEAR; 
        `$INSTANCE_NAME`_PREGEN_AUX_CTL_REG  |= `$INSTANCE_NAME`_FX_CLEAR;  
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts); 
    #endif /* (CY_UDB_V0) */        
    
    /* Restore Frame and Block Intervals */
    /* Preamble and Post Data Period */ 
    `$INSTANCE_NAME`_FCNT_PRE_POST_REG = `$INSTANCE_NAME`_PRE_POST_PERIOD;    
    /* Number of frames in block */
    `$INSTANCE_NAME`_FCNT_BLOCK_PERIOD_REG = `$INSTANCE_NAME`_BLOCK_PERIOD;    
    /* UDB array version 0 */    
    #if(CY_UDB_V0) 
        /* Frame Period */
        `$INSTANCE_NAME`_FRAME_PERIOD_REG = `$INSTANCE_NAME`_FRAME_PERIOD;
        /* Audio Sample Word Length */ 
        `$INSTANCE_NAME`_FCNT_AUDIO_LENGTH_REG = `$INSTANCE_NAME`_AUDIO_DATA_PERIOD;  
    #endif /* (CY_UDB_V0) */
        
    /* Restore Preamble Patterns */
    /* UDB array version 0 */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_PREGEN_PREX_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_X_PATTERN;
        `$INSTANCE_NAME`_PREGEN_PREY_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_Y_PATTERN;
    #endif /* (CY_UDB_V0) */            
    `$INSTANCE_NAME`_PREGEN_PREZ_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_Z_PATTERN;
    
    /* Restore Interrupt Mask */
    /* UDB array version 0 */
    #if(CY_UDB_V0)
        `$INSTANCE_NAME`_STATUS_MASK_REG = `$INSTANCE_NAME`_backup.interruptMask;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Prepares SPDIF_Tx goes to sleep.
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
void `$INSTANCE_NAME`_Sleep(void)
{
    /* Stop component */
    `$INSTANCE_NAME`_Stop();

    /* Save registers configuration */
    `$INSTANCE_NAME`_SaveConfig();    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Prepares SPDIF_Tx to wake up.
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
*  No.
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{   
    /* Restore registers values */
    `$INSTANCE_NAME`_RestoreConfig();        
}


/* [] END OF FILE */
