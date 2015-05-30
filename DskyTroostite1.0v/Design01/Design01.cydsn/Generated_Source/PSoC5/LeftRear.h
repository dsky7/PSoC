/*******************************************************************************
* File Name: LeftRear.h  
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

#if !defined(CY_PINS_LeftRear_H) /* Pins LeftRear_H */
#define CY_PINS_LeftRear_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LeftRear_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LeftRear__PORT == 15 && ((LeftRear__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LeftRear_Write(uint8 value) ;
void    LeftRear_SetDriveMode(uint8 mode) ;
uint8   LeftRear_ReadDataReg(void) ;
uint8   LeftRear_Read(void) ;
uint8   LeftRear_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LeftRear_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LeftRear_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LeftRear_DM_RES_UP          PIN_DM_RES_UP
#define LeftRear_DM_RES_DWN         PIN_DM_RES_DWN
#define LeftRear_DM_OD_LO           PIN_DM_OD_LO
#define LeftRear_DM_OD_HI           PIN_DM_OD_HI
#define LeftRear_DM_STRONG          PIN_DM_STRONG
#define LeftRear_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LeftRear_MASK               LeftRear__MASK
#define LeftRear_SHIFT              LeftRear__SHIFT
#define LeftRear_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LeftRear_PS                     (* (reg8 *) LeftRear__PS)
/* Data Register */
#define LeftRear_DR                     (* (reg8 *) LeftRear__DR)
/* Port Number */
#define LeftRear_PRT_NUM                (* (reg8 *) LeftRear__PRT) 
/* Connect to Analog Globals */                                                  
#define LeftRear_AG                     (* (reg8 *) LeftRear__AG)                       
/* Analog MUX bux enable */
#define LeftRear_AMUX                   (* (reg8 *) LeftRear__AMUX) 
/* Bidirectional Enable */                                                        
#define LeftRear_BIE                    (* (reg8 *) LeftRear__BIE)
/* Bit-mask for Aliased Register Access */
#define LeftRear_BIT_MASK               (* (reg8 *) LeftRear__BIT_MASK)
/* Bypass Enable */
#define LeftRear_BYP                    (* (reg8 *) LeftRear__BYP)
/* Port wide control signals */                                                   
#define LeftRear_CTL                    (* (reg8 *) LeftRear__CTL)
/* Drive Modes */
#define LeftRear_DM0                    (* (reg8 *) LeftRear__DM0) 
#define LeftRear_DM1                    (* (reg8 *) LeftRear__DM1)
#define LeftRear_DM2                    (* (reg8 *) LeftRear__DM2) 
/* Input Buffer Disable Override */
#define LeftRear_INP_DIS                (* (reg8 *) LeftRear__INP_DIS)
/* LCD Common or Segment Drive */
#define LeftRear_LCD_COM_SEG            (* (reg8 *) LeftRear__LCD_COM_SEG)
/* Enable Segment LCD */
#define LeftRear_LCD_EN                 (* (reg8 *) LeftRear__LCD_EN)
/* Slew Rate Control */
#define LeftRear_SLW                    (* (reg8 *) LeftRear__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LeftRear_PRTDSI__CAPS_SEL       (* (reg8 *) LeftRear__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LeftRear_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LeftRear__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LeftRear_PRTDSI__OE_SEL0        (* (reg8 *) LeftRear__PRTDSI__OE_SEL0) 
#define LeftRear_PRTDSI__OE_SEL1        (* (reg8 *) LeftRear__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LeftRear_PRTDSI__OUT_SEL0       (* (reg8 *) LeftRear__PRTDSI__OUT_SEL0) 
#define LeftRear_PRTDSI__OUT_SEL1       (* (reg8 *) LeftRear__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LeftRear_PRTDSI__SYNC_OUT       (* (reg8 *) LeftRear__PRTDSI__SYNC_OUT) 


#if defined(LeftRear__INTSTAT)  /* Interrupt Registers */

    #define LeftRear_INTSTAT                (* (reg8 *) LeftRear__INTSTAT)
    #define LeftRear_SNAP                   (* (reg8 *) LeftRear__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LeftRear_H */


/* [] END OF FILE */
