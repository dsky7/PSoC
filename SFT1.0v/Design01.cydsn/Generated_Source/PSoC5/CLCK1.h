/*******************************************************************************
* File Name: CLCK1.h  
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

#if !defined(CY_PINS_CLCK1_H) /* Pins CLCK1_H */
#define CY_PINS_CLCK1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CLCK1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CLCK1__PORT == 15 && ((CLCK1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CLCK1_Write(uint8 value) ;
void    CLCK1_SetDriveMode(uint8 mode) ;
uint8   CLCK1_ReadDataReg(void) ;
uint8   CLCK1_Read(void) ;
uint8   CLCK1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CLCK1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CLCK1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CLCK1_DM_RES_UP          PIN_DM_RES_UP
#define CLCK1_DM_RES_DWN         PIN_DM_RES_DWN
#define CLCK1_DM_OD_LO           PIN_DM_OD_LO
#define CLCK1_DM_OD_HI           PIN_DM_OD_HI
#define CLCK1_DM_STRONG          PIN_DM_STRONG
#define CLCK1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CLCK1_MASK               CLCK1__MASK
#define CLCK1_SHIFT              CLCK1__SHIFT
#define CLCK1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CLCK1_PS                     (* (reg8 *) CLCK1__PS)
/* Data Register */
#define CLCK1_DR                     (* (reg8 *) CLCK1__DR)
/* Port Number */
#define CLCK1_PRT_NUM                (* (reg8 *) CLCK1__PRT) 
/* Connect to Analog Globals */                                                  
#define CLCK1_AG                     (* (reg8 *) CLCK1__AG)                       
/* Analog MUX bux enable */
#define CLCK1_AMUX                   (* (reg8 *) CLCK1__AMUX) 
/* Bidirectional Enable */                                                        
#define CLCK1_BIE                    (* (reg8 *) CLCK1__BIE)
/* Bit-mask for Aliased Register Access */
#define CLCK1_BIT_MASK               (* (reg8 *) CLCK1__BIT_MASK)
/* Bypass Enable */
#define CLCK1_BYP                    (* (reg8 *) CLCK1__BYP)
/* Port wide control signals */                                                   
#define CLCK1_CTL                    (* (reg8 *) CLCK1__CTL)
/* Drive Modes */
#define CLCK1_DM0                    (* (reg8 *) CLCK1__DM0) 
#define CLCK1_DM1                    (* (reg8 *) CLCK1__DM1)
#define CLCK1_DM2                    (* (reg8 *) CLCK1__DM2) 
/* Input Buffer Disable Override */
#define CLCK1_INP_DIS                (* (reg8 *) CLCK1__INP_DIS)
/* LCD Common or Segment Drive */
#define CLCK1_LCD_COM_SEG            (* (reg8 *) CLCK1__LCD_COM_SEG)
/* Enable Segment LCD */
#define CLCK1_LCD_EN                 (* (reg8 *) CLCK1__LCD_EN)
/* Slew Rate Control */
#define CLCK1_SLW                    (* (reg8 *) CLCK1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CLCK1_PRTDSI__CAPS_SEL       (* (reg8 *) CLCK1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CLCK1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CLCK1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CLCK1_PRTDSI__OE_SEL0        (* (reg8 *) CLCK1__PRTDSI__OE_SEL0) 
#define CLCK1_PRTDSI__OE_SEL1        (* (reg8 *) CLCK1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CLCK1_PRTDSI__OUT_SEL0       (* (reg8 *) CLCK1__PRTDSI__OUT_SEL0) 
#define CLCK1_PRTDSI__OUT_SEL1       (* (reg8 *) CLCK1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CLCK1_PRTDSI__SYNC_OUT       (* (reg8 *) CLCK1__PRTDSI__SYNC_OUT) 


#if defined(CLCK1__INTSTAT)  /* Interrupt Registers */

    #define CLCK1_INTSTAT                (* (reg8 *) CLCK1__INTSTAT)
    #define CLCK1_SNAP                   (* (reg8 *) CLCK1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CLCK1_H */


/* [] END OF FILE */
