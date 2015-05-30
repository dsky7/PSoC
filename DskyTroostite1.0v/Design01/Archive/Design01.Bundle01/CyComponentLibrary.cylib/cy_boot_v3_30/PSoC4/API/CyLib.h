/*******************************************************************************
* File Name: CyLib.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
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

#if !defined(CY_BOOT_CYLIB_H)
#define CY_BOOT_CYLIB_H

#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice_trm.h"
#include "cyPm.h"


/***************************************
*    Function Prototypes
***************************************/

/* Clocks API */
void CySysClkImoStart(void);
void CySysClkImoStop(void);
void CySysClkIloStart(void);
void CySysClkIloStop(void);
void CySysClkWriteHfclkDirect(uint8 clkSelect);
void CySysClkWriteSysclkDiv(uint8 divider);
void CySysClkWriteImoFreq(uint8 freq);

/* WDT API */
void   CySysWdtLock(void);
void   CySysWdtUnlock(void);
void   CySysWdtWriteMode(uint8 counterNum, uint8 mode);
uint8  CySysWdtReadMode(uint8 counterNum);
void   CySysWdtWriteClearOnMatch(uint8 counterNum, uint8 enable);
uint8  CySysWdtReadClearOnMatch(uint8 counterNum);
void   CySysWdtEnable(uint32 counterMask);
void   CySysWdtDisable(uint32 counterMask);
void   CySysWdtWriteCascade(uint32 cascadeMask);
uint32 CySysWdtReadCascade(void);
void   CySysWdtWriteMatch(uint8 counterNum, uint16 match);
void   CySysWdtWriteBits2(uint8 bits);
uint8  CySysWdtReadBits2(void);
uint16 CySysWdtReadMatch(uint8 counterNum);
uint32 CySysWdtReadCount(uint8 counterNum);
uint32 CySysWdtReadIntr(void);
void   CySysWdtClearIntr(uint32 counterMask);
void   CySysWdtResetCount(uint32 counterMask);


/* Interrupt Function Prototypes */
cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address);
cyisraddress CyIntGetSysVector(uint8 number);

cyisraddress CyIntSetVector(uint8 number, cyisraddress address);
cyisraddress CyIntGetVector(uint8 number);

void   CyIntSetPriority(uint8 number, uint8 priority);
uint8  CyIntGetPriority(uint8 number);

void   CyIntEnable(uint8 number);
uint8  CyIntGetState(uint8 number);
void   CyIntDisable(uint8 number);

void   CyIntSetPending(uint8 number);
void   CyIntClearPending(uint8 number);

uint32 CyDisableInts(void);
void   CyEnableInts(uint32 mask);


/* System Function Prototypes */
void  CyDelay(uint32 milliseconds);
void  CyDelayUs(uint16 microseconds);
void  CyDelayFreq(uint32 freq);
void  CyDelayCycles(uint32 cycles);

void  CySoftwareReset(void);
uint8 CyEnterCriticalSection(void);
void  CyExitCriticalSection(uint8 savedIntrStatus);
void  CyHalt(uint8 reason);


/***************************************
* API Constants
***************************************/


/*******************************************************************************
* Clock API Constants
*******************************************************************************/

/* CySysClkWriteSysclkDiv() - prescaler divide for SYSCLK */
#define CY_SYS_CLK_SYSCLK_DIV1          (0u)
#define CY_SYS_CLK_SYSCLK_DIV2          (1u)
#define CY_SYS_CLK_SYSCLK_DIV4          (2u)
#define CY_SYS_CLK_SYSCLK_DIV8          (3u)
#define CY_SYS_CLK_SYSCLK_DIV16         (4u)
#define CY_SYS_CLK_SYSCLK_DIV32         (5u)
#define CY_SYS_CLK_SYSCLK_DIV64         (6u)
#define CY_SYS_CLK_SYSCLK_DIV128        (7u)

#define CY_SYS_CLK_HFCLK_IMO            (0u)    /* IMO */
#define CY_SYS_CLK_HFCLK_EXTCLK         (1u)    /* External clock pin */

#define CY_CLK_IMO_CONFIG_ENABLE        ((uint32)(0x01u << 31u))
#define CY_CLK_IMO_FREQ_BITS_MASK       (0x3Fu)
#define CY_CLK_IMO_FREQ_CLEAR           (CY_CLK_IMO_FREQ_BITS_MASK << 8u )
#define CY_CLK_ILO_CONFIG_ENABLE        (0x01u << 31u)
#define CY_CLK_HFCLK_SELECT_BIT_POS     (16u)
#define CY_CLK_HFCLK_SELECT_SET         (0x03u << 16u)
#define CY_CLK_HFCLK_SELECT_MASK        (0x01u)
#define CY_CLK_HFCLK_SELECT_EXTCLK      (0x01u)
#define CY_CLK_SYSCLK_SELECT_MASK       (0x07u)
#define CY_CLK_HFCLK_FROM_SYSCLK        (19u)

/* SFLASH0 block has been renamed to SFLASH */
#if !defined(CYREG_SFLASH_IMO_TRIM21)
    #define CYREG_SFLASH_IMO_TRIM21     (CYREG_SFLASH0_IMO_TRIM21)
#endif  /* !defined(CYREG_SFLASH_IMO_TRIM21) */


/*******************************************************************************
* WDT API Constants
*******************************************************************************/
#define CY_SYS_WDT_MODE_NONE            (0) /* Free running */
#define CY_SYS_WDT_MODE_INT             (1) /* Interrupt generated on match for counter 0 and 1,
                                               and on bit toggle for counter 2*/
#define CY_SYS_WDT_MODE_RESET           (2) /* Reset on match (valid for counter 0 and 1 only)*/
#define CY_SYS_WDT_MODE_INT_RESET       (3) /* Generate an interrupt.  Generate a reset on
                                               the 3rd unhandled interrupt. (valid for counter 0 and 1 only) */

#define CY_SYS_WDT_COUNTER0_ENABLE      (0x01u)         /* Counter 0 */
#define CY_SYS_WDT_COUNTER1_ENABLE      (0x01u << 8)    /* Counter 1 */
#define CY_SYS_WDT_COUNTER2_ENABLE      (0x01u << 16)   /* Counter 2 */

#define CY_SYS_WDT_CASCADE_NONE         (0x00u)         /* Neither */
#define CY_SYS_WDT_CASCADE_01           (0x01u << 3)    /* Cascade 01 */
#define CY_SYS_WDT_CASCADE_12           (0x01u << 11)   /* Cascade 12 */

#define CY_SYS_WDT_COUNTER0_INT         (0x01u << 2)    /* Interrupt of WDT 0 */
#define CY_SYS_WDT_COUNTER1_INT         (0x01u << 10)   /* Interrupt of WDT 1 */
#define CY_SYS_WDT_COUNTER2_INT         (0x01u << 18)   /* Interrupt of WDT 2 */

#define CY_SYS_WDT_COUNTER0_RESET       (0x01u << 3)    /* Counter of WDT 0 */
#define CY_SYS_WDT_COUNTER1_RESET       (0x01u << 11)   /* Counter of WDT 1 */
#define CY_SYS_WDT_COUNTER2_RESET       (0x01u << 19)   /* Counter of WDT 2 */

#define CY_CLK_SYS_WDT_MODE_MASK 0x3u                      /*1:0 are Mode mask bits */

#define CY_CLK_CONFIG_WDT_BITS_MASK    (0x03u << 14)    /* "Prohibits writing to WDT_* registers and
                                                           CLK_ILO/WCO_CONFIG registerst when not equal 0.
                                                           Requires at least two different writes to unlock.
                                                           Writing to this field has the following effect:
                                                             0: No effect
                                                             1: Clears bit 0
                                                             2: Clears bit 1
                                                             3: Sets both bits 0 and 1" */
#define CY_CLK_CONFIG_WDT_BIT0          (0x01u << 14)
#define CY_CLK_CONFIG_WDT_BIT1          (0x01u << 15)

#define CY_CLK_WDT_CONFIG_BITS2_MASK    (0x1Fu)         /* Bits[5:0] to configure */
#define CY_CLK_WDT_CONFIG_BITS2_POS     (24u)           /* Bits[24:28] are Counter2 BITS */
#define CY_LOWER_16BITS_ONLY            (0xFFFFu)       /* Lower 16 bits allowed - Bits [15:0]*/
#define CY_WDT_COUNTERS_MAX             (3u)            /* There are 3 WDT counters */


/*******************************************************************************
* System API Constants
*******************************************************************************/
#define CY_SOFTWARE_RESET               (0x05FA0004u)

#if defined(__ARMCC_VERSION)
    #define CyGlobalIntEnable           {__enable_irq();}
    #define CyGlobalIntDisable          {__disable_irq();}
#elif defined(__GNUC__)
    #define CyGlobalIntEnable           {__asm("CPSIE   i");}
    #define CyGlobalIntDisable          {__asm("CPSID   i");}
#endif  /* (__ARMCC_VERSION) */


/*******************************************************************************
* Macro Name: CyAssert
********************************************************************************
* Summary:
*  Macro that evaluates the expression and if it is false (evaluates to 0)
*  then the processor is halted.
*
*  This macro is evaluated unless NDEBUG is defined.
*  If NDEBUG is defined, then no code is generated for this macro.
*  NDEBUG is defined by default for a Release build setting and not defined for
*  a Debug build setting.
*
* Parameters:
*  expr: Logical expression.  Asserts if false.
*
* Return:
*  None
*
*******************************************************************************/
#if !defined(NDEBUG)
    #define CYASSERT(x)                 { \
                                            if(!(x)) \
                                                CyHalt((uint32) (x)); \
                                        }
#else
    #define CYASSERT(x)
#endif /* !defined(NDEBUG) */


/*******************************************************************************
* Interrupt API Constants
*******************************************************************************/
#define CY_NUM_INTERRUPTS               (16u)
#define CY_MIN_PRIORITY                 (3u)

#define CY_INT_IRQ_BASE                 (16)
#define CY_INT_CLEAR_DISABLE_ALL        (0xFFFFFFFFu)
#define CY_INT_ENABLE_RANGE_MASK        (0x0Fu)

/* Register n contains priorities for interrupts N=4n .. 4n+3 */
#define CY_INT_PRIORITY_SHIFT(number)   (6 + (8 * ((number) % 4)))

/* Mask to get valid range of system priority 0-3 */
#define CY_INT_PRIORITY_MASK            (0x3u)


/***************************************
* Registers
***************************************/


/*******************************************************************************
* Clocks API Registers
*******************************************************************************/

#define CY_CLK_IMO_CONFIG_REG           (*(reg32 *) CYREG_CLK_IMO_CONFIG)
#define CY_CLK_IMO_CONFIG_PTR           ( (reg32 *) CYREG_CLK_IMO_CONFIG)

#define CY_CLK_ILO_CONFIG_REG           (*(reg32 *) CYREG_CLK_ILO_CONFIG)
#define CY_CLK_ILO_CONFIG_PTR           ( (reg32 *) CYREG_CLK_ILO_CONFIG)

#define CY_CLK_SELECT_REG               (*(reg32 *) CYREG_CLK_SELECT)
#define CY_CLK_SELECT_PTR               ( (reg32 *) CYREG_CLK_SELECT)

#define CY_CLK_ILO_TRIM_REG             (*(reg32 *) CYREG_CLK_ILO_TRIM)
#define CY_CLK_ILO_TRIM_PTR             ( (reg32 *) CYREG_CLK_ILO_TRIM)

#define CY_CLK_IMO_TRIM1_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM1)
#define CY_CLK_IMO_TRIM1_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM1)

#define CY_CLK_IMO_TRIM2_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM2)
#define CY_CLK_IMO_TRIM2_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM2)

#define CY_CLK_IMO_TRIM3_REG            (*(reg32 *) CYREG_CLK_IMO_TRIM3)
#define CY_CLK_IMO_TRIM3_PTR            ( (reg32 *) CYREG_CLK_IMO_TRIM3)


/*******************************************************************************
* WDT API Registers
*******************************************************************************/
#if(CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4G)

    #define CY_CLK_WDT_CTRLOW_REG           (*(reg8 *) CYREG_CLK_WDT_CTRLOW)
    #define CY_CLK_WDT_CTRLOW_PTR           ( (reg8 *) CYREG_CLK_WDT_CTRLOW)

    #define CY_CLK_WDT_CTRHIGH_REG          (*(reg8 *) CYREG_CLK_WDT_CTRHIGH)
    #define CY_CLK_WDT_CTRHIGH_PTR          ( (reg8 *) CYREG_CLK_WDT_CTRHIGH)

    #define CY_CLK_WDT_MATCH_REG            (*(reg8 *) CYREG_CLK_WDT_MATCH)
    #define CY_CLK_WDT_MATCH_PTR            ( (reg8 *) CYREG_CLK_WDT_MATCH)

    #define CY_CLK_WDT_CONFIG_REG           (*(reg8 *) CYREG_CLK_WDT_CONFIG)
    #define CY_CLK_WDT_CONFIG_PTR           ( (reg8 *) CYREG_CLK_WDT_CONFIG)

    #define CY_CLK_WDT_CONTROL_REG          (*(reg8 *) CYREG_CLK_WDT_CONTROL)
    #define CY_CLK_WDT_CONTROL_PTR          ( (reg8 *) CYREG_CLK_WDT_CONTROL)

#else

    #define CY_CLK_WDT_CTRLOW_REG           (*(reg32 *) CYREG_WDT_CTRLOW)
    #define CY_CLK_WDT_CTRLOW_PTR           ( (reg32 *) CYREG_WDT_CTRLOW)

    #define CY_CLK_WDT_CTRHIGH_REG          (*(reg32 *) CYREG_WDT_CTRHIGH)
    #define CY_CLK_WDT_CTRHIGH_PTR          ( (reg32 *) CYREG_WDT_CTRHIGH)

    #define CY_CLK_WDT_MATCH_REG            (*(reg32 *) CYREG_WDT_MATCH)
    #define CY_CLK_WDT_MATCH_PTR            ( (reg32 *) CYREG_WDT_MATCH)

    #define CY_CLK_WDT_CONFIG_REG           (*(reg32 *) CYREG_WDT_CONFIG)
    #define CY_CLK_WDT_CONFIG_PTR           ( (reg32 *) CYREG_WDT_CONFIG)

    #define CY_CLK_WDT_CONTROL_REG          (*(reg32 *) CYREG_WDT_CONTROL)
    #define CY_CLK_WDT_CONTROL_PTR          ( (reg32 *) CYREG_WDT_CONTROL)

#endif /* (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4G) */


/*******************************************************************************
* System API Registers
*******************************************************************************/
#define CY_CM0_AIRCR_REG                (*(reg32 *) CYREG_CM0_AIRCR)
#define CY_CM0_AIRCR_PTR                ( (reg32 *) CYREG_CM0_AIRCR)


/*******************************************************************************
* Interrupt API Registers
*******************************************************************************/
#define CY_INT_VECT_TABLE               ( (cyisraddress **) CYDEV_SRAM_BASE)

#define CY_INT_PRIORITY_REG(number)     ( ((reg32 *) CYREG_CM0_IPR0)[number/4])
#define CY_INT_PRIORITY_PTR(number)     (&((reg32 *) CYREG_CM0_IPR0)[number/4])

#define CY_INT_ENABLE_REG               (*(reg32 *) CYREG_CM0_ISER)
#define CY_INT_ENABLE_PTR               ( (reg32 *) CYREG_CM0_ISER)

#define CY_INT_CLEAR_REG                (*(reg32 *) CYREG_CM0_ICER)
#define CY_INT_CLEAR_PTR                ( (reg32 *) CYREG_CM0_ICER)

#define CY_INT_SET_PEND_REG             (*(reg32 *) CYREG_CM0_ISPR)
#define CY_INT_SET_PEND_PTR             ( (reg32 *) CYREG_CM0_ISPR)

#define CY_INT_CLR_PEND_REG             (*(reg32 *) CYREG_CM0_ICPR)
#define CY_INT_CLR_PEND_PTR             ( (reg32 *) CYREG_CM0_ICPR)


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from cy_boot 3.30
*******************************************************************************/
#define CLK_IMO_CONFIG_ENABLE           CY_CLK_IMO_CONFIG_ENABLE
#define CLK_IMO_FREQ_BITS_MASK          CY_CLK_IMO_FREQ_BITS_MASK
#define CLK_IMO_FREQ_CLEAR              CY_CLK_IMO_FREQ_CLEAR
#define CLK_ILO_CONFIG_ENABLE           CY_CLK_ILO_CONFIG_ENABLE
#define CLK_HFCLK_SELECT_BIT_POS        CY_CLK_HFCLK_SELECT_BIT_POS
#define CLK_HFCLK_SELECT_SET            CY_CLK_HFCLK_SELECT_SET
#define CLK_HFLK_SELECT_MASK            CY_CLK_HFCLK_SELECT_MASK
#define CLK_HFCLK_SELECT_EXTCLK         CY_CLK_HFCLK_SELECT_EXTCLK
#define CLK_SYSCLK_SELECT_MASK          CY_CLK_SYSCLK_SELECT_MASK
#define CLK_HFLK_FROM_SYSCLK            CY_CLK_HFCLK_FROM_SYSCLK

#define CLK_SYS_WDT_MODE_MASK           CY_CLK_SYS_WDT_MODE_MASK
#define CLK_CONFIG_WDT_BITS_MASK        CY_CLK_CONFIG_WDT_BITS_MASK
#define CLK_CONFIG_WDT_BIT0             CY_CLK_CONFIG_WDT_BIT0
#define CLK_CONFIG_WDT_BIT1             CY_CLK_CONFIG_WDT_BIT1

#define NUM_INTERRUPTS                  CY_NUM_INTERRUPTS
#define MIN_PRIORITY                    CY_MIN_PRIORITY
#define CYINT_IRQ_BASE                  CY_INT_IRQ_BASE
#define CYINT_CLEAR_DISABLE_ALL         CY_INT_CLEAR_DISABLE_ALL
#define CYINT_ENABLE_RANGE_MASK         CY_INT_ENABLE_RANGE_MASK
#define CYINT_PRIORITY_SHIFT(number)    CY_INT_PRIORITY_SHIFT(number)
#define CYINT_PRIORITY_MASK             CY_INT_PRIORITY_MASK

#define RESET_CR2                       ((reg8 *) CYREG_RESET_CR2)

#define CYINT_VECT_TABLE                CY_INT_VECT_TABLE
#define CYINT_PRIORITY                  CY_INT_PRIORITY_PTR(0)
#define CYINT_ENABLE                    CY_INT_ENABLE_PTR
#define CYINT_CLEAR                     CY_INT_CLEAR_PTR
#define CYINT_SET_PEND                  CY_INT_SET_PEND_PTR
#define CYINT_CLR_PEND                  CY_INT_CLR_PEND_PTR


#endif  /* CY_BOOT_CYLIB_H */


/* [] END OF FILE */
