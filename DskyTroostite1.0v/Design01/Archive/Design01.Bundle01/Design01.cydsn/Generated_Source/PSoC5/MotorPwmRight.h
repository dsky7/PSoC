/*******************************************************************************
* File Name: MotorPwmRight.h  
* Version 3.0
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_MotorPwmRight_H)
#define CY_PWM_MotorPwmRight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorPwmRight_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MotorPwmRight_Resolution 8u
#define MotorPwmRight_UsingFixedFunction 0u
#define MotorPwmRight_DeadBandMode 0u
#define MotorPwmRight_KillModeMinTime 0u
#define MotorPwmRight_KillMode 0u
#define MotorPwmRight_PWMMode 1u
#define MotorPwmRight_PWMModeIsCenterAligned 0u
#define MotorPwmRight_DeadBandUsed 0u
#define MotorPwmRight_DeadBand2_4 0u

#if !defined(MotorPwmRight_PWMUDB_genblk8_stsreg__REMOVED)
    #define MotorPwmRight_UseStatus 1u
#else
    #define MotorPwmRight_UseStatus 0u
#endif /* !defined(MotorPwmRight_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MotorPwmRight_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MotorPwmRight_UseControl 1u
#else
    #define MotorPwmRight_UseControl 0u
#endif /* !defined(MotorPwmRight_PWMUDB_genblk1_ctrlreg__REMOVED) */
#define MotorPwmRight_UseOneCompareMode 0u
#define MotorPwmRight_MinimumKillTime 1u
#define MotorPwmRight_EnableMode 0u

#define MotorPwmRight_CompareMode1SW 0u
#define MotorPwmRight_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MotorPwmRight__B_PWM__DISABLED 0
#define MotorPwmRight__B_PWM__ASYNCHRONOUS 1
#define MotorPwmRight__B_PWM__SINGLECYCLE 2
#define MotorPwmRight__B_PWM__LATCHED 3
#define MotorPwmRight__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MotorPwmRight__B_PWM__DBMDISABLED 0
#define MotorPwmRight__B_PWM__DBM_2_4_CLOCKS 1
#define MotorPwmRight__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MotorPwmRight__B_PWM__ONE_OUTPUT 0
#define MotorPwmRight__B_PWM__TWO_OUTPUTS 1
#define MotorPwmRight__B_PWM__DUAL_EDGE 2
#define MotorPwmRight__B_PWM__CENTER_ALIGN 3
#define MotorPwmRight__B_PWM__DITHER 5
#define MotorPwmRight__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MotorPwmRight__B_PWM__LESS_THAN 1
#define MotorPwmRight__B_PWM__LESS_THAN_OR_EQUAL 2
#define MotorPwmRight__B_PWM__GREATER_THAN 3
#define MotorPwmRight__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MotorPwmRight__B_PWM__EQUAL 0
#define MotorPwmRight__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!MotorPwmRight_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!MotorPwmRight_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!MotorPwmRight_PWMModeIsCenterAligned) */
        #if (MotorPwmRight_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MotorPwmRight_UseStatus) */
        
        /* Backup for Deadband parameters */
        #if(MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_256_CLOCKS || \
            MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */
        
        /* Backup Kill Mode Counter*/
        #if(MotorPwmRight_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MotorPwmRight_KillModeMinTime) */
       
        /* Backup control register */
        #if(MotorPwmRight_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MotorPwmRight_UseControl) */
        
    #endif /* (!MotorPwmRight_UsingFixedFunction) */
   
}MotorPwmRight_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    MotorPwmRight_Start(void) ;
void    MotorPwmRight_Stop(void) ;

#if (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction)
    void  MotorPwmRight_SetInterruptMode(uint8 interruptMode) ;
    uint8 MotorPwmRight_ReadStatusRegister(void) ;
#endif /* (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction) */

#define MotorPwmRight_GetInterruptSource() MotorPwmRight_ReadStatusRegister()

#if (MotorPwmRight_UseControl)
    uint8 MotorPwmRight_ReadControlRegister(void) ; 
    void  MotorPwmRight_WriteControlRegister(uint8 control) ;
#endif /* (MotorPwmRight_UseControl) */

#if (MotorPwmRight_UseOneCompareMode)
   #if (MotorPwmRight_CompareMode1SW)
       void    MotorPwmRight_SetCompareMode(uint8 comparemode) ;
   #endif /* (MotorPwmRight_CompareMode1SW) */
#else
    #if (MotorPwmRight_CompareMode1SW)
        void    MotorPwmRight_SetCompareMode1(uint8 comparemode) ;
    #endif /* (MotorPwmRight_CompareMode1SW) */
    #if (MotorPwmRight_CompareMode2SW)
        void    MotorPwmRight_SetCompareMode2(uint8 comparemode) ;
    #endif /* (MotorPwmRight_CompareMode2SW) */
#endif /* (MotorPwmRight_UseOneCompareMode) */

#if (!MotorPwmRight_UsingFixedFunction)
    uint8   MotorPwmRight_ReadCounter(void) ;
    uint8 MotorPwmRight_ReadCapture(void) ;
    
	#if (MotorPwmRight_UseStatus)
	        void MotorPwmRight_ClearFIFO(void) ;
	#endif /* (MotorPwmRight_UseStatus) */

    void    MotorPwmRight_WriteCounter(uint8 counter) ;
#endif /* (!MotorPwmRight_UsingFixedFunction) */

void    MotorPwmRight_WritePeriod(uint8 period) ;
uint8 MotorPwmRight_ReadPeriod(void) ;

#if (MotorPwmRight_UseOneCompareMode)
    void    MotorPwmRight_WriteCompare(uint8 compare) ;
    uint8 MotorPwmRight_ReadCompare(void) ; 
#else
    void    MotorPwmRight_WriteCompare1(uint8 compare) ;
    uint8 MotorPwmRight_ReadCompare1(void) ; 
    void    MotorPwmRight_WriteCompare2(uint8 compare) ;
    uint8 MotorPwmRight_ReadCompare2(void) ; 
#endif /* (MotorPwmRight_UseOneCompareMode) */


#if (MotorPwmRight_DeadBandUsed)
    void    MotorPwmRight_WriteDeadTime(uint8 deadtime) ;
    uint8   MotorPwmRight_ReadDeadTime(void) ;
#endif /* (MotorPwmRight_DeadBandUsed) */

#if ( MotorPwmRight_KillModeMinTime)
    void MotorPwmRight_WriteKillTime(uint8 killtime) ;
    uint8 MotorPwmRight_ReadKillTime(void) ; 
#endif /* ( MotorPwmRight_KillModeMinTime) */

void MotorPwmRight_Init(void) ;
void MotorPwmRight_Enable(void) ;
void MotorPwmRight_Sleep(void) ;
void MotorPwmRight_Wakeup(void) ;
void MotorPwmRight_SaveConfig(void) ;
void MotorPwmRight_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MotorPwmRight_INIT_PERIOD_VALUE        255u
#define MotorPwmRight_INIT_COMPARE_VALUE1      0u
#define MotorPwmRight_INIT_COMPARE_VALUE2      0u
#define MotorPwmRight_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << MotorPwmRight_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << MotorPwmRight_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << MotorPwmRight_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << MotorPwmRight_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MotorPwmRight_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << MotorPwmRight_CTRL_CMPMODE2_SHIFT)
#define MotorPwmRight_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << MotorPwmRight_CTRL_CMPMODE1_SHIFT)
#define MotorPwmRight_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (MotorPwmRight_UsingFixedFunction)
   #define MotorPwmRight_PERIOD_LSB          (*(reg16 *) MotorPwmRight_PWMHW__PER0)
   #define MotorPwmRight_PERIOD_LSB_PTR      ( (reg16 *) MotorPwmRight_PWMHW__PER0)
   #define MotorPwmRight_COMPARE1_LSB        (*(reg16 *) MotorPwmRight_PWMHW__CNT_CMP0)
   #define MotorPwmRight_COMPARE1_LSB_PTR    ( (reg16 *) MotorPwmRight_PWMHW__CNT_CMP0)
   #define MotorPwmRight_COMPARE2_LSB        0x00u
   #define MotorPwmRight_COMPARE2_LSB_PTR    0x00u
   #define MotorPwmRight_COUNTER_LSB         (*(reg16 *) MotorPwmRight_PWMHW__CNT_CMP0)
   #define MotorPwmRight_COUNTER_LSB_PTR     ( (reg16 *) MotorPwmRight_PWMHW__CNT_CMP0)
   #define MotorPwmRight_CAPTURE_LSB         (*(reg16 *) MotorPwmRight_PWMHW__CAP0)
   #define MotorPwmRight_CAPTURE_LSB_PTR     ( (reg16 *) MotorPwmRight_PWMHW__CAP0)
   #define MotorPwmRight_RT1                 (*(reg8 *)  MotorPwmRight_PWMHW__RT1)
   #define MotorPwmRight_RT1_PTR             ( (reg8 *)  MotorPwmRight_PWMHW__RT1)
      
#else
   #if (MotorPwmRight_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(MotorPwmRight_PWMModeIsCenterAligned)
	       #define MotorPwmRight_PERIOD_LSB      (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
	       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #else
	       #define MotorPwmRight_PERIOD_LSB      (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F0_REG)
	       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F0_REG)
	   #endif /* (MotorPwmRight_PWMModeIsCenterAligned) */
	   
	   #define MotorPwmRight_COMPARE1_LSB    (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define MotorPwmRight_COMPARE1_LSB_PTR ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define MotorPwmRight_COMPARE2_LSB    (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define MotorPwmRight_COMPARE2_LSB_PTR ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define MotorPwmRight_COUNTERCAP_LSB   (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define MotorPwmRight_COUNTERCAP_LSB_PTR ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define MotorPwmRight_COUNTER_LSB     (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define MotorPwmRight_COUNTER_LSB_PTR  ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define MotorPwmRight_CAPTURE_LSB     (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F1_REG)
	   #define MotorPwmRight_CAPTURE_LSB_PTR  ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(MotorPwmRight_PWMModeIsCenterAligned)
		       #define MotorPwmRight_PERIOD_LSB      (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
		       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #else
		       #define MotorPwmRight_PERIOD_LSB      (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F0_REG)
		       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F0_REG)
		    #endif /* (MotorPwmRight_PWMModeIsCenterAligned) */
		   
		    #define MotorPwmRight_COMPARE1_LSB    (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define MotorPwmRight_COMPARE1_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define MotorPwmRight_COMPARE2_LSB    (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define MotorPwmRight_COMPARE2_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define MotorPwmRight_COUNTERCAP_LSB   (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define MotorPwmRight_COUNTERCAP_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define MotorPwmRight_COUNTER_LSB     (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define MotorPwmRight_COUNTER_LSB_PTR  ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define MotorPwmRight_CAPTURE_LSB     (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F1_REG)
		    #define MotorPwmRight_CAPTURE_LSB_PTR  ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__F1_REG)
		#else
			#if(MotorPwmRight_PWMModeIsCenterAligned)
		       #define MotorPwmRight_PERIOD_LSB      (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define MotorPwmRight_PERIOD_LSB      (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		       #define MotorPwmRight_PERIOD_LSB_PTR   ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (MotorPwmRight_PWMModeIsCenterAligned) */
		   
		    #define MotorPwmRight_COMPARE1_LSB    (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define MotorPwmRight_COMPARE1_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define MotorPwmRight_COMPARE2_LSB    (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define MotorPwmRight_COMPARE2_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define MotorPwmRight_COUNTERCAP_LSB   (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define MotorPwmRight_COUNTERCAP_LSB_PTR ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define MotorPwmRight_COUNTER_LSB     (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define MotorPwmRight_COUNTER_LSB_PTR  ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define MotorPwmRight_CAPTURE_LSB     (*(reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		    #define MotorPwmRight_CAPTURE_LSB_PTR  ((reg16 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define MotorPwmRight_AUX_CONTROLDP1    (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define MotorPwmRight_AUX_CONTROLDP1_PTR  ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MotorPwmRight_Resolution == 8) */
   
   #define MotorPwmRight_AUX_CONTROLDP0      (*(reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define MotorPwmRight_AUX_CONTROLDP0_PTR  ((reg8 *) MotorPwmRight_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MotorPwmRight_UsingFixedFunction) */
   
#if(MotorPwmRight_KillModeMinTime )
    #define MotorPwmRight_KILLMODEMINTIME      (*(reg8 *) MotorPwmRight_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MotorPwmRight_KILLMODEMINTIME_PTR   ((reg8 *) MotorPwmRight_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MotorPwmRight_KillModeMinTime ) */

#if(MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_256_CLOCKS)
    #define MotorPwmRight_DEADBAND_COUNT      (*(reg8 *) MotorPwmRight_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPwmRight_DEADBAND_COUNT_PTR  ((reg8 *) MotorPwmRight_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPwmRight_DEADBAND_LSB_PTR    ((reg8 *) MotorPwmRight_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MotorPwmRight_DEADBAND_LSB        (*(reg8 *) MotorPwmRight_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MotorPwmRight_UsingFixedFunction)
        #define MotorPwmRight_DEADBAND_COUNT        (*(reg8 *) MotorPwmRight_PWMHW__CFG0) 
        #define MotorPwmRight_DEADBAND_COUNT_PTR     ((reg8 *) MotorPwmRight_PWMHW__CFG0)
        #define MotorPwmRight_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPwmRight_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MotorPwmRight_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MotorPwmRight_DEADBAND_COUNT        (*(reg8 *) MotorPwmRight_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPwmRight_DEADBAND_COUNT_PTR     ((reg8 *) MotorPwmRight_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPwmRight_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPwmRight_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define MotorPwmRight_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (MotorPwmRight_UsingFixedFunction) */
#endif /* (MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_256_CLOCKS) */



#if (MotorPwmRight_UsingFixedFunction)
    #define MotorPwmRight_STATUS                (*(reg8 *) MotorPwmRight_PWMHW__SR0)
    #define MotorPwmRight_STATUS_PTR            ((reg8 *) MotorPwmRight_PWMHW__SR0)
    #define MotorPwmRight_STATUS_MASK           (*(reg8 *) MotorPwmRight_PWMHW__SR0)
    #define MotorPwmRight_STATUS_MASK_PTR       ((reg8 *) MotorPwmRight_PWMHW__SR0)
    #define MotorPwmRight_CONTROL               (*(reg8 *) MotorPwmRight_PWMHW__CFG0)
    #define MotorPwmRight_CONTROL_PTR           ((reg8 *) MotorPwmRight_PWMHW__CFG0)    
    #define MotorPwmRight_CONTROL2              (*(reg8 *) MotorPwmRight_PWMHW__CFG1)    
    #define MotorPwmRight_CONTROL3              (*(reg8 *) MotorPwmRight_PWMHW__CFG2)
    #define MotorPwmRight_GLOBAL_ENABLE         (*(reg8 *) MotorPwmRight_PWMHW__PM_ACT_CFG)
    #define MotorPwmRight_GLOBAL_ENABLE_PTR       ( (reg8 *) MotorPwmRight_PWMHW__PM_ACT_CFG)
    #define MotorPwmRight_GLOBAL_STBY_ENABLE      (*(reg8 *) MotorPwmRight_PWMHW__PM_STBY_CFG)
    #define MotorPwmRight_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) MotorPwmRight_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MotorPwmRight_BLOCK_EN_MASK          MotorPwmRight_PWMHW__PM_ACT_MSK
    #define MotorPwmRight_BLOCK_STBY_EN_MASK     MotorPwmRight_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define MotorPwmRight_CTRL_ENABLE_SHIFT      0x00u
    
    #define MotorPwmRight_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    
    #define MotorPwmRight_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */

    /* Fixed Function Block Only CFG register bit definitions */
    #define MotorPwmRight_CFG0_MODE              0x02u   /*  Set to compare mode */
    
    /* #define MotorPwmRight_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define MotorPwmRight_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define MotorPwmRight_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPwmRight_CTRL_ENABLE_SHIFT)
    #define MotorPwmRight_CTRL_RESET             (uint8)((uint8)0x01u << MotorPwmRight_CTRL_RESET_SHIFT)
    #define MotorPwmRight_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPwmRight_CTRL_CMPMODE2_SHIFT)
    #define MotorPwmRight_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPwmRight_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorPwmRight_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define MotorPwmRight_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MotorPwmRight_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define MotorPwmRight_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define MotorPwmRight_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define MotorPwmRight_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define MotorPwmRight_STATUS_TC_INT_EN_MASK_SHIFT            (MotorPwmRight_STATUS_TC_SHIFT - 4u)
    #define MotorPwmRight_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define MotorPwmRight_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorPwmRight_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define MotorPwmRight_STATUS_TC              (uint8)((uint8)0x01u << MotorPwmRight_STATUS_TC_SHIFT)
    #define MotorPwmRight_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPwmRight_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks */
    #define MotorPwmRight_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MotorPwmRight_STATUS_TC >> 4u)
    #define MotorPwmRight_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MotorPwmRight_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants */
    #define MotorPwmRight_RT1_SHIFT             0x04u
    #define MotorPwmRight_RT1_MASK              (uint8)((uint8)0x03u << MotorPwmRight_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define MotorPwmRight_SYNC                  (uint8)((uint8)0x03u << MotorPwmRight_RT1_SHIFT)
    #define MotorPwmRight_SYNCDSI_SHIFT         0x00u
    #define MotorPwmRight_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MotorPwmRight_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define MotorPwmRight_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MotorPwmRight_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define MotorPwmRight_STATUS                (*(reg8 *) MotorPwmRight_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPwmRight_STATUS_PTR            ((reg8 *) MotorPwmRight_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPwmRight_STATUS_MASK           (*(reg8 *) MotorPwmRight_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPwmRight_STATUS_MASK_PTR       ((reg8 *) MotorPwmRight_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPwmRight_STATUS_AUX_CTRL       (*(reg8 *) MotorPwmRight_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MotorPwmRight_CONTROL               (*(reg8 *) MotorPwmRight_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MotorPwmRight_CONTROL_PTR           ((reg8 *) MotorPwmRight_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define MotorPwmRight_CTRL_ENABLE_SHIFT      0x07u
    #define MotorPwmRight_CTRL_RESET_SHIFT       0x06u
    #define MotorPwmRight_CTRL_CMPMODE2_SHIFT    0x03u
    #define MotorPwmRight_CTRL_CMPMODE1_SHIFT    0x00u
    #define MotorPwmRight_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define MotorPwmRight_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPwmRight_CTRL_ENABLE_SHIFT)
    #define MotorPwmRight_CTRL_RESET             (uint8)((uint8)0x01u << MotorPwmRight_CTRL_RESET_SHIFT)
    #define MotorPwmRight_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPwmRight_CTRL_CMPMODE2_SHIFT)
    #define MotorPwmRight_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPwmRight_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define MotorPwmRight_STATUS_KILL_SHIFT          0x05u
    #define MotorPwmRight_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define MotorPwmRight_STATUS_FIFOFULL_SHIFT      0x03u  
    #define MotorPwmRight_STATUS_TC_SHIFT            0x02u
    #define MotorPwmRight_STATUS_CMP2_SHIFT          0x01u
    #define MotorPwmRight_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MotorPwmRight_STATUS_KILL_INT_EN_MASK_SHIFT          MotorPwmRight_STATUS_KILL_SHIFT          
    #define MotorPwmRight_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    MotorPwmRight_STATUS_FIFONEMPTY_SHIFT    
    #define MotorPwmRight_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      MotorPwmRight_STATUS_FIFOFULL_SHIFT        
    #define MotorPwmRight_STATUS_TC_INT_EN_MASK_SHIFT            MotorPwmRight_STATUS_TC_SHIFT            
    #define MotorPwmRight_STATUS_CMP2_INT_EN_MASK_SHIFT          MotorPwmRight_STATUS_CMP2_SHIFT          
    #define MotorPwmRight_STATUS_CMP1_INT_EN_MASK_SHIFT          MotorPwmRight_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define MotorPwmRight_STATUS_KILL            (uint8)((uint8)0x00u << MotorPwmRight_STATUS_KILL_SHIFT )
    #define MotorPwmRight_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MotorPwmRight_STATUS_FIFOFULL_SHIFT)
    #define MotorPwmRight_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MotorPwmRight_STATUS_FIFONEMPTY_SHIFT)
    #define MotorPwmRight_STATUS_TC              (uint8)((uint8)0x01u << MotorPwmRight_STATUS_TC_SHIFT)
    #define MotorPwmRight_STATUS_CMP2            (uint8)((uint8)0x01u << MotorPwmRight_STATUS_CMP2_SHIFT) 
    #define MotorPwmRight_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPwmRight_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MotorPwmRight_STATUS_KILL_INT_EN_MASK            MotorPwmRight_STATUS_KILL
    #define MotorPwmRight_STATUS_FIFOFULL_INT_EN_MASK        MotorPwmRight_STATUS_FIFOFULL
    #define MotorPwmRight_STATUS_FIFONEMPTY_INT_EN_MASK      MotorPwmRight_STATUS_FIFONEMPTY
    #define MotorPwmRight_STATUS_TC_INT_EN_MASK              MotorPwmRight_STATUS_TC
    #define MotorPwmRight_STATUS_CMP2_INT_EN_MASK            MotorPwmRight_STATUS_CMP2
    #define MotorPwmRight_STATUS_CMP1_INT_EN_MASK            MotorPwmRight_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define MotorPwmRight_AUX_CTRL_FIFO0_CLR     0x01u
    #define MotorPwmRight_AUX_CTRL_FIFO1_CLR     0x02u
    #define MotorPwmRight_AUX_CTRL_FIFO0_LVL     0x04u
    #define MotorPwmRight_AUX_CTRL_FIFO1_LVL     0x08u
    #define MotorPwmRight_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* MotorPwmRight_UsingFixedFunction */

#endif  /* CY_PWM_MotorPwmRight_H */


/* [] END OF FILE */
