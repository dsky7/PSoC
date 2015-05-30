/*******************************************************************************
* File Name: `$INSTANCE_NAME`_I2C.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
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


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 `$INSTANCE_NAME`_state;  /* Current state of I2C FSM */


#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const `$INSTANCE_NAME`_I2C_INIT_STRUCT `$INSTANCE_NAME`_configI2C =
    {
        `$INSTANCE_NAME`_I2C_MODE,
        `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW,
        `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH,
        `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS,
        `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK,
        `$INSTANCE_NAME`_I2C_ACCEPT_ADDRESS,
        `$INSTANCE_NAME`_I2C_WAKE_ENABLE
    };

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
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
    void `$INSTANCE_NAME`_I2CInit(const `$INSTANCE_NAME`_I2C_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad function parameter */
        }
        else
        {
            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_I2C, `$INSTANCE_NAME`_DUMMY_PARAM,
                                                                    `$INSTANCE_NAME`_DUMMY_PARAM);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_I2C;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL;

            `$INSTANCE_NAME`_mode          = (uint8) config->mode;
            `$INSTANCE_NAME`_acceptAddr    = (uint8) config->acceptAddr;

            /* Configure I2C interface */
            `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->acceptAddr) |
                                            `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE (config->enableWake);

            `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                                            `$INSTANCE_NAME`_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)  |
                                            `$INSTANCE_NAME`_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode)           |
                                            `$INSTANCE_NAME`_I2C_CTRL;

        #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

            /* Configure RX direction */
            `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                `$INSTANCE_NAME`_I2C_RX_CTRL;
            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_CLEAR_REG;

            /* Set default address and mask */
            `$INSTANCE_NAME`_RX_MATCH_REG    = ((`$INSTANCE_NAME`_I2C_SLAVE) ?
                                                (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (`$INSTANCE_NAME`_CLEAR_REG));


            /* Configure TX direction */
            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_I2C_TX_CTRL;
            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_I2C_ISR);

            /* Configure interrupt sources */
        #if(!`$INSTANCE_NAME`_CY_SCBIP_V1_I2C_ONLY)
            `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1_I2C_ONLY) */

            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;

            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = ((`$INSTANCE_NAME`_I2C_SLAVE) ?
                                                     (`$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK) :
                                                     (`$INSTANCE_NAME`_CLEAR_REG));

            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = ((`$INSTANCE_NAME`_I2C_MASTER) ?
                                                     (`$INSTANCE_NAME`_I2C_INTR_MASTER_MASK) :
                                                     (`$INSTANCE_NAME`_CLEAR_REG));

            /* Configure global variables */
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

            /* Internal slave variables */
            `$INSTANCE_NAME`_slStatus        = 0u;
            `$INSTANCE_NAME`_slRdBufIndex    = 0u;
            `$INSTANCE_NAME`_slWrBufIndex    = 0u;
            `$INSTANCE_NAME`_slOverFlowCount = 0u;

            /* Internal master variables */
            `$INSTANCE_NAME`_mstrStatus     = 0u;
            `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
            `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CInit(void)
    {
        /* Configure I2C interface */
        `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_CTRL;
        `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_I2C_CTRL;

    #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

        /* Configure RX direction */
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_I2C_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_I2C_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
    #if(!`$INSTANCE_NAME`_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_I2C_ISR);
    #endif /* (`$INSTANCE_NAME`_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!`$INSTANCE_NAME`_CY_SCBIP_V1_I2C_ONLY)
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1_I2C_ONLY) */

        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

    #if(`$INSTANCE_NAME`_I2C_SLAVE)
        /* Internal slave variable */
        `$INSTANCE_NAME`_slStatus        = 0u;
        `$INSTANCE_NAME`_slRdBufIndex    = 0u;
        `$INSTANCE_NAME`_slWrBufIndex    = 0u;
        `$INSTANCE_NAME`_slOverFlowCount = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_SLAVE) */

    #if(`$INSTANCE_NAME`_I2C_MASTER)
    /* Internal master variable */
        `$INSTANCE_NAME`_mstrStatus     = 0u;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
        `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_MASTER) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state and disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CStop(void)
{
    /* Disable TX interrupt sources in order not to cause a false trigger.
    * The incoming transaction will enable an appropriate TX interrupt.
    */
    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

#if(`$INSTANCE_NAME`_CY_SCBIP_V0)
    /* Clear pending interrupt as TX FIFO becomes empty and block does not gate interrupt trigger when disabled */
    `$INSTANCE_NAME`_ClearPendingInt();
#endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

    `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
}


#if(`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CSaveConfig(void)
    {
        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Added for compatibility.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CRestoreConfig(void)
    {
        /* `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP is masked-off in the interrupt */
    }
#endif /* (`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
