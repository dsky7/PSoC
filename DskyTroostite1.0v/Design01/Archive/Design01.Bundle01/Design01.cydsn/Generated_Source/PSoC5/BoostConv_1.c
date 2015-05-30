/*******************************************************************************
* File Name: BoostConv_1.c
* Version 5.0
*
* Description:
*  This file provides the source code to the API for the Boost Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BoostConv_1.h"

uint8 BoostConv_1_initVar = 0u;
static BoostConv_1_BACKUP_STRUCT BoostConv_1_backup = {BoostConv_1_INIT_VOUT,
                                                                 BoostConv_1_BOOSTMODE_ACTIVE};


/*******************************************************************************
* Function Name: BoostConv_1_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default BoostConv configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_1_Init(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    #if (CY_PSOC3)
        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_1_CONTROL_REG1;
        tmp = BoostConv_1_CONTROL_REG1;
        /* Enables mode control from xmode[1:0] instead of control register 1 */
        BoostConv_1_CONTROL_REG1 = tmp | BoostConv_1_PWMEXT_ENABLE;
    #endif /* CY_PSOC3 */

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG2;
    tmp = BoostConv_1_CONTROL_REG2;

    #if (0u != BoostConv_1_DISABLE_AUTO_BATTERY)
        BoostConv_1_CONTROL_REG2 = tmp | BoostConv_1_AUTO_BATTERY_DISABLE;
    #else
        BoostConv_1_CONTROL_REG2 = tmp & ((uint8) (~BoostConv_1_AUTO_BATTERY_DISABLE));
    #endif /* (0u != BoostConv_1_DISABLE_AUTO_BATTERY) */

    CyExitCriticalSection(enableInterrupts);

    #if (CY_PSOC3)
        BoostConv_1_SelExtClk(BoostConv_1_EXTCLK_SRC);
    #else /* CY_PSOC5LP */
        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_1_CONTROL_REG1;
        tmp = BoostConv_1_CONTROL_REG1;

        BoostConv_1_CONTROL_REG1 = (tmp & ((uint8) (~BoostConv_1_FREQ_MASK))) |
                                                         BoostConv_1__SWITCH_FREQ_400KHZ;
    #endif /* CY_PSOC3 */

    BoostConv_1_SelVoltage(BoostConv_1_INIT_VOUT);
    BoostConv_1_SetMode(BoostConv_1_BOOSTMODE_ACTIVE);
}


/*******************************************************************************
* Function Name: BoostConv_1_Start
********************************************************************************
*
* Summary:
*  Starts the BoostConv_1 component and puts the boost block into Active
*  mode. The component is in this state when the chip powers up. This is the
*  preferred method to begin component operation. BoostConv_1_Start()
*  sets the initVar variable, calls the BoostConv_1_Init() function, and
*  then calls the BoostConv_1_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  BoostConv_1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Side Effect:
*  If the initVar variable is already set, this function: 1) sets init value
*  of target output voltage (from customizer) and mode (Active mode) or
*  restores target output voltage and mode saved by BoostConv_1_Stop()
*  function; 2) calls the BoostConv_1_Enable() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BoostConv_1_Start(void) 
{
    uint16 timeout = BoostConv_1_STARTUP_TIMEOUT;
    uint8 tmp;

    do
    {
        CyDelayUs(1u);
        tmp = BoostConv_1_ReadStatus();
        timeout--;

    } while ((0u != timeout) && (BoostConv_1_RDY != (tmp & BoostConv_1_RDY)));

    tmp = BoostConv_1_ReadStatus();

    if (BoostConv_1_RDY == (tmp & BoostConv_1_RDY))
    {
        if (0u == BoostConv_1_initVar)
        {
            BoostConv_1_Init();
            BoostConv_1_initVar = 1u;
        }
        else
        {
            BoostConv_1_SelVoltage(BoostConv_1_backup.selVoltage);
            BoostConv_1_SetMode(BoostConv_1_backup.mode);
        }

        BoostConv_1_Enable();
    }
    else
    {
        /* Boost internal circuits have not been initialized.
         * Halt CPU in debug mode.
         */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: BoostConv_1_Stop
********************************************************************************
*
* Summary:
*  Saves boost converter target output voltage and mode. Disables
*  the BoostConv_1 component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effect:
* Turns off power to the boost converter circuitry. For PSoC 3 sets the boost
* converter to Standby mode, for PSoC 5LP to Sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BoostConv_1_Stop(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG0;
    tmp = BoostConv_1_CONTROL_REG0;

    BoostConv_1_backup.mode = (tmp & BoostConv_1_MODE_MASK) >> BoostConv_1_MODE_SHIFT;
    BoostConv_1_backup.selVoltage = tmp & BoostConv_1_VOLTAGE_MASK;

    CyExitCriticalSection(enableInterrupts);

    BoostConv_1_SelVoltage(BoostConv_1_VOUT_OFF);
    #if (CY_PSOC3)
        BoostConv_1_SetMode(BoostConv_1_BOOSTMODE_STANDBY);
    #endif /* CY_PSOC3 */
    #if (CY_PSOC5LP)
        BoostConv_1_SetMode(BoostConv_1_BOOSTMODE_SLEEP);
    #endif /* CY_PSOC5LP */
    BoostConv_1_Disable();
}


/*******************************************************************************
* Function Name: BoostConv_1_Enable
********************************************************************************
*
* Summary:
*  This function enables the boost only when it is in Active mode. By default
*  this is enabled.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_1_Enable(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG1;
    tmp = BoostConv_1_CONTROL_REG1;

    BoostConv_1_CONTROL_REG1 = tmp | BoostConv_1_BOOST_ENABLE;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_1_Disable
********************************************************************************
*
* Summary:
*  This function disables the boost.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_1_Disable(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG1;
    tmp = BoostConv_1_CONTROL_REG1;

    BoostConv_1_CONTROL_REG1 = tmp & ((uint8) (~BoostConv_1_BOOST_ENABLE));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_1_SetMode
********************************************************************************
*
* Summary:
*  This function sets the mode of the Boost: Active, and Standby for PSoC 3 or
*  Sleep for PSoC 5LP.
*
* Parameters:
*  mode: Mode of operation.
*
* Return:
*  None.
*
* Side Effect:
*  PSoC 3:
*   1) For Standby mode, this function enables automatic thump mode
*   and sets the switching frequency clock source to the 32-kHz external clock.
*   2) For Active mode this function disables automatic thump mode
*   and sets the switching frequency clock source to the 400-kHz internal clock.
*
*******************************************************************************/
void BoostConv_1_SetMode(uint8 mode) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    #if (CY_PSOC3)
        if (0u == mode)
        {
            /* Parameter value is incompatible with PSoC 3 device.
             * Halt CPU in debug mode.
             */
            CYASSERT(0u != 0u);
        }
    #endif /* CY_PSOC3 */
    #if (CY_PSOC5LP)
        if (1u == mode)
        {
            /* Parameter value is incompatible with PSoC 5LP device.
             * Halt CPU in debug mode.
             */
            CYASSERT(0u != 0u);
        }
    #endif /* CY_PSOC5LP */

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG0;
    tmp = BoostConv_1_CONTROL_REG0;

    BoostConv_1_CONTROL_REG0 = (tmp & ((uint8) (~BoostConv_1_MODE_MASK))) |
                                    (BoostConv_1_MODE_MASK & ((uint8) (mode << BoostConv_1_MODE_SHIFT)));

    CyExitCriticalSection(enableInterrupts);

    #if (CY_PSOC3)
        if (mode == BoostConv_1_BOOSTMODE_STANDBY)
        {
           BoostConv_1_SelFreq(BoostConv_1__SWITCH_FREQ_32KHZ);
           BoostConv_1_EnableAutoThump();
        }
        else /* mode == BoostConv_1_BOOSTMODE_ACTIVE */
        {
            BoostConv_1_SelFreq(BoostConv_1__SWITCH_FREQ_400KHZ);
            BoostConv_1_DisableAutoThump();
        }
    #endif /* CY_PSOC3 */
}


/*******************************************************************************
* Function Name: BoostConv_1_SelVoltage
********************************************************************************
*
* Summary:
*  This function selects the target output voltage the boost converter will
*  maintain.
*
* Parameters:
*  voltage: Desired output voltage.
*
* Return:
*  None.
*
*******************************************************************************/
void BoostConv_1_SelVoltage(uint8 voltage) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG0;
    tmp = BoostConv_1_CONTROL_REG0;

    BoostConv_1_CONTROL_REG0 = (tmp & ((uint8) (~BoostConv_1_VOLTAGE_MASK))) |
                                            (BoostConv_1_VOLTAGE_MASK & voltage);

    CyExitCriticalSection(enableInterrupts);
}


#if (CY_PSOC3)

    /*******************************************************************************
    * Function Name: BoostConv_1_SelFreq
    ********************************************************************************
    *
    * Summary:
    *  This function sets the frequency to one of the 2 possible values:
    *  400kHz (which is generated internal to the Boost Converter block with a
    *  dedicated oscillator) or 32kHz (which comes from the chips ECO-32kHz or
    *  ILO-32kHz). The 32kHz frequency is only applicable for PSoC 3.
    *
    * Parameters:
    *  frequency: Desired switching frequency.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_1_SelFreq(uint8 frequency) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_1_CONTROL_REG1;
        tmp = BoostConv_1_CONTROL_REG1;

        BoostConv_1_CONTROL_REG1 = (tmp & ((uint8) (~BoostConv_1_FREQ_MASK))) |
                                                (BoostConv_1_FREQ_MASK & frequency);

        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: BoostConv_1_SelExtClk
    ********************************************************************************
    *
    * Summary:
    *  This function sets the source of 32kHz frequency: the chips ECO-32kHz
    *  or ILO-32kHz.
    *
    * Parameters:
    *  source: source of 32kHz frequency.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void  BoostConv_1_SelExtClk(uint8 source) 
    {
        BoostConv_1_CONTROL_REG4 = (BoostConv_1_CONTROL_REG4 & ((uint8) (~BoostConv_1_EXTCLK_SRC_MASK)))
                                        | (BoostConv_1_EXTCLK_SRC_MASK &
                                        ((uint8) (source << BoostConv_1_EXTCLK_SRC_SHIFT)));
    }


    /*******************************************************************************
    * Function Name: BoostConv_1_EnableAutoThump
    ********************************************************************************
    *
    * Summary:
    *  This function enables automatic thump mode (only available when Boost is
    *  in Standby mode)
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_1_EnableAutoThump(void) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_1_CONTROL_REG2;
        tmp = BoostConv_1_CONTROL_REG2;

        BoostConv_1_CONTROL_REG2 = tmp | BoostConv_1_AUTO_THUMP_ENABLE;

        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: BoostConv_1_DisableAutoThump
    ********************************************************************************
    *
    * Summary:
    *  This function disables automatic thump mode (only available when Boost is
    *  in Standby mode)
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BoostConv_1_DisableAutoThump(void) 
    {
        uint8 tmp;
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Accessing Boost block registers in read mode has speed limitation and
         * requires two consecutive reads of registers resides in Boost hard-IP block
         */
        (void) BoostConv_1_CONTROL_REG2;
        tmp = BoostConv_1_CONTROL_REG2;

        BoostConv_1_CONTROL_REG2 = tmp & ((uint8) (~BoostConv_1_AUTO_THUMP_ENABLE));

        CyExitCriticalSection(enableInterrupts);
    }

#endif /* CY_PSOC3 */


/*******************************************************************************
* Function Name: BoostConv_1_ManualThump
********************************************************************************
*
* Summary:
*  This function forces a single pulse of the boost converter switch
*  transistors.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Thump - produces one ~500ns pulse when set. Must be reset to 0 before another
*  pulse can be generated. It should not re-set the bit until after the 500ns
*  pulse has expired. Used for discrete switch control.
*
* Side Effects:
*  This routine writes a "0" followed by a "1" to the bit 7 "thump" bit in the
*  boost block BOOST_CR0 register.
*
*******************************************************************************/
void BoostConv_1_ManualThump(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation  and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_CONTROL_REG0;
    tmp = BoostConv_1_CONTROL_REG0;

    BoostConv_1_CONTROL_REG0 = tmp | BoostConv_1_MANUAL_THUMP_ENABLE;
    CyDelayUs(1u);
    BoostConv_1_CONTROL_REG0 = tmp & ((uint8) (~BoostConv_1_MANUAL_THUMP_ENABLE));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BoostConv_1_ReadStatus
********************************************************************************
*
* Summary:
*  This function returns the contents of the boost block status register.
*
* Parameters:
*  None.
*
* Return:
*  Boost block status register.
*
*******************************************************************************/
uint8 BoostConv_1_ReadStatus(void) 
{
    uint8 tmp;
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Accessing Boost block registers in read mode has speed limitation and
     * requires two consecutive reads of registers resides in Boost hard-IP block
     */
    (void) BoostConv_1_STATUS_REG;
    tmp = BoostConv_1_STATUS_REG;

    CyExitCriticalSection(enableInterrupts);

    return (tmp);
}


/*******************************************************************************
* Function Name: BoostConv_1_EnableInt
********************************************************************************
*
* Summary:
*  This function enables the Boost block Output Under-Voltage interrupt
*  generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void  BoostConv_1_EnableInt(void) 
{
    BoostConv_1_CONTROL_REG4 |= BoostConv_1_INT_ENABLE_MASK;
}


/*******************************************************************************
* Function Name: BoostConv_1_DisableInt
********************************************************************************
*
* Summary:
*  This function disables the Boost block Output Under-Voltage interrupt
*  generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void  BoostConv_1_DisableInt(void) 
{
    BoostConv_1_CONTROL_REG4 &= (uint8) (~BoostConv_1_INT_ENABLE_MASK);
}


/*******************************************************************************
* Function Name: BoostConv_1_ReadIntStatus
********************************************************************************
*
* Summary:
*  This function returns the contents of the boost block interrupt status
*  register.
*
* Parameters:
*  None.
*
* Return:
*  Boost interrupt status register.
*
*******************************************************************************/
uint8 BoostConv_1_ReadIntStatus(void) 
{
    return (BoostConv_1_STATUS_REG2 & BoostConv_1_INT_ENABLE_MASK);
}


/* [] END OF FILE */
