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
* Copyright 2010-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"

/* Convertion between CySysClkWriteImoFreq() parameter and register's value */
static const uint8 cyImoFreqMhz2Reg[49u] = {
     3u,  3u,  3u,  3u,  4u,  5u,  6u,  7u,  8u,  9u, 10u, 11u, 12u,
    14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u,
    27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u,
    37u, 38u, 39u, 40u, 41u, 42u, 43u,
    46u, 47u, 48u, 49u, 50u, 51u, 52u, 53u};

/* Convertion table between register's value and frequency */
static const uint8 cyImoFreqReg2Mhz[54u] = {
     3u,  3u,  3u,  3u,  4u,  5u,  6u,  7u,  8u,  9u, 10u, 11u, 12u,
    13u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u,
    25u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u,
    33u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u,
    41u, 41u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u};


/*******************************************************************************
* Function Name: CySysClkImoStart
********************************************************************************
*
* Summary:
*  Enables the IMO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkImoStart()
{
    /* Sets the IMO clock enable bit */
    CY_SET_REG32(CY_CLK_IMO_CONFIG_PTR, CY_GET_REG32(CY_CLK_IMO_CONFIG_PTR) |
        CY_CLK_IMO_CONFIG_ENABLE);
}


/*******************************************************************************
* Function Name: CySysClkImoStop
********************************************************************************
*
* Summary:
*  Disables the IMO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkImoStop()
{
    CY_SET_REG32(CY_CLK_IMO_CONFIG_PTR, CY_GET_REG32(CY_CLK_IMO_CONFIG_PTR) &
        ~CY_CLK_IMO_CONFIG_ENABLE);
}


/*******************************************************************************
* Function Name: CySysClkIloStart
********************************************************************************
*
* Summary:
*  Enables the ILO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkIloStart(void)
{
    CY_SET_REG32(CY_CLK_ILO_CONFIG_PTR, CY_GET_REG32(CY_CLK_ILO_CONFIG_PTR) |
        CY_CLK_ILO_CONFIG_ENABLE);
}


/*******************************************************************************
* Function Name: CySysClkIloStop
********************************************************************************
*
* Summary:
*  Disables the ILO.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkIloStop(void)
{
    CY_SET_REG32(CY_CLK_ILO_CONFIG_PTR, CY_GET_REG32(CY_CLK_ILO_CONFIG_PTR) &
        ~CY_CLK_ILO_CONFIG_ENABLE);
}


/*******************************************************************************
* Function Name: CySysClkWriteHfclkDirect
********************************************************************************
*
* Summary:
*  Selects the direct source for the HFCLK.
*
* Parameters:
*  clkSelect: One of the available HFCLK direct sources
*   Value        Define                    Source
*    0            CY_SYS_CLK_HFCLK_IMO      IMO
*    1            CY_SYS_CLK_HFCLK_EXTCLK   External clock pin
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkWriteHfclkDirect(uint8 clkSelect)
{
    CY_SET_REG32(CY_CLK_SELECT_PTR, (CY_GET_REG32(CY_CLK_SELECT_PTR) &
        ~CY_CLK_HFCLK_SELECT_SET) | ((clkSelect & CY_CLK_HFCLK_SELECT_MASK)));
}


/*******************************************************************************
* Function Name: CySysClkWriteSysclkDiv
********************************************************************************
*
* Summary:
*  Selects the pre-scaler divide amount for SYSCLK from HFCLK.
*
* Parameters:
*  divider: Power of 2 prescaler selection
*
*   Value    Define                        Divider
*   0        CY_SYS_CLK_SYSCLK_DIV1        1
*   1        CY_SYS_CLK_SYSCLK_DIV2        2
*   2        CY_SYS_CLK_SYSCLK_DIV4        4
*   3        CY_SYS_CLK_SYSCLK_DIV8        8
*   4        CY_SYS_CLK_SYSCLK_DIV16       16
*   5        CY_SYS_CLK_SYSCLK_DIV32       32
*   6        CY_SYS_CLK_SYSCLK_DIV64       64
*   7        CY_SYS_CLK_SYSCLK_DIV128      128
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkWriteSysclkDiv(uint8 divider)
{
    CY_SET_REG32(CY_CLK_SELECT_PTR, CY_GET_REG32(CY_CLK_SELECT_PTR) |
        ((divider & CY_CLK_SYSCLK_SELECT_MASK) << CY_CLK_HFCLK_FROM_SYSCLK));
}


/*******************************************************************************
* Function Name: CySysClkWriteImoFreq
********************************************************************************
*
* Summary:
*  Sets the frequency of the IMO.
*
* Parameters:
*  freq: Valid range [3-48].  Frequency for operation of the IMO.
*  Note: Invalid frequency will be ignored.
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkWriteImoFreq(uint8 freq)
{
    uint8 currentFreq;
    uint32 inr = CY_GET_REG32(CYREG_CLK_IMO_TRIM2) & CLK_IMO_FREQ_BITS_MASK;
    currentFreq = cyImoFreqReg2Mhz[inr];

    /* Invalid range is ignored */
    CYASSERT(freq < 49);

    if(freq <= 48)
    {
        if(currentFreq >= freq)
        {
            /* Set the frequency register */
            CY_SET_REG32((CYREG_CLK_IMO_TRIM2), cyImoFreqMhz2Reg[freq & CLK_IMO_FREQ_BITS_MASK]);
            CyDelayCycles(5u);

            /* Set the trim register */
            CY_SET_REG32((CYREG_CLK_IMO_TRIM1), (CY_GET_REG32(CYREG_SFLASH_IMO_TRIM21)));
            CyDelayUs(5u);
        }
        else
        {
            CY_SET_REG32((CYREG_CLK_IMO_TRIM1), (CY_GET_REG32(CYREG_SFLASH_IMO_TRIM21)));
            CyDelayUs(5u);
            CY_SET_REG32((CYREG_CLK_IMO_TRIM2), cyImoFreqMhz2Reg[freq & CLK_IMO_FREQ_BITS_MASK]);
            CyDelayCycles(5u);
        }
    }
}


/*******************************************************************************
* Function Name: CySysWdtLock
********************************************************************************
*
* Summary:
*  Locks out configuration changes to the Watchdog timer register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysWdtLock(void)
{
    /* CLK_SELECT register's bits 15:14 are WDT_LOCK */
    CY_SET_REG32(CY_CLK_SELECT_PTR, (CY_GET_REG32(CY_CLK_SELECT_PTR) & ~CY_CLK_CONFIG_WDT_BITS_MASK)
                                    | CY_CLK_CONFIG_WDT_BITS_MASK);
}


/*******************************************************************************
* Function Name: CySysWdtUnlock
********************************************************************************
*
* Summary:
*  Unlocks the Watchdog Timer configuration register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysWdtUnlock(void)
{
    CY_SET_REG32(CY_CLK_SELECT_PTR, (CY_GET_REG32(CY_CLK_SELECT_PTR) & ~CY_CLK_CONFIG_WDT_BITS_MASK)
                                    | CY_CLK_CONFIG_WDT_BIT0);

    CY_SET_REG32(CY_CLK_SELECT_PTR, (CY_GET_REG32(CY_CLK_SELECT_PTR) & ~CY_CLK_CONFIG_WDT_BITS_MASK)
                                    | CY_CLK_CONFIG_WDT_BIT1);
}


/*******************************************************************************
* Function Name: CySysGetWdtEnabledMode
********************************************************************************
*
* Summary:
*  Reads the mode of one of the three WDT counters.
*  Note: A private function to cy_boot.
*
* Parameters:
*  counterNum: Valid range [0-2].  Number of the WDT counter.
*
* Return:
*  uint8
*
*******************************************************************************/
uint8 CySysGetWdtEnabledMode(uint8 counterNum)
{
    CYASSERT(counterNum < CY_WDT_COUNTERS_MAX);

    return ((CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR) >> ((8 * counterNum) +1)) & 0x01u);
}


/*******************************************************************************
* Function Name: CySysWdtWriteMode
********************************************************************************
*
* Summary:
*   Writes the mode of one of the three WDT counters.
*
* Parameters:
*   counterNum: Valid range [0-2].  Number of the WDT counter.
*   mode:       Mode of operation for the counter
*   Value    Define                   Mode
*   0     CY_SYS_WDT_MODE_NONE       Free running
*   1     CY_SYS_WDT_MODE_INT        Interrupt generated on match for counter 0
*                                    and 1, and on bit toggle for counter 2.
*   2     CY_SYS_WDT_MODE_RESET      Reset on match (valid for counter 0 and 1
*                                    only)
*   3     CY_SYS_WDT_MODE_INT_RESET  Generate an interrupt.  Generate a reset on
*                                    the 3rd unhandled interrupt.
*                                    (valid for counter 0 and 1 only)
* Return:
*   None
*
*******************************************************************************/
void CySysWdtWriteMode(uint8 counterNum, uint8 mode)
{
    CYASSERT(counterNum < CY_WDT_COUNTERS_MAX);
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);

    if(!CySysGetWdtEnabledMode(counterNum))
    {
        CY_SET_REG32(CY_CLK_WDT_CONFIG_PTR,
            (CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR) & (~(CY_CLK_SYS_WDT_MODE_MASK) << (counterNum * 8)))
            | (mode & CY_CLK_SYS_WDT_MODE_MASK) << (counterNum * 8));
    }
}


/*******************************************************************************
* Function Name: CySysWdtReadMode
********************************************************************************
*
* Summary:
*  Reads the mode of one of the three WDT counters.
*
* Parameters:
*  counterNum: Valid range [0-2].  Number of the WDT counter.
*
* Return:
*  Mode of the counter.  Same enumerated values as mode parameter used in
*  CySysWdtSetMode().
*
*******************************************************************************/
uint8 CySysWdtReadMode(uint8 counterNum)
{
    uint32 configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
    return ((configreg_value >> (counterNum * 8)) & 0x3u);
}


/*******************************************************************************
* Function Name: CySysWdtWriteClearOnMatch
********************************************************************************
*
* Summary:
*  Configures the WDT counter clear on a match setting.  If configured to clear
*  on match the counter will count from 0 to the MatchValue giving it a
*  period of (MatchValue + 1).
*
* Parameters:
*  counterNum:
*   Valid range [0-1].  Number of the WDT counter.  Match values are not
*   supported by counter 2.
*
* enable:
*   0 to disable, 1 to enable
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtWriteClearOnMatch(uint8 counterNum, uint8 enable)
{
    uint32 regValue = 0u;

    CYASSERT(counterNum < 2);
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CLK_CONFIG_WDT_BITS_MASK) == 0);

    if(0u == CySysGetWdtEnabledMode(counterNum))
    {
        regValue = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
        regValue |= enable << (counterNum * 8 + 2);
        CY_SET_REG32(CY_CLK_WDT_CONFIG_PTR, regValue);
    }
}


/*******************************************************************************
* Function Name: CySysWdtReadClearOnMatch
********************************************************************************
*
* Summary:
*  Reads the clear on match setting for the specified counter.
*
* Parameters:
*   counterNum: Valid range [0-1].  Number of the WDT counter.  Match values are
*               not supported by counter 2.
*
* Return:
*   Clear on Match status: 1 if enabled, 0 if disabled
*
*******************************************************************************/
uint8 CySysWdtReadClearOnMatch(uint8 counterNum)
{
    uint32 configreg_value;

    CYASSERT(counterNum < 2);

    configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
    return ((configreg_value >> ((counterNum * 8) + 2)) & 0x1u);
}


/*******************************************************************************
* Function Name: CySysWdtEnable
********************************************************************************
*
* Summary:
*  Enables the specified WDT counters.  All counters specified in the mask are
*  enabled.
*
*  Note:
*  Enabling or disabling a WDT requires 3 LF Clock cycles to come into effect.
*
* Parameters:
*  counterMask: Mask of all counters to enable
*      Value    Define                       Counter
*      1<<0    CY_SYS_WDT_COUNTER0_ENABLE    0
*      1<<8    CY_SYS_WDT_COUNTER1_ENABLE    1
*      1<<16    CY_SYS_WDT_COUNTER2_ENABLE    2
*
* Return:
*  None
*
*******************************************************************************/
void CySysWdtEnable(uint32 counterMask)
{
    CY_SET_REG32(CY_CLK_WDT_CONTROL_PTR, (CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR) | counterMask));
}


/*******************************************************************************
* Function Name: CySysWdtDisable
********************************************************************************
*
* Summary:
*  Disables the specified WDT counters.  All counters specified in the mask are
*  disabled.
*
*  Note:
*   Enabling or disabling a WDT requires 3 LF Clock cycles to come into effect.
*
* Parameters:
*  uint32 counterMask: Mask of all counters to disable
*       Define                       Counter
*   CY_SYS_WDT_COUNTER0_ENABLE          0
*   CY_SYS_WDT_COUNTER1_ENABLE          1
*   CY_SYS_WDT_COUNTER2_ENABLE          2
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtDisable(uint32 counterMask)
{
    CY_SET_REG32(CY_CLK_WDT_CONTROL_PTR, (CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR) & ~counterMask));
}


/*******************************************************************************
* Function Name: CySysWdtWriteCascade
********************************************************************************
*
* Summary:
*   Writes the two WDT cascade values based on the combination of mask values specified.
*
* Parameters:
*   cascadeMask: Mask value used to set or clear both of the cascade values.
*   Value    Define                    Cascade
*   0        CY_SYS_WDT_CASCADE_NONE    Neither
*   1<<3     CY_SYS_WDT_CASCADE_01      Cascade 01
*   1<<11    CY_SYS_WDT_CASCADE_12      Cascade 12
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtWriteCascade(uint32 cascadeMask)
{
    uint32 configreg_value = 0;
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);

    if (!CySysGetWdtEnabledMode(0) | !CySysGetWdtEnabledMode(1) | !CySysGetWdtEnabledMode(2))
    {
        configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
        configreg_value |= cascadeMask;
        CY_SET_REG32(CY_CLK_WDT_CONFIG_PTR, configreg_value);
    }
}


/*******************************************************************************
* Function Name: CySysWdtReadCascade
********************************************************************************
*
* Summary:
*   Reads the two WDT cascade values returning a mask of the bits set.
*
* Parameters:
*   None
*
* Return:
*   Mask of cascade values set.
*   Value    Define                   Cascade
*   1<<3     CY_SYS_WDT_CASCADE_01    Cascade 01
*   1<<11    CY_SYS_WDT_CASCADE_12    Cascade 12
*
*******************************************************************************/
uint32 CySysWdtReadCascade(void)
{
    uint32 configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
    return (configreg_value & (CY_SYS_WDT_CASCADE_01 | CY_SYS_WDT_CASCADE_12));
}


/*******************************************************************************
* Function Name: CySysWdtWriteMatch
********************************************************************************
*
* Summary:
*  Configures the WDT counter match comparison value.
*
* Parameters:
*  counterNum:
*   Valid range [0-1]. Number of the WDT counter. Match values are not
*   supported by counter 2.
*
*  match:
*   16-bit value to be used to match against the counter.
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtWriteMatch(uint8 counterNum, uint16 match)
{
    uint32 reg_value = 0;

    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);
    CYASSERT(counterNum < 2);
    CYASSERT(!CySysGetWdtEnabledMode(counterNum));

    /* Set the comparison value only if not running */
    if (!CySysGetWdtEnabledMode(counterNum))
    {
        reg_value = CY_GET_REG32(CY_CLK_WDT_MATCH_PTR) & ~(CY_LOWER_16BITS_ONLY << (counterNum * 16));
        CY_SET_REG32(CY_CLK_WDT_MATCH_PTR, (reg_value | match << (counterNum * 16)));
    }
}


/*******************************************************************************
* Function Name: CySysWdtWriteBits2
********************************************************************************
*
* Summary:
*  Configures which bit in the WDT counter 2 to monitor for a toggle.  When that
*  bit toggles an interrupt is generated if the mode for counter 2 has
*  interrupts enabled.
*
* Parameters:
*  bit:
*   Valid range [0-31].  Counter 2 bit to monitor for a toggle.
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtWriteBits2(uint8 bits)
{
    uint32 configreg_value = 0;
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);

    if (0u == CySysGetWdtEnabledMode(2u))
    {
        configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
        configreg_value &= ~(CY_CLK_WDT_CONFIG_BITS2_MASK << CY_CLK_WDT_CONFIG_BITS2_POS) ;
        configreg_value |= ((bits & CY_CLK_WDT_CONFIG_BITS2_MASK) << CY_CLK_WDT_CONFIG_BITS2_POS);
        CY_SET_REG32(CY_CLK_WDT_CONFIG_PTR, configreg_value);
    }
}


/*******************************************************************************
* Function Name: CySysWdtReadBits2
********************************************************************************
*
* Summary:
*  Reads which bit in the WDT counter 2 is monitored for a toggle.
*
* Parameters:
*  None
*
* Return:
*  Bit that is monitored (range of 0 to 31)
*
*******************************************************************************/
uint8 CySysWdtReadBits2(void)
{
    uint32 configreg_value = CY_GET_REG32(CY_CLK_WDT_CONFIG_PTR);
    return (uint8)(configreg_value >> CY_CLK_WDT_CONFIG_BITS2_POS);
}


/*******************************************************************************
* Function Name: CySysWdtReadMatch
********************************************************************************
*
* Summary:
*  Reads the WDT counter match comparison value.
*
* Parameters:
*  counterNum: Valid range [0-1].  Number of the WDT counter.  Match values
*               are not supported by counter 2.
*
* Return:
*  16-bit match value
*
*******************************************************************************/
uint16 CySysWdtReadMatch(uint8 counterNum)
{
    CYASSERT(counterNum < 2u);

    return((uint16)(CY_GET_REG32(CY_CLK_WDT_MATCH_PTR) >> (counterNum * 16u)));
}


/*******************************************************************************
* Function Name: CySysWdtReadCount
********************************************************************************
*
* Summary:
*  Reads the current WDT counter value.
*
* Parameters:
*  uint8 counterNum: Valid range [0-2].  Number of the WDT counter.
*
* Return:
*  uint32: Live counter value.  Counter 0 and 1 are 16 bit counters and counter
*  2 is a 32 bit counter.
*
*******************************************************************************/
uint32 CySysWdtReadCount(uint8 counterNum)
{
    uint32 regValue = 0u;

    switch(counterNum)
    {
        /* WDT Counter 0 */
        case 0u:
            regValue = CY_GET_REG32(CY_CLK_WDT_CTRLOW_PTR) & 0x0000FFFFu;
        break;

        /* WDT Counter 1 */
        case 1u:
            regValue = CY_GET_REG32(CY_CLK_WDT_CTRLOW_PTR) >> 16u;
        break;

        /* WDT Counter 2 */
        case 2u:
            regValue = CY_GET_REG32(CY_CLK_WDT_CTRHIGH_PTR);
        break;

        default:
            CYASSERT(0u != 0u);
        break;
    }

    return(regValue);
}


/*******************************************************************************
* Function Name: CySysWdtReadIntr
********************************************************************************
*
* Summary:
*   Reads a mask containing all the WDT interrupts that are currently set.
*
* Parameters:
*   None
*
* Return:
*   Mask of interrupts set.
*   Value    Define                    Counter
*   1<<2     CY_SYS_WDT_COUNTER0_INT    0
*   1<<10    CY_SYS_WDT_COUNTER1_INT    1
*   1<<18    CY_SYS_WDT_COUNTER2_INT    2
*
*******************************************************************************/
uint32 CySysWdtReadIntr(void)
{
    uint32 configreg_value = CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR);
    return (configreg_value & (CY_SYS_WDT_COUNTER0_INT | CY_SYS_WDT_COUNTER1_INT | CY_SYS_WDT_COUNTER2_INT));
}


/*******************************************************************************
* Function Name: CySysWdtClearIntr
********************************************************************************
*
* Summary:
*   Clears all WDT counter interrupts set in the mask.
*
* Parameters:
*   counterMask: Mask of all counters to enable
*   Value    Define                    Counter
*   1<<2     CY_SYS_WDT_COUNTER0_INT    0
*   1<<10    CY_SYS_WDT_COUNTER1_INT    1
*   1<<18    CY_SYS_WDT_COUNTER2_INT    2
*
* Return:
*   None
*
*******************************************************************************/
void CySysWdtClearIntr(uint32 counterMask)
{
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);

    /* Set the new WDT control register value */
    CY_SET_REG32(CY_CLK_WDT_CONTROL_PTR, CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR) |
    (counterMask & ((CY_SYS_WDT_COUNTER0_INT | CY_SYS_WDT_COUNTER1_INT | CY_SYS_WDT_COUNTER2_INT))));
}


/*******************************************************************************
* Function Name: CySysWdtResetCount
********************************************************************************
*
* Summary:
*  Resets all WDT counters set in the mask.
*
* Parameters:
*  counterMask: Mask of all counters to reset.
*   Value    Define                       Counter
*  1<<3     CY_SYS_WDT_COUNTER0_RESET    0
*  1<<11    CY_SYS_WDT_COUNTER1_RESET    1
*  1<<19    CY_SYS_WDT_COUNTER2_RESET    2
*
* Return:
*  None
*
*******************************************************************************/
void CySysWdtResetCount(uint32 counterMask)
{
    CYASSERT((CY_GET_REG32(CY_CLK_SELECT_PTR) & CY_CLK_CONFIG_WDT_BITS_MASK) == 0);

    /* Set the new WDT reset value */
    CY_SET_REG32(CY_CLK_WDT_CONTROL_PTR, CY_GET_REG32(CY_CLK_WDT_CONTROL_PTR) |
     (counterMask & ((CY_SYS_WDT_COUNTER0_RESET | CY_SYS_WDT_COUNTER1_RESET | CY_SYS_WDT_COUNTER2_RESET))));
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
uint32 CyDisableInts(void)
{
    uint32 intState;

    /* Get the curreent interrutp state. */
    intState = CY_GET_REG32(CY_INT_CLEAR_PTR);

    /* Disable all of the interrupts. */
    CY_SET_REG32(CY_INT_CLEAR_PTR, CY_INT_CLEAR_DISABLE_ALL);

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
*   mask, 32 bit mask of interrupts to enable.
*
* Return:
*  None
*
*******************************************************************************/
void CyEnableInts(uint32 mask)
{
    /* Set interrupts as enabled. */
    CY_SET_REG32(CY_INT_ENABLE_PTR, mask);
}


/*******************************************************************************
* Function Name: CyIntSetSysVector
********************************************************************************
*
* Summary:
*  Sets the interrupt vector of the specified system interrupt number. These
*  interrupts are for SysTick, PendSV and others.
*
* Parameters:
*  number: Interrupt number, valid range [0-15].
*  address: Pointer to an interrupt service routine.
*
* Return:
*  The old ISR vector at this location.
*
*******************************************************************************/
cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address)
{
    cyisraddress oldIsr;
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    /* Save old Interrupt service routine. */
    oldIsr = ramVectorTable[number];

    /* Set new Interrupt service routine. */
    ramVectorTable[number] = address;

    return(oldIsr);
}


/*******************************************************************************
* Function Name: CyIntGetSysVector
********************************************************************************
*
* Summary:
*   Gets the interrupt vector of the specified system interrupt number. These
*   interrupts are for SysTick, PendSV and others.
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
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    return(ramVectorTable[number]);
}


/*******************************************************************************
* Function Name: CyIntSetVector
********************************************************************************
*
* Summary:
*  Sets the interrupt vector of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number
*  address: Pointer to an interrupt service routine
*
* Return:
*   Previous interrupt vector value.
*
*******************************************************************************/
cyisraddress CyIntSetVector(uint8 number, cyisraddress address)
{
    cyisraddress oldIsr;
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    /* Save old Interrupt service routine. */
    oldIsr = ramVectorTable[CY_INT_IRQ_BASE + number];

    /* Set new Interrupt service routine. */
    ramVectorTable[CY_INT_IRQ_BASE + number] = address;

    return(oldIsr);
}


/*******************************************************************************
* Function Name: CyIntGetVector
********************************************************************************
*
* Summary:
*  Gets the interrupt vector of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number
*
* Return:
*  Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress CyIntGetVector(uint8 number)
{
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    return (ramVectorTable[CY_INT_IRQ_BASE + number]);
}

/*******************************************************************************
* Function Name: CyIntSetPriority
********************************************************************************
*
* Summary:
*  Sets the Priority of the Interrupt.
*
* Parameters:
*  priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*  number: The number of the interrupt, 0 - 15.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntSetPriority(uint8 number, uint8 priority)
{
    uint8 interruptState;
    uint32 shift;
    uint32 value;

    CYASSERT(priority <= CY_MIN_PRIORITY);
    CYASSERT(number < CY_NUM_INTERRUPTS);

    shift = CY_INT_PRIORITY_SHIFT(number);

    interruptState = CyEnterCriticalSection();

    value = CY_GET_REG32(CY_INT_PRIORITY_PTR(number));
    value &= ~(CY_INT_PRIORITY_MASK << shift);
    value |= (priority << shift);
    CY_SET_REG32(CY_INT_PRIORITY_PTR(number), value);
    
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CyIntGetPriority
********************************************************************************
*
* Summary:
*  Gets the Priority of the Interrupt.
*
* Parameters:
*  number: The number of the interrupt, 0 - 15.
*
* Return:
*  Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 CyIntGetPriority(uint8 number)
{
    uint8 priority;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    priority = CY_GET_REG32(CY_INT_PRIORITY_PTR(number)) >> CY_INT_PRIORITY_SHIFT(number);

    return (priority & CY_INT_PRIORITY_MASK);
}


/*******************************************************************************
* Function Name: CyIntEnable
********************************************************************************
*
* Summary:
*  Enables the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number
*
* Return:
*  None
*
*******************************************************************************/
void CyIntEnable(uint8 number)
{
    /* Enable the interrupt. */
    CY_SET_REG32(CY_INT_ENABLE_PTR, 1 << (CY_INT_ENABLE_RANGE_MASK & number));
}


/*******************************************************************************
* Function Name: CyIntGetState
********************************************************************************
*
* Summary:
*  Gets the enable state of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number.
*
* Return:
*  Enable status: 1 if enabled, 0 if disabled
*
*******************************************************************************/
uint8 CyIntGetState(uint8 number)
{
    /* Get the state of the interrupt. */
    return (CY_GET_REG32(CY_INT_ENABLE_PTR) & (1 << (CY_INT_ENABLE_RANGE_MASK & number))) ? 1:0;
}


/*******************************************************************************
* Function Name: CyIntDisable
********************************************************************************
*
* Summary:
*   Disables the specified interrupt number.
*
* Parameters:
*   number: Valid range [0-15].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntDisable(uint8 number)
{
    /* Disable the interrupt. */
    CY_SET_REG32(CY_INT_CLEAR_PTR, 1 << (0x0F & number));
}

/*******************************************************************************
* Function Name: CyIntSetPending
********************************************************************************
*
* Summary:
*  Forces the specified interrupt number to be pending.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntSetPending(uint8 number)
{
    /* Pending the interrupt. */
    CY_SET_REG32(CY_INT_SET_PEND_PTR, 1 << (0x0F & number));
}


/*******************************************************************************
* Function Name: CyIntClearPending
********************************************************************************
*
* Summary:
*  Clears any pending interrupt for the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-15].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntClearPending(uint8 number)
{
    /* Clear the pending interrupt. */
    CY_SET_REG32(CY_INT_CLR_PEND_PTR, 1 << (0x0F & number));
}


/*******************************************************************************
* Function Name: CyHalt
********************************************************************************
*
* Summary:
*  Halts the CPU
*
* Parameters:
*  reason: Value to be used during debugging.
*
* Return:
*  None
*
*******************************************************************************/
void CyHalt(uint8 reason)
{
    reason = reason;

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
void CySoftwareReset(void)
{
    /* Perform a reset by setting CM0_AIRCR register's reset bit */
    CY_SET_REG32(CY_CM0_AIRCR_PTR, CY_SOFTWARE_RESET);
}


uint32 cydelay_freq_hz = CYDEV_BCLK__SYSCLK__HZ;
uint32 cydelay_freq_khz = (CYDEV_BCLK__SYSCLK__HZ + 999u) / 1000u;
uint8 cydelay_freq_mhz = (uint8)((CYDEV_BCLK__SYSCLK__HZ + 999999u) / 1000000u);
uint32 cydelay_32k_ms = 32768 * ((CYDEV_BCLK__SYSCLK__HZ + 999u) / 1000u);


/*******************************************************************************
* Function Name: CyDelay
********************************************************************************
*
* Summary:
*  Blocks for milliseconds.
*
* Parameters:
*  milliseconds: number of milliseconds to delay.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelay(uint32 milliseconds)
{
    while (milliseconds > 32768)
    {
        /* This loop prevents overflow.
         * At 100MHz, milliseconds * delay_freq_khz overflows at about 42 seconds
         */
        CyDelayCycles(cydelay_32k_ms);
        milliseconds -= 32768;
    }

    CyDelayCycles(milliseconds * cydelay_freq_khz);
}


/*******************************************************************************
* Function Name: CyDelayUs
********************************************************************************
* Summary:
*  Blocks for microseconds.
*
* Parameters:
*  microseconds: number of microseconds to delay.
*
* Return:
*  None
*
*******************************************************************************/
#if defined(__ARMCC_VERSION)
    void CyDelayUs(uint16 microseconds)
    {
        CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
    }
#elif defined(__GNUC__)
    void CyDelayUs(uint16 microseconds)
    {
        CyDelayCycles((uint32)microseconds * cydelay_freq_mhz);
    }
#endif  /* defined(__ARMCC_VERSION) */


/*******************************************************************************
* Function Name: CyDelayFreq
********************************************************************************
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
void CyDelayFreq(uint32 freq)
{
    if (freq != 0u)
    {
        cydelay_freq_hz = freq;
    }
    else
    {
        cydelay_freq_hz = CYDEV_BCLK__SYSCLK__HZ;
    }

    cydelay_freq_mhz = (uint8)((cydelay_freq_hz + 999999u) / 1000000u);
    cydelay_freq_khz = (cydelay_freq_hz + 999u) / 1000u;
    cydelay_32k_ms = 32768 * cydelay_freq_khz;
}


/* [] END OF FILE */
