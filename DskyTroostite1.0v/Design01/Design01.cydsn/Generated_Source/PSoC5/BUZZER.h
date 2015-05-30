/*******************************************************************************
* File Name: BUZZER.h  
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

#if !defined(CY_PINS_BUZZER_H) /* Pins BUZZER_H */
#define CY_PINS_BUZZER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BUZZER_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BUZZER__PORT == 15 && ((BUZZER__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    BUZZER_Write(uint8 value) ;
void    BUZZER_SetDriveMode(uint8 mode) ;
uint8   BUZZER_ReadDataReg(void) ;
uint8   BUZZER_Read(void) ;
uint8   BUZZER_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BUZZER_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BUZZER_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BUZZER_DM_RES_UP          PIN_DM_RES_UP
#define BUZZER_DM_RES_DWN         PIN_DM_RES_DWN
#define BUZZER_DM_OD_LO           PIN_DM_OD_LO
#define BUZZER_DM_OD_HI           PIN_DM_OD_HI
#define BUZZER_DM_STRONG          PIN_DM_STRONG
#define BUZZER_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BUZZER_MASK               BUZZER__MASK
#define BUZZER_SHIFT              BUZZER__SHIFT
#define BUZZER_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BUZZER_PS                     (* (reg8 *) BUZZER__PS)
/* Data Register */
#define BUZZER_DR                     (* (reg8 *) BUZZER__DR)
/* Port Number */
#define BUZZER_PRT_NUM                (* (reg8 *) BUZZER__PRT) 
/* Connect to Analog Globals */                                                  
#define BUZZER_AG                     (* (reg8 *) BUZZER__AG)                       
/* Analog MUX bux enable */
#define BUZZER_AMUX                   (* (reg8 *) BUZZER__AMUX) 
/* Bidirectional Enable */                                                        
#define BUZZER_BIE                    (* (reg8 *) BUZZER__BIE)
/* Bit-mask for Aliased Register Access */
#define BUZZER_BIT_MASK               (* (reg8 *) BUZZER__BIT_MASK)
/* Bypass Enable */
#define BUZZER_BYP                    (* (reg8 *) BUZZER__BYP)
/* Port wide control signals */                                                   
#define BUZZER_CTL                    (* (reg8 *) BUZZER__CTL)
/* Drive Modes */
#define BUZZER_DM0                    (* (reg8 *) BUZZER__DM0) 
#define BUZZER_DM1                    (* (reg8 *) BUZZER__DM1)
#define BUZZER_DM2                    (* (reg8 *) BUZZER__DM2) 
/* Input Buffer Disable Override */
#define BUZZER_INP_DIS                (* (reg8 *) BUZZER__INP_DIS)
/* LCD Common or Segment Drive */
#define BUZZER_LCD_COM_SEG            (* (reg8 *) BUZZER__LCD_COM_SEG)
/* Enable Segment LCD */
#define BUZZER_LCD_EN                 (* (reg8 *) BUZZER__LCD_EN)
/* Slew Rate Control */
#define BUZZER_SLW                    (* (reg8 *) BUZZER__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BUZZER_PRTDSI__CAPS_SEL       (* (reg8 *) BUZZER__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BUZZER_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BUZZER__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BUZZER_PRTDSI__OE_SEL0        (* (reg8 *) BUZZER__PRTDSI__OE_SEL0) 
#define BUZZER_PRTDSI__OE_SEL1        (* (reg8 *) BUZZER__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BUZZER_PRTDSI__OUT_SEL0       (* (reg8 *) BUZZER__PRTDSI__OUT_SEL0) 
#define BUZZER_PRTDSI__OUT_SEL1       (* (reg8 *) BUZZER__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BUZZER_PRTDSI__SYNC_OUT       (* (reg8 *) BUZZER__PRTDSI__SYNC_OUT) 


#if defined(BUZZER__INTSTAT)  /* Interrupt Registers */

    #define BUZZER_INTSTAT                (* (reg8 *) BUZZER__INTSTAT)
    #define BUZZER_SNAP                   (* (reg8 *) BUZZER__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BUZZER_H */


/* [] END OF FILE */
