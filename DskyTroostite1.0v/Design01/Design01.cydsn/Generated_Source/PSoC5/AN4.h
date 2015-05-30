/*******************************************************************************
* File Name: AN4.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AN4_H) /* Pins AN4_H */
#define CY_PINS_AN4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AN4_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AN4__PORT == 15 && ((AN4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    AN4_Write(uint8 value) ;
void    AN4_SetDriveMode(uint8 mode) ;
uint8   AN4_ReadDataReg(void) ;
uint8   AN4_Read(void) ;
uint8   AN4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define AN4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define AN4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define AN4_DM_RES_UP          PIN_DM_RES_UP
#define AN4_DM_RES_DWN         PIN_DM_RES_DWN
#define AN4_DM_OD_LO           PIN_DM_OD_LO
#define AN4_DM_OD_HI           PIN_DM_OD_HI
#define AN4_DM_STRONG          PIN_DM_STRONG
#define AN4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define AN4_MASK               AN4__MASK
#define AN4_SHIFT              AN4__SHIFT
#define AN4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AN4_PS                     (* (reg8 *) AN4__PS)
/* Data Register */
#define AN4_DR                     (* (reg8 *) AN4__DR)
/* Port Number */
#define AN4_PRT_NUM                (* (reg8 *) AN4__PRT) 
/* Connect to Analog Globals */                                                  
#define AN4_AG                     (* (reg8 *) AN4__AG)                       
/* Analog MUX bux enable */
#define AN4_AMUX                   (* (reg8 *) AN4__AMUX) 
/* Bidirectional Enable */                                                        
#define AN4_BIE                    (* (reg8 *) AN4__BIE)
/* Bit-mask for Aliased Register Access */
#define AN4_BIT_MASK               (* (reg8 *) AN4__BIT_MASK)
/* Bypass Enable */
#define AN4_BYP                    (* (reg8 *) AN4__BYP)
/* Port wide control signals */                                                   
#define AN4_CTL                    (* (reg8 *) AN4__CTL)
/* Drive Modes */
#define AN4_DM0                    (* (reg8 *) AN4__DM0) 
#define AN4_DM1                    (* (reg8 *) AN4__DM1)
#define AN4_DM2                    (* (reg8 *) AN4__DM2) 
/* Input Buffer Disable Override */
#define AN4_INP_DIS                (* (reg8 *) AN4__INP_DIS)
/* LCD Common or Segment Drive */
#define AN4_LCD_COM_SEG            (* (reg8 *) AN4__LCD_COM_SEG)
/* Enable Segment LCD */
#define AN4_LCD_EN                 (* (reg8 *) AN4__LCD_EN)
/* Slew Rate Control */
#define AN4_SLW                    (* (reg8 *) AN4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AN4_PRTDSI__CAPS_SEL       (* (reg8 *) AN4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AN4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AN4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AN4_PRTDSI__OE_SEL0        (* (reg8 *) AN4__PRTDSI__OE_SEL0) 
#define AN4_PRTDSI__OE_SEL1        (* (reg8 *) AN4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AN4_PRTDSI__OUT_SEL0       (* (reg8 *) AN4__PRTDSI__OUT_SEL0) 
#define AN4_PRTDSI__OUT_SEL1       (* (reg8 *) AN4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AN4_PRTDSI__SYNC_OUT       (* (reg8 *) AN4__PRTDSI__SYNC_OUT) 


#if defined(AN4__INTSTAT)  /* Interrupt Registers */

    #define AN4_INTSTAT                (* (reg8 *) AN4__INTSTAT)
    #define AN4_SNAP                   (* (reg8 *) AN4__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AN4_H */


/* [] END OF FILE */
