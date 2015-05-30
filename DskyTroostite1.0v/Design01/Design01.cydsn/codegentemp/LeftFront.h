/*******************************************************************************
* File Name: LeftFront.h  
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

#if !defined(CY_PINS_LeftFront_H) /* Pins LeftFront_H */
#define CY_PINS_LeftFront_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LeftFront_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LeftFront__PORT == 15 && ((LeftFront__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LeftFront_Write(uint8 value) ;
void    LeftFront_SetDriveMode(uint8 mode) ;
uint8   LeftFront_ReadDataReg(void) ;
uint8   LeftFront_Read(void) ;
uint8   LeftFront_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LeftFront_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LeftFront_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LeftFront_DM_RES_UP          PIN_DM_RES_UP
#define LeftFront_DM_RES_DWN         PIN_DM_RES_DWN
#define LeftFront_DM_OD_LO           PIN_DM_OD_LO
#define LeftFront_DM_OD_HI           PIN_DM_OD_HI
#define LeftFront_DM_STRONG          PIN_DM_STRONG
#define LeftFront_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LeftFront_MASK               LeftFront__MASK
#define LeftFront_SHIFT              LeftFront__SHIFT
#define LeftFront_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LeftFront_PS                     (* (reg8 *) LeftFront__PS)
/* Data Register */
#define LeftFront_DR                     (* (reg8 *) LeftFront__DR)
/* Port Number */
#define LeftFront_PRT_NUM                (* (reg8 *) LeftFront__PRT) 
/* Connect to Analog Globals */                                                  
#define LeftFront_AG                     (* (reg8 *) LeftFront__AG)                       
/* Analog MUX bux enable */
#define LeftFront_AMUX                   (* (reg8 *) LeftFront__AMUX) 
/* Bidirectional Enable */                                                        
#define LeftFront_BIE                    (* (reg8 *) LeftFront__BIE)
/* Bit-mask for Aliased Register Access */
#define LeftFront_BIT_MASK               (* (reg8 *) LeftFront__BIT_MASK)
/* Bypass Enable */
#define LeftFront_BYP                    (* (reg8 *) LeftFront__BYP)
/* Port wide control signals */                                                   
#define LeftFront_CTL                    (* (reg8 *) LeftFront__CTL)
/* Drive Modes */
#define LeftFront_DM0                    (* (reg8 *) LeftFront__DM0) 
#define LeftFront_DM1                    (* (reg8 *) LeftFront__DM1)
#define LeftFront_DM2                    (* (reg8 *) LeftFront__DM2) 
/* Input Buffer Disable Override */
#define LeftFront_INP_DIS                (* (reg8 *) LeftFront__INP_DIS)
/* LCD Common or Segment Drive */
#define LeftFront_LCD_COM_SEG            (* (reg8 *) LeftFront__LCD_COM_SEG)
/* Enable Segment LCD */
#define LeftFront_LCD_EN                 (* (reg8 *) LeftFront__LCD_EN)
/* Slew Rate Control */
#define LeftFront_SLW                    (* (reg8 *) LeftFront__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LeftFront_PRTDSI__CAPS_SEL       (* (reg8 *) LeftFront__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LeftFront_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LeftFront__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LeftFront_PRTDSI__OE_SEL0        (* (reg8 *) LeftFront__PRTDSI__OE_SEL0) 
#define LeftFront_PRTDSI__OE_SEL1        (* (reg8 *) LeftFront__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LeftFront_PRTDSI__OUT_SEL0       (* (reg8 *) LeftFront__PRTDSI__OUT_SEL0) 
#define LeftFront_PRTDSI__OUT_SEL1       (* (reg8 *) LeftFront__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LeftFront_PRTDSI__SYNC_OUT       (* (reg8 *) LeftFront__PRTDSI__SYNC_OUT) 


#if defined(LeftFront__INTSTAT)  /* Interrupt Registers */

    #define LeftFront_INTSTAT                (* (reg8 *) LeftFront__INTSTAT)
    #define LeftFront_SNAP                   (* (reg8 *) LeftFront__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LeftFront_H */


/* [] END OF FILE */
