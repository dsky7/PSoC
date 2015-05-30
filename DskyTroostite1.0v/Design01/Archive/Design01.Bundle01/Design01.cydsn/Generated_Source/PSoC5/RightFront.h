/*******************************************************************************
* File Name: RightFront.h  
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

#if !defined(CY_PINS_RightFront_H) /* Pins RightFront_H */
#define CY_PINS_RightFront_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RightFront_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RightFront__PORT == 15 && ((RightFront__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RightFront_Write(uint8 value) ;
void    RightFront_SetDriveMode(uint8 mode) ;
uint8   RightFront_ReadDataReg(void) ;
uint8   RightFront_Read(void) ;
uint8   RightFront_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RightFront_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RightFront_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RightFront_DM_RES_UP          PIN_DM_RES_UP
#define RightFront_DM_RES_DWN         PIN_DM_RES_DWN
#define RightFront_DM_OD_LO           PIN_DM_OD_LO
#define RightFront_DM_OD_HI           PIN_DM_OD_HI
#define RightFront_DM_STRONG          PIN_DM_STRONG
#define RightFront_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RightFront_MASK               RightFront__MASK
#define RightFront_SHIFT              RightFront__SHIFT
#define RightFront_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RightFront_PS                     (* (reg8 *) RightFront__PS)
/* Data Register */
#define RightFront_DR                     (* (reg8 *) RightFront__DR)
/* Port Number */
#define RightFront_PRT_NUM                (* (reg8 *) RightFront__PRT) 
/* Connect to Analog Globals */                                                  
#define RightFront_AG                     (* (reg8 *) RightFront__AG)                       
/* Analog MUX bux enable */
#define RightFront_AMUX                   (* (reg8 *) RightFront__AMUX) 
/* Bidirectional Enable */                                                        
#define RightFront_BIE                    (* (reg8 *) RightFront__BIE)
/* Bit-mask for Aliased Register Access */
#define RightFront_BIT_MASK               (* (reg8 *) RightFront__BIT_MASK)
/* Bypass Enable */
#define RightFront_BYP                    (* (reg8 *) RightFront__BYP)
/* Port wide control signals */                                                   
#define RightFront_CTL                    (* (reg8 *) RightFront__CTL)
/* Drive Modes */
#define RightFront_DM0                    (* (reg8 *) RightFront__DM0) 
#define RightFront_DM1                    (* (reg8 *) RightFront__DM1)
#define RightFront_DM2                    (* (reg8 *) RightFront__DM2) 
/* Input Buffer Disable Override */
#define RightFront_INP_DIS                (* (reg8 *) RightFront__INP_DIS)
/* LCD Common or Segment Drive */
#define RightFront_LCD_COM_SEG            (* (reg8 *) RightFront__LCD_COM_SEG)
/* Enable Segment LCD */
#define RightFront_LCD_EN                 (* (reg8 *) RightFront__LCD_EN)
/* Slew Rate Control */
#define RightFront_SLW                    (* (reg8 *) RightFront__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RightFront_PRTDSI__CAPS_SEL       (* (reg8 *) RightFront__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RightFront_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RightFront__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RightFront_PRTDSI__OE_SEL0        (* (reg8 *) RightFront__PRTDSI__OE_SEL0) 
#define RightFront_PRTDSI__OE_SEL1        (* (reg8 *) RightFront__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RightFront_PRTDSI__OUT_SEL0       (* (reg8 *) RightFront__PRTDSI__OUT_SEL0) 
#define RightFront_PRTDSI__OUT_SEL1       (* (reg8 *) RightFront__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RightFront_PRTDSI__SYNC_OUT       (* (reg8 *) RightFront__PRTDSI__SYNC_OUT) 


#if defined(RightFront__INTSTAT)  /* Interrupt Registers */

    #define RightFront_INTSTAT                (* (reg8 *) RightFront__INTSTAT)
    #define RightFront_SNAP                   (* (reg8 *) RightFront__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RightFront_H */


/* [] END OF FILE */
