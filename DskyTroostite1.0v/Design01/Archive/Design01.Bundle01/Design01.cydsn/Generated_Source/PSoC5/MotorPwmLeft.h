/*******************************************************************************
* File Name: MotorPwmLeft.h  
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

#if !defined(CY_PWM_MotorPwmLeft_H)
#define CY_PWM_MotorPwmLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorPwmLeft_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MotorPwmLeft_Resolution 8u
#define MotorPwmLeft_UsingFixedFunction 0u
#define MotorPwmLeft_DeadBandMode 0u
#define MotorPwmLeft_KillModeMinTime 0u
#define MotorPwmLeft_KillMode 0u
#define MotorPwmLeft_PWMMode 1u
#define MotorPwmLeft_PWMModeIsCenterAligned 0u
#define MotorPwmLeft_DeadBandUsed 0u
#define MotorPwmLeft_DeadBand2_4 0u

#if !defined(MotorPwmLeft_PWMUDB_genblk8_stsreg__REMOVED)
    #define MotorPwmLeft_UseStatus 1u
#else
    #define MotorPwmLeft_UseStatus 0u
#endif /* !defined(MotorPwmLeft_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MotorPwmLeft_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MotorPwmLeft_UseControl 1u
#else
    #define MotorPwmLeft_UseControl 0u
#endif /* !defined(MotorPwmLeft_PWMUDB_genblk1_ctrlreg__REMOVED) */
#define MotorPwmLeft_UseOneCompareMode 0u
#define MotorPwmLeft_MinimumKillTime 1u
#define MotorPwmLeft_EnableMode 0u

#define MotorPwmLeft_CompareMode1SW 0u
#define MotorPwmLeft_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MotorPwmLeft__B_PWM__DISABLED 0
#define MotorPwmLeft__B_PWM__ASYNCHRONOUS 1
#define MotorPwmLeft__B_PWM__SINGLECYCLE 2
#define MotorPwmLeft__B_PWM__LATCHED 3
#define MotorPwmLeft__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MotorPwmLeft__B_PWM__DBMDISABLED 0
#define MotorPwmLeft__B_PWM__DBM_2_4_CLOCKS 1
#define MotorPwmLeft__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MotorPwmLeft__B_PWM__ONE_OUTPUT 0
#define MotorPwmLeft__B_PWM__TWO_OUTPUTS 1
#define MotorPwmLeft__B_PWM__DUAL_EDGE 2
#define MotorPwmLeft__B_PWM__CENTER_ALIGN 3
#define MotorPwmLeft__B_PWM__DITHER 5
#define MotorPwmLeft__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MotorPwmLeft__B_PWM__LESS_THAN 1
#define MotorPwmLeft__B_PWM__LESS_THAN_OR_EQUAL 2
#define MotorPwmLeft__B_PWM__GREATER_THAN 3
#define MotorPwmLeft__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MotorPwmLeft__B_PWM__EQUAL 0
#define MotorPwmLeft__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!MotorPwmLeft_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!MotorPwmLeft_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!MotorPwmLeft_PWMModeIsCenterAligned) */
        #if (MotorPwmLeft_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MotorPwmLeft_UseStatus) */
        
        /* Backup for Deadband parameters */
        #if(MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_256_CLOCKS || \
            MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */
        
        /* Backup Kill Mode Counter*/
        #if(MotorPwmLeft_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MotorPwmLeft_KillModeMinTime) */
       
        /* Backup control register */
        #if(MotorPwmLeft_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MotorPwmLeft_UseControl) */
        
    #endif /* (!MotorPwmLeft_UsingFixedFunction) */
   
}MotorPwmLeft_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    MotorPwmLeft_Start(void) ;
void    MotorPwmLeft_Stop(void) ;

#if (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction)
    void  MotorPwmLeft_SetInterruptMode(uint8 interruptMode) ;
    uint8 MotorPwmLeft_ReadStatusRegister(void) ;
#endif /* (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction) */

#define MotorPwmLeft_GetInterruptSource() MotorPwmLeft_ReadStatusRegister()

#if (MotorPwmLeft_UseControl)
    uint8 MotorPwmLeft_ReadControlRegister(void) ; 
    void  MotorPwmLeft_WriteControlRegister(uint8 control) ;
#endif /* (MotorPwmLeft_UseControl) */

#if (MotorPwmLeft_UseOneCompareMode)
   #if (MotorPwmLeft_CompareMode1SW)
       void    MotorPwmLeft_SetCompareMode(uint8 comparemode) ;
   #endif /* (MotorPwmLeft_CompareMode1SW) */
#else
    #if (MotorPwmLeft_CompareMode1SW)
        void    MotorPwmLeft_SetCompareMode1(uint8 comparemode) ;
    #endif /* (MotorPwmLeft_CompareMode1SW) */
    #if (MotorPwmLeft_CompareMode2SW)
        void    MotorPwmLeft_SetCompareMode2(uint8 comparemode) ;
    #endif /* (MotorPwmLeft_CompareMode2SW) */
#endif /* (MotorPwmLeft_UseOneCompareMode) */

#if (!MotorPwmLeft_UsingFixedFunction)
    uint8   MotorPwmLeft_ReadCounter(void) ;
    uint8 MotorPwmLeft_ReadCapture(void) ;
    
	#if (MotorPwmLeft_UseStatus)
	        void MotorPwmLeft_ClearFIFO(void) ;
	#endif /* (MotorPwmLeft_UseStatus) */

    void    MotorPwmLeft_WriteCounter(uint8 counter) ;
#endif /* (!MotorPwmLeft_UsingFixedFunction) */

void    MotorPwmLeft_WritePeriod(uint8 period) ;
uint8 MotorPwmLeft_ReadPeriod(void) ;

#if (MotorPwmLeft_UseOneCompareMode)
    void    MotorPwmLeft_WriteCompare(uint8 compare) ;
    uint8 MotorPwmLeft_ReadCompare(void) ; 
#else
    void    MotorPwmLeft_WriteCompare1(uint8 compare) ;
    uint8 MotorPwmLeft_ReadCompare1(void) ; 
    void    MotorPwmLeft_WriteCompare2(uint8 compare) ;
    uint8 MotorPwmLeft_ReadCompare2(void) ; 
#endif /* (MotorPwmLeft_UseOneCompareMode) */


#if (MotorPwmLeft_DeadBandUsed)
    void    MotorPwmLeft_WriteDeadTime(uint8 deadtime) ;
    uint8   MotorPwmLeft_ReadDeadTime(void) ;
#endif /* (MotorPwmLeft_DeadBandUsed) */

#if ( MotorPwmLeft_KillModeMinTime)
    void MotorPwmLeft_WriteKillTime(uint8 killtime) ;
    uint8 MotorPwmLeft_ReadKillTime(void) ; 
#endif /* ( MotorPwmLeft_KillModeMinTime) */

void MotorPwmLeft_Init(void) ;
void MotorPwmLeft_Enable(void) ;
void MotorPwmLeft_Sleep(void) ;
void MotorPwmLeft_Wakeup(void) ;
void MotorPwmLeft_SaveConfig(void) ;
void MotorPwmLeft_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MotorPwmLeft_INIT_PERIOD_VALUE        255u
#define MotorPwmLeft_INIT_COMPARE_VALUE1      0u
#define MotorPwmLeft_INIT_COMPARE_VALUE2      0u
#define MotorPwmLeft_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << MotorPwmLeft_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << MotorPwmLeft_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << MotorPwmLeft_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << MotorPwmLeft_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MotorPwmLeft_DEFAULT_COMPARE2_MODE    (uint8)((uint8)1u << MotorPwmLeft_CTRL_CMPMODE2_SHIFT)
#define MotorPwmLeft_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << MotorPwmLeft_CTRL_CMPMODE1_SHIFT)
#define MotorPwmLeft_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (MotorPwmLeft_UsingFixedFunction)
   #define MotorPwmLeft_PERIOD_LSB          (*(reg16 *) MotorPwmLeft_PWMHW__PER0)
   #define MotorPwmLeft_PERIOD_LSB_PTR      ( (reg16 *) MotorPwmLeft_PWMHW__PER0)
   #define MotorPwmLeft_COMPARE1_LSB        (*(reg16 *) MotorPwmLeft_PWMHW__CNT_CMP0)
   #define MotorPwmLeft_COMPARE1_LSB_PTR    ( (reg16 *) MotorPwmLeft_PWMHW__CNT_CMP0)
   #define MotorPwmLeft_COMPARE2_LSB        0x00u
   #define MotorPwmLeft_COMPARE2_LSB_PTR    0x00u
   #define MotorPwmLeft_COUNTER_LSB         (*(reg16 *) MotorPwmLeft_PWMHW__CNT_CMP0)
   #define MotorPwmLeft_COUNTER_LSB_PTR     ( (reg16 *) MotorPwmLeft_PWMHW__CNT_CMP0)
   #define MotorPwmLeft_CAPTURE_LSB         (*(reg16 *) MotorPwmLeft_PWMHW__CAP0)
   #define MotorPwmLeft_CAPTURE_LSB_PTR     ( (reg16 *) MotorPwmLeft_PWMHW__CAP0)
   #define MotorPwmLeft_RT1                 (*(reg8 *)  MotorPwmLeft_PWMHW__RT1)
   #define MotorPwmLeft_RT1_PTR             ( (reg8 *)  MotorPwmLeft_PWMHW__RT1)
      
#else
   #if (MotorPwmLeft_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(MotorPwmLeft_PWMModeIsCenterAligned)
	       #define MotorPwmLeft_PERIOD_LSB      (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
	       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #else
	       #define MotorPwmLeft_PERIOD_LSB      (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F0_REG)
	       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F0_REG)
	   #endif /* (MotorPwmLeft_PWMModeIsCenterAligned) */
	   
	   #define MotorPwmLeft_COMPARE1_LSB    (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define MotorPwmLeft_COMPARE1_LSB_PTR ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D0_REG)
	   #define MotorPwmLeft_COMPARE2_LSB    (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define MotorPwmLeft_COMPARE2_LSB_PTR ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
	   #define MotorPwmLeft_COUNTERCAP_LSB   (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define MotorPwmLeft_COUNTERCAP_LSB_PTR ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A1_REG)
	   #define MotorPwmLeft_COUNTER_LSB     (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define MotorPwmLeft_COUNTER_LSB_PTR  ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A0_REG)
	   #define MotorPwmLeft_CAPTURE_LSB     (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F1_REG)
	   #define MotorPwmLeft_CAPTURE_LSB_PTR  ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(MotorPwmLeft_PWMModeIsCenterAligned)
		       #define MotorPwmLeft_PERIOD_LSB      (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
		       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #else
		       #define MotorPwmLeft_PERIOD_LSB      (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F0_REG)
		       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F0_REG)
		    #endif /* (MotorPwmLeft_PWMModeIsCenterAligned) */
		   
		    #define MotorPwmLeft_COMPARE1_LSB    (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define MotorPwmLeft_COMPARE1_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D0_REG)
		    #define MotorPwmLeft_COMPARE2_LSB    (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define MotorPwmLeft_COMPARE2_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__D1_REG)
		    #define MotorPwmLeft_COUNTERCAP_LSB   (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define MotorPwmLeft_COUNTERCAP_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A1_REG)
		    #define MotorPwmLeft_COUNTER_LSB     (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define MotorPwmLeft_COUNTER_LSB_PTR  ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__A0_REG)
		    #define MotorPwmLeft_CAPTURE_LSB     (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F1_REG)
		    #define MotorPwmLeft_CAPTURE_LSB_PTR  ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__F1_REG)
		#else
			#if(MotorPwmLeft_PWMModeIsCenterAligned)
		       #define MotorPwmLeft_PERIOD_LSB      (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define MotorPwmLeft_PERIOD_LSB      (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		       #define MotorPwmLeft_PERIOD_LSB_PTR   ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (MotorPwmLeft_PWMModeIsCenterAligned) */
		   
		    #define MotorPwmLeft_COMPARE1_LSB    (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define MotorPwmLeft_COMPARE1_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
		    #define MotorPwmLeft_COMPARE2_LSB    (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define MotorPwmLeft_COMPARE2_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
		    #define MotorPwmLeft_COUNTERCAP_LSB   (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define MotorPwmLeft_COUNTERCAP_LSB_PTR ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
		    #define MotorPwmLeft_COUNTER_LSB     (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define MotorPwmLeft_COUNTER_LSB_PTR  ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
		    #define MotorPwmLeft_CAPTURE_LSB     (*(reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		    #define MotorPwmLeft_CAPTURE_LSB_PTR  ((reg16 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define MotorPwmLeft_AUX_CONTROLDP1    (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define MotorPwmLeft_AUX_CONTROLDP1_PTR  ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MotorPwmLeft_Resolution == 8) */
   
   #define MotorPwmLeft_AUX_CONTROLDP0      (*(reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define MotorPwmLeft_AUX_CONTROLDP0_PTR  ((reg8 *) MotorPwmLeft_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MotorPwmLeft_UsingFixedFunction) */
   
#if(MotorPwmLeft_KillModeMinTime )
    #define MotorPwmLeft_KILLMODEMINTIME      (*(reg8 *) MotorPwmLeft_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MotorPwmLeft_KILLMODEMINTIME_PTR   ((reg8 *) MotorPwmLeft_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MotorPwmLeft_KillModeMinTime ) */

#if(MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_256_CLOCKS)
    #define MotorPwmLeft_DEADBAND_COUNT      (*(reg8 *) MotorPwmLeft_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPwmLeft_DEADBAND_COUNT_PTR  ((reg8 *) MotorPwmLeft_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPwmLeft_DEADBAND_LSB_PTR    ((reg8 *) MotorPwmLeft_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MotorPwmLeft_DEADBAND_LSB        (*(reg8 *) MotorPwmLeft_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MotorPwmLeft_UsingFixedFunction)
        #define MotorPwmLeft_DEADBAND_COUNT        (*(reg8 *) MotorPwmLeft_PWMHW__CFG0) 
        #define MotorPwmLeft_DEADBAND_COUNT_PTR     ((reg8 *) MotorPwmLeft_PWMHW__CFG0)
        #define MotorPwmLeft_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPwmLeft_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MotorPwmLeft_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MotorPwmLeft_DEADBAND_COUNT        (*(reg8 *) MotorPwmLeft_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPwmLeft_DEADBAND_COUNT_PTR     ((reg8 *) MotorPwmLeft_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPwmLeft_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPwmLeft_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define MotorPwmLeft_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
#endif /* (MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_256_CLOCKS) */



#if (MotorPwmLeft_UsingFixedFunction)
    #define MotorPwmLeft_STATUS                (*(reg8 *) MotorPwmLeft_PWMHW__SR0)
    #define MotorPwmLeft_STATUS_PTR            ((reg8 *) MotorPwmLeft_PWMHW__SR0)
    #define MotorPwmLeft_STATUS_MASK           (*(reg8 *) MotorPwmLeft_PWMHW__SR0)
    #define MotorPwmLeft_STATUS_MASK_PTR       ((reg8 *) MotorPwmLeft_PWMHW__SR0)
    #define MotorPwmLeft_CONTROL               (*(reg8 *) MotorPwmLeft_PWMHW__CFG0)
    #define MotorPwmLeft_CONTROL_PTR           ((reg8 *) MotorPwmLeft_PWMHW__CFG0)    
    #define MotorPwmLeft_CONTROL2              (*(reg8 *) MotorPwmLeft_PWMHW__CFG1)    
    #define MotorPwmLeft_CONTROL3              (*(reg8 *) MotorPwmLeft_PWMHW__CFG2)
    #define MotorPwmLeft_GLOBAL_ENABLE         (*(reg8 *) MotorPwmLeft_PWMHW__PM_ACT_CFG)
    #define MotorPwmLeft_GLOBAL_ENABLE_PTR       ( (reg8 *) MotorPwmLeft_PWMHW__PM_ACT_CFG)
    #define MotorPwmLeft_GLOBAL_STBY_ENABLE      (*(reg8 *) MotorPwmLeft_PWMHW__PM_STBY_CFG)
    #define MotorPwmLeft_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) MotorPwmLeft_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MotorPwmLeft_BLOCK_EN_MASK          MotorPwmLeft_PWMHW__PM_ACT_MSK
    #define MotorPwmLeft_BLOCK_STBY_EN_MASK     MotorPwmLeft_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define MotorPwmLeft_CTRL_ENABLE_SHIFT      0x00u
    
    #define MotorPwmLeft_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    
    #define MotorPwmLeft_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */

    /* Fixed Function Block Only CFG register bit definitions */
    #define MotorPwmLeft_CFG0_MODE              0x02u   /*  Set to compare mode */
    
    /* #define MotorPwmLeft_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define MotorPwmLeft_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define MotorPwmLeft_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPwmLeft_CTRL_ENABLE_SHIFT)
    #define MotorPwmLeft_CTRL_RESET             (uint8)((uint8)0x01u << MotorPwmLeft_CTRL_RESET_SHIFT)
    #define MotorPwmLeft_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPwmLeft_CTRL_CMPMODE2_SHIFT)
    #define MotorPwmLeft_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPwmLeft_CTRL_CMPMODE1_SHIFT)
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorPwmLeft_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define MotorPwmLeft_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MotorPwmLeft_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define MotorPwmLeft_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define MotorPwmLeft_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define MotorPwmLeft_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define MotorPwmLeft_STATUS_TC_INT_EN_MASK_SHIFT            (MotorPwmLeft_STATUS_TC_SHIFT - 4u)
    #define MotorPwmLeft_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define MotorPwmLeft_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorPwmLeft_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define MotorPwmLeft_STATUS_TC              (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_TC_SHIFT)
    #define MotorPwmLeft_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks */
    #define MotorPwmLeft_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MotorPwmLeft_STATUS_TC >> 4u)
    #define MotorPwmLeft_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MotorPwmLeft_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants */
    #define MotorPwmLeft_RT1_SHIFT             0x04u
    #define MotorPwmLeft_RT1_MASK              (uint8)((uint8)0x03u << MotorPwmLeft_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define MotorPwmLeft_SYNC                  (uint8)((uint8)0x03u << MotorPwmLeft_RT1_SHIFT)
    #define MotorPwmLeft_SYNCDSI_SHIFT         0x00u
    #define MotorPwmLeft_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MotorPwmLeft_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define MotorPwmLeft_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MotorPwmLeft_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define MotorPwmLeft_STATUS                (*(reg8 *) MotorPwmLeft_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPwmLeft_STATUS_PTR            ((reg8 *) MotorPwmLeft_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPwmLeft_STATUS_MASK           (*(reg8 *) MotorPwmLeft_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPwmLeft_STATUS_MASK_PTR       ((reg8 *) MotorPwmLeft_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPwmLeft_STATUS_AUX_CTRL       (*(reg8 *) MotorPwmLeft_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MotorPwmLeft_CONTROL               (*(reg8 *) MotorPwmLeft_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MotorPwmLeft_CONTROL_PTR           ((reg8 *) MotorPwmLeft_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define MotorPwmLeft_CTRL_ENABLE_SHIFT      0x07u
    #define MotorPwmLeft_CTRL_RESET_SHIFT       0x06u
    #define MotorPwmLeft_CTRL_CMPMODE2_SHIFT    0x03u
    #define MotorPwmLeft_CTRL_CMPMODE1_SHIFT    0x00u
    #define MotorPwmLeft_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define MotorPwmLeft_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPwmLeft_CTRL_ENABLE_SHIFT)
    #define MotorPwmLeft_CTRL_RESET             (uint8)((uint8)0x01u << MotorPwmLeft_CTRL_RESET_SHIFT)
    #define MotorPwmLeft_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPwmLeft_CTRL_CMPMODE2_SHIFT)
    #define MotorPwmLeft_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPwmLeft_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define MotorPwmLeft_STATUS_KILL_SHIFT          0x05u
    #define MotorPwmLeft_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define MotorPwmLeft_STATUS_FIFOFULL_SHIFT      0x03u  
    #define MotorPwmLeft_STATUS_TC_SHIFT            0x02u
    #define MotorPwmLeft_STATUS_CMP2_SHIFT          0x01u
    #define MotorPwmLeft_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MotorPwmLeft_STATUS_KILL_INT_EN_MASK_SHIFT          MotorPwmLeft_STATUS_KILL_SHIFT          
    #define MotorPwmLeft_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    MotorPwmLeft_STATUS_FIFONEMPTY_SHIFT    
    #define MotorPwmLeft_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      MotorPwmLeft_STATUS_FIFOFULL_SHIFT        
    #define MotorPwmLeft_STATUS_TC_INT_EN_MASK_SHIFT            MotorPwmLeft_STATUS_TC_SHIFT            
    #define MotorPwmLeft_STATUS_CMP2_INT_EN_MASK_SHIFT          MotorPwmLeft_STATUS_CMP2_SHIFT          
    #define MotorPwmLeft_STATUS_CMP1_INT_EN_MASK_SHIFT          MotorPwmLeft_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define MotorPwmLeft_STATUS_KILL            (uint8)((uint8)0x00u << MotorPwmLeft_STATUS_KILL_SHIFT )
    #define MotorPwmLeft_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_FIFOFULL_SHIFT)
    #define MotorPwmLeft_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_FIFONEMPTY_SHIFT)
    #define MotorPwmLeft_STATUS_TC              (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_TC_SHIFT)
    #define MotorPwmLeft_STATUS_CMP2            (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_CMP2_SHIFT) 
    #define MotorPwmLeft_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPwmLeft_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MotorPwmLeft_STATUS_KILL_INT_EN_MASK            MotorPwmLeft_STATUS_KILL
    #define MotorPwmLeft_STATUS_FIFOFULL_INT_EN_MASK        MotorPwmLeft_STATUS_FIFOFULL
    #define MotorPwmLeft_STATUS_FIFONEMPTY_INT_EN_MASK      MotorPwmLeft_STATUS_FIFONEMPTY
    #define MotorPwmLeft_STATUS_TC_INT_EN_MASK              MotorPwmLeft_STATUS_TC
    #define MotorPwmLeft_STATUS_CMP2_INT_EN_MASK            MotorPwmLeft_STATUS_CMP2
    #define MotorPwmLeft_STATUS_CMP1_INT_EN_MASK            MotorPwmLeft_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define MotorPwmLeft_AUX_CTRL_FIFO0_CLR     0x01u
    #define MotorPwmLeft_AUX_CTRL_FIFO1_CLR     0x02u
    #define MotorPwmLeft_AUX_CTRL_FIFO0_LVL     0x04u
    #define MotorPwmLeft_AUX_CTRL_FIFO1_LVL     0x08u
    #define MotorPwmLeft_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* MotorPwmLeft_UsingFixedFunction */

#endif  /* CY_PWM_MotorPwmLeft_H */


/* [] END OF FILE */
