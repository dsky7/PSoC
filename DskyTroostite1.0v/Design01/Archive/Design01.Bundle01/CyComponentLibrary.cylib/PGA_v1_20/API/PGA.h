/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the PGA User Module.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include "cytypes.h"
#include "cyfitter.h"

#if !defined(CY_PGA_`$INSTANCE_NAME`_H) 
#define CY_PGA_`$INSTANCE_NAME`_H 

/***************************************
*        Function Prototypes 
***************************************/

void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetPower(uint8 power);
void    `$INSTANCE_NAME`_SetGain(uint8 gain);


/***************************************
*       Initialization Values
***************************************/

#define `$INSTANCE_NAME`_DEFAULT_GAIN  `$Gain`
#define `$INSTANCE_NAME`_VREF_MODE     (`$Vref_Input` ? 0x00 : `$INSTANCE_NAME`_GNDVREF_E )
#define `$INSTANCE_NAME`_DEFAULT_POWER `$Power`
/* #define `$INSTANCE_NAME`_ACLK_ENABLE   ((`$Vref_Input` ? 0 : 1) | `$Minimum_Vdda` )  */
#define `$INSTANCE_NAME`_ACLK_ENABLE   `$Minimum_Vdda` 

/***************************************
*              Registers        
***************************************/

#define `$INSTANCE_NAME`_CR0    (* (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR1    (* (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR2    (* (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_PWRMGR (* (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )  /* Power manager */
#define `$INSTANCE_NAME`_BST    (* (reg8 *) `$INSTANCE_NAME`_SC__BST )

#if (`$INSTANCE_NAME`_ACLK_ENABLE)
   #define `$INSTANCE_NAME`_ACLK_PWRMGR (* (reg8 *) `$INSTANCE_NAME`_ScBoostClk__PM_ACT_CFG )  /* Power manager */
   #define `$INSTANCE_NAME`_ACLK_ACT_PWR_EN   `$INSTANCE_NAME`_ScBoostClk__PM_ACT_MSK /* Power enable mask */
#endif

/***************************************
*              Constants        
***************************************/

/* Power constants for SetPower function */
#define `$INSTANCE_NAME`_MINPOWER   0x00u
#define `$INSTANCE_NAME`_LOWPOWER   0x01u
#define `$INSTANCE_NAME`_MEDPOWER   0x02u
#define `$INSTANCE_NAME`_HIGHPOWER  0x03u

/* Constants for SetGain function */
#define `$INSTANCE_NAME`_GAIN_01    0x00u
#define `$INSTANCE_NAME`_GAIN_02    0x01u
#define `$INSTANCE_NAME`_GAIN_04    0x02u
#define `$INSTANCE_NAME`_GAIN_08    0x03u
#define `$INSTANCE_NAME`_GAIN_16    0x04u
#define `$INSTANCE_NAME`_GAIN_24    0x05u
#define `$INSTANCE_NAME`_GAIN_25    0x06u
#define `$INSTANCE_NAME`_GAIN_32    0x07u
#define `$INSTANCE_NAME`_GAIN_48    0x08u
#define `$INSTANCE_NAME`_GAIN_50    0x09u
#define `$INSTANCE_NAME`_GAIN_MAX   0x09u

/* Constant for VDDA Threshold */
#define `$INSTANCE_NAME`_CYDEV_VDDA_MV  CYDEV_VDDA_MV
#define `$INSTANCE_NAME`_VDDA_THRESHOLD_MV 3500u

/* SC_MISC constants */
#define `$INSTANCE_NAME`_PUMP_FORCE     0x20u
#define `$INSTANCE_NAME`_PUMP_AUTO      0x10u
#define `$INSTANCE_NAME`_DIFF_PGA_1_3   0x02u
#define `$INSTANCE_NAME`_DIFF_PGA_0_2   0x01u


/* CR0 SC/CT Control Register 0 definitions */
#define `$INSTANCE_NAME`_MODE_PGA      0x0Cu

/* CR1 SC/CT Control Register 1 definitions */
/* Bit Field  SC_COMP_ENUM                  */
#define `$INSTANCE_NAME`_COMP_MASK     0x0Cu
#define `$INSTANCE_NAME`_COMP_3P0PF    0x00u
#define `$INSTANCE_NAME`_COMP_3P6PF    0x04u
#define `$INSTANCE_NAME`_COMP_4P35PF   0x08u
#define `$INSTANCE_NAME`_COMP_5P1PF    0x0Cu

/* Bit Field  SC_DIV2_ENUM                  */
#define `$INSTANCE_NAME`_DIV2_MASK     0x10u
#define `$INSTANCE_NAME`_DIV2_DISABLE  0x00u
#define `$INSTANCE_NAME`_DIV2_ENABLE   0x10u

/* Bit Field  SC_DRIVE_ENUM                 */
#define `$INSTANCE_NAME`_DRIVE_MASK    0x03u
#define `$INSTANCE_NAME`_DRIVE_280UA   0x00u
#define `$INSTANCE_NAME`_DRIVE_420UA   0x01u
#define `$INSTANCE_NAME`_DRIVE_530UA   0x02u
#define `$INSTANCE_NAME`_DRIVE_650UA   0x03u

/* Bit Field  SC_PGA_MODE_ENUM              */
#define `$INSTANCE_NAME`_PGA_MODE_MASK 0x20u
#define `$INSTANCE_NAME`_PGA_INV       0x00u
#define `$INSTANCE_NAME`_PGA_NINV      0x20u

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM          */
#define `$INSTANCE_NAME`_BIAS_MASK     0x01u
#define `$INSTANCE_NAME`_BIAS_NORMAL   0x00u
#define `$INSTANCE_NAME`_BIAS_LOW      0x01u

/* Bit Field  SC_PGA_GNDVREF_ENUM           */
#define `$INSTANCE_NAME`_GNDVREF_MASK  0x80u
#define `$INSTANCE_NAME`_GNDVREF_DI    0x00u
#define `$INSTANCE_NAME`_GNDVREF_E     0x80u

/* Bit Field  SC_R20_40B_ENUM               */
#define `$INSTANCE_NAME`_R20_40B_MASK  0x02u
#define `$INSTANCE_NAME`_R20_40B_40K   0x00u
#define `$INSTANCE_NAME`_R20_40B_20K   0x02u

/* Bit Field  SC_REDC_ENUM                  */
#define `$INSTANCE_NAME`_REDC_MASK     0x0Cu
#define `$INSTANCE_NAME`_REDC_00       0x00u
#define `$INSTANCE_NAME`_REDC_01       0x04u
#define `$INSTANCE_NAME`_REDC_10       0x08u
#define `$INSTANCE_NAME`_REDC_11       0x0Cu

/* Bit Field  SC_RVAL_ENUM                  */
#define `$INSTANCE_NAME`_RVAL_MASK     0x70u
#define `$INSTANCE_NAME`_RVAL_20K      0x00u
#define `$INSTANCE_NAME`_RVAL_30K      0x10u
#define `$INSTANCE_NAME`_RVAL_40K      0x20u
#define `$INSTANCE_NAME`_RVAL_60K      0x30u
#define `$INSTANCE_NAME`_RVAL_120K     0x40u
#define `$INSTANCE_NAME`_RVAL_250K     0x50u
#define `$INSTANCE_NAME`_RVAL_500K     0x60u
#define `$INSTANCE_NAME`_RVAL_1000K    0x70u

/* Bit Field  PGA_GAIN_ENUM    */
#define `$INSTANCE_NAME`_PGA_GAIN_MASK  0x72u
#define `$INSTANCE_NAME`_PGA_GAIN_01    0x00u
#define `$INSTANCE_NAME`_PGA_GAIN_02    0x10u
#define `$INSTANCE_NAME`_PGA_GAIN_04    0x20u
#define `$INSTANCE_NAME`_PGA_GAIN_08    0x30u
#define `$INSTANCE_NAME`_PGA_GAIN_16    0x40u
#define `$INSTANCE_NAME`_PGA_GAIN_24    0x50u
#define `$INSTANCE_NAME`_PGA_GAIN_25    0x70u
#define `$INSTANCE_NAME`_PGA_GAIN_32    0x52u
#define `$INSTANCE_NAME`_PGA_GAIN_48    0x62u
#define `$INSTANCE_NAME`_PGA_GAIN_50    0x72u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define `$INSTANCE_NAME`_ACT_PWR_EN   `$INSTANCE_NAME`_SC__PM_ACT_MSK /* Power enable mask */

/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

#endif /* CY_PGA_`$INSTANCE_NAME`_H */

/* [] END OF FILE */

