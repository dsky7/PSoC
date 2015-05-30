/*******************************************************************************
* File Name: AN4.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "AN4.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 AN4__PORT == 15 && ((AN4__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: AN4_Write
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
void AN4_Write(uint8 value) 
{
    uint8 staticBits = (AN4_DR & (uint8)(~AN4_MASK));
    AN4_DR = staticBits | ((uint8)(value << AN4_SHIFT) & AN4_MASK);
}


/*******************************************************************************
* Function Name: AN4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void AN4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(AN4_0, mode);
}


/*******************************************************************************
* Function Name: AN4_Read
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
*  Macro AN4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 AN4_Read(void) 
{
    return (AN4_PS & AN4_MASK) >> AN4_SHIFT;
}


/*******************************************************************************
* Function Name: AN4_ReadDataReg
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
uint8 AN4_ReadDataReg(void) 
{
    return (AN4_DR & AN4_MASK) >> AN4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(AN4_INTSTAT) 

    /*******************************************************************************
    * Function Name: AN4_ClearInterrupt
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
    uint8 AN4_ClearInterrupt(void) 
    {
        return (AN4_INTSTAT & AN4_MASK) >> AN4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
