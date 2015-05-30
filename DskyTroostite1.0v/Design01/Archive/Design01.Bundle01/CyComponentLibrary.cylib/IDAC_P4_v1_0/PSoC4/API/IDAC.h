/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the IDAC_P4
*  component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC_`$INSTANCE_NAME`_H)
#define CY_IDAC_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Internal Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


extern uint32 `$INSTANCE_NAME`_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_IDAC_RESOLUTION    (`$Resolution`u)
#define `$INSTANCE_NAME`_IDAC_RANGE         (`$IDACRange`u)
#define `$INSTANCE_NAME`_IDAC_POLARITY      (`$Polarity`u)


/***************************************
*    Initial Parameter Constants
***************************************/
#define `$INSTANCE_NAME`_IDAC_INIT_VALUE    (`$IDACValue`u)




/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetValue(uint32  value);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Wakeup(void);


/***************************************
*            API Constants
***************************************/

#define `$INSTANCE_NAME`_IDAC_EN_MODE              (3u)
#define `$INSTANCE_NAME`_IDAC_CSD_EN               (1u)
#define `$INSTANCE_NAME`_IDAC_CSD_EN_POSITION      (31u)
#define `$INSTANCE_NAME`_IDAC_VALUE_POSITION       (`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT)
#define `$INSTANCE_NAME`_IDAC_MODE_SHIFT           (8u)
#define `$INSTANCE_NAME`_IDAC_POLARITY_POSITION    (`$INSTANCE_NAME`_cy_psoc4_idac__POLARITY_SHIFT)
#define `$INSTANCE_NAME`_IDAC_MODE_POSITION        ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT + \
                                                        (uint32)`$INSTANCE_NAME`_IDAC_MODE_SHIFT)
#define `$INSTANCE_NAME`_IDAC_RANGE_SHIFT          (10u)
#define `$INSTANCE_NAME`_IDAC_RANGE_POSITION       ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT + \
                                                        (uint32)`$INSTANCE_NAME`_IDAC_RANGE_SHIFT)

#define `$INSTANCE_NAME`_IDAC_CDS_EN_MASK      (0x80000000u)

#if(`$INSTANCE_NAME`_IDAC_RESOLUTION == 8u)
  #define `$INSTANCE_NAME`_IDAC_VALUE_MASK     (0xFFu)
#else
  #define `$INSTANCE_NAME`_IDAC_VALUE_MASK     (0x7Fu)
#endif /* (`$INSTANCE_NAME`_IDAC_RESOLUTION == 8u) */

#define `$INSTANCE_NAME`_IDAC_MODE_MASK        (3u)
#define `$INSTANCE_NAME`_IDAC_RANGE_MASK       (1u)
#define `$INSTANCE_NAME`_IDAC_POLARITY_MASK    (1u)


/***************************************
*        Registers
***************************************/

#define `$INSTANCE_NAME`_IDAC_CONTROL_REG    (*(reg32 *) (uint32)CYREG_CSD_IDAC)
#define `$INSTANCE_NAME`_IDAC_CONTROL_PTR    ( (reg32 *) CYREG_CSD_IDAC)

#define `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_REG    (*(reg32 *) CYREG_CSD_CONFIG)
#define `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_PTR    ( (reg32 *) CYREG_CSD_CONFIG)

#endif /* CY_IDAC_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
