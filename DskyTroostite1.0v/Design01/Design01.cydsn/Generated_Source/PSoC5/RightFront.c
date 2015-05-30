/*******************************************************************************
* File Name: RightFront.c  
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
#include "RightFront.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 RightFront__PORT == 15 && ((RightFront__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: RightFront_Write
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
void RightFront_Write(uint8 value) 
{
    uint8 staticBits = (RightFront_DR & (uint8)(~RightFront_MASK));
    RightFront_DR = staticBits | ((uint8)(value << RightFront_SHIFT) & RightFront_MASK);
}


/*******************************************************************************
* Function Name: RightFront_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RightFront_DM_STRONG     Strong Drive 
*  RightFront_DM_OD_HI      Open Drain, Drives High 
*  RightFront_DM_OD_LO      Open Drain, Drives Low 
*  RightFront_DM_RES_UP     Resistive Pull Up 
*  RightFront_DM_RES_DWN    Resistive Pull Down 
*  RightFront_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RightFront_DM_DIG_HIZ    High Impedance Digital 
*  RightFront_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RightFront_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RightFront_0, mode);
}


/*******************************************************************************
* Function Name: RightFront_Read
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
*  Macro RightFront_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RightFront_Read(void) 
{
    return (RightFront_PS & RightFront_MASK) >> RightFront_SHIFT;
}


/*******************************************************************************
* Function Name: RightFront_ReadDataReg
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
uint8 RightFront_ReadDataReg(void) 
{
    return (RightFront_DR & RightFront_MASK) >> RightFront_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RightFront_INTSTAT) 

    /*******************************************************************************
    * Function Name: RightFront_ClearInterrupt
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
    uint8 RightFront_ClearInterrupt(void) 
    {
        return (RightFront_INTSTAT & RightFront_MASK) >> RightFront_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
