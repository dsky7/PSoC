/*******************************************************************************
* File Name: STB.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_STB_H) /* Pins STB_H */
#define CY_PINS_STB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "STB_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 STB__PORT == 15 && ((STB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    STB_Write(uint8 value) ;
void    STB_SetDriveMode(uint8 mode) ;
uint8   STB_ReadDataReg(void) ;
uint8   STB_Read(void) ;
uint8   STB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define STB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define STB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define STB_DM_RES_UP          PIN_DM_RES_UP
#define STB_DM_RES_DWN         PIN_DM_RES_DWN
#define STB_DM_OD_LO           PIN_DM_OD_LO
#define STB_DM_OD_HI           PIN_DM_OD_HI
#define STB_DM_STRONG          PIN_DM_STRONG
#define STB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define STB_MASK               STB__MASK
#define STB_SHIFT              STB__SHIFT
#define STB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define STB_PS                     (* (reg8 *) STB__PS)
/* Data Register */
#define STB_DR                     (* (reg8 *) STB__DR)
/* Port Number */
#define STB_PRT_NUM                (* (reg8 *) STB__PRT) 
/* Connect to Analog Globals */                                                  
#define STB_AG                     (* (reg8 *) STB__AG)                       
/* Analog MUX bux enable */
#define STB_AMUX                   (* (reg8 *) STB__AMUX) 
/* Bidirectional Enable */                                                        
#define STB_BIE                    (* (reg8 *) STB__BIE)
/* Bit-mask for Aliased Register Access */
#define STB_BIT_MASK               (* (reg8 *) STB__BIT_MASK)
/* Bypass Enable */
#define STB_BYP                    (* (reg8 *) STB__BYP)
/* Port wide control signals */                                                   
#define STB_CTL                    (* (reg8 *) STB__CTL)
/* Drive Modes */
#define STB_DM0                    (* (reg8 *) STB__DM0) 
#define STB_DM1                    (* (reg8 *) STB__DM1)
#define STB_DM2                    (* (reg8 *) STB__DM2) 
/* Input Buffer Disable Override */
#define STB_INP_DIS                (* (reg8 *) STB__INP_DIS)
/* LCD Common or Segment Drive */
#define STB_LCD_COM_SEG            (* (reg8 *) STB__LCD_COM_SEG)
/* Enable Segment LCD */
#define STB_LCD_EN                 (* (reg8 *) STB__LCD_EN)
/* Slew Rate Control */
#define STB_SLW                    (* (reg8 *) STB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define STB_PRTDSI__CAPS_SEL       (* (reg8 *) STB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define STB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) STB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define STB_PRTDSI__OE_SEL0        (* (reg8 *) STB__PRTDSI__OE_SEL0) 
#define STB_PRTDSI__OE_SEL1        (* (reg8 *) STB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define STB_PRTDSI__OUT_SEL0       (* (reg8 *) STB__PRTDSI__OUT_SEL0) 
#define STB_PRTDSI__OUT_SEL1       (* (reg8 *) STB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define STB_PRTDSI__SYNC_OUT       (* (reg8 *) STB__PRTDSI__SYNC_OUT) 


#if defined(STB__INTSTAT)  /* Interrupt Registers */

    #define STB_INTSTAT                (* (reg8 *) STB__INTSTAT)
    #define STB_SNAP                   (* (reg8 *) STB__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_STB_H */


/* [] END OF FILE */
