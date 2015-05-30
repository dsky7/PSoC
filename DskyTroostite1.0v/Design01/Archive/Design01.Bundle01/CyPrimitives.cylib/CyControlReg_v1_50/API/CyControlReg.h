/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CONTROL_REG_`$INSTANCE_NAME`_H) /* CY_CONTROL_REG_`$INSTANCE_NAME`_H */
#define CY_CONTROL_REG_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*         Function Prototypes 
***************************************/    

void    `$INSTANCE_NAME`_Write(uint8 control) `=ReentrantKeil($INSTANCE_NAME . "_Write")`;
uint8   `$INSTANCE_NAME`_Read(void) `=ReentrantKeil($INSTANCE_NAME . "_Read")`;

/***************************************
*            Registers        
***************************************/

/* Control Register */
#define `$INSTANCE_NAME`_Control         (* (reg8 *) `$INSTANCE_NAME`_ctrl_reg__CONTROL_REG )
#endif /* End CY_CONTROL_REG_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
