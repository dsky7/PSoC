/*******************************************************************************
* File Name: rts.c  
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
#include "rts.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 rts__PORT == 15 && ((rts__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: rts_Write
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
void rts_Write(uint8 value) 
{
    uint8 staticBits = (rts_DR & (uint8)(~rts_MASK));
    rts_DR = staticBits | ((uint8)(value << rts_SHIFT) & rts_MASK);
}


/*******************************************************************************
* Function Name: rts_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  rts_DM_STRONG     Strong Drive 
*  rts_DM_OD_HI      Open Drain, Drives High 
*  rts_DM_OD_LO      Open Drain, Drives Low 
*  rts_DM_RES_UP     Resistive Pull Up 
*  rts_DM_RES_DWN    Resistive Pull Down 
*  rts_DM_RES_UPDWN  Resistive Pull Up/Down 
*  rts_DM_DIG_HIZ    High Impedance Digital 
*  rts_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void rts_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(rts_0, mode);
}


/*******************************************************************************
* Function Name: rts_Read
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
*  Macro rts_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 rts_Read(void) 
{
    return (rts_PS & rts_MASK) >> rts_SHIFT;
}


/*******************************************************************************
* Function Name: rts_ReadDataReg
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
uint8 rts_ReadDataReg(void) 
{
    return (rts_DR & rts_MASK) >> rts_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(rts_INTSTAT) 

    /*******************************************************************************
    * Function Name: rts_ClearInterrupt
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
    uint8 rts_ClearInterrupt(void) 
    {
        return (rts_INTSTAT & rts_MASK) >> rts_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
