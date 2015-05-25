/*******************************************************************************
* File Name: RUN_BRAKE_3.h  
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

#if !defined(CY_PINS_RUN_BRAKE_3_H) /* Pins RUN_BRAKE_3_H */
#define CY_PINS_RUN_BRAKE_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RUN_BRAKE_3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RUN_BRAKE_3__PORT == 15 && ((RUN_BRAKE_3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RUN_BRAKE_3_Write(uint8 value) ;
void    RUN_BRAKE_3_SetDriveMode(uint8 mode) ;
uint8   RUN_BRAKE_3_ReadDataReg(void) ;
uint8   RUN_BRAKE_3_Read(void) ;
uint8   RUN_BRAKE_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RUN_BRAKE_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RUN_BRAKE_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RUN_BRAKE_3_DM_RES_UP          PIN_DM_RES_UP
#define RUN_BRAKE_3_DM_RES_DWN         PIN_DM_RES_DWN
#define RUN_BRAKE_3_DM_OD_LO           PIN_DM_OD_LO
#define RUN_BRAKE_3_DM_OD_HI           PIN_DM_OD_HI
#define RUN_BRAKE_3_DM_STRONG          PIN_DM_STRONG
#define RUN_BRAKE_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RUN_BRAKE_3_MASK               RUN_BRAKE_3__MASK
#define RUN_BRAKE_3_SHIFT              RUN_BRAKE_3__SHIFT
#define RUN_BRAKE_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RUN_BRAKE_3_PS                     (* (reg8 *) RUN_BRAKE_3__PS)
/* Data Register */
#define RUN_BRAKE_3_DR                     (* (reg8 *) RUN_BRAKE_3__DR)
/* Port Number */
#define RUN_BRAKE_3_PRT_NUM                (* (reg8 *) RUN_BRAKE_3__PRT) 
/* Connect to Analog Globals */                                                  
#define RUN_BRAKE_3_AG                     (* (reg8 *) RUN_BRAKE_3__AG)                       
/* Analog MUX bux enable */
#define RUN_BRAKE_3_AMUX                   (* (reg8 *) RUN_BRAKE_3__AMUX) 
/* Bidirectional Enable */                                                        
#define RUN_BRAKE_3_BIE                    (* (reg8 *) RUN_BRAKE_3__BIE)
/* Bit-mask for Aliased Register Access */
#define RUN_BRAKE_3_BIT_MASK               (* (reg8 *) RUN_BRAKE_3__BIT_MASK)
/* Bypass Enable */
#define RUN_BRAKE_3_BYP                    (* (reg8 *) RUN_BRAKE_3__BYP)
/* Port wide control signals */                                                   
#define RUN_BRAKE_3_CTL                    (* (reg8 *) RUN_BRAKE_3__CTL)
/* Drive Modes */
#define RUN_BRAKE_3_DM0                    (* (reg8 *) RUN_BRAKE_3__DM0) 
#define RUN_BRAKE_3_DM1                    (* (reg8 *) RUN_BRAKE_3__DM1)
#define RUN_BRAKE_3_DM2                    (* (reg8 *) RUN_BRAKE_3__DM2) 
/* Input Buffer Disable Override */
#define RUN_BRAKE_3_INP_DIS                (* (reg8 *) RUN_BRAKE_3__INP_DIS)
/* LCD Common or Segment Drive */
#define RUN_BRAKE_3_LCD_COM_SEG            (* (reg8 *) RUN_BRAKE_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define RUN_BRAKE_3_LCD_EN                 (* (reg8 *) RUN_BRAKE_3__LCD_EN)
/* Slew Rate Control */
#define RUN_BRAKE_3_SLW                    (* (reg8 *) RUN_BRAKE_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RUN_BRAKE_3_PRTDSI__CAPS_SEL       (* (reg8 *) RUN_BRAKE_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RUN_BRAKE_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RUN_BRAKE_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RUN_BRAKE_3_PRTDSI__OE_SEL0        (* (reg8 *) RUN_BRAKE_3__PRTDSI__OE_SEL0) 
#define RUN_BRAKE_3_PRTDSI__OE_SEL1        (* (reg8 *) RUN_BRAKE_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RUN_BRAKE_3_PRTDSI__OUT_SEL0       (* (reg8 *) RUN_BRAKE_3__PRTDSI__OUT_SEL0) 
#define RUN_BRAKE_3_PRTDSI__OUT_SEL1       (* (reg8 *) RUN_BRAKE_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RUN_BRAKE_3_PRTDSI__SYNC_OUT       (* (reg8 *) RUN_BRAKE_3__PRTDSI__SYNC_OUT) 


#if defined(RUN_BRAKE_3__INTSTAT)  /* Interrupt Registers */

    #define RUN_BRAKE_3_INTSTAT                (* (reg8 *) RUN_BRAKE_3__INTSTAT)
    #define RUN_BRAKE_3_SNAP                   (* (reg8 *) RUN_BRAKE_3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RUN_BRAKE_3_H */


/* [] END OF FILE */
