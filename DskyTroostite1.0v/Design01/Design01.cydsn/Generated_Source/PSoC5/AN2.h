/*******************************************************************************
* File Name: AN2.h  
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

#if !defined(CY_PINS_AN2_H) /* Pins AN2_H */
#define CY_PINS_AN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AN2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AN2__PORT == 15 && ((AN2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    AN2_Write(uint8 value) ;
void    AN2_SetDriveMode(uint8 mode) ;
uint8   AN2_ReadDataReg(void) ;
uint8   AN2_Read(void) ;
uint8   AN2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define AN2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define AN2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define AN2_DM_RES_UP          PIN_DM_RES_UP
#define AN2_DM_RES_DWN         PIN_DM_RES_DWN
#define AN2_DM_OD_LO           PIN_DM_OD_LO
#define AN2_DM_OD_HI           PIN_DM_OD_HI
#define AN2_DM_STRONG          PIN_DM_STRONG
#define AN2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define AN2_MASK               AN2__MASK
#define AN2_SHIFT              AN2__SHIFT
#define AN2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AN2_PS                     (* (reg8 *) AN2__PS)
/* Data Register */
#define AN2_DR                     (* (reg8 *) AN2__DR)
/* Port Number */
#define AN2_PRT_NUM                (* (reg8 *) AN2__PRT) 
/* Connect to Analog Globals */                                                  
#define AN2_AG                     (* (reg8 *) AN2__AG)                       
/* Analog MUX bux enable */
#define AN2_AMUX                   (* (reg8 *) AN2__AMUX) 
/* Bidirectional Enable */                                                        
#define AN2_BIE                    (* (reg8 *) AN2__BIE)
/* Bit-mask for Aliased Register Access */
#define AN2_BIT_MASK               (* (reg8 *) AN2__BIT_MASK)
/* Bypass Enable */
#define AN2_BYP                    (* (reg8 *) AN2__BYP)
/* Port wide control signals */                                                   
#define AN2_CTL                    (* (reg8 *) AN2__CTL)
/* Drive Modes */
#define AN2_DM0                    (* (reg8 *) AN2__DM0) 
#define AN2_DM1                    (* (reg8 *) AN2__DM1)
#define AN2_DM2                    (* (reg8 *) AN2__DM2) 
/* Input Buffer Disable Override */
#define AN2_INP_DIS                (* (reg8 *) AN2__INP_DIS)
/* LCD Common or Segment Drive */
#define AN2_LCD_COM_SEG            (* (reg8 *) AN2__LCD_COM_SEG)
/* Enable Segment LCD */
#define AN2_LCD_EN                 (* (reg8 *) AN2__LCD_EN)
/* Slew Rate Control */
#define AN2_SLW                    (* (reg8 *) AN2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AN2_PRTDSI__CAPS_SEL       (* (reg8 *) AN2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AN2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AN2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AN2_PRTDSI__OE_SEL0        (* (reg8 *) AN2__PRTDSI__OE_SEL0) 
#define AN2_PRTDSI__OE_SEL1        (* (reg8 *) AN2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AN2_PRTDSI__OUT_SEL0       (* (reg8 *) AN2__PRTDSI__OUT_SEL0) 
#define AN2_PRTDSI__OUT_SEL1       (* (reg8 *) AN2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AN2_PRTDSI__SYNC_OUT       (* (reg8 *) AN2__PRTDSI__SYNC_OUT) 


#if defined(AN2__INTSTAT)  /* Interrupt Registers */

    #define AN2_INTSTAT                (* (reg8 *) AN2__INTSTAT)
    #define AN2_SNAP                   (* (reg8 *) AN2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AN2_H */


/* [] END OF FILE */
