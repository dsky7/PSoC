/*******************************************************************************
* File Name: RightRear_Rev.h  
* Version 2.5
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RightRear_Rev_H) /* Pins RightRear_Rev_H */
#define CY_PINS_RightRear_Rev_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RightRear_Rev_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RightRear_Rev__PORT == 15 && ((RightRear_Rev__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RightRear_Rev_Write(uint8 value) ;
void    RightRear_Rev_SetDriveMode(uint8 mode) ;
uint8   RightRear_Rev_ReadDataReg(void) ;
uint8   RightRear_Rev_Read(void) ;
uint8   RightRear_Rev_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RightRear_Rev_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RightRear_Rev_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RightRear_Rev_DM_RES_UP          PIN_DM_RES_UP
#define RightRear_Rev_DM_RES_DWN         PIN_DM_RES_DWN
#define RightRear_Rev_DM_OD_LO           PIN_DM_OD_LO
#define RightRear_Rev_DM_OD_HI           PIN_DM_OD_HI
#define RightRear_Rev_DM_STRONG          PIN_DM_STRONG
#define RightRear_Rev_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RightRear_Rev_MASK               RightRear_Rev__MASK
#define RightRear_Rev_SHIFT              RightRear_Rev__SHIFT
#define RightRear_Rev_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RightRear_Rev_PS                     (* (reg8 *) RightRear_Rev__PS)
/* Data Register */
#define RightRear_Rev_DR                     (* (reg8 *) RightRear_Rev__DR)
/* Port Number */
#define RightRear_Rev_PRT_NUM                (* (reg8 *) RightRear_Rev__PRT) 
/* Connect to Analog Globals */                                                  
#define RightRear_Rev_AG                     (* (reg8 *) RightRear_Rev__AG)                       
/* Analog MUX bux enable */
#define RightRear_Rev_AMUX                   (* (reg8 *) RightRear_Rev__AMUX) 
/* Bidirectional Enable */                                                        
#define RightRear_Rev_BIE                    (* (reg8 *) RightRear_Rev__BIE)
/* Bit-mask for Aliased Register Access */
#define RightRear_Rev_BIT_MASK               (* (reg8 *) RightRear_Rev__BIT_MASK)
/* Bypass Enable */
#define RightRear_Rev_BYP                    (* (reg8 *) RightRear_Rev__BYP)
/* Port wide control signals */                                                   
#define RightRear_Rev_CTL                    (* (reg8 *) RightRear_Rev__CTL)
/* Drive Modes */
#define RightRear_Rev_DM0                    (* (reg8 *) RightRear_Rev__DM0) 
#define RightRear_Rev_DM1                    (* (reg8 *) RightRear_Rev__DM1)
#define RightRear_Rev_DM2                    (* (reg8 *) RightRear_Rev__DM2) 
/* Input Buffer Disable Override */
#define RightRear_Rev_INP_DIS                (* (reg8 *) RightRear_Rev__INP_DIS)
/* LCD Common or Segment Drive */
#define RightRear_Rev_LCD_COM_SEG            (* (reg8 *) RightRear_Rev__LCD_COM_SEG)
/* Enable Segment LCD */
#define RightRear_Rev_LCD_EN                 (* (reg8 *) RightRear_Rev__LCD_EN)
/* Slew Rate Control */
#define RightRear_Rev_SLW                    (* (reg8 *) RightRear_Rev__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RightRear_Rev_PRTDSI__CAPS_SEL       (* (reg8 *) RightRear_Rev__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RightRear_Rev_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RightRear_Rev__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RightRear_Rev_PRTDSI__OE_SEL0        (* (reg8 *) RightRear_Rev__PRTDSI__OE_SEL0) 
#define RightRear_Rev_PRTDSI__OE_SEL1        (* (reg8 *) RightRear_Rev__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RightRear_Rev_PRTDSI__OUT_SEL0       (* (reg8 *) RightRear_Rev__PRTDSI__OUT_SEL0) 
#define RightRear_Rev_PRTDSI__OUT_SEL1       (* (reg8 *) RightRear_Rev__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RightRear_Rev_PRTDSI__SYNC_OUT       (* (reg8 *) RightRear_Rev__PRTDSI__SYNC_OUT) 


#if defined(RightRear_Rev__INTSTAT)  /* Interrupt Registers */

    #define RightRear_Rev_INTSTAT                (* (reg8 *) RightRear_Rev__INTSTAT)
    #define RightRear_Rev_SNAP                   (* (reg8 *) RightRear_Rev__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RightRear_Rev_H */


/* [] END OF FILE */
