/*******************************************************************************
* File Name: MotorPwmRight.c  
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
#include "MotorPwmRight.h"

uint8 MotorPwmRight_initVar = 0u;


/*******************************************************************************
* Function Name: MotorPwmRight_Start
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
*  MotorPwmRight_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MotorPwmRight_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MotorPwmRight_initVar == 0u)
    {
        MotorPwmRight_Init();
        MotorPwmRight_initVar = 1u;
    }
    MotorPwmRight_Enable();

}


/*******************************************************************************
* Function Name: MotorPwmRight_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  MotorPwmRight_Start().
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void MotorPwmRight_Init(void) 
{
    #if (MotorPwmRight_UsingFixedFunction || MotorPwmRight_UseControl)
        uint8 ctrl;
    #endif /* (MotorPwmRight_UsingFixedFunction || MotorPwmRight_UseControl) */
    
    #if(!MotorPwmRight_UsingFixedFunction) 
        #if(MotorPwmRight_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MotorPwmRight_interruptState;
        #endif /* (MotorPwmRight_UseStatus) */
    #endif /* (!MotorPwmRight_UsingFixedFunction) */
    
    #if (MotorPwmRight_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MotorPwmRight_CONTROL |= MotorPwmRight_CFG0_MODE;
        #if (MotorPwmRight_DeadBand2_4)
            MotorPwmRight_CONTROL |= MotorPwmRight_CFG0_DB;
        #endif /* (MotorPwmRight_DeadBand2_4) */
                
        ctrl = MotorPwmRight_CONTROL3 & ((uint8 )(~MotorPwmRight_CTRL_CMPMODE1_MASK));
        MotorPwmRight_CONTROL3 = ctrl | MotorPwmRight_DEFAULT_COMPARE1_MODE;
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MotorPwmRight_RT1 &= ((uint8)(~MotorPwmRight_RT1_MASK));
        MotorPwmRight_RT1 |= MotorPwmRight_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        MotorPwmRight_RT1 &= ((uint8)(~MotorPwmRight_SYNCDSI_MASK));
        MotorPwmRight_RT1 |= MotorPwmRight_SYNCDSI_EN;
       
    #elif (MotorPwmRight_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MotorPwmRight_CONTROL & ((uint8)(~MotorPwmRight_CTRL_CMPMODE2_MASK)) & ((uint8)(~MotorPwmRight_CTRL_CMPMODE1_MASK));
        MotorPwmRight_CONTROL = ctrl | MotorPwmRight_DEFAULT_COMPARE2_MODE | 
                                   MotorPwmRight_DEFAULT_COMPARE1_MODE;
    #endif /* (MotorPwmRight_UsingFixedFunction) */
        
    #if (!MotorPwmRight_UsingFixedFunction)
        #if (MotorPwmRight_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MotorPwmRight_AUX_CONTROLDP0 |= (MotorPwmRight_AUX_CTRL_FIFO0_CLR);
        #else /* (MotorPwmRight_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MotorPwmRight_AUX_CONTROLDP0 |= (MotorPwmRight_AUX_CTRL_FIFO0_CLR);
            MotorPwmRight_AUX_CONTROLDP1 |= (MotorPwmRight_AUX_CTRL_FIFO0_CLR);
        #endif /* (MotorPwmRight_Resolution == 8) */

        MotorPwmRight_WriteCounter(MotorPwmRight_INIT_PERIOD_VALUE);
    #endif /* (!MotorPwmRight_UsingFixedFunction) */
        
    MotorPwmRight_WritePeriod(MotorPwmRight_INIT_PERIOD_VALUE);

        #if (MotorPwmRight_UseOneCompareMode)
            MotorPwmRight_WriteCompare(MotorPwmRight_INIT_COMPARE_VALUE1);
        #else
            MotorPwmRight_WriteCompare1(MotorPwmRight_INIT_COMPARE_VALUE1);
            MotorPwmRight_WriteCompare2(MotorPwmRight_INIT_COMPARE_VALUE2);
        #endif /* (MotorPwmRight_UseOneCompareMode) */
        
        #if (MotorPwmRight_KillModeMinTime)
            MotorPwmRight_WriteKillTime(MotorPwmRight_MinimumKillTime);
        #endif /* (MotorPwmRight_KillModeMinTime) */
        
        #if (MotorPwmRight_DeadBandUsed)
            MotorPwmRight_WriteDeadTime(MotorPwmRight_INIT_DEAD_TIME);
        #endif /* (MotorPwmRight_DeadBandUsed) */

    #if (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction)
        MotorPwmRight_SetInterruptMode(MotorPwmRight_INIT_INTERRUPTS_MODE);
    #endif /* (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction) */
        
    #if (MotorPwmRight_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MotorPwmRight_GLOBAL_ENABLE |= MotorPwmRight_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MotorPwmRight_CONTROL2 |= MotorPwmRight_CTRL2_IRQ_SEL;
    #else
        #if(MotorPwmRight_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MotorPwmRight_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MotorPwmRight_STATUS_AUX_CTRL |= MotorPwmRight_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(MotorPwmRight_interruptState);
            
            /* Clear the FIFO to enable the MotorPwmRight_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MotorPwmRight_ClearFIFO();
        #endif /* (MotorPwmRight_UseStatus) */
    #endif /* (MotorPwmRight_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmRight_Enable
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
void MotorPwmRight_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MotorPwmRight_UsingFixedFunction)
        MotorPwmRight_GLOBAL_ENABLE |= MotorPwmRight_BLOCK_EN_MASK;
        MotorPwmRight_GLOBAL_STBY_ENABLE |= MotorPwmRight_BLOCK_STBY_EN_MASK;
    #endif /* (MotorPwmRight_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (MotorPwmRight_UseControl || MotorPwmRight_UsingFixedFunction)
        MotorPwmRight_CONTROL |= MotorPwmRight_CTRL_ENABLE;
    #endif /* (MotorPwmRight_UseControl || MotorPwmRight_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmRight_Stop
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
void MotorPwmRight_Stop(void) 
{
    #if (MotorPwmRight_UseControl || MotorPwmRight_UsingFixedFunction)
        MotorPwmRight_CONTROL &= ((uint8)(~MotorPwmRight_CTRL_ENABLE));
    #endif /* (MotorPwmRight_UseControl || MotorPwmRight_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (MotorPwmRight_UsingFixedFunction)
        MotorPwmRight_GLOBAL_ENABLE &= ((uint8)(~MotorPwmRight_BLOCK_EN_MASK));
        MotorPwmRight_GLOBAL_STBY_ENABLE &= ((uint8)(~MotorPwmRight_BLOCK_STBY_EN_MASK));
    #endif /* (MotorPwmRight_UsingFixedFunction) */
}


#if (MotorPwmRight_UseOneCompareMode)
	#if (MotorPwmRight_CompareMode1SW)


		/*******************************************************************************
		* Function Name: MotorPwmRight_SetCompareMode
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
		void MotorPwmRight_SetCompareMode(uint8 comparemode) 
		{
		    #if(MotorPwmRight_UsingFixedFunction)
            
                #if(0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmRight_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT) */
            
	            MotorPwmRight_CONTROL3 &= ((uint8)(~MotorPwmRight_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
	            MotorPwmRight_CONTROL3 |= comparemodemasked;     
		                
		    #elif (MotorPwmRight_UseControl)
		        
                #if(0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << MotorPwmRight_CTRL_CMPMODE1_SHIFT)) & 
    		                                    MotorPwmRight_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & MotorPwmRight_CTRL_CMPMODE1_MASK;                
                #endif /* (0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT) */
                
                #if(0 != MotorPwmRight_CTRL_CMPMODE2_SHIFT)                            
    		        uint8 comparemode2masked = ((uint8)((uint8)comparemode << MotorPwmRight_CTRL_CMPMODE2_SHIFT)) & 
    		                                   MotorPwmRight_CTRL_CMPMODE2_MASK;
                #else
    		        uint8 comparemode2masked = comparemode & MotorPwmRight_CTRL_CMPMODE2_MASK;                
                #endif /* (0 != MotorPwmRight_CTRL_CMPMODE2_SHIFT) */
                
		        /*Clear existing mode */
		        MotorPwmRight_CONTROL &= ((uint8)(~(MotorPwmRight_CTRL_CMPMODE1_MASK | MotorPwmRight_CTRL_CMPMODE2_MASK))); 
		        MotorPwmRight_CONTROL |= (comparemode1masked | comparemode2masked);
		        
		    #else
		        uint8 temp = comparemode;
		    #endif /* (MotorPwmRight_UsingFixedFunction) */
		}
	#endif /* MotorPwmRight_CompareMode1SW */

#else /* UseOneCompareMode */

	#if (MotorPwmRight_CompareMode1SW)


		/*******************************************************************************
		* Function Name: MotorPwmRight_SetCompareMode1
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
		void MotorPwmRight_SetCompareMode1(uint8 comparemode) 
		{
		    #if(0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmRight_CTRL_CMPMODE1_SHIFT)) & 
    		                               MotorPwmRight_CTRL_CMPMODE1_MASK;
		    #else
                uint8 comparemodemasked = comparemode & MotorPwmRight_CTRL_CMPMODE1_MASK;                
            #endif /* (0 != MotorPwmRight_CTRL_CMPMODE1_SHIFT) */
                   
		    #if (MotorPwmRight_UseControl)
		        MotorPwmRight_CONTROL &= ((uint8)(~MotorPwmRight_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
		        MotorPwmRight_CONTROL |= comparemodemasked;
		    #endif /* (MotorPwmRight_UseControl) */
		}
	#endif /* MotorPwmRight_CompareMode1SW */

#if (MotorPwmRight_CompareMode2SW)


    /*******************************************************************************
    * Function Name: MotorPwmRight_SetCompareMode2
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
    void MotorPwmRight_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != MotorPwmRight_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmRight_CTRL_CMPMODE2_SHIFT)) & 
                                                 MotorPwmRight_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & MotorPwmRight_CTRL_CMPMODE2_MASK;            
        #endif /* (0 != MotorPwmRight_CTRL_CMPMODE2_SHIFT) */
        
        #if (MotorPwmRight_UseControl)
            MotorPwmRight_CONTROL &= ((uint8)(~MotorPwmRight_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            MotorPwmRight_CONTROL |= comparemodemasked;
        #endif /* (MotorPwmRight_UseControl) */
    }
    #endif /*MotorPwmRight_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!MotorPwmRight_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteCounter
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
    void MotorPwmRight_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(MotorPwmRight_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadCounter
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
    uint8 MotorPwmRight_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
        (void)MotorPwmRight_COUNTERCAP_LSB;
        
        /* Read the data from the FIFO (or capture register for Fixed Function)*/
        return (CY_GET_REG8(MotorPwmRight_CAPTURE_LSB_PTR));
    }

        #if (MotorPwmRight_UseStatus)


            /*******************************************************************************
            * Function Name: MotorPwmRight_ClearFIFO
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
            void MotorPwmRight_ClearFIFO(void) 
            {
                while(0u != (MotorPwmRight_ReadStatusRegister() & MotorPwmRight_STATUS_FIFONEMPTY))
                {
                    (void)MotorPwmRight_ReadCapture();
                }
            }

        #endif /* MotorPwmRight_UseStatus */

#endif /* !MotorPwmRight_UsingFixedFunction */


/*******************************************************************************
* Function Name: MotorPwmRight_WritePeriod
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
void MotorPwmRight_WritePeriod(uint8 period) 
{
    #if(MotorPwmRight_UsingFixedFunction)
        CY_SET_REG16(MotorPwmRight_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(MotorPwmRight_PERIOD_LSB_PTR, period);
    #endif /* (MotorPwmRight_UsingFixedFunction) */
}

#if (MotorPwmRight_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteCompare
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
    void MotorPwmRight_WriteCompare(uint8 compare) \
                                       
    {	
		#if(MotorPwmRight_UsingFixedFunction)
			CY_SET_REG16(MotorPwmRight_COMPARE1_LSB_PTR, (uint16)compare);
		#else
	        CY_SET_REG8(MotorPwmRight_COMPARE1_LSB_PTR, compare);	
		#endif /* (MotorPwmRight_UsingFixedFunction) */
        
        #if (MotorPwmRight_PWMMode == MotorPwmRight__B_PWM__DITHER)
            #if(MotorPwmRight_UsingFixedFunction)
    			CY_SET_REG16(MotorPwmRight_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
    		#else
    	        CY_SET_REG8(MotorPwmRight_COMPARE2_LSB_PTR, (compare + 1u));	
    		#endif /* (MotorPwmRight_UsingFixedFunction) */
        #endif /* (MotorPwmRight_PWMMode == MotorPwmRight__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteCompare1
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
    void MotorPwmRight_WriteCompare1(uint8 compare) \
                                        
    {
        #if(MotorPwmRight_UsingFixedFunction)
            CY_SET_REG16(MotorPwmRight_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorPwmRight_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorPwmRight_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteCompare2
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
    void MotorPwmRight_WriteCompare2(uint8 compare) \
                                        
    {
        #if(MotorPwmRight_UsingFixedFunction)
            CY_SET_REG16(MotorPwmRight_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(MotorPwmRight_COMPARE2_LSB_PTR, compare);
        #endif /* (MotorPwmRight_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (MotorPwmRight_DeadBandUsed)


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteDeadTime
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
    void MotorPwmRight_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!MotorPwmRight_DeadBand2_4)
            CY_SET_REG8(MotorPwmRight_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */        
            /* Clear existing data */
            MotorPwmRight_DEADBAND_COUNT &= ((uint8)(~MotorPwmRight_DEADBAND_COUNT_MASK));
            
            /* Set new dead time */
            #if(MotorPwmRight_DEADBAND_COUNT_SHIFT)        
                MotorPwmRight_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << MotorPwmRight_DEADBAND_COUNT_SHIFT)) & 
                                                    MotorPwmRight_DEADBAND_COUNT_MASK;
            #else
                MotorPwmRight_DEADBAND_COUNT |= deadtime & MotorPwmRight_DEADBAND_COUNT_MASK;        
            #endif /* (MotorPwmRight_DEADBAND_COUNT_SHIFT) */
        
        #endif /* (!MotorPwmRight_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadDeadTime
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
    uint8 MotorPwmRight_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!MotorPwmRight_DeadBand2_4)
            return (CY_GET_REG8(MotorPwmRight_DEADBAND_COUNT_PTR));
        #else
        
            /* Otherwise the data has to be masked and offset */
            #if(MotorPwmRight_DEADBAND_COUNT_SHIFT)      
                return ((uint8)(((uint8)(MotorPwmRight_DEADBAND_COUNT & MotorPwmRight_DEADBAND_COUNT_MASK)) >> 
                                                                           MotorPwmRight_DEADBAND_COUNT_SHIFT));
            #else
                return (MotorPwmRight_DEADBAND_COUNT & MotorPwmRight_DEADBAND_COUNT_MASK);
            #endif /* (MotorPwmRight_DEADBAND_COUNT_SHIFT) */
        #endif /* (!MotorPwmRight_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmRight_SetInterruptMode
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
    void MotorPwmRight_SetInterruptMode(uint8 interruptMode)  
    {
    	CY_SET_REG8(MotorPwmRight_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadStatusRegister
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
    uint8 MotorPwmRight_ReadStatusRegister(void)   
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(MotorPwmRight_STATUS_PTR);
    	return (result);
    }

#endif /* (MotorPwmRight_UseStatus || MotorPwmRight_UsingFixedFunction) */


#if (MotorPwmRight_UseControl)


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadControlRegister
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
    uint8 MotorPwmRight_ReadControlRegister(void) 
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(MotorPwmRight_CONTROL_PTR);
    	return (result);
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteControlRegister
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
    void MotorPwmRight_WriteControlRegister(uint8 control) 
    {
    	CY_SET_REG8(MotorPwmRight_CONTROL_PTR, control);
    }
	
#endif /* (MotorPwmRight_UseControl) */


#if (!MotorPwmRight_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadCapture
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
    uint8 MotorPwmRight_ReadCapture(void)  
    {
    	return (CY_GET_REG8(MotorPwmRight_CAPTURE_LSB_PTR));
    }
	
#endif /* (!MotorPwmRight_UsingFixedFunction) */


#if (MotorPwmRight_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadCompare
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
    uint8 MotorPwmRight_ReadCompare(void)  
    {
		#if(MotorPwmRight_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(MotorPwmRight_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(MotorPwmRight_COMPARE1_LSB_PTR));
        #endif /* (MotorPwmRight_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadCompare1
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
    uint8 MotorPwmRight_ReadCompare1(void) 
    {
		return (CY_GET_REG8(MotorPwmRight_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadCompare2
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
    uint8 MotorPwmRight_ReadCompare2(void)  
    {
		return (CY_GET_REG8(MotorPwmRight_COMPARE2_LSB_PTR));
    }

#endif /* (MotorPwmRight_UseOneCompareMode) */


/*******************************************************************************
* Function Name: MotorPwmRight_ReadPeriod
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
uint8 MotorPwmRight_ReadPeriod(void) 
{
	#if(MotorPwmRight_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(MotorPwmRight_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(MotorPwmRight_PERIOD_LSB_PTR));
    #endif /* (MotorPwmRight_UsingFixedFunction) */
}

#if ( MotorPwmRight_KillModeMinTime)


    /*******************************************************************************
    * Function Name: MotorPwmRight_WriteKillTime
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
    void MotorPwmRight_WriteKillTime(uint8 killtime) 
    {
    	CY_SET_REG8(MotorPwmRight_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: MotorPwmRight_ReadKillTime
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
    uint8 MotorPwmRight_ReadKillTime(void) 
    {
    	return (CY_GET_REG8(MotorPwmRight_KILLMODEMINTIME_PTR));
    }

#endif /* ( MotorPwmRight_KillModeMinTime) */

/* [] END OF FILE */
