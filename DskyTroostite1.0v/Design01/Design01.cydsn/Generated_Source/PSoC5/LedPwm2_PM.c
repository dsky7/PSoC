/*******************************************************************************
* File Name: LedPwm2_PM.c
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
#include "LedPwm2.h"

static LedPwm2_backupStruct LedPwm2_backup;


/*******************************************************************************
* Function Name: LedPwm2_SaveConfig
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
*  LedPwm2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void LedPwm2_SaveConfig(void) 
{
    
    #if(!LedPwm2_UsingFixedFunction)
        #if(!LedPwm2_PWMModeIsCenterAligned)
            LedPwm2_backup.PWMPeriod = LedPwm2_ReadPeriod();
        #endif /* (!LedPwm2_PWMModeIsCenterAligned) */
        LedPwm2_backup.PWMUdb = LedPwm2_ReadCounter();
        #if (LedPwm2_UseStatus)
            LedPwm2_backup.InterruptMaskValue = LedPwm2_STATUS_MASK;
        #endif /* (LedPwm2_UseStatus) */
        
        #if(LedPwm2_DeadBandMode == LedPwm2__B_PWM__DBM_256_CLOCKS || \
            LedPwm2_DeadBandMode == LedPwm2__B_PWM__DBM_2_4_CLOCKS)
            LedPwm2_backup.PWMdeadBandValue = LedPwm2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(LedPwm2_KillModeMinTime)
             LedPwm2_backup.PWMKillCounterPeriod = LedPwm2_ReadKillTime();
        #endif /* (LedPwm2_KillModeMinTime) */
        
        #if(LedPwm2_UseControl)
            LedPwm2_backup.PWMControlRegister = LedPwm2_ReadControlRegister();
        #endif /* (LedPwm2_UseControl) */
    #endif  /* (!LedPwm2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LedPwm2_RestoreConfig
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
*  LedPwm2_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LedPwm2_RestoreConfig(void) 
{
        #if(!LedPwm2_UsingFixedFunction)
            #if(!LedPwm2_PWMModeIsCenterAligned)
                LedPwm2_WritePeriod(LedPwm2_backup.PWMPeriod);
            #endif /* (!LedPwm2_PWMModeIsCenterAligned) */
            LedPwm2_WriteCounter(LedPwm2_backup.PWMUdb);
            #if (LedPwm2_UseStatus)
                LedPwm2_STATUS_MASK = LedPwm2_backup.InterruptMaskValue;
            #endif /* (LedPwm2_UseStatus) */
            
            #if(LedPwm2_DeadBandMode == LedPwm2__B_PWM__DBM_256_CLOCKS || \
                LedPwm2_DeadBandMode == LedPwm2__B_PWM__DBM_2_4_CLOCKS)
                LedPwm2_WriteDeadTime(LedPwm2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(LedPwm2_KillModeMinTime)
                LedPwm2_WriteKillTime(LedPwm2_backup.PWMKillCounterPeriod);
            #endif /* (LedPwm2_KillModeMinTime) */
            
            #if(LedPwm2_UseControl)
                LedPwm2_WriteControlRegister(LedPwm2_backup.PWMControlRegister); 
            #endif /* (LedPwm2_UseControl) */
        #endif  /* (!LedPwm2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LedPwm2_Sleep
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
*  LedPwm2_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LedPwm2_Sleep(void) 
{
    #if(LedPwm2_UseControl)
        if(LedPwm2_CTRL_ENABLE == (LedPwm2_CONTROL & LedPwm2_CTRL_ENABLE))
        {
            /*Component is enabled */
            LedPwm2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LedPwm2_backup.PWMEnableState = 0u;
        }
    #endif /* (LedPwm2_UseControl) */

    /* Stop component */
    LedPwm2_Stop();
    
    /* Save registers configuration */
    LedPwm2_SaveConfig();
}


/*******************************************************************************
* Function Name: LedPwm2_Wakeup
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
*  LedPwm2_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LedPwm2_Wakeup(void) 
{
     /* Restore registers values */
    LedPwm2_RestoreConfig();
    
    if(LedPwm2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LedPwm2_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
