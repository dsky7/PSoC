/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the EZI2C
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZI2C_PVT_`$INSTANCE_NAME`_H)
#define CY_EZI2C_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*     Vars with External Linkage
***************************************/

extern `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;

extern volatile uint8 `$INSTANCE_NAME`_curStatus; /* Status byte */
extern volatile uint8 `$INSTANCE_NAME`_curState;  /* Current state of I2C state machine */

/* Pointer to data exposed to I2C Master */
extern volatile uint8 * `$INSTANCE_NAME`_dataPtrS1;

/* Size of buffer1 in bytes */
extern volatile uint16 `$INSTANCE_NAME`_bufSizeS1; 

/* Offset for read and write operations, set at each write sequence */
extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwOffsetS1;

/* Points to next value to be read or written */
extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwIndexS1;

/* Offset where data is read only */
extern volatile uint16 `$INSTANCE_NAME`_wrProtectS1;

/* If two slave addresses, creat second set of varaibles  */
#if(`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)

    /* Software address compare 1 */
    extern volatile uint8 `$INSTANCE_NAME`_addrS1;

    /* Software address compare 2 */
    extern volatile uint8 `$INSTANCE_NAME`_addrS2;

    /* Pointer to data exposed to I2C Master */
    extern volatile uint8 * `$INSTANCE_NAME`_dataPtrS2;

    /* Size of buffer2 in bytes */
    extern volatile uint16 `$INSTANCE_NAME`_bufSizeS2; 

    /* Offset for read and write operations, set at each write sequence */
    extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwOffsetS2;

    /* Points to next value to be read or written */
    extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwIndexS2;

    /* Offset where data is read only */
    extern volatile uint16 `$INSTANCE_NAME`_wrProtectS2;

#endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */

#if(`$INSTANCE_NAME`_WAKEUP_ENABLED)
    extern volatile uint8 `$INSTANCE_NAME`_wakeupSource;
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

#endif /* CY_EZI2C_PVT_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
