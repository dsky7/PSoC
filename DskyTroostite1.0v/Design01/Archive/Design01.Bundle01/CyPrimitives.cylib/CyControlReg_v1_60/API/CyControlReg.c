/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains API to enable firmware control of a control register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

#if !defined(`$INSTANCE_NAME`_ctrl_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write
********************************************************************************
*
* Summary:
*  Write a byte to a control register.
*
* Parameters:  
*  control:  The value to be assigned to the control register. 
*
* Return: 
*  void 
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
void `$INSTANCE_NAME`_Write(uint8 control) `=ReentrantKeil($INSTANCE_NAME . "_Write")`
{
    `$INSTANCE_NAME`_Control = control;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
********************************************************************************
*
* Summary:
*  Read the current value assigned to a control register.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the control register
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`
{
    return `$INSTANCE_NAME`_Control;
}

#endif /* End check for removal by optimization */
