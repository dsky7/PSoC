/*******************************************************************************
* File Name: `$INSTANCE_NAME`_boot.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Boot loader API for USBFS Component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*    Bootloader Variables
***************************************/

static uint8  `$INSTANCE_NAME`_started = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the component and enables the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function starts the USB with 3V or 5V operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStart(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`
{
    CyGlobalIntEnable;      /* Enable Global Interrupts */

    /*Start USBFS Operation/device 0 and with 5V or 3V operation depend on Voltage Configuration in DWR */
    `$INSTANCE_NAME`_Start(0u, `$INSTANCE_NAME`_DWR_VDDD_OPERATION);

    /* USB component started, the correct enumeration will be checked in first Read operation */
    `$INSTANCE_NAME`_started = 1u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStop.
********************************************************************************
*
* Summary:
*  Disable the component and disable the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStop(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`
{
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommReset.
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication Buffers.
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
void `$INSTANCE_NAME`_CyBtldrCommReset(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`
{
    `$INSTANCE_NAME`_EnableOutEP(`$INSTANCE_NAME`_BTLDR_OUT_EP);  /* Enable the OUT endpoint */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite.
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the boot loader host. The function will
*  handle polling to allow a block of data to be completely sent to the host
*  device.
*
* Parameters:
*  pData:    A pointer to the block of data to send to the device
*  size:     The number of bytes to write.
*  count:    Pointer to an unsigned short variable to write the number of
*             bytes actually written.
*  timeOut:  Number of units to wait before returning because of a timeout.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`
{
    cystatus retCode;
    uint16 timeoutMs;

    timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS check to number 1mS checks */
    
    /* Enable IN transfer */
    `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_BTLDR_IN_EP, pData, `$INSTANCE_NAME`_BTLDR_SIZEOF_READ_BUFFER);

    /* Wait for the master to read it. */
    while ((`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_IN_EP) == `$INSTANCE_NAME`_IN_BUFFER_FULL) &&
           (0u != timeoutMs))
    {
        CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    if (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_IN_EP) == `$INSTANCE_NAME`_IN_BUFFER_FULL)
    {
        retCode = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        retCode = CYRET_SUCCESS;
    }

    return(retCode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommRead.
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the boot loader host. The function will
*  handle polling to allow a block of data to be completely received from the
*  host device.
*
* Parameters:
*  pData:    A pointer to the area to store the block of data received
*             from the device.
*  size:     The number of bytes to read.
*  count:    Pointer to an unsigned short variable to write the number
*             of bytes actually read.
*  timeOut:  Number of units to wait before returning because of a timeOut.
*            Timeout is measured in 10s of ms.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`
{
    cystatus retCode;
    uint16 timeoutMs;

    timeoutMs = ((uint16) 10u * timeOut);  /* Convert from 10mS check to number 1mS checks */
    
    if (size > `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER;
    }

    /* Wait on enumeration in first time */
    if (0u != `$INSTANCE_NAME`_started)
    {
        /* Wait for Device to enumerate */
        while ((0u ==`$INSTANCE_NAME`_GetConfiguration()) && (0u != timeoutMs))
        {
            CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
            timeoutMs--;
        }
        
        /* Enable first OUT, if enumeration complete */
        if (0u != `$INSTANCE_NAME`_GetConfiguration())
        {
            (void) `$INSTANCE_NAME`_IsConfigurationChanged();  /* Clear configuration changes state status */
            `$INSTANCE_NAME`_CyBtldrCommReset();
            `$INSTANCE_NAME`_started = 0u;
        }
    }
    else /* Check for configuration changes, has been done by Host */
    {
        if (0u != `$INSTANCE_NAME`_IsConfigurationChanged()) /* Host could send double SET_INTERFACE request or RESET */
        {
            if (0u != `$INSTANCE_NAME`_GetConfiguration())   /* Init OUT endpoints when device reconfigured */
            {
                `$INSTANCE_NAME`_CyBtldrCommReset();
            }
        }
    }
    
    timeoutMs = ((uint16) 10u * timeOut); /* Re-arm timeout */
    
    /* Wait on next packet */
    while((`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_OUT_EP) != `$INSTANCE_NAME`_OUT_BUFFER_FULL) && \
          (0u != timeoutMs))
    {
        CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    /* OUT EP has completed */
    if (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_OUT_EP) == `$INSTANCE_NAME`_OUT_BUFFER_FULL)
    {
        *count = `$INSTANCE_NAME`_ReadOutEP(`$INSTANCE_NAME`_BTLDR_OUT_EP, pData, size);
        retCode = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        retCode = CYRET_TIMEOUT;
    }
    
    return(retCode);
}

#endif /*  CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME` */


/* [] END OF FILE */
