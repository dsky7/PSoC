/*******************************************************************************
* File Name: SPEED_4.c  
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
#include "SPEED_4.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SPEED_4__PORT == 15 && ((SPEED_4__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SPEED_4_Write
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
void SPEED_4_Write(uint8 value) 
{
    uint8 staticBits = (SPEED_4_DR & (uint8)(~SPEED_4_MASK));
    SPEED_4_DR = staticBits | ((uint8)(value << SPEED_4_SHIFT) & SPEED_4_MASK);
}


/*******************************************************************************
* Function Name: SPEED_4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SPEED_4_DM_STRONG     Strong Drive 
*  SPEED_4_DM_OD_HI      Open Drain, Drives High 
*  SPEED_4_DM_OD_LO      Open Drain, Drives Low 
*  SPEED_4_DM_RES_UP     Resistive Pull Up 
*  SPEED_4_DM_RES_DWN    Resistive Pull Down 
*  SPEED_4_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SPEED_4_DM_DIG_HIZ    High Impedance Digital 
*  SPEED_4_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SPEED_4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SPEED_4_0, mode);
}


/*******************************************************************************
* Function Name: SPEED_4_Read
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
*  Macro SPEED_4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SPEED_4_Read(void) 
{
    return (SPEED_4_PS & SPEED_4_MASK) >> SPEED_4_SHIFT;
}


/*******************************************************************************
* Function Name: SPEED_4_ReadDataReg
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
uint8 SPEED_4_ReadDataReg(void) 
{
    return (SPEED_4_DR & SPEED_4_MASK) >> SPEED_4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SPEED_4_INTSTAT) 

    /*******************************************************************************
    * Function Name: SPEED_4_ClearInterrupt
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
    uint8 SPEED_4_ClearInterrupt(void) 
    {
        return (SPEED_4_INTSTAT & SPEED_4_MASK) >> SPEED_4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
