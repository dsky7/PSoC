/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v1_50_`$INSTANCE_NAME`_H)
#define CY_Timer_v1_50_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* PSoC3 ES2 or early */
#define `$INSTANCE_NAME`_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES1 or early */
#define `$INSTANCE_NAME`_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define `$INSTANCE_NAME`_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES2 or later */
#define `$INSTANCE_NAME`_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


/**************************************
*           Parameter Defaults        
**************************************/

#define `$INSTANCE_NAME`_Resolution                 `$Resolution`u
#define `$INSTANCE_NAME`_UsingFixedFunction         `$FixedFunctionUsed`u
#define `$INSTANCE_NAME`_UsingHWCaptureCounter      `$HWCaptureCounterEnabled`u
#define `$INSTANCE_NAME`_SoftwareCaptureMode        `$SoftwareCaptureModeEnabled`u
#define `$INSTANCE_NAME`_SoftwareTriggerMode        `$SoftwareTriggerModeEnabled`u
#define `$INSTANCE_NAME`_UsingHWEnable              `$UsesHWEnable`u
#define `$INSTANCE_NAME`_EnableTriggerMode          `$TriggerInputEnabled`u
#define `$INSTANCE_NAME`_InterruptOnCaptureCount    `$InterruptOnCapture`u
#define `$INSTANCE_NAME`_RunModeUsed                `$RunMode`u
#define `$INSTANCE_NAME`_ControlRegRemoved          `$ControlRegRemoved`u


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct `$INSTANCE_NAME`_backupStruct
{
    #if (!`$INSTANCE_NAME`_ControlRegRemoved)
        #if (!`$INSTANCE_NAME`_UsingFixedFunction)
            uint8 control;
        #endif
        
        uint8 enableState;
    #endif   
    
    #if (!`$INSTANCE_NAME`_UsingFixedFunction)
        `$RegSizeReplacementString` counterUdb;
        `$RegSizeReplacementString` captureValue;
    #endif     
}`$INSTANCE_NAME`_backupStruct;


/*************************************** 
*       Function Prototypes 
***************************************/

void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;

void    `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptMode) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`;
uint8   `$INSTANCE_NAME`_GetInterruptSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSource")`;

uint8   `$INSTANCE_NAME`_ReadStatusRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatusRegister")`;

#if(!`$INSTANCE_NAME`_ControlRegRemoved)
    uint8   `$INSTANCE_NAME`_ReadControlRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadControlRegister")`;
    void    `$INSTANCE_NAME`_WriteControlRegister(uint8 control) \
        `=ReentrantKeil($INSTANCE_NAME . "_WriteControlRegister")`;
#endif

`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`;
void    `$INSTANCE_NAME`_WritePeriod(`$RegSizeReplacementString` period) \
    `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`;
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`;
void    `$INSTANCE_NAME`_WriteCounter(`$RegSizeReplacementString` counter) \
    `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`;
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCapture(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCapture")`;
void    `$INSTANCE_NAME`_SoftwareCapture(void) `=ReentrantKeil($INSTANCE_NAME . "_SoftwareCapture")`;


#if(!`$INSTANCE_NAME`_UsingFixedFunction) /* UDB Prototypes */
    #if (`$INSTANCE_NAME`_SoftwareCaptureMode)
        void    `$INSTANCE_NAME`_SetCaptureMode(uint8 captureMode) `=ReentrantKeil($INSTANCE_NAME . "_SetCaptureMode")`;
    #endif

    #if (`$INSTANCE_NAME`_SoftwareTriggerMode)
        void    `$INSTANCE_NAME`_SetTriggerMode(uint8 triggerMode) `=ReentrantKeil($INSTANCE_NAME . "_SetTriggerMode")`;
    #endif
    #if (`$INSTANCE_NAME`_EnableTriggerMode)
        void    `$INSTANCE_NAME`_EnableTrigger(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableTrigger")`;
        void    `$INSTANCE_NAME`_DisableTrigger(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableTrigger")`;
    #endif

    #if(`$INSTANCE_NAME`_InterruptOnCaptureCount)
        #if(!`$INSTANCE_NAME`_ControlRegRemoved)
            void    `$INSTANCE_NAME`_SetInterruptCount(uint8 interruptCount) \
                `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptCount")`;
        #endif
    #endif

    #if (`$INSTANCE_NAME`_UsingHWCaptureCounter)
        void    `$INSTANCE_NAME`_SetCaptureCount(uint8 captureCount) \
            `=ReentrantKeil($INSTANCE_NAME . "_SetCaptureCount")`;
        uint8   `$INSTANCE_NAME`_ReadCaptureCount(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCaptureCount")`;
    #endif

    void `$INSTANCE_NAME`_ClearFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void `$INSTANCE_NAME`_Init(void)          `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)        `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void)        `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
`#cy_declare_enum B_Timer__CaptureModes`

/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define `$INSTANCE_NAME`__B_TIMER__TM_NONE 0x00u
#define `$INSTANCE_NAME`__B_TIMER__TM_RISINGEDGE 0x04u
#define `$INSTANCE_NAME`__B_TIMER__TM_FALLINGEDGE 0x08u
#define `$INSTANCE_NAME`__B_TIMER__TM_EITHEREDGE 0x0Cu
#define `$INSTANCE_NAME`__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_INIT_PERIOD             `$Period`u
#define `$INSTANCE_NAME`_INIT_CAPTURE_MODE       (`$CaptureMode`u << `$INSTANCE_NAME`_CTRL_CAP_MODE_SHIFT)
#define `$INSTANCE_NAME`_INIT_TRIGGER_MODE       (`$TriggerMode`u << `$INSTANCE_NAME`_CTRL_TRIG_MODE_SHIFT)
#if (`$INSTANCE_NAME`_UsingFixedFunction)
    #define `$INSTANCE_NAME`_INIT_INTERRUPT_MODE ((`$IntOnTC`u << `$INSTANCE_NAME`_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (`$IntOnCapture` << `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define `$INSTANCE_NAME`_INIT_INTERRUPT_MODE ((`$IntOnTC`u << `$INSTANCE_NAME`_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (`$IntOnCapture` << `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                  (`$IntOnFIFOFull` << `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif
#define `$INSTANCE_NAME`_INIT_CAPTURE_COUNT      (`$CaptureCount`u)
#define `$INSTANCE_NAME`_INIT_INT_CAPTURE_COUNT  ((`$NumberOfCaptures`u - 1) << `$INSTANCE_NAME`_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (`$INSTANCE_NAME`_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */

    
    /***************************************
    *    Fixed Function Registers 
    ***************************************/
    
    #define `$INSTANCE_NAME`_STATUS         (*(reg8 *) `$INSTANCE_NAME`_TimerHW__SR0 )
    #define `$INSTANCE_NAME`_STATUS_MASK    (*(reg8 *) `$INSTANCE_NAME`_TimerHW__SR0 ) /* In Fixed Function Block Status and Mask are the same register */
    #define `$INSTANCE_NAME`_CONTROL        (*(reg8 *) `$INSTANCE_NAME`_TimerHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL2       (*(reg8 *) `$INSTANCE_NAME`_TimerHW__CFG1)
    #define `$INSTANCE_NAME`_CONTROL2_PTR   ( (reg8 *) `$INSTANCE_NAME`_TimerHW__CFG1)    
    #if (`$INSTANCE_NAME`_PSOC3_ES3 || `$INSTANCE_NAME`_PSOC5_ES2)
        #define `$INSTANCE_NAME`_RT1            (*(reg8 *) `$INSTANCE_NAME`_TimerHW__RT1)
        #define `$INSTANCE_NAME`_RT1_PTR        ( (reg8 *) `$INSTANCE_NAME`_TimerHW__RT1)
        #define `$INSTANCE_NAME`_CONTROL3       (*(reg8 *) `$INSTANCE_NAME`_TimerHW__CFG2)
        #define `$INSTANCE_NAME`_CONTROL3_PTR   ( (reg8 *) `$INSTANCE_NAME`_TimerHW__CFG2)
    #endif
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE  (*(reg8 *) `$INSTANCE_NAME`_TimerHW__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE  (*(reg8 *) `$INSTANCE_NAME`_TimerHW__PM_STBY_CFG)
    
    #define `$INSTANCE_NAME`_CAPTURE_LSB         (* (reg16 *) `$INSTANCE_NAME`_TimerHW__CAP0 )
    #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR       ((reg16 *) `$INSTANCE_NAME`_TimerHW__CAP0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB          (* (reg16 *) `$INSTANCE_NAME`_TimerHW__PER0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB_PTR        ((reg16 *) `$INSTANCE_NAME`_TimerHW__PER0 )
    #define `$INSTANCE_NAME`_COUNTER_LSB         (* (reg16 *) `$INSTANCE_NAME`_TimerHW__CNT_CMP0 )
    #define `$INSTANCE_NAME`_COUNTER_LSB_PTR       ((reg16 *) `$INSTANCE_NAME`_TimerHW__CNT_CMP0 )
    
    /***************************************
    *    Register Constants
    ***************************************/
    
    /* Fixed Function Block Chosen */
    #define `$INSTANCE_NAME`_BLOCK_EN_MASK                     `$INSTANCE_NAME`_TimerHW__PM_ACT_MSK
    #define `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK                `$INSTANCE_NAME`_TimerHW__PM_STBY_MSK    
    
    /* Control Register Bit Locations */
    #define `$INSTANCE_NAME`_CTRL_INTCNT_SHIFT                  0x00u       /* Interrupt Count - Not valid for Fixed Function Block */
    #define `$INSTANCE_NAME`_CTRL_TRIG_MODE_SHIFT               0x00u       /* Trigger Polarity - Not valid for Fixed Function Block */
    #define `$INSTANCE_NAME`_CTRL_TRIG_EN_SHIFT                 0x00u       /* Trigger Enable - Not valid for Fixed Function Block */
    #define `$INSTANCE_NAME`_CTRL_CAP_MODE_SHIFT                0x00u       /* Capture Polarity - Not valid for Fixed Function Block */ 
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT                  0x00u       /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */

    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE                        (0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    
    /* Control2 Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT                 0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL                      (0x01u << `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT) 
    
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
        /* Use CFG1 Mode bits to set run mode */
        #define `$INSTANCE_NAME`_CTRL_MODE_SHIFT                     0x01u       /* As defined by Verilog Implementation */ 
        #define `$INSTANCE_NAME`_CTRL_MODE_MASK                     (0x07u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT) 
    #endif
    #if (`$INSTANCE_NAME`_PSOC3_ES3 || `$INSTANCE_NAME`_PSOC5_ES2)
        /* Control3 Register Bit Locations */
        #define `$INSTANCE_NAME`_CTRL_RCOD_SHIFT        0x02u
        #define `$INSTANCE_NAME`_RT1_SHIFT              0x04u
        #define `$INSTANCE_NAME`_CTRL_ENBL_SHIFT        0x00u
        #define `$INSTANCE_NAME`_CTRL_MODE_SHIFT        0x00u 
        
        /* Control3 Register Bit Masks */
        #define `$INSTANCE_NAME`_CTRL_RCOD_MASK  (0x03u << `$INSTANCE_NAME`_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define `$INSTANCE_NAME`_RT1_MASK        (0x03u << `$INSTANCE_NAME`_RT1_SHIFT)  /* Sync TC and CMP bit masks */
        #define `$INSTANCE_NAME`_CTRL_ENBL_MASK  (0x80u << `$INSTANCE_NAME`_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define `$INSTANCE_NAME`_CTRL_MODE_MASK  (0x03u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT) /* Run mode bit mask */
        
        #define `$INSTANCE_NAME`_CTRL_RCOD       (0x03u << `$INSTANCE_NAME`_CTRL_RCOD_SHIFT)
        #define `$INSTANCE_NAME`_SYNC            (0x03u << `$INSTANCE_NAME`_RT1_SHIFT)
        #define `$INSTANCE_NAME`_CTRL_ENBL       (0x80u << `$INSTANCE_NAME`_CTRL_ENBL_SHIFT) 
    #endif
    
    #define `$INSTANCE_NAME`_CTRL_MODE_PULSEWIDTH               (0x01u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT) 
    #define `$INSTANCE_NAME`_CTRL_MODE_PERIOD                   (0x02u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT) 
    #define `$INSTANCE_NAME`_CTRL_MODE_CONTINUOUS               (0x00u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT) 
    
    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT                    0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT               0x06u  /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define `$INSTANCE_NAME`_STATUS_TC_INT_MASK_SHIFT           (`$INSTANCE_NAME`_STATUS_TC_SHIFT - 4)      /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK_SHIFT      (`$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT - 4) /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */ 
    
    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_TC                          (0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CAPTURE                     (0x01u << `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_TC_INT_MASK                 (0x01u << `$INSTANCE_NAME`_STATUS_TC_INT_MASK_SHIFT)      /* Interrupt Enable Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK            (0x01u << `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK_SHIFT) /* Interrupt Enable Bit-Mask */ 
    
#else   /* UDB Registers and Register Constants */

    
    /***************************************
    *           UDB Registers 
    ***************************************/
    
    #define `$INSTANCE_NAME`_STATUS              (* (reg8 *) `$INSTANCE_NAME`_TimerUDB_`$RstStatusReplacementString`_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_MASK         (* (reg8 *) `$INSTANCE_NAME`_TimerUDB_`$RstStatusReplacementString`_stsreg__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_AUX_CTRL     (* (reg8 *) `$INSTANCE_NAME`_TimerUDB_`$RstStatusReplacementString`_stsreg__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_CONTROL             (* (reg8 *) `$INSTANCE_NAME`_TimerUDB_sCTRLReg_`$CtlModeReplacementString`_ctrlreg__CONTROL_REG )
    
    #define `$INSTANCE_NAME`_CAPTURE_LSB         (* (`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__F0_REG )
    #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR       ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__F0_REG )
    #define `$INSTANCE_NAME`_PERIOD_LSB          (* (`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__D0_REG )
    #define `$INSTANCE_NAME`_PERIOD_LSB_PTR        ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__D0_REG )
    #define `$INSTANCE_NAME`_COUNTER_LSB         (* (`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__A0_REG )
    #define `$INSTANCE_NAME`_COUNTER_LSB_PTR       ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_TimerUDB_`$VerilogSectionReplacementString`_timerdp_u0__A0_REG )

    #if (`$INSTANCE_NAME`_UsingHWCaptureCounter)
        #define `$INSTANCE_NAME`_CAP_COUNT              (*(reg8 *) `$INSTANCE_NAME`_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define `$INSTANCE_NAME`_CAP_COUNT_PTR          ( (reg8 *) `$INSTANCE_NAME`_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define `$INSTANCE_NAME`_CAPTURE_COUNT_CTRL     (*(reg8 *) `$INSTANCE_NAME`_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define `$INSTANCE_NAME`_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) `$INSTANCE_NAME`_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif


    /***************************************
    *       Register Constants
    ***************************************/
    
    /* Control Register Bit Locations */
    #define `$INSTANCE_NAME`_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */
    
    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_INTCNT_MASK               (0x03u << `$INSTANCE_NAME`_CTRL_INTCNT_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_TRIG_MODE_MASK            (0x03u << `$INSTANCE_NAME`_CTRL_TRIG_MODE_SHIFT)  
    #define `$INSTANCE_NAME`_CTRL_TRIG_EN                   (0x01u << `$INSTANCE_NAME`_CTRL_TRIG_EN_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CAP_MODE_MASK             (0x03u << `$INSTANCE_NAME`_CTRL_CAP_MODE_SHIFT)   
    #define `$INSTANCE_NAME`_CTRL_ENABLE                    (0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    
    /* Bit Counter (7-bit) Control Register Bit Definitions */
    #define `$INSTANCE_NAME`_CNTR_ENABLE                    0x20u   /* As defined by the Register map for the AUX Control Register */
    
    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_TC_INT_MASK_SHIFT       `$INSTANCE_NAME`_STATUS_TC_SHIFT                
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK_SHIFT  `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_MASK_SHIFT `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_TC                      (0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)             /* Sticky TC Event Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE                 (0x01u << `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT)        /* Sticky Capture Event Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_TC_INT_MASK             (0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)             /* Interrupt Enable Bit-Mask */            
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_MASK        (0x01u << `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT)        /* Interrupt Enable Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL                (0x01u << `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT)       /* NOT-Sticky FIFO Full Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP                (0x01u << `$INSTANCE_NAME`_STATUS_FIFONEMP_SHIFT)       /* NOT-Sticky FIFO Not Empty Bit-Mask */ 
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_MASK       (0x01u << `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT)       /* Interrupt Enable Bit-Mask */ 
    
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */
    
#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v1_50_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
