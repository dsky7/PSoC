/*******************************************************************************
* File Name: DATA1.h  
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

#if !defined(CY_PINS_DATA1_H) /* Pins DATA1_H */
#define CY_PINS_DATA1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DATA1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DATA1__PORT == 15 && ((DATA1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DATA1_Write(uint8 value) ;
void    DATA1_SetDriveMode(uint8 mode) ;
uint8   DATA1_ReadDataReg(void) ;
uint8   DATA1_Read(void) ;
uint8   DATA1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DATA1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DATA1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DATA1_DM_RES_UP          PIN_DM_RES_UP
#define DATA1_DM_RES_DWN         PIN_DM_RES_DWN
#define DATA1_DM_OD_LO           PIN_DM_OD_LO
#define DATA1_DM_OD_HI           PIN_DM_OD_HI
#define DATA1_DM_STRONG          PIN_DM_STRONG
#define DATA1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DATA1_MASK               DATA1__MASK
#define DATA1_SHIFT              DATA1__SHIFT
#define DATA1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DATA1_PS                     (* (reg8 *) DATA1__PS)
/* Data Register */
#define DATA1_DR                     (* (reg8 *) DATA1__DR)
/* Port Number */
#define DATA1_PRT_NUM                (* (reg8 *) DATA1__PRT) 
/* Connect to Analog Globals */                                                  
#define DATA1_AG                     (* (reg8 *) DATA1__AG)                       
/* Analog MUX bux enable */
#define DATA1_AMUX                   (* (reg8 *) DATA1__AMUX) 
/* Bidirectional Enable */                                                        
#define DATA1_BIE                    (* (reg8 *) DATA1__BIE)
/* Bit-mask for Aliased Register Access */
#define DATA1_BIT_MASK               (* (reg8 *) DATA1__BIT_MASK)
/* Bypass Enable */
#define DATA1_BYP                    (* (reg8 *) DATA1__BYP)
/* Port wide control signals */                                                   
#define DATA1_CTL                    (* (reg8 *) DATA1__CTL)
/* Drive Modes */
#define DATA1_DM0                    (* (reg8 *) DATA1__DM0) 
#define DATA1_DM1                    (* (reg8 *) DATA1__DM1)
#define DATA1_DM2                    (* (reg8 *) DATA1__DM2) 
/* Input Buffer Disable Override */
#define DATA1_INP_DIS                (* (reg8 *) DATA1__INP_DIS)
/* LCD Common or Segment Drive */
#define DATA1_LCD_COM_SEG            (* (reg8 *) DATA1__LCD_COM_SEG)
/* Enable Segment LCD */
#define DATA1_LCD_EN                 (* (reg8 *) DATA1__LCD_EN)
/* Slew Rate Control */
#define DATA1_SLW                    (* (reg8 *) DATA1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DATA1_PRTDSI__CAPS_SEL       (* (reg8 *) DATA1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DATA1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DATA1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DATA1_PRTDSI__OE_SEL0        (* (reg8 *) DATA1__PRTDSI__OE_SEL0) 
#define DATA1_PRTDSI__OE_SEL1        (* (reg8 *) DATA1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DATA1_PRTDSI__OUT_SEL0       (* (reg8 *) DATA1__PRTDSI__OUT_SEL0) 
#define DATA1_PRTDSI__OUT_SEL1       (* (reg8 *) DATA1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DATA1_PRTDSI__SYNC_OUT       (* (reg8 *) DATA1__PRTDSI__SYNC_OUT) 


#if defined(DATA1__INTSTAT)  /* Interrupt Registers */

    #define DATA1_INTSTAT                (* (reg8 *) DATA1__INTSTAT)
    #define DATA1_SNAP                   (* (reg8 *) DATA1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DATA1_H */


/* [] END OF FILE */
