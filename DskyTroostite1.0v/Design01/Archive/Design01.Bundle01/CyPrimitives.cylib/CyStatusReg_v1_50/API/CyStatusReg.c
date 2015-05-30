/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains API to enable firmware to read the value of a status 
*  register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

#if !defined(`$INSTANCE_NAME`_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
********************************************************************************
*
* Summary:
*  Read the value of the `$INSTANCE_NAME`_Status register
*
* Parameters:  
*  void
*
* Return: 
*  The value of the `$INSTANCE_NAME`_Status register.
*
* Reentrant:
*  Yes
* 
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`
{ 
    return `$INSTANCE_NAME`_Status;
}


#endif /* Check for removal by optimization */

