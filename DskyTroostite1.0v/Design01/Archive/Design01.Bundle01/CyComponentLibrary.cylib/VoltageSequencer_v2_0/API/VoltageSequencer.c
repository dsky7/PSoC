/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all API functionality of the Voltage Sequencer component.
*
* Note:
*
*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

/* Power system configuration set by user in the customizer. Used to initialize
*  the settings in `$INSTANCE_NAME`_Init() API.
*/
#if(`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u)
    `$initStsPgoodMaskList`
    `$initStsPgoodPolarityList`
#endif /* `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u) */

#if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
    `$initCtlShutdownMaskList`
#endif /*`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */

`$initPgoodOnThresholdList`
`$initPgoodPrereqList`
`$initTonDelayList`
`$initTonMaxDelayList`
`$initPgoodOffThresholdList`
`$initPgoodShutdownMaskList`
`$initToffDelayList`
`$initToffMaxDelayList`
`$initTonMaxFaultReseqCfg`
`$initCtlFaultReseqCfg`
`$initPgoodFaultReseqCfg`
`$initOvFaultReseqCfg`
`$initUvFaultReseqCfg`
`$initOcFaultReseqCfg`
`$initFaultReseqSrcList`
`$initState`


/*******************************************************************************
*                      Runtime power system configuration
*******************************************************************************/    

/* Polarity of the general purpose control inputs */
#if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
    uint8  `$INSTANCE_NAME`_ctlPolarity;
    /* Defines which ctl[x] pins are power up pre-requisites for each converter */    
    `$ctlPrereqList`
    /* Defines which ctl[x] pins will generate a fault condition for each converter */
    uint8  `$INSTANCE_NAME`_ctlShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    /* Defines shutdown group for each of ctl[x] inputs */
    `$ctlGroupShutdownMask`
    /* Specifies which ctl[x] pins have caused a shutdown */
    volatile uint8 `$INSTANCE_NAME`_ctlStatus;
    /* Defines the re-sequence configuration for CTL fault conditions */
    uint8 `$INSTANCE_NAME`_ctlFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */

#if(`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u)
    /* Defines which pgood[x] pins are used to generate each sts[x] output */
    uint32 `$INSTANCE_NAME`_stsPgoodMaskList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    /* Defines the logic conditions for generation of each sts[x] output */
    uint32 `$INSTANCE_NAME`_stsPgoodPolarityList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
#endif /* `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u) */

/* Defines power good voltage threshold for power on detection */
uint16 `$INSTANCE_NAME`_pgoodOnThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines which converter have the enable pin as a power up pre-requisite */
uint32 `$INSTANCE_NAME`_enPinPrereqMask;
/* Defines which converter have a host initiated Forced On command as a power up pre-requisite */
uint32 `$INSTANCE_NAME`_onCmdPrereqMask;
/* Defines which pgood[x] pins are power up pre-requisites for each converter */
uint32 `$INSTANCE_NAME`_pgoodPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TON_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_tonDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TON_MAX_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_tonMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines power good voltage threshold for power off detection */
uint16 `$INSTANCE_NAME`_pgoodOffThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines which pgood[x] pins will generate a fault condition for each converter */
uint32 `$INSTANCE_NAME`_pgoodShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines which converters will be disabled if pgood[x] generates a fault */
`$pgoodGroupShutdownMask`
/* Defines TOFF_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_toffDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TOFF_MAX_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_toffMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* System Stable Time parameter */
uint16 `$INSTANCE_NAME`_sysStableTime;
/* Global TRESEQ_DELAY parameter */
uint16 `$INSTANCE_NAME`_globalReseqDelay;
/* Defines the power converter fault re-sequence sources */
uint8 `$INSTANCE_NAME`_faultReseqSrcList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for OV fault conditions */
uint8 `$INSTANCE_NAME`_ovFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for UV fault conditions */
uint8 `$INSTANCE_NAME`_uvFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for OC fault conditions */
uint8 `$INSTANCE_NAME`_ocFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for TON_MAX fault conditions */
uint8 `$INSTANCE_NAME`_tonMaxFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for pgood fault conditions */
uint8 `$INSTANCE_NAME`_pgoodFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Enable/disable assertion of the fault output signal */ 
uint8 `$INSTANCE_NAME`_faultEnable;
/* Defines which power converters have faults enabled */
uint32 `$INSTANCE_NAME`_faultMask;
/* Enable/disable assertion of the warn output signal */
#if (`$INSTANCE_NAME`_DISABLE_WARNINGS == 0u)
    uint8 `$INSTANCE_NAME`_warnEnable;
#endif /* `$INSTANCE_NAME`_DISABLE_WARNINGS == 0u */    
/* Defines which power converters have warnings enabled */
uint32 `$INSTANCE_NAME`_warnMask;
/* Power system status and mask registers */
/* Contains TOFF_MAX_WARN warning status for all power converters */
volatile uint32 `$INSTANCE_NAME`_warnStatus = 0x00000000u;
/* Contains TOFF_MAX_WARN warning status for all power converters */
volatile uint32 `$INSTANCE_NAME`_faultStatus = 0x00000000u;
/* Sequencer State Machine States  */
CYPDATA volatile uint8  `$INSTANCE_NAME`_state[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Forced ON and forced OFF command registers */
volatile uint32 `$INSTANCE_NAME`_forceOnCmdReg = 0x00000000u;
volatile uint32 `$INSTANCE_NAME`_forceOffCmdReg = 0x00000000u;
uint32 `$INSTANCE_NAME`_powerOffMode = 0x00000000u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitSystemConfig
********************************************************************************
*
* Summary:
*  Sets all variables based on parameters entered into the customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void `$INSTANCE_NAME`_InitSystemConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_InitSystemConfig")`
{
    uint8 converterNum;
    
    #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
        `$INSTANCE_NAME`_ctlPolarity = `$INSTANCE_NAME`_INIT_CTL_POLARITY;        
    #endif /* (`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u) */

    #if(`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u)
        for(converterNum = 0; converterNum < `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS; converterNum++)
        {
            `$INSTANCE_NAME`_stsPgoodMaskList[converterNum] = `$INSTANCE_NAME`_initStsPgoodMaskList[converterNum];
            `$INSTANCE_NAME`_stsPgoodPolarityList[converterNum] = \
                                                          `$INSTANCE_NAME`_initStsPgoodPolarityList[converterNum];
        }    
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u) */

    `$INSTANCE_NAME`_enPinPrereqMask = `$INSTANCE_NAME`_INIT_EN_PIN_PREREQ_MASK;
    `$INSTANCE_NAME`_onCmdPrereqMask = `$INSTANCE_NAME`_INIT_ON_CMD_PREREQ_MASK;
    `$INSTANCE_NAME`_sysStableTime = `$INSTANCE_NAME`_INIT_SYS_STABLE_TIME;
    `$INSTANCE_NAME`_globalReseqDelay = `$INSTANCE_NAME`_INIT_GLOBAL_RESEQ_DELAY;
    
    for(converterNum = 0u; converterNum < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; converterNum++)
    {
        `$INSTANCE_NAME`_pgoodOnThresholdList[converterNum] = `$INSTANCE_NAME`_initPgoodOnThresholdList[converterNum];
        `$INSTANCE_NAME`_pgoodPrereqList[converterNum] = `$INSTANCE_NAME`_initPgoodPrereqList[converterNum];
        `$INSTANCE_NAME`_tonDelayList[converterNum] = `$INSTANCE_NAME`_initTonDelayList[converterNum];
        `$INSTANCE_NAME`_tonMaxDelayList[converterNum] = `$INSTANCE_NAME`_initTonMaxDelayList[converterNum];
        `$INSTANCE_NAME`_pgoodOffThresholdList[converterNum] = `$INSTANCE_NAME`_initPgoodOffThresholdList[converterNum];
        #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
            `$INSTANCE_NAME`_ctlShutdownMaskList[converterNum] = `$INSTANCE_NAME`_initCtlShutdownMaskList[converterNum];
        #endif /* (`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u) */
        `$INSTANCE_NAME`_faultReseqSrcList[converterNum] = `$INSTANCE_NAME`_initFaultReseqSrcList[converterNum];
        `$INSTANCE_NAME`_toffDelayList[converterNum] = `$INSTANCE_NAME`_initToffDelayList[converterNum];
        `$INSTANCE_NAME`_toffMaxDelayList[converterNum] = `$INSTANCE_NAME`_initToffMaxDelayList[converterNum];       
        `$INSTANCE_NAME`_pgoodShutdownMaskList[converterNum] = `$INSTANCE_NAME`_initPgoodShutdownMaskList[converterNum];
        `$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initTonMaxFaultReseqCfg[converterNum];
        `$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initCtlFaultReseqCfg[converterNum];
        `$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initPgoodFaultReseqCfg[converterNum];
        `$INSTANCE_NAME`_ovFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initOvFaultReseqCfg[converterNum];
        `$INSTANCE_NAME`_uvFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initUvFaultReseqCfg[converterNum];
        `$INSTANCE_NAME`_ocFaultReseqCfg[converterNum] = `$INSTANCE_NAME`_initOcFaultReseqCfg[converterNum];        
    }          
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Enables the component and places all power converter state machines
*  into the appropriate state (OFF or PEND_ON).
*  Calls the Init() API if the component has not been initialized before.
*  Calls the Enable() API.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on 
*  first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    uint8 converterNum;
    
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Place all power converter state machines into the appropriate state */
    for(converterNum = 0u; converterNum < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; converterNum++)
    {
        `$INSTANCE_NAME`_state[converterNum] = `$INSTANCE_NAME`_initState[converterNum];
    }
    /* Enable fault generation for all power converters */
    `$INSTANCE_NAME`_faultMask = `$INSTANCE_NAME`_CONVERTER_MASK;
    /* Enable assertion of the fault output signal */
    `$INSTANCE_NAME`_faultEnable = `$INSTANCE_NAME`_ENABLED;
    /* Clear power converter warning mask */
    `$INSTANCE_NAME`_warnMask = ~`$INSTANCE_NAME`_CONVERTER_MASK;
    
    #if (`$INSTANCE_NAME`_DISABLE_WARNINGS == 0u)
        /* Enable assertion of the warn output signal */
        `$INSTANCE_NAME`_warnEnable = `$INSTANCE_NAME`_ENABLED;
    #endif /* `$INSTANCE_NAME`_DISABLE_WARNINGS == 0u) */
    
    /* Initialize general status outputs */
    #ifdef `$INSTANCE_NAME`_GENERATE_STATUS
        `$INSTANCE_NAME`_STS_OUT_REG = (uint8)(~`$INSTANCE_NAME`_INIT_STS_POLARITY);
    #endif /* `$INSTANCE_NAME`_GENERATE_STATUS */
 
    
    /***************************************************************************
    * Add your custom code between the following #START and #END tags
    ***************************************************************************/
    /* `#START INIT_SECTION` */
    
    /* `#END`  */
       
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All output terminals are de-asserted.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;
    
    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();    
    /* Enable time tick genaration */
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG &= ~`$INSTANCE_NAME`_TICK_TIMER_EN;
    /* Disable ctl input monitoring */
    #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
        `$INSTANCE_NAME`_CTL_LO_AUX_REG &= ~`$INSTANCE_NAME`_CTL_MON_EN;
        `$INSTANCE_NAME`_CTL_HI_AUX_REG &= ~`$INSTANCE_NAME`_CTL_MON_EN;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);
    
    /* Disable interrupts */
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);    
    CyIntClearPending(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    
    /* De-assert all output terminal */
    
    /* De-assert converters 1 through 8 */
    `$INSTANCE_NAME`_EN_CTL1_REG = 0u;
    `$INSTANCE_NAME`_ON_CTL1_REG = 0u;
    
    /* De-assert converters 9 through 16 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u)
        `$INSTANCE_NAME`_EN_CTL2_REG = 0u;
        `$INSTANCE_NAME`_ON_CTL2_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u */
    
    /* De-assert converters 17 through 24 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 16u)
        `$INSTANCE_NAME`_EN_CTL3_REG = 0u;
        `$INSTANCE_NAME`_ON_CTL3_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 16u */
    
    /* De-assert converters 25 through 32 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 24u)
        `$INSTANCE_NAME`_EN_CTL4_REG = 0u;
        `$INSTANCE_NAME`_ON_CTL4_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 24u */
    
    /* De-assert general status outputs */
    #ifdef `$INSTANCE_NAME`_GENERATE_STATUS
        `$INSTANCE_NAME`_STS_OUT_REG = (uint8)(~`$INSTANCE_NAME`_INIT_STS_POLARITY);
    #endif /* `$INSTANCE_NAME`_GENERATE_STATUS */
    
    /* De-assert system status outputs */
    #ifndef `$INSTANCE_NAME`_VSeq_SystemStsReg__REMOVED
        `$INSTANCE_NAME`_SYSTEM_STATUS_REG = 0u;
    #endif /* `$INSTANCE_NAME`_VSeq_SystemStsReg__REMOVED */
    
    /* Clear all statuss */
    #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
        `$INSTANCE_NAME`_ctlStatus   = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */
    `$INSTANCE_NAME`_faultStatus = 0u;
    `$INSTANCE_NAME`_warnStatus = 0u;
    `$INSTANCE_NAME`_forceOnCmdReg = 0u;
    `$INSTANCE_NAME`_forceOffCmdReg = 0u;
    `$INSTANCE_NAME`_powerOffMode = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the component. Parameter settings are initialized based on
*  parameters entered into the customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_InitSystemConfig();
    /* Mask ctl[6:1] fault monitoring */
    `$INSTANCE_NAME`_CTL_LO_MASK_REG = `$INSTANCE_NAME`_CTL_LO_FLT_DISBL;                              
    #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
        `$INSTANCE_NAME`_CTL_HI_MASK_REG = `$INSTANCE_NAME`_CTL_HI_FLT_DISBL;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */
    
    /* Voltage Sequencer ISR Initialization */
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    /* Set the ISR to point to the Interrupt processing routines */
    CyIntSetVector(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER, `$INSTANCE_NAME`_SeqStateMachineIsr);
    CyIntSetVector(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER, `$INSTANCE_NAME`_SysStableTimerIsr);
    CyIntSetVector(`$INSTANCE_NAME`_FAULT_ISR_NUMBER, `$INSTANCE_NAME`_FaultHandlerIsr);
    /* Set the priority */
    CyIntSetPriority(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER, `$INSTANCE_NAME`_SEQUENCER_ISR_PRIORITY);
    CyIntSetPriority(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER, `$INSTANCE_NAME`_STABLE_TIMER_ISR_PRIORITY);
    CyIntSetPriority(`$INSTANCE_NAME`_FAULT_ISR_NUMBER, `$INSTANCE_NAME`_FAULT_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    
    /* Enable control input fault monitoring */
    #if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)
        `$INSTANCE_NAME`_CTL_LO_AUX_REG |= `$INSTANCE_NAME`_CTL_MON_EN;
        `$INSTANCE_NAME`_CTL_HI_AUX_REG |= `$INSTANCE_NAME`_CTL_MON_EN;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */
    
    /* Enable interrupts */
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    
    /* Enable time tick genaration */
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG |= `$INSTANCE_NAME`_TICK_TIMER_EN;    
    
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);
    
}

#if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlPolarity
    ********************************************************************************
    *
    * Summary:
    *  Sets the polarity of the selected general purpose
    *  sequencer control input (ctl[x]).
    *
    * Parameters:
    *  ctlNum: Specifies the control pin number (Valid range: 1-6).
    *  ctlPolarity: Specifies the polarity of the control pin.
    *   Options: 1=active high, 0=active low
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlPolarity(uint8 ctlNum, uint8 ctlPolarity) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetCtlPolarity")`
    {
        if(ctlNum <= `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS)
        {   
            CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            `$INSTANCE_NAME`_ctlPolarity &= ~(0x01u << (ctlNum - 1u));
            `$INSTANCE_NAME`_ctlPolarity |= ((ctlPolarity & 0x01u) << (ctlNum - 1u));
            CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlPolarity
    ********************************************************************************
    *
    * Summary:
    *  Returns the polarity of the selected general purpose
    *  sequencer control input (ctl[x]).
    *
    * Parameters:
    *  uint8 ctlNum:
    *   Specifies the control pin number
    *   Valid range: 1-6
    *
    * Return:
    *  uint8 ctlPolarity:
    *   Specifies the polarity of the control pin
    *   Options: 1=active high, 0=active low
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlPolarity(uint8 ctlNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlPolarity")`
    {
        uint8 CtlPolarity = 0u;

        if((ctlNum > 0) && (ctlNum <= `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS))
        {
            CtlPolarity = (`$INSTANCE_NAME`_ctlPolarity >> (ctlNum-1u)) & 0x01u;
        }

        return (CtlPolarity);
    }
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */

#if(`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetStsPgoodMask
    ********************************************************************************
    *
    * Summary:
    *  Specifies which pgood[x] signals participate in the generation of the
    *  specified general purpose sequencer control output pins (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *  stsPgoodMask:
    *   Bit Field          Status Pgood Mask
    *   0                  1=Sts output depends on pgood[1]
    *   1                  1=Sts output depends on pgood[2]
    *   ...                ...
    *   31                 1=Sts output depends on pgood[32]
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodMaskList[] - defines which pgood[x] pins
    *   are used to generate each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetStsPgoodMask(uint8 stsNum, uint32 stsPgoodMask) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetStsPgoodMask")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            `$INSTANCE_NAME`_stsPgoodMaskList[(stsNum - 1u)] = stsPgoodMask;
            CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetStsPgoodMask
    ********************************************************************************
    *
    * Summary:
    *  Returns which pgood[x] signals participate in the generation of the
    *  specified general purpose sequencer control output pins (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *
    * Return:
    *  stsPgoodMask:
    *   Bit Field          Status Pgood Mask
    *   0                  1=Sts output depends on pgood[1]
    *   1                  1=Sts output depends on pgood[2]
    *   ...                ...
    *   31                 1=Sts output depends on pgood[32]
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodMaskList[] - defines which pgood[x] pins
    *   are used to generate each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetStsPgoodMask(uint8 stsNum) `=ReentrantKeil($INSTANCE_NAME . "_GetStsPgoodMask")`
    {
        uint32 stsPgoodMask = 0u;

        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            stsPgoodMask = `$INSTANCE_NAME`_stsPgoodMaskList[(stsNum - 1u)];
        }
        
        return (stsPgoodMask);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetStsPgoodPolarity
    ********************************************************************************
    *
    * Summary:
    *  Configures the logic conditions that will cause the selected general
    *  purpose sequencer control output pins (sts[x]) to be asserted.
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *  stsPgoodPolarity - specifies the polarity of the pgood[x] signal required
    *   to assert the specified sts[x] signal:
    *   Bit Field          Status Polarity
    *   0                  0=pgood[1] must be low,
    *                      1=pgood[1] must be high
    *   1                  0=pgood[2] must be low,
    *                      1=pgood[2] must be high
    *   ...                ...
    *   31                 0=pgood[32] must be low,
    *                      1=pgood[32] must be high
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodPolarityList[] - the logic conditions for
    *   generation of each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetStsPgoodPolarity(uint8 stsNum, uint32 pgoodPolarity) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetStsPgoodPolarity")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            `$INSTANCE_NAME`_stsPgoodPolarityList[(stsNum - 1u)] = pgoodPolarity;
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetStsPgoodPolarity
    ********************************************************************************
    *
    * Summary:
    *  Returns the polarity of the pgood[x] signals used in the AND expression
    *  for the selected general purpose sequencer control output (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *
    * Return:
    *  stsPgoodPolarity - specifies the polarity of the pgood[x] signal required
    *   to assert the specified sts[x] signal:
    *   Bit Field          Status Polarity
    *   0                  0=pgood[1] must be low,
    *                      1=pgood[1] must be high
    *   1                  0=pgood[2] must be low,
    *                      1=pgood[2] must be high
    *   ...                ...
    *   31                 0=pgood[32] must be low,
    *                      1=pgood[32] must be high
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodPolarityList[] - the logic conditions for
    *   generation of each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetStsPgoodPolarity(uint8 stsNum) `=ReentrantKeil($INSTANCE_NAME . "_GetStsPgoodPolarity")`
    {
        uint32 pgoodPolarity = 0u;

        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            pgoodPolarity = `$INSTANCE_NAME`_stsPgoodPolarityList[(stsNum - 1u)];
        }

        return (pgoodPolarity);
    }

#endif /* `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS > 0u */

    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodOnThreshold
********************************************************************************
*
* Summary:
*  Sets the power good voltage threshold for power on detection.
*
* Parameters:
*  ctlNum - specifies the converter number. Valid range: 1-32.
*  onThreshold - specifies the power good power on threshold in mV.
*   Valid range: 0-65535
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOnThresholdList[] - defines power good voltage
*   threshold for power on detection.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodOnThreshold(uint8 converterNum, uint16 onThreshold) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOnThreshold")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_pgoodOnThresholdList[(converterNum - 1u)] = onThreshold;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodOnThreshold
********************************************************************************
*
* Summary:
*  Returns the power good voltage threshold for power on detection.
*
* Parameters:
*  uint8 ctlNum - specifies the converter number. Valid range: 1-32.
*
* Return:
*  uint16 onThreshold - specifies the power good power on threshold in mV.
*   Valid range: 0-65535
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOnThresholdList[] - defines power good voltage
*   threshold for power on detection.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetPgoodOnThreshold(uint8 converterNum) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOnThreshold")`
{
    uint16 onThreshold = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        onThreshold = `$INSTANCE_NAME`_pgoodOnThresholdList[(converterNum - 1u)];
    }

    return (onThreshold);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetEnPinPrereq
********************************************************************************
*
* Summary:
*  Determines which power converter state machines have
*  the enable pin as a power up pre-requisite.
*
* Parameters:
*  converterMask:
*   Bit Field          Converter Mask
*   0                  1=power converter 1 has the enable signal
*                       as a sequencing pre-requisite
*   1                  1=power converter 2 has the enable signal
*                       as a sequencing pre-requisite
*   ...                ...
*   31                 1=power converter 32 has the enable signal
*                       as a sequencing pre-requisite
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_enPinPrereqMask - defines which converter
*   have the enable pin as a power up pre-requisite.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetEnPinPrereq(uint32 converterMask) `=ReentrantKeil($INSTANCE_NAME . "_SetEnPinPrereq")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_enPinPrereqMask = converterMask;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetEnPinPrereq
********************************************************************************
*
* Summary:
*  Returns which power converter state machines have
*  the enable pin as a power up pre-requisite.
*
* Parameters:
*  None
*
* Return:
*  converterMask:
*   Bit Field          Converter Mask
*   0                  1=power converter 1 has the enable signal
*                       as a sequencing pre-requisite
*   1                  1=power converter 2 has the enable signal
*                       as a sequencing pre-requisite
*   ...                ...
*   31                 1=power converter 32 has the enable signal
*                       as a sequencing pre-requisite
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_enPinPrereqMask - defines which converter
*   have the enable pin as a power up pre-requisite.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetEnPinPrereq(void) `=ReentrantKeil($INSTANCE_NAME . "_GetEnPinPrereq")`
{
    return (`$INSTANCE_NAME`_enPinPrereqMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOnCmdPrereq
********************************************************************************
*
* Summary:
*  Determines which power converter state machines have
*  a host initiated Forced On command as a power up prerequisite.
*
* Parameters:
*  converterMask:
*   Bit Field          Converter Mask
*   0                  1=power converter 1 has Forced On
*                       command as a sequencing pre-requisite
*   1                  1=power converter 2 has Forced On
*                       command as a sequencing pre-requisite
*   ...                ...
*   31                 1=power converter 32 has Forced On
*                       command as a sequencing pre-requisite
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_onCmdPrereqMask - defines which converter
*   have the enable pin as a power up pre-requisite.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOnCmdPrereq(uint32 converterMask) `=ReentrantKeil($INSTANCE_NAME . "_SetOnCmdPrereq")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_onCmdPrereqMask = converterMask;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOnCmdPrereq
********************************************************************************
*
* Summary:
*  Determines which power converter state machines have
*  a host initiated Forced On command as a power up prerequisite.
*
* Parameters:
*  None
*
* Return:
*  converterMask:
*   Bit Field          Converter Mask
*   0                  1=power converter 1 has Forced On
*                       command as a sequencing pre-requisite
*   1                  1=power converter 2 has Forced On
*                       command as a sequencing pre-requisite
*   ...                ...
*   31                 1=power converter 32 has Forced On
*                       command as a sequencing pre-requisite
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_onCmdPrereqMask - defines which converter
*   have the enable pin as a power up pre-requisite.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetOnCmdPrereq(void) `=ReentrantKeil($INSTANCE_NAME . "_GetOnCmdPrereq")`
{
    return (`$INSTANCE_NAME`_onCmdPrereqMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodPrereq
********************************************************************************
*
* Summary:
*  Determines which pgood[x] pins are power up prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  pgoodMask - specifies which pgood[x] pins are power up prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=pgood[1] must be asserted
*   1                  1=pgood[2] must be asserted
*   ...                ...
*   31                 1=pgood[32] must be asserted
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodPrereqList[] - defines which pgood[x] pins
*   are power up pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodPrereq(uint8 converterNum, uint32 pgoodMask) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodPrereq")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_pgoodPrereqList[(converterNum - 1u)] = pgoodMask;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodPrereq
********************************************************************************
*
* Summary:
*  Determines which pgood[x] pins are power up prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  pgoodMask - specifies which pgood[x] pins are power up prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=pgood[1] must be asserted
*   1                  1=pgood[2] must be asserted
*   ...                ...
*   31                 1=pgood[32] must be asserted
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodPrereqList[]- defines which pgood[x] pins
*   are power up pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetPgoodPrereq(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodPrereq")`
{
    uint32 pgoodMask = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        pgoodMask = `$INSTANCE_NAME`_pgoodPrereqList[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

    return (pgoodMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonDelay
********************************************************************************
*
* Summary:
*  Sets the TON delay parameter for the selected power converter.
*  Defined as the time between a state machine's pre-requisites
*  all becoming satisfied and the en[x] being asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  tonDelay - units = 0.25 ms per LSB.
*   Valid Range=0-65535 (0-16.384 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonDelayList[]- defines TON_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonDelay(uint8 converterNum, uint16 tonDelay) \
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetTonDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_tonDelayList[(converterNum - 1u)] = tonDelay;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonDelay
********************************************************************************
*
* Summary:
*  Returns the TON delay parameter for the selected power converter.
*  Defined as the time between a state machine's pre-requisites
*  all becoming satisfied and the en[x] being asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  tonDelay - units = 0.25 ms per LSB.
*   Valid Range=0-65535 (0-16.384 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonDelayList[]- defines TON_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetTonDelay(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonDelay")`
{
    uint16 tonDelay = 0u;

    if((converterNum > 0u) == (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        tonDelay = `$INSTANCE_NAME`_tonDelayList[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

    return (tonDelay);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMax
********************************************************************************
*
* Summary:
*  Sets the TON_MAX parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being asserted and pgood[x] being asserted. Failure to do
*  so generates a fault condition.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  tonMax - units = 0.25 ms per LSB.
*   Valid Range=0-65535 (0-16.384 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxDelayList[]- defines TON_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMax(uint8 converterNum, uint16 tonMax) `=ReentrantKeil($INSTANCE_NAME . "_SetTonMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_tonMaxDelayList[(converterNum - 1u)] = tonMax;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMax
********************************************************************************
*
* Summary:
*  Returns the TON_MAX parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being asserted and pgood[x] being asserted. Failure to do
*  so generates a fault condition.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  tonMax - units = 0.25 ms per LSB.
*   Valid Range=0-65535 (0-16.384 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxDelayList[]- defines TON_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetTonMax(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMax")`
{
    uint16 tonMax = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        tonMax = `$INSTANCE_NAME`_tonMaxDelayList[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

    return (tonMax);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodOffThreshold
********************************************************************************
*
* Summary:
*  Sets the power good voltage threshold for power off detection.
*
* Parameters:
*  ctlNum - specifies the converter number. Valid range: 1-32.
*  offThreshold - specifies the power good power off threshold in mV.
*   Valid range: 0-65535
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOffThresholdList[] - defines power good voltage
*   threshold for power off detection.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodOffThreshold(uint8 converterNum, uint16 offThreshold) \
                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOffThreshold")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_pgoodOffThresholdList[(converterNum - 1u)] = offThreshold;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodOffThreshold
********************************************************************************
*
* Summary:
*  Returns the power good voltage threshold for power off detection.
*
* Parameters:
*  ctlNum - specifies the converter number. Valid range: 1-32.
*
* Return:
*  offThreshold - specifies the power good power off threshold in mV.
*   Valid range: 0-65535
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOffThresholdList[] - defines power good voltage
*   threshold for power off detection.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetPgoodOffThreshold(uint8 converterNum) \
                                                        `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOffThreshold")`
{
    uint16 offThreshold = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        offThreshold = `$INSTANCE_NAME`_pgoodOffThresholdList[(converterNum - 1u)];
    }

    return (offThreshold);
}


#if(`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlShutdownMask
    ********************************************************************************
    *
    * Summary:
    *  Determines which ctl[x] pins will cause the selected power converter to 
    *  shutdown when de-asserted.
    *
    * Parameters:
    *  converterNum - specifies the power converter number.
    *   Valid range: 1-32.
    *  ctlPinMask - specifies which ctl[x] pins can cause a shutdown:
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion will shutdown the converter
    *   1                  1=ctl[2] de-assertion will shutdown the converter
    *   ...                ...
    *   5                  1=ctl[6] de-assertion will shutdown the converter
    *   7..6               Reserved. Set to zeroes
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlShutdownMaskList[] - defines which ctl[x] pins will
    *   cause shutdown for each converter.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlShutdownMask(uint8 converterNum, uint8 ctlPinMask) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetCtlShutdownMask")`
    {
        uint8 enableInterrupts;
        uint8 ctlPin;
        uint32 converterMask;
        converterMask = (1u << (converterNum - 1u)); /* Determine bit to set */
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            /* Enter critical section */
            enableInterrupts = CyEnterCriticalSection();

            `$INSTANCE_NAME`_ctlShutdownMaskList[(converterNum - 1u)] = ctlPinMask;        
            for(ctlPin = 0u; ctlPin < `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS; ctlPin++)
            {              
                if((ctlPinMask & 0x01u) == 0u)
                {
                    `$INSTANCE_NAME`_ctlGroupShutdownMask[ctlPin] &= ~converterMask;
                }
                else
                {
                    `$INSTANCE_NAME`_ctlGroupShutdownMask[ctlPin] |= converterMask;
                }
                ctlPinMask >>= 1u;
            }
            /* Exit critical section */
            CyExitCriticalSection(enableInterrupts);
        }    
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlShutdownMask
    ********************************************************************************
    *
    * Summary:
    *  Determines which ctl[x] pins will cause the selected power converter to 
    *  shutdown when de-asserted.
    *
    * Parameters:
    *  converterNum - specifies the power converter number.
    *   Valid range: 1-32.
    *
    * Return:
    *  ctlPinMask - specifies which ctl[x] pins can cause a shutdown:
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion will shutdown the converter
    *   1                  1=ctl[2] de-assertion will shutdown the converter
    *   ...                ...
    *   5                  1=ctl[6] de-assertion will shutdown the converter
    *   7..6               Reserved. Set to zeroes
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlShutdownMaskList[] - defines which ctl[x] pins will
    *   cause shutdown for each converter.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlShutdownMask(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlShutdownMask")`
    {
        uint8 ctlPinMask = 0u;

        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            ctlPinMask = `$INSTANCE_NAME`_ctlShutdownMaskList[(converterNum - 1u)];
        }

        return (ctlPinMask);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlReseqCnt
    ********************************************************************************
    *
    * Summary:
    *  Sets the re-sequence count for fault conditions due to
    *  de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
    *   1-30=valid re-sequencing counts.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlReseqCnt(uint8 converterNum, uint8 reseqCnt) \
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetCtlReseqCnt")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
    		`$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] = 
                 (`$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                     | (reseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlReseqCnt
    ********************************************************************************
    *
    * Summary:
    *  Returns the re-sequence count for fault conditions due to
    *  de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *
    * Return:
    *  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
    *   1-30=valid re-sequencing counts.
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlReseqCnt")`
    {
        uint8 reseqCnt = 0u;

        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            reseqCnt = `$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
        }

        return (reseqCnt);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlFaultResp
    ********************************************************************************
    *
    * Summary:
    *  Sets the shutdown mode for power converters in response to
    *  fault conditions due to de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *  faultResponse - specifies the shutdown mode for any slave power converters.
    *   Options: 0=immediate, 1=soft.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetCtlFaultResp")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            `$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] = 
                   (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                          (`$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlFaultResp
    ********************************************************************************
    *
    * Summary:
    *  Returns the shutdown mode for power converters in response to
    *  fault conditions due to de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *
    * Return:
    *  faultResponse - specifies the shutdown mode for any slave power converters.
    *   Options: 0=immediate, 1=soft.
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlFaultResp")`
    {
        uint8 faultResponse = 0u;

        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            faultResponse = (`$INSTANCE_NAME`_ctlFaultReseqCfg[(converterNum - 1u)] >>
                                                                        `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
        }

        return (faultResponse);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns which ctl[x] pins have caused one or more converters to shutdown.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 ctlStatus:
    *   Specifies which ctl[x] pins have caused a shutdown
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion caused a shutdown
    *   1                  1=ctl[2] de-assertion caused a shutdown
    *   ...                ...
    *   5                  1=ctl[6] de-assertion caused a shutdown
    *   7..6               Reserved. Set to zeroes.
    * Side Effects:
    *  Calling this API de-asserts the fault output pin.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlStatus")`
    {
        return (`$INSTANCE_NAME`_ctlStatus);
    }

#endif /* `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS > 0u */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodShutdownMask
********************************************************************************
*
* Summary:
*  Determines which other pgood[x] pins will shutdown the selected power
*  converter state machine when de-asserted.
*  Note that the pgood[converterNum] pin is automatically a fault
*  source for the selected power converter whether or not the
*  corresponding bit in the pgoodMask is set or not.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  pgoodMask - specifies which pgood[x] pins can cause a shutdown:
*   Bit Field          Power Good Mask
*   0                  1=pgood[1] de-assertion will shutdown the converter
*   1                  1=pgood[2] de-assertion will shutdown the converter
*   ...                ...
*   31                 1=pgood[32] de-assertion will shutdown the converter
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodShutdownMaskList[] - defines which pgood[x] pins
*   will cause shutdown for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodShutdownMask(uint8 converterNum, uint32 pgoodMask) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodShutdownMask")`
{
    uint8 enableInterrupts;
    uint8 bitPos;
    uint32 bitMask;
    
    bitMask = 1u << (converterNum - 1u); /* Determine bit to set */
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {   
        /* Enter critical section */
        enableInterrupts = CyEnterCriticalSection();
        
        `$INSTANCE_NAME`_pgoodShutdownMaskList[(converterNum - 1u)] = pgoodMask;
        for(bitPos = 0u; bitPos < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; bitPos++)
        {              
            if((pgoodMask & 0x01u) == 0u)
            {
                    `$INSTANCE_NAME`_pgoodGroupShutdownMask[bitPos] &= ~bitMask;
            }
            else
            {
                    `$INSTANCE_NAME`_pgoodGroupShutdownMask[bitPos] |= bitMask;
            }
            pgoodMask >>= 1u;
        }
        /* Exit critical section */
        CyExitCriticalSection(enableInterrupts);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodShutdownMask
********************************************************************************
*
* Summary:
*  Returns which other pgood[x] pins will shutdown the selected power converter
*  when de-asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  pgoodMask - specifies which pgood[x] pins can cause a shutdown:
*   Bit Field          Power Good Power Mask
*   0                  1=pgood[1] de-assertion will shutdown the converter
*   1                  1=pgood[2] de-assertion will shutdown the converter
*   ...                ...
*   31                 1=pgood[32] de-assertion will shutdown the converter
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodShutdownMaskList[] - defines which pgood[x] pins
*   will cause shutdown for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetPgoodShutdownMask(uint8 converterNum) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodShutdownMask")`
{
    uint32 pgoodMask = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        pgoodMask = `$INSTANCE_NAME`_pgoodShutdownMaskList[(converterNum - 1u)];
    }

    return (pgoodMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetToffDelay
********************************************************************************
*
* Summary:
*  Sets the TOFF delay parameter for the selected power converter.
*  Defined as the time between making the decision to turn a power
*  converter of and to actually deasserting the en[x] pin.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  toffDelay - units = 0.25 ms per LSB. Valid Range=0-65535 (0-16.384 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffDelayList[] - defines TOFF_DELAY parameter for
*   each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetToffDelay(uint8 converterNum, uint16 toffDelay) \
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetToffDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_toffDelayList[(converterNum - 1u)] = toffDelay;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetToffDelay
********************************************************************************
*
* Summary:
*  Returns the TOFF delay parameter for the selected power converter.
*  Defined as the time between making the decision to turn a power
*  converter of and to actually de-asserting the en[x] pin.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  toffDelay - units = 0.25 ms per LSB. Valid Range=0-65535 (0-16.384 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffDelayList[] - defines TOFF_DELAY parameter for
*   each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetToffDelay(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetToffDelay")`
{
    uint16 toffDelay = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        toffDelay = `$INSTANCE_NAME`_toffDelayList[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

    return (toffDelay);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetToffMax
********************************************************************************
*
* Summary:
*  Sets the TOFF_MAX_DELAY parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being de-asserted and power converter actually turning off.
*  Failure to do so generates a warning condition.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  toffMax - units = 0.25 ms per LSB. Valid Range=0-65535 (0-16.384 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffMaxDelayList[] - defines TOFF_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetToffMax(uint8 converterNum, uint16 toffMax) `=ReentrantKeil($INSTANCE_NAME . "_SetToffMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_toffMaxDelayList[(converterNum - 1u)] = toffMax;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetToffMax
********************************************************************************
*
* Summary:
*  Returns the TOFF_MAX_DELAY parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being de-asserted and power converter actually turning off.
*  Failure to do so generates a warning condition.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  toffMax - units = 0.25 ms per LSB. Valid Range=0-65535 (0-16.384 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffMaxDelayList[] - defines TOFF_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetToffMax(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetToffMax")`
{
    uint16 toffMax = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        toffMax = `$INSTANCE_NAME`_toffMaxDelayList[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

    return (toffMax);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSysStableTime
********************************************************************************
*
* Summary:
*  Sets the global System Stable Time parameter.
*
* Parameters:
*  stableTime - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_sysStableTime - system Stable Time parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSysStableTime(uint16 stableTime) `=ReentrantKeil($INSTANCE_NAME . "_SetSysStableTime")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_sysStableTime = stableTime;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSysStableTime
********************************************************************************
*
* Summary:
*  Returns the global System Stable Time parameter.
*
* Parameters:
*  None
*
* Return:
*  stableTime - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_sysStableTime - system Stable Time parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetSysStableTime(void) `=ReentrantKeil($INSTANCE_NAME . "_GetSysStableTime")`
{
    uint16 stableTime = 0;
    
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    stableTime = `$INSTANCE_NAME`_sysStableTime;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    
    return (stableTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetReseqDelay
********************************************************************************
*
* Summary:
*  Sets the global TRESEQ_DELAY parameter for all power
*  converter state machines. Defined as the time between making the
*  decision to re-sequence and beginning a new power up sequence.
*
* Parameters:
*  reseqDelay - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_globalReseqDelay - global TRESEQ_DELAY parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetReseqDelay(uint16 reseqDelay) `=ReentrantKeil($INSTANCE_NAME . "_SetReseqDelay")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_globalReseqDelay = reseqDelay;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetReseqDelay
********************************************************************************
*
* Summary:
*  Returns the global TRESEQ_DELAY parameter for all power
*  converter state machines. Defined as the time between making the
*  decision to re-sequence and beginning a new power up sequence.
*
* Parameters:
*  None
*
* Return:
*  reseqDelay - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_globalReseqDelay - global TRESEQ_DELAY parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetReseqDelay(void) `=ReentrantKeil($INSTANCE_NAME . "_GetReseqDelay")`
{
    return (`$INSTANCE_NAME`_globalReseqDelay);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMaxReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for TON_MAX fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  reseqCnt - 5 bit number. Options: 0=no re-sequencing,
*   31=infinite resequencing, 1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMaxReseqCnt(uint8 converterNum, uint8 ReseqCnt) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetTonMaxReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
		`$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] = 
             (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (ReseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMaxReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for TON_MAX fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. Options: 0=no re-sequencing,
*   31=infinite resequencing, 1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTonMaxReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMaxReseqCnt")`
{
    uint8 ReseqCnt = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        ReseqCnt = `$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }

    return (ReseqCnt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMaxFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves when a TON_MAX fault
*  condition occurs on the selected master converter.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMaxFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetTonMaxFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] = 
               (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                      (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMaxFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves when a TON_MAX fault
*  condition occurs on the selected master converter.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTonMaxFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMaxFaultResp")`
{
    uint8 faultResponse = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        faultResponse = (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[(converterNum - 1u)] >>
                                                            `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
    }

    return (faultResponse);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultReseqSrc
********************************************************************************
*
* Summary:
*  Sets the power converter fault re-sequence sources.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqSrc:
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=OV fault source enabled
*   1                  1=UV fault source enabled
*   2                  1=OC fault source enabled
*   7:3                Reserved
*
* Return:
*  None
*
* Side Effects:
*  When reseqSrc is zero, power good (pgood) inputs
*  become the fault re-sequence source.
*
* Global variables:
*  `$INSTANCE_NAME`_faultReseqSrcList[] - defines the power converter fault
*   re-sequence sources.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultReseqSrc(uint8 converterNum, uint8 reseqSrc) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetFaultReseqSrc")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_faultReseqSrcList[(converterNum - 1u)] = reseqSrc;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultReseqSrc
********************************************************************************
*
* Summary:
*  Sets the power converter fault re-sequence sources.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  uint8 reseqSrc:
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=OV fault source enabled
*   1                  1=UV fault source enabled
*   2                  1=OC fault source enabled
*   7:3                Reserved
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultReseqSrcList[] - defines the power converter fault
*   re-sequence sources.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetFaultReseqSrc(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultReseqSrc")`
{
    uint8 reseqSrc = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        reseqSrc = `$INSTANCE_NAME`_faultReseqSrcList[(converterNum - 1u)];
    }

    return (reseqSrc);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for fault conditions due to
*  de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:.
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodReseqCnt(uint8 converterNum, uint8 reseqCnt) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
		`$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] = 
             (`$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for fault conditions due to
*  de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPgoodReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodReseqCnt")`
{
    uint8 reseqCnt = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        reseqCnt = `$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }

    return (reseqCnt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves for fault conditions
*  due to de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] = 
               (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                      (`$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves for fault conditions
*  due to de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPgoodFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodFaultResp")`
{
    uint8 faultResponse = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        faultResponse = (`$INSTANCE_NAME`_pgoodFaultReseqCfg[(converterNum - 1u)] >>
                                                                    `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
    }

    return (faultResponse);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOvReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for over-voltage (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOvReseqCnt(uint8 converterNum, uint8 reseqCnt) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
		`$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] = 
             (`$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOvReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for over-voltage (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOvReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOvReseqCnt")`
{
    uint8 reseqCnt = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        reseqCnt = `$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }

    return (reseqCnt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOvFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to overvoltage
*  (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOvFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] = 
               (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                      (`$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOvFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to overvoltage
*  (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initOvFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOvFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOvFaultResp")`
{
    uint8 faultResponse = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        faultResponse = (`$INSTANCE_NAME`_ovFaultReseqCfg[(converterNum - 1u)] >>
                                                                    `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
    }

    return (faultResponse);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUvReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for under-voltage (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUvReseqCnt(uint8 converterNum, uint8 reseqCnt) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetUvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
		`$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] = 
             (`$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUvReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for under-voltage (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetUvReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUvReseqCnt")`
{
    uint8 reseqCnt = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        reseqCnt = `$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }

    return (reseqCnt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUvFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to undervoltage
*  (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUvFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetUvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] = 
               (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                      (`$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUvFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to undervoltage
*  (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetUvFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUvFaultResp")`
{
    uint8 faultResponse = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        faultResponse = (`$INSTANCE_NAME`_uvFaultReseqCfg[(converterNum - 1u)] >>
                                                                    `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
    }

    return (faultResponse);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOcReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for over-current (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOcReseqCnt(uint8 converterNum, uint8 reseqCnt) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOcReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
		`$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] = 
             (`$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOcReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for over-current (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOcReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOcReseqCnt")`
{
    uint8 reseqCnt = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        reseqCnt = `$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] & (~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }

    return (reseqCnt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOcFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to overcurrent
*  (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOcFaultResp(uint8 converterNum, uint8 faultResponse) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOcFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] = 
               (faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) | 
                      (`$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] & ~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOcFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to overcurrent
*  (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOcFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOcFaultResp")`
{
    uint8 faultResponse = 0u;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        faultResponse = (`$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] >>
                                                                    `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u;
    }

    return (faultResponse);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnFaults
********************************************************************************
*
* Summary:
*  Enables/disables assertion of the fault output signal.
*  Faults are still processed by the state machine and fault
*  status is still available through the GetFaultStatus() API.
*
* Parameters:
*  faultEnable - Options: 0=disabled, 1=enabled.
*   Enabled when the component is started.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultRespMode - enable/disable assertion of the
*   fault output signal.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnFaults(uint8 faultEnable) `=ReentrantKeil($INSTANCE_NAME . "_EnFaults")`
{
    `$INSTANCE_NAME`_faultEnable = faultEnable;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultMask
********************************************************************************
*
* Summary:
*  Sets which power converters have faults enabled.
*
* Parameters:
*  faultMask:
*   Bit Field          Fault Mask
*   0                  1=enable fault detection for power converter 1
*   1                  1=enable fault detection for power converter 2
*   ...                ...
*   31                 1=enable fault detection for power converter 32
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultMask - defines which power converters have
*   faults enabled.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultMask(uint32 faultMask) `=ReentrantKeil($INSTANCE_NAME . "_SetFaultMask")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_faultMask = faultMask;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultMask
********************************************************************************
*
* Summary:
*  Gets which power converters have faults enabled.
*
* Parameters:
*  None
*
* Return:
*  faultMask:
*  Fault mask of power converters
*   Bit Field          Fault Mask
*   0                  1=fault detection for power converter 1 is enabled
*   1                  1=fault detection for power converter 2 is enabled
*   ...                ...
*   31                 1=fault detection for power converter 32 is enabled
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultMask - defines which power converters have
*   faults enabled.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetFaultMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultMask")`
{
    return(`$INSTANCE_NAME`_faultMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultStatus
********************************************************************************
*
* Summary:
*  Returns a bit mask containing the pgood fault status for all power 
*  converters. Bits are sticky until cleared by calling this API.
*
* Parameters:
*  None
*
* Return:
*  uint32 faultStatus:
*   Fault status of power converters
*   Bit Field          Fault Mask
*   0                  1=power converter 1 has/had a fault
*   1                  1=power converter 2 has/had a fault
*   ...                ...
*   31                 1=power converter 32 has/had a fault
*
* Side Effects:
*  Calling this API de-asserts the fault output pin.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetFaultStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultStatus")`
{
    uint8 enableInterrupts;
    uint32 faultStatus;

    /* Enter critical section */
    enableInterrupts = CyEnterCriticalSection();
    
    faultStatus = `$INSTANCE_NAME`_faultStatus;
    `$INSTANCE_NAME`_faultStatus = 0u;
    
    /* Exit critical section */
    CyExitCriticalSection(enableInterrupts);
    return (faultStatus);
}

#if (`$INSTANCE_NAME`_DISABLE_WARNINGS == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnWarnings
    ********************************************************************************
    *
    * Summary:
    *  Enables/disables assertion of the warn output signal.
    *  Warning status is still available through the GetWarningStatus() API.
    *
    * Parameters:
    *  uint8 warnEnable:
    *   Options: 0=disabled, 1=enabled
    *   Enabled when the component is started
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnWarnings(uint8 warnEnable) `=ReentrantKeil($INSTANCE_NAME . "_EnWarnings")`
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_warnEnable = warnEnable;
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }

#endif /* `$INSTANCE_NAME`_DISABLE_WARNINGS == 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetWarnMask
********************************************************************************
*
* Summary:
*  Sets which power converters have warnings enabled.
*
* Parameters:
*  uint32 warnMask:
*   Bit Field          Warning Mask
*   0                  1=enable warnings for power converter 1
*   1                  1=enable warnings for power converter 2
*   ...                ...
*   31                 1=enable warnings for power converter 32
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetWarnMask(uint32 warnMask) `=ReentrantKeil($INSTANCE_NAME . "_SetWarningMask")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_warnMask = warnMask;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetWarnMask
********************************************************************************
*
* Summary:
*  Returns which power converters have warnings enabled.
*
* Parameters:
*  None
*
* Return:
*  uint32 warnMask:
*   Bit Field          Warning Mask
*   0                  1=warnings for power converter 1 are enabled
*   1                  1=warnings for power converter 2 are enabled
*   ...                ...
*   31                 1=warnings for power converter 32 are enabled
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetWarnMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetWarningMask")`
{
    uint32 warnMask;
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    warnMask = `$INSTANCE_NAME`_warnMask;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    return(warnMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetWarnStatus
********************************************************************************
*
* Summary:
*  Returns a bit mask containing TOFF_MAX_WARN warning status
*  for all power converters. Bits are sticky until
*  cleared by calling this API.
*
* Parameters:
*  None
*
* Return:
*  uint32 warnStatus:
*   Warn status of power converters
*   Bit Field          Warning Status
*   0                  1=power converter 1 has/had a warning
*   1                  1=power converter 2 has/had a warning
*   ...                ...
*   31                 1=power converter 32 has/had a warning
*
* Side Effects:
*  Calling this API de-asserts the warn output pin.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetWarnStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetWarnStatus")`
{
    uint32 warnStatus;
    
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    warnStatus = `$INSTANCE_NAME`_warnStatus;
    `$INSTANCE_NAME`_warnStatus = 0u;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    return warnStatus;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetState
********************************************************************************
*
* Summary:
*  Returns the current state machine state for the selected
*  power converter.
*
* Parameters:
*  uint8 converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*
* Return:
*  uint32 warningStatus:
*   Fault status of power converters
*   Encoding           State
*   0                  OFF
*   1                  PEND_ON
*   2                  TON_DELAY
*   3                  TON_MAX
*   4                  ON
*   5                  TOFF_DELAY
*   6                  TOFF_MAX
*   7                  PEND_RESEQ
*   8                  TRESEQ_DELAY                  
*   9..255             Undefined
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetState(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetState")`
{
    uint8 state = 0xFF; /* Undefined */
    
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        state = `$INSTANCE_NAME`_state[(converterNum - 1u)];
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    
    return state;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceOff
********************************************************************************
*
* Summary:
*  Forces the selected power converter to power down
*  either immediately or after the TOFF delay.
*
* Parameters:
*  uint8 converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*  uint8 powerOffMode:
*   Specifies the shutdown mode
*   Options: 0=immediate, 1=soft
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceOff(uint8 converterNum, uint8 powerOffMode) `=ReentrantKeil($INSTANCE_NAME . "_ForceOff")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_powerOffMode   |= (((uint32) powerOffMode) << (converterNum - 1u));
        `$INSTANCE_NAME`_forceOffCmdReg |= (((uint32) 1u) << (converterNum - 1u));
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceAllOff
********************************************************************************
*
* Summary:
*  Forces all power converters to power down either
*  immediately or after their TOFF delays.
*
* Parameters:
*  uint8 powerOffMode:
*   Specifies the shutdown mode
*   Options: 0=immediate, 1=soft
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceAllOff(uint8 powerOffMode) `=ReentrantKeil($INSTANCE_NAME . "_ForceAllOff")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    if(powerOffMode == 0u)
    {
        `$INSTANCE_NAME`_powerOffMode = 0u; /* Immediate shutdown */
    }
    else
    {
        `$INSTANCE_NAME`_powerOffMode = `$INSTANCE_NAME`_CONVERTER_MASK; /* Soft shutdown */
    }
    `$INSTANCE_NAME`_forceOffCmdReg = `$INSTANCE_NAME`_CONVERTER_MASK;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceOn
********************************************************************************
*
* Summary:
*  Forces the selected power converter to power up.
*
* Parameters:
*  uint8 converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*
* Return:
*  None
*
* Side Effects:
*  Reset the re-sequence counter for the selected power converter.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceOn(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_ForceOn")`
{   
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_forceOnCmdReg |= (((uint32)1u) << (converterNum - 1u));
        CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceAllOn
********************************************************************************
*
* Summary:
*  Forces all power converter to power up.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Reset the re-sequence counters for all power converters.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceAllOn(void) `=ReentrantKeil($INSTANCE_NAME . "_ForceAllOn")`
{
    CyIntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_forceOnCmdReg = `$INSTANCE_NAME`_CONVERTER_MASK;
    CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/* [] END OF FILE */
