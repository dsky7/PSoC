/*******************************************************************************
* File Name: BUZZER.c  
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
#include "BUZZER.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 BUZZER__PORT == 15 && ((BUZZER__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: BUZZER_Write
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
void BUZZER_Write(uint8 value) 
{
    uint8 staticBits = (BUZZER_DR & (uint8)(~BUZZER_MASK));
    BUZZER_DR = staticBits | ((uint8)(value << BUZZER_SHIFT) & BUZZER_MASK);
}


/*******************************************************************************
* Function Name: BUZZER_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  BUZZER_DM_STRONG     Strong Drive 
*  BUZZER_DM_OD_HI      Open Drain, Drives High 
*  BUZZER_DM_OD_LO      Open Drain, Drives Low 
*  BUZZER_DM_RES_UP     Resistive Pull Up 
*  BUZZER_DM_RES_DWN    Resistive Pull Down 
*  BUZZER_DM_RES_UPDWN  Resistive Pull Up/Down 
*  BUZZER_DM_DIG_HIZ    High Impedance Digital 
*  BUZZER_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void BUZZER_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(BUZZER_0, mode);
}


/*******************************************************************************
* Function Name: BUZZER_Read
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
*  Macro BUZZER_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 BUZZER_Read(void) 
{
    return (BUZZER_PS & BUZZER_MASK) >> BUZZER_SHIFT;
}


/*******************************************************************************
* Function Name: BUZZER_ReadDataReg
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
uint8 BUZZER_ReadDataReg(void) 
{
    return (BUZZER_DR & BUZZER_MASK) >> BUZZER_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(BUZZER_INTSTAT) 

    /*******************************************************************************
    * Function Name: BUZZER_ClearInterrupt
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
    uint8 BUZZER_ClearInterrupt(void) 
    {
        return (BUZZER_INTSTAT & BUZZER_MASK) >> BUZZER_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
