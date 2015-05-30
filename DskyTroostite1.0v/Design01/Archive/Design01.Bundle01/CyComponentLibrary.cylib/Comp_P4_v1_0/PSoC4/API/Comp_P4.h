/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMPARATOR_`$INSTANCE_NAME`_H)
#define CY_COMPARATOR_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h"


/***************************************
* Internal Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*       Type defines
***************************************/

/* component init state */
extern uint32 `$INSTANCE_NAME`_initVar;


/**************************************
*        Function Prototypes
**************************************/
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetSpeed(uint32 speed);
uint32  `$INSTANCE_NAME`_ZeroCal(void);
void    `$INSTANCE_NAME`_LoadTrim(uint32 trimVal);
void    `$INSTANCE_NAME`_Sleep(void);
void    `$INSTANCE_NAME`_Wakeup(void);
void    `$INSTANCE_NAME`_SaveConfig(void);
void    `$INSTANCE_NAME`_RestoreConfig(void);
uint32  `$INSTANCE_NAME`_GetCompare(void);


/**************************************
*           API Constants
**************************************/

/* Power constants for SetSpeed() function */
#define `$INSTANCE_NAME`_SLOWSPEED                     (0x01u)
#define `$INSTANCE_NAME`_MEDSPEED                      (0x02u)
#define `$INSTANCE_NAME`_HIGHSPEED                     (0x03u)

#define `$INSTANCE_NAME`_HYSTERESIS                    (`$Hysteresis`u)
#define `$INSTANCE_NAME`_POWER                         (`$Power`u)


/**************************************
*             Registers
**************************************/
#define `$INSTANCE_NAME`_CTB_CTRL_REG                  (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define `$INSTANCE_NAME`_OA_CTRL_REG                   (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__OA_RES_CTRL)
#define `$INSTANCE_NAME`_OA_COMPSTAT_REG               (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__COMP_STAT)
#define `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG            (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__OA_OFFSET_TRIM)
#define `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG      (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)
#define `$INSTANCE_NAME`_OA_COMPSHIFT                  (`$INSTANCE_NAME`_cy_psoc4_abuf__COMP_STAT_SHIFT)


/*trim defines*/
#define `$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT          (5u)
#define `$INSTANCE_NAME`_COMP_TRIM_MAX_VALUE           (32u)


/***************************************
*        Registers Constants
***************************************/

/* Bit Field  CTB_CTRL */
#define `$INSTANCE_NAME`_OA_CTB_EN_SHIFT               (31u)


/* Bit Field  OA_CTRL */
#define `$INSTANCE_NAME`_OA_PWR_MODE_HIGH              (3u)
#define `$INSTANCE_NAME`_OA_PWR_MODE_MASK              (3u)
#define `$INSTANCE_NAME`_OA_COMP_EN_SHIFT              (4u)
#define `$INSTANCE_NAME`_OA_BYPASS_SHIFT               (6u)
#define `$INSTANCE_NAME`_OA_HYST_EN_SHIFT              (5u)
#define `$INSTANCE_NAME`_OA_PUMP_EN_SHIFT              (11u)

#endif /*  CY_COMPARATOR_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
