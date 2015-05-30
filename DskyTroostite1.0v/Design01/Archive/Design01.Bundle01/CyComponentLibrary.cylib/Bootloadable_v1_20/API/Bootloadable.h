/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides an API for the Bootloadable application. The API includes a
*   single function for starting bootloader.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#ifndef CY_BOOTLOADABLE_`$INSTANCE_NAME`_H
#define CY_BOOTLOADABLE_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "CyFlash.h"


/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* !defined (CY_PSOC5LP) */


#ifndef CYDEV_FLASH_BASE
    #define CYDEV_FLASH_BASE                            CYDEV_FLS_BASE
    #define CYDEV_FLASH_SIZE                            CYDEV_FLS_SIZE
#endif /* CYDEV_FLASH_BASE */

#if(CY_PSOC3)
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)         (*((uint8  CYCODE *) (idx)))
#else
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)         (*((uint8  *)(CYDEV_FLASH_BASE + (idx))))
#endif /* (CY_PSOC3) */


/*******************************************************************************
* This variable is used by Bootloader/Bootloadable components to schedule what
* application will be started after software reset.
*******************************************************************************/
#if (CY_PSOC4)
    #if defined(__ARMCC_VERSION)
        __attribute__ ((section(".bootloaderruntype"), zero_init))
    #elif defined (__GNUC__)
        __attribute__ ((section(".bootloaderruntype")))
   #elif defined (__ICCARM__)
        #pragma location=".bootloaderruntype"
    #endif  /* defined(__ARMCC_VERSION) */
    extern volatile uint32 cyBtldrRunType;
#endif  /* (CY_PSOC4) */


/*******************************************************************************
* Get the reason of the device reset
*******************************************************************************/
#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_RES_CAUSE_RESET_SOFT   (0x10u)
    #define `$INSTANCE_NAME`_GET_RUN_TYPE           \
                        (((CY_GET_REG32(CYREG_RES_CAUSE) & `$INSTANCE_NAME`_RES_CAUSE_RESET_SOFT) > 0u) \
                            ? (cyBtldrRunType) \
                            : 0u)
#else
    #define `$INSTANCE_NAME`_GET_RUN_TYPE           (CY_GET_REG8(CYREG_RESET_SR0) & \
                                                    (`$INSTANCE_NAME`_START_BTLDR | `$INSTANCE_NAME`_START_APP))
#endif  /* (CY_PSOC4) */


/*******************************************************************************
* Schedule Bootloader/Bootloadable to be run after software reset
*******************************************************************************/
#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)        (cyBtldrRunType = (x))
#else
    #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)        CY_SET_REG8(CYREG_RESET_SR0, (x))
#endif  /* (CY_PSOC4) */



/***************************************
*     Function Prototypes
***************************************/
extern void `$INSTANCE_NAME`_Load(void) `=ReentrantKeil("`$INSTANCE_NAME`_Load")`;


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from version 1.10
*******************************************************************************/
#define CYBTDLR_SET_RUN_TYPE(x)     `$INSTANCE_NAME`_SET_RUN_TYPE(x)


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from version 1.20
*******************************************************************************/
#define `$INSTANCE_NAME`_START_APP                      (0x80u)
#define `$INSTANCE_NAME`_START_BTLDR                    (0x40u)
#define `$INSTANCE_NAME`_META_DATA_SIZE                 (64u)
#define `$INSTANCE_NAME`_META_APP_CHECKSUM_OFFSET       (0u)

#if(CY_PSOC3)

    #define `$INSTANCE_NAME`_APP_ADDRESS                    uint16
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)             (*((uint32 CYCODE *) (idx)))

    /* Offset by 2 from 32 bit start because only need 16 bits */
    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           (3u)
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    (7u)
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       (11u)
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       (15u)

#else

    #define `$INSTANCE_NAME`_APP_ADDRESS                    uint32
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)             (*((uint32 *)(CYDEV_FLASH_BASE + (idx))))

    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           (1u)
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    (5u)
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       (9u)
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       (13u)

#endif /* (CY_PSOC3) */

#define `$INSTANCE_NAME`_META_APP_ACTIVE_OFFSET             (16u)
#define `$INSTANCE_NAME`_META_APP_VERIFIED_OFFSET           (17u)

#define `$INSTANCE_NAME`_META_APP_BL_BUILD_VER_OFFSET       (18u)
#define `$INSTANCE_NAME`_META_APP_ID_OFFSET                 (20u)
#define `$INSTANCE_NAME`_META_APP_VER_OFFSET                (22u)
#define `$INSTANCE_NAME`_META_APP_CUST_ID_OFFSET            (24u)

#define `$INSTANCE_NAME`_SetFlashRunType(runType)           \
                        `$INSTANCE_NAME`_SetFlashByte(`$INSTANCE_NAME`_MD_APP_RUN_ADDR(0), (runType))

void `$INSTANCE_NAME`_SetFlashByte(uint32 address, uint8 runType) `=ReentrantKeil("`$INSTANCE_NAME`_SetFlashByte")`;

#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_SOFTWARE_RESET         CY_SET_REG32(CYREG_CM0_AIRCR, 0x05FA0004u)
#else
    #define `$INSTANCE_NAME`_SOFTWARE_RESET         CY_SET_REG8(CYREG_RESET_CR2, 0x01u)
#endif  /* (CY_PSOC4) */

#if(CY_PSOC4)
    extern uint8 appRunType;
#endif  /* (CY_PSOC4) */


#endif /* CY_BOOTLOADABLE_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
