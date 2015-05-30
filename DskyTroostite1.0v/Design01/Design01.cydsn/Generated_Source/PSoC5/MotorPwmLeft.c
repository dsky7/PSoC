/*******************************************************************************
* File Name: MotorPwmLeft.c  
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
#include "MotorPwmLeft.h"

uint8 MotorPwmLeft_initVar = 0u;


/*******************************************************************************
* Function Name: MotorPwmLeft_Start
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
*  MotorPwmLeft_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MotorPwmLeft_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MotorPwmLeft_initVar == 0u)
    {
        MotorPwmLeft_Init();
        MotorPwmLeft_initVar = 1u;
    }
    MotorPwmLeft_Enable();

}


/*******************************************************************************
* Function Name: MotorPwmLeft_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  MotorPwmLeft_Start().
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void MotorPwmLeft_Init(void) 
{
    #if (MotorPwmLeft_UsingFixedFunction || MotorPwmLeft_UseControl)
        uint8 ctrl;
    #endif /* (MotorPwmLeft_UsingFixedFunction || MotorPwmLeft_UseControl) */
    
    #if(!MotorPwmLeft_UsingFixedFunction) 
        #if(MotorPwmLeft_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MotorPwmLeft_interruptState;
        #endif /* (MotorPwmLeft_UseStatus) */
    #endif /* (!MotorPwmLeft_UsingFixedFunction) */
    
    #if (MotorPwmLeft_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MotorPwmLeft_CONTROL |= MotorPwmLeft_CFG0_MODE;
        #if (MotorPwmLeft_DeadBand2_4)
            MotorPwmLeft_CONTROL |= MotorPwmLeft_CFG0_DB;
        #endif /* (MotorPwmLeft_DeadBand2_4) */
                
        ctrl = MotorPwmLeft_CONTROL3 & ((uint8 )(~MotorPwmLeft_CTRL_CMPMODE1_MASK));
        MotorPwmLeft_CONTROL3 = ctrl | MotorPwmLeft_DEFAULT_COMPARE1_MODE;
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MotorPwmLeft_RT1 &= ((uint8)(~MotorPwmLeft_RT1_MASK));
        MotorPwmLeft_RT1 |= MotorPwmLeft_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        MotorPwmLeft_RT1 &= ((uint8)(~MotorPwmLeft_SYNCDSI_MASK));
        MotorPwmLeft_RT1 |= MotorPwmLeft_SYNCDSI_EN;
       
    #elif (MotorPwmLeft_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MotorPwmLeft_CONTROL & ((uint8)(~MotorPwmLeft_CTRL_CMPMODE2_MASK)) & ((uint8)(~MotorPwmLeft_CTRL_CMPMODE1_MASK));
        MotorPwmLeft_CONTROL = ctrl | MotorPwmLeft_DEFAULT_COMPARE2_MODE | 
                                   MotorPwmLeft_DEFAULT_COMPARE1_MODE;
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
        
    #if (!MotorPwmLeft_UsingFixedFunction)
        #if (MotorPwmLeft_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MotorPwmLeft_AUX_CONTROLDP0 |= (MotorPwmLeft_AUX_CTRL_FIFO0_CLR);
        #else /* (MotorPwmLeft_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MotorPwmLeft_AUX_CONTROLDP0 |= (MotorPwmLeft_AUX_CTRL_FIFO0_CLR);
            MotorPwmLeft_AUX_CONTROLDP1 |= (MotorPwmLeft_AUX_CTRL_FIFO0_CLR);
        #endif /* (MotorPwmLeft_Resolution == 8) */

        MotorPwmLeft_WriteCounter(MotorPwmLeft_INIT_PERIOD_VALUE);
    #endif /* (!MotorPwmLeft_UsingFixedFunction) */
        
    MotorPwmLeft_WritePeriod(MotorPwmLeft_INIT_PERIOD_VALUE);

        #if (MotorPwmLeft_UseOneCompareMode)
            MotorPwmLeft_WriteCompare(MotorPwmLeft_INIT_COMPARE_VALUE1);
        #else
            MotorPwmLeft_WriteCompare1(MotorPwmLeft_INIT_COMPARE_VALUE1);
            MotorPwmLeft_WriteCompare2(MotorPwmLeft_INIT_COMPARE_VALUE2);
        #endif /* (MotorPwmLeft_UseOneCompareMode) */
        
        #if (MotorPwmLeft_KillModeMinTime)
            MotorPwmLeft_WriteKillTime(MotorPwmLeft_MinimumKillTime);
        #endif /* (MotorPwmLeft_KillModeMinTime) */
        
        #if (MotorPwmLeft_DeadBandUsed)
            MotorPwmLeft_WriteDeadTime(MotorPwmLeft_INIT_DEAD_TIME);
        #endif /* (MotorPwmLeft_DeadBandUsed) */

    #if (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction)
        MotorPwmLeft_SetInterruptMode(MotorPwmLeft_INIT_INTERRUPTS_MODE);
    #endif /* (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction) */
        
    #if (MotorPwmLeft_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MotorPwmLeft_GLOBAL_ENABLE |= MotorPwmLeft_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MotorPwmLeft_CONTROL2 |= MotorPwmLeft_CTRL2_IRQ_SEL;
    #else
        #if(MotorPwmLeft_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MotorPwmLeft_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MotorPwmLeft_STATUS_AUX_CTRL |= MotorPwmLeft_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(MotorPwmLeft_interruptState);
            
            /* Clear the FIFO to enable the MotorPwmLeft_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MotorPwmLeft_ClearFIFO();
        #endif /* (MotorPwmLeft_UseStatus) */
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmLeft_Enable
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
void MotorPwmLeft_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MotorPwmLeft_UsingFixedFunction)
        MotorPwmLeft_GLOBAL_ENABLE |= MotorPwmLeft_BLOCK_EN_MASK;
        MotorPwmLeft_GLOBAL_STBY_ENABLE |= MotorPwmLeft_BLOCK_STBY_EN_MASK;
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (MotorPwmLeft_UseControl || MotorPwmLeft_UsingFixedFunction)
        MotorPwmLeft_CONTROL |= MotorPwmLeft_CTRL_ENABLE;
    #endif /* (MotorPwmLeft_UseControl || MotorPwmLeft_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPwmLeft_Stop
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
void MotorPwmLeft_Stop(void) 
{
    #if (MotorPwmLeft_UseControl || MotorPwmLeft_UsingFixedFunction)
        MotorPwmLeft_CONTROL &= ((uint8)(~MotorPwmLeft_CTRL_ENABLE));
    #endif /* (MotorPwmLeft_UseControl || MotorPwmLeft_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (MotorPwmLeft_UsingFixedFunction)
        MotorPwmLeft_GLOBAL_ENABLE &= ((uint8)(~MotorPwmLeft_BLOCK_EN_MASK));
        MotorPwmLeft_GLOBAL_STBY_ENABLE &= ((uint8)(~MotorPwmLeft_BLOCK_STBY_EN_MASK));
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
}


#if (MotorPwmLeft_UseOneCompareMode)
	#if (MotorPwmLeft_CompareMode1SW)


		/*******************************************************************************
		* Function Name: MotorPwmLeft_SetCompareMode
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
		void MotorPwmLeft_SetCompareMode(uint8 comparemode) 
		{
		    #if(MotorPwmLeft_UsingFixedFunction)
            
                #if(0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmLeft_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT) */
            
	            MotorPwmLeft_CONTROL3 &= ((uint8)(~MotorPwmLeft_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
	            MotorPwmLeft_CONTROL3 |= comparemodemasked;     
		                
		    #elif (MotorPwmLeft_UseControl)
		        
                #if(0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << MotorPwmLeft_CTRL_CMPMODE1_SHIFT)) & 
    		                                    MotorPwmLeft_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & MotorPwmLeft_CTRL_CMPMODE1_MASK;                
                #endif /* (0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT) */
                
                #if(0 != MotorPwmLeft_CTRL_CMPMODE2_SHIFT)                            
    		        uint8 comparemode2masked = ((uint8)((uint8)comparemode << MotorPwmLeft_CTRL_CMPMODE2_SHIFT)) & 
    		                                   MotorPwmLeft_CTRL_CMPMODE2_MASK;
                #else
    		        uint8 comparemode2masked = comparemode & MotorPwmLeft_CTRL_CMPMODE2_MASK;                
                #endif /* (0 != MotorPwmLeft_CTRL_CMPMODE2_SHIFT) */
                
		        /*Clear existing mode */
		        MotorPwmLeft_CONTROL &= ((uint8)(~(MotorPwmLeft_CTRL_CMPMODE1_MASK | MotorPwmLeft_CTRL_CMPMODE2_MASK))); 
		        MotorPwmLeft_CONTROL |= (comparemode1masked | comparemode2masked);
		        
		    #else
		        uint8 temp = comparemode;
		    #endif /* (MotorPwmLeft_UsingFixedFunction) */
		}
	#endif /* MotorPwmLeft_CompareMode1SW */

#else /* UseOneCompareMode */

	#if (MotorPwmLeft_CompareMode1SW)


		/*******************************************************************************
		* Function Name: MotorPwmLeft_SetCompareMode1
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
		void MotorPwmLeft_SetCompareMode1(uint8 comparemode) 
		{
		    #if(0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmLeft_CTRL_CMPMODE1_SHIFT)) & 
    		                               MotorPwmLeft_CTRL_CMPMODE1_MASK;
		    #else
                uint8 comparemodemasked = comparemode & MotorPwmLeft_CTRL_CMPMODE1_MASK;                
            #endif /* (0 != MotorPwmLeft_CTRL_CMPMODE1_SHIFT) */
                   
		    #if (MotorPwmLeft_UseControl)
		        MotorPwmLeft_CONTROL &= ((uint8)(~MotorPwmLeft_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
		        MotorPwmLeft_CONTROL |= comparemodemasked;
		    #endif /* (MotorPwmLeft_UseControl) */
		}
	#endif /* MotorPwmLeft_CompareMode1SW */

#if (MotorPwmLeft_CompareMode2SW)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_SetCompareMode2
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
    void MotorPwmLeft_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != MotorPwmLeft_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPwmLeft_CTRL_CMPMODE2_SHIFT)) & 
                                                 MotorPwmLeft_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & MotorPwmLeft_CTRL_CMPMODE2_MASK;            
        #endif /* (0 != MotorPwmLeft_CTRL_CMPMODE2_SHIFT) */
        
        #if (MotorPwmLeft_UseControl)
            MotorPwmLeft_CONTROL &= ((uint8)(~MotorPwmLeft_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            MotorPwmLeft_CONTROL |= comparemodemasked;
        #endif /* (MotorPwmLeft_UseControl) */
    }
    #endif /*MotorPwmLeft_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!MotorPwmLeft_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteCounter
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
    void MotorPwmLeft_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(MotorPwmLeft_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadCounter
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
    uint8 MotorPwmLeft_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
        (void)MotorPwmLeft_COUNTERCAP_LSB;
        
        /* Read the data from the FIFO (or capture register for Fixed Function)*/
        return (CY_GET_REG8(MotorPwmLeft_CAPTURE_LSB_PTR));
    }

        #if (MotorPwmLeft_UseStatus)


            /*******************************************************************************
            * Function Name: MotorPwmLeft_ClearFIFO
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
            void MotorPwmLeft_ClearFIFO(void) 
            {
                while(0u != (MotorPwmLeft_ReadStatusRegister() & MotorPwmLeft_STATUS_FIFONEMPTY))
                {
                    (void)MotorPwmLeft_ReadCapture();
                }
            }

        #endif /* MotorPwmLeft_UseStatus */

#endif /* !MotorPwmLeft_UsingFixedFunction */


/*******************************************************************************
* Function Name: MotorPwmLeft_WritePeriod
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
void MotorPwmLeft_WritePeriod(uint8 period) 
{
    #if(MotorPwmLeft_UsingFixedFunction)
        CY_SET_REG16(MotorPwmLeft_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(MotorPwmLeft_PERIOD_LSB_PTR, period);
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
}

#if (MotorPwmLeft_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteCompare
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
    void MotorPwmLeft_WriteCompare(uint8 compare) \
                                       
    {	
		#if(MotorPwmLeft_UsingFixedFunction)
			CY_SET_REG16(MotorPwmLeft_COMPARE1_LSB_PTR, (uint16)compare);
		#else
	        CY_SET_REG8(MotorPwmLeft_COMPARE1_LSB_PTR, compare);	
		#endif /* (MotorPwmLeft_UsingFixedFunction) */
        
        #if (MotorPwmLeft_PWMMode == MotorPwmLeft__B_PWM__DITHER)
            #if(MotorPwmLeft_UsingFixedFunction)
    			CY_SET_REG16(MotorPwmLeft_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
    		#else
    	        CY_SET_REG8(MotorPwmLeft_COMPARE2_LSB_PTR, (compare + 1u));	
    		#endif /* (MotorPwmLeft_UsingFixedFunction) */
        #endif /* (MotorPwmLeft_PWMMode == MotorPwmLeft__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteCompare1
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
    void MotorPwmLeft_WriteCompare1(uint8 compare) \
                                        
    {
        #if(MotorPwmLeft_UsingFixedFunction)
            CY_SET_REG16(MotorPwmLeft_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorPwmLeft_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorPwmLeft_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteCompare2
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
    void MotorPwmLeft_WriteCompare2(uint8 compare) \
                                        
    {
        #if(MotorPwmLeft_UsingFixedFunction)
            CY_SET_REG16(MotorPwmLeft_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(MotorPwmLeft_COMPARE2_LSB_PTR, compare);
        #endif /* (MotorPwmLeft_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (MotorPwmLeft_DeadBandUsed)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteDeadTime
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
    void MotorPwmLeft_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!MotorPwmLeft_DeadBand2_4)
            CY_SET_REG8(MotorPwmLeft_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */        
            /* Clear existing data */
            MotorPwmLeft_DEADBAND_COUNT &= ((uint8)(~MotorPwmLeft_DEADBAND_COUNT_MASK));
            
            /* Set new dead time */
            #if(MotorPwmLeft_DEADBAND_COUNT_SHIFT)        
                MotorPwmLeft_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << MotorPwmLeft_DEADBAND_COUNT_SHIFT)) & 
                                                    MotorPwmLeft_DEADBAND_COUNT_MASK;
            #else
                MotorPwmLeft_DEADBAND_COUNT |= deadtime & MotorPwmLeft_DEADBAND_COUNT_MASK;        
            #endif /* (MotorPwmLeft_DEADBAND_COUNT_SHIFT) */
        
        #endif /* (!MotorPwmLeft_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadDeadTime
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
    uint8 MotorPwmLeft_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!MotorPwmLeft_DeadBand2_4)
            return (CY_GET_REG8(MotorPwmLeft_DEADBAND_COUNT_PTR));
        #else
        
            /* Otherwise the data has to be masked and offset */
            #if(MotorPwmLeft_DEADBAND_COUNT_SHIFT)      
                return ((uint8)(((uint8)(MotorPwmLeft_DEADBAND_COUNT & MotorPwmLeft_DEADBAND_COUNT_MASK)) >> 
                                                                           MotorPwmLeft_DEADBAND_COUNT_SHIFT));
            #else
                return (MotorPwmLeft_DEADBAND_COUNT & MotorPwmLeft_DEADBAND_COUNT_MASK);
            #endif /* (MotorPwmLeft_DEADBAND_COUNT_SHIFT) */
        #endif /* (!MotorPwmLeft_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_SetInterruptMode
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
    void MotorPwmLeft_SetInterruptMode(uint8 interruptMode)  
    {
    	CY_SET_REG8(MotorPwmLeft_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadStatusRegister
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
    uint8 MotorPwmLeft_ReadStatusRegister(void)   
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(MotorPwmLeft_STATUS_PTR);
    	return (result);
    }

#endif /* (MotorPwmLeft_UseStatus || MotorPwmLeft_UsingFixedFunction) */


#if (MotorPwmLeft_UseControl)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadControlRegister
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
    uint8 MotorPwmLeft_ReadControlRegister(void) 
    {
    	uint8 result;
    	
    	result = CY_GET_REG8(MotorPwmLeft_CONTROL_PTR);
    	return (result);
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteControlRegister
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
    void MotorPwmLeft_WriteControlRegister(uint8 control) 
    {
    	CY_SET_REG8(MotorPwmLeft_CONTROL_PTR, control);
    }
	
#endif /* (MotorPwmLeft_UseControl) */


#if (!MotorPwmLeft_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadCapture
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
    uint8 MotorPwmLeft_ReadCapture(void)  
    {
    	return (CY_GET_REG8(MotorPwmLeft_CAPTURE_LSB_PTR));
    }
	
#endif /* (!MotorPwmLeft_UsingFixedFunction) */


#if (MotorPwmLeft_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadCompare
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
    uint8 MotorPwmLeft_ReadCompare(void)  
    {
		#if(MotorPwmLeft_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(MotorPwmLeft_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(MotorPwmLeft_COMPARE1_LSB_PTR));
        #endif /* (MotorPwmLeft_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadCompare1
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
    uint8 MotorPwmLeft_ReadCompare1(void) 
    {
		return (CY_GET_REG8(MotorPwmLeft_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadCompare2
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
    uint8 MotorPwmLeft_ReadCompare2(void)  
    {
		return (CY_GET_REG8(MotorPwmLeft_COMPARE2_LSB_PTR));
    }

#endif /* (MotorPwmLeft_UseOneCompareMode) */


/*******************************************************************************
* Function Name: MotorPwmLeft_ReadPeriod
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
uint8 MotorPwmLeft_ReadPeriod(void) 
{
	#if(MotorPwmLeft_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(MotorPwmLeft_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(MotorPwmLeft_PERIOD_LSB_PTR));
    #endif /* (MotorPwmLeft_UsingFixedFunction) */
}

#if ( MotorPwmLeft_KillModeMinTime)


    /*******************************************************************************
    * Function Name: MotorPwmLeft_WriteKillTime
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
    void MotorPwmLeft_WriteKillTime(uint8 killtime) 
    {
    	CY_SET_REG8(MotorPwmLeft_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: MotorPwmLeft_ReadKillTime
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
    uint8 MotorPwmLeft_ReadKillTime(void) 
    {
    	return (CY_GET_REG8(MotorPwmLeft_KILLMODEMINTIME_PTR));
    }

#endif /* ( MotorPwmLeft_KillModeMinTime) */

/* [] END OF FILE */
