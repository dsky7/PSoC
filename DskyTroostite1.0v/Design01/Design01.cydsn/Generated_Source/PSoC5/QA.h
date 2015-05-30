/*******************************************************************************
* File Name: QA.h  
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

#if !defined(CY_PINS_QA_H) /* Pins QA_H */
#define CY_PINS_QA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QA_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QA__PORT == 15 && ((QA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    QA_Write(uint8 value) ;
void    QA_SetDriveMode(uint8 mode) ;
uint8   QA_ReadDataReg(void) ;
uint8   QA_Read(void) ;
uint8   QA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define QA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define QA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define QA_DM_RES_UP          PIN_DM_RES_UP
#define QA_DM_RES_DWN         PIN_DM_RES_DWN
#define QA_DM_OD_LO           PIN_DM_OD_LO
#define QA_DM_OD_HI           PIN_DM_OD_HI
#define QA_DM_STRONG          PIN_DM_STRONG
#define QA_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define QA_MASK               QA__MASK
#define QA_SHIFT              QA__SHIFT
#define QA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QA_PS                     (* (reg8 *) QA__PS)
/* Data Register */
#define QA_DR                     (* (reg8 *) QA__DR)
/* Port Number */
#define QA_PRT_NUM                (* (reg8 *) QA__PRT) 
/* Connect to Analog Globals */                                                  
#define QA_AG                     (* (reg8 *) QA__AG)                       
/* Analog MUX bux enable */
#define QA_AMUX                   (* (reg8 *) QA__AMUX) 
/* Bidirectional Enable */                                                        
#define QA_BIE                    (* (reg8 *) QA__BIE)
/* Bit-mask for Aliased Register Access */
#define QA_BIT_MASK               (* (reg8 *) QA__BIT_MASK)
/* Bypass Enable */
#define QA_BYP                    (* (reg8 *) QA__BYP)
/* Port wide control signals */                                                   
#define QA_CTL                    (* (reg8 *) QA__CTL)
/* Drive Modes */
#define QA_DM0                    (* (reg8 *) QA__DM0) 
#define QA_DM1                    (* (reg8 *) QA__DM1)
#define QA_DM2                    (* (reg8 *) QA__DM2) 
/* Input Buffer Disable Override */
#define QA_INP_DIS                (* (reg8 *) QA__INP_DIS)
/* LCD Common or Segment Drive */
#define QA_LCD_COM_SEG            (* (reg8 *) QA__LCD_COM_SEG)
/* Enable Segment LCD */
#define QA_LCD_EN                 (* (reg8 *) QA__LCD_EN)
/* Slew Rate Control */
#define QA_SLW                    (* (reg8 *) QA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QA_PRTDSI__CAPS_SEL       (* (reg8 *) QA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QA_PRTDSI__OE_SEL0        (* (reg8 *) QA__PRTDSI__OE_SEL0) 
#define QA_PRTDSI__OE_SEL1        (* (reg8 *) QA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QA_PRTDSI__OUT_SEL0       (* (reg8 *) QA__PRTDSI__OUT_SEL0) 
#define QA_PRTDSI__OUT_SEL1       (* (reg8 *) QA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QA_PRTDSI__SYNC_OUT       (* (reg8 *) QA__PRTDSI__SYNC_OUT) 


#if defined(QA__INTSTAT)  /* Interrupt Registers */

    #define QA_INTSTAT                (* (reg8 *) QA__INTSTAT)
    #define QA_SNAP                   (* (reg8 *) QA__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QA_H */


/* [] END OF FILE */
