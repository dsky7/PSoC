/*******************************************************************************
* File Name: LeftRear.c  
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
#include "LeftRear.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LeftRear__PORT == 15 && ((LeftRear__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LeftRear_Write
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
void LeftRear_Write(uint8 value) 
{
    uint8 staticBits = (LeftRear_DR & (uint8)(~LeftRear_MASK));
    LeftRear_DR = staticBits | ((uint8)(value << LeftRear_SHIFT) & LeftRear_MASK);
}


/*******************************************************************************
* Function Name: LeftRear_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LeftRear_DM_STRONG     Strong Drive 
*  LeftRear_DM_OD_HI      Open Drain, Drives High 
*  LeftRear_DM_OD_LO      Open Drain, Drives Low 
*  LeftRear_DM_RES_UP     Resistive Pull Up 
*  LeftRear_DM_RES_DWN    Resistive Pull Down 
*  LeftRear_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LeftRear_DM_DIG_HIZ    High Impedance Digital 
*  LeftRear_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LeftRear_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LeftRear_0, mode);
}


/*******************************************************************************
* Function Name: LeftRear_Read
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
*  Macro LeftRear_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LeftRear_Read(void) 
{
    return (LeftRear_PS & LeftRear_MASK) >> LeftRear_SHIFT;
}


/*******************************************************************************
* Function Name: LeftRear_ReadDataReg
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
uint8 LeftRear_ReadDataReg(void) 
{
    return (LeftRear_DR & LeftRear_MASK) >> LeftRear_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LeftRear_INTSTAT) 

    /*******************************************************************************
    * Function Name: LeftRear_ClearInterrupt
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
    uint8 LeftRear_ClearInterrupt(void) 
    {
        return (LeftRear_INTSTAT & LeftRear_MASK) >> LeftRear_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
