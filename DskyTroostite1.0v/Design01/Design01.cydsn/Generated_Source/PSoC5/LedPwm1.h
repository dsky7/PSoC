/*******************************************************************************
* File Name: LedPwm1.h  
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

#if !defined(CY_PWM_LedPwm1_H)
#define CY_PWM_LedPwm1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LedPwm1_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define LedPwm1_Resolution 8u
#define LedPwm1_UsingFixedFunction 0u
#define LedPwm1_DeadBandMode 0u
#define LedPwm1_KillModeMinTime 0u
#define LedPwm1_KillMode 0u
#define LedPwm1_PWMMode 1u
#define LedPwm1_PWMModeIsCenterAligned 0u
#define LedPwm1_DeadBandUsed 0u
#define LedPwm1_DeadBand2_4 0u

#if !defined(LedPwm1_PWMUDB_genblk8_stsreg__REMOVED)
    #define LedPwm1_UseStatus 1u
#else
    #define LedPwm1_UseStatus 0u
#endif /* !defined(LedPwm1_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(LedPwm1_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define LedPwm1_UseControl 1u
#else
    #define LedPwm1_UseControl 0u
#endif /* !defined(LedPwm1_PWMUDB_genblk1_ctrlreg__REMOVED) */
#define LedPwm1_UseOneCompareMode 0u
#define LedPwm1_MinimumKillTime 1u
#define LedPwm1_EnableMode 0u

#define LedPwm1_CompareMode1SW 0u
#define LedPwm1_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define LedPwm1__B_PWM__DISABLED 0
#define LedPwm1__B_PWM__ASYNCHRONOUS 1
#define LedPwm1__B_PWM__SINGLECYCLE 2
#define LedPwm1__B_PWM__LATCHED 3
#define LedPwm1__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define LedPwm1__B_PWM__DBMDISABLED 0
#define LedPwm1__B_PWM__DBM_2_4_CLOCKS 1
#define LedPwm1__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define LedPwm1__B_PWM__ONE_OUTPUT 0
#define LedPwm1__B_PWM__TWO_OUTPUTS 1
#define LedPwm1__B_PWM__DUAL_EDGE 2
#define LedPwm1__B_PWM__CENTER_ALIGN 3
#define LedPwm1__B_PWM__DITHER 5
#define LedPwm1__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define LedPwm1__B_PWM__LESS_THAN 1
#define LedPwm1__B_PWM__LESS_THAN_OR_EQUAL 2
#define LedPwm1__B_PWM__GREATER_THAN 3
#define LedPwm1__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define LedPwm1__B_PWM__EQUAL 0
#define LedPwm1__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!LedPwm1_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!LedPwm1_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!LedPwm1_PWMModeIsCenterAligned) */
        #if (LedPwm1_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (LedPwm1_UseStatus) */
        
        /* Backup for Deadband parameters */
        #if(LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_256_CLOCKS || \
            LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */
        
        /* Backup Kill Mode Counter*/
        #if(LedPwm1_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (LedPwm1_KillModeMinTime) */
       
        /* Backup control register */
        #if(LedPwm1_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (LedPwm1_UseControl) */
        
    #endif /* (!LedPwm1_UsingFixedFunction) */
   
}LedPwm1_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    LedPwm1_Start(void) ;
void    LedPwm1_Stop(void) ;

#if (LedPwm1_UseStatus || LedPwm1_UsingFixedFunction)
    void  LedPwm1_SetInterruptMode(uint8 interruptMode) ;
    uint8 LedPwm1_ReadStatusRegister(void) ;
#endif /* (LedPwm1_UseStatus || LedPwm1_UsingFixedFunction) */

#define LedPwm1_GetInterruptSource() LedPwm1_ReadStatusRegister()

#if (LedPwm1_UseControl)
    uint8 LedPwm1_ReadControlRegister(void) ; 
    void  LedPwm1_WriteControlRegister(uint8 control) ;
#endif /* (LedPwm1_UseControl) */

#if (LedPwm1_UseOneCompareMode)
   #if (LedPwm1_CompareMode1SW)
       void    LedPwm1_SetCompareMode(uint8 comparemode) ;
   #endif /* (LedPwm1_CompareMode1SW) */
#else
    #if (LedPwm1_CompareMode1SW)
        void    LedPwm1_SetCompareMode1(uint8 comparemode) ;
    #endif /* (LedPwm1_CompareMode1SW) */
    #if (LedPwm1_CompareMode2SW)
        void    LedPwm1_SetCompareMode2(uint8 comparemode) ;
    #endif /* (LedPwm1_CompareMode2SW) */
#endif /* (LedPwm1_UseOneCompareMode) */

#if (!LedPwm1_UsingFixedFunction)
    uint8   LedPwm1_ReadCounter(void) ;
    uint8 LedPwm1_ReadCapture(void) ;
    
	#if (LedPwm1_UseStatus)
	        void LedPwm1_ClearFIFO(void) ;
	#endif /* (LedPwm1_UseStatus) */

    void    LedPwm1_WriteCounter(uint8 counter) ;
#endif /* (!LedPwm1_UsingFixedFunction) */

void    LedPwm1_WritePeriod(uint8 period) ;
uint8 LedPwm1_ReadPeriod(void) ;

#if (LedPwm1_UseOneCompareMode)
    void    LedPwm1_WriteCompare(uint8 compare) ;
    uint8 LedPwm1_ReadCompare(void) ; 
#else
    void    LedPwm1_WriteCompare1(uint8 compare) ;
    uint8 LedPwm1_ReadCompare1(void) ; 
    void    LedPwm1_WriteCompare2(uint8 compare) ;
    uint8 LedPwm1_ReadCompare2(void) ; 
#endif /* (LedPwm1_UseOneCompareMode) */


#if (LedPwm1_DeadBandUsed)
    void    LedPwm1_WriteDeadTime(uint8 deadtime) ;
    uint8   LedPwm1_ReadDeadTime(void) ;
#endif /* (LedPwm1_DeadBandUsed) */

#if ( LedPwm1_KillModeMinTime)
    void LedPwm1_WriteKillTime(uint8 killtime) ;
    uint8 LedPwm1_ReadKillTime(void) ; 
#endif /* ( LedPwm1_KillModeMinTime) */

void LedPwm1_Init(void) ;
void LedPwm1_Enable(void) ;
void LedPwm1_Sleep(void) ;
void LedPwm1_Wakeup(void) ;
void LedPwm1_SaveConfig(void) ;
void LedPwm1_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define LedPwm1_INIT_PERIOD_VALUE        255u
#define LedPwm1_INIT_COMPARE_VALUE1      127u
#define LedPwm1_INIT_COMPARE_VALUE2      63u
#define LedPwm1_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << LedPwm1_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << LedPwm1_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << LedPwm1_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << LedPwm1_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define LedPwm1_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << LedPwm1_CTRL_CMPMODE2_SHIFT)
#define LedPwm1_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << LedPwm1_CTRL_CMPMODE1_SHIFT)
#define LedPwm1_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (LedPwm1_UsingFixedFunction)
   #define LedPwm1_PERIOD_LSB          (*(reg16 *) LedPwm1_PWMHW__PER0)
   #define LedPwm1_PERIOD_LSB_PTR      ( (reg16 *) LedPwm1_PWMHW__PER0)
   #define LedPwm1_COMPARE1_LSB        (*(reg16 *) LedPwm1_PWMHW__CNT_CMP0)
   #define LedPwm1_COMPARE1_LSB_PTR    ( (reg16 *) LedPwm1_PWMHW__CNT_CMP0)
   #define LedPwm1_COMPARE2_LSB        0x00u
   #define LedPwm1_COMPARE2_LSB_PTR    0x00u
   #define LedPwm1_COUNTER_LSB         (*(reg16 *) LedPwm1_PWMHW__CNT_CMP0)
   #define LedPwm1_COUNTER_LSB_PTR     ( (reg16 *) LedPwm1_PWMHW__CNT_CMP0)
   #define LedPwm1_CAPTURE_LSB         (*(reg16 *) LedPwm1_PWMHW__CAP0)
   #define LedPwm1_CAPTURE_LSB_PTR     ( (reg16 *) LedPwm1_PWMHW__CAP0)
   #define LedPwm1_RT1                 (*(reg8 *)  LedPwm1_PWMHW__RT1)
   #define LedPwm1_RT1_PTR             ( (reg8 *)  LedPwm1_PWMHW__RT1)
      
#else
   #if (LedPwm1_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(LedPwm1_PWMModeIsCenterAligned)
	       #define LedPwm1_PERIOD_LSB      (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
	       #define LedPwm1_PERIOD_LSB_PTR   ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #else
	       #define LedPwm1_PERIOD_LSB      (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F0_REG)
	       #define LedPwm1_PERIOD_LSB_PTR   ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F0_REG)
	   #endif /* (LedPwm1_PWMModeIsCenterAligned) */
	   
	   #define LedPwm1_COMPARE1_LSB    (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define LedPwm1_COMPARE1_LSB_PTR ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define LedPwm1_COMPARE2_LSB    (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define LedPwm1_COMPARE2_LSB_PTR ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define LedPwm1_COUNTERCAP_LSB   (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define LedPwm1_COUNTERCAP_LSB_PTR ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define LedPwm1_COUNTER_LSB     (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define LedPwm1_COUNTER_LSB_PTR  ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define LedPwm1_CAPTURE_LSB     (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F1_REG)
	   #define LedPwm1_CAPTURE_LSB_PTR  ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(LedPwm1_PWMModeIsCenterAligned)
		       #define LedPwm1_PERIOD_LSB      (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
		       #define LedPwm1_PERIOD_LSB_PTR   ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #else
		       #define LedPwm1_PERIOD_LSB      (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F0_REG)
		       #define LedPwm1_PERIOD_LSB_PTR   ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F0_REG)
		    #endif /* (LedPwm1_PWMModeIsCenterAligned) */
		   
		    #define LedPwm1_COMPARE1_LSB    (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define LedPwm1_COMPARE1_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define LedPwm1_COMPARE2_LSB    (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define LedPwm1_COMPARE2_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define LedPwm1_COUNTERCAP_LSB   (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define LedPwm1_COUNTERCAP_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define LedPwm1_COUNTER_LSB     (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define LedPwm1_COUNTER_LSB_PTR  ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define LedPwm1_CAPTURE_LSB     (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F1_REG)
		    #define LedPwm1_CAPTURE_LSB_PTR  ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__F1_REG)
		#else
			#if(LedPwm1_PWMModeIsCenterAligned)
		       #define LedPwm1_PERIOD_LSB      (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		       #define LedPwm1_PERIOD_LSB_PTR   ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define LedPwm1_PERIOD_LSB      (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		       #define LedPwm1_PERIOD_LSB_PTR   ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (LedPwm1_PWMModeIsCenterAligned) */
		   
		    #define LedPwm1_COMPARE1_LSB    (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define LedPwm1_COMPARE1_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define LedPwm1_COMPARE2_LSB    (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define LedPwm1_COMPARE2_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define LedPwm1_COUNTERCAP_LSB   (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define LedPwm1_COUNTERCAP_LSB_PTR ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define LedPwm1_COUNTER_LSB     (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define LedPwm1_COUNTER_LSB_PTR  ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define LedPwm1_CAPTURE_LSB     (*(reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		    #define LedPwm1_CAPTURE_LSB_PTR  ((reg16 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define LedPwm1_AUX_CONTROLDP1    (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define LedPwm1_AUX_CONTROLDP1_PTR  ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (LedPwm1_Resolution == 8) */
   
   #define LedPwm1_AUX_CONTROLDP0      (*(reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define LedPwm1_AUX_CONTROLDP0_PTR  ((reg8 *) LedPwm1_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (LedPwm1_UsingFixedFunction) */
   
#if(LedPwm1_KillModeMinTime )
    #define LedPwm1_KILLMODEMINTIME      (*(reg8 *) LedPwm1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define LedPwm1_KILLMODEMINTIME_PTR   ((reg8 *) LedPwm1_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (LedPwm1_KillModeMinTime ) */

#if(LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_256_CLOCKS)
    #define LedPwm1_DEADBAND_COUNT      (*(reg8 *) LedPwm1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LedPwm1_DEADBAND_COUNT_PTR  ((reg8 *) LedPwm1_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LedPwm1_DEADBAND_LSB_PTR    ((reg8 *) LedPwm1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define LedPwm1_DEADBAND_LSB        (*(reg8 *) LedPwm1_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (LedPwm1_UsingFixedFunction)
        #define LedPwm1_DEADBAND_COUNT        (*(reg8 *) LedPwm1_PWMHW__CFG0) 
        #define LedPwm1_DEADBAND_COUNT_PTR     ((reg8 *) LedPwm1_PWMHW__CFG0)
        #define LedPwm1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LedPwm1_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define LedPwm1_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define LedPwm1_DEADBAND_COUNT        (*(reg8 *) LedPwm1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LedPwm1_DEADBAND_COUNT_PTR     ((reg8 *) LedPwm1_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LedPwm1_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LedPwm1_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define LedPwm1_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (LedPwm1_UsingFixedFunction) */
#endif /* (LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_256_CLOCKS) */



#if (LedPwm1_UsingFixedFunction)
    #define LedPwm1_STATUS                (*(reg8 *) LedPwm1_PWMHW__SR0)
    #define LedPwm1_STATUS_PTR            ((reg8 *) LedPwm1_PWMHW__SR0)
    #define LedPwm1_STATUS_MASK           (*(reg8 *) LedPwm1_PWMHW__SR0)
    #define LedPwm1_STATUS_MASK_PTR       ((reg8 *) LedPwm1_PWMHW__SR0)
    #define LedPwm1_CONTROL               (*(reg8 *) LedPwm1_PWMHW__CFG0)
    #define LedPwm1_CONTROL_PTR           ((reg8 *) LedPwm1_PWMHW__CFG0)    
    #define LedPwm1_CONTROL2              (*(reg8 *) LedPwm1_PWMHW__CFG1)    
    #define LedPwm1_CONTROL3              (*(reg8 *) LedPwm1_PWMHW__CFG2)
    #define LedPwm1_GLOBAL_ENABLE         (*(reg8 *) LedPwm1_PWMHW__PM_ACT_CFG)
    #define LedPwm1_GLOBAL_ENABLE_PTR       ( (reg8 *) LedPwm1_PWMHW__PM_ACT_CFG)
    #define LedPwm1_GLOBAL_STBY_ENABLE      (*(reg8 *) LedPwm1_PWMHW__PM_STBY_CFG)
    #define LedPwm1_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) LedPwm1_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define LedPwm1_BLOCK_EN_MASK          LedPwm1_PWMHW__PM_ACT_MSK
    #define LedPwm1_BLOCK_STBY_EN_MASK     LedPwm1_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define LedPwm1_CTRL_ENABLE_SHIFT      0x00u
    
    #define LedPwm1_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    
    #define LedPwm1_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */

    /* Fixed Function Block Only CFG register bit definitions */
    #define LedPwm1_CFG0_MODE              0x02u   /*  Set to compare mode */
    
    /* #define LedPwm1_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define LedPwm1_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define LedPwm1_CTRL_ENABLE            (uint8)((uint8)0x01u << LedPwm1_CTRL_ENABLE_SHIFT)
    #define LedPwm1_CTRL_RESET             (uint8)((uint8)0x01u << LedPwm1_CTRL_RESET_SHIFT)
    #define LedPwm1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LedPwm1_CTRL_CMPMODE2_SHIFT)
    #define LedPwm1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LedPwm1_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LedPwm1_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define LedPwm1_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << LedPwm1_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define LedPwm1_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define LedPwm1_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define LedPwm1_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define LedPwm1_STATUS_TC_INT_EN_MASK_SHIFT            (LedPwm1_STATUS_TC_SHIFT - 4u)
    #define LedPwm1_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define LedPwm1_STATUS_CMP1_INT_EN_MASK_SHIFT          (LedPwm1_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define LedPwm1_STATUS_TC              (uint8)((uint8)0x01u << LedPwm1_STATUS_TC_SHIFT)
    #define LedPwm1_STATUS_CMP1            (uint8)((uint8)0x01u << LedPwm1_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks */
    #define LedPwm1_STATUS_TC_INT_EN_MASK              (uint8)((uint8)LedPwm1_STATUS_TC >> 4u)
    #define LedPwm1_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)LedPwm1_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants */
    #define LedPwm1_RT1_SHIFT             0x04u
    #define LedPwm1_RT1_MASK              (uint8)((uint8)0x03u << LedPwm1_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define LedPwm1_SYNC                  (uint8)((uint8)0x03u << LedPwm1_RT1_SHIFT)
    #define LedPwm1_SYNCDSI_SHIFT         0x00u
    #define LedPwm1_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << LedPwm1_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define LedPwm1_SYNCDSI_EN            (uint8)((uint8)0x0Fu << LedPwm1_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define LedPwm1_STATUS                (*(reg8 *) LedPwm1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LedPwm1_STATUS_PTR            ((reg8 *) LedPwm1_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LedPwm1_STATUS_MASK           (*(reg8 *) LedPwm1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LedPwm1_STATUS_MASK_PTR       ((reg8 *) LedPwm1_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LedPwm1_STATUS_AUX_CTRL       (*(reg8 *) LedPwm1_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define LedPwm1_CONTROL               (*(reg8 *) LedPwm1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define LedPwm1_CONTROL_PTR           ((reg8 *) LedPwm1_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define LedPwm1_CTRL_ENABLE_SHIFT      0x07u
    #define LedPwm1_CTRL_RESET_SHIFT       0x06u
    #define LedPwm1_CTRL_CMPMODE2_SHIFT    0x03u
    #define LedPwm1_CTRL_CMPMODE1_SHIFT    0x00u
    #define LedPwm1_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define LedPwm1_CTRL_ENABLE            (uint8)((uint8)0x01u << LedPwm1_CTRL_ENABLE_SHIFT)
    #define LedPwm1_CTRL_RESET             (uint8)((uint8)0x01u << LedPwm1_CTRL_RESET_SHIFT)
    #define LedPwm1_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LedPwm1_CTRL_CMPMODE2_SHIFT)
    #define LedPwm1_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LedPwm1_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define LedPwm1_STATUS_KILL_SHIFT          0x05u
    #define LedPwm1_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define LedPwm1_STATUS_FIFOFULL_SHIFT      0x03u  
    #define LedPwm1_STATUS_TC_SHIFT            0x02u
    #define LedPwm1_STATUS_CMP2_SHIFT          0x01u
    #define LedPwm1_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LedPwm1_STATUS_KILL_INT_EN_MASK_SHIFT          LedPwm1_STATUS_KILL_SHIFT          
    #define LedPwm1_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    LedPwm1_STATUS_FIFONEMPTY_SHIFT    
    #define LedPwm1_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      LedPwm1_STATUS_FIFOFULL_SHIFT        
    #define LedPwm1_STATUS_TC_INT_EN_MASK_SHIFT            LedPwm1_STATUS_TC_SHIFT            
    #define LedPwm1_STATUS_CMP2_INT_EN_MASK_SHIFT          LedPwm1_STATUS_CMP2_SHIFT          
    #define LedPwm1_STATUS_CMP1_INT_EN_MASK_SHIFT          LedPwm1_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define LedPwm1_STATUS_KILL            (uint8)((uint8)0x00u << LedPwm1_STATUS_KILL_SHIFT )
    #define LedPwm1_STATUS_FIFOFULL        (uint8)((uint8)0x01u << LedPwm1_STATUS_FIFOFULL_SHIFT)
    #define LedPwm1_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << LedPwm1_STATUS_FIFONEMPTY_SHIFT)
    #define LedPwm1_STATUS_TC              (uint8)((uint8)0x01u << LedPwm1_STATUS_TC_SHIFT)
    #define LedPwm1_STATUS_CMP2            (uint8)((uint8)0x01u << LedPwm1_STATUS_CMP2_SHIFT) 
    #define LedPwm1_STATUS_CMP1            (uint8)((uint8)0x01u << LedPwm1_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LedPwm1_STATUS_KILL_INT_EN_MASK            LedPwm1_STATUS_KILL
    #define LedPwm1_STATUS_FIFOFULL_INT_EN_MASK        LedPwm1_STATUS_FIFOFULL
    #define LedPwm1_STATUS_FIFONEMPTY_INT_EN_MASK      LedPwm1_STATUS_FIFONEMPTY
    #define LedPwm1_STATUS_TC_INT_EN_MASK              LedPwm1_STATUS_TC
    #define LedPwm1_STATUS_CMP2_INT_EN_MASK            LedPwm1_STATUS_CMP2
    #define LedPwm1_STATUS_CMP1_INT_EN_MASK            LedPwm1_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define LedPwm1_AUX_CTRL_FIFO0_CLR     0x01u
    #define LedPwm1_AUX_CTRL_FIFO1_CLR     0x02u
    #define LedPwm1_AUX_CTRL_FIFO0_LVL     0x04u
    #define LedPwm1_AUX_CTRL_FIFO1_LVL     0x08u
    #define LedPwm1_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* LedPwm1_UsingFixedFunction */

#endif  /* CY_PWM_LedPwm1_H */


/* [] END OF FILE */
