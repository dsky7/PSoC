/*******************************************************************************
* File Name: LedPwm2.c  
* Version 3.0
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks. 
*  The compare value output may be configured to be active when the present 
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "LedPwm2.h"

uint8 LedPwm2_initVar = 0u;


/*******************************************************************************
* Function Name: LedPwm2_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
* Global variables:
*  LedPwm2_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void LedPwm2_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LedPwm2_initVar == 0u)
    {
        LedPwm2_Init();
        LedPwm2_initVar = 1u;
    }
    LedPwm2_Enable();

}


/*******************************************************************************
* Function Name: LedPwm2_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  LedPwm2_Start().
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void LedPwm2_Init(void) 
{
    #if (LedPwm2_UsingFixedFunction || LedPwm2_UseControl)
        uint8 ctrl;
    #endif /* (LedPwm2_UsingFixedFunction || LedPwm2_UseControl) */
    
    #if(!LedPwm2_UsingFixedFunction) 
        #if(LedPwm2_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 LedPwm2_interruptState;
        #endif /* (LedPwm2_UseStatus) */
    #endif /* (!LedPwm2_UsingFixedFunction) */
    
    #if (LedPwm2_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        LedPwm2_CONTROL |= LedPwm2_CFG0_MODE;
        #if (LedPwm2_DeadBand2_4)
            LedPwm2_CONTROL |= LedPwm2_CFG0_DB;
        #endif /* (LedPwm2_DeadBand2_4) */
                
        ctrl = LedPwm2_CONTROL3 & ((uint8 )(~LedPwm2_CTRL_CMPMODE1_MASK));
        LedPwm2_CONTROL3 = ctrl | LedPwm2_DEFAULT_COMPARE1_MODE;
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        LedPwm2_RT1 &= ((uint8)(~LedPwm2_RT1_MASK));
        LedPwm2_RT1 |= LedPwm2_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        LedPwm2_RT1 &= ((uint8)(~LedPwm2_SYNCDSI_MASK));
        LedPwm2_RT1 |= LedPwm2_SYNCDSI_EN;
       
    #elif (LedPwm2_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = LedPwm2_CONTROL & ((uint8)(~LedPwm2_CTRL_CMPMODE2_MASK)) & ((uint8)(~LedPwm2_CTRL_CMPMODE1_MASK));
        LedPwm2_CONTROL = ctrl | LedPwm2_DEFAULT_COMPARE2_MODE | 
                                   LedPwm2_DEFAULT_COMPARE1_MODE;
    #endif /* (LedPwm2_UsingFixedFunction) */
        
    #if (!LedPwm2_UsingFixedFunction)
        #if (LedPwm2_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            LedPwm2_AUX_CONTROLDP0 |= (LedPwm2_AUX_CTRL_FIFO0_CLR);
        #else /* (LedPwm2_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            LedPwm2_AUX_CONTROLDP0 |= (LedPwm2_AUX_CTRL_FIFO0_CLR);
            LedPwm2_AUX_CONTROLDP1 |= (LedPwm2_AUX_CTRL_FIFO0_CLR);
        #endif /* (LedPwm2_Resolution == 8) */

        LedPwm2_WriteCounter(LedPwm2_INIT_PERIOD_VALUE);
    #endif /* (!LedPwm2_UsingFixedFunction) */
        
    LedPwm2_WritePeriod(LedPwm2_INIT_PERIOD_VALUE);

        #if (LedPwm2_UseOneCompareMode)
            LedPwm2_WriteCompare(LedPwm2_INIT_COMPARE_VALUE1);
        #else
            LedPwm2_WriteCompare1(LedPwm2_INIT_COMPARE_VALUE1);
            LedPwm2_WriteCompare2(LedPwm2_INIT_COMPARE_VALUE2);
        #endif /* (LedPwm2_UseOneCompareMode) */
        
        #if (LedPwm2_KillModeMinTime)
            LedPwm2_WriteKillTime(LedPwm2_MinimumKillTime);
        #endif /* (LedPwm2_KillModeMinTime) */
        
        #if (LedPwm2_DeadBandUsed)
            LedPwm2_WriteDeadTime(LedPwm2_INIT_DEAD_TIME);
        #endif /* (LedPwm2_DeadBandUsed) */

    #if (LedPwm2_UseStatus || LedPwm2_UsingFixedFunction)
        LedPwm2_SetInterruptMode(LedPwm2_INIT_INTERRUPTS_MODE);
    #endif /* (LedPwm2_UseStatus || LedPwm2_UsingFixedFunction) */
        
    #if (LedPwm2_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        LedPwm2_GLOBAL_ENABLE |= LedPwm2_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        LedPwm2_CONTROL2 |= LedPwm2_CTRL2_IRQ_SEL;
    #else
        #if(LedPwm2_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LedPwm2_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            LedPwm2_STATUS_AUX_CTRL |= LedPwm2_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(LedPwm2_interruptState);
            
            /* Clear the FIFO to enable the LedPwm2_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            LedPwm2_ClearFIFO();
        #endif /* (LedPwm2_UseStatus) */
    #endif /* (LedPwm2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LedPwm2_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void LedPwm2_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LedPwm2_UsingFixedFunction)
        LedPwm2_GLOBAL_ENABLE |= LedPwm2_BLOCK_EN_MASK;
        LedPwm2_GLOBAL_STBY_ENABLE |= LedPwm2_BLOCK_STBY_EN_MASK;
    #endif /* (LedPwm2_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (LedPwm2_UseControl || LedPwm2_UsingFixedFunction)
        LedPwm2_CONTROL |= LedPwm2_CTRL_ENABLE;
    #endif /* (LedPwm2_UseControl || LedPwm2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LedPwm2_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void LedPwm2_Stop(void) 
{
    #if (LedPwm2_UseControl || LedPwm2_UsingFixedFunction)
        LedPwm2_CONTROL &= ((uint8)(~LedPwm2_CTRL_ENABLE));
    #endif /* (LedPwm2_UseControl || LedPwm2_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (LedPwm2_UsingFixedFunction)
        LedPwm2_GLOBAL_ENABLE &= ((uint8)(~LedPwm2_BLOCK_EN_MASK));
        LedPwm2_GLOBAL_STBY_ENABLE &= ((uint8)(~LedPwm2_BLOCK_STBY_EN_MASK));
    #endif /* (LedPwm2_UsingFixedFunction) */
}


#if (LedPwm2_UseOneCompareMode)
	#if (LedPwm2_CompareMode1SW)


		/*******************************************************************************
		* Function Name: LedPwm2_SetCompareMode
		********************************************************************************
		* 
		* Summary:
		*  This function writes the Compare Mode for the pwm output when in Dither mode,
		*  Center Align Mode or One Output Mode.
		*
		* Parameters:
		*  comparemode:  The new compare mode for the PWM output. Use the compare types
		*                defined in the H file as input arguments.
		*
		* Return:
		*  None
		*
		*******************************************************************************/
		void LedPwm2_SetCompareMode(uint8 comparemode) 
		{
		    #if(LedPwm2_UsingFixedFunction)
            
                #if(0 != LedPwm2_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << LedPwm2_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != LedPwm2_CTRL_CMPMODE1_SHIFT) */
            
	            LedPwm2_CONTROL3 &= ((uint8)(~LedPwm2_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
	            LedPwm2_CONTROL3 |= comparemodemasked;     
		                
		    #elif (LedPwm2_UseControl)
		        
                #if(0 != LedPwm2_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << LedPwm2_CTRL_CMPMODE1_SHIFT)) & 
    		                                    LedPwm2_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & LedPwm2_CTRL_CMPMODE1_MASK;                
                #endif /* (0 != LedPwm2_CTRL_CMPMODE1_SHIFT) */
                
                #if(0 != LedPwm2_CTRL_CMPMODE2_SHIFT)                            
    		        uint8 comparemode2masked = ((uint8)((uint8)comparemode << LedPwm2_CTRL_CMPMODE2_SHIFT)) & 
    		                                   LedPwm2_CTRL_CMPMODE2_MASK;
                #else
    		        uint8 comparemode2masked = comparemode & LedPwm2_CTRL_CMPMODE2_MASK;                
                #endif /* (0 != LedPwm2_CTRL_CMPMODE2_SHIFT) */
                
		        /*Clear existing mode */
		        LedPwm2_CONTROL &= ((uint8)(~(LedPwm2_CTRL_CMPMODE1_MASK | LedPwm2_CTRL_CMPMODE2_MASK))); 
		        LedPwm2_CONTROL |= (comparemode1masked | comparemode2masked);
		        
		    #else
		        uint8 temp = comparemode;
		    #endif /* (LedPwm2_UsingFixedFunction) */
		}
	#endif /* LedPwm2_CompareMode1SW */

#else /* UseOneCompareMode */

	#if (LedPwm2_CompareMode1SW)


		/*******************************************************************************
		* Function Name: LedPwm2_SetCompareMode1
		********************************************************************************
		* 
		* Summary:
		*  This function writes the Compare Mode for the pwm or pwm1 output
		*
		* Parameters:  
		*  comparemode:  The new compare mode for the PWM output. Use the compare types
		*                defined in the H file as input arguments.
		*
		* Return: 
		*  None
		*
		*******************************************************************************/
		void LedPwm2_SetCompareMode1(uint8 comparemode) 
		{
		    #if(0 != LedPwm2_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << LedPwm2_CTRL_CMPMODE1_SHIFT)) & 
    		                               LedPwm2_CTRL_CMPMODE1_MASK;
		    #else
                uint8 comparemodemasked = comparemode & LedPwm2_CTRL_CMPMODE1_MASK;                
            #endif /* (0 != LedPwm2_CTRL_CMPMODE1_SHIFT) */
                   
		    #if (LedPwm2_UseControl)
		        LedPwm2_CONTROL &= ((uint8)(~LedPwm2_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
		        LedPwm2_CONTROL |= comparemodemasked;
		    #endif /* (LedPwm2_UseControl) */
		}
	#endif /* LedPwm2_CompareMode1SW */

#if (LedPwm2_CompareMode2SW)


    /*******************************************************************************
    * Function Name: LedPwm2_SetCompareMode2
    ********************************************************************************
    * 
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:  
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void LedPwm2_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != LedPwm2_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << LedPwm2_CTRL_CMPMODE2_SHIFT)) & 
                                                 LedPwm2_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & LedPwm2_CTRL_CMPMODE2_MASK;            
        #endif /* (0 != LedPwm2_CTRL_CMPMODE2_SHIFT) */
        
        #if (LedPwm2_UseControl)
            LedPwm2_CONTROL &= ((uint8)(~LedPwm2_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            LedPwm2_CONTROL |= comparemodemasked;
        #endif /* (LedPwm2_UseControl) */
    }
    #endif /*LedPwm2_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!LedPwm2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LedPwm2_WriteCounter
    ********************************************************************************
    * 
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be 
    *  implemented for that currently running period and only that period. This API 
    *  is valid only for UDB implementation and not available for fixed function 
    *  PWM implementation.    
    *
    * Parameters:  
    *  counter:  The period new period counter value.
    *
    * Return: 
    *  None
    *
    * Side Effects: 
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void LedPwm2_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(LedPwm2_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: LedPwm2_ReadCounter
    ********************************************************************************
    * 
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:  
    *  None  
    *
    * Return: 
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 LedPwm2_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
        (void)LedPwm2_COUNTERCAP_LSB;
        
        /* Read the data from the FIFO (or capture register for Fixed Function)*/
        return (CY_GET_REG8(LedPwm2_CAPTURE_LSB_PTR));
    }

        #if (LedPwm2_UseStatus)


            /*******************************************************************************
            * Function Name: LedPwm2_ClearFIFO
            ********************************************************************************
            * 
            * Summary:
            *  This function clears all capture data from the capture FIFO
            *
            * Parameters:  
            *  None
            *
            * Return: 
            *  None
            *
            *******************************************************************************/
            void LedPwm2_ClearFIFO(void) 
            {
                while(0u != (LedPwm2_ReadStatusRegister() & LedPwm2_STATUS_FIFONEMPTY))
                {
                    (void)LedPwm2_ReadCapture();
                }
            }

        #endif /* LedPwm2_UseStatus */

#endif /* !LedPwm2_UsingFixedFunction */


/*******************************************************************************
* Function Name: LedPwm2_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0 
*           will result in the counter remaining at zero.
*
* Return: 
*  None
*
*******************************************************************************/
void LedPwm2_WritePeriod(uint8 period) 
{
    #if(LedPwm2_UsingFixedFunction)
        CY_SET_REG16(LedPwm2_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(LedPwm2_PERIOD_LSB_PTR, period);
    #endif /* (LedPwm2_UsingFixedFunction) */
}

#if (LedPwm2_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LedPwm2_WriteCompare
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock. 
    *  The compare output will be driven high when the present counter value is 
    *  compared to the compare value based on the compare mode defined in 
    *  Dither Mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void LedPwm2_WriteCompare(uint8 compare) \
                                       
    {	
		#if(LedPwm2_UsingFixedFunction)
			CY_SET_REG16(LedPwm2_COMPARE1_LSB_PTR, (uint16)compare);
		#else
	        CY_SET_REG8(LedPwm2_COMPARE1_LSB_PTR, compare);	
		#endif /* (LedPwm2_UsingFixedFunction) */
        
        #if (LedPwm2_PWMMode == LedPwm2__B_PWM__DITHER)
            #if(LedPwm2_UsingFixedFunction)
    			CY_SET_REG16(LedPwm2_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
    		#else
    	        CY_SET_REG8(LedPwm2_COMPARE2_LSB_PTR, (compare + 1u));	
    		#endif /* (LedPwm2_UsingFixedFunction) */
        #endif /* (LedPwm2_PWMMode == LedPwm2__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: LedPwm2_WriteCompare1
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will 
    *  reflect the new value on the next UDB clock.  The compare output will be 
    *  driven high when the present counter value is less than or less than or 
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void LedPwm2_WriteCompare1(uint8 compare) \
                                        
    {
        #if(LedPwm2_UsingFixedFunction)
            CY_SET_REG16(LedPwm2_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(LedPwm2_COMPARE1_LSB_PTR, compare);
        #endif /* (LedPwm2_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: LedPwm2_WriteCompare2
    ********************************************************************************
    * 
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.  
    *  The compare output will reflect the new value on the next UDB clock.  
    *  The compare output will be driven high when the present counter value is 
    *  less than or less than or equal to the compare register, depending on the 
    *  mode.
    *
    * Parameters:  
    *  compare:  New compare value.  
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void LedPwm2_WriteCompare2(uint8 compare) \
                                        
    {
        #if(LedPwm2_UsingFixedFunction)
            CY_SET_REG16(LedPwm2_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(LedPwm2_COMPARE2_LSB_PTR, compare);
        #endif /* (LedPwm2_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (LedPwm2_DeadBandUsed)


    /*******************************************************************************
    * Function Name: LedPwm2_WriteDeadTime
    ********************************************************************************
    * 
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:  
    *  deadtime:  Number of counts for dead time 
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void LedPwm2_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!LedPwm2_DeadBand2_4)
            CY_SET_REG8(LedPwm2_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */        
            /* Clear existing data */
            LedPwm2_DEADBAND_COUNT &= ((uint8)(~LedPwm2_DEADBAND_COUNT_MASK));
            
            /* Set new dead time */
            #if(LedPwm2_DEADBAND_COUNT_SHIFT)        
                LedPwm2_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << LedPwm2_DEADBAND_COUNT_SHIFT)) & 
                                                    LedPwm2_DEADBAND_COUNT_MASK;
            #else
                LedPwm2_DEADBAND_COUNT |= deadtime & LedPwm2_DEADBAND_COUNT_MASK;        
            #endif /* (LedPwm2_DEADBAND_COUNT_SHIFT) */
        
        #endif /* (!LedPwm2_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: LedPwm2_ReadDeadTime
    ********************************************************************************
    * 
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 LedPwm2_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!LedPwm2_DeadBand2_4)
            return (CY_GET_REG8(LedPwm2_DEADBAND_COUNT_PTR));
        #else
        
            /* Otherwise the data has to be masked and offset */
            #if(LedPwm2_DEADBAND_COUNT_SHIFT)      
                return ((uint8)(((uint8)(LedPwm2_DEADBAND_COUNT & LedPwm2_DEADBAND_COUNT_MASK)) >> 
                                                                           LedPwm2_DEADBAND_COUNT_SHIFT));
            #else
                return (LedPwm2_DEADBAND_COUNT & LedPwm2_DEADBAND_COUNT_MASK);
            #endif /* (LedPwm2_DEADBAND_COUNT_SHIFT) */
        #endif /* (!LedPwm2_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (LedPwm2_UseStatus || LedPwm2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LedPwm2_SetInterruptMode
    ********************************************************************************
    * 
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt 
    *  source status register.
    *
    * Parameters:  
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled 
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void LedPwm2_SetInterruptMode(uint8 interruptMode)  
    {
    	CY_SET_REG8(LedPwm2_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: LedPwm2_ReadStatusRegister
    ********************************************************************************
    * 
    * Summary:
    *  This function returns the current state of the status register. 
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 LedPwm2_ReadStatusRegister(void)   
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(LedPwm2_STATUS_PTR);
    	return (result);
    }

#endif /* (LedPwm2_UseStatus || LedPwm2_UsingFixedFunction) */


#if (LedPwm2_UseControl)


    /*******************************************************************************
    * Function Name: LedPwm2_ReadControlRegister
    ********************************************************************************
    * 
    * Summary:
    *  Returns the current state of the control register. This API is available 
    *  only if the control register is not removed.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  uint8 : Current control register value
    *
    *******************************************************************************/    
    uint8 LedPwm2_ReadControlRegister(void) 
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(LedPwm2_CONTROL_PTR);
    	return (result);
    }


    /*******************************************************************************
    * Function Name: LedPwm2_WriteControlRegister
    ********************************************************************************
    * 
    * Summary:
    *  Sets the bit field of the control register. This API is available only if 
    *  the control register is not removed.
    *
    * Parameters:  
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return: 
    *  None
    *
    *******************************************************************************/  
    void LedPwm2_WriteControlRegister(uint8 control) 
    {
    	CY_SET_REG8(LedPwm2_CONTROL_PTR, control);
    }
	
#endif /* (LedPwm2_UseControl) */


#if (!LedPwm2_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LedPwm2_ReadCapture
    ********************************************************************************
    * 
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/  
    uint8 LedPwm2_ReadCapture(void)  
    {
    	return (CY_GET_REG8(LedPwm2_CAPTURE_LSB_PTR));
    }
	
#endif /* (!LedPwm2_UsingFixedFunction) */


#if (LedPwm2_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LedPwm2_ReadCompare
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is 
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/  
    uint8 LedPwm2_ReadCompare(void)  
    {
		#if(LedPwm2_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(LedPwm2_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(LedPwm2_COMPARE1_LSB_PTR));
        #endif /* (LedPwm2_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: LedPwm2_ReadCompare1
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/  
    uint8 LedPwm2_ReadCompare1(void) 
    {
		return (CY_GET_REG8(LedPwm2_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: LedPwm2_ReadCompare2
    ********************************************************************************
    * 
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/  
    uint8 LedPwm2_ReadCompare2(void)  
    {
		return (CY_GET_REG8(LedPwm2_COMPARE2_LSB_PTR));
    }

#endif /* (LedPwm2_UseOneCompareMode) */


/*******************************************************************************
* Function Name: LedPwm2_ReadPeriod
********************************************************************************
* 
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:  
*  None
*
* Return: 
*  uint8/16: Period value
*
*******************************************************************************/ 
uint8 LedPwm2_ReadPeriod(void) 
{
	#if(LedPwm2_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(LedPwm2_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(LedPwm2_PERIOD_LSB_PTR));
    #endif /* (LedPwm2_UsingFixedFunction) */
}

#if ( LedPwm2_KillModeMinTime)


    /*******************************************************************************
    * Function Name: LedPwm2_WriteKillTime
    ********************************************************************************
    * 
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode 
    *  is set to Minimum Time.
    *
    * Parameters:  
    *  uint8: Minimum Time kill counts
    *
    * Return: 
    *  None
    *
    *******************************************************************************/ 
    void LedPwm2_WriteKillTime(uint8 killtime) 
    {
    	CY_SET_REG8(LedPwm2_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: LedPwm2_ReadKillTime
    ********************************************************************************
    * 
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set 
    *  to Minimum Time.
    *
    * Parameters:  
    *  None
    *
    * Return: 
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/ 
    uint8 LedPwm2_ReadKillTime(void) 
    {
    	return (CY_GET_REG8(LedPwm2_KILLMODEMINTIME_PTR));
    }

#endif /* ( LedPwm2_KillModeMinTime) */

/* [] END OF FILE */
