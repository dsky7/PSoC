/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
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

`$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{   
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{
	if(`$INSTANCE_NAME`_CSD_CFG_REG & `$INSTANCE_NAME`_CSD_CFG_ENABLE)
	{
		`$INSTANCE_NAME`_backup.enableState = 1u;
	}
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Disables Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save component state before enter sleep 
*  mode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
	`$INSTANCE_NAME`_SaveConfig();
		
	/* Disable interrupt */
	CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
	
	`$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_SENSE_EN);
	CyDelayUs(100u);
	`$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN);
	
	`$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_ENABLE);
	
	/* Disable the Clocks */
    `$INSTANCE_NAME`_CSD_Clk1_Stop();
    `$INSTANCE_NAME`_CSD_Clk2_Stop();
	
	/* Clear all sensors */
    `$INSTANCE_NAME`_ClearSensors();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after `$INSTANCE_NAME`_SaveConfig() routine. Otherwise 
*  the component configuration will be overwritten with its initial setting.  
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{

}
 
 
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores CapSense configuration and non-retention register values. 
*  Restores enabled state of component by setting Active mode power template 
*  bits for number of component used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
	/* Enable the Clocks */
    `$INSTANCE_NAME`_CSD_Clk1_Start();
    `$INSTANCE_NAME`_CSD_Clk2_Start();
    
	/* Restore CapSense Enable state */
    if (`$INSTANCE_NAME`_backup.enableState != 0u)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
