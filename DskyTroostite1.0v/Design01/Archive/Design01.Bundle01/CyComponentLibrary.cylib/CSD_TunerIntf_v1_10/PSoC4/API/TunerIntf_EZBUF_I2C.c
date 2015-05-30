/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZBUFI2C.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  EZI2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_EZBUF_MODE.h"

/***************************************
*     HW buffer initialization
****************************************/

uint32 volatile * const `$INSTANCE_NAME`_ezBufferHw = `$INSTANCE_NAME`_EZBUF_DATA00_PTR;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzBufI2CInit
********************************************************************************
*
* Summary:
*  Configures the SCB for EZ Buffred I2C operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzBufI2CInit(void)
{
    /* Configure EZI2C interface */
    `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_CTRL;
    `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_I2C_CTRL;

    /* Adjust SDA filter settigns for EC_AM = 1 */
    `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);

    /* Configure RX direction */
    `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_CTRL;
    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_FIFO_CTRL;

    /* Configure slave address */
    `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_MATCH;

    /* Configure TX direction */
    `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_TX_CTRL;
    `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_TX_FIFO_CTRL;

    /* Configure interrupt sources */
    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_I2C_EC_MASK;
    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_SPI_EC_MASK;
    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_SLAVE_MASK;
    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_MASTER_MASK;
    `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_RX_MASK;
    `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_TX_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzBufWriteByte
********************************************************************************
*
* Summary:
*  Writes one byte of data to the component hardware buffer at offset addr.
*  The status of write operation is returned: zero value if write operation was
*  successful and non-zero otherwise.
*  The clocking mode has influence on the function implementation:
*   - Internally clocked: the write operations are always successful and zero
*     value returned.
*    - Externally clocked: in case of conflict between internal and external
*     logic the write operation is ignored and the non-zero value is returned
*     by the function.
*
* Parameters:
*  addr:  Address within the buffer. The address range is not checked.
*  data:  The byte tobe written.
*
* Return:
*  Status of write buffer operation: zero - means succesfull, any other value
*  means failure.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzBufWriteByte(uint32 addr, uint32 dataByte)
{
   `$INSTANCE_NAME`_ezBufferHw[addr] = dataByte; /* Write the byte */

    return(0u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzBufReadByte
********************************************************************************
*
* Summary:
*  Reads one byte of data from the component hardware buffer at offset addr.
*  The error value (0xFFFF FFFF) is returned when read operation was failed,
*  the valid value is byte (0x0000 00XX).
*  The clocking mode has influence on the function implementation:
*   - Internally clocked: the read operations are always successful and zero
*     value returned.
*   - Externally clocked: in case of conflict between internal and external
*     logic the value (0xFFFF FFFF) is returned by the function.
*
* Parameters:
*  addr:  Address within the buffer. The address range is not checked.
*
* Return:
*  The byte read from buffer or error condition.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzBufReadByte(uint32 addr)
{
    uint32 theByte;
    
    theByte = `$INSTANCE_NAME`_ezBufferHw[addr];
    /* Read the byte */
    return(theByte);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzBufGetEzAddress
********************************************************************************
*
* Summary:
*  Returns the address which was most recently accessed (written or read) by
*  external master.
*  When externally clocked mode is selected function returns zero as hardware
*  does not support this option in this mode.
*
* Parameters:
*  None
*
* Return:
*  Address which was most recently accessed (written or read) by external
*  master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzBufGetEzAddress(void)
{
    uint32 addr;

    /* Only valied for internally clocked operations */
    addr = `$INSTANCE_NAME`_GET_I2C_STATUS_EZBUF_ADDRESS;

    return(addr);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzBufIsBusBusy
********************************************************************************
*
* Summary:
*  Checks the state of the EzBuf interface and determines whether a transaction 
*  is active.
*  When externally clocked mode is selected function returns zero as hardware
*  does not support this option in this mode.
*
* Parameters:
*  None
*
* Return:
*  Bus status: 0 - bus is free or 1 - bus is busy.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzBufIsBusBusy(void)
{
    uint32 status;

    /* Only valied for internally clocked operations */
    status = (uint32) `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY);
   
    return(status);
}


/* [] END OF FILE */
