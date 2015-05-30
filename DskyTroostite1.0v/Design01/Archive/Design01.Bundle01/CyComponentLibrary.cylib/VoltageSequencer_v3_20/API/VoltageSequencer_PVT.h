/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the Voltage
*  Sequencer component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H)
#define CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
*       Macros to accelerate processing of 32-bit variables
*******************************************************************************/

#if(`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS <= 8u)
    #define `$INSTANCE_NAME`_CLEAR_BIT(var, grp, msk) ((var) &= (uint8)~(msk))
    #define `$INSTANCE_NAME`_SET_BIT(  var, grp, msk) ((var) |=         (msk))
    #define `$INSTANCE_NAME`_TEST_BIT( var, grp, msk) ((var) &          (msk))
    #define `$INSTANCE_NAME`_GET_GROUP(var, grp)       (var)
#else
    #define `$INSTANCE_NAME`_CLEAR_BIT(var, grp, msk) ((((uint8 *)&(var))[grp]) &= (uint8)~(msk))
    #define `$INSTANCE_NAME`_SET_BIT(  var, grp, msk) ((((uint8 *)&(var))[grp]) |=         (msk))
    #define `$INSTANCE_NAME`_TEST_BIT( var, grp, msk) ((((uint8 *)&(var))[grp]) &          (msk))
    #define `$INSTANCE_NAME`_GET_GROUP(var, grp)       (((uint8 *)&(var))[grp])
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS <= 8u */


/*******************************************************************************
* Faster version of CyIntDisable() and CyIntEnable()
* Selectively disable/enable an individual IRQ.
* When disabled, IRQ assertion is latched and pending,
* but the ISR is prevented from executing until reenabled.
*******************************************************************************/

#ifdef __C51__
    #define `$INSTANCE_NAME`_IntDisable(irqNum) \
        do { \
            ((reg8*)CY_INT_CLEAR_PTR)[((CY_INT_NUMBER_MASK & (irqNum)) >> 3u)] = \
                   (uint8)1u << (0x07u & (irqNum)); \
        } while (0u)
#else
    #define `$INSTANCE_NAME`_IntDisable(irqNum) \
        do { \
            CY_INT_CLEAR_REG = (uint32)1u << (CY_INT_NUMBER_MASK & (irqNum)); \
      } while (0u)
#endif /* __C51__ */

#ifdef __C51__
    #if(`$INSTANCE_NAME`_DEBUG_MODE != 0u)
        #define `$INSTANCE_NAME`_IntEnable(irqNum) \
            do { \
                if(`$INSTANCE_NAME`_operatingMode != `$INSTANCE_NAME`_SEQUENCER_PAUSE) \
                { \
                    ((reg8*)CY_INT_ENABLE_PTR)[((CY_INT_NUMBER_MASK & (irqNum)) >> 3u)] = \
                        (uint8)1u << (0x07u & (irqNum)); \
                } \
        } while (0u)
    #else
        #define `$INSTANCE_NAME`_IntEnable(irqNum) \
            do { \
                    ((reg8*)CY_INT_ENABLE_PTR)[((CY_INT_NUMBER_MASK & (irqNum)) >> 3u)] = \
                        (uint8)1u << (0x07u & (irqNum)); \
        } while (0u)
    #endif /* `$INSTANCE_NAME`_DEBUG_MODE != 0u */
#else
    #if(`$INSTANCE_NAME`_DEBUG_MODE != 0u)
        #define `$INSTANCE_NAME`_IntEnable(irqNum) \
            do { \
                if(`$INSTANCE_NAME`_operatingMode != `$INSTANCE_NAME`_SEQUENCER_PAUSE) \
                { \
                    CY_INT_ENABLE_REG = (uint32)1u << (CY_INT_NUMBER_MASK & (irqNum)); \
                } \
            } while (0u)
    #else
        #define `$INSTANCE_NAME`_IntEnable(irqNum) \
            do { \
                CY_INT_ENABLE_REG = (uint32)1u << (CY_INT_NUMBER_MASK & (irqNum)); \
            } while (0u)
        #endif /* `$INSTANCE_NAME`_DEBUG_MODE != 0u */
#endif /* __C51__ */


/*******************************************************************************
*       Power Up Configuration Variables
*******************************************************************************/

extern `$SeqBitsType`   `$INSTANCE_NAME`_pgoodOnPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16   `$INSTANCE_NAME`_tonDelayList   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16   `$INSTANCE_NAME`_tonMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16   `$INSTANCE_NAME`_sysStableTime;

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)
    extern uint16 `$INSTANCE_NAME`_pgoodOnThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */


/*******************************************************************************
*       Control Input Configuration Variables
*******************************************************************************/

#if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
    extern uint8          `$INSTANCE_NAME`_ctlPrereqList       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern uint8          `$INSTANCE_NAME`_ctlFaultReseqCfg    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern `$SeqBitsType`         `$INSTANCE_NAME`_ctlGroupShutdownMask[`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS];
    extern uint8          `$INSTANCE_NAME`_ctlShutdownMaskList [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern volatile uint8 `$INSTANCE_NAME`_ctlStatus;
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */


/*******************************************************************************
*      Power Down Configaration Variables
*******************************************************************************/

extern `$SeqBitsType`   `$INSTANCE_NAME`_pgoodOffPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

extern uint16   `$INSTANCE_NAME`_toffDelayList   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint16   `$INSTANCE_NAME`_toffMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)
    extern uint16 `$INSTANCE_NAME`_pgoodOffThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */


/*******************************************************************************
*       Fault Response and Resequence Configuration Variables
*******************************************************************************/

extern uint16 `$INSTANCE_NAME`_globalReseqDelay;
extern `$SeqBitsType` `$INSTANCE_NAME`_pgoodShutdownMaskList [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern `$SeqBitsType` `$INSTANCE_NAME`_pgoodGroupShutdownMask[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_tonMaxFaultReseqCfg   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_pgoodFaultReseqCfg    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_ovFaultReseqCfg       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_uvFaultReseqCfg       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_ocFaultReseqCfg       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern uint8  `$INSTANCE_NAME`_faultReseqSrcList     [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];


/*******************************************************************************
*       Sequencer Command and Status Registers
*******************************************************************************/

extern volatile `$SeqBitsType`  `$INSTANCE_NAME`_forceOnCmdReg;
extern volatile `$SeqBitsType`  `$INSTANCE_NAME`_forceOffCmdReg;
extern volatile `$SeqBitsType`  `$INSTANCE_NAME`_forceOffModeReg;
extern volatile `$SeqBitsType`  `$INSTANCE_NAME`_faultStatus;
extern volatile `$SeqBitsType`  `$INSTANCE_NAME`_warnStatus;


/*******************************************************************************
*      Output Configuration Registers
*******************************************************************************/

extern `$SeqBitsType`   `$INSTANCE_NAME`_faultMask;
extern uint8    `$INSTANCE_NAME`_faultEnable;
extern `$SeqBitsType`   `$INSTANCE_NAME`_warnMask;

#if (`$INSTANCE_NAME`_ENABLE_WARNINGS != 0u)
    extern uint8 `$INSTANCE_NAME`_warnEnable;
#endif /* `$INSTANCE_NAME`_ENABLE_WARNINGS != 0u */

#ifdef `$INSTANCE_NAME`_GENERATE_STATUS
    extern `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodMaskList    [`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    extern `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodPolarityList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
#endif /* `$INSTANCE_NAME`_GENERATE_STATUS */


/*******************************************************************************
*       Sequencer State Machine State Variable
*******************************************************************************/

extern CYPDATA volatile uint8   `$INSTANCE_NAME`_state[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/* Enable pin last sample */
extern volatile CYBIT `$INSTANCE_NAME`_enPinLast;

#endif /* (CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
