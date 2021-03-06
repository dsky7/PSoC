/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include "cytypes.h"
#include "cyfitter.h"

#if !defined(CY_PWM_`$INSTANCE_NAME`_H)
#define CY_PWM_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_Resolution `$Resolution`
#define `$INSTANCE_NAME`_UsingFixedFunction `$FixedFunctionUsed`
#define `$INSTANCE_NAME`_DeadBandMode `$DeadBand`
#define `$INSTANCE_NAME`_KillModeMinTime `$KillModeMinTime`
#define `$INSTANCE_NAME`_KillMode `$KillMode`
#define `$INSTANCE_NAME`_PWMMode `$PWMMode`
#define `$INSTANCE_NAME`_PWMModeIsCenterAligned `$PWMModeCenterAligned`
#define `$INSTANCE_NAME`_DeadBandUsed `$DeadBandUsed`
#define `$INSTANCE_NAME`_DeadBand2_4 `$DeadBand2_4`
#if !defined(`$INSTANCE_NAME`_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define `$INSTANCE_NAME`_UseStatus `$UseStatus`
#else
    #define `$INSTANCE_NAME`_UseStatus 0
#endif
#if !defined(`$INSTANCE_NAME`_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define `$INSTANCE_NAME`_UseControl `$UseControl`
#else
    #define `$INSTANCE_NAME`_UseControl 0
#endif
#define `$INSTANCE_NAME`_UseOneCompareMode `$OneCompare`
#define `$INSTANCE_NAME`_MinimumKillTime `$MinimumKillTime`
#define `$INSTANCE_NAME`_EnableMode `$EnableMode`

#define `$INSTANCE_NAME`_CompareMode1SW `$CompareType1Software`
#define `$INSTANCE_NAME`_CompareMode2SW `$CompareType2Software`

/* Use Kill Mode Enumerated Types */
`#cy_declare_enum B_PWM__KillModes`

/* Use Dead Band Mode Enumerated Types */
`#cy_declare_enum B_PWM__DeadBandModes`

/* Used PWM Mode Enumerated Types */
`#cy_declare_enum B_PWM__PWMModes`

/* Used PWM Compare Mode Enumerated Types */
`#cy_declare_enum B_PWM__CompareTypes`

/***************************************
 *   Function Prototypes
 **************************************/
void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptMode);
uint8   `$INSTANCE_NAME`_GetInterruptSource(void);
#if (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction)
	uint8   `$INSTANCE_NAME`_ReadStatusRegister(void);
#endif
#if (`$INSTANCE_NAME`_UseControl)
	uint8   `$INSTANCE_NAME`_ReadControlRegister(void);
	void    `$INSTANCE_NAME`_WriteControlRegister(uint8 control);
#endif
#if `$INSTANCE_NAME`_UseOneCompareMode
	#if `$INSTANCE_NAME`_CompareMode1SW
	void    `$INSTANCE_NAME`_SetCompareMode(uint8 comparemode);
	#endif
#else
	#if `$INSTANCE_NAME`_CompareMode1SW
	void    `$INSTANCE_NAME`_SetCompareMode1(uint8 comparemode);
	#endif
	#if `$INSTANCE_NAME`_CompareMode2SW
	void    `$INSTANCE_NAME`_SetCompareMode2(uint8 comparemode);
	#endif
#endif

#if (!`$INSTANCE_NAME`_UsingFixedFunction)
`$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadCounter(void);
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCapture(void);
#if (`$INSTANCE_NAME`_UseStatus)
void `$INSTANCE_NAME`_ClearFIFO(void);
#endif
#endif

void    `$INSTANCE_NAME`_WriteCounter(`$RegSizeReplacementString` counter);
void    `$INSTANCE_NAME`_WritePeriod(`$RegSizeReplacementString` period);
`$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadPeriod(void);
#if `$INSTANCE_NAME`_UseOneCompareMode
    void    `$INSTANCE_NAME`_WriteCompare(`$RegSizeReplacementString` compare);
    `$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadCompare(void);
#else
    void    `$INSTANCE_NAME`_WriteCompare1(`$RegSizeReplacementString` compare);
    `$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadCompare1(void);
    void    `$INSTANCE_NAME`_WriteCompare2(`$RegSizeReplacementString` compare);
    `$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadCompare2(void);
#endif


#if (`$INSTANCE_NAME`_DeadBandUsed)
	void    `$INSTANCE_NAME`_WriteDeadTime(uint8 deadtime);
	uint8   `$INSTANCE_NAME`_ReadDeadTime(void);
#endif

#if ( `$INSTANCE_NAME`_KillModeMinTime)
	void `$INSTANCE_NAME`_WriteKillTime(uint8 killtime);
	uint8 `$INSTANCE_NAME`_ReadKillTime(void);
#endif

/***************************************
 *    Initialization Values
 **************************************/
#define `$INSTANCE_NAME`_INIT_PERIOD_VALUE        `$Period`
#define `$INSTANCE_NAME`_INIT_COMPARE_VALUE1      `$CompareValue1`
#define `$INSTANCE_NAME`_INIT_COMPARE_VALUE2      `$CompareValue2`
#define `$INSTANCE_NAME`_INIT_INTERRUPTS_MODE     ((`$IntOnTC` << `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT) | (`$IntOnCMP2` << `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT) | (`$IntOnCMP1` << `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT ) | (`$IntOnKill` << `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define `$INSTANCE_NAME`_DEFAULT_COMPARE2_MODE    (`$CompareType2` << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
#define `$INSTANCE_NAME`_DEFAULT_COMPARE1_MODE    (`$CompareType1` << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
#define `$INSTANCE_NAME`_INIT_DEAD_TIME           `$DeadTime`

/********************************
 ******     Registers       *****
 ******************************** */

#if (`$INSTANCE_NAME`_UsingFixedFunction)
   #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg16 *) `$INSTANCE_NAME`_PWMHW__PER0)
   #define `$INSTANCE_NAME`_PERIOD_LSB_PTR   ((reg16 *) `$INSTANCE_NAME`_PWMHW__PER0)
   #define `$INSTANCE_NAME`_COMPARE1_LSB    (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR ((reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COMPARE2_LSB     0x00u
   #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR 0x00u
   #define `$INSTANCE_NAME`_COUNTER_LSB     (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COUNTER_LSB_PTR  ((reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_CAPTURE_LSB     (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CAP0)
   #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR  ((reg16 *) `$INSTANCE_NAME`_PWMHW__CAP0)
   
#else
   #if(`$INSTANCE_NAME`_PWMModeIsCenterAligned)
       #define `$INSTANCE_NAME`_PERIOD_LSB      (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
       #define `$INSTANCE_NAME`_PERIOD_LSB_PTR   ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
   #else
       #define `$INSTANCE_NAME`_PERIOD_LSB      (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
       #define `$INSTANCE_NAME`_PERIOD_LSB_PTR   ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
   #endif
   #define `$INSTANCE_NAME`_COMPARE1_LSB    (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
   #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
   #define `$INSTANCE_NAME`_COMPARE2_LSB    (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
   #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
   #define `$INSTANCE_NAME`_COUNTERCAP_LSB   *(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
   #define `$INSTANCE_NAME`_COUNTERCAP_LSB_PTR ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
   #define `$INSTANCE_NAME`_COUNTER_LSB     (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
   #define `$INSTANCE_NAME`_COUNTER_LSB_PTR  ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
   #define `$INSTANCE_NAME`_CAPTURE_LSB     (*(`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)
   #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR  ((`$RegDefReplacementString` *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)
   #define `$INSTANCE_NAME`_AUX_CONTROLDP0      (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__DP_AUX_CTL_REG)
   #define `$INSTANCE_NAME`_AUX_CONTROLDP0_PTR  ((reg8 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__DP_AUX_CTL_REG)
   #if (`$INSTANCE_NAME`_Resolution == 16)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP1    (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u1__DP_AUX_CTL_REG)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP1_PTR  ((reg8 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u1__DP_AUX_CTL_REG)
   #endif
#endif
   
#if(`$INSTANCE_NAME`_KillModeMinTime )
    #define `$INSTANCE_NAME`_KILLMODEMINTIME      (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define `$INSTANCE_NAME`_KILLMODEMINTIME_PTR   ((reg8 *) `$INSTANCE_NAME`_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif

#if(`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_256_CLOCKS)
    #define `$INSTANCE_NAME`_DEADBAND_COUNT        (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *) `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
#elif(`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT        (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG0) 
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *) `$INSTANCE_NAME`_PWMHW__CFG0)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_MASK    (0x03u << `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT) 
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT   0x06u /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */ 
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define `$INSTANCE_NAME`_DEADBAND_COUNT        (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sDB3_dbctrlreg__CONTROL_REG)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *) `$INSTANCE_NAME`_PWMUDB_sDB3_dbctrlreg__CONTROL_REG)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_MASK    (0x03u << `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT) 
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT   0x00u /* As defined by the verilog implementation of the Control Register */
    #endif
#endif



#if (`$INSTANCE_NAME`_UsingFixedFunction)
    #define `$INSTANCE_NAME`_STATUS                (*(reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_STATUS_MASK           (*(reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_CONTROL               (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL2              (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG1)
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE         (*(reg8 *) `$INSTANCE_NAME`_PWMHW__PM_ACT_CFG)

    /***********************************
    *     Constants
    ***********************************/
    /* Fixed Function Block Chosen */
    #define `$INSTANCE_NAME`_BLOCK_EN_MASK          `$INSTANCE_NAME`_PWMHW__PM_ACT_MSK
    /* Control Register definitions */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      0x00u
    #define `$INSTANCE_NAME`_CTRL_RESET_SHIFT       0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT    0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #define `$INSTANCE_NAME`_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define `$INSTANCE_NAME`_CFG0_MODE              0x03u   /* Enable the block to run and set to compare mode */
    #define `$INSTANCE_NAME`_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            (0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_RESET             (0x01u << `$INSTANCE_NAME`_CTRL_RESET_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK     (0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK     (0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT    0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL          (0x01u << `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_SHIFT          0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT    0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT      0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define `$INSTANCE_NAME`_STATUS_CMP2_SHIFT          0x00u   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    /* Status Register Interrupt Enable Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (0x00u)   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (0x00u)   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT            (`$INSTANCE_NAME`_STATUS_TC_SHIFT - 4)
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)   /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT          (`$INSTANCE_NAME`_STATUS_CMP1_SHIFT - 4)
    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_KILL            (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY      (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL        (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_TC              (0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP2            (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_CMP1            (0x01u << `$INSTANCE_NAME`_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks*/
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK            (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK      (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK        (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK              (`$INSTANCE_NAME`_STATUS_TC >> 4)
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK            (0x00u) /* Not available in Fixed Function Block */
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK            (`$INSTANCE_NAME`_STATUS_CMP1 >> 4)

    /* Datapath Auxillary Control Register definitions */
    //#define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    //#define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_CLR       0x02u   /* As defined by Register map */
    //#define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_LVL       0x04u   /* As defined by Register map */
    //#define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_LVL       0x08u   /* As defined by Register map */
    //#define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
#else
    #define `$INSTANCE_NAME`_STATUS                (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sSTSReg_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_MASK           (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sSTSReg_stsreg__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_AUX_CTRL       (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_CONTROL               (*(reg8 *) `$INSTANCE_NAME`_PWMUDB_sCTRLReg_ctrlreg__CONTROL_REG)
    /***********************************
    *     Constants
    ***********************************/
    /* Control Register definitions */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      0x07u
    #define `$INSTANCE_NAME`_CTRL_RESET_SHIFT       0x06u
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT    0x03u
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT    0x00u
	#define `$INSTANCE_NAME`_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            (0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_RESET             (0x01u << `$INSTANCE_NAME`_CTRL_RESET_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK     (0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK     (0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_SHIFT          0x05u
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT      0x03u  
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT            0x02u
    #define `$INSTANCE_NAME`_STATUS_CMP2_SHIFT          0x01u
    #define `$INSTANCE_NAME`_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT          `$INSTANCE_NAME`_STATUS_KILL_SHIFT          
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT    
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT        
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT            `$INSTANCE_NAME`_STATUS_TC_SHIFT            
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT          `$INSTANCE_NAME`_STATUS_CMP2_SHIFT          
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT          `$INSTANCE_NAME`_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_KILL            (0x00u << `$INSTANCE_NAME`_STATUS_KILL_SHIFT )
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL        (0x01u << `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY      (0x01u << `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_TC              (0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP2            (0x01u << `$INSTANCE_NAME`_STATUS_CMP2_SHIFT) 
    #define `$INSTANCE_NAME`_STATUS_CMP1            (0x01u << `$INSTANCE_NAME`_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK            `$INSTANCE_NAME`_STATUS_KILL
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK        `$INSTANCE_NAME`_STATUS_FIFOFULL
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK      `$INSTANCE_NAME`_STATUS_FIFONEMPTY
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK              `$INSTANCE_NAME`_STATUS_TC
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK            `$INSTANCE_NAME`_STATUS_CMP2
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK            `$INSTANCE_NAME`_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR     0x01u
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_CLR     0x02u
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_LVL     0x04u
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_LVL     0x08u
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* `$INSTANCE_NAME`_UsingFixedFunction */

#endif  /* CY_PWM_`$INSTANCE_NAME`_H */
