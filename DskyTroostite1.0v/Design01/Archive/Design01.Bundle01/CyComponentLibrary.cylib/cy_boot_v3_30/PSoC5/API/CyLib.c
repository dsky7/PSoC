/*******************************************************************************
* File Name: CyLib.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"


/*******************************************************************************
* The CyResetStatus variable is used to obtain value of RESET_SR0 register after
* a device reset.
*******************************************************************************/
uint8 CYXDATA CyResetStatus;


#if(!CY_PSOC5A)

    /* Variable Vdda */
    #if(CYDEV_VARIABLE_VDDA == 1)

        uint8 CyScPumpEnabled = (uint8)(CYDEV_VDDA_MV < 2700);

    #endif  /* (CYDEV_VARIABLE_VDDA == 1) */

#endif /* (!CY_PSOC5A) */


/* Do not use these definitions directly in your application */
uint32 cydelay_freq_hz  = BCLK__BUS_CLK__HZ;
uint32 cydelay_freq_khz = (BCLK__BUS_CLK__HZ + 999u) / 1000u;
uint8  cydelay_freq_mhz = (uint8)((BCLK__BUS_CLK__HZ + 999999u) / 1000000u);
uint32 cydelay_32k_ms   = 32768u * ((BCLK__BUS_CLK__HZ + 999u) / 1000u);


/* Function Prototypes */
static uint8 CyUSB_PowerOnCheck(void)  `=ReentrantKeil("CyUSB_PowerOnCheck")`;
static void CyIMO_SetTrimValue(uint8 freq) `=ReentrantKeil("CyIMO_SetTrimValue")`;
static void CyBusClk_Internal_SetDivider(uint16 divider)`=ReentrantKeil("CyBusClk_Internal_SetDivider")`;


/*******************************************************************************
* Function Name: CyPLL_OUT_Start
********************************************************************************
*
* Summary:
*   Enables the PLL.  Optionally waits for it to become stable.
*   Waits at least 250 us or until it is detected that the PLL is stable.
*
* Parameters:
*   wait:
*    0: Return immediately after configuration
*    1: Wait for PLL lock or timeout.
*
* Return:
*   Status
*    CYRET_SUCCESS - Completed successfully
*    CYRET_TIMEOUT - Timeout occurred without detecting a stable clock.
*     If the input source of the clock is jittery, then the lock indication
*     may not occur.  However, after the timeout has expired the generated PLL
*     clock can still be used.
*
* Side Effects:
*  If wait is enabled: This function wses the Fast Time Wheel to time the wait.
*  Any other use of the Fast Time Wheel will be stopped during the period of
*  this function and then restored. This function also uses the 100 KHz ILO.
*  If not enabled, this function will enable the 100 KHz ILO for the period of
*  this function.
*
*  No changes to the setup of the ILO, Fast Time Wheel, Central Time Wheel or
*  Once Per Second interrupt may be made by interrupt routines during the period
*  of this function execution. The current operation of the ILO, Central Time
*  Wheel and Once Per Second interrupt are maintained during the operation of
*  this function provided the reading of the Power Manager Interrupt Status
*  Register is only done using the CyPmReadStatus() function.
*
*******************************************************************************/
cystatus CyPLL_OUT_Start(uint8 wait) `=ReentrantKeil("CyPLL_OUT_Start")`
{
    cystatus status = CYRET_SUCCESS;

    uint8 iloEnableState;
    uint8 pmTwCfg0State;
    uint8 pmTwCfg2State;


    /* Enables the PLL circuit  */
    CY_CLK_PLL_CFG0_REG |= CY_CLK_PLL_ENABLE;

    if(wait != 0u)
    {
        /* Save 100 KHz ILO, FTW interval, enable and interrupt enable */
        iloEnableState = SLOWCLK_ILO_CR0;
        pmTwCfg0State = CY_PM_TW_CFG0_REG;
        pmTwCfg2State = CY_PM_TW_CFG2_REG;

        CyPmFtwSetInterval(CY_CLK_PLL_FTW_INTERVAL);

        status = CYRET_TIMEOUT;


        while(CyPmReadStatus(CY_PM_FTW_INT) != CY_PM_FTW_INT)
        {
            /* Wait for the interrupt status */
            if(0u != (CY_CLK_PLL_SR_REG & CY_CLK_PLL_LOCK_STATUS))
            {
                if(0u != (CY_CLK_PLL_SR_REG & CY_CLK_PLL_LOCK_STATUS))
                {
                    status = CYRET_SUCCESS;
                    break;
                }
            }
        }


        /* Restore 100 KHz ILO, FTW interval, enable and interrupt enable */
        if(0u == (iloEnableState & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }
        CY_PM_TW_CFG0_REG = pmTwCfg0State;
        CY_PM_TW_CFG2_REG = pmTwCfg2State;
    }

    return(status);
}


/*******************************************************************************
* Function Name: CyPLL_OUT_Stop
********************************************************************************
*
* Summary:
*  Disables the PLL.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyPLL_OUT_Stop(void) `=ReentrantKeil("CyPLL_OUT_Stop")`
{
    CY_CLK_PLL_CFG0_REG &= ((uint8)(~CY_CLK_PLL_ENABLE));
}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetPQ
********************************************************************************
*
* Summary:
*  Sets the P and Q dividers and the charge pump current.
*  The Frequency Out will be P/Q * Frequency In.
*  The PLL must be disabled before calling this function.
*
* Parameters:
*  uint8 pDiv:
*   Valid range [8 - 255].
*
*  uint8 qDiv:
*   Valid range [1 - 16]. Input Frequency / Q must be in range of 1 to 3 MHz.

*  uint8 current:
*   Valid range [1 - 7]. Charge pump current in uA. Refer to the device TRM and
*   datasheet for more information.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyPLL_OUT_SetPQ(uint8 pDiv, uint8 qDiv, uint8 current) `=ReentrantKeil("CyPLL_OUT_SetPQ")`
{
    /* Halt CPU in debug mode if PLL is enabled */
    CYASSERT(0u == (CY_CLK_PLL_CFG0_REG & CY_CLK_PLL_ENABLE));

    if((pDiv    >= CY_CLK_PLL_MIN_P_VALUE  ) &&
       (qDiv    <= CY_CLK_PLL_MAX_Q_VALUE  ) && (qDiv    >= CY_CLK_PLL_MIN_Q_VALUE  ) &&
       (current >= CY_CLK_PLL_MIN_CUR_VALUE) && (current <= CY_CLK_PLL_MAX_CUR_VALUE))
    {
        /* Set new values */
        CY_CLK_PLL_P_REG = pDiv;
        CY_CLK_PLL_Q_REG = ((uint8)(qDiv - 1u));
        CY_CLK_PLL_CFG1_REG = (CY_CLK_PLL_CFG1_REG & CY_CLK_PLL_CURRENT_MASK) |
                                ((uint8)(((uint8)(current - 1u)) << CY_CLK_PLL_CURRENT_POSITION));
    }
    else
    {
        /***********************************************************************
        * Halt CPU in debug mode if:
        * - P divider is less than required
        * - Q divider is out of range
        * - pump current is out of range
        ***********************************************************************/
        CYASSERT(0u != 0u);
    }

}


/*******************************************************************************
* Function Name: CyPLL_OUT_SetSource
********************************************************************************
*
* Summary:
*  Sets the input clock source to the PLL. The PLL must be disabled before
*  calling this function.
*
* Parameters:
*   source: One of the three available PLL clock sources
*            0 :        IMO
*            1 :        MHz Crystal
*            2 :        DSI
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyPLL_OUT_SetSource(uint8 source) `=ReentrantKeil("CyPLL_OUT_SetSource")`
{
    /* Halt CPU in debug mode if PLL is enabled */
    CYASSERT(0u == (CY_CLK_PLL_CFG0_REG & CY_CLK_PLL_ENABLE));

    switch(source)
    {
        case CY_PLL_SOURCE_IMO:
        case CY_PLL_SOURCE_XTAL:
        case CY_PLL_SOURCE_DSI:
            CY_LIB_CLKDIST_CR_REG = ((CY_LIB_CLKDIST_CR_REG & CY_LIB_CLKDIST_CR_PLL_SCR_MASK) | source);
        break;

        default:
            CYASSERT(0u != 0u);
        break;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Start
********************************************************************************
*
* Summary:
*  Enables the IMO. Optionally waits at least 6 us for it to settle.
*
* Parameters:
*  uint8 wait:
*   0: Return immediately after configuration
*   1: Wait for at least 6 us for the IMO to settle.
*
* Return:
*  None
*
* Side Effects:
*  If wait is enabled: This function wses the Fast Time Wheel to time the wait.
*  Any other use of the Fast Time Wheel will be stopped during the period of
*  this function and then restored. This function also uses the 100 KHz ILO.
*  If not enabled, this function will enable the 100 KHz ILO for the period of
*  this function.
*
*  No changes to the setup of the ILO, Fast Time Wheel, Central Time Wheel or
*  Once Per Second interrupt may be made by interrupt routines during the period
*  of this function execution. The current operation of the ILO, Central Time
*  Wheel and Once Per Second interrupt are maintained during the operation of
*  this function provided the reading of the Power Manager Interrupt Status
*  Register is only done using the CyPmReadStatus() function.
*
*******************************************************************************/
void CyIMO_Start(uint8 wait) `=ReentrantKeil("CyIMO_Start")`
{
    uint8 pmFtwCfg2Reg;
    uint8 pmFtwCfg0Reg;
    uint8 iloControlReg;

    /* Set the bit to enable the clock. */
    PM_ACT_CFG0 |= IMO_PM_ENABLE;

    /* Wait for 6 us */
    if(0u != wait)
    {
        /* Need to turn on the 100KHz ILO if it happens to not already be running.*/
        iloControlReg = SLOWCLK_ILO_CR0;

        if(0u == (iloControlReg & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Start100K();
        }

        /* Use ILO 100 KHz */
        pmFtwCfg2Reg = PM_TW_CFG2;
        pmFtwCfg0Reg = PM_TW_CFG0;

        /* FTW_EN (bit 0) must be clear to change the period*/
        PM_TW_CFG2 &= FTW_CLEAR_FTW_BITS;

        /* Set the FTW interval of 1 100KHz ILO clocks
        Should result in status getting set at a (100/1)KHz rate*/
        PM_TW_CFG0 = 0u;

        /* Enable FTW, but not the interrupt */
        PM_TW_CFG2 = FTW_ENABLE;

        /* Read FTW value */
        while (CyPmReadStatus(CY_PM_FTW_INT) == 0u)
        {
            /* Wait for the interrupt status */
        }

        /* Reset the clock */
        if(0u == (iloControlReg & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }

        /* Restore the FTW */
        PM_TW_CFG0 = pmFtwCfg0Reg;
        PM_TW_CFG2 = pmFtwCfg2Reg;
    }
}


/*******************************************************************************
* Function Name: CyIMO_Stop
********************************************************************************
*
* Summary:
*   Disables the IMO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_Stop(void) `=ReentrantKeil("CyIMO_Stop")`
{
    /* Clear the bit to disable the clock. */
    PM_ACT_CFG0 &= ((uint8)(~IMO_PM_ENABLE));
}


/*******************************************************************************
* Function Name: CyUSB_PowerOnCheck
********************************************************************************
*
* Summary:
*  Returns the USB power status value. A private function to cy_boot.
*
* Parameters:
*   None
*
* Return:
*   uint8: one if the USB is enabled, 0 if not enabled.
*
*******************************************************************************/
static uint8 CyUSB_PowerOnCheck(void)  `=ReentrantKeil("CyUSB_PowerOnCheck")`
{
    uint8 poweredOn = 0u;

    /* Check whether device is in Active or AltActiv and if USB is powered on */
    if((((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ACTIVE ) &&
       (0u != (CY_PM_ACT_CFG5_REG & CY_ACT_USB_ENABLED     )))  ||
       (((CY_PM_MODE_CSR_REG & CY_PM_MODE_CSR_MASK) == CY_PM_MODE_CSR_ALT_ACT) &&
       (0u != (CY_PM_STBY_CFG5_REG & CY_ALT_ACT_USB_ENABLED))))
    {
        poweredOn = 1u;
    }

    return (poweredOn);
}


/*******************************************************************************
* Function Name: CyIMO_SetTrimValue
********************************************************************************
*
* Summary:
*  Sets the IMO factory trim values.
*
* Parameters:
*  uint8 freq - frequency for which trims must be set
*
* Return:
*  None
*
*******************************************************************************/
static void CyIMO_SetTrimValue(uint8 freq) `=ReentrantKeil("CyIMO_SetTrimValue")`
{
    uint8 usb_power_on = CyUSB_PowerOnCheck();

    /* If USB is powered */
    if(usb_power_on == 1u)
    {
        /* Unlock USB write */
        CY_USB_CR1 &= ((uint8)(~CLOCK_USB_ENABLE));
    }
    switch(freq)
    {
    case CY_IMO_FREQ_3MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_3MHZ_PTR);
        break;

    case CY_IMO_FREQ_6MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_6MHZ_PTR);
        break;

    case CY_IMO_FREQ_12MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_12MHZ_PTR);
        break;

    case CY_IMO_FREQ_24MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_24MHZ_PTR);
        break;

    case CY_IMO_FREQ_48MHZ:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_MFG_CFG_IMO_TR1_PTR);
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

        case CY_IMO_FREQ_62MHZ:
            IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_67MHZ_PTR);
            break;

    #endif  /* (!CY_PSOC5A) */

    case CY_IMO_FREQ_USB:
        IMO_TR1 = CY_GET_XTND_REG8(FLSHID_CUST_TABLES_IMO_USB_PTR);

        /* If USB is powered */
        if(usb_power_on == 1u)
        {
            /* Lock the USB Oscillator */
            CY_USB_CR1 |= CLOCK_USB_ENABLE;
        }
        break;

    default:
            CYASSERT(0u != 0u);
        break;
    }

}


/*******************************************************************************
* Function Name: CyIMO_SetFreq
********************************************************************************
*
* Summary:
*  Sets the frequency of the IMO. Changes may be made while the IMO is running.
*
* Parameters:
*  freq: Frequency of IMO operation
*       CY_IMO_FREQ_3MHZ  to set  3   MHz
*       CY_IMO_FREQ_6MHZ  to set  6   MHz
*       CY_IMO_FREQ_12MHZ to set 12   MHz
*       CY_IMO_FREQ_24MHZ to set 24   MHz
*       CY_IMO_FREQ_48MHZ to set 48   MHz
*       CY_IMO_FREQ_62MHZ to set 62 MHz (unsupported by PSoC 5)
*       CY_IMO_FREQ_USB   to set 24   MHz (Trimmed for USB operation)
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*  When the USB setting is chosen, the USB clock locking circuit is enabled.
*  Otherwise this circuit is disabled. The USB block must be powered before
*  selecting the USB setting.
*
*******************************************************************************/
void CyIMO_SetFreq(uint8 freq) `=ReentrantKeil("CyIMO_SetFreq")`
{
    uint8 currentFreq;
    uint8 nextFreq;

    /***************************************************************************
    * When changing the IMO frequency the Trim values must also be set
    * accordingly.This requires reading the current frequency. If the new
    * frequency is faster, then set the new trim and then change the frequency,
    * otherwise change the frequency and then set the new trim values.
    ***************************************************************************/

    currentFreq = CY_LIB_FASTCLK_IMO_CR_REG & ((uint8)(~CY_LIB_FASTCLK_IMO_CR_RANGE_MASK));

    /* Check if the requested frequency is USB. */
    nextFreq = (freq == CY_IMO_FREQ_USB) ? CY_IMO_FREQ_24MHZ : freq;

    switch (currentFreq)
    {
    case 0u:
        currentFreq = CY_IMO_FREQ_12MHZ;
        break;

    case 1u:
        currentFreq = CY_IMO_FREQ_6MHZ;
        break;

    case 2u:
        currentFreq = CY_IMO_FREQ_24MHZ;
        break;

    case 3u:
        currentFreq = CY_IMO_FREQ_3MHZ;
        break;

    case 4u:
        currentFreq = CY_IMO_FREQ_48MHZ;
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

        case 5u:
            currentFreq = CY_IMO_FREQ_62MHZ;
            break;

    #endif  /* (!CY_PSOC5A) */

    default:
        CYASSERT(0u != 0u);
        break;
    }

    if (nextFreq >= currentFreq)
    {
        /* Set the new trim first */
        CyIMO_SetTrimValue(freq);
    }

    /* Set the usbclk_on bit when using CY_IMO_FREQ_USB, if not clear it */
    switch(freq)
    {
    case CY_IMO_FREQ_3MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_3MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    case CY_IMO_FREQ_6MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_6MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    case CY_IMO_FREQ_12MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_12MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    case CY_IMO_FREQ_24MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_24MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    case CY_IMO_FREQ_48MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_48MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    /* The IMO frequencies above 48 MHz are not supported by PSoC5 */
    #if(!CY_PSOC5A)

    case CY_IMO_FREQ_62MHZ:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_62MHZ_VALUE) & ((uint8)(~FASTCLK_IMO_USBCLK_ON_SET));
        break;

    #endif  /* (!CY_PSOC5A) */

    case CY_IMO_FREQ_USB:
        CY_LIB_FASTCLK_IMO_CR_REG = ((CY_LIB_FASTCLK_IMO_CR_REG & CY_LIB_FASTCLK_IMO_CR_RANGE_MASK) |
            CLOCK_IMO_24MHZ_VALUE) | FASTCLK_IMO_USBCLK_ON_SET;
        break;

    default:
        CYASSERT(0u != 0u);
        break;
    }

    /* Turn on the IMO Doubler, if switching to CY_IMO_FREQ_USB */
    if (freq == CY_IMO_FREQ_USB)
    {
        CyIMO_EnableDoubler();
    }
    else
    {
        CyIMO_DisableDoubler();
    }

    if (nextFreq < currentFreq)
    {
        /* Set the new trim after setting the frequency */
        CyIMO_SetTrimValue(freq);
    }
}


/*******************************************************************************
* Function Name: CyIMO_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the clock output from the IMO block.
*
*  The output from the IMO is by default the IMO itself. Optionally the MHz
*  Crystal or a DSI input can be the source of the IMO output instead.
*
* Parameters:
*   source, CY_IMO_SOURCE_DSI to set the DSI as source.
*           CY_IMO_SOURCE_XTAL to set the MHz as source.
*           CY_IMO_SOURCE_IMO to set the IMO itself.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyIMO_SetSource(uint8 source) `=ReentrantKeil("CyIMO_SetSource")`
{
    switch(source)
    {
    case CY_IMO_SOURCE_DSI:
        CY_LIB_CLKDIST_CR_REG     &= ((uint8)(~CY_LIB_CLKDIST_CR_IMO2X));
        CY_LIB_FASTCLK_IMO_CR_REG |= CY_LIB_FASTCLK_IMO_IMO;
        break;

    case CY_IMO_SOURCE_XTAL:
        CY_LIB_CLKDIST_CR_REG     |= CY_LIB_CLKDIST_CR_IMO2X;
        CY_LIB_FASTCLK_IMO_CR_REG |= CY_LIB_FASTCLK_IMO_IMO;
        break;

    case CY_IMO_SOURCE_IMO:
        CY_LIB_FASTCLK_IMO_CR_REG &= ((uint8)(~CY_LIB_FASTCLK_IMO_IMO));
        break;

    default:
        /* Incorrect source value */
        CYASSERT(0u != 0u);
        break;
    }
}


/*******************************************************************************
* Function Name: CyIMO_EnableDoubler
********************************************************************************
*
* Summary:
*  Enables the IMO doubler.  The 2x frequency clock is used to convert a 24 MHz
*  input to a 48 MHz output for use by the USB block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_EnableDoubler(void) `=ReentrantKeil("CyIMO_EnableDoubler")`
{
    /* Set the FASTCLK_IMO_CR_PTR regigster's 4th bit */
    CY_LIB_FASTCLK_IMO_CR_REG |= CY_LIB_FASTCLK_IMO_DOUBLER;
}


/*******************************************************************************
* Function Name: CyIMO_DisableDoubler
********************************************************************************
*
* Summary:
*   Disables the IMO doubler.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyIMO_DisableDoubler(void) `=ReentrantKeil("CyIMO_DisableDoubler")`
{
    CY_LIB_FASTCLK_IMO_CR_REG &= ((uint8)(~CY_LIB_FASTCLK_IMO_DOUBLER));
}


/*******************************************************************************
* Function Name: CyMasterClk_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the master clock.
*
* Parameters:
*   source: One of the four available Master clock sources.
*     CY_MASTER_SOURCE_IMO
*     CY_MASTER_SOURCE_PLL
*     CY_MASTER_SOURCE_XTAL
*     CY_MASTER_SOURCE_DSI
*
* Return:
*  None
*
* Side Effects:
*  The current source and the new source must both be running and stable before
*  calling this function.
*
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyMasterClk_SetSource(uint8 source) `=ReentrantKeil("CyMasterClk_SetSource")`
{
    #if(CY_PSOC5A)

        uint8 masterReg0;

        /* Read the current setting */
        masterReg0 = CY_LIB_CLKDIST_MSTR0_REG;

        /* Write a non-zero period to the master mux clock divider */
        if (masterReg0 == 0x00u)
        {
            CY_LIB_CLKDIST_MSTR0_REG = 3u;
        }

    #endif  /* (CY_PSOC5A) */

    CY_LIB_CLKDIST_MSTR1_REG = (CY_LIB_CLKDIST_MSTR1_REG & MASTER_CLK_SRC_CLEAR) |
                                (source & ((uint8)(~MASTER_CLK_SRC_CLEAR)));

    #if(CY_PSOC5A)

        /* Restore zero period (if desired) to the master mux clock divider */
        if (masterReg0 == 0x00u)
        {
            CY_LIB_CLKDIST_MSTR0_REG = 0u;
        }

    #endif  /* (CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: CyMasterClk_SetDivider
********************************************************************************
*
* Summary:
*  Sets the divider value used to generate Master Clock.
*
* Parameters:
*  uint8 divider:
*   Valid range [0-255]. The clock will be divided by this value + 1.
*   For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*  When changing the Master or Bus clock divider value from div-by-n to div-by-1
*  the first clock cycle output after the div-by-1 can be up to 4 ns shorter
*  than the final/expected div-by-1 period.
*
*******************************************************************************/
void CyMasterClk_SetDivider(uint8 divider) `=ReentrantKeil("CyMasterClk_SetDivider")`
{
    CY_LIB_CLKDIST_MSTR0_REG = divider;
}


/*******************************************************************************
* Function Name: CyBusClk_Internal_SetDivider
********************************************************************************
*
* Summary:
*  Function used by CyBusClk_SetDivider(). For internal use only.
*
* Parameters:
*   divider: Valid range [0-65535].
*   The clock will be divided by this value + 1.
*   For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
*******************************************************************************/
static void CyBusClk_Internal_SetDivider(uint16 divider)`=ReentrantKeil("CyBusClk_Internal_SetDivider")`
{
    /* Mask bits to enable shadow loads  */
    CY_LIB_CLKDIST_AMASK_REG &= CY_LIB_CLKDIST_AMASK_MASK;
    CY_LIB_CLKDIST_DMASK_REG  = CY_LIB_CLKDIST_DMASK_MASK;

    /* Enable mask bits to enable shadow loads */
    CY_LIB_CLKDIST_BCFG2_REG |= CY_LIB_CLKDIST_BCFG2_MASK;

    /* Update Shadow Divider Value Register with the new divider */
    CY_LIB_CLKDIST_WRK_LSB_REG = LO8(divider);
    CY_LIB_CLKDIST_WRK_MSB_REG = HI8(divider);


    /***************************************************************************
    * Copy shadow value defined in Shadow Divider Value Register
    * (CY_LIB_CLKDIST_WRK_LSB_REG and CY_LIB_CLKDIST_WRK_MSB_REG) to all
    * dividers selected in Analog and Digital Clock Mask Registers
    * (CY_LIB_CLKDIST_AMASK_REG and CY_LIB_CLKDIST_DMASK_REG).
    ***************************************************************************/
    CY_LIB_CLKDIST_LD_REG |= CY_LIB_CLKDIST_LD_LOAD;
}


/*******************************************************************************
* Function Name: CyBusClk_SetDivider
********************************************************************************
*
* Summary:
*  Sets the divider value used to generate Bus Clock.
*
* Parameters:
*  divider: Valid range [0-65535]. The clock will be divided by this value + 1.
*  For example to divide by 2 this parameter should be set to 1.
*
* Return:
*  None
*
* Side Effects:
*  If as result of this function execution the CPU clock frequency is increased
*  then the number of clock cycles the cache will wait before it samples data
*  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
*  with appropriate parameter. It can be optionally called if CPU clock
*  frequency is lowered in order to improve CPU performance.
*  See CyFlash_SetWaitCycles() description for more information.
*
*******************************************************************************/
void CyBusClk_SetDivider(uint16 divider) `=ReentrantKeil("CyBusClk_SetDivider")`
{
    uint8  masterClkDiv;
    uint16 busClkDiv;
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    /* Work around to set the bus clock divider value */
    busClkDiv = ((uint16)(((uint16)(CY_LIB_CLKDIST_BCFG_MSB_REG)) << 8u)) | CY_LIB_CLKDIST_BCFG_LSB_REG;

    if ((divider == 0u) || (busClkDiv == 0u))
    {
        /* Save away the master clock divider value */
        masterClkDiv = CY_LIB_CLKDIST_MSTR0_REG;

        if (masterClkDiv < CY_LIB_CLKDIST_MASTERCLK_DIV)
        {
            /* Set master clock divider to 7 */
            CyMasterClk_SetDivider(CY_LIB_CLKDIST_MASTERCLK_DIV);
        }

        if (divider == 0u)
        {
            /* Set the SSS bit and the divider register desired value */
            CY_LIB_CLKDIST_BCFG2_REG |= CY_LIB_CLKDIST_BCFG2_SSS;
            CyBusClk_Internal_SetDivider(divider);
        }
        else
        {
            CyBusClk_Internal_SetDivider(divider);
            CY_LIB_CLKDIST_BCFG2_REG &= ((uint8)(~CY_LIB_CLKDIST_BCFG2_SSS));
        }

        /* Restore the master clock */
        CyMasterClk_SetDivider(masterClkDiv);
    }
    else
    {
        CyBusClk_Internal_SetDivider(divider);
    }

    CyExitCriticalSection(interruptState);
}


#if(CY_PSOC3)

    /*******************************************************************************
    * Function Name: CyCpuClk_SetDivider
    ********************************************************************************
    *
    * Summary:
    *  Sets the divider value used to generate the CPU Clock. Only applicable for
    *  PSoC 3 parts.
    *
    * Parameters:
    *  divider: Valid range [0-15]. The clock will be divided by this value + 1.
    *  For example to divide by 2 this parameter should be set to 1.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  If as result of this function execution the CPU clock frequency is increased
    *  then the number of clock cycles the cache will wait before it samples data
    *  coming back from Flash must be adjusted by calling CyFlash_SetWaitCycles()
    *  with appropriate parameter. It can be optionally called if CPU clock
    *  frequency is lowered in order to improve CPU performance.
    *  See CyFlash_SetWaitCycles() description for more information.
    *
    *******************************************************************************/
    void CyCpuClk_SetDivider(uint8 divider) `=ReentrantKeil("CyCpuClk_SetDivider")`
    {
            CLKDIST_MSTR1 = (CLKDIST_MSTR1 & CLKDIST_MSTR1_DIV_CLEAR) |
                                ((uint8)(divider << CLKDIST_DIV_POSITION));
    }

#endif /* (CY_PSOC3) */


/*******************************************************************************
* Function Name: CyUsbClk_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the USB clock.
*
* Parameters:
*  source: One of the four available USB clock sources
*             USB_CLK_IMO2X     - IMO 2x
*             USB_CLK_IMO       - IMO
*             USB_CLK_PLL       - PLL
*             USB_CLK_DSI       - DSI
*
* Return:
*  None
*
*******************************************************************************/
void CyUsbClk_SetSource(uint8 source) `=ReentrantKeil("CyUsbClk_SetSource")`
{
    CLKDIST_UCFG = (CLKDIST_UCFG & ((uint8)(~USB_CLKDIST_CONFIG_MASK))) |
                        (USB_CLKDIST_CONFIG_MASK & source);
}


/*******************************************************************************
* Function Name: CyILO_Start1K
********************************************************************************
*
* Summary:
*  Enables the ILO 1 KHz oscillator.
*
*  Note The ILO 1 KHz oscillator is always enabled by default, regardless of the
*  selection in the Clock Editor. Therefore, this API is only needed if the
*  oscillator was turned off manually.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Start1K(void) `=ReentrantKeil("CyILO_Start1K")`
{
    /* Set the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_1KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop1K
********************************************************************************
*
* Summary:
*  Disables the ILO 1 KHz oscillator.
*
*  Note The ILO 1 KHz oscillator must be enabled if Sleep or Hibernate low power
*  mode APIs are expected to be used. For more information, refer to the Power
*  Management section of this document.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  PSoC5: Stopping the ILO 1 kHz could break the active WDT functionality.
*
*******************************************************************************/
void CyILO_Stop1K(void) `=ReentrantKeil("CyILO_Stop1K")`
{
    /* Clear the bit 1 of ILO RS */
    SLOWCLK_ILO_CR0 &= ((uint8)(~ILO_CONTROL_1KHZ_ON));
}


/*******************************************************************************
* Function Name: CyILO_Start100K
********************************************************************************
*
* Summary:
*  Enables the ILO 100 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Start100K(void) `=ReentrantKeil("CyILO_Start100K")`
{
    /* Set the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_100KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Stop100K
********************************************************************************
*
* Summary:
*  Disables the ILO 100 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Stop100K(void) `=ReentrantKeil("CyILO_Stop100K")`
{
    /* Clear the bit 2 of ILO RS */
    SLOWCLK_ILO_CR0 &= ((uint8)(~ILO_CONTROL_100KHZ_ON));
}


/*******************************************************************************
* Function Name: CyILO_Enable33K
********************************************************************************
*
* Summary:
*  Enables the ILO 33 KHz divider.
*
*  Note that the 33 KHz clock is generated from the 100 KHz oscillator,
*  so it must also be running in order to generate the 33 KHz output.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Enable33K(void) `=ReentrantKeil("CyILO_Enable33K")`
{
    /* Set the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 |= ILO_CONTROL_33KHZ_ON;
}


/*******************************************************************************
* Function Name: CyILO_Disable33K
********************************************************************************
*
* Summary:
*  Disables the ILO 33 KHz divider.
*
*  Note that the 33 KHz clock is generated from the 100 KHz oscillator, but this
*  API does not disable the 100 KHz clock.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_Disable33K(void) `=ReentrantKeil("CyILO_Disable33K")`
{
    /* Clear the bit 5 of ILO RS */
    SLOWCLK_ILO_CR0 &= ((uint8)(~ILO_CONTROL_33KHZ_ON));
}


/*******************************************************************************
* Function Name: CyILO_SetSource
********************************************************************************
*
* Summary:
*  Sets the source of the clock output from the ILO block.
*
* Parameters:
*  source: One of the three available ILO output sources
*       Value        Define                Source
*       0            CY_ILO_SOURCE_100K    ILO 100 KHz
*       1            CY_ILO_SOURCE_33K     ILO 33 KHz
*       2            CY_ILO_SOURCE_1K      ILO 1 KHz
*
* Return:
*  None
*
*******************************************************************************/
void CyILO_SetSource(uint8 source) `=ReentrantKeil("CyILO_SetSource")`
{
    CLKDIST_CR = (CLKDIST_CR & CY_ILO_SOURCE_BITS_CLEAR) |
                    (((uint8) (source << 2u)) & ((uint8)(~CY_ILO_SOURCE_BITS_CLEAR)));
}


/*******************************************************************************
* Function Name: CyILO_SetPowerMode
********************************************************************************
*
* Summary:
*  Sets the power mode used by the ILO during power down. Allows for lower power
*  down power usage resulting in a slower startup time.
*
* Parameters:
*  uint8 mode
*   CY_ILO_FAST_START - Faster start-up, internal bias left on when powered down
*   CY_ILO_SLOW_START - Slower start-up, internal bias off when powered down
*
* Return:
*   Prevous power mode state.
*
*******************************************************************************/
uint8 CyILO_SetPowerMode(uint8 mode) `=ReentrantKeil("CyILO_SetPowerMode")`
{
    uint8 state;

    /* Get current state. */
    state = SLOWCLK_ILO_CR0;

    /* Set the the oscillator power mode. */
    if(mode != CY_ILO_FAST_START)
    {
        SLOWCLK_ILO_CR0 = (state | ILO_CONTROL_PD_MODE);
    }
    else
    {
        SLOWCLK_ILO_CR0 = (state & ((uint8)(~ILO_CONTROL_PD_MODE)));
    }

    /* Return the old mode. */
    return ((state & ILO_CONTROL_PD_MODE) >> ILO_CONTROL_PD_POSITION);
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_Start
********************************************************************************
*
* Summary:
*  Enables the 32 KHz Crystal Oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_32KHZ_Start(void) `=ReentrantKeil("CyXTAL_32KHZ_Start")`
{
    volatile uint16 i;

    CY_CLK_XTAL32_TST_REG = CY_CLK_XTAL32_TST_DEFAULT;
    CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_STARTUP;
    CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ((uint8)(~CY_CLK_XTAL32_CFG_LP_MASK))) |
                                CY_CLK_XTAL32_CFG_LP_DEFAULT;

    #if(CY_PSOC3)
        CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_PDBEN;
    #endif  /* (CY_PSOC3) */

    /* Enable operation of the 32K Crystal Oscillator */
    CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_EN;

    for (i = 1000u; i > 0u; i--)
    {
        if(0u != (CyXTAL_32KHZ_ReadStatus() & CY_XTAL32K_ANA_STAT))
        {
            /* Ready - switch to the hign power mode */
            (void) CyXTAL_32KHZ_SetPowerMode(0u);

            break;
        }
        CyDelayUs(1u);
    }
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_Stop
********************************************************************************
*
* Summary:
*  Disables the 32KHz Crystal Oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_32KHZ_Stop(void) `=ReentrantKeil("CyXTAL_32KHZ_Stop")`
{
    CY_CLK_XTAL32_TST_REG  = CY_CLK_XTAL32_TST_DEFAULT;
    CY_CLK_XTAL32_TR_REG   = CY_CLK_XTAL32_TR_POWERDOWN;
    CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ((uint8)(~CY_CLK_XTAL32_CFG_LP_MASK))) | CY_CLK_XTAL32_CFG_LP_DEFAULT;
    CY_CLK_XTAL32_CR_REG &= ((uint8)(~(CY_CLK_XTAL32_CR_EN | CY_CLK_XTAL32_CR_LPM)));

    #if(CY_PSOC3)
        CY_CLK_XTAL32_CR_REG &= ((uint8)(~CY_CLK_XTAL32_CR_PDBEN));
    #endif  /* (CY_PSOC3) */
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_ReadStatus
********************************************************************************
*
* Summary:
*  Returns status of the 32 KHz oscillator.
*
* Parameters:
*  None
*
* Return:
*  Value     Define                    Source
*  20        CY_XTAL32K_ANA_STAT       Analog measurement
*                                       1: Stable
*                                       0: Not stable
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_ReadStatus(void) `=ReentrantKeil("CyXTAL_32KHZ_ReadStatus")`
{
    return(CY_CLK_XTAL32_CR_REG & CY_XTAL32K_ANA_STAT);
}


/*******************************************************************************
* Function Name: CyXTAL_32KHZ_SetPowerMode
********************************************************************************
*
* Summary:
*  Sets the power mode for the 32 KHz oscillator used during sleep mode.
*  Allows for lower power during sleep when there are fewer sources of noise.
*  During active mode the oscillator is always run in high power mode.
*
* Parameters:
*  uint8 mode
*       0: High power mode
*       1: Low power mode during sleep
*
* Return:
*  Previous power mode.
*
*******************************************************************************/
uint8 CyXTAL_32KHZ_SetPowerMode(uint8 mode) `=ReentrantKeil("CyXTAL_32KHZ_SetPowerMode")`
{
    uint8 state = (0u != (CY_CLK_XTAL32_CR_REG & CY_CLK_XTAL32_CR_LPM)) ? 1u : 0u;

    CY_CLK_XTAL32_TST_REG = CY_CLK_XTAL32_TST_DEFAULT;

    if(1u == mode)
    {
        /* Low power mode during Sleep */
        CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_LOW_POWER;
        CyDelayUs(10u);
        CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ((uint8)(~CY_CLK_XTAL32_CFG_LP_MASK))) | CY_CLK_XTAL32_CFG_LP_LOWPOWER;
        CyDelayUs(20u);
        CY_CLK_XTAL32_CR_REG |= CY_CLK_XTAL32_CR_LPM;
    }
    else
    {
        /* High power mode */
        CY_CLK_XTAL32_TR_REG  = CY_CLK_XTAL32_TR_HIGH_POWER;
        CyDelayUs(10u);
        CY_CLK_XTAL32_CFG_REG = (CY_CLK_XTAL32_CFG_REG & ((uint8)(~CY_CLK_XTAL32_CFG_LP_MASK))) | CY_CLK_XTAL32_CFG_LP_DEFAULT;
        CY_CLK_XTAL32_CR_REG &= ((uint8)(~CY_CLK_XTAL32_CR_LPM));
    }

    return(state);
}


/*******************************************************************************
* Function Name: CyXTAL_Start
********************************************************************************
*
* Summary:
*  Enables the megahertz crystal.
*
*  PSoC3:
*  Waits until the XERR bit is low (no error) for a millisecond or until the
*  number of milliseconds specified by the wait parameter has expired.
*
*  PSoC5:
*  Waits for CY_CLK_XMHZ_MIN_TIMEOUT milliseconds (or number of milliseconds
*  specified by parameter if it is greater than CY_CLK_XMHZ_MIN_TIMEOUT. The
*  XERR bit status is not checked.
*
* Parameters:
*   wait: Valid range [0-255].
*   This is the timeout value in milliseconds.
*   The appropriate value is crystal specific.
*
* Return:
*   CYRET_SUCCESS - Completed successfully
*   CYRET_TIMEOUT - Timeout occurred without detecting a low value on XERR.
*
* Side Effects and Restrictions:
*  If wait is enabled (non-zero wait). Uses the Fast Timewheel to time the wait.
*  Any other use of the Fast Timewheel (FTW) will be stopped during the period
*  of this function and then restored.
*
*  Uses the 100KHz ILO.  If not enabled, this function will enable the 100KHz
*  ILO for the period of this function. No changes to the setup of the ILO,
*  Fast Timewheel, Central Timewheel or Once Per Second interrupt may be made
*  by interrupt routines during the period of this function.
*
*  The current operation of the ILO, Central Timewheel and Once Per Second
*  interrupt are maintained during the operation of this function provided the
*  reading of the Power Manager Interrupt Status Register is only done using the
*  CyPmReadStatus() function.
*
*******************************************************************************/
cystatus CyXTAL_Start(uint8 wait) `=ReentrantKeil("CyXTAL_Start")`
{
    cystatus status = CYRET_SUCCESS;

    #if(CY_PSOC5A)
        volatile uint8  timeout = (wait < CY_CLK_XMHZ_MIN_TIMEOUT) ? CY_CLK_XMHZ_MIN_TIMEOUT : wait;
    #else
        volatile uint8  timeout = wait;
    #endif  /* (CY_PSOC5A) */

    volatile uint8 count;
    uint8 iloEnableState;
    uint8 pmTwCfg0Tmp;
    uint8 pmTwCfg2Tmp;


    /* Enables the MHz crystal oscillator circuit  */
    CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_ENABLE;


    if(wait > 0u)
    {
        /* Save 100 KHz ILO, FTW interval, enable and interrupt enable */
        iloEnableState = SLOWCLK_ILO_CR0;
        pmTwCfg0Tmp = CY_PM_TW_CFG0_REG;
        pmTwCfg2Tmp = CY_PM_TW_CFG2_REG;

        /* Set 250 us interval */
        CyPmFtwSetInterval(CY_CLK_XMHZ_FTW_INTERVAL);
        status = CYRET_TIMEOUT;


        for( ; timeout > 0u; timeout--)
        {
            #if(!CY_PSOC5A)

                /* Read XERR bit to clear it */
                (void) CY_CLK_XMHZ_CSR_REG;

            #endif  /* (!CY_PSOC5A) */


            /* Wait for a millisecond - 4 x 250 us */
            for(count = 4u; count > 0u; count--)
            {
                while(!(CY_PM_FTW_INT == CyPmReadStatus(CY_PM_FTW_INT)))
                {
                    /* Wait for the FTW interrupt event */
                }
            }


            #if(!CY_PSOC5A)

                /*******************************************************************
                * High output indicates oscillator failure.
                * Only can be used after start-up interval (1 ms) is completed.
                *******************************************************************/
                if(0u == (CY_CLK_XMHZ_CSR_REG & CY_CLK_XMHZ_CSR_XERR))
                {
                    status = CYRET_SUCCESS;
                    break;
                }

            #endif  /* (!CY_PSOC5A) */
        }


        /* Restore 100 KHz ILO, FTW interval, enable and interrupt enable */
        if(0u == (iloEnableState & ILO_CONTROL_100KHZ_ON))
        {
            CyILO_Stop100K();
        }
        CY_PM_TW_CFG0_REG = pmTwCfg0Tmp;
        CY_PM_TW_CFG2_REG = pmTwCfg2Tmp;
    }

    return(status);
}


/*******************************************************************************
* Function Name: CyXTAL_Stop
********************************************************************************
*
* Summary:
*  Disables the megahertz crystal oscillator.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_Stop(void) `=ReentrantKeil("CyXTAL_Stop")`
{
    /* Disable the the oscillator. */
    FASTCLK_XMHZ_CSR &= ((uint8)(~XMHZ_CONTROL_ENABLE));
}


#if(!CY_PSOC5A)

    /*******************************************************************************
    * Function Name: CyXTAL_EnableErrStatus
    ********************************************************************************
    *
    * Summary:
    *  Enables the generation of the XERR status bit for the megahertz crystal.
    *  This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_EnableErrStatus(void) `=ReentrantKeil("CyXTAL_EnableErrStatus")`
    {
        /* If oscillator has insufficient amplitude, XERR bit will be high. */
        CY_CLK_XMHZ_CSR_REG &= ((uint8)(~CY_CLK_XMHZ_CSR_XFB));
    }


    /*******************************************************************************
    * Function Name: CyXTAL_DisableErrStatus
    ********************************************************************************
    *
    * Summary:
    *  Disables the generation of the XERR status bit for the megahertz crystal.
    *  This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_DisableErrStatus(void) `=ReentrantKeil("CyXTAL_DisableErrStatus")`
    {
        /* If oscillator has insufficient amplitude, XERR bit will be high. */
        CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_XFB;
    }


    /*******************************************************************************
    * Function Name: CyXTAL_ReadStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the XERR status bit for the megahertz crystal. This status bit is a
    *  sticky clear on read value. This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *   Status
    *    0: No error
    *    1: Error
    *
    *******************************************************************************/
    uint8 CyXTAL_ReadStatus(void) `=ReentrantKeil("CyXTAL_ReadStatus")`
    {
        /***************************************************************************
        * High output indicates oscillator failure. Only use this after start-up
        * interval is completed. This can be used for status and failure recovery.
        ***************************************************************************/
        return((0u != (CY_CLK_XMHZ_CSR_REG & CY_CLK_XMHZ_CSR_XERR)) ? 1u : 0u);
    }


    /*******************************************************************************
    * Function Name: CyXTAL_EnableFaultRecovery
    ********************************************************************************
    *
    * Summary:
    *  Enables the fault recovery circuit which will switch to the IMO in the case
    *  of a fault in the megahertz crystal circuit. The crystal must be up and
    *  running with the XERR bit at 0, before calling this function to prevent
    *  immediate fault switchover. This function is not available for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_EnableFaultRecovery(void) `=ReentrantKeil("CyXTAL_EnableFaultRecovery")`
    {
        CY_CLK_XMHZ_CSR_REG |= CY_CLK_XMHZ_CSR_XPROT;
    }


    /*******************************************************************************
    * Function Name: CyXTAL_DisableFaultRecovery
    ********************************************************************************
    *
    * Summary:
    *  Disables the fault recovery circuit which will switch to the IMO in the case
    *  of a fault in the megahertz crystal circuit. This function is not available
    *  for PSoC5.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_DisableFaultRecovery(void) `=ReentrantKeil("CyXTAL_DisableFaultRecovery")`
    {
        CY_CLK_XMHZ_CSR_REG &= ((uint8)(~CY_CLK_XMHZ_CSR_XPROT));
    }

#endif  /* (!CY_PSOC5A) */

/*******************************************************************************
* Function Name: CyXTAL_SetStartup
********************************************************************************
*
* Summary:
*  Sets the startup settings for the crystal. Logic model outputs a frequency
*  (setting + 4) MHz when enabled.
*
*  This is artificial as the actual frequency is determined by an attached
*  external crystal.
*
* Parameters:
*  setting: Valid range [0-31].
*   Value is dependent on the frequency and quality of the crystal being used.
*   Refer to the device TRM and datasheet for more information.
*
* Return:
*  None
*
*******************************************************************************/
void CyXTAL_SetStartup(uint8 setting) `=ReentrantKeil("CyXTAL_SetStartup")`
{
    CY_CLK_XMHZ_CFG0_REG = (CY_CLK_XMHZ_CFG0_REG & ((uint8)(~CY_CLK_XMHZ_CFG0_XCFG_MASK))) |
                           (setting & CY_CLK_XMHZ_CFG0_XCFG_MASK);
}


#if(CY_PSOC3 || CY_PSOC5LP)
    /*******************************************************************************
    * Function Name: CyXTAL_SetFbVoltage
    ********************************************************************************
    *
    * Summary:
    *  Sets the feedback reference voltage to use for the crystal circuit.
    *  This function is only available for PSoC3 and PSoC 5LP.
    *
    * Parameters:
    *  setting: Valid range [0-15].
    *  Refer to the device TRM and datasheet for more information.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_SetFbVoltage(uint8 setting) `=ReentrantKeil("CyXTAL_SetFbVoltage")`
    {
        CY_CLK_XMHZ_CFG1_REG = ((CY_CLK_XMHZ_CFG1_REG & ((uint8)(~CY_CLK_XMHZ_CFG1_VREF_FB_MASK))) |
                                (setting & CY_CLK_XMHZ_CFG1_VREF_FB_MASK));
    }


    /*******************************************************************************
    * Function Name: CyXTAL_SetWdVoltage
    ********************************************************************************
    *
    * Summary:
    *  Sets the reference voltage used by the watchdog to detect a failure in the
    *  crystal circuit. This function is only available for PSoC3 and PSoC 5LP.
    *
    * Parameters:
    *  setting: Valid range [0-7].
    *  Refer to the device TRM and datasheet for more information.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyXTAL_SetWdVoltage(uint8 setting) `=ReentrantKeil("CyXTAL_SetWdVoltage")`
    {
        CY_CLK_XMHZ_CFG1_REG = ((CY_CLK_XMHZ_CFG1_REG & ((uint8)(~CY_CLK_XMHZ_CFG1_VREF_WD_MASK))) |
                                (((uint8)(setting << 4u)) & CY_CLK_XMHZ_CFG1_VREF_WD_MASK));
    }

#endif /* (CY_PSOC3 || CY_PSOC5LP) */


/*******************************************************************************
* Function Name: CyHalt
********************************************************************************
*
* Summary:
*  Halts the CPU.
*
* Parameters:
*  uint8 reason: Value to be used during debugging.
*
* Return:
*  None
*
*******************************************************************************/
void CyHalt(uint8 reason) CYREENTRANT
{
    if(0u != reason)
    {
        /* To remove unreferenced local variable warning */
    }

    #if defined (__ARMCC_VERSION)
        __breakpoint(0x0);
    #elif defined(__GNUC__)
        __asm("    bkpt    1");
    #elif defined(__C51__)
        CYDEV_HALT_CPU;
    #endif  /* (__ARMCC_VERSION) */
}


/*******************************************************************************
* Function Name: CySoftwareReset
********************************************************************************
*
* Summary:
*  Forces a software reset of the device.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySoftwareReset(void) `=ReentrantKeil("CySoftwareReset")`
{
    /* Perform software reset */
    *RESET_CR2 = 0x1u;
}


/*******************************************************************************
* Function Name: CyDelay
********************************************************************************
*
* Summary:
*  Blocks for milliseconds.
*
*  Note:
*  CyDelay has been implemented with the instruction cache assumed enabled. When
*  instruction cache is disabled on PSoC5, CyDelay will be two times larger. For
*  example, with instruction cache disabled CyDelay(100) would result in about
*  200 ms delay instead of 100 ms.
*
* Parameters:
*  milliseconds: number of milliseconds to delay.
*
* Return:
*   None
*
*******************************************************************************/
void CyDelay(uint32 milliseconds) CYREENTRANT
{
    while (milliseconds > 32768u)
    {
        /***********************************************************************
        * This loop prevents overflow.At 100MHz, milliseconds * delay_freq_khz
        * overflows at about 42 seconds.
        ***********************************************************************/
        CyDelayCycles(cydelay_32k_ms);
        milliseconds = ((uint32)(milliseconds - 32768u));
    }

    CyDelayCycles(milliseconds * cydelay_freq_khz);
}


#if(!CY_PSOC3)

    /* For PSoC3 devices function is defined in CyBootAsmKeil.a51 file */

    /*******************************************************************************
    * Function Name: CyDelayUs
    ********************************************************************************
    *
    * Summary:
    *  Blocks for microseconds.
    *
    *  Note:
    *   CyDelay has been implemented with the instruction cache assumed enabled.
    *   When instruction cache is disabled on PSoC5, CyDelayUs will be two times
    *   larger. Ex: With instruction cache disabled CyDelayUs(100) would result
    *   in about 200us delay instead of 100us.
    *
    * Parameters:
    *  uint16 microseconds: number of microseconds to delay.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  CyDelayUS has been implemented with the instruction cache assumed enabled.
    *  When instruction cache is disabled on PSoC 5, CyDelayUs will be two times
    *  larger. For example, with instruction cache disabled CyDelayUs(100) would
    *  result in about 200 us delay instead of 100 us.
    *
    *  If the bus clock frequency is a small non-integer number, the actual delay
    *  can be up to twice as long as the nominal value. The actual delay cannot be
    *  shorter than the nominal one.
    *******************************************************************************/
    void CyDelayUs(uint16 microseconds) CYREENTRANT
    {
        CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
    }

#endif  /* (!CY_PSOC3) */


/*******************************************************************************
* Function Name: CyDelayFreq
********************************************************************************
*
* Summary:
*  Sets clock frequency for CyDelay.
*
* Parameters:
*  freq: Frequency of bus clock in Hertz.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelayFreq(uint32 freq) CYREENTRANT
{
    if (freq != 0u)
    {
        cydelay_freq_hz = freq;
    }
    else
    {
        cydelay_freq_hz = BCLK__BUS_CLK__HZ;
    }

    cydelay_freq_mhz = (uint8)((cydelay_freq_hz + 999999u) / 1000000u);
    cydelay_freq_khz = (cydelay_freq_hz + 999u) / 1000u;
    cydelay_32k_ms   = 32768u * cydelay_freq_khz;
}


/*******************************************************************************
* Function Name: CyWdtStart
********************************************************************************
*
* Summary:
*  Enables the watchdog timer.
*
*  The timer is configured for the specified count interval, the central
*  timewheel is cleared, the setting for low power mode is configured and the
*  watchdog timer is enabled.
*
*  Once enabled the watchdog cannot be disabled. The watchdog counts each time
*  the Central Time Wheel (CTW) reaches the period specified. The watchdog must
*  be cleared using the CyWdtClear() function before three ticks of the watchdog
*  timer occur. The CTW is free running, so this will occur after between 2 and
*  3 timer periods elapse.
*
*  PSoC5: The watchdog timer should not be used during sleep modes. Since the
*  WDT cannot be disabled after it is enabled, the WDT timeout period can be
*  set to be greater than the sleep wakeup period, then feed the dog on each
*  wakeup from Sleep.
*
* Parameters:
*  ticks: One of the four available timer periods. Once WDT enabled, the
   interval cannot be changed.
*         CYWDT_2_TICKS     -     4 - 6     ms
*         CYWDT_16_TICKS    -    32 - 48    ms
*         CYWDT_128_TICKS   -   256 - 384   ms
*         CYWDT_1024_TICKS  - 2.048 - 3.072 s
*
*  lpMode: Low power mode configuration. This parameter is ignored for PSoC 5.
*          The WDT always acts as if CYWDT_LPMODE_NOCHANGE is passed.
*
*          CYWDT_LPMODE_NOCHANGE - No Change
*          CYWDT_LPMODE_MAXINTER - Switch to longest timer mode during low power
*                                 mode
*          CYWDT_LPMODE_DISABLED - Disable WDT during low power mode
*
* Return:
*  None
*
* Side Effects:
*  PSoC5: The ILO 1 KHz must be enabled for proper WDT operation. Stopping the
*  ILO 1 kHz could break the active WDT functionality.
*
*******************************************************************************/
void CyWdtStart(uint8 ticks, uint8 lpMode) `=ReentrantKeil("CyWdtStart")`
{
    #if(CY_PSOC5A)
        CyILO_Start1K();
    #endif  /* (CY_PSOC5A) */

    /* Set WDT interval */
    CY_WDT_CFG_REG = (CY_WDT_CFG_REG & ((uint8)(~CY_WDT_CFG_INTERVAL_MASK))) | (ticks & CY_WDT_CFG_INTERVAL_MASK);

    /* Reset CTW to ensure that first watchdog period is full */
    CY_WDT_CFG_REG |= CY_WDT_CFG_CTW_RESET;
    CY_WDT_CFG_REG &= ((uint8)(~CY_WDT_CFG_CTW_RESET));

    #if(!CY_PSOC5A)

        /* Setting the low power mode */
        CY_WDT_CFG_REG = (((uint8)(lpMode << CY_WDT_CFG_LPMODE_SHIFT)) & CY_WDT_CFG_LPMODE_MASK) |
                          (CY_WDT_CFG_REG & ((uint8)(~CY_WDT_CFG_LPMODE_MASK)));
    #else

        if(0u != lpMode)
        {
            /* To remove unreferenced local variable warning */
        }

    #endif  /* (!CY_PSOC5A) */

    /* Enables the watchdog reset */
    CY_WDT_CFG_REG |= CY_WDT_CFG_WDR_EN;
}


/*******************************************************************************
* Function Name: CyWdtClear
********************************************************************************
*
* Summary:
*  Clears (feeds) the watchdog timer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyWdtClear(void) `=ReentrantKeil("CyWdtClear")`
{
    #if(CY_PSOC5A)

        /* PSoC5 ES1 watchdog time clear requires workaround */
        uint8 wdtCfg = CY_WDT_CFG_REG;
        CY_WDT_CR_REG  = CY_WDT_CR_FEED;
        CY_WDT_CFG_REG = CY_WDT_CFG_CLEAR_ALL;
        CY_WDT_CFG_REG = wdtCfg;

    #else

        CY_WDT_CR_REG = CY_WDT_CR_FEED;

    #endif  /* (CY_PSOC5A) */
}



/*******************************************************************************
* Function Name: CyVdLvDigitEnable
********************************************************************************
*
* Summary:
*  Enables the digital low voltage monitors to generate interrupt on Vddd
*   archives specified threshold and optionally resets device.
*
* Parameters:
*  reset: Option to reset device at a specified Vddd threshold:
*           0 - Device is not reset.
*           1 - Device is reset.
*         This option is applicable for PSoC 3/PSoC 5LP devices only.
*
*  threshold: Sets the trip level for the voltage monitor.
*  Values from 1.70 V to 5.45 V(for PSoC 3/PSoC 5LP) and from 2.45 V to 5.45 V
*  (for PSoC 5TM) are accepted with the approximately 250 mV interval.
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvDigitEnable(uint8 reset, uint8 threshold) `=ReentrantKeil("CyVdLvDigitEnable")`
{
    *CY_INT_CLEAR_PTR = 0x01u;

    #if(!CY_PSOC5A)
        CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESD_EN));
    #endif /*(!CY_PSOC5A)*/

    CY_VD_LVI_TRIP_REG = (threshold & CY_VD_LVI_TRIP_LVID_MASK) |
                            (CY_VD_LVI_TRIP_REG & ((uint8)(~CY_VD_LVI_TRIP_LVID_MASK)));
    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_LVID_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);

	(void)CY_VD_PERSISTENT_STATUS_REG;

    #if(!CY_PSOC5A)
        if(0u != reset)
        {
            CY_VD_PRES_CONTROL_REG |= CY_VD_PRESD_EN;
        }
        else
        {
            CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESD_EN));
        }
    #else

        if(0u != reset)
        {
            /* To remove unreferenced local variable warning */
        }

    #endif /*(!CY_PSOC5A)*/

    *CY_INT_CLR_PEND_PTR = 0x01u;
    *CY_INT_ENABLE_PTR   = 0x01u;
}


/*******************************************************************************
* Function Name: CyVdLvAnalogEnable
********************************************************************************
*
* Summary:
*  Enables the analog low voltage monitors to generate interrupt on Vdda
*   archives specified threshold and optionally resets device.
*
* Parameters:
*  reset: Option to reset device at a specified Vdda threshold:
*           0 - Device is not reset.
*           1 - Device is reset.
*         This option is applicable for PSoC 3/PSoC 5LP devices only.
*
*  threshold: Sets the trip level for the voltage monitor.
*  Values from 1.70 V to 5.45 V(for PSoC 3/PSoC 5LP) and from 2.45 V to 5.45 V
*  (for PSoC 5TM) are accepted with the approximately 250 mV interval.
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvAnalogEnable(uint8 reset, uint8 threshold) `=ReentrantKeil("CyVdLvAnalogEnable")`
{
    *CY_INT_CLEAR_PTR = 0x01u;

    #if(!CY_PSOC5A)
        CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESA_EN));
    #endif /*(!CY_PSOC5A)*/

    CY_VD_LVI_TRIP_REG = ((uint8)(threshold << 4u)) | (CY_VD_LVI_TRIP_REG & 0x0Fu);
    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_LVIA_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);

	(void)CY_VD_PERSISTENT_STATUS_REG;

    #if(!CY_PSOC5A)
        if(0u != reset)
        {
            CY_VD_PRES_CONTROL_REG |= CY_VD_PRESA_EN;
        }
        else
        {
            CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESA_EN));
        }
    #else

        if(0u != reset)
        {
            /* To remove unreferenced local variable warning */
        }

    #endif /*(!CY_PSOC5A)*/

    *CY_INT_CLR_PEND_PTR = 0x01u;
    *CY_INT_ENABLE_PTR   = 0x01u;
}


/*******************************************************************************
* Function Name: CyVdLvDigitDisable
********************************************************************************
*
* Summary:
*  Disables the digital low voltage monitor (interrupt and device reset are
*  disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvDigitDisable(void) `=ReentrantKeil("CyVdLvDigitDisable")`
{
    CY_VD_LVI_HVI_CONTROL_REG &= ((uint8)(~CY_VD_LVID_EN));

    #if(!CY_PSOC5A)
        CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESD_EN));
    #endif /*(!CY_PSOC5A)*/

    while(0u != (CY_VD_PERSISTENT_STATUS_REG & 0x07u))
    {

    }
}


/*******************************************************************************
* Function Name: CyVdLvAnalogDisable
********************************************************************************
*
* Summary:
*  Disables the analog low voltage monitor
*  (interrupt and device reset are disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdLvAnalogDisable(void) `=ReentrantKeil("CyVdLvAnalogDisable")`
{
    CY_VD_LVI_HVI_CONTROL_REG &= ((uint8)(~CY_VD_LVIA_EN));

    #if(!CY_PSOC5A)
        CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESA_EN));
    #endif /*(!CY_PSOC5A)*/

    while(0u != (CY_VD_PERSISTENT_STATUS_REG & 0x07u))
    {

    }
}


/*******************************************************************************
* Function Name: CyVdHvAnalogEnable
********************************************************************************
*
* Summary:
*  Enables the analog high voltage monitors to generate interrupt on
*  Vdda archives 5.75 V threshold and optionally resets device.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdHvAnalogEnable(void) `=ReentrantKeil("CyVdHvAnalogEnable")`
{
    *CY_INT_CLEAR_PTR = 0x01u;

    #if(!CY_PSOC5A)
        CY_VD_PRES_CONTROL_REG &= ((uint8)(~CY_VD_PRESA_EN));
    #endif /*(!CY_PSOC5A)*/

    CY_VD_LVI_HVI_CONTROL_REG |= CY_VD_HVIA_EN;

    /* Timeout to eliminate glitches on the LVI/HVI when enabling */
    CyDelayUs(1u);

	(void) CY_VD_PERSISTENT_STATUS_REG;

    *CY_INT_CLR_PEND_PTR = 0x01u;
    *CY_INT_ENABLE_PTR   = 0x01u;
}


/*******************************************************************************
* Function Name: CyVdHvAnalogDisable
********************************************************************************
*
* Summary:
*  Disables the analog low voltage monitor
*  (interrupt and device reset are disabled).
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CyVdHvAnalogDisable(void) `=ReentrantKeil("CyVdHvAnalogDisable")`
{
    CY_VD_LVI_HVI_CONTROL_REG &= ((uint8)(~CY_VD_HVIA_EN));
}


/*******************************************************************************
* Function Name: CyVdStickyStatus
********************************************************************************
*
* Summary:
*  Manages the Reset and Voltage Detection Status Register 0.
*  This register has the interrupt status for the HVIA, LVID and LVIA.
*  This hardware register clears on read.
*
* Parameters:
*  mask: Bits in the shadow register to clear.
*       Value        Define                Bit To Clear
*       0x01         CY_VD_LVID            LVID
*       0x02         CY_VD_LVIA            LVIA
*       0x04         CY_VD_HVIA            HVIA
*
* Return:
*  Status.  Same enumerated bit values as used for the mask parameter.
*
*******************************************************************************/
uint8 CyVdStickyStatus(uint8 mask) `=ReentrantKeil("CyVdStickyStatus")`
{
    uint8 status;

    status = CY_VD_PERSISTENT_STATUS_REG;
    CY_VD_PERSISTENT_STATUS_REG &= ((uint8)(~mask));

    return(status);
}


/*******************************************************************************
* Function Name: CyVdRealTimeStatus
********************************************************************************
*
* Summary:
*  Returns the real time voltage detection status.
*
* Parameters:
*  None
*
* Return:
*  Status. Same enumerated bit values as used for the mask parameter.
*
*******************************************************************************/
uint8 CyVdRealTimeStatus(void) `=ReentrantKeil("CyVdRealTimeStatus")`
{
    uint8 interruptState;
    uint8 vdFlagsState;

    interruptState = CyEnterCriticalSection();
    vdFlagsState = CY_VD_RT_STATUS_REG;
    CyExitCriticalSection(interruptState);

    return(vdFlagsState);
}


/*******************************************************************************
* Function Name: CyDisableInts
********************************************************************************
*
* Summary:
*  Disables the interrupt enable for each interrupt.
*
* Parameters:
*  None
*
* Return:
*  32 bit mask of previously enabled interrupts.
*
*******************************************************************************/
uint32 CyDisableInts(void) `=ReentrantKeil("CyDisableInts")`
{
    uint32 intState;
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    #if(CY_PSOC3)

        /* Get the current interrupt state. */
        intState  = ((uint32) CY_GET_REG8(CY_INT_CLR_EN0_PTR));
        intState |= ((uint32) (((uint32) CY_GET_REG8(CY_INT_CLR_EN1_PTR)) << 8u));
        intState |= ((uint32) (((uint32) CY_GET_REG8(CY_INT_CLR_EN2_PTR)) << 16u));
        intState |= ((uint32) (((uint32) CY_GET_REG8(CY_INT_CLR_EN3_PTR)) << 24u));


        /* Disable all of the interrupts. */
        CY_SET_REG8(CY_INT_CLR_EN0_PTR, 0xFFu);
        CY_SET_REG8(CY_INT_CLR_EN1_PTR, 0xFFu);
        CY_SET_REG8(CY_INT_CLR_EN2_PTR, 0xFFu);
        CY_SET_REG8(CY_INT_CLR_EN3_PTR, 0xFFu);

    #else

        /* Get the current interrupt state. */
        intState = CY_GET_REG32(CY_INT_CLEAR_PTR);

        /* Disable all of the interrupts. */
        CY_SET_REG32(CY_INT_CLEAR_PTR, 0xFFFFFFFFu);

    #endif /* (CY_PSOC3) */

    CyExitCriticalSection(interruptState);

    return (intState);
}


/*******************************************************************************
* Function Name: CyEnableInts
********************************************************************************
*
* Summary:
*  Enables interrupts to a given state.
*
* Parameters:
*  uint32 mask: 32 bit mask of interrupts to enable.
*
* Return:
*  None
*
*******************************************************************************/
void CyEnableInts(uint32 mask) `=ReentrantKeil("CyEnableInts")`
{

    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    #if(CY_PSOC3)

        /* Set interrupts as enabled. */
        CY_SET_REG8(CY_INT_SET_EN3_PTR, ((uint8) (mask >> 24u)));
        CY_SET_REG8(CY_INT_SET_EN2_PTR, ((uint8) (mask >> 16u)));
        CY_SET_REG8(CY_INT_SET_EN1_PTR, ((uint8) (mask >> 8u )));
        CY_SET_REG8(CY_INT_SET_EN0_PTR, ((uint8) (mask )));

    #else

        CY_SET_REG32(CY_INT_ENABLE_PTR, mask);

    #endif /* (CY_PSOC3) */

    CyExitCriticalSection(interruptState);

}

#if(CY_PSOC5)

    /*******************************************************************************
    * Function Name: CyFlushCache
    ********************************************************************************
    * Summary:
    *  Flushes the PSoC 5/5LP cache by invalidating all entries.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyFlushCache(void)
    {
        uint8 interruptState;

        /* Save current global interrupt enable and disable it */
        interruptState = CyEnterCriticalSection();

        /* Fill instruction prefectch unit to insure data integrity */
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;

        /* All entries in the cache are invalidated on the next clock cycle. */
        CY_CACHE_CONTROL_REG |= CY_CACHE_CONTROL_FLUSH;


        /***********************************************************************
        * The prefetch unit could/would be filled with the instructions that
        * succeed the flush. Since a flush is desired then theoretically those
        * instructions might be considered stale/invalid.
        ***********************************************************************/
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;
        CY_NOP;

        /* Restore global interrupt enable state */
        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CyIntSetSysVector
    ********************************************************************************
    * Summary:
    *  Sets the interrupt vector of the specified system interrupt number. System
    *  interrupts are present only for the ARM platform. These interrupts are for
    *  SysTick, PendSV and others.
    *
    * Parameters:
    *  number: Interrupt number, valid range [0-15].
       address: Pointer to an interrupt service routine.
    *
    * Return:
    *   The old ISR vector at this location.
    *
    *******************************************************************************/
    cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address)
    {
        cyisraddress oldIsr;
        cyisraddress *ramVectorTable = *CY_INT_VECT_TABLE;

        CYASSERT(number <= CY_INT_SYS_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = ramVectorTable[number & CY_INT_SYS_NUMBER_MASK];

        /* Set new Interrupt service routine. */
        ramVectorTable[number & CY_INT_SYS_NUMBER_MASK] = address;

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetSysVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified system interrupt number. System
    *  interrupts are present only for the ARM platform. These interrupts are for
    *  SysTick, PendSV and others.
    *
    * Parameters:
    *   number: The interrupt number, valid range [0-15].
    *
    * Return:
    *   Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetSysVector(uint8 number)
    {
        cyisraddress *ramVectorTable = *CY_INT_VECT_TABLE;
        CYASSERT(number <= CY_INT_SYS_NUMBER_MAX);

        return ramVectorTable[number & CY_INT_SYS_NUMBER_MASK];
    }


    /*******************************************************************************
    * Function Name: CyIntSetVector
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *  address: Pointer to an interrupt service routine
    *
    * Return:
    *   Previous interrupt vector value.
    *
    *******************************************************************************/
    cyisraddress CyIntSetVector(uint8 number, cyisraddress address)
    {
        cyisraddress oldIsr;
        cyisraddress *ramVectorTable = *CY_INT_VECT_TABLE;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = ramVectorTable[CY_INT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)];

        /* Set new Interrupt service routine. */
        ramVectorTable[CY_INT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)] = address;

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetVector(uint8 number)
    {
        cyisraddress *ramVectorTable = *CY_INT_VECT_TABLE;
        CYASSERT(number <= CY_INT_NUMBER_MAX);

        return (ramVectorTable[CY_INT_IRQ_BASE + (number & CY_INT_NUMBER_MASK)]);
    }


    /*******************************************************************************
    * Function Name: CyIntSetPriority
    ********************************************************************************
    *
    * Summary:
    *  Sets the Priority of the Interrupt.
    *
    * Parameters:
    *  priority: Priority of the interrupt. 0 - 7, 0 being the highest.
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPriority(uint8 number, uint8 priority)
    {
        CYASSERT(priority <= CY_INT_PRIORITY_MAX);
        CYASSERT(number <= CY_INT_NUMBER_MAX);
        CY_INT_PRIORITY_PTR[number & CY_INT_NUMBER_MASK] = (priority & CY_INT_PRIORITY_MASK)<< 5;
    }


    /*******************************************************************************
    * Function Name: CyIntGetPriority
    ********************************************************************************
    *
    * Summary:
    *  Gets the Priority of the Interrupt.
    *
    * Parameters:
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  Priority of the interrupt. 0 - 7, 0 being the highest.
    *
    *******************************************************************************/
    uint8 CyIntGetPriority(uint8 number)
    {
        uint8 priority;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        priority = CY_INT_PRIORITY_PTR[number & CY_INT_NUMBER_MASK] >> 5;

        return (priority);
    }


    /*******************************************************************************
    * Function Name: CyIntGetState
    ********************************************************************************
    *
    * Summary:
    *   Gets the enable state of the specified interrupt number.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *   Enable status: 1 if enabled, 0 if disabled
    *
    *******************************************************************************/
    uint8 CyIntGetState(uint8 number)
    {
        reg32 * stateReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        stateReg = CY_INT_ENABLE_PTR;

        /* Get the state of the interrupt. */
        return (0u != (*stateReg & (((uint32) 1u) << (0x1Fu & number)))) ? ((uint8)(1u)) : ((uint8)(0u));
    }


#else   /* PSoC3 */


    /*******************************************************************************
    * Function Name: CyIntSetVector
    ********************************************************************************
    *
    * Summary:
    *  Sets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number:  Valid range [0-31].  Interrupt number
    *  address: Pointer to an interrupt service routine
    *
    * Return:
    *  Previous interrupt vector value.
    *
    *******************************************************************************/
    cyisraddress CyIntSetVector(uint8 number, cyisraddress address) `=ReentrantKeil("CyIntSetVector")`
    {
        cyisraddress oldIsr;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Save old Interrupt service routine. */
        oldIsr = (cyisraddress) \
                    CY_GET_REG16(&CY_INT_VECT_TABLE[number & CY_INT_NUMBER_MASK]);

        /* Set new Interrupt service routine. */
        CY_SET_REG16(&CY_INT_VECT_TABLE[number], (uint16) address);

        return (oldIsr);
    }


    /*******************************************************************************
    * Function Name: CyIntGetVector
    ********************************************************************************
    *
    * Summary:
    *  Gets the interrupt vector of the specified interrupt number.
    *
    * Parameters:
    *  number: Valid range [0-31].  Interrupt number
    *
    * Return:
    *  Address of the ISR in the interrupt vector table.
    *
    *******************************************************************************/
    cyisraddress CyIntGetVector(uint8 number) `=ReentrantKeil("CyIntGetVector")`
    {
        CYASSERT(number <= CY_INT_NUMBER_MAX);

        return ((cyisraddress) \
                CY_GET_REG16(&CY_INT_VECT_TABLE[number & CY_INT_NUMBER_MASK]));
    }


    /*******************************************************************************
    * Function Name: CyIntSetPriority
    ********************************************************************************
    *
    * Summary:
    *  Sets the Priority of the Interrupt.
    *
    * Parameters:
    *  priority: Priority of the interrupt. 0 - 7, 0 being the highest.
    *  number:   The number of the interrupt, 0 - 31.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CyIntSetPriority(uint8 number, uint8 priority) `=ReentrantKeil("CyIntSetPriority")`
    {
        CYASSERT(priority <= CY_INT_PRIORITY_MAX);

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        CY_INT_PRIORITY_PTR[number & CY_INT_NUMBER_MASK] =
                    (priority & CY_INT_PRIORITY_MASK) << 5;
    }


    /*******************************************************************************
    * Function Name: CyIntGetPriority
    ********************************************************************************
    *
    * Summary:
    *  Gets the Priority of the Interrupt.
    *
    * Parameters:
    *  number: The number of the interrupt, 0 - 31.
    *
    * Return:
    *  Priority of the interrupt. 0 - 7, 0 being the highest.
    *
    *******************************************************************************/
    uint8 CyIntGetPriority(uint8 number) `=ReentrantKeil("CyIntGetPriority")`
    {
        uint8 priority;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        priority = CY_INT_PRIORITY_PTR[number & CY_INT_NUMBER_MASK] >> 5;

        return (priority);
    }


    /*******************************************************************************
    * Function Name: CyIntGetState
    ********************************************************************************
    *
    * Summary:
    *   Gets the enable state of the specified interrupt number.
    *
    * Parameters:
    *   number: Valid range [0-31].  Interrupt number.
    *
    * Return:
    *   Enable status: 1 if enabled, 0 if disabled
    *
    *******************************************************************************/
    uint8 CyIntGetState(uint8 number) `=ReentrantKeil("CyIntGetState")`
    {
        reg8 * stateReg;

        CYASSERT(number <= CY_INT_NUMBER_MAX);

        /* Get a pointer to the Interrupt enable register. */
        stateReg = CY_INT_ENABLE_PTR + ((number & CY_INT_NUMBER_MASK) >> 3u);

        /* Get the state of the interrupt. */
        return ((0u != (*stateReg & ((uint8)(1u << (0x07u & number))))) ? ((uint8)(1u)) : ((uint8)(0u)));
    }


#endif  /* (CY_PSOC5) */


#if(!CY_PSOC5A)

    #if(CYDEV_VARIABLE_VDDA == 1)


        /*******************************************************************************
        * Function Name: CySetScPumps
        ********************************************************************************
        *
        * Summary:
        *  If 1 is passed as a parameter:
        *   - if any of the SC blocks are used - enable pumps for the SC blocks and
        *     start boost clock.
        *   - For the each enabled SC block set boost clock index and enable boost clock.
        *
        *  If non-1 value is passed as a parameter:
        *   - If all SC blocks are not used - disable pumps for the SC blocks and
        *     stop boost clock.
        *   - For the each enabled SC block clear boost clock index and disable boost
        *     clock.
		*
        *  The global variable CyScPumpEnabled is updated to be equal to passed
        *  parameter.
        *
        * Parameters:
        *   uint8 enable: Enable/disable SC pumps and boost clock for enabled SC block.
        *                 1 - Enable
        *                 0 - Disable
        *
        * Return:
        *   None
        *
        *******************************************************************************/
        void CySetScPumps(uint8 enable) `=ReentrantKeil("CySetScPumps")`
        {

            if(1u == enable)
            {
                /* The SC pumps should be enabled */
                CyScPumpEnabled = 1u;


                /* Enable pumps if any of SC blocks are used */
                if(0u != (CY_LIB_ACT_CFG9_REG & CY_LIB_ACT_CFG9_SWCAPS_MASK))
                {

                    CY_LIB_SC_MISC_REG |= CY_LIB_SC_MISC_PUMP_FORCE;

                    CyScBoostClk_Start();
                }


                /* Set positive pump for each enabled SC block: set clock index and enable it */
                if(0u != (CY_LIB_ACT_CFG9_REG & CY_LIB_ACT_CFG9_SWCAP0_EN))
                {
                    CY_LIB_SC0_BST_REG = (CY_LIB_SC0_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK) | CyScBoostClk__INDEX;
                    CY_LIB_SC0_BST_REG |= CY_LIB_SC_BST_CLK_EN;
                }

                if(0u != (CY_LIB_ACT_CFG9_REG & CY_LIB_ACT_CFG9_SWCAP1_EN))
                {
                    CY_LIB_SC1_BST_REG = (CY_LIB_SC1_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK) | CyScBoostClk__INDEX;
                    CY_LIB_SC1_BST_REG |= CY_LIB_SC_BST_CLK_EN;
                }

                if(0u != (CY_LIB_ACT_CFG9_REG & CY_LIB_ACT_CFG9_SWCAP2_EN))
                {
                    CY_LIB_SC2_BST_REG = (CY_LIB_SC2_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK) | CyScBoostClk__INDEX;
                    CY_LIB_SC2_BST_REG |= CY_LIB_SC_BST_CLK_EN;
                }

                if(0u != (CY_LIB_ACT_CFG9_REG & CY_LIB_ACT_CFG9_SWCAP3_EN))
                {
                    CY_LIB_SC3_BST_REG = (CY_LIB_SC3_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK) | CyScBoostClk__INDEX;
                    CY_LIB_SC3_BST_REG |= CY_LIB_SC_BST_CLK_EN;
                }
            }
            else
            {
                /* The SC pumps should be disabled */
                CyScPumpEnabled = 0u;

                /* Disable pumps for all SC blocks and stop boost clock */
                CY_LIB_SC_MISC_REG &= ((uint8)(~CY_LIB_SC_MISC_PUMP_FORCE));
                CyScBoostClk_Stop();

                /* Disable boost clock and clear clock index for each SC block */
                CY_LIB_SC0_BST_REG &= ((uint8)(~CY_LIB_SC_BST_CLK_EN));
                CY_LIB_SC0_BST_REG = CY_LIB_SC0_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK;

                CY_LIB_SC1_BST_REG &= ((uint8)(~CY_LIB_SC_BST_CLK_EN));
                CY_LIB_SC1_BST_REG = CY_LIB_SC1_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK;

                CY_LIB_SC2_BST_REG &= ((uint8)(~CY_LIB_SC_BST_CLK_EN));
                CY_LIB_SC2_BST_REG = CY_LIB_SC2_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK;

                CY_LIB_SC3_BST_REG &= ((uint8)(~CY_LIB_SC_BST_CLK_EN));
                CY_LIB_SC3_BST_REG = CY_LIB_SC3_BST_REG & CY_LIB_SC_BST_CLK_INDEX_MASK;
            }
        }

    #endif  /* (CYDEV_VARIABLE_VDDA == 1) */

#endif /* (!CY_PSOC5A) */


/* [] END OF FILE */
