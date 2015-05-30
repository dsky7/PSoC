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
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup = 
{
    /* Generation of vertical and horizontal timing is disabled */
    `$INSTANCE_NAME`_DISABLED,
    
    /* Horizontal timing configuration */
    `$INSTANCE_NAME`_HORIZ_BACK_PORCH,          /* Back Porch    (F0) */
    `$INSTANCE_NAME`_HORIZ_ACTIVE_REG,          /* Active Region (F1) */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_HORIZ_FRONT_PORCH,     /* Front Porch (D0) */
        `$INSTANCE_NAME`_HORIZ_SYNC_WIDTH,      /* Sync Widht (D1)  */
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
    
    /* Vertical timing configuration */
    `$INSTANCE_NAME`_VERT_BACK_PORCH,           /* Back Porch    (F0) */    
    `$INSTANCE_NAME`_VERT_ACTIVE_REG,           /* Active Region (F1) */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_VERT_FRONT_PORCH,      /* Front Porch (D0) */
        `$INSTANCE_NAME`_VERT_SYNC_WIDTH,       /* Sync Width  (D1) */
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
    
    /* SRAM access configuration for panel refreshing */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_INIT_FRAME_ADDRESS,    /* Frame buffer address */
        `$INSTANCE_NAME`_INIT_LINE_INCR + 1u    /* Increment at the end of a line. Should be
                                                 * one more than init value */
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
* Summary:
*  Saves the user configuration of GraphicLCDCtrl non-retention registers.
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
    /* Saves Horizontal timing configuration */
    `$INSTANCE_NAME`_backup.horizBp  = `$INSTANCE_NAME`_HORIZ_BP_REG;
    `$INSTANCE_NAME`_backup.horizAct = `$INSTANCE_NAME`_HORIZ_ACT_REG;
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_backup.horizFp   = `$INSTANCE_NAME`_HORIZ_FP_REG;
        `$INSTANCE_NAME`_backup.horizSync = `$INSTANCE_NAME`_HORIZ_SYNC_REG;
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
    
    /* Saves Vertical timing configuration */
    `$INSTANCE_NAME`_backup.vertBp  = `$INSTANCE_NAME`_VERT_BP_REG;
    `$INSTANCE_NAME`_backup.vertAct = `$INSTANCE_NAME`_VERT_ACT_REG;
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_backup.vertFp   = `$INSTANCE_NAME`_VERT_FP_REG;
        `$INSTANCE_NAME`_backup.vertSync = `$INSTANCE_NAME`_VERT_SYNC_REG;
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
    
    /* Saves SRAM access configuration for panel refreshing */
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        `$INSTANCE_NAME`_backup.frameAddr = CY_GET_REG24(`$INSTANCE_NAME`_FRAME_BUF_LSB_PTR);
        `$INSTANCE_NAME`_backup.lineIncr  = CY_GET_REG24(`$INSTANCE_NAME`_LINE_INCR_LSB_PTR);
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
* Summary:
*  Restores the user configuration of GraphicLCDCtrl non-retention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
* `$INSTANCE_NAME`_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)   `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    /* Set FIFOs in the Single Buffer Mode */
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) 
        uint8 enableInterrupts;
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_HORIZ_DP_AUX_CTL_REG |= `$INSTANCE_NAME`_FX_CLEAR;  
        `$INSTANCE_NAME`_VERT_DP_AUX_CTL_REG  |= `$INSTANCE_NAME`_FX_CLEAR;
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */ 
    
    /* Restores the Horizontal Timing configuration */ 
    `$INSTANCE_NAME`_HORIZ_BP_REG  = `$INSTANCE_NAME`_backup.horizBp;
    `$INSTANCE_NAME`_HORIZ_ACT_REG = `$INSTANCE_NAME`_backup.horizAct;
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)    
        `$INSTANCE_NAME`_HORIZ_FP_REG   = `$INSTANCE_NAME`_backup.horizFp;
        `$INSTANCE_NAME`_HORIZ_SYNC_REG = `$INSTANCE_NAME`_backup.horizSync;
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */   
    
    /* Restores the Vertical Timing configuration */
    `$INSTANCE_NAME`_VERT_BP_REG  = `$INSTANCE_NAME`_backup.vertBp;
    `$INSTANCE_NAME`_VERT_ACT_REG = `$INSTANCE_NAME`_backup.vertAct;
    /* PSoC3 ES2 or early, PSoC5 ES1*/    
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)   
        `$INSTANCE_NAME`_VERT_FP_REG   = `$INSTANCE_NAME`_backup.vertFp;
        `$INSTANCE_NAME`_VERT_SYNC_REG = `$INSTANCE_NAME`_backup.vertSync; 
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */  
    
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if(`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) 
        /* Restores the frame starting address */
        CY_SET_REG24(`$INSTANCE_NAME`_FRAME_BUF_LSB_PTR, `$INSTANCE_NAME`_backup.frameAddr);
    
        /* Restores the increment at the end of the line */
        CY_SET_REG24(`$INSTANCE_NAME`_LINE_INCR_LSB_PTR, `$INSTANCE_NAME`_backup.lineIncr);
    #endif /* (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */ 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  prior to entering sleep.
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
    if((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_ENABLE) == `$INSTANCE_NAME`_ENABLE)
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else /* The component is disabled */
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
    
    /* Stop component */
    `$INSTANCE_NAME`_Stop();

    /* Save registers configuration */
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  after awaking from sleep.
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
void `$INSTANCE_NAME`_Wakeup(void)  `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Restore registers values */
    `$INSTANCE_NAME`_RestoreConfig();
    
    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Enable component's operation */
        `$INSTANCE_NAME`_Enable();

    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */
