/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Mixer component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_MIXER_`$INSTANCE_NAME`_H) 
#define CY_MIXER_`$INSTANCE_NAME`_H 

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* PSoC3 ES2 or early */
#define `$INSTANCE_NAME`_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES1 or early */
#define `$INSTANCE_NAME`_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define `$INSTANCE_NAME`_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES2 or later */
#define `$INSTANCE_NAME`_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct _`$INSTANCE_NAME`_backupStruct
{
    uint8   enableState;
}   `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetPower(uint8 power) `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`;
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;


/***************************************
*              Constants        
***************************************/

/* Constants for Mixer Type */
#define `$INSTANCE_NAME`_CTMIXER                (0x00u)
#define `$INSTANCE_NAME`_DTMIXER                (0x01u)

/* Constants for Local Oscillator Freq */
#define `$INSTANCE_NAME`_LO_LT_100K             (0x00u)
#define `$INSTANCE_NAME`_LO_GTE_100K            (0x01u)

/* Constants for Minimum Vdda paramater */
#define  `$INSTANCE_NAME`_MIN_VDDA_GTE_2_7V     (0x00u)
#define  `$INSTANCE_NAME`_MIN_VDDA_LT_2_7V      (0x01u)

/* Constants for SetPower function */
#define `$INSTANCE_NAME`_MINPOWER               (0x00u)
#define `$INSTANCE_NAME`_LOWPOWER               (0x01u)
#define `$INSTANCE_NAME`_MEDPOWER               (0x02u)
#define `$INSTANCE_NAME`_HIGHPOWER              (0x03u)

/* Constant for VDDA Threshold */
#define `$INSTANCE_NAME`_CYDEV_VDDA_MV          (CYDEV_VDDA_MV)
#define `$INSTANCE_NAME`_VDDA_THRESHOLD_MV      (3500u)


/***************************************
*       Initial Paramater Values
***************************************/

#define `$INSTANCE_NAME`_MIXER_TYPE             (`$Mixer_Type`u)
#define `$INSTANCE_NAME`_INIT_POWER             (`$Power`u)
#define `$INSTANCE_NAME`_LO_FREQ_FLAG           (`$LO_Freq`u)
#define `$INSTANCE_NAME`_MIN_VDDA               (`$Minimum_Vdda`u)


/***************************************
*              Registers        
***************************************/

/* SC Block Configuration Registers */
#define `$INSTANCE_NAME`_CR0_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR0_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR1_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR1_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR2_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CR2_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CLK_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CLK )  /* SC Block clk control */
#define `$INSTANCE_NAME`_CLK_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CLK )
#define `$INSTANCE_NAME`_BSTCLK_REG             (* (reg8 *) `$INSTANCE_NAME`_SC__BST )  /* SC Boost clk Control */
#define `$INSTANCE_NAME`_BSTCLK_PTR             (  (reg8 *) `$INSTANCE_NAME`_SC__BST )
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG         (* (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )  /* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR         (  (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG        (* (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )  /* Power manager */
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR        (  (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )

/* Pump clock selectin register */
#define `$INSTANCE_NAME`_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)   
#define `$INSTANCE_NAME`_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC_REG            (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define `$INSTANCE_NAME`_SC_MISC_PTR            (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define `$INSTANCE_NAME`_ACT_PWR_EN             `$INSTANCE_NAME`_SC__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
#define `$INSTANCE_NAME`_STBY_PWR_EN             `$INSTANCE_NAME`_SC__PM_STBY_MSK /* Power enable mask */



/***************************************
*        Register Constants        
***************************************/

/* ANIF.PUMP.CR1 Constants */
#define `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL     (0x80u)

/* SC_MISC constants */
#define `$INSTANCE_NAME`_PUMP_FORCE             (0x20u)
#define `$INSTANCE_NAME`_PUMP_AUTO              (0x10u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3           (0x02u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2           (0x01u)

/* CR0 SC Block Control Register 0 definitions */

/* Bit Field SC_MODE_ENUM - SCxx_CR0[3:1] */
#define `$INSTANCE_NAME`_MODE_CTMIXER           (0x02u << 1)
#define `$INSTANCE_NAME`_MODE_DTMIXER           (0x03u << 1)

/* CR1 SC Block Control Register 1 definitions */

/* Bit Field  SC_DRIVE_ENUM - SCxx_CR1[1:0] */
#define `$INSTANCE_NAME`_DRIVE_MASK             (0x03u)
#define `$INSTANCE_NAME`_DRIVE_280UA            (0x00u)
#define `$INSTANCE_NAME`_DRIVE_420UA            (0x01u)
#define `$INSTANCE_NAME`_DRIVE_530UA            (0x02u)
#define `$INSTANCE_NAME`_DRIVE_650UA            (0x03u)

/* Bit Field  SC_COMP_ENUM - SCxx_CR1[3:2] */
#define `$INSTANCE_NAME`_COMP_MASK              (0x03u << 2)
#define `$INSTANCE_NAME`_COMP_3P0PF             (0x00u << 2)
#define `$INSTANCE_NAME`_COMP_3P6PF             (0x01u << 2)
#define `$INSTANCE_NAME`_COMP_4P35PF            (0x02u << 2)
#define `$INSTANCE_NAME`_COMP_5P1PF             (0x03u << 2)

/* Bit Field  SC_DIV2_ENUM - SCxx_CR1[4] */
#define `$INSTANCE_NAME`_DIV2                   (0x01u << 4)
#define `$INSTANCE_NAME`_DIV2_DISABLE           (0x00u << 4)
#define `$INSTANCE_NAME`_DIV2_ENABLE            (0x01u << 4)

/* Bit Field  SC_GAIN_ENUM - SCxx_CR1[5] */
#define `$INSTANCE_NAME`_GAIN                    (0x01u << 5)
#define `$INSTANCE_NAME`_GAIN_0DB                (0x00u << 5)
#define `$INSTANCE_NAME`_GAIN_6DB                (0x01u << 5)

/* CR2 SC Block Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM - SCxx_CR2[0] */
#define `$INSTANCE_NAME`_BIAS                    (0x01u)
#define `$INSTANCE_NAME`_BIAS_NORMAL             (0x00u)
#define `$INSTANCE_NAME`_BIAS_LOW                (0x01u)

/* Bit Field  SC_R20_40B_ENUM - SCxx_CR2[1] */
#define `$INSTANCE_NAME`_R20_40B                 (0x01u << 1)
#define `$INSTANCE_NAME`_R20_40B_40K             (0x00u << 1)
#define `$INSTANCE_NAME`_R20_40B_20K             (0x01u << 1)

/* Bit Field  SC_REDC_ENUM  - SCxx_CR2[3:2] */
#define `$INSTANCE_NAME`_REDC_MASK               (0x03u << 2)
#define `$INSTANCE_NAME`_REDC_00                 (0x00u << 2)
#define `$INSTANCE_NAME`_REDC_01                 (0x01u << 2)
#define `$INSTANCE_NAME`_REDC_10                 (0x02u << 2)
#define `$INSTANCE_NAME`_REDC_11                 (0x03u << 2)

/* Bit Field  SC_RVAL_ENUM  - SCxx_CR2[6:4] */
#define `$INSTANCE_NAME`_RVAL_MASK               (0x07u << 4)
#define `$INSTANCE_NAME`_RVAL_20K                (0x00u << 4)
#define `$INSTANCE_NAME`_RVAL_30K                (0x01u << 4)
#define `$INSTANCE_NAME`_RVAL_40K                (0x02u << 4)
#define `$INSTANCE_NAME`_RVAL_80K                (0x03u << 4)
#define `$INSTANCE_NAME`_RVAL_120K               (0x04u << 4)
#define `$INSTANCE_NAME`_RVAL_250K               (0x05u << 4)
#define `$INSTANCE_NAME`_RVAL_500K               (0x06u << 4)
#define `$INSTANCE_NAME`_RVAL_1000K              (0x07u << 4)

/* Bit Field  SC_PGA_GNDVREF_ENUM - SCxx_CR2[7] */
#define `$INSTANCE_NAME`_GNDVREF                 (0x01u << 7)
#define `$INSTANCE_NAME`_GNDVREF_DI              (0x00u << 7)
#define `$INSTANCE_NAME`_GNDVREF_E               (0x01u << 7) 

/* SC Block Clock Control SCx.CLk */
#define `$INSTANCE_NAME`_DYN_CNTL_EN             (0x01u << 5)
#define `$INSTANCE_NAME`_BYPASS_SYNC             (0x01u << 4)
#define `$INSTANCE_NAME`_CLK_EN                  (0x01u << 3)

/* SC Block Boost Clock Selection Register - Boost Clock Enable  SCxx_BST[3]  */
#define `$INSTANCE_NAME`_BST_CLK_EN              (0x01u << 3)

#endif /* CY_MIXER_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
