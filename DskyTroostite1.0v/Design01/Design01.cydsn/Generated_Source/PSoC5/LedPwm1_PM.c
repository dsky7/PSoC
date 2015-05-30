/*******************************************************************************
* File Name: LedPwm1_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "LedPwm1.h"

static LedPwm1_backupStruct LedPwm1_backup;


/*******************************************************************************
* Function Name: LedPwm1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  LedPwm1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void LedPwm1_SaveConfig(void) 
{
    
    #if(!LedPwm1_UsingFixedFunction)
        #if(!LedPwm1_PWMModeIsCenterAligned)
            LedPwm1_backup.PWMPeriod = LedPwm1_ReadPeriod();
        #endif /* (!LedPwm1_PWMModeIsCenterAligned) */
        LedPwm1_backup.PWMUdb = LedPwm1_ReadCounter();
        #if (LedPwm1_UseStatus)
            LedPwm1_backup.InterruptMaskValue = LedPwm1_STATUS_MASK;
        #endif /* (LedPwm1_UseStatus) */
        
        #if(LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_256_CLOCKS || \
            LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_2_4_CLOCKS)
            LedPwm1_backup.PWMdeadBandValue = LedPwm1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(LedPwm1_KillModeMinTime)
             LedPwm1_backup.PWMKillCounterPeriod = LedPwm1_ReadKillTime();
        #endif /* (LedPwm1_KillModeMinTime) */
        
        #if(LedPwm1_UseControl)
            LedPwm1_backup.PWMControlRegister = LedPwm1_ReadControlRegister();
        #endif /* (LedPwm1_UseControl) */
    #endif  /* (!LedPwm1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LedPwm1_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  LedPwm1_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LedPwm1_RestoreConfig(void) 
{
        #if(!LedPwm1_UsingFixedFunction)
            #if(!LedPwm1_PWMModeIsCenterAligned)
                LedPwm1_WritePeriod(LedPwm1_backup.PWMPeriod);
            #endif /* (!LedPwm1_PWMModeIsCenterAligned) */
            LedPwm1_WriteCounter(LedPwm1_backup.PWMUdb);
            #if (LedPwm1_UseStatus)
                LedPwm1_STATUS_MASK = LedPwm1_backup.InterruptMaskValue;
            #endif /* (LedPwm1_UseStatus) */
            
            #if(LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_256_CLOCKS || \
                LedPwm1_DeadBandMode == LedPwm1__B_PWM__DBM_2_4_CLOCKS)
                LedPwm1_WriteDeadTime(LedPwm1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(LedPwm1_KillModeMinTime)
                LedPwm1_WriteKillTime(LedPwm1_backup.PWMKillCounterPeriod);
            #endif /* (LedPwm1_KillModeMinTime) */
            
            #if(LedPwm1_UseControl)
                LedPwm1_WriteControlRegister(LedPwm1_backup.PWMControlRegister); 
            #endif /* (LedPwm1_UseControl) */
        #endif  /* (!LedPwm1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LedPwm1_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  LedPwm1_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LedPwm1_Sleep(void) 
{
    #if(LedPwm1_UseControl)
        if(LedPwm1_CTRL_ENABLE == (LedPwm1_CONTROL & LedPwm1_CTRL_ENABLE))
        {
            /*Component is enabled */
            LedPwm1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LedPwm1_backup.PWMEnableState = 0u;
        }
    #endif /* (LedPwm1_UseControl) */

    /* Stop component */
    LedPwm1_Stop();
    
    /* Save registers configuration */
    LedPwm1_SaveConfig();
}


/*******************************************************************************
* Function Name: LedPwm1_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  LedPwm1_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LedPwm1_Wakeup(void) 
{
     /* Restore registers values */
    LedPwm1_RestoreConfig();
    
    if(LedPwm1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LedPwm1_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
