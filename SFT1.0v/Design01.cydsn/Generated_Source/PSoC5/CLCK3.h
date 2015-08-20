/*******************************************************************************
* File Name: CLCK3.h  
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

#if !defined(CY_PINS_CLCK3_H) /* Pins CLCK3_H */
#define CY_PINS_CLCK3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CLCK3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CLCK3__PORT == 15 && ((CLCK3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CLCK3_Write(uint8 value) ;
void    CLCK3_SetDriveMode(uint8 mode) ;
uint8   CLCK3_ReadDataReg(void) ;
uint8   CLCK3_Read(void) ;
uint8   CLCK3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CLCK3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CLCK3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CLCK3_DM_RES_UP          PIN_DM_RES_UP
#define CLCK3_DM_RES_DWN         PIN_DM_RES_DWN
#define CLCK3_DM_OD_LO           PIN_DM_OD_LO
#define CLCK3_DM_OD_HI           PIN_DM_OD_HI
#define CLCK3_DM_STRONG          PIN_DM_STRONG
#define CLCK3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CLCK3_MASK               CLCK3__MASK
#define CLCK3_SHIFT              CLCK3__SHIFT
#define CLCK3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CLCK3_PS                     (* (reg8 *) CLCK3__PS)
/* Data Register */
#define CLCK3_DR                     (* (reg8 *) CLCK3__DR)
/* Port Number */
#define CLCK3_PRT_NUM                (* (reg8 *) CLCK3__PRT) 
/* Connect to Analog Globals */                                                  
#define CLCK3_AG                     (* (reg8 *) CLCK3__AG)                       
/* Analog MUX bux enable */
#define CLCK3_AMUX                   (* (reg8 *) CLCK3__AMUX) 
/* Bidirectional Enable */                                                        
#define CLCK3_BIE                    (* (reg8 *) CLCK3__BIE)
/* Bit-mask for Aliased Register Access */
#define CLCK3_BIT_MASK               (* (reg8 *) CLCK3__BIT_MASK)
/* Bypass Enable */
#define CLCK3_BYP                    (* (reg8 *) CLCK3__BYP)
/* Port wide control signals */                                                   
#define CLCK3_CTL                    (* (reg8 *) CLCK3__CTL)
/* Drive Modes */
#define CLCK3_DM0                    (* (reg8 *) CLCK3__DM0) 
#define CLCK3_DM1                    (* (reg8 *) CLCK3__DM1)
#define CLCK3_DM2                    (* (reg8 *) CLCK3__DM2) 
/* Input Buffer Disable Override */
#define CLCK3_INP_DIS                (* (reg8 *) CLCK3__INP_DIS)
/* LCD Common or Segment Drive */
#define CLCK3_LCD_COM_SEG            (* (reg8 *) CLCK3__LCD_COM_SEG)
/* Enable Segment LCD */
#define CLCK3_LCD_EN                 (* (reg8 *) CLCK3__LCD_EN)
/* Slew Rate Control */
#define CLCK3_SLW                    (* (reg8 *) CLCK3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CLCK3_PRTDSI__CAPS_SEL       (* (reg8 *) CLCK3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CLCK3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CLCK3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CLCK3_PRTDSI__OE_SEL0        (* (reg8 *) CLCK3__PRTDSI__OE_SEL0) 
#define CLCK3_PRTDSI__OE_SEL1        (* (reg8 *) CLCK3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CLCK3_PRTDSI__OUT_SEL0       (* (reg8 *) CLCK3__PRTDSI__OUT_SEL0) 
#define CLCK3_PRTDSI__OUT_SEL1       (* (reg8 *) CLCK3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CLCK3_PRTDSI__SYNC_OUT       (* (reg8 *) CLCK3__PRTDSI__SYNC_OUT) 


#if defined(CLCK3__INTSTAT)  /* Interrupt Registers */

    #define CLCK3_INTSTAT                (* (reg8 *) CLCK3__INTSTAT)
    #define CLCK3_SNAP                   (* (reg8 *) CLCK3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CLCK3_H */


/* [] END OF FILE */
