/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (`$INSTANCE_NAME`_RX_ENABLED || `$INSTANCE_NAME`_HD_ENABLED) && \
     (`$INSTANCE_NAME`_RXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_rxBuffer - RAM buffer pointer for save received data.
    *  `$INSTANCE_NAME`_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  `$INSTANCE_NAME`_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  `$INSTANCE_NAME`_rxBufferOverflow - software overflow flag. Set to one
    *     when `$INSTANCE_NAME`_rxBufferWrite index overtakes
    *     `$INSTANCE_NAME`_rxBufferRead index.
    *  `$INSTANCE_NAME`_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when `$INSTANCE_NAME`_rxBufferWrite is equal to
    *    `$INSTANCE_NAME`_rxBufferRead
    *  `$INSTANCE_NAME`_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  `$INSTANCE_NAME`_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START `$INSTANCE_NAME`_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = `$INSTANCE_NAME`_RXSTATUS_REG;

        if((readData & (`$INSTANCE_NAME`_RX_STS_BREAK | `$INSTANCE_NAME`_RX_STS_PAR_ERROR |
                        `$INSTANCE_NAME`_RX_STS_STOP_ERROR | `$INSTANCE_NAME`_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START `$INSTANCE_NAME`_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & `$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (`$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED)
                if(`$INSTANCE_NAME`_rxAddressMode == (uint8)`$INSTANCE_NAME`__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & `$INSTANCE_NAME`_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & `$INSTANCE_NAME`_RX_STS_ADDR_MATCH) != 0u)
                        {
                            `$INSTANCE_NAME`_rxAddressDetected = 1u;
                        }
                        else
                        {
                            `$INSTANCE_NAME`_rxAddressDetected = 0u;
                        }
                    }

                    readData = `$INSTANCE_NAME`_RXDATA_REG;
                    if(`$INSTANCE_NAME`_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        `$INSTANCE_NAME`_rxBuffer[`$INSTANCE_NAME`_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    `$INSTANCE_NAME`_rxBuffer[`$INSTANCE_NAME`_rxBufferWrite] = `$INSTANCE_NAME`_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                `$INSTANCE_NAME`_rxBuffer[`$INSTANCE_NAME`_rxBufferWrite] = `$INSTANCE_NAME`_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(`$INSTANCE_NAME`_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    `$INSTANCE_NAME`_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                `$INSTANCE_NAME`_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(`$INSTANCE_NAME`_rxBufferWrite >= `$INSTANCE_NAME`_RXBUFFERSIZE)
                {
                    `$INSTANCE_NAME`_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(`$INSTANCE_NAME`_rxBufferWrite == `$INSTANCE_NAME`_rxBufferRead)
                {
                    `$INSTANCE_NAME`_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(`$INSTANCE_NAME`_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        `$INSTANCE_NAME`_RXSTATUS_MASK_REG  &= (uint8)~`$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(`$INSTANCE_NAME`_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End `$INSTANCE_NAME`_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = `$INSTANCE_NAME`_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START `$INSTANCE_NAME`_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End `$INSTANCE_NAME`_RX_ENABLED && (`$INSTANCE_NAME`_RXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH) */


#if(`$INSTANCE_NAME`_TX_ENABLED && (`$INSTANCE_NAME`_TXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_txBuffer - RAM buffer pointer for transmit data from.
    *  `$INSTANCE_NAME`_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  `$INSTANCE_NAME`_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START `$INSTANCE_NAME`_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((`$INSTANCE_NAME`_txBufferRead != `$INSTANCE_NAME`_txBufferWrite) &&
             ((`$INSTANCE_NAME`_TXSTATUS_REG & `$INSTANCE_NAME`_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(`$INSTANCE_NAME`_txBufferRead >= `$INSTANCE_NAME`_TXBUFFERSIZE)
            {
                `$INSTANCE_NAME`_txBufferRead = 0u;
            }

            `$INSTANCE_NAME`_TXDATA_REG = `$INSTANCE_NAME`_txBuffer[`$INSTANCE_NAME`_txBufferRead];

            /* Set next pointer. */
            `$INSTANCE_NAME`_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START `$INSTANCE_NAME`_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End `$INSTANCE_NAME`_TX_ENABLED && (`$INSTANCE_NAME`_TXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH) */


/* [] END OF FILE */
