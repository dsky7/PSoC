/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_SCB_MODE_I2C_INC)
    #include "`$INSTANCE_NAME`_I2C_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_INC) */

#if(`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC)
    #include "`$INSTANCE_NAME`_SPI_UART_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

`$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Calls SaveConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    `$INSTANCE_NAME`_backup.enableState = (uint8) `$INSTANCE_NAME`_GET_CTRL_ENABLED;

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #elif(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
        `$INSTANCE_NAME`_I2CSaveConfig();

    #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
        `$INSTANCE_NAME`_SpiSaveConfig();

    #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
        `$INSTANCE_NAME`_UartSaveConfig();

    #else
        /* Do nothing */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Stop();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Calls RestoreConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #elif(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
        `$INSTANCE_NAME`_I2CRestoreConfig();

    #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
        `$INSTANCE_NAME`_SpiRestoreConfig();

    #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
        `$INSTANCE_NAME`_UartRestoreConfig();

    #else
        /* Do nothing */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
