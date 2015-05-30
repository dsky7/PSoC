/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the OpAmp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_`$INSTANCE_NAME`_H)
#define CY_OPAMP_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/* Component init state */
extern uint32 `$INSTANCE_NAME`_initVar;


/**************************************
*        Function Prototypes
**************************************/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetPower(uint32 power);
void `$INSTANCE_NAME`_PumpControl(uint32 onOff);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/
#define `$INSTANCE_NAME`_LOWPOWER                   (1u)
#define `$INSTANCE_NAME`_MEDPOWER                   (2u)
#define `$INSTANCE_NAME`_HIGHPOWER                  (3u)

#define `$INSTANCE_NAME`_OUTPUT_CURRENT             (`$OutputCurrent`u)
#define `$INSTANCE_NAME`_POWER                      (`$Power`u)
#define `$INSTANCE_NAME`_MODE                       (`$Mode`u)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_VALUE         (`$Compensation`u)


/**************************************
*             Registers
**************************************/
#define `$INSTANCE_NAME`_OA_CTRL                    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define `$INSTANCE_NAME`_OA_RES_CTRL                (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_COMP_TRIM_REG           (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__OA_COMP_TRIM)

/* Bit Field  OA_CTRL */
#define `$INSTANCE_NAME`_OA_CTB_EN_SHIFT            (31u)

/* PUMP ON/OFF defines */
#define `$INSTANCE_NAME`_PUMPON                     (1u)
#define `$INSTANCE_NAME`_PUMPOFF                    (0u)

#define `$INSTANCE_NAME`_PUMP_PROTECT_MASK          (1u)

/* Bit Field  OA_CTRL */
#define `$INSTANCE_NAME`_OA_PWR_MODE_MASK           (0x3u)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_MASK      (0x4u)
#define `$INSTANCE_NAME`_OA_DRIVE_STR_SEL_10X       (0x4u)
#define `$INSTANCE_NAME`_OA_PUMP_EN_MASK            (0x800u)
#define `$INSTANCE_NAME`_OA_PUMP_CTRL_SHIFT         (11u)

#endif    /* CY_OPAMP_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
