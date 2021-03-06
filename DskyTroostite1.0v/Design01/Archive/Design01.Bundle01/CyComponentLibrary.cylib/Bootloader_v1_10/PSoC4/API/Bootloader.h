/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides an API for the Bootloader. The API includes functions for starting
*   boot loading operations, validating the application and jumping to the
*   application.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOTLOADER_`$INSTANCE_NAME`_H)
#define CY_BOOTLOADER_`$INSTANCE_NAME`_H

#include "device.h"
#include <string.h>


/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5X) */

/* Map existing call to the instance specific one */
#define CyBtldr_Start   `$INSTANCE_NAME`_Start

#define `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER        (`$multiAppBootloader`)
#define `$INSTANCE_NAME`_BOOTLOADER_APP_VERSION     (`$bootloaderAppVersion`)
#define `$INSTANCE_NAME`_FAST_APP_VALIDATION        (`$fastAppValidation`)
#define `$INSTANCE_NAME`_PACKET_CHECKSUM_CRC        (`$packetChecksumCrc`)
#define `$INSTANCE_NAME`_WAIT_FOR_COMMAND           (`$waitForCommand`)
#define `$INSTANCE_NAME`_WAIT_FOR_COMMAND_TIME      (`$waitForCommandTime`)
#define `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION  (`$bootloaderAppValidation`)

#define `$INSTANCE_NAME`_CMD_GET_FLASH_SIZE_AVAIL   (`$cmdGetFlashSizeAvail`)
#define `$INSTANCE_NAME`_CMD_ERASE_ROW_AVAIL        (`$cmdEraseRowAvail`)
#define `$INSTANCE_NAME`_CMD_VERIFY_ROW_AVAIL       (`$cmdVerifyRowAvail`)
#define `$INSTANCE_NAME`_CMD_SYNC_BOOTLOADER_AVAIL  (`$cmdSyncBootloaderAvail`)
#define `$INSTANCE_NAME`_CMD_SEND_DATA_AVAIL        (`$cmdSendDataAvail`)

#if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)
    #define `$INSTANCE_NAME`_CMD_GET_APP_STATUS_AVAIL   (`$cmdGetAppStatusAvail`)
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_GET_REG16(x)   ((uint16)(                                                                   \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x) + 1u) <<  8u))       \
                                            ))


    #define `$INSTANCE_NAME`_GET_REG32(x)   (                                                                    \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 1u) <<  8u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 2u) << 16u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 3u) << 24u))       \
                                            )
#endif  /* (CY_PSOC4) */

/*******************************************************************************
* A common code for the Bootloader and Bootloadable
*******************************************************************************/

/* Mask used to indicate starting application */
#define `$INSTANCE_NAME`_START_APP                      0x80

 /* Mask used to indicate starting bootloader */
#define `$INSTANCE_NAME`_START_BTLDR                    0x40


#ifndef CYDEV_FLASH_BASE
    #define CYDEV_FLASH_BASE                            CYDEV_FLS_BASE
    #define CYDEV_FLASH_SIZE                            CYDEV_FLS_SIZE
#endif /* CYDEV_FLASH_BASE */


#define `$INSTANCE_NAME`_META_DATA_SIZE                 64
#define `$INSTANCE_NAME`_META_APP_CHECKSUM_OFFSET       0


#if(CY_PSOC3)

    #define `$INSTANCE_NAME`_APP_ADDRESS                uint16
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)         *((uint8  CYCODE *) idx)
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)         *((uint32 CYCODE *) idx)

    /* Offset by 2 from 32 bit start because only need 16 bits */
    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           3       /* 2 bytes */
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    7       /* 4 bytes */
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       11      /* 4 bytes */
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       15      /* 1 byte  */

#else

    #define `$INSTANCE_NAME`_APP_ADDRESS                uint32
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)         *((uint8  *)(CYDEV_FLASH_BASE + (idx)))
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)         *((uint32 *)(CYDEV_FLASH_BASE + (idx)))

    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           1   /* 4 bytes */
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    5   /* 4 bytes */
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       9   /* 4 bytes */
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       13  /* 1 byte  */

#endif /* (CY_PSOC3) */

#define `$INSTANCE_NAME`_META_APP_ACTIVE_OFFSET             16  /* 1 byte  */
#define `$INSTANCE_NAME`_META_APP_VERIFIED_OFFSET           17  /* 1 byte  */

#define `$INSTANCE_NAME`_META_APP_BL_BUILD_VER_OFFSET       18  /* 2 bytes */
#define `$INSTANCE_NAME`_META_APP_ID_OFFSET                 20  /* 2 bytes */
#define `$INSTANCE_NAME`_META_APP_VER_OFFSET                22  /* 2 bytes */
#define `$INSTANCE_NAME`_META_APP_CUST_ID_OFFSET            24  /* 4 bytes */


#if (CY_PSOC4)
    #if (__ARMCC_VERSION)
       extern volatile uint32 __attribute__ ((section(".bootloaderruntype"), zero_init))  cyBtldrRunType;
    #else   /* (__GNUC__) */
       extern volatile uint32 __attribute__ ((section(".bootloaderruntype")))             cyBtldrRunType;
    #endif  /* (__ARMCC_VERSION) */
#endif  /* (CY_PSOC4) */


#if(CY_PSOC4)

    extern uint8 appRunType;

    #define `$INSTANCE_NAME`_SOFTWARE_RESET CY_SET_REG32(CYREG_CM0_AIRCR, 0x05FA0004)

    #define `$INSTANCE_NAME`_RES_CAUSE_RESET_SOFT   (0x10u)
    #define `$INSTANCE_NAME`_GET_RUN_TYPE           \
                        (((CY_GET_REG32(CYREG_RES_CAUSE) & `$INSTANCE_NAME`_RES_CAUSE_RESET_SOFT) > 0u) \
                            ? (cyBtldrRunType) \
                            : 0u)


    #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)                (cyBtldrRunType = (x))

#else

    #define `$INSTANCE_NAME`_SOFTWARE_RESET CY_SET_REG8(CYREG_RESET_CR2, 0x01)

    #define `$INSTANCE_NAME`_GET_RUN_TYPE   (CY_GET_REG8(CYREG_RESET_SR0) & \
                                            (`$INSTANCE_NAME`_START_BTLDR | `$INSTANCE_NAME`_START_APP))

    #if defined(WORKAROUND_OPT_XRES)
        #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)     `$INSTANCE_NAME`_SetFlashByte(`$INSTANCE_NAME`_MD_APP_RUN_ADDR(`$INSTANCE_NAME`_activeApp), (x))
    #else
        #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)     CY_SET_REG8(CYREG_RESET_SR0, (x))
    #endif  /* defined(WORKAROUND_OPT_XRES) */

#endif  /* (CY_PSOC4) */


#define `$INSTANCE_NAME`_SetFlashRunType(runType)        `$INSTANCE_NAME`_SetFlashByte(`$INSTANCE_NAME`_MD_APP_RUN_ADDR(0), (runType))


void `$INSTANCE_NAME`_SetFlashByte(uint32 address, uint8 value) `=ReentrantKeil("`$INSTANCE_NAME`_SetFlashByte")`;


/*******************************************************************************
* Metadata addresses and pointer defines
*******************************************************************************/

#define `$INSTANCE_NAME`_META_BASE(x)                 (CYDEV_FLASH_BASE + (CYDEV_FLASH_SIZE - ((x) * CYDEV_FLS_ROW_SIZE) - `$INSTANCE_NAME`_META_DATA_SIZE))
#define `$INSTANCE_NAME`_META_ARRAY                   (`$INSTANCE_NAME`_FLASH_NUMBER_SECTORS - 1)

#define `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(x) (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_ADDR_OFFSET)
#define `$INSTANCE_NAME`_META_APP_BYTE_LEN(x)         (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET)
#define `$INSTANCE_NAME`_META_APP_RUN_ADDR(x)         (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET)
#define `$INSTANCE_NAME`_META_APP_ACTIVE_ADDR(x)      (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_ACTIVE_OFFSET)
#define `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(x)    (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_VERIFIED_OFFSET)
#define `$INSTANCE_NAME`_META_APP_BLDBL_VER_ADDR(x)   (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_BL_BUILD_VER_OFFSET)
#define `$INSTANCE_NAME`_META_APP_VER_ADDR(x)         (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_VER_OFFSET)
#define `$INSTANCE_NAME`_META_APP_ID_ADDR(x)          (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_ID_OFFSET)
#define `$INSTANCE_NAME`_META_APP_CUST_ID_ADDR(x)     (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_CUST_ID_OFFSET)
#define `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(x)   (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET)
#define `$INSTANCE_NAME`_META_CHECKSUM_ADDR(x)        (`$INSTANCE_NAME`_META_BASE(x) + `$INSTANCE_NAME`_META_APP_CHECKSUM_OFFSET)


#if(0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

    #define `$INSTANCE_NAME`_MD_BASE                    `$INSTANCE_NAME`_META_BASE(0)
    #define `$INSTANCE_NAME`_MD_ROW                     ((CY_FLASH_NUMBER_ROWS / `$INSTANCE_NAME`_FLASH_NUMBER_SECTORS) - 1)
    #define `$INSTANCE_NAME`_MD_CHECKSUM_ADDR           `$INSTANCE_NAME`_META_CHECKSUM_ADDR(0)
    #define `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR      `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(0)
    #define `$INSTANCE_NAME`_MD_APP_BYTE_LEN            `$INSTANCE_NAME`_META_APP_BYTE_LEN(0)
    #define `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR       `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(0)
    #define `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR    `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(0)
    #define `$INSTANCE_NAME`_MD_APP_RUN_ADDR            `$INSTANCE_NAME`_META_APP_RUN_ADDR(0)

#else

    #define `$INSTANCE_NAME`_MD_ROW(x)                  ((CY_FLASH_NUMBER_ROWS / `$INSTANCE_NAME`_FLASH_NUMBER_SECTORS) - 1 - (x))
    #define `$INSTANCE_NAME`_MD_CHECKSUM_ADDR           `$INSTANCE_NAME`_META_CHECKSUM_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR      `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_APP_BYTE_LEN            `$INSTANCE_NAME`_META_APP_BYTE_LEN(appId)
    #define `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR       `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR    `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(`$INSTANCE_NAME`_activeApp)
    #define `$INSTANCE_NAME`_MD_APP_RUN_ADDR            `$INSTANCE_NAME`_META_APP_RUN_ADDR(`$INSTANCE_NAME`_activeApp)

#endif  /* (0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */

/* Pointers to the Bootloader metadata items */
#define `$INSTANCE_NAME`_P_APP_ACTIVE(x)             ((uint8 CYCODE *)        `$INSTANCE_NAME`_META_APP_ACTIVE_ADDR(x))

#define `$INSTANCE_NAME`_MD_PTR_CHECKSUM                 ((uint8  CYCODE *)       `$INSTANCE_NAME`_MD_CHECKSUM_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_ENTRY_POINT          ((`$INSTANCE_NAME`_APP_ADDRESS CYCODE *) `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_LAST_BLDR_ROW            ((uint16 CYCODE *)       `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_BYTE_LEN             ((`$INSTANCE_NAME`_APP_ADDRESS CYCODE *) `$INSTANCE_NAME`_MD_APP_BYTE_LEN)
#define `$INSTANCE_NAME`_MD_PTR_APP_RUN_ADDR             ((uint8  CYCODE *)        `$INSTANCE_NAME`_MD_APP_RUN_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_VERIFIED             ((uint8  CYCODE *)        `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_BLD_BL_VER           ((uint16 CYCODE *)       `$INSTANCE_NAME`_MD_APP_BLDBL_VER_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_VER                  ((uint16 CYCODE *)       `$INSTANCE_NAME`_MD_APP_VER_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_ID                   ((uint16 CYCODE *)       `$INSTANCE_NAME`_MD_APP_ID_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_CUST_ID              ((uint32 CYCODE *)       `$INSTANCE_NAME`_MD_APP_CUST_ID_ADDR)


/*******************************************************************************
* External References
*******************************************************************************/
extern void LaunchApp(uint32 addr);
extern void `$INSTANCE_NAME`_Start(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Start")`;
extern void `$INSTANCE_NAME`_LaunchApplication(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_LaunchApplication")`;
extern void `$INSTANCE_NAME`_HostLink(uint8 TimeOut) `=ReentrantKeil("`$INSTANCE_NAME`_HostLink")`;

#if(1u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

    extern cystatus `$INSTANCE_NAME`_ValidateApp(uint8 appId) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_ValidateApp")`;
    #define `$INSTANCE_NAME`_ValidateApplication()   `$INSTANCE_NAME`_ValidateApp(0)

#else

    extern cystatus `$INSTANCE_NAME`_ValidateApplication(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_ValidateApplication")`;
    #define `$INSTANCE_NAME`_ValidateApp(x) `$INSTANCE_NAME`_ValidateApplication()

#endif  /* (1u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


/* If using custom interface as the IO Component, user must provide these functions */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == `$INSTANCE_NAME`_Custom_Interface)

    extern void CyBtldrCommStart(void);
    extern void CyBtldrCommStop (void);
    extern void CyBtldrCommReset(void);
    extern cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut);
    extern cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut);

#endif  /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == `$INSTANCE_NAME`_Custom_Interface) */


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from version 1.10
*******************************************************************************/
#define `$INSTANCE_NAME`_BOOTLOADABLE_APP_VALID     (`$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION)

#endif /* CY_BOOTLOADER_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
