/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <`$INSTANCE_NAME`.h>

#if !defined(`$INSTANCE_NAME`__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START `$INSTANCE_NAME`_intc` */
    
    
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    /* For all we know the interrupt is active. */
    `$INSTANCE_NAME`_Disable();

    /* Set the ISR to point to the `$INSTANCE_NAME` Interrupt. */
    `$INSTANCE_NAME`_SetVector(&`$INSTANCE_NAME`_Interrupt);

    /* Set the priority. */
    `$INSTANCE_NAME`_SetPriority((uint8)`$INSTANCE_NAME`_INTC_PRIOR_NUMBER);

    /* Enable it. */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    `$INSTANCE_NAME`_Disable();

    /* Set the ISR to point to the `$INSTANCE_NAME` Interrupt. */
    `$INSTANCE_NAME`_SetVector(address);

    /* Set the priority. */
    `$INSTANCE_NAME`_SetPriority((uint8)`$INSTANCE_NAME`_INTC_PRIOR_NUMBER);

    /* Enable it. */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    /* Disable this interrupt. */
    `$INSTANCE_NAME`_Disable();

    /* Set the ISR to point to the passive one. */
    `$INSTANCE_NAME`_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for `$INSTANCE_NAME`.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_Interrupt` */



    /* `#END` */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling `$INSTANCE_NAME`_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use `$INSTANCE_NAME`_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + `$INSTANCE_NAME`__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress `$INSTANCE_NAME`_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + `$INSTANCE_NAME`__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling `$INSTANCE_NAME`_Start
*   or `$INSTANCE_NAME`_StartEx will override any effect this method would 
*   have had. This method should only be called after `$INSTANCE_NAME`_Start or 
*   `$INSTANCE_NAME`_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((`$INSTANCE_NAME`__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *`$INSTANCE_NAME`_INTC_PRIOR = (*`$INSTANCE_NAME`_INTC_PRIOR & (uint32)(~`$INSTANCE_NAME`__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((`$INSTANCE_NAME`__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*`$INSTANCE_NAME`_INTC_PRIOR & `$INSTANCE_NAME`__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    /* Enable the general interrupt. */
    *`$INSTANCE_NAME`_INTC_SET_EN = `$INSTANCE_NAME`__INTC_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*`$INSTANCE_NAME`_INTC_SET_EN & (uint32)`$INSTANCE_NAME`__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Disable(void)
{
    /* Disable the general interrupt. */
    *`$INSTANCE_NAME`_INTC_CLR_EN = `$INSTANCE_NAME`__INTC_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPending(void)
{
    *`$INSTANCE_NAME`_INTC_SET_PD = `$INSTANCE_NAME`__INTC_MASK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearPending(void)
{
    *`$INSTANCE_NAME`_INTC_CLR_PD = `$INSTANCE_NAME`__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
