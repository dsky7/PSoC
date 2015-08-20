/*******************************************************************************
* File Name: CW_CCW_3.h  
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

#if !defined(CY_PINS_CW_CCW_3_H) /* Pins CW_CCW_3_H */
#define CY_PINS_CW_CCW_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CW_CCW_3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CW_CCW_3__PORT == 15 && ((CW_CCW_3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CW_CCW_3_Write(uint8 value) ;
void    CW_CCW_3_SetDriveMode(uint8 mode) ;
uint8   CW_CCW_3_ReadDataReg(void) ;
uint8   CW_CCW_3_Read(void) ;
uint8   CW_CCW_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CW_CCW_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CW_CCW_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CW_CCW_3_DM_RES_UP          PIN_DM_RES_UP
#define CW_CCW_3_DM_RES_DWN         PIN_DM_RES_DWN
#define CW_CCW_3_DM_OD_LO           PIN_DM_OD_LO
#define CW_CCW_3_DM_OD_HI           PIN_DM_OD_HI
#define CW_CCW_3_DM_STRONG          PIN_DM_STRONG
#define CW_CCW_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CW_CCW_3_MASK               CW_CCW_3__MASK
#define CW_CCW_3_SHIFT              CW_CCW_3__SHIFT
#define CW_CCW_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CW_CCW_3_PS                     (* (reg8 *) CW_CCW_3__PS)
/* Data Register */
#define CW_CCW_3_DR                     (* (reg8 *) CW_CCW_3__DR)
/* Port Number */
#define CW_CCW_3_PRT_NUM                (* (reg8 *) CW_CCW_3__PRT) 
/* Connect to Analog Globals */                                                  
#define CW_CCW_3_AG                     (* (reg8 *) CW_CCW_3__AG)                       
/* Analog MUX bux enable */
#define CW_CCW_3_AMUX                   (* (reg8 *) CW_CCW_3__AMUX) 
/* Bidirectional Enable */                                                        
#define CW_CCW_3_BIE                    (* (reg8 *) CW_CCW_3__BIE)
/* Bit-mask for Aliased Register Access */
#define CW_CCW_3_BIT_MASK               (* (reg8 *) CW_CCW_3__BIT_MASK)
/* Bypass Enable */
#define CW_CCW_3_BYP                    (* (reg8 *) CW_CCW_3__BYP)
/* Port wide control signals */                                                   
#define CW_CCW_3_CTL                    (* (reg8 *) CW_CCW_3__CTL)
/* Drive Modes */
#define CW_CCW_3_DM0                    (* (reg8 *) CW_CCW_3__DM0) 
#define CW_CCW_3_DM1                    (* (reg8 *) CW_CCW_3__DM1)
#define CW_CCW_3_DM2                    (* (reg8 *) CW_CCW_3__DM2) 
/* Input Buffer Disable Override */
#define CW_CCW_3_INP_DIS                (* (reg8 *) CW_CCW_3__INP_DIS)
/* LCD Common or Segment Drive */
#define CW_CCW_3_LCD_COM_SEG            (* (reg8 *) CW_CCW_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define CW_CCW_3_LCD_EN                 (* (reg8 *) CW_CCW_3__LCD_EN)
/* Slew Rate Control */
#define CW_CCW_3_SLW                    (* (reg8 *) CW_CCW_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CW_CCW_3_PRTDSI__CAPS_SEL       (* (reg8 *) CW_CCW_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CW_CCW_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CW_CCW_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CW_CCW_3_PRTDSI__OE_SEL0        (* (reg8 *) CW_CCW_3__PRTDSI__OE_SEL0) 
#define CW_CCW_3_PRTDSI__OE_SEL1        (* (reg8 *) CW_CCW_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CW_CCW_3_PRTDSI__OUT_SEL0       (* (reg8 *) CW_CCW_3__PRTDSI__OUT_SEL0) 
#define CW_CCW_3_PRTDSI__OUT_SEL1       (* (reg8 *) CW_CCW_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CW_CCW_3_PRTDSI__SYNC_OUT       (* (reg8 *) CW_CCW_3__PRTDSI__SYNC_OUT) 


#if defined(CW_CCW_3__INTSTAT)  /* Interrupt Registers */

    #define CW_CCW_3_INTSTAT                (* (reg8 *) CW_CCW_3__INTSTAT)
    #define CW_CCW_3_SNAP                   (* (reg8 *) CW_CCW_3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CW_CCW_3_H */


/* [] END OF FILE */
