/*******************************************************************************
* File Name: BuzzerPin.h  
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

#if !defined(CY_PINS_BuzzerPin_H) /* Pins BuzzerPin_H */
#define CY_PINS_BuzzerPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BuzzerPin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BuzzerPin__PORT == 15 && ((BuzzerPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    BuzzerPin_Write(uint8 value) ;
void    BuzzerPin_SetDriveMode(uint8 mode) ;
uint8   BuzzerPin_ReadDataReg(void) ;
uint8   BuzzerPin_Read(void) ;
uint8   BuzzerPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BuzzerPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BuzzerPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BuzzerPin_DM_RES_UP          PIN_DM_RES_UP
#define BuzzerPin_DM_RES_DWN         PIN_DM_RES_DWN
#define BuzzerPin_DM_OD_LO           PIN_DM_OD_LO
#define BuzzerPin_DM_OD_HI           PIN_DM_OD_HI
#define BuzzerPin_DM_STRONG          PIN_DM_STRONG
#define BuzzerPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BuzzerPin_MASK               BuzzerPin__MASK
#define BuzzerPin_SHIFT              BuzzerPin__SHIFT
#define BuzzerPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BuzzerPin_PS                     (* (reg8 *) BuzzerPin__PS)
/* Data Register */
#define BuzzerPin_DR                     (* (reg8 *) BuzzerPin__DR)
/* Port Number */
#define BuzzerPin_PRT_NUM                (* (reg8 *) BuzzerPin__PRT) 
/* Connect to Analog Globals */                                                  
#define BuzzerPin_AG                     (* (reg8 *) BuzzerPin__AG)                       
/* Analog MUX bux enable */
#define BuzzerPin_AMUX                   (* (reg8 *) BuzzerPin__AMUX) 
/* Bidirectional Enable */                                                        
#define BuzzerPin_BIE                    (* (reg8 *) BuzzerPin__BIE)
/* Bit-mask for Aliased Register Access */
#define BuzzerPin_BIT_MASK               (* (reg8 *) BuzzerPin__BIT_MASK)
/* Bypass Enable */
#define BuzzerPin_BYP                    (* (reg8 *) BuzzerPin__BYP)
/* Port wide control signals */                                                   
#define BuzzerPin_CTL                    (* (reg8 *) BuzzerPin__CTL)
/* Drive Modes */
#define BuzzerPin_DM0                    (* (reg8 *) BuzzerPin__DM0) 
#define BuzzerPin_DM1                    (* (reg8 *) BuzzerPin__DM1)
#define BuzzerPin_DM2                    (* (reg8 *) BuzzerPin__DM2) 
/* Input Buffer Disable Override */
#define BuzzerPin_INP_DIS                (* (reg8 *) BuzzerPin__INP_DIS)
/* LCD Common or Segment Drive */
#define BuzzerPin_LCD_COM_SEG            (* (reg8 *) BuzzerPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define BuzzerPin_LCD_EN                 (* (reg8 *) BuzzerPin__LCD_EN)
/* Slew Rate Control */
#define BuzzerPin_SLW                    (* (reg8 *) BuzzerPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BuzzerPin_PRTDSI__CAPS_SEL       (* (reg8 *) BuzzerPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BuzzerPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BuzzerPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BuzzerPin_PRTDSI__OE_SEL0        (* (reg8 *) BuzzerPin__PRTDSI__OE_SEL0) 
#define BuzzerPin_PRTDSI__OE_SEL1        (* (reg8 *) BuzzerPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BuzzerPin_PRTDSI__OUT_SEL0       (* (reg8 *) BuzzerPin__PRTDSI__OUT_SEL0) 
#define BuzzerPin_PRTDSI__OUT_SEL1       (* (reg8 *) BuzzerPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BuzzerPin_PRTDSI__SYNC_OUT       (* (reg8 *) BuzzerPin__PRTDSI__SYNC_OUT) 


#if defined(BuzzerPin__INTSTAT)  /* Interrupt Registers */

    #define BuzzerPin_INTSTAT                (* (reg8 *) BuzzerPin__INTSTAT)
    #define BuzzerPin_SNAP                   (* (reg8 *) BuzzerPin__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BuzzerPin_H */


/* [] END OF FILE */
