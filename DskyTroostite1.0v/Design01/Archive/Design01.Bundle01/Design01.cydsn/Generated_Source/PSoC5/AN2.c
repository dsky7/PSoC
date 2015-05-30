/*******************************************************************************
* File Name: AN2.c  
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
#include "AN2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 AN2__PORT == 15 && ((AN2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: AN2_Write
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
void AN2_Write(uint8 value) 
{
    uint8 staticBits = (AN2_DR & (uint8)(~AN2_MASK));
    AN2_DR = staticBits | ((uint8)(value << AN2_SHIFT) & AN2_MASK);
}


/*******************************************************************************
* Function Name: AN2_SetDriveMode
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
void AN2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(AN2_0, mode);
}


/*******************************************************************************
* Function Name: AN2_Read
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
*  Macro AN2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 AN2_Read(void) 
{
    return (AN2_PS & AN2_MASK) >> AN2_SHIFT;
}


/*******************************************************************************
* Function Name: AN2_ReadDataReg
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
uint8 AN2_ReadDataReg(void) 
{
    return (AN2_DR & AN2_MASK) >> AN2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(AN2_INTSTAT) 

    /*******************************************************************************
    * Function Name: AN2_ClearInterrupt
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
    uint8 AN2_ClearInterrupt(void) 
    {
        return (AN2_INTSTAT & AN2_MASK) >> AN2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
