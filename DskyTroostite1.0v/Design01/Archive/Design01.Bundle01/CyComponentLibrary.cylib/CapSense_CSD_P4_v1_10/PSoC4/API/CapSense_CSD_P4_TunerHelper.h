/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TunerHelper.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the tunner hepl
*  APIs for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_CSHL.h"
#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    #include "`$INSTANCE_NAME`_MBX.h"
#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define `$INSTANCE_NAME`_DEFAULT_MAILBOXES_NUMBER   (1u)
#define `$INSTANCE_NAME`_CMD_WAIT_TIMEOUT           (0xFFFFFFFFu)


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_TunerStart(void);
void `$INSTANCE_NAME`_TunerComm(void);

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    uint8 `$INSTANCE_NAME`_ReadCommand(void);
    void `$INSTANCE_NAME`_WriteCommand(uint32 cmd);
    void `$INSTANCE_NAME`_ClearCommand(uint32 cmd);
    void `$INSTANCE_NAME`_TxData(volatile `$INSTANCE_NAME`_OUTBOX *inbox);
	
	#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    	void `$INSTANCE_NAME`_RxData(volatile `$INSTANCE_NAME`_INBOX *inbox);
	#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */	

#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H)*/


/* [] END OF FILE */
