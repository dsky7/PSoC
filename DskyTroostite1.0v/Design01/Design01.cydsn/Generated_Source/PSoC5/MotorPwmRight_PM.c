/*******************************************************************************
* File Name: MotorPwmRight_PM.c
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
#include "MotorPwmRight.h"

static MotorPwmRight_backupStruct MotorPwmRight_backup;


/*******************************************************************************
* Function Name: MotorPwmRight_SaveConfig
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
*  MotorPwmRight_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MotorPwmRight_SaveConfig(void) 
{
    
    #if(!MotorPwmRight_UsingFixedFunction)
        #if(!MotorPwmRight_PWMModeIsCenterAligned)
            MotorPwmRight_backup.PWMPeriod = MotorPwmRight_ReadPeriod();
        #endif /* (!MotorPwmRight_PWMModeIsCenterAligned) */
        MotorPwmRight_backup.PWMUdb = MotorPwmRight_ReadCounter();
        #if (MotorPwmRight_UseStatus)
            MotorPwmRight_backup.InterruptMaskValue = MotorPwmRight_STATUS_MASK;
        #endif /* (MotorPwmRight_UseStatus) */
        
        #if(MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_256_CLOCKS || \
            MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_2_4_CLOCKS)
            MotorPwmRight_backup.PWMdeadBandValue = MotorPwmRight_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(MotorPwmRight_KillModeMinTime)
             MotorPwmRight_backup.PWMKillCounterPeriod = MotorPwmRight_ReadKillTime();
        #endif /* (MotorPwmRight_KillModeMinTime) */
        
        #if(MotorPwmRight_UseControl)
            MotorPwmRight_backup.PWMControlRegister = MotorPwmRight_ReadControlRegister();
        #endif /* (MotorPwmRight_UseControl) */
    #endif  /* (!MotorPwmRight_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmRight_RestoreConfig
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
*  MotorPwmRight_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPwmRight_RestoreConfig(void) 
{
        #if(!MotorPwmRight_UsingFixedFunction)
            #if(!MotorPwmRight_PWMModeIsCenterAligned)
                MotorPwmRight_WritePeriod(MotorPwmRight_backup.PWMPeriod);
            #endif /* (!MotorPwmRight_PWMModeIsCenterAligned) */
            MotorPwmRight_WriteCounter(MotorPwmRight_backup.PWMUdb);
            #if (MotorPwmRight_UseStatus)
                MotorPwmRight_STATUS_MASK = MotorPwmRight_backup.InterruptMaskValue;
            #endif /* (MotorPwmRight_UseStatus) */
            
            #if(MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_256_CLOCKS || \
                MotorPwmRight_DeadBandMode == MotorPwmRight__B_PWM__DBM_2_4_CLOCKS)
                MotorPwmRight_WriteDeadTime(MotorPwmRight_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(MotorPwmRight_KillModeMinTime)
                MotorPwmRight_WriteKillTime(MotorPwmRight_backup.PWMKillCounterPeriod);
            #endif /* (MotorPwmRight_KillModeMinTime) */
            
            #if(MotorPwmRight_UseControl)
                MotorPwmRight_WriteControlRegister(MotorPwmRight_backup.PWMControlRegister); 
            #endif /* (MotorPwmRight_UseControl) */
        #endif  /* (!MotorPwmRight_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorPwmRight_Sleep
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
*  MotorPwmRight_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorPwmRight_Sleep(void) 
{
    #if(MotorPwmRight_UseControl)
        if(MotorPwmRight_CTRL_ENABLE == (MotorPwmRight_CONTROL & MotorPwmRight_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorPwmRight_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorPwmRight_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorPwmRight_UseControl) */

    /* Stop component */
    MotorPwmRight_Stop();
    
    /* Save registers configuration */
    MotorPwmRight_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorPwmRight_Wakeup
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
*  MotorPwmRight_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPwmRight_Wakeup(void) 
{
     /* Restore registers values */
    MotorPwmRight_RestoreConfig();
    
    if(MotorPwmRight_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorPwmRight_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
