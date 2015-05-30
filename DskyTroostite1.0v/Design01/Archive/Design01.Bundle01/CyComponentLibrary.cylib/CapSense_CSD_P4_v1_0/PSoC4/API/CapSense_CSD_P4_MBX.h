/*******************************************************************************
* File Name: `$INSTANCE_NAME`_MBX.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the tuner 
*  communication the for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_CSHL.h"


/***************************************
*   Condition compilation parameters
***************************************/

/* Check Sum to identify data */
#define `$INSTANCE_NAME`_CHECK_SUM      (`$CheckSum`u)

#define `$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT     (((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

#define CYPACKED __attribute__ ((packed))

#define `$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT           (`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)

#define `$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT     (`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)


/***************************************
*      Type defines for mailboxes
***************************************/

/* Outbox structure definition */
typedef struct _`$INSTANCE_NAME`_outbox
{   
    uint16  size;
	uint16  checkSum;
    #if (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
        uint16   position[`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT];
    #endif  /* (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */

    #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8   mb_position[`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2];
    #endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

    uint16   rawData[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    uint16   baseLine[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    `$SizeReplacementString` signal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    uint8    onMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT];
    
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
        `$SizeReplacementString`   fingerThreshold[`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT];
        `$SizeReplacementString`   noiseThreshold[`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT];
        uint8   scanResolution[`$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT];
        uint8   idac1Value[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
        uint8   idac2Value[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
		uint8   analogSwitchDivider[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
        uint8   modulatorDivider[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */

    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
        uint8   noReadMsg;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */
    
} CYPACKED `$INSTANCE_NAME`_OUTBOX;

/* Inbox structure definition */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    typedef struct _`$INSTANCE_NAME`_inbox
    {
        uint8   sensorIndex;

        uint8   idac1Settings;
        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            uint8   idac2Settings;
        #endif /* ( (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

        uint8   resolution;
        `$SizeReplacementString`   fingerThreshold;
        `$SizeReplacementString`   noiseThreshold;
        `$SizeReplacementString`   hysteresis;
        uint8   debounce;
        uint8   analogSwitchDivider;
		uint8   modulatorDivider;
    } CYPACKED `$INSTANCE_NAME`_INBOX;
    
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */

/* Mailbox structure definition */
typedef struct _`$INSTANCE_NAME`_mailBox
{
    `$INSTANCE_NAME`_OUTBOX  outbox;
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
        `$INSTANCE_NAME`_INBOX inbox;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */
    
} CYPACKED `$INSTANCE_NAME`_MAILBOX;


/* Mailboxes structure definition */
typedef struct _`$INSTANCE_NAME`_mailboxes
{
    uint8   numMailBoxes;       /* This must always be the first. Represents # of mailboxes */
    `$INSTANCE_NAME`_MAILBOX    csdMailbox;
    
} CYPACKED `$INSTANCE_NAME`_MAILBOXES;

#define `$INSTANCE_NAME`_INBOX_SIZE  sizeof(`$INSTANCE_NAME`_INBOX)
#define `$INSTANCE_NAME`_OUTBOX_SIZE sizeof(`$INSTANCE_NAME`_OUTBOX)

/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_InitMailbox(volatile `$INSTANCE_NAME`_MAILBOX *mbx);
void `$INSTANCE_NAME`_PostMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx);

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    void `$INSTANCE_NAME`_ReadMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx);
    void `$INSTANCE_NAME`_RxData(volatile `$INSTANCE_NAME`_INBOX *inbox);
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */


/***************************************
*           API Constants        
***************************************/

/* The selected ID for this version of Tuner */
#define `$INSTANCE_NAME`_START_FRAME    (0x01u)
#define `$INSTANCE_NAME`_NEXT_FRAME     (0x02u)
#define `$INSTANCE_NAME`_END_FRAME      (0x04u)
#define `$INSTANCE_NAME`_READY          (0x08u)
#define `$INSTANCE_NAME`_START_SCAN     (0x10u)
#define `$INSTANCE_NAME`_HAVE_MSG       (0x20u)
#define `$INSTANCE_NAME`_RESEND_REQ     (0x40u)

#endif  /* (CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
