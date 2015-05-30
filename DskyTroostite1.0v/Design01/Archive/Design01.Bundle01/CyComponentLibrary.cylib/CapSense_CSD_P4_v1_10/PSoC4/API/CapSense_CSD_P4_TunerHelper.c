/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TunerHelper.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Tuner helper APIs for the CapSense CSD 
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_TunerHelper.h"

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    #include "`$EzI2CInstanceName`.h"
	#include "`$EzI2CInstanceName`_EZBUF_MODE.h"
    
    void `$INSTANCE_NAME`_ProcessAllWidgets(volatile `$INSTANCE_NAME`_OUTBOX *outbox);
    
    volatile `$INSTANCE_NAME`_MAILBOXES `$INSTANCE_NAME`_mailboxesComm;

    extern uint8 `$INSTANCE_NAME`_SensorOnMask[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
#endif  /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerStart
********************************************************************************
*
* Summary:
*  Initializes CapSense CSD component and EzI2C communication componenet to use
*  mailbox data structure for communication with Tuner GUI.
*  Start the scanning, after initialization complete.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerStart(void)
{
    #if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
        
        /* Init mbx and quick check */
        `$INSTANCE_NAME`_InitMailbox(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
        `$INSTANCE_NAME`_mailboxesComm.numMailBoxes = `$INSTANCE_NAME`_DEFAULT_MAILBOXES_NUMBER;
        
        /* Start EzI2C, clears buf pointers */
        `$EzI2CInstanceName`_Start(); 
        
        /* Start CapSense and baselines */
        `$INSTANCE_NAME`_Start();
        
        /* Initialize baselines */ 
        `$INSTANCE_NAME`_InitializeAllBaselines();
        `$INSTANCE_NAME`_InitializeAllBaselines();
        
        /* Starts scan all enabled sensors */
        `$INSTANCE_NAME`_ScanEnabledWidgets();
    
    #endif  /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scaning loop is completed and apply
*  new parameters from Tuner GUI if available (manual tuning mode only). Updates
*  enabled baselines and state of widgets. Waits while Tuner GUI reports that 
*  content of mailbox could be modified. Then loads the report data into outbox 
*  and sets the busy flag. Starts new scanning loop.
*  
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_TunerComm(void)
{   
    #if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
            
        if (0u == `$INSTANCE_NAME`_IsBusy())
        {	
            
            `$EzI2CInstanceName`_EzBufWriteByte((uint32)0u, 0);
            
            `$INSTANCE_NAME`_ProcessAllWidgets(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox.outbox);
            `$INSTANCE_NAME`_PostMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
            
            do{
                `$INSTANCE_NAME`_ClearCommand(`$INSTANCE_NAME`_RESEND_REQ);
                `$INSTANCE_NAME`_TxData(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox.outbox);
            }while(`$INSTANCE_NAME`_RESEND_REQ & `$INSTANCE_NAME`_ReadCommand());
            
        #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
				if(`$INSTANCE_NAME`_HAVE_MSG & `$INSTANCE_NAME`_ReadCommand())
				{
					`$INSTANCE_NAME`_ClearCommand(`$INSTANCE_NAME`_HAVE_MSG);
					`$INSTANCE_NAME`_RxData(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox.inbox);
                	`$INSTANCE_NAME`_ReadMessage(&`$INSTANCE_NAME`_mailboxesComm.csdMailbox);
				}
        #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */
		
	    /* Update all baselines and process all widgets */
        `$INSTANCE_NAME`_UpdateEnabledBaselines();
		
        /* Start scan all sensors */
        `$INSTANCE_NAME`_ScanEnabledWidgets();
		
        }
        
    #endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */
    
}


#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Call required functions to update all widgets state:
    *   - `$INSTANCE_NAME`_GetCentroidPos() - calls only if linear sliders 
    *     available.
    *   - `$INSTANCE_NAME`_GetRadialCentroidPos() - calls only if radial slider 
    *     available.
    *   - `$INSTANCE_NAME`_GetTouchCentroidPos() - calls only if touch pad slider 
    *     available.
    *   - `$INSTANCE_NAME`_CheckIsAnyWidgetActive();
    *  The results of opeartions are copied to OUTBOX.
    *   
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_OUTBOX outbox - structure which is used as ouput 
    *  buffer for report data to Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ProcessAllWidgets(volatile `$INSTANCE_NAME`_OUTBOX *outbox)
    {
        uint8 i = 0u;

        #if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
            uint16 pos[2];
        #endif  /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */
        
        #if ( (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) || \
              (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) )
            uint8 widgetCnt = 0u;
        #endif  /* ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)) || 
                *   (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
                */
        
        /* Calculate widget with centroids */
        #if (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < `$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = (uint16)`$INSTANCE_NAME`_GetCentroidPos(i);
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT) */
        
        #if (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < widgetCnt + `$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = (uint16)`$INSTANCE_NAME`_GetRadialCentroidPos(i);
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT) */
        
        #if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT * 2)); i=i+2)
            {
                if(`$INSTANCE_NAME`_GetTouchCentroidPos(i, pos) == 0u)
                {
                    outbox->position[i] = 0xFFFFu;
                    outbox->position[i+1] = 0xFFFFu;
                }
                else
                {
                    outbox->position[i] = (uint16) pos[0u];
                    outbox->position[i+1] =(uint16) pos[1u];
                }
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */

        #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
            i += `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0;
            for(; widgetCnt < (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2); i += 2)
            {
                if(`$INSTANCE_NAME`_GetMatrixButtonPos(i, ((uint8*) &outbox->mb_position[widgetCnt])) == 0)
                {
                    outbox->mb_position[widgetCnt] = 0xFFu;
                    outbox->mb_position[widgetCnt+1] = 0xFF;
                }
                widgetCnt += 2;
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

        /* Update On/Off State */
        `$INSTANCE_NAME`_CheckIsAnyWidgetActive();

        /* Copy OnMask */
        for(i=0; i < `$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT; i++)
        {
            outbox->onMask[i]  = `$INSTANCE_NAME`_SensorOnMask[i];
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to getting commands from EzI2C buffer. 
    *  
    * Parameters:
    *  None
    *
    * Return:
    *  Returns command from tuner.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_ReadCommand(void)
    {
        return ((uint8)`$EzI2CInstanceName`_EzBufReadByte((uint32)0u));
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to writing command for tuner into EzI2C buffer. 
    *  
    * Parameters:
    *  Command that need to be executed by tuner.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_WriteCommand(uint32 cmd)
    {
        uint32 tmp_cmd = cmd | `$EzI2CInstanceName`_EzBufReadByte((uint32)0u); 
        `$EzI2CInstanceName`_EzBufWriteByte((uint32)0u, tmp_cmd);
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ClearCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to clearing command in EzI2C buffer after execution. 
    *  
    * Parameters:
    *  Flags that need to be cleared.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ClearCommand(uint32 cmd)
    {
        uint32 tmp_cmd = ~cmd & `$EzI2CInstanceName`_EzBufReadByte((uint32)0u); 
        `$EzI2CInstanceName`_EzBufWriteByte((uint32)0u, tmp_cmd);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TxData
    ********************************************************************************
    *
    * Summary:
    *  Transmission of data from target to the tuner. 
    *  
    * Parameters:
    *  Pointer to the outbox buffer.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_TxData(volatile `$INSTANCE_NAME`_OUTBOX *outbox)
    {
        uint32 cmdWaitTimer;
        uint16 outboxIndex = 0u;
        uint8  txBufferIndex = 1u;
        uint8 *outboxPtr = (uint8*)outbox;
        
        while((outboxIndex < outbox->size) && (!((`$INSTANCE_NAME`_START_SCAN | `$INSTANCE_NAME`_RESEND_REQ | `$INSTANCE_NAME`_HAVE_MSG) & `$INSTANCE_NAME`_ReadCommand())))
        {
            txBufferIndex = 1u;
            cmdWaitTimer = 0u;
            
            while((txBufferIndex < 32u) && (outboxIndex < `$INSTANCE_NAME`_OUTBOX_SIZE))
            {
                `$EzI2CInstanceName`_EzBufWriteByte(txBufferIndex, outboxPtr[outboxIndex]);
                txBufferIndex++;
                outboxIndex++;
            }
            if(outboxIndex < 32u)
            {
                `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_START_FRAME);
            }
            if(outboxIndex == outbox->size)
            {
                `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_END_FRAME);
            }
            else
            {
                `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_NEXT_FRAME);
            }
            
            while(!((`$INSTANCE_NAME`_START_SCAN | `$INSTANCE_NAME`_READY | `$INSTANCE_NAME`_RESEND_REQ | `$INSTANCE_NAME`_HAVE_MSG) & `$INSTANCE_NAME`_ReadCommand()))
            {
                cmdWaitTimer++;
            }
            `$INSTANCE_NAME`_ClearCommand(`$INSTANCE_NAME`_READY);
        }
    }
    
	#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING)
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_RxData
    ********************************************************************************
    *
    * Summary:
    *  Transmision data from tuner to target. 
    *  
    * Parameters:
    *  Pointer to the inbox buffer.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
	    void `$INSTANCE_NAME`_RxData(volatile `$INSTANCE_NAME`_INBOX *inbox)
	    {
	        uint8 *inboxPtr = (uint8*)inbox;
	        uint8  txBufferIndex = 0u;
	        
	        for(txBufferIndex = 0u; txBufferIndex < `$INSTANCE_NAME`_INBOX_SIZE; txBufferIndex++)
	        {
	            inboxPtr[txBufferIndex] = `$EzI2CInstanceName`_EzBufReadByte(txBufferIndex + 1u);
	        }
	    }
	#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_MANUAL_TUNING) */
	
#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

/* [] END OF FILE */
