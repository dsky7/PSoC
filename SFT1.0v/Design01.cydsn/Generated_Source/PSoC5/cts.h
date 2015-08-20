/*******************************************************************************
* File Name: cts.h  
* Version 2.10
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

#if !defined(CY_PINS_cts_H) /* Pins cts_H */
#define CY_PINS_cts_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "cts_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 cts__PORT == 15 && ((cts__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    cts_Write(uint8 value) ;
void    cts_SetDriveMode(uint8 mode) ;
uint8   cts_ReadDataReg(void) ;
uint8   cts_Read(void) ;
uint8   cts_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define cts_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define cts_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define cts_DM_RES_UP          PIN_DM_RES_UP
#define cts_DM_RES_DWN         PIN_DM_RES_DWN
#define cts_DM_OD_LO           PIN_DM_OD_LO
#define cts_DM_OD_HI           PIN_DM_OD_HI
#define cts_DM_STRONG          PIN_DM_STRONG
#define cts_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define cts_MASK               cts__MASK
#define cts_SHIFT              cts__SHIFT
#define cts_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define cts_PS                     (* (reg8 *) cts__PS)
/* Data Register */
#define cts_DR                     (* (reg8 *) cts__DR)
/* Port Number */
#define cts_PRT_NUM                (* (reg8 *) cts__PRT) 
/* Connect to Analog Globals */                                                  
#define cts_AG                     (* (reg8 *) cts__AG)                       
/* Analog MUX bux enable */
#define cts_AMUX                   (* (reg8 *) cts__AMUX) 
/* Bidirectional Enable */                                                        
#define cts_BIE                    (* (reg8 *) cts__BIE)
/* Bit-mask for Aliased Register Access */
#define cts_BIT_MASK               (* (reg8 *) cts__BIT_MASK)
/* Bypass Enable */
#define cts_BYP                    (* (reg8 *) cts__BYP)
/* Port wide control signals */                                                   
#define cts_CTL                    (* (reg8 *) cts__CTL)
/* Drive Modes */
#define cts_DM0                    (* (reg8 *) cts__DM0) 
#define cts_DM1                    (* (reg8 *) cts__DM1)
#define cts_DM2                    (* (reg8 *) cts__DM2) 
/* Input Buffer Disable Override */
#define cts_INP_DIS                (* (reg8 *) cts__INP_DIS)
/* LCD Common or Segment Drive */
#define cts_LCD_COM_SEG            (* (reg8 *) cts__LCD_COM_SEG)
/* Enable Segment LCD */
#define cts_LCD_EN                 (* (reg8 *) cts__LCD_EN)
/* Slew Rate Control */
#define cts_SLW                    (* (reg8 *) cts__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define cts_PRTDSI__CAPS_SEL       (* (reg8 *) cts__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define cts_PRTDSI__DBL_SYNC_IN    (* (reg8 *) cts__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define cts_PRTDSI__OE_SEL0        (* (reg8 *) cts__PRTDSI__OE_SEL0) 
#define cts_PRTDSI__OE_SEL1        (* (reg8 *) cts__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define cts_PRTDSI__OUT_SEL0       (* (reg8 *) cts__PRTDSI__OUT_SEL0) 
#define cts_PRTDSI__OUT_SEL1       (* (reg8 *) cts__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define cts_PRTDSI__SYNC_OUT       (* (reg8 *) cts__PRTDSI__SYNC_OUT) 


#if defined(cts__INTSTAT)  /* Interrupt Registers */

    #define cts_INTSTAT                (* (reg8 *) cts__INTSTAT)
    #define cts_SNAP                   (* (reg8 *) cts__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_cts_H */


/* [] END OF FILE */
