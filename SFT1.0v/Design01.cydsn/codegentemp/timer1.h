/*******************************************************************************
* File Name: timer1.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_timer1_H)
#define CY_ISR_timer1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void timer1_Start(void);
void timer1_StartEx(cyisraddress address);
void timer1_Stop(void);

CY_ISR_PROTO(timer1_Interrupt);

void timer1_SetVector(cyisraddress address);
cyisraddress timer1_GetVector(void);

void timer1_SetPriority(uint8 priority);
uint8 timer1_GetPriority(void);

void timer1_Enable(void);
uint8 timer1_GetState(void);
void timer1_Disable(void);

void timer1_SetPending(void);
void timer1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the timer1 ISR. */
#define timer1_INTC_VECTOR            ((reg32 *) timer1__INTC_VECT)

/* Address of the timer1 ISR priority. */
#define timer1_INTC_PRIOR             ((reg8 *) timer1__INTC_PRIOR_REG)

/* Priority of the timer1 interrupt. */
#define timer1_INTC_PRIOR_NUMBER      timer1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable timer1 interrupt. */
#define timer1_INTC_SET_EN            ((reg32 *) timer1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the timer1 interrupt. */
#define timer1_INTC_CLR_EN            ((reg32 *) timer1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the timer1 interrupt state to pending. */
#define timer1_INTC_SET_PD            ((reg32 *) timer1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the timer1 interrupt. */
#define timer1_INTC_CLR_PD            ((reg32 *) timer1__INTC_CLR_PD_REG)


#endif /* CY_ISR_timer1_H */


/* [] END OF FILE */
