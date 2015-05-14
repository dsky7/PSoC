/*******************************************************************************
* File Name: CLCK2.h  
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

#if !defined(CY_PINS_CLCK2_H) /* Pins CLCK2_H */
#define CY_PINS_CLCK2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CLCK2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CLCK2__PORT == 15 && ((CLCK2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CLCK2_Write(uint8 value) ;
void    CLCK2_SetDriveMode(uint8 mode) ;
uint8   CLCK2_ReadDataReg(void) ;
uint8   CLCK2_Read(void) ;
uint8   CLCK2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CLCK2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CLCK2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CLCK2_DM_RES_UP          PIN_DM_RES_UP
#define CLCK2_DM_RES_DWN         PIN_DM_RES_DWN
#define CLCK2_DM_OD_LO           PIN_DM_OD_LO
#define CLCK2_DM_OD_HI           PIN_DM_OD_HI
#define CLCK2_DM_STRONG          PIN_DM_STRONG
#define CLCK2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CLCK2_MASK               CLCK2__MASK
#define CLCK2_SHIFT              CLCK2__SHIFT
#define CLCK2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CLCK2_PS                     (* (reg8 *) CLCK2__PS)
/* Data Register */
#define CLCK2_DR                     (* (reg8 *) CLCK2__DR)
/* Port Number */
#define CLCK2_PRT_NUM                (* (reg8 *) CLCK2__PRT) 
/* Connect to Analog Globals */                                                  
#define CLCK2_AG                     (* (reg8 *) CLCK2__AG)                       
/* Analog MUX bux enable */
#define CLCK2_AMUX                   (* (reg8 *) CLCK2__AMUX) 
/* Bidirectional Enable */                                                        
#define CLCK2_BIE                    (* (reg8 *) CLCK2__BIE)
/* Bit-mask for Aliased Register Access */
#define CLCK2_BIT_MASK               (* (reg8 *) CLCK2__BIT_MASK)
/* Bypass Enable */
#define CLCK2_BYP                    (* (reg8 *) CLCK2__BYP)
/* Port wide control signals */                                                   
#define CLCK2_CTL                    (* (reg8 *) CLCK2__CTL)
/* Drive Modes */
#define CLCK2_DM0                    (* (reg8 *) CLCK2__DM0) 
#define CLCK2_DM1                    (* (reg8 *) CLCK2__DM1)
#define CLCK2_DM2                    (* (reg8 *) CLCK2__DM2) 
/* Input Buffer Disable Override */
#define CLCK2_INP_DIS                (* (reg8 *) CLCK2__INP_DIS)
/* LCD Common or Segment Drive */
#define CLCK2_LCD_COM_SEG            (* (reg8 *) CLCK2__LCD_COM_SEG)
/* Enable Segment LCD */
#define CLCK2_LCD_EN                 (* (reg8 *) CLCK2__LCD_EN)
/* Slew Rate Control */
#define CLCK2_SLW                    (* (reg8 *) CLCK2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CLCK2_PRTDSI__CAPS_SEL       (* (reg8 *) CLCK2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CLCK2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CLCK2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CLCK2_PRTDSI__OE_SEL0        (* (reg8 *) CLCK2__PRTDSI__OE_SEL0) 
#define CLCK2_PRTDSI__OE_SEL1        (* (reg8 *) CLCK2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CLCK2_PRTDSI__OUT_SEL0       (* (reg8 *) CLCK2__PRTDSI__OUT_SEL0) 
#define CLCK2_PRTDSI__OUT_SEL1       (* (reg8 *) CLCK2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CLCK2_PRTDSI__SYNC_OUT       (* (reg8 *) CLCK2__PRTDSI__SYNC_OUT) 


#if defined(CLCK2__INTSTAT)  /* Interrupt Registers */

    #define CLCK2_INTSTAT                (* (reg8 *) CLCK2__INTSTAT)
    #define CLCK2_SNAP                   (* (reg8 *) CLCK2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CLCK2_H */


/* [] END OF FILE */
