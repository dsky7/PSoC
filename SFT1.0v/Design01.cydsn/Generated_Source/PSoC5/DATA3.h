/*******************************************************************************
* File Name: DATA3.h  
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

#if !defined(CY_PINS_DATA3_H) /* Pins DATA3_H */
#define CY_PINS_DATA3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DATA3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DATA3__PORT == 15 && ((DATA3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DATA3_Write(uint8 value) ;
void    DATA3_SetDriveMode(uint8 mode) ;
uint8   DATA3_ReadDataReg(void) ;
uint8   DATA3_Read(void) ;
uint8   DATA3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DATA3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DATA3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DATA3_DM_RES_UP          PIN_DM_RES_UP
#define DATA3_DM_RES_DWN         PIN_DM_RES_DWN
#define DATA3_DM_OD_LO           PIN_DM_OD_LO
#define DATA3_DM_OD_HI           PIN_DM_OD_HI
#define DATA3_DM_STRONG          PIN_DM_STRONG
#define DATA3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DATA3_MASK               DATA3__MASK
#define DATA3_SHIFT              DATA3__SHIFT
#define DATA3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DATA3_PS                     (* (reg8 *) DATA3__PS)
/* Data Register */
#define DATA3_DR                     (* (reg8 *) DATA3__DR)
/* Port Number */
#define DATA3_PRT_NUM                (* (reg8 *) DATA3__PRT) 
/* Connect to Analog Globals */                                                  
#define DATA3_AG                     (* (reg8 *) DATA3__AG)                       
/* Analog MUX bux enable */
#define DATA3_AMUX                   (* (reg8 *) DATA3__AMUX) 
/* Bidirectional Enable */                                                        
#define DATA3_BIE                    (* (reg8 *) DATA3__BIE)
/* Bit-mask for Aliased Register Access */
#define DATA3_BIT_MASK               (* (reg8 *) DATA3__BIT_MASK)
/* Bypass Enable */
#define DATA3_BYP                    (* (reg8 *) DATA3__BYP)
/* Port wide control signals */                                                   
#define DATA3_CTL                    (* (reg8 *) DATA3__CTL)
/* Drive Modes */
#define DATA3_DM0                    (* (reg8 *) DATA3__DM0) 
#define DATA3_DM1                    (* (reg8 *) DATA3__DM1)
#define DATA3_DM2                    (* (reg8 *) DATA3__DM2) 
/* Input Buffer Disable Override */
#define DATA3_INP_DIS                (* (reg8 *) DATA3__INP_DIS)
/* LCD Common or Segment Drive */
#define DATA3_LCD_COM_SEG            (* (reg8 *) DATA3__LCD_COM_SEG)
/* Enable Segment LCD */
#define DATA3_LCD_EN                 (* (reg8 *) DATA3__LCD_EN)
/* Slew Rate Control */
#define DATA3_SLW                    (* (reg8 *) DATA3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DATA3_PRTDSI__CAPS_SEL       (* (reg8 *) DATA3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DATA3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DATA3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DATA3_PRTDSI__OE_SEL0        (* (reg8 *) DATA3__PRTDSI__OE_SEL0) 
#define DATA3_PRTDSI__OE_SEL1        (* (reg8 *) DATA3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DATA3_PRTDSI__OUT_SEL0       (* (reg8 *) DATA3__PRTDSI__OUT_SEL0) 
#define DATA3_PRTDSI__OUT_SEL1       (* (reg8 *) DATA3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DATA3_PRTDSI__SYNC_OUT       (* (reg8 *) DATA3__PRTDSI__SYNC_OUT) 


#if defined(DATA3__INTSTAT)  /* Interrupt Registers */

    #define DATA3_INTSTAT                (* (reg8 *) DATA3__INTSTAT)
    #define DATA3_SNAP                   (* (reg8 *) DATA3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DATA3_H */


/* [] END OF FILE */
