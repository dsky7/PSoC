/*******************************************************************************
* File Name: AN3.h  
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

#if !defined(CY_PINS_AN3_H) /* Pins AN3_H */
#define CY_PINS_AN3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AN3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AN3__PORT == 15 && ((AN3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    AN3_Write(uint8 value) ;
void    AN3_SetDriveMode(uint8 mode) ;
uint8   AN3_ReadDataReg(void) ;
uint8   AN3_Read(void) ;
uint8   AN3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define AN3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define AN3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define AN3_DM_RES_UP          PIN_DM_RES_UP
#define AN3_DM_RES_DWN         PIN_DM_RES_DWN
#define AN3_DM_OD_LO           PIN_DM_OD_LO
#define AN3_DM_OD_HI           PIN_DM_OD_HI
#define AN3_DM_STRONG          PIN_DM_STRONG
#define AN3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define AN3_MASK               AN3__MASK
#define AN3_SHIFT              AN3__SHIFT
#define AN3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AN3_PS                     (* (reg8 *) AN3__PS)
/* Data Register */
#define AN3_DR                     (* (reg8 *) AN3__DR)
/* Port Number */
#define AN3_PRT_NUM                (* (reg8 *) AN3__PRT) 
/* Connect to Analog Globals */                                                  
#define AN3_AG                     (* (reg8 *) AN3__AG)                       
/* Analog MUX bux enable */
#define AN3_AMUX                   (* (reg8 *) AN3__AMUX) 
/* Bidirectional Enable */                                                        
#define AN3_BIE                    (* (reg8 *) AN3__BIE)
/* Bit-mask for Aliased Register Access */
#define AN3_BIT_MASK               (* (reg8 *) AN3__BIT_MASK)
/* Bypass Enable */
#define AN3_BYP                    (* (reg8 *) AN3__BYP)
/* Port wide control signals */                                                   
#define AN3_CTL                    (* (reg8 *) AN3__CTL)
/* Drive Modes */
#define AN3_DM0                    (* (reg8 *) AN3__DM0) 
#define AN3_DM1                    (* (reg8 *) AN3__DM1)
#define AN3_DM2                    (* (reg8 *) AN3__DM2) 
/* Input Buffer Disable Override */
#define AN3_INP_DIS                (* (reg8 *) AN3__INP_DIS)
/* LCD Common or Segment Drive */
#define AN3_LCD_COM_SEG            (* (reg8 *) AN3__LCD_COM_SEG)
/* Enable Segment LCD */
#define AN3_LCD_EN                 (* (reg8 *) AN3__LCD_EN)
/* Slew Rate Control */
#define AN3_SLW                    (* (reg8 *) AN3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AN3_PRTDSI__CAPS_SEL       (* (reg8 *) AN3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AN3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AN3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AN3_PRTDSI__OE_SEL0        (* (reg8 *) AN3__PRTDSI__OE_SEL0) 
#define AN3_PRTDSI__OE_SEL1        (* (reg8 *) AN3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AN3_PRTDSI__OUT_SEL0       (* (reg8 *) AN3__PRTDSI__OUT_SEL0) 
#define AN3_PRTDSI__OUT_SEL1       (* (reg8 *) AN3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AN3_PRTDSI__SYNC_OUT       (* (reg8 *) AN3__PRTDSI__SYNC_OUT) 


#if defined(AN3__INTSTAT)  /* Interrupt Registers */

    #define AN3_INTSTAT                (* (reg8 *) AN3__INTSTAT)
    #define AN3_SNAP                   (* (reg8 *) AN3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AN3_H */


/* [] END OF FILE */
