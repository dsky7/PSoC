/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Low Power Comparator component.
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
#include "cyfitter.h"


/***************************************
*       Type defines
***************************************/

/* Component init state */
extern uint32 `$INSTANCE_NAME`_initVar;


/**************************************
*        Function Prototypes
**************************************/
void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetSpeed(uint32 speed);
void    `$INSTANCE_NAME`_SetInterruptMode(uint32 mode);
uint32  `$INSTANCE_NAME`_GetInterruptSource(void);
void    `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis);
void    `$INSTANCE_NAME`_SetFilter(uint32 filter);
uint32  `$INSTANCE_NAME`_GetCompare(void);
uint32  `$INSTANCE_NAME`_ZeroCal(void);
void    `$INSTANCE_NAME`_LoadTrim(uint32 trimVal);


/**************************************
*           API Constants
**************************************/

#define `$INSTANCE_NAME`_INTR_PARAM_MASK            (0x03u)
#define `$INSTANCE_NAME`_SPEED_PARAM_MASK           (0x03u)
#define `$INSTANCE_NAME`_INTR_SHIFT                 (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SHIFT)

/* `$INSTANCE_NAME`_SetSpeed() parameters */
#define `$INSTANCE_NAME`_MEDSPEED                   (0x00u)
#define `$INSTANCE_NAME`_HIGHSPEED                  (0x01u)
#define `$INSTANCE_NAME`_LOWSPEED                   (0x02u)


/* `$INSTANCE_NAME`_SetInterruptMode() parameters */
#define `$INSTANCE_NAME`_INTR_DISABLE               (0x00u)
#define `$INSTANCE_NAME`_INTR_RISING                (0x01u)
#define `$INSTANCE_NAME`_INTR_FALLING               (0x02u)
#define `$INSTANCE_NAME`_INTR_BOTH                  (0x03u)

/* `$INSTANCE_NAME`_SetHysteresis() parameters */
#define `$INSTANCE_NAME`_HYST_ENABLE                (0x01u)
#define `$INSTANCE_NAME`_HYST_DISABLE               (0x00u)

/* `$INSTANCE_NAME`_SetFilter() parameters */
#define `$INSTANCE_NAME`_FILT_DISABLE               (0x00u)
#define `$INSTANCE_NAME`_FILT_ENABLE                (0x01u)

#define `$INSTANCE_NAME`_INTR                       ((uint32)((uint32)0x01u << `$INSTANCE_NAME`_INTR_SHIFT))


#define `$INSTANCE_NAME`_INTERRUPT                  (`$Interrupt`u)
#define `$INSTANCE_NAME`_SPEED                      (`$Speed`u)
#define `$INSTANCE_NAME`_HYSTERESIS                 (`$Hysteresis`u)
#define `$INSTANCE_NAME`_DIGITAL_FILTER             (`$DigitalFilter`u)


/**************************************
*             Registers
**************************************/

/* LPCOMP configuration register */
#define `$INSTANCE_NAME`_CONFIG_REG                 (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG)
#define `$INSTANCE_NAME`_CONFIG_PTR                 ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG)

/* LPCOMP DFT register */
#define `$INSTANCE_NAME`_DFT_REG                    (*(reg32 *)CYREG_LPCOMP_DFT)
#define `$INSTANCE_NAME`_DFT_PTR                    ( (reg32 *)CYREG_LPCOMP_DFT)

/* LPCOMP interrupt request register */
#define `$INSTANCE_NAME`_INTR_REG                   (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR)
#define `$INSTANCE_NAME`_INTR_PTR                   ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR)

/* LPCOMP interrupt set register */
#define `$INSTANCE_NAME`_INTR_SET_REG               (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SET)
#define `$INSTANCE_NAME`_INTR_SET_PTR               ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SET)

/* LPCOMP trim register */
#define `$INSTANCE_NAME`_TRIMA_REG                  (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_A)
#define `$INSTANCE_NAME`_TRIMA_PTR                  ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_A)

/* LPCOMP trim register */
#define `$INSTANCE_NAME`_TRIMB_REG                  (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_B)
#define `$INSTANCE_NAME`_TRIMB_PTR                  ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_B)


/***************************************
*        Registers Constants
***************************************/

#define `$INSTANCE_NAME`_CONFIG_REG_SHIFT           (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG_SHIFT)

/* LPCOMP configuration register bit fields */
#define `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT    (0u)
#define `$INSTANCE_NAME`_CONFIG_SPEED_MODE_MASK     ((uint32)((uint32)((uint32)0x03u << \
                                        `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))

#define `$INSTANCE_NAME`_CONFIG_HYST_SHIFT          (2u)
#define `$INSTANCE_NAME`_CONFIG_HYST                ((uint32)((uint32)((uint32)0x01u << \
                                        `$INSTANCE_NAME`_CONFIG_HYST_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))

#define `$INSTANCE_NAME`_CONFIG_FILT_SHIFT          (3u)
#define `$INSTANCE_NAME`_CONFIG_FILT                ((uint32)((uint32)((uint32)0x01u << \
                                        `$INSTANCE_NAME`_CONFIG_FILT_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))

#define `$INSTANCE_NAME`_CONFIG_INTR_SHIFT          (4u)
#define `$INSTANCE_NAME`_CONFIG_INTR_MASK           ((uint32)((uint32)((uint32)0x03u << \
                                        `$INSTANCE_NAME`_CONFIG_INTR_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))

#define `$INSTANCE_NAME`_CONFIG_OUT_SHIFT           (6u)
#define `$INSTANCE_NAME`_CONFIG_OUT                 ((uint32)((uint32)0x01u << `$INSTANCE_NAME`_CONFIG_OUT_SHIFT) << \
                                        `$INSTANCE_NAME`_CONFIG_REG_SHIFT)

#define `$INSTANCE_NAME`_CONFIG_EN_SHIFT            (7u)
#define `$INSTANCE_NAME`_CONFIG_EN                  ((uint32)((uint32)((uint32)0x01u << \
                                        `$INSTANCE_NAME`_CONFIG_EN_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))


/* LPCOMP DFT register bit fields */
#define `$INSTANCE_NAME`_DFT_CAL_EN                 ((uint32)0x01u)

/* LPCOMP Trim Registers bit fields */
#define `$INSTANCE_NAME`_TRIMA_MASK                 (0x1Fu)
#define `$INSTANCE_NAME`_TRIMA_SIGNBIT              (4u)
#define `$INSTANCE_NAME`_TRIMA_MAX_VALUE            (15u)

#define `$INSTANCE_NAME`_TRIMB_MASK                 (0x1Fu)
#define `$INSTANCE_NAME`_TRIMB_SHIFT                (8u)
#define `$INSTANCE_NAME`_TRIMB_SIGNBIT              (4u)
#define `$INSTANCE_NAME`_TRIMB_MAX_VALUE            (15u)

#define `$INSTANCE_NAME`_CONFIG_MASK                (0xFFu)
/* Default configuration for LPCOMP configuration register */
#define `$INSTANCE_NAME`_CONFIG_DEFAULT             ((uint32)(\
                            ( (uint32)`$INSTANCE_NAME`_INTERRUPT      << `$INSTANCE_NAME`_CONFIG_INTR_SHIFT) | \
                            ( (uint32)`$INSTANCE_NAME`_DIGITAL_FILTER << `$INSTANCE_NAME`_CONFIG_FILT_SHIFT) | \
                            ( (uint32)`$INSTANCE_NAME`_HYSTERESIS     << `$INSTANCE_NAME`_CONFIG_HYST_SHIFT) | \
                            ( (uint32)`$INSTANCE_NAME`_SPEED          << `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT)))


#endif    /* CY_COMPARATOR_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
