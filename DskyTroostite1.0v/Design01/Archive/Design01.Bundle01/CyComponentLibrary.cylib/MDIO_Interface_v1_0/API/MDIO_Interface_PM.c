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
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_ADVANCED_MODE)
    #include "`$INSTANCE_NAME`_REG.h"
#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

static `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    /* By default the component and interrupts are disabled */
    `$INSTANCE_NAME`_DISABLED,
    `$INSTANCE_NAME`_DISABLED
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves MDIO_Interface configuration.
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
    `$INSTANCE_NAME`_backup.interruptState = `$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_INT_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores MDIO_Interface configuration.
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
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    #if(CY_UDB_V0)
    
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFOs in the Single Buffer Mode */
        `$INSTANCE_NAME`_FP_AUX_CTL0_REG |= `$INSTANCE_NAME`_F0_CLEAR;
        `$INSTANCE_NAME`_FP_AUX_CTL1_REG |= `$INSTANCE_NAME`_F0_CLEAR;
        CyExitCriticalSection(enableInterrupts);
               
        /* Update physical and device addresses */
        `$INSTANCE_NAME`_UpdatePhyAddress();
        
        /* Set bit counter period */ 
        `$INSTANCE_NAME`_BCNT_PERIOD_REG = `$INSTANCE_NAME`_BCNT_PER;
        
    #endif /* (CY_UDB_V0) */
    
    #if(`$INSTANCE_NAME`_ADVANCED_MODE)
    
        #if(CY_UDB_V0)
            /* Set the size of register page info */
            CY_SET_REG16(`$INSTANCE_NAME`_INFO_INC_PTR, `$INSTANCE_NAME`_PAGE_INFO_INC);
            /* Set the lower 16-bit address of the page info array */
            CY_SET_REG16(`$INSTANCE_NAME`_INFO_BASE_PTR, LO16((uint32)`$INSTANCE_NAME`_pageInfoList));
        #endif /* CY_UDB_V0 */
        
        /* Set memory type of the each register page */
        `$INSTANCE_NAME`_MEM_TYPE_REG   = `$INSTANCE_NAME`_PAGE_MEM_TYPE;
        /* Set data width of the each register page */
        `$INSTANCE_NAME`_PAGE_WIDTH_REG = `$INSTANCE_NAME`_PAGE_DATA_WIDTH;
    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */
    
    /* Restore interrupt state */
    `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_backup.interruptState;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  prior to entering low power mode.
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
    if(`$INSTANCE_NAME`_DISABLED != (`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_EN))
    {
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_ENABLED;
    }
    else /* The component is disabled */
    {
        `$INSTANCE_NAME`_backup.enableState = `$INSTANCE_NAME`_DISABLED;
    }
    
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
*  Enables block's operation and restores its configuration. Should be called
*  after awaking from low power mode.
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
void `$INSTANCE_NAME`_Wakeup(void)  `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    /* Restore registers values */
    `$INSTANCE_NAME`_RestoreConfig();
    
    if(`$INSTANCE_NAME`_DISABLED != `$INSTANCE_NAME`_backup.enableState)
    {
        /* Enable component's operation */
        `$INSTANCE_NAME`_Enable();

    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */
