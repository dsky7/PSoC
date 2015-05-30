/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_STATUS_REG_`$INSTANCE_NAME`_H) /* CY_STATUS_REG_`$INSTANCE_NAME`_H */
#define CY_STATUS_REG_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*        Function Prototypes 		    
***************************************/    

uint8 `$INSTANCE_NAME`_Read(void);


/***************************************
*             Registers        
***************************************/

/* Status Register */
#define `$INSTANCE_NAME`_Status		(* (reg8 *) `$INSTANCE_NAME`_sts_reg__STATUS_REG )

#endif /* End CY_STATUS_REG_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
