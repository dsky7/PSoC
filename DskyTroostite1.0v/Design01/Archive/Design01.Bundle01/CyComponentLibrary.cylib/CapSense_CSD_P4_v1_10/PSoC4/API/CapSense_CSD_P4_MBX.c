/*******************************************************************************
* File Name: `$INSTANCE_NAME`_MBX.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Tuner communication APIs for the 
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_MBX.h"

extern uint8 `$INSTANCE_NAME`_idac1Settings[];

#if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
    extern uint8 `$INSTANCE_NAME`_idac2Settings[];
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

extern uint32 `$INSTANCE_NAME`_widgetResolution[];
extern uint16 `$INSTANCE_NAME`_SensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern const uint8 CYCODE `$INSTANCE_NAME`_widgetNumber[];

extern uint16 `$INSTANCE_NAME`_SensorBaseline[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern `$SizeReplacementString` `$INSTANCE_NAME`_SensorSignal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_noiseThreshold[];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_hysteresis[];
    extern uint8 `$INSTANCE_NAME`_debounce[];
    
#elif (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
    extern uint8 `$INSTANCE_NAME`_lowLevelTuningDone;
    extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[];
    extern `$SizeReplacementString` `$INSTANCE_NAME`_noiseThreshold[];

    extern uint8 `$INSTANCE_NAME`_GetPrescaler(void);
#else
    /* No tunning */
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */

#if ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) || \
      (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )
            extern uint8 `$INSTANCE_NAME`_Clk1DividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
            extern uint8 `$INSTANCE_NAME`_Clk2DividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
#else
            extern uint8 `$INSTANCE_NAME`_Clk1DividerVal;
            extern uint8 `$INSTANCE_NAME`_Clk2DividerVal;
#endif /* ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
       *    (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )
       */


#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitParams
    ********************************************************************************
    *
    * Summary:
    *  Configures component parameters to match the parameters in the inbox.
    *  Used only in manual tuning mode to apply new scanning parameters from Tuner 
    *  GUI.
    *
    * Parameters:
    *  inbox:  Pointer to Inbox structure in RAM.
    *
    * Return:
    *  None. Contents of the structure are not modified.
    * 
    * Side Effects: 
    *  Resets baseline values.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_idacSettings[] - used to store idac value for all sensors.
    *  `$INSTANCE_NAME`_fingerThreshold[] - used to store finger threshold for all 
    *  widgets.
    *  `$INSTANCE_NAME`_noiseThreshold[] - used to sotre noise threshold for all 
    *  widgets.
    *  `$INSTANCE_NAME`_hysteresis[] - used to store finger threshold for all 
    *  widgets.
    *  `$INSTANCE_NAME`_debounce[] - used to store finger threshold for all 
    *  widgets.
    *  `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
    *  for parameters from Tuner GUI. Only used in manual tuning mode.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_InitParams(volatile `$INSTANCE_NAME`_INBOX *inbox)
    {
        /* Define widget sensor belongs to */
        uint8 sensor = inbox->sensorIndex;
        uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
        
        /* Scanning parameters */
        `$INSTANCE_NAME`_idac1Settings[sensor] = inbox->idac1Settings;

        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            `$INSTANCE_NAME`_idac2Settings[sensor] = inbox->idac2Settings;
        #endif /* ( `$INSTANCE_NAME`_IDAC_CNT == 2u ) */

        `$INSTANCE_NAME`_widgetResolution[widget] = (uint32)((uint32)inbox->resolution << 
                                                    `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET);
                                                    
        `$INSTANCE_NAME`_widgetResolution[widget] |= `$INSTANCE_NAME`_RESOLUTION_8_BITS;                                            
    
        #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
            /* Exclude generic wiget */
            if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
            {
        #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
        
            /* High level parameters */
            `$INSTANCE_NAME`_fingerThreshold[widget] = inbox->fingerThreshold;
            `$INSTANCE_NAME`_noiseThreshold[widget]  = inbox->noiseThreshold;
            
            `$INSTANCE_NAME`_hysteresis[widget] = inbox->hysteresis;
            `$INSTANCE_NAME`_debounce[widget]   = inbox->debounce;
        
        #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
            /* Exclude generic wiget */
            }
        #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

        #if ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET )
        
            `$INSTANCE_NAME`_Clk1DividerVal[sensor] = inbox->analogSwitchDivider;
            `$INSTANCE_NAME`_Clk2DividerVal[sensor] = inbox->modulatorDivider;
        #else
            `$INSTANCE_NAME`_Clk1DividerVal = inbox->analogSwitchDivider;
            `$INSTANCE_NAME`_Clk2DividerVal = inbox->modulatorDivider;
        #endif /* ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) */

        /* Re-Init baselines */
        `$INSTANCE_NAME`_InitializeAllBaselines();
    }
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitMailbox
********************************************************************************
*
* Summary:
*  Initialize parameters  of mailbox structure.
*  Sets type and size of mailbox structure. 
*  Sets check sum to check by Tuner GUI and noReadMsg flag to indicate that this 
*  is the first communication packet.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx and mbx->outbox.
*
* Global Variables:
*  `$INSTANCE_NAME`_MAILBOXES - structure which incorporates two fields: 
*    - numMailBoxes (number of mailboxes);
*    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
*  `$INSTANCE_NAME`_MAILBOX - structure which incorporates status output and
*  input buffer fields and `$INSTANCE_NAME`_OUTBOX and `$INSTANCE_NAME`_INBOX.
*    - type (used as outbox read status of Tuner GUI);
*    - size (used as inbox apply status of component);
*    - `$INSTANCE_NAME`_OUTBOX outbox - structure which is used as ouput 
*      buffer for report data to Tuner GUI.
*    - `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
*      for paramters from Tuner GUI. Only used in manual tuning mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitMailbox(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
{
    /* Restore default value - clear "have_msg" */
    mbx->outbox.size = `$INSTANCE_NAME`_OUTBOX_SIZE; 
    
    /* Addtional fields for async and reset handling */
    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
        mbx->outbox.noReadMsg = 1u;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */
    
    mbx->outbox.checkSum = (uint16)(`$INSTANCE_NAME`_CHECK_SUM);
}


/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_PostMessage
********************************************************************************
*
* Summary:
*  This blocking function waits while Tuner GUI reports that content of mailbox 
*  could be modified (clears `$INSTANCE_NAME`_BUSY_FLAG). Then loads the report 
*  data to outbox and sets the busy flag.
*  In manual tuning mode the report data:
*    - raw data, baseline, signal;
*  In auto tuning mode to report added data:
*    - fingerThreshold;
*    - noiseThreshold;
*    - scanResolution;
*    - idacValue;
*    - prescaler.
*
* Parameters:
*  mbx:  Pointer to Mailbox structure in RAM.
*
* Return:
*  None. Modifies the contents of mbx->outbox.
*
* Global Variables:
*  `$INSTANCE_NAME`_MAILBOXES - structure which incorporates two fields: 
*    - numMailBoxes (number of mailboxes);
*    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
*  `$INSTANCE_NAME`_MAILBOX - structure which incorporates status output and
*  input buffer fields and `$INSTANCE_NAME`_OUTBOX and `$INSTANCE_NAME`_INBOX.
*    - type (used as outbox read status of Tuner GUI);
*    - size (used as inbox apply status of component);
*    - `$INSTANCE_NAME`_OUTBOX outbox - structure which is used as ouput 
*      buffer for report data to Tuner GUI.
*    - `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
*      for parameters from Tuner GUI. Only used in manual tuning mode.
*  `$INSTANCE_NAME`_lowLevelTuningDone - used to notify the Tuner GUI that 
*  tuning of scanning parameters are done. The scanning parameters in mailbox
*  will not be updated after clear it.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
{
    uint8 i;
    
    /* Copy all data - Raw, Base, Signal, OnMask */
    for(i=0; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        mbx->outbox.rawData[i]  = `$INSTANCE_NAME`_SensorRaw[i];
        mbx->outbox.baseLine[i] = `$INSTANCE_NAME`_SensorBaseline[i];
        #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
            mbx->outbox.signal[i]   = `$INSTANCE_NAME`_SensorSignal[i];
        #else
            mbx->outbox.signal[i]   = `$INSTANCE_NAME`_SensorSignal[i];
        #endif  /* (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8) */
    }
        
    /* AutoTuning - need to copy all High Level parameters */
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
        
        /* Parameters are changed in run time */
        for(i=0; i < `$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT; i++)
        {
            mbx->outbox.fingerThreshold[i] = `$INSTANCE_NAME`_fingerThreshold[i];
            mbx->outbox.noiseThreshold[i]  = `$INSTANCE_NAME`_noiseThreshold[i];
        }
        
        /* Widget resolution, take to account TP and MB */
        for(i=0; i < `$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT; i++)
        {
            mbx->outbox.scanResolution[i]  = (uint8)(`$INSTANCE_NAME`_widgetResolution[i] >> `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET);
        }

        /* Copy tuned idac values */
        for(i=0; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
        {
            mbx->outbox.idac1Value[i] = `$INSTANCE_NAME`_idac1Settings[i];
			#if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            	mbx->outbox.idac2Value[i] = `$INSTANCE_NAME`_idac2Settings[i];
			#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */	
        }
            
        /* Pass parameters only once */
        `$INSTANCE_NAME`_lowLevelTuningDone = 0u;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */

    /* Copy scan parameters */
    #if ( `$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING )
        for(i=0; i < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; i++)
        {
            mbx->outbox.analogSwitchDivider[i] = `$INSTANCE_NAME`_Clk1DividerVal[i];
            mbx->outbox.modulatorDivider[i] = `$INSTANCE_NAME`_Clk2DividerVal[i];
        }
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */
    
}

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadMessage
    ********************************************************************************
    *
    * Summary:
    *  If `$INSTANCE_NAME`_HAVE_MSG is found in the mailbox, initialize component 
    *  with parameters found in the inbox. Signal DONE by overwriting the
    *  value in size field in mailbox.
    *  Only available when manual tuning mode.
    *
    * Parameters:
    *  mbx:  Pointer to Mailbox structure in RAM.
    *
    * Return:
    *  None. Modifies the contents of mbx.
    *
    * Side Effects: 
    *  Initializes component parameters if `$INSTANCE_NAME`_HAVE_MSG is received.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_MAILBOXES - structure which incorporates two fields: 
    *    - numMailBoxes (number of mailboxes);
    *    - `$INSTANCE_NAME`_MAILBOX csdMailbox;
    *  `$INSTANCE_NAME`_MAILBOX - structure which incorporates status output and
    *  input buffer fields and `$INSTANCE_NAME`_OUTBOX and `$INSTANCE_NAME`_INBOX.
    *    - type (used as outbox read status of Tuner GUI);
    *    - size (used as inbox apply status of component);
    *    - `$INSTANCE_NAME`_OUTBOX outbox - structure which is used as ouput 
    *      buffer for report data to Tuner GUI.
    *    - `$INSTANCE_NAME`_INBOX inbox - structure which is used as input buffer
    *      for parameters from Tuner GUI. Only used in manual tuning mode.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ReadMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx)
    {
        volatile `$INSTANCE_NAME`_INBOX *tmpInbox;
       
        tmpInbox = &(mbx->inbox);
            
        `$INSTANCE_NAME`_InitParams(tmpInbox);
        
        /* Defualt settings where changed */
        mbx->outbox.noReadMsg = 0u;
    }
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */


/* [] END OF FILE */
