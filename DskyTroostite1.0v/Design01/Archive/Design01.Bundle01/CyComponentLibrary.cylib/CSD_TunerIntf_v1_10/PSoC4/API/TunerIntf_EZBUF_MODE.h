/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZBUF_MODE.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  EZI2C and EZSPI modes.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZBUF_MODE_`$INSTANCE_NAME`_H)
#define CY_EZBUF_MODE_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*   EZBUFI2C Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_EZBUF_I2C_OPERATION_MODE       (`$EzBufI2cOperationMode`u)
#define `$INSTANCE_NAME`_EZBUF_I2C_WAIT_STATES_ENABLE   (`$EzBufI2cWaitStatesEnable`u)
#define `$INSTANCE_NAME`_EZBUF_I2C_MEDIAN_FILTER_ENABLE (`$EzBufI2cMedianFilterEnable`u)
#define `$INSTANCE_NAME`_EZBUF_I2C_SLAVE_ADDRESS        (`$EzBufI2cSlaveAddress`u)
#define `$INSTANCE_NAME`_EZBUF_I2C_SLAVE_ADDRESS_MASK   (`$EzBufI2cSlaveAddressMask`u)


/***************************************
*        Function Prototypes
***************************************/

/* EZI2C specific functions */
void `$INSTANCE_NAME`_EzBufI2CInit(void);

/* Data processing */
uint32 `$INSTANCE_NAME`_EzBufWriteByte(uint32 addr, uint32 dataByte);
uint32 `$INSTANCE_NAME`_EzBufReadByte(uint32 addr);

/* Service functions */
uint32 `$INSTANCE_NAME`_EzBufGetEzAddress(void);
uint32 `$INSTANCE_NAME`_EzBufIsBusBusy(void);

/***************************************
*             API Constants
***************************************/

/* Operaion mode enum. */
#define `$INSTANCE_NAME`_EZBUF_INTERNALLY_CLOCKED  (0u)
#define `$INSTANCE_NAME`_EZBUF_EXTERNALLY_CLOCKED  (1u)

/* Wakeup action enum. */
#define `$INSTANCE_NAME`_EZBUF_I2C_WAKE_CLOCK_STRETCH   (0u)
#define `$INSTANCE_NAME`_EZBUF_I2C_WAKE_ADDRESS_NACK    (1u)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint32 volatile * const `$INSTANCE_NAME`_ezBufferHw;


/***************************************
*  Common EZI2C/EZSPI Register Settings
***************************************/

#define `$INSTANCE_NAME`_EZBUF_RX_CTRL  ((`$INSTANCE_NAME`_FIFO_SIZE - 1u)   | \
                                          `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST | \
                                          `$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_EZBUF_TX_CTRL  ((`$INSTANCE_NAME`_FIFO_SIZE - 1u)   | \
                                          `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST | \
                                          `$INSTANCE_NAME`_TX_CTRL_ENABLED)


/***************************************
*      EZI2C Register Settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_EZBUF_I2C     (`$INSTANCE_NAME`_CTRL_EZBUF_MODE | \
                                             `$INSTANCE_NAME`_CTRL_MODE_I2C)

#define `$INSTANCE_NAME`_EZBUF_I2C_I2C_CTRL (`$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE | \
                                             `$INSTANCE_NAME`_I2C_CTRL_S_READY_ADDR_ACK | \
                                             `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK | \
                                             `$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE)


/***************************************
*      EZI2C Init Register Settings
***************************************/

#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_CTRL \
                                (`$INSTANCE_NAME`_GET_CTRL_EC_OP_MODE(`$INSTANCE_NAME`_EZBUF_I2C_OPERATION_MODE) | \
                                 `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(`$INSTANCE_NAME`_EZBUF_I2C_OPERATION_MODE) | \
                                 `$INSTANCE_NAME`_CTRL_EZBUF_I2C)
                                 
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_I2C_CTRL           (`$INSTANCE_NAME`_EZBUF_I2C_I2C_CTRL)

#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_MATCH \
                                (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(`$INSTANCE_NAME`_EZBUF_I2C_SLAVE_ADDRESS) | \
                                 `$INSTANCE_NAME`_GET_RX_MATCH_MASK(`$INSTANCE_NAME`_EZBUF_I2C_SLAVE_ADDRESS_MASK))

#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_CTRL \
                        (`$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(`$INSTANCE_NAME`_EZBUF_I2C_MEDIAN_FILTER_ENABLE) | \
                         `$INSTANCE_NAME`_EZBUF_RX_CTRL)

#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_TX_CTRL  (`$INSTANCE_NAME`_EZBUF_TX_CTRL)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_RX_FIFO_CTRL (0u)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_TX_FIFO_CTRL (0u)

/* Interrupt sources not used */
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_SLAVE_MASK  (`$INSTANCE_NAME`_NO_INTR_SOURCES)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_MASTER_MASK (`$INSTANCE_NAME`_NO_INTR_SOURCES)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_SPI_EC_MASK (`$INSTANCE_NAME`_NO_INTR_SOURCES)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_I2C_EC_MASK (`$INSTANCE_NAME`_NO_INTR_SOURCES)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_RX_MASK     (`$INSTANCE_NAME`_NO_INTR_SOURCES)
#define `$INSTANCE_NAME`_EZBUF_I2C_DEFAULT_INTR_TX_MASK     (`$INSTANCE_NAME`_NO_INTR_SOURCES)


#endif /* (CY_EZBUF_MODE_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
