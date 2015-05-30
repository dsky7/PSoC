/*******************************************************************************
* File Name: `$INSTANCE_NAME`_UART.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "`$INSTANCE_NAME`_SPI_UART_PVT.h"


#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const `$INSTANCE_NAME`_UART_INIT_STRUCT `$INSTANCE_NAME`_configUart =
    {
        `$INSTANCE_NAME`_UART_SUB_MODE,
        `$INSTANCE_NAME`_UART_DIRECTION,
        `$INSTANCE_NAME`_UART_DATA_BITS_NUM,
        `$INSTANCE_NAME`_UART_PARITY_TYPE,
        `$INSTANCE_NAME`_UART_STOP_BITS_NUM,
        `$INSTANCE_NAME`_UART_OVS_FACTOR,
        `$INSTANCE_NAME`_UART_IRDA_LOW_POWER,
        `$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_UART_RETRY_ON_NACK,
        `$INSTANCE_NAME`_UART_IRDA_POLARITY,
        `$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR,
        `$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR,
        `$INSTANCE_NAME`_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        `$INSTANCE_NAME`_UART_MP_MODE_ENABLE,
        `$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS,
        `$INSTANCE_NAME`_UART_MP_RX_ADDRESS,
        `$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK,
        (uint32) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL,
        `$INSTANCE_NAME`_UART_INTR_RX_MASK,
        `$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL,
        `$INSTANCE_NAME`_UART_INTR_TX_MASK,
        `$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartInit(const `$INSTANCE_NAME`_UART_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad function parameter */
        }
        else
        {
            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_UART, config->mode, config->direction);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_UART;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            `$INSTANCE_NAME`_rxBuffer      =         config->rxBuffer;
            `$INSTANCE_NAME`_rxDataBits    = (uint8) config->dataBits;
            `$INSTANCE_NAME`_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            `$INSTANCE_NAME`_txBuffer      =         config->txBuffer;
            `$INSTANCE_NAME`_txDataBits    = (uint8) config->dataBits;
            `$INSTANCE_NAME`_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(`$INSTANCE_NAME`_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                `$INSTANCE_NAME`_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (`$INSTANCE_NAME`_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (`$INSTANCE_NAME`_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                `$INSTANCE_NAME`_CTRL_REG  = `$INSTANCE_NAME`_GET_CTRL_OVS(config->oversample);
            }

            `$INSTANCE_NAME`_CTRL_REG     |= `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             `$INSTANCE_NAME`_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            `$INSTANCE_NAME`_UART_CTRL_REG = `$INSTANCE_NAME`_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            `$INSTANCE_NAME`_UART_RX_CTRL_REG = `$INSTANCE_NAME`_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
            {
               `$INSTANCE_NAME`_UART_RX_CTRL_REG |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED;
            }

            `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                `$INSTANCE_NAME`_GET_UART_RX_CTRL_ENABLED(config->direction);

            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            `$INSTANCE_NAME`_UART_TX_CTRL_REG = `$INSTANCE_NAME`_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                `$INSTANCE_NAME`_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
            {
               `$INSTANCE_NAME`_UART_TX_CTRL_REG |= `$INSTANCE_NAME`_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED;
            }

            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                `$INSTANCE_NAME`_GET_UART_TX_CTRL_ENABLED(config->direction);

            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);



            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, `$INSTANCE_NAME`_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, &`$INSTANCE_NAME`_UART_WAKEUP_ISR);
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_RX_MASK_REG     = config->rxInterruptMask;
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            `$INSTANCE_NAME`_rxBufferHead     = 0u;
            `$INSTANCE_NAME`_rxBufferTail     = 0u;
            `$INSTANCE_NAME`_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            `$INSTANCE_NAME`_txBufferHead = 0u;
            `$INSTANCE_NAME`_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartInit(void)
    {
        /* Configure UART interface */
        `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        `$INSTANCE_NAME`_UART_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        `$INSTANCE_NAME`_UART_RX_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_RX_CTRL;
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_UART_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_RX_FIFO_CTRL;
        `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        `$INSTANCE_NAME`_UART_TX_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_UART_TX_CTRL;
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_UART_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_UART_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with UART handler but do not enable it */
    #if(`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
        CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_SPI_UART_ISR);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, `$INSTANCE_NAME`_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(`$INSTANCE_NAME`_RX_WAKE_ISR_NUMBER, &`$INSTANCE_NAME`_UART_WAKEUP_ISR);
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_SPI_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_UART_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_UART_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_UART_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_UART_DEFAULT_INTR_TX_MASK;

    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_rxBufferHead     = 0u;
        `$INSTANCE_NAME`_rxBufferTail     = 0u;
        `$INSTANCE_NAME`_rxBufferOverflow = 0u;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_txBufferHead = 0u;
        `$INSTANCE_NAME`_txBufferTail = 0u;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the Multiprocessor
*  mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = `$INSTANCE_NAME`_RX_MATCH_REG;

    matchReg &= ((uint32) ~`$INSTANCE_NAME`_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & `$INSTANCE_NAME`_RX_MATCH_ADDR_MASK)); /* Set address  */

    `$INSTANCE_NAME`_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = `$INSTANCE_NAME`_RX_MATCH_REG;

    matchReg &= ((uint32) ~`$INSTANCE_NAME`_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << `$INSTANCE_NAME`_RX_MATCH_MASK_POS));

    `$INSTANCE_NAME`_RX_MATCH_REG = matchReg;
}


#if(`$INSTANCE_NAME`_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from the software receive
    *    buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Read data only if there is data to read */
        if(0u != `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
        {
            rxData = `$INSTANCE_NAME`_SpiUartReadRxData();
        }

        if(`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: return zero */
            `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the received byte
    *  and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved from the RX FIFO.
    *     Undefined data will be returned if the RX FIFO is empty.
    *   - The RX software buffer is enabled: returns data element from the software receive
    *     buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 15-8 contains status and bits 7-0 contains the next data element from
    *  receive buffer. If the bits 15-8 are non-zero, an error has occurred.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = `$INSTANCE_NAME`_SpiUartDisableIntRx();

        if(0u != `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
        {
             /*
             * Enable interrupt to receive more bytes: at least one byte is in
             * buffer.
             */
            `$INSTANCE_NAME`_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = `$INSTANCE_NAME`_SpiUartReadRxData();
        }
        else
        {
            /*
            * Read byte directly from RX FIFO: the underflow is raised in case
            * of empty. In other case the first received byte will be read.
            */
            rxData = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

            /*
            * Enable interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine in case
            * the byte was received and read above.
            */
            `$INSTANCE_NAME`_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (`$INSTANCE_NAME`_GetRxInterruptSource() & `$INSTANCE_NAME`_INTR_RX_ERR);
        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ERR);

        /*
        * Put together data and error status:
        * MP mode and accept address: the 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }

#endif /* (`$INSTANCE_NAME`_UART_RX_DIRECTION) */


#if(`$INSTANCE_NAME`_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Block the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            `$INSTANCE_NAME`_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and line feed (0x0A)
    *  into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartPutCRLF(uint32 txDataByte)
    {
        `$INSTANCE_NAME`_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        `$INSTANCE_NAME`_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        `$INSTANCE_NAME`_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }
#endif /* (`$INSTANCE_NAME`_UART_TX_DIRECTION) */


#if(`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the active
    *  mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. On GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        `$INSTANCE_NAME`_UART_RX_CTRL_REG |= `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        `$INSTANCE_NAME`_RxWakeClearPendingInt();
        `$INSTANCE_NAME`_RxWakeEnableInt();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt remains
    *  active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
        `$INSTANCE_NAME`_RxWakeDisableInt();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST) */


#if(`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup event. This
    *  event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is only disabled
        * by `$INSTANCE_NAME`_UartRestoreConfig() call.
        */
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */
    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (`$INSTANCE_NAME`_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
