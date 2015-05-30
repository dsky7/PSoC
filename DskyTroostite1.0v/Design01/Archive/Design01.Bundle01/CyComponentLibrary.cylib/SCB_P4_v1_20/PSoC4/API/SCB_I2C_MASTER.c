/*******************************************************************************
* File Name: `$INSTANCE_NAME`_I2C_MASTER.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C Master mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_I2C_PVT.h"

#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)

/***************************************
*      I2C Master Private Vars
***************************************/

/* Master variables */
volatile uint16 `$INSTANCE_NAME`_mstrStatus;      /* Master Status byte  */
volatile uint8  `$INSTANCE_NAME`_mstrControl;     /* Master Control byte */

/* Receive buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrRdBufPtr;   /* Pointer to Master Read buffer */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufSize;  /* Master Read buffer size       */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufIndex; /* Master Read buffer Index      */

/* Transmit buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrWrBufPtr;   /* Pointer to Master Write buffer */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufSize;  /* Master Write buffer size       */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndex; /* Master Write buffer Index      */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteBuf
********************************************************************************
*
* Summary:
* Automatically writes an entire buffer of data to a slave device.
* Once the data transfer is initiated by this function, further data transfer
* is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_WR_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer of data to be sent.
*  cnt:       Size of buffer to send.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrWrBufPtr - used to store pointer to master write buffer.
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*  `$INSTANCE_NAME`_mstrWrBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != wrData)  /* Check buffer pointer */
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_DisableInt();

            /* Check bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT;
                              errStatus  = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }


    /* Check if master is ready to start  */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        /* Set up write transaction */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_ADDR;
        `$INSTANCE_NAME`_mstrWrBufIndexTmp = 0u;
        `$INSTANCE_NAME`_mstrWrBufIndex    = 0u;
        `$INSTANCE_NAME`_mstrWrBufSize     = cnt;
        `$INSTANCE_NAME`_mstrWrBufPtr      = (volatile uint8 *) wrData;
        `$INSTANCE_NAME`_mstrControl       = (uint8) mode;

        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT;

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
        /* The TX and RX FIFO have to be EMPTY */

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }

         /* Catch when address is sent */
        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
    }

    `$INSTANCE_NAME`_EnableInt();

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadBuf
********************************************************************************
*
* Summary:
*  Automatically reads an entire buffer of data from a slave device.
*  Once the data transfer is initiated by this function, further data transfer
*  is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_RD_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer where to put data from slave.
*  cnt:       Size of buffer to read.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrRdBufPtr - used to store pointer to master write buffer.
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master write
*  buffer.
*  `$INSTANCE_NAME`_mstrRdBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_DisableInt();

            /* Check bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT;
                              errStatus  =  `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check master ready to proceed */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        /* Set up read transaction */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_ADDR;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
        `$INSTANCE_NAME`_mstrRdBufSize  = cnt;
        `$INSTANCE_NAME`_mstrRdBufPtr   = (volatile uint8 *) rdData;
        `$INSTANCE_NAME`_mstrControl    = (uint8) mode;

        slaveAddress = (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress) | `$INSTANCE_NAME`_I2C_READ_FLAG);

        `$INSTANCE_NAME`_mstrStatus &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT;

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* The TX and RX FIFO have to be EMPTY */

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }

        /* Prepare reading */
        if(`$INSTANCE_NAME`_mstrRdBufSize < `$INSTANCE_NAME`_I2C_FIFO_SIZE) /* Reading byte-by-byte */
        {
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
        }
        else /* Reading use RX FIFO */
        {
            `$INSTANCE_NAME`_ENABLE_MASTER_AUTO_DATA_ACK;
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
        }
    }

    `$INSTANCE_NAME`_EnableInt();

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStart
********************************************************************************
*
* Summary:
*  Generates Start condition and sends slave address with read/write bit.
*  Disables the I2C interrupt.
*  This function is blocking and does not return until start condition and
*  address byte are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Erorr status.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32  resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Start condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
    {
        /* If bus is free, generate Start condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY;
        }
        else
        {
            `$INSTANCE_NAME`_DisableInt();

            slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

            if(0u == bitRnW) /* Write direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
            }
            else /* Read direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                         slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
            }

            /* The TX and RX FIFO have to be EMPTY */

            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress; /* Put address in TX FIFO */
            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;


            while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
            {
                /*
                * Write: wait until address has been transferred
                * Read : wait until address has been transferred, data byte is going to RX FIFO as well.
                */
            }

            /* Check the results of the address phase */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
            }
            else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
            }
            else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                             resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
            }
            else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is else condition */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                             resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
            }

            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            if(0u != resetIp)
            {
                `$INSTANCE_NAME`_SCB_SW_RESET;
            }
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendRestart
********************************************************************************
*
* Summary:
*  Generates Restart condition and sends slave address with read/write bit.
*  This function is blocking and does not return until start condition and
*  address are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Error status
*
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating ReStart condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        if(0u == bitRnW) /* Write direction */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
        }
        else  /* Read direction */
        {
            `$INSTANCE_NAME`_state  = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                      slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
        }

        /* The TX and RX FIFO have to be EMPTY */

        /* Clean-up interrupt status */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* Proper ReStart sequence is: generate ReStart then put address byte in the TX FIFO.
        * Otherwise master treats address in the TX FIFO as data byte if previous transfer is write.
        * The write transfer continue instead of ReStart.
        */
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;

        while(`$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START))
        {
            /* Wait until ReStart has been generated */
        }

        /* Put address into TX FIFO */
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;

        /* Wait for address to be transferred */
        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until address has been transferred */
        }

        /* Check results of address phase */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is else condition */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStop
********************************************************************************
*
* Summary:
*  Generates Stop condition on the bus.
*  At least one byte has to be read if start or restart condition with read
*  direction was generated before.
*  This function is blocking and does not return until a stop condition
*  is generated or error occurred.
*
* Parameters:
*  None
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*  For read transfer, at least one byte has to be read before Stop generation.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStop(void)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Stop condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        /*
        * Write direction: generates Stop
        * Read  direction: generates NACK and Stop
        */
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_STOP;

        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until Stop has been generated */
        }

        /* Check Stop generation */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
            resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR is set */
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
            resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteByte
********************************************************************************
*
* Summary:
*  Sends one byte to a slave.
*  This function is blocking and does not return until byte is transmitted
*  or error occurred.
*
* Parameters:
*  data: The data byte to send to the slave.
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteByte(uint32 theByte)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before write byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = theByte;

        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until byte has been transferred */
        }

        /* Check the results after byte was sent */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR set is */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = `$INSTANCE_NAME`_I2C_RESET_ERROR;
        }

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK      |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadByte
********************************************************************************
*
* Summary:
*  Reads one byte from a slave and ACKs or NAKs received byte.
*  This function does not generate NAK explicitly. The following call
*  SCB_I2CMasterSendStop() or SCB_I2CMasterSendRestart() will generate NAK and
*  Stop or ReStart condition appropriately.
*  This function is blocking and does not return until byte is received
*  or error occurred.
*
* Parameters:
*  ackNack: Response to received byte.
*
* Return:
*  Byte read from the slave. In case of error the MSB of returned data
*  is set to 1.
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling this
*  function. This function does nothing and returns invalid byte value
*  if Start or ReStart conditions failed before this function was called.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadByte(uint32 ackNack)
{
    uint32 theByte;

    /* Return invalid byte in case BUS_ERR happen during receiving */
    theByte = `$INSTANCE_NAME`_I2C_INVALID_BYTE;

    /* Check FSM state before read byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        while((!`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY)) &&
              (!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR)))
        {
            /* Wait until byte has been received */
        }

        /* Check the results after the byte was sent */
        if(`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
        {
            theByte = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);

            if(0u == ackNack)
            {
                `$INSTANCE_NAME`_I2C_MASTER_GENERATE_ACK;
            }
            else
            {
                /* NACK is generated by Stop or ReStart command*/
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
            }
        }
        else
        {
            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            `$INSTANCE_NAME`_SCB_SW_RESET;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that has been transferred with an
*  SCB_I2CMasterReadBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  the byte count transferred so far.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetReadBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that have been transferred with an
*  SCB_I2CMasterWriteBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  zero unit transfer completion.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetWriteBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearReadBuf(void)
{
    `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearWriteBuf(void)
{
    `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= (uint16) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterStatus
********************************************************************************
*
* Summary:
*  Returns the master's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterStatus(void)
{
    uint32 status;

    status = (uint32) `$INSTANCE_NAME`_mstrStatus;

    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        /* Add status of master pending transaction: MSTAT_XFER_INP */
        status |= (uint32) `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP;
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearStatus
********************************************************************************
*
* Summary:
*  Clears all status flags and returns the master status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterClearStatus(void)
{
    uint32 status;

    /* Read and clear master status */
    status = (uint32) `$INSTANCE_NAME`_mstrStatus;
    `$INSTANCE_NAME`_mstrStatus = `$INSTANCE_NAME`_I2C_MSTAT_CLEAR;

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CReStartGeneration
********************************************************************************
*
* Summary:
*  Generates a ReStart condition:
*  SCB IP V1 and later: Generates ReStart using the scb IP functionality
*    Sets the I2C_MASTER_CMD_M_START and I2C_MASTER_CMD_M_NACK (if the previous
*    transaction was read) bits in the SCB.I2C_MASTER_CMD register. This combination
*    forces the master to generate ReStart.
*
*  SCB IP V0: Generates Restart using the GPIO and scb IP functionality.
*   After the master completes write or read, the SCL is stretched. The master waits
*   until SDA line is released by the slave. Then the GPIO function is enabled and
*   the scb IP disabled as it already does not drive the bus. In case of the previous
*   transfer was read, the NACK is generated by the GPIO. The delay of tLOW is
*   added to manage the hold time. Set I2C_M_CMD.START and enable the scb IP.
*   The ReStart generation is started after the I2C function is enabled for the SCL.
*   Note1: the scb IP due re-enable generates Start but on the I2C bus it
*          appears as ReStart.
*   Note2: the I2C_M_CMD.START is queued if scb IP is disabled.
*   Note3: the I2C_STATUS_M_READ is cleared is address was NACKed before.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  SCB IP V0: The NACK generation by the GPIO may cause a greater SCL period than
*  expected for the selected master data rate.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CReStartGeneration(void)
{
#if(`$INSTANCE_NAME`_CY_SCBIP_V0)
    /* Generates Restart use GPIO and scb IP functionality. Ticket ID#143715,
    ID#145238 and ID#173656 */
    uint32 status = `$INSTANCE_NAME`_I2C_STATUS_REG;

    while(`$INSTANCE_NAME`_WAIT_SDA_SET_HIGH)
    {
        /* Wait when slave release SDA line: SCL tHIGH is complete */
    }

    /* Prepare DR register to drive SCL line */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);

    /* Switch HSIOM to GPIO: SCL goes low */
    `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(`$INSTANCE_NAME`_HSIOM_GPIO_SEL);

    /* Disable SCB block */
    `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED;

    if(0u != (status & `$INSTANCE_NAME`_I2C_STATUS_M_READ))
    {
        /* Generate NACK use GPIO functionality */
        `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);
        CyDelayUs(`$INSTANCE_NAME`_I2C_TLOW_TIME); /* Count tLOW */

        `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_HIGH);
        while(`$INSTANCE_NAME`_WAIT_SCL_SET_HIGH)
        {
            /* Wait until slave releases SCL in case if it stretches */
        }
        CyDelayUs(`$INSTANCE_NAME`_I2C_THIGH_TIME); /* Count tHIGH */
    }

    /* Count tLOW as hold time for write and read */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_LOW);
    CyDelayUs(`$INSTANCE_NAME`_I2C_TLOW_TIME); /* Count tLOW */

    /* Set command for Start generation: it will appear */
    `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START;

    /* Enable SCB block */
    `$INSTANCE_NAME`_CTRL_REG |= (uint32) `$INSTANCE_NAME`_CTRL_ENABLED;

    /* Switch HSIOM to I2C: */
    `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(`$INSTANCE_NAME`_HSIOM_I2C_SEL);

    /* Revert SCL DR register */
    `$INSTANCE_NAME`_SET_I2C_SCL_DR(`$INSTANCE_NAME`_I2C_SCL_HIGH);
#else
    uint32 cmd;

    /* Generates ReStart use scb IP functionality */
    cmd  = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START;
    cmd |= `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_M_READ) ?
                (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK) : (0u);

    `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = cmd;
#endif /* (`$INSTANCE_NAME`_CY_SCBIP_V1) */
}


#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */


/* [] END OF FILE */
