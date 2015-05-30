/*******************************************************************************
* File Name: RightFront_Rev.c  
* Version 2.5
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RightFront_Rev.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 RightFront_Rev__PORT == 15 && ((RightFront_Rev__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: RightFront_Rev_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void RightFront_Rev_Write(uint8 value) 
{
    uint8 staticBits = (RightFront_Rev_DR & (uint8)(~RightFront_Rev_MASK));
    RightFront_Rev_DR = staticBits | ((uint8)(value << RightFront_Rev_SHIFT) & RightFront_Rev_MASK);
}


/*******************************************************************************
* Function Name: RightFront_Rev_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RightFront_Rev_DM_STRONG     Strong Drive 
*  RightFront_Rev_DM_OD_HI      Open Drain, Drives High 
*  RightFront_Rev_DM_OD_LO      Open Drain, Drives Low 
*  RightFront_Rev_DM_RES_UP     Resistive Pull Up 
*  RightFront_Rev_DM_RES_DWN    Resistive Pull Down 
*  RightFront_Rev_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RightFront_Rev_DM_DIG_HIZ    High Impedance Digital 
*  RightFront_Rev_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RightFront_Rev_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RightFront_Rev_0, mode);
}


/*******************************************************************************
* Function Name: RightFront_Rev_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RightFront_Rev_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RightFront_Rev_Read(void) 
{
    return (RightFront_Rev_PS & RightFront_Rev_MASK) >> RightFront_Rev_SHIFT;
}


/*******************************************************************************
* Function Name: RightFront_Rev_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RightFront_Rev_ReadDataReg(void) 
{
    return (RightFront_Rev_DR & RightFront_Rev_MASK) >> RightFront_Rev_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RightFront_Rev_INTSTAT) 

    /*******************************************************************************
    * Function Name: RightFront_Rev_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RightFront_Rev_ClearInterrupt(void) 
    {
        return (RightFront_Rev_INTSTAT & RightFront_Rev_MASK) >> RightFront_Rev_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
