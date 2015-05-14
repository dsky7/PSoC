/*******************************************************************************
* File Name: rts.h  
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

#if !defined(CY_PINS_rts_H) /* Pins rts_H */
#define CY_PINS_rts_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rts_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 rts__PORT == 15 && ((rts__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    rts_Write(uint8 value) ;
void    rts_SetDriveMode(uint8 mode) ;
uint8   rts_ReadDataReg(void) ;
uint8   rts_Read(void) ;
uint8   rts_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define rts_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define rts_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define rts_DM_RES_UP          PIN_DM_RES_UP
#define rts_DM_RES_DWN         PIN_DM_RES_DWN
#define rts_DM_OD_LO           PIN_DM_OD_LO
#define rts_DM_OD_HI           PIN_DM_OD_HI
#define rts_DM_STRONG          PIN_DM_STRONG
#define rts_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define rts_MASK               rts__MASK
#define rts_SHIFT              rts__SHIFT
#define rts_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rts_PS                     (* (reg8 *) rts__PS)
/* Data Register */
#define rts_DR                     (* (reg8 *) rts__DR)
/* Port Number */
#define rts_PRT_NUM                (* (reg8 *) rts__PRT) 
/* Connect to Analog Globals */                                                  
#define rts_AG                     (* (reg8 *) rts__AG)                       
/* Analog MUX bux enable */
#define rts_AMUX                   (* (reg8 *) rts__AMUX) 
/* Bidirectional Enable */                                                        
#define rts_BIE                    (* (reg8 *) rts__BIE)
/* Bit-mask for Aliased Register Access */
#define rts_BIT_MASK               (* (reg8 *) rts__BIT_MASK)
/* Bypass Enable */
#define rts_BYP                    (* (reg8 *) rts__BYP)
/* Port wide control signals */                                                   
#define rts_CTL                    (* (reg8 *) rts__CTL)
/* Drive Modes */
#define rts_DM0                    (* (reg8 *) rts__DM0) 
#define rts_DM1                    (* (reg8 *) rts__DM1)
#define rts_DM2                    (* (reg8 *) rts__DM2) 
/* Input Buffer Disable Override */
#define rts_INP_DIS                (* (reg8 *) rts__INP_DIS)
/* LCD Common or Segment Drive */
#define rts_LCD_COM_SEG            (* (reg8 *) rts__LCD_COM_SEG)
/* Enable Segment LCD */
#define rts_LCD_EN                 (* (reg8 *) rts__LCD_EN)
/* Slew Rate Control */
#define rts_SLW                    (* (reg8 *) rts__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rts_PRTDSI__CAPS_SEL       (* (reg8 *) rts__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rts_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rts__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rts_PRTDSI__OE_SEL0        (* (reg8 *) rts__PRTDSI__OE_SEL0) 
#define rts_PRTDSI__OE_SEL1        (* (reg8 *) rts__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rts_PRTDSI__OUT_SEL0       (* (reg8 *) rts__PRTDSI__OUT_SEL0) 
#define rts_PRTDSI__OUT_SEL1       (* (reg8 *) rts__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rts_PRTDSI__SYNC_OUT       (* (reg8 *) rts__PRTDSI__SYNC_OUT) 


#if defined(rts__INTSTAT)  /* Interrupt Registers */

    #define rts_INTSTAT                (* (reg8 *) rts__INTSTAT)
    #define rts_SNAP                   (* (reg8 *) rts__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_rts_H */


/* [] END OF FILE */
