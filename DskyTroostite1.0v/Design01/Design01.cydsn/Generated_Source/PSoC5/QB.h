/*******************************************************************************
* File Name: QB.h  
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

#if !defined(CY_PINS_QB_H) /* Pins QB_H */
#define CY_PINS_QB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QB_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QB__PORT == 15 && ((QB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    QB_Write(uint8 value) ;
void    QB_SetDriveMode(uint8 mode) ;
uint8   QB_ReadDataReg(void) ;
uint8   QB_Read(void) ;
uint8   QB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define QB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define QB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define QB_DM_RES_UP          PIN_DM_RES_UP
#define QB_DM_RES_DWN         PIN_DM_RES_DWN
#define QB_DM_OD_LO           PIN_DM_OD_LO
#define QB_DM_OD_HI           PIN_DM_OD_HI
#define QB_DM_STRONG          PIN_DM_STRONG
#define QB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define QB_MASK               QB__MASK
#define QB_SHIFT              QB__SHIFT
#define QB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QB_PS                     (* (reg8 *) QB__PS)
/* Data Register */
#define QB_DR                     (* (reg8 *) QB__DR)
/* Port Number */
#define QB_PRT_NUM                (* (reg8 *) QB__PRT) 
/* Connect to Analog Globals */                                                  
#define QB_AG                     (* (reg8 *) QB__AG)                       
/* Analog MUX bux enable */
#define QB_AMUX                   (* (reg8 *) QB__AMUX) 
/* Bidirectional Enable */                                                        
#define QB_BIE                    (* (reg8 *) QB__BIE)
/* Bit-mask for Aliased Register Access */
#define QB_BIT_MASK               (* (reg8 *) QB__BIT_MASK)
/* Bypass Enable */
#define QB_BYP                    (* (reg8 *) QB__BYP)
/* Port wide control signals */                                                   
#define QB_CTL                    (* (reg8 *) QB__CTL)
/* Drive Modes */
#define QB_DM0                    (* (reg8 *) QB__DM0) 
#define QB_DM1                    (* (reg8 *) QB__DM1)
#define QB_DM2                    (* (reg8 *) QB__DM2) 
/* Input Buffer Disable Override */
#define QB_INP_DIS                (* (reg8 *) QB__INP_DIS)
/* LCD Common or Segment Drive */
#define QB_LCD_COM_SEG            (* (reg8 *) QB__LCD_COM_SEG)
/* Enable Segment LCD */
#define QB_LCD_EN                 (* (reg8 *) QB__LCD_EN)
/* Slew Rate Control */
#define QB_SLW                    (* (reg8 *) QB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QB_PRTDSI__CAPS_SEL       (* (reg8 *) QB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QB_PRTDSI__OE_SEL0        (* (reg8 *) QB__PRTDSI__OE_SEL0) 
#define QB_PRTDSI__OE_SEL1        (* (reg8 *) QB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QB_PRTDSI__OUT_SEL0       (* (reg8 *) QB__PRTDSI__OUT_SEL0) 
#define QB_PRTDSI__OUT_SEL1       (* (reg8 *) QB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QB_PRTDSI__SYNC_OUT       (* (reg8 *) QB__PRTDSI__SYNC_OUT) 


#if defined(QB__INTSTAT)  /* Interrupt Registers */

    #define QB_INTSTAT                (* (reg8 *) QB__INTSTAT)
    #define QB_SNAP                   (* (reg8 *) QB__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QB_H */


/* [] END OF FILE */
