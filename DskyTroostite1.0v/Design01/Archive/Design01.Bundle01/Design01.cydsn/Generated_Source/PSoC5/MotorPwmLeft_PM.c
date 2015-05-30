/*******************************************************************************
* File Name: MotorPwmLeft_PM.c
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
#include "MotorPwmLeft.h"

static MotorPwmLeft_backupStruct MotorPwmLeft_backup;


/*******************************************************************************
* Function Name: MotorPwmLeft_SaveConfig
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
*  MotorPwmLeft_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void MotorPwmLeft_SaveConfig(void) 
{
    
    #if(!MotorPwmLeft_UsingFixedFunction)
        #if(!MotorPwmLeft_PWMModeIsCenterAligned)
            MotorPwmLeft_backup.PWMPeriod = MotorPwmLeft_ReadPeriod();
        #endif /* (!MotorPwmLeft_PWMModeIsCenterAligned) */
        MotorPwmLeft_backup.PWMUdb = MotorPwmLeft_ReadCounter();
        #if (MotorPwmLeft_UseStatus)
            MotorPwmLeft_backup.InterruptMaskValue = MotorPwmLeft_STATUS_MASK;
        #endif /* (MotorPwmLeft_UseStatus) */
        
        #if(MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_256_CLOCKS || \
            MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_2_4_CLOCKS)
            MotorPwmLeft_backup.PWMdeadBandValue = MotorPwmLeft_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(MotorPwmLeft_KillModeMinTime)
             MotorPwmLeft_backup.PWMKillCounterPeriod = MotorPwmLeft_ReadKillTime();
        #endif /* (MotorPwmLeft_KillModeMinTime) */
        
        #if(MotorPwmLeft_UseControl)
            MotorPwmLeft_backup.PWMControlRegister = MotorPwmLeft_ReadControlRegister();
        #endif /* (MotorPwmLeft_UseControl) */
    #endif  /* (!MotorPwmLeft_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmLeft_RestoreConfig
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
*  MotorPwmLeft_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPwmLeft_RestoreConfig(void) 
{
        #if(!MotorPwmLeft_UsingFixedFunction)
            #if(!MotorPwmLeft_PWMModeIsCenterAligned)
                MotorPwmLeft_WritePeriod(MotorPwmLeft_backup.PWMPeriod);
            #endif /* (!MotorPwmLeft_PWMModeIsCenterAligned) */
            MotorPwmLeft_WriteCounter(MotorPwmLeft_backup.PWMUdb);
            #if (MotorPwmLeft_UseStatus)
                MotorPwmLeft_STATUS_MASK = MotorPwmLeft_backup.InterruptMaskValue;
            #endif /* (MotorPwmLeft_UseStatus) */
            
            #if(MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_256_CLOCKS || \
                MotorPwmLeft_DeadBandMode == MotorPwmLeft__B_PWM__DBM_2_4_CLOCKS)
                MotorPwmLeft_WriteDeadTime(MotorPwmLeft_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(MotorPwmLeft_KillModeMinTime)
                MotorPwmLeft_WriteKillTime(MotorPwmLeft_backup.PWMKillCounterPeriod);
            #endif /* (MotorPwmLeft_KillModeMinTime) */
            
            #if(MotorPwmLeft_UseControl)
                MotorPwmLeft_WriteControlRegister(MotorPwmLeft_backup.PWMControlRegister); 
            #endif /* (MotorPwmLeft_UseControl) */
        #endif  /* (!MotorPwmLeft_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorPwmLeft_Sleep
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
*  MotorPwmLeft_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorPwmLeft_Sleep(void) 
{
    #if(MotorPwmLeft_UseControl)
        if(MotorPwmLeft_CTRL_ENABLE == (MotorPwmLeft_CONTROL & MotorPwmLeft_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorPwmLeft_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorPwmLeft_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorPwmLeft_UseControl) */

    /* Stop component */
    MotorPwmLeft_Stop();
    
    /* Save registers configuration */
    MotorPwmLeft_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorPwmLeft_Wakeup
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
*  MotorPwmLeft_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPwmLeft_Wakeup(void) 
{
     /* Restore registers values */
    MotorPwmLeft_RestoreConfig();
    
    if(MotorPwmLeft_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorPwmLeft_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
