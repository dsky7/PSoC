/*******************************************************************************
* File Name: Enable1.h  
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

#if !defined(CY_PINS_Enable1_H) /* Pins Enable1_H */
#define CY_PINS_Enable1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Enable1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Enable1__PORT == 15 && ((Enable1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Enable1_Write(uint8 value) ;
void    Enable1_SetDriveMode(uint8 mode) ;
uint8   Enable1_ReadDataReg(void) ;
uint8   Enable1_Read(void) ;
uint8   Enable1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Enable1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Enable1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Enable1_DM_RES_UP          PIN_DM_RES_UP
#define Enable1_DM_RES_DWN         PIN_DM_RES_DWN
#define Enable1_DM_OD_LO           PIN_DM_OD_LO
#define Enable1_DM_OD_HI           PIN_DM_OD_HI
#define Enable1_DM_STRONG          PIN_DM_STRONG
#define Enable1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Enable1_MASK               Enable1__MASK
#define Enable1_SHIFT              Enable1__SHIFT
#define Enable1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Enable1_PS                     (* (reg8 *) Enable1__PS)
/* Data Register */
#define Enable1_DR                     (* (reg8 *) Enable1__DR)
/* Port Number */
#define Enable1_PRT_NUM                (* (reg8 *) Enable1__PRT) 
/* Connect to Analog Globals */                                                  
#define Enable1_AG                     (* (reg8 *) Enable1__AG)                       
/* Analog MUX bux enable */
#define Enable1_AMUX                   (* (reg8 *) Enable1__AMUX) 
/* Bidirectional Enable */                                                        
#define Enable1_BIE                    (* (reg8 *) Enable1__BIE)
/* Bit-mask for Aliased Register Access */
#define Enable1_BIT_MASK               (* (reg8 *) Enable1__BIT_MASK)
/* Bypass Enable */
#define Enable1_BYP                    (* (reg8 *) Enable1__BYP)
/* Port wide control signals */                                                   
#define Enable1_CTL                    (* (reg8 *) Enable1__CTL)
/* Drive Modes */
#define Enable1_DM0                    (* (reg8 *) Enable1__DM0) 
#define Enable1_DM1                    (* (reg8 *) Enable1__DM1)
#define Enable1_DM2                    (* (reg8 *) Enable1__DM2) 
/* Input Buffer Disable Override */
#define Enable1_INP_DIS                (* (reg8 *) Enable1__INP_DIS)
/* LCD Common or Segment Drive */
#define Enable1_LCD_COM_SEG            (* (reg8 *) Enable1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Enable1_LCD_EN                 (* (reg8 *) Enable1__LCD_EN)
/* Slew Rate Control */
#define Enable1_SLW                    (* (reg8 *) Enable1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Enable1_PRTDSI__CAPS_SEL       (* (reg8 *) Enable1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Enable1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Enable1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Enable1_PRTDSI__OE_SEL0        (* (reg8 *) Enable1__PRTDSI__OE_SEL0) 
#define Enable1_PRTDSI__OE_SEL1        (* (reg8 *) Enable1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Enable1_PRTDSI__OUT_SEL0       (* (reg8 *) Enable1__PRTDSI__OUT_SEL0) 
#define Enable1_PRTDSI__OUT_SEL1       (* (reg8 *) Enable1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Enable1_PRTDSI__SYNC_OUT       (* (reg8 *) Enable1__PRTDSI__SYNC_OUT) 


#if defined(Enable1__INTSTAT)  /* Interrupt Registers */

    #define Enable1_INTSTAT                (* (reg8 *) Enable1__INTSTAT)
    #define Enable1_SNAP                   (* (reg8 *) Enable1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Enable1_H */


/* [] END OF FILE */
