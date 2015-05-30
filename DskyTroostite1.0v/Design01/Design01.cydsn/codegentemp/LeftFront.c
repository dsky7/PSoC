/*******************************************************************************
* File Name: LeftFront.c  
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
#include "LeftFront.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LeftFront__PORT == 15 && ((LeftFront__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LeftFront_Write
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
void LeftFront_Write(uint8 value) 
{
    uint8 staticBits = (LeftFront_DR & (uint8)(~LeftFront_MASK));
    LeftFront_DR = staticBits | ((uint8)(value << LeftFront_SHIFT) & LeftFront_MASK);
}


/*******************************************************************************
* Function Name: LeftFront_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LeftFront_DM_STRONG     Strong Drive 
*  LeftFront_DM_OD_HI      Open Drain, Drives High 
*  LeftFront_DM_OD_LO      Open Drain, Drives Low 
*  LeftFront_DM_RES_UP     Resistive Pull Up 
*  LeftFront_DM_RES_DWN    Resistive Pull Down 
*  LeftFront_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LeftFront_DM_DIG_HIZ    High Impedance Digital 
*  LeftFront_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LeftFront_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LeftFront_0, mode);
}


/*******************************************************************************
* Function Name: LeftFront_Read
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
*  Macro LeftFront_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LeftFront_Read(void) 
{
    return (LeftFront_PS & LeftFront_MASK) >> LeftFront_SHIFT;
}


/*******************************************************************************
* Function Name: LeftFront_ReadDataReg
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
uint8 LeftFront_ReadDataReg(void) 
{
    return (LeftFront_DR & LeftFront_MASK) >> LeftFront_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LeftFront_INTSTAT) 

    /*******************************************************************************
    * Function Name: LeftFront_ClearInterrupt
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
    uint8 LeftFront_ClearInterrupt(void) 
    {
        return (LeftFront_INTSTAT & LeftFront_MASK) >> LeftFront_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
