/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides an API for the Bootloader component. The API includes functions
*   for starting boot loading operations, validating the application and
*   jumping to the application.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

#include "project.h"
#include <string.h>


/*******************************************************************************
* The Checksum and SizeBytes are forcefully set in code. We then post process
* the hex file from the linker and inject their values then. When the hex file
* is loaded onto the device these two variables should have valid values.
* Because the compiler can do optimizations remove the constant
* accesses, these should not be accessed directly. Instead, the variables
* CyBtldr_ChecksumAccess & CyBtldr_SizeBytesAccess should be used to get the
* proper values at runtime.
*******************************************************************************/
#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */

const uint8  CYCODE `$INSTANCE_NAME`_Checksum = 0u;
const uint8  CYCODE *`$INSTANCE_NAME`_ChecksumAccess  = (const uint8  CYCODE *)(&`$INSTANCE_NAME`_Checksum);

#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */

const uint32 CYCODE `$INSTANCE_NAME`_SizeBytes = 0xFFFFFFFFu;
const uint32 CYCODE *`$INSTANCE_NAME`_SizeBytesAccess = (const uint32 CYCODE *)(&`$INSTANCE_NAME`_SizeBytes);


#if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)
    uint8 `$INSTANCE_NAME`_activeApp = `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_NONE;
#else
    #define `$INSTANCE_NAME`_activeApp      (`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_0)
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


/***************************************
*     Function Prototypes
***************************************/
static cystatus `$INSTANCE_NAME`_WritePacket(uint8 status, uint8 buffer[], uint16 size) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_WritePacket")`;

static uint16   `$INSTANCE_NAME`_CalcPacketChecksum(const uint8 buffer[], uint16 size) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_CalcPacketChecksum")`;

static uint8    `$INSTANCE_NAME`_Calc8BitFlashSum(uint32 start, uint32 size) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_Calc8BitFlashSum")`;
#if(!CY_PSOC4)
static uint8    `$INSTANCE_NAME`_Calc8BitEepromSum(uint32 start, uint32 size) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_Calc8BitEepromSum")`;
#endif /* (!CY_PSOC4) */

static void     `$INSTANCE_NAME`_HostLink(uint8 timeOut) \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_HostLink")`;

static void     `$INSTANCE_NAME`_LaunchApplication(void) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_LaunchApplication")`;

static cystatus `$INSTANCE_NAME`_ValidateBootloadable(uint8 appId) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_ValidateBootloadable")`;

static uint32   `$INSTANCE_NAME`_GetMetadata(uint8 fieldName, uint8 appId)\
                                    `=ReentrantKeil("`$INSTANCE_NAME`_GetMetadata")`;

#if(!CY_PSOC3)
    /* Implementation for the PSoC 3 resides in a `$INSTANCE_NAME`_psoc3.a51 file.  */
    static void     `$INSTANCE_NAME`_LaunchBootloadable(uint32 appAddr);
#endif  /* (!CY_PSOC3) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalcPacketChecksum
********************************************************************************
*
* Summary:
*  This computes the 16 bit checksum for the provided number of bytes contained
*  in the provided buffer
*
* Parameters:
*  buffer:
*     The buffer containing the data to compute the checksum for
*  size:
*     The number of bytes in buffer to compute the checksum for
*
* Returns:
*  16 bit checksum for the provided data
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_CalcPacketChecksum(const uint8 buffer[], uint16 size) \
                    CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_CalcPacketChecksum")`
{
    #if(0u != `$INSTANCE_NAME`_PACKET_CHECKSUM_CRC)

        uint16 CYDATA crc = `$INSTANCE_NAME`_CRC_CCITT_INITIAL_VALUE;
        uint16 CYDATA tmp;
        uint8  CYDATA i;
        uint16 CYDATA tmpIndex = size;

        if(0u == size)
        {
            crc = ~crc;
        }
        else
        {
            do
            {
                tmp = buffer[tmpIndex - size];

                for (i = 0u; i < 8u; i++)
                {
                    if (0u != ((crc & 0x0001u) ^ (tmp & 0x0001u)))
                    {
                        crc = (crc >> 1u) ^ `$INSTANCE_NAME`_CRC_CCITT_POLYNOMIAL;
                    }
                    else
                    {
                        crc >>= 1u;
                    }

                    tmp >>= 1u;
                }

                size--;
            }
            while(0u != size);

            crc = ~crc;
            tmp = crc;
            crc = ( uint16 )(crc << 8u) | (tmp >> 8u);
        }

        return(crc);

    #else

        uint16 CYDATA sum = 0u;

        while (size > 0u)
        {
            sum += buffer[size - 1u];
            size--;
        }

        return(( uint16 )1u + ( uint16 )(~sum));

    #endif /* (0u != `$INSTANCE_NAME`_PACKET_CHECKSUM_CRC) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Calc8BitFlashSum
********************************************************************************
*
* Summary:
*  This computes the 8 bit sum for the provided number of bytes contained in
*  flash.
*
* Parameters:
*  start:
*     The starting address to start summing data for
*  size:
*     The number of bytes to read and compute the sum for
*
* Returns:
*   8 bit sum for the provided data
*
*******************************************************************************/
static uint8 `$INSTANCE_NAME`_Calc8BitFlashSum(uint32 start, uint32 size) \
                CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Calc8BitFlashSum")`
{
    uint8 CYDATA sum = 0u;

    while (size > 0u)
    {
        size--;
        sum += `$INSTANCE_NAME`_GET_CODE_BYTE(start + size);
    }

    return(sum);
}


#if(!CY_PSOC4)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Calc8BitEepromSum
    ********************************************************************************
    *
    * Summary:
    *  This computes the 8 bit sum for the provided number of bytes contained in
    *  EEPROM.
    *
    * Parameters:
    *  start:
    *     The starting address to start summing data for
    *  size:
    *     The number of bytes to read and compute the sum for
    *
    * Returns:
    *   8 bit sum for the provided data
    *
    *******************************************************************************/
    static uint8 `$INSTANCE_NAME`_Calc8BitEepromSum(uint32 start, uint32 size) \
                    CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Calc8BitEepromSum")`
    {
        uint8 CYDATA sum = 0u;

        while (size > 0u)
        {
            size--;
            sum += `$INSTANCE_NAME`_GET_EEPROM_BYTE(start + size);
        }

        return(sum);
    }

#endif  /* (!CY_PSOC4) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
* Summary:
*  This function is called in order executing following algorithm:
*
*  - Identify active bootloadable application (applicable only to
*    Multi-application bootloader)
*
*  - Validate bootloader application (desing-time configurable, Bootloader
*    application validation option of the component customizer)
*
*  - Validate active bootloadable application
*
*  - Run communication subroutine (desing-time configurable, Wait for command
*    option of the component customizer)
*
*  - Schedule bootloadable and reset device
*
* Parameters:
*  None
*
* Return:
*  This method will never return. It will either load a new application and
*  reset the device or it will jump directly to the existing application.
*
* Side Effects:
*  If this method determines that the bootloader appliation itself is corrupt,
*  this method will not return, instead it will simply hang the application.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Start")`
{
    #if(0u != `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION)
        uint8 CYDATA calcedChecksum;
    #endif    /* (0u != `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION) */

    #if(!CY_PSOC4)
        uint8 CYXDATA `$INSTANCE_NAME`_flashBuffer[`$INSTANCE_NAME`_FROW_SIZE];
    #endif  /* (!CY_PSOC4) */

    cystatus tmpStatus;


    /* Identify active bootloadable application */
    #if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

        if(`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_VALUE(0u) == `$INSTANCE_NAME`_MD_BTLDB_IS_ACTIVE)
        {
            `$INSTANCE_NAME`_activeApp = `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_0;
        }
        else if (`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_VALUE(1u) == `$INSTANCE_NAME`_MD_BTLDB_IS_ACTIVE)
        {
            `$INSTANCE_NAME`_activeApp = `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_1;
        }
        else
        {
            `$INSTANCE_NAME`_activeApp = `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_NONE;
        }

    #endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


    /* Initialize Flash subsystem for non-PSoC 4 devices */
    #if(!CY_PSOC4)
        if (CYRET_SUCCESS != CySetTemp())
        {
            CyHalt(0x00u);
        }

        if (CYRET_SUCCESS != CySetFlashEEBuffer(`$INSTANCE_NAME`_flashBuffer))
        {
            CyHalt(0x00u);
        }
    #endif  /* (CY_PSOC4) */


    /***********************************************************************
    * Bootloader Application Validation
    *
    * Halt device if:
    *  - Calculated checksum does not much one stored in metadata section
    *  - Invalid pointer to the place where bootloader application ends
    *  - Flash subsystem where not initialized correctly
    ***********************************************************************/
    #if(0u != `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION)

        /* Calculate Bootloader application checksum */
        calcedChecksum = `$INSTANCE_NAME`_Calc8BitFlashSum(`$INSTANCE_NAME`_MD_BTLDR_ADDR_PTR,
                *`$INSTANCE_NAME`_SizeBytesAccess - `$INSTANCE_NAME`_MD_BTLDR_ADDR_PTR);

        /* we actually included the checksum, so remove it */
        calcedChecksum -= *`$INSTANCE_NAME`_ChecksumAccess;
        calcedChecksum = ( uint8 )1u + ( uint8 )(~calcedChecksum);

        /* Checksum and pointer to bootloader verification */
        if((calcedChecksum != *`$INSTANCE_NAME`_ChecksumAccess) ||
           (0u == *`$INSTANCE_NAME`_SizeBytesAccess))
        {
            CyHalt(0x00u);
        }

    #endif  /* (0u != `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION) */


    /***********************************************************************
    * Active Bootloadable Application Validation
    *
    * If active bootloadable application is invalid or bootloader
    * application is scheduled - do the following:
    *  - schedule bootloader application to be run after software reset
    *  - Go to the communication subroutine. Will wait for commands forever
    ***********************************************************************/
    tmpStatus = `$INSTANCE_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_activeApp);

    if ((`$INSTANCE_NAME`_GET_RUN_TYPE == `$INSTANCE_NAME`_START_BTLDR) ||
        (CYRET_SUCCESS != tmpStatus))
    {
        `$INSTANCE_NAME`_SET_RUN_TYPE(0u);

        `$INSTANCE_NAME`_HostLink(`$INSTANCE_NAME`_WAIT_FOR_COMMAND_FOREVER);
    }


    /* Go to the communication subroutine. Will wait for commands specifed time */
    #if(0u != `$INSTANCE_NAME`_WAIT_FOR_COMMAND)

        /* Timeout is in 100s of miliseconds */
        `$INSTANCE_NAME`_HostLink(`$INSTANCE_NAME`_WAIT_FOR_COMMAND_TIME);

    #endif  /* (0u != `$INSTANCE_NAME`_WAIT_FOR_COMMAND) */


    /* Schedule bootloadable application and perform software reset */
    `$INSTANCE_NAME`_LaunchApplication();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LaunchApplication
********************************************************************************
*
* Summary:
*  Jumps the PC to the start address of the user application in flash.
*
* Parameters:
*  None
*
* Returns:
*  This method will never return if it succesfully goes to the user application.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_LaunchApplication(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_LaunchApplication")`
{
    /* Schedule Bootloadable to start after reset */
    `$INSTANCE_NAME`_SET_RUN_TYPE(`$INSTANCE_NAME`_START_APP);

    CySoftwareReset();
}


/*******************************************************************************
* Function Name: CyBtldr_CheckLaunch
********************************************************************************
*
* Summary:
*  This routine checks to see if the bootloader or the bootloadable application
*  should be run.  If the application is to be run, it will start executing.
*  If the bootloader is to be run, it will return so the bootloader can
*  continue starting up.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void CyBtldr_CheckLaunch(void) CYSMALL `=ReentrantKeil("CyBtldr_CheckLaunch")`
{

#if(CY_PSOC4)

    /*******************************************************************************
    * Set cyBtldrRunType to zero in case of non-software reset occured. This means
    * that bootloader application is scheduled - that is initial clean state. The
    * value of cyBtldrRunType is valid only in case of software reset.
    *******************************************************************************/
    if (0u == (`$INSTANCE_NAME`_RES_CAUSE_REG & `$INSTANCE_NAME`_RES_CAUSE_RESET_SOFT))
    {
        cyBtldrRunType = 0u;
    }

#endif /* (CY_PSOC4) */


    if (`$INSTANCE_NAME`_GET_RUN_TYPE == `$INSTANCE_NAME`_START_APP)
    {
        `$INSTANCE_NAME`_SET_RUN_TYPE(0u);

        /*******************************************************************************
        * Indicates that we have told ourselves to jump to the application since we have
        * already told ourselves to jump, we do not do any expensive verification of the
        * application. We just check to make sure that the value at CY_APP_ADDR_ADDRESS
        * is something other than 0.
        *******************************************************************************/
        if(0u != `$INSTANCE_NAME`_GetMetadata(`$INSTANCE_NAME`_GET_METADATA_BTLDB_ADDR, `$INSTANCE_NAME`_activeApp))
        {
            /* Never return from this method */
            `$INSTANCE_NAME`_LaunchBootloadable(`$INSTANCE_NAME`_GetMetadata(`$INSTANCE_NAME`_GET_METADATA_BTLDB_ADDR,
                                                                             `$INSTANCE_NAME`_activeApp));
        }
    }
}


/* Moves the arguement appAddr (RO) into PC, moving execution to the appAddr */
#if defined (__ARMCC_VERSION)

    __asm static void `$INSTANCE_NAME`_LaunchBootloadable(uint32 appAddr)
    {
        BX  R0
        ALIGN
    }

#elif defined(__GNUC__)

    __attribute__((noinline)) /* Workaround for GCC toolchain bug with inlining */
    __attribute__((naked))
    static void `$INSTANCE_NAME`_LaunchBootloadable(uint32 appAddr)
    {
        __asm volatile("    BX  R0\n");
    }

#elif defined (__ICCARM__)

    static void `$INSTANCE_NAME`_LaunchBootloadable(uint32 appAddr)
    {
        __asm volatile("    BX  R0\n");
    }

#endif  /* (__ARMCC_VERSION) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ValidateBootloadable
********************************************************************************
* Summary:
*  This routine computes the checksum, zero check, 0xFF check of the
*  application area to determine whether a valid application is loaded.
*
* Parameters:
*  appId:
*      The application number to verify
*
* Returns:
*  CYRET_SUCCESS  - if successful
*  CYRET_BAD_DATA - if the bootloadable is corrupt
*
*******************************************************************************/
static cystatus `$INSTANCE_NAME`_ValidateBootloadable(uint8 appId) CYSMALL \
`=ReentrantKeil("`$INSTANCE_NAME`_ValidateBootloadable")`
    {
        uint32 CYDATA idx;

        uint32 CYDATA end   = `$INSTANCE_NAME`_FIRST_APP_BYTE(appId) +
                                `$INSTANCE_NAME`_GetMetadata(`$INSTANCE_NAME`_GET_METADATA_BTLDB_LENGTH,
                                                       appId);

        CYBIT         valid = 0u; /* Assume bad flash image */
        uint8  CYDATA calcedChecksum = 0u;


        #if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

            if(appId > 1u)
            {
                return(CYRET_BAD_DATA);
            }

        #endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


        #if(0u != `$INSTANCE_NAME`_FAST_APP_VALIDATION)

            if(`$INSTANCE_NAME`_MD_BTLDB_VERIFIED_VALUE(appId) == `$INSTANCE_NAME`_MD_BTLDB_IS_VERIFIED)
            {
                return(CYRET_SUCCESS);
            }

        #endif  /* (0u != `$INSTANCE_NAME`_FAST_APP_VALIDATION) */


        /* Calculate checksum of bootloadable image */
        for(idx = `$INSTANCE_NAME`_FIRST_APP_BYTE(appId); idx < end; ++idx)
        {
            uint8 CYDATA curByte = `$INSTANCE_NAME`_GET_CODE_BYTE(idx);

            if((curByte != 0u) && (curByte != 0xFFu))
            {
                valid = 1u;
            }

            calcedChecksum += curByte;
        }


        /***************************************************************************
        * We do not compute checksum over the meta data section, so no need to
        * subtract off App Verified or App Active information here like we do when
        * verifying a row.
        ***************************************************************************/


        #if((!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0u))

            /* Add ECC data to checksum */
            idx = ((`$INSTANCE_NAME`_FIRST_APP_BYTE(appId)) >> 3u);

            /* Flash may run into meta data, ECC does not so use full row */
            end = (end == (CY_FLASH_SIZE - `$INSTANCE_NAME`_MD_SIZEOF))
                ? (CY_FLASH_SIZE >> 3u)
                : (end >> 3u);

            for (; idx < end; ++idx)
            {
                calcedChecksum += CY_GET_XTND_REG8((volatile uint8 *)(CYDEV_ECC_BASE + idx));
            }

        #endif  /* ((!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0u)) */


        calcedChecksum = ( uint8 )1u + ( uint8 )(~calcedChecksum);

        if((calcedChecksum != `$INSTANCE_NAME`_MD_BTLDB_CHECKSUM_VALUE(appId)) ||
           (0u == valid))
        {
            return(CYRET_BAD_DATA);
        }


        #if(0u != `$INSTANCE_NAME`_FAST_APP_VALIDATION)
            `$INSTANCE_NAME`_SetFlashByte((uint32) `$INSTANCE_NAME`_MD_BTLDB_VERIFIED_OFFSET(appId),
                                          `$INSTANCE_NAME`_MD_BTLDB_IS_VERIFIED);
        #endif  /* (0u != `$INSTANCE_NAME`_FAST_APP_VALIDATION) */


        return(CYRET_SUCCESS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HostLink
********************************************************************************
*
* Summary:
*  Causes the bootloader to attempt to read data being transmitted by the
*  host application.  If data is sent from the host, this establishes the
*  communication interface to process all requests.
*
* Parameters:
*  timeOut:
*   The amount of time to listen for data before giving up. Timeout is
*   measured in 10s of ms.  Use 0 for infinite wait.
*
* Return:
*   None
*
*******************************************************************************/
static void `$INSTANCE_NAME`_HostLink(uint8 timeOut) `=ReentrantKeil("`$INSTANCE_NAME`_HostLink")`
{
    uint16    CYDATA numberRead;
    uint16    CYDATA rspSize;
    uint8     CYDATA ackCode;
    uint16    CYDATA pktChecksum;
    cystatus  CYDATA readStat;
    uint16    CYDATA pktSize    = 0u;
    uint16    CYDATA dataOffset = 0u;
    uint8     CYDATA timeOutCnt = 10u;

    #if(0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)
        uint8 CYDATA clearedMetaData = 0u;
    #endif  /* (0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */

    CYBIT     communicationState = `$INSTANCE_NAME`_COMMUNICATION_STATE_IDLE;

    uint8     packetBuffer[`$INSTANCE_NAME`_SIZEOF_COMMAND_BUFFER];
    uint8     dataBuffer  [`$INSTANCE_NAME`_SIZEOF_COMMAND_BUFFER];


    /* Initialize communications channel. */
    CyBtldrCommStart();

    /* Enable global interrupts */
    CyGlobalIntEnable;

    do
    {
        ackCode = CYRET_SUCCESS;

        do
        {
            readStat = CyBtldrCommRead(packetBuffer,
                                        `$INSTANCE_NAME`_SIZEOF_COMMAND_BUFFER,
                                        &numberRead,
                                        (0u == timeOut) ? 0xFFu : timeOut);
            if (0u != timeOut)
            {
                timeOutCnt--;
            }

        } while ( (0u != timeOutCnt) && (readStat != CYRET_SUCCESS) );


        if( readStat != CYRET_SUCCESS )
        {
            continue;
        }

        if((numberRead < `$INSTANCE_NAME`_MIN_PKT_SIZE) ||
           (packetBuffer[`$INSTANCE_NAME`_SOP_ADDR] != `$INSTANCE_NAME`_SOP))
        {
            ackCode = `$INSTANCE_NAME`_ERR_DATA;
        }
        else
        {
            pktSize = ((uint16)((uint16)packetBuffer[`$INSTANCE_NAME`_SIZE_ADDR + 1u] << 8u)) |
                               packetBuffer[`$INSTANCE_NAME`_SIZE_ADDR];

            pktChecksum = ((uint16)((uint16)packetBuffer[`$INSTANCE_NAME`_CHK_ADDR(pktSize) + 1u] << 8u)) |
                                   packetBuffer[`$INSTANCE_NAME`_CHK_ADDR(pktSize)];

            if((pktSize + `$INSTANCE_NAME`_MIN_PKT_SIZE) > numberRead)
            {
                ackCode = `$INSTANCE_NAME`_ERR_LENGTH;
            }
            else if(packetBuffer[`$INSTANCE_NAME`_EOP_ADDR(pktSize)] != `$INSTANCE_NAME`_EOP)
            {
                ackCode = `$INSTANCE_NAME`_ERR_DATA;
            }
            else if(pktChecksum != `$INSTANCE_NAME`_CalcPacketChecksum(packetBuffer,
                                                                        pktSize + `$INSTANCE_NAME`_DATA_ADDR))
            {
                ackCode = `$INSTANCE_NAME`_ERR_CHECKSUM;
            }
            else
            {
                /* Empty section */
            }
        }

        rspSize = 0u;
        if(ackCode == CYRET_SUCCESS)
        {
            uint8 CYDATA btldrData = packetBuffer[`$INSTANCE_NAME`_DATA_ADDR];

            ackCode = `$INSTANCE_NAME`_ERR_DATA;
            switch(packetBuffer[`$INSTANCE_NAME`_CMD_ADDR])
            {


            /***************************************************************************
            *   Get metadata
            ***************************************************************************/
            #if(0u != `$INSTANCE_NAME`_CMD_GET_METADATA)

                case `$INSTANCE_NAME`_COMMAND_GET_METADATA:

                    if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 1u))
                    {
                        if (btldrData >= `$INSTANCE_NAME`_MAX_NUM_OF_BTLDB)
                        {
                            ackCode = `$INSTANCE_NAME`_ERR_APP;
                        }
                        else if(CYRET_SUCCESS == `$INSTANCE_NAME`_ValidateBootloadable(btldrData))
                        {
                            #if(CY_PSOC3)
                                (void) memcpy(&packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                            ((uint8  CYCODE *) (`$INSTANCE_NAME`_META_BASE(btldrData))), 56);
                            #else
                                (void) memcpy(&packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                            (uint8 *) `$INSTANCE_NAME`_META_BASE(btldrData), 56u);
                            #endif  /* (CY_PSOC3) */

                            rspSize = 56u;
                            ackCode = CYRET_SUCCESS;
                        }
                        else
                        {
                            ackCode = `$INSTANCE_NAME`_ERR_APP;
                        }
                    }
                    break;

            #endif  /* (0u != `$INSTANCE_NAME`_CMD_GET_METADATA) */


            /***************************************************************************
            *   Verify checksum
            ***************************************************************************/
            case `$INSTANCE_NAME`_COMMAND_CHECKSUM:

                if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 0u))
                {
                    packetBuffer[`$INSTANCE_NAME`_DATA_ADDR] =
                            (uint8)(`$INSTANCE_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_activeApp) == CYRET_SUCCESS);

                    rspSize = 1u;
                    ackCode = CYRET_SUCCESS;
                }
                break;


            /***************************************************************************
            *   Get flash size
            ***************************************************************************/
            #if(0u != `$INSTANCE_NAME`_CMD_GET_FLASH_SIZE_AVAIL)

                case `$INSTANCE_NAME`_COMMAND_REPORT_SIZE:

                    if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 1u))
                    {
                        /* btldrData holds flash array ID sent by host */
                        if(btldrData < `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS)
                        {
                            #if (1u == `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS)
                                uint16 CYDATA startRow = (uint16)*`$INSTANCE_NAME`_SizeBytesAccess / CYDEV_FLS_ROW_SIZE;
                            #else
                                uint16 CYDATA startRow = 0u;
                            #endif  /* (1u == `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS) */

                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR]      = LO8(startRow);
                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 1u] = HI8(startRow);
                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 2u] = LO8(CY_FLASH_NUMBER_ROWS - 1u);
                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 3u] = HI8(CY_FLASH_NUMBER_ROWS - 1u);

                            rspSize = 4u;
                            ackCode = CYRET_SUCCESS;
                        }

                    }
                    break;

            #endif  /* (0u != `$INSTANCE_NAME`_CMD_GET_FLASH_SIZE_AVAIL) */


            /***************************************************************************
            *   Get application status
            ***************************************************************************/
            #if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

                #if(0u != `$INSTANCE_NAME`_CMD_GET_APP_STATUS_AVAIL)

                    case `$INSTANCE_NAME`_COMMAND_APP_STATUS:

                        if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 1u))
                        {

                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR] =
                                (uint8)`$INSTANCE_NAME`_ValidateBootloadable(btldrData);

                            packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 1u] =
                                (uint8)`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_VALUE(btldrData);

                            rspSize = 2u;
                            ackCode = CYRET_SUCCESS;
                        }
                        break;

                #endif  /* (0u != `$INSTANCE_NAME`_CMD_GET_APP_STATUS_AVAIL) */

            #endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


            /***************************************************************************
            *   Program / Erase row
            ***************************************************************************/
            case `$INSTANCE_NAME`_COMMAND_PROGRAM:

            /* The btldrData variable holds Flash Array ID */

        #if (0u != `$INSTANCE_NAME`_CMD_ERASE_ROW_AVAIL)

            case `$INSTANCE_NAME`_COMMAND_ERASE:
                if (`$INSTANCE_NAME`_COMMAND_ERASE == packetBuffer[`$INSTANCE_NAME`_CMD_ADDR])
                {
                    if ((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 3u))
                    {
                        #if(!CY_PSOC4)
                            if((btldrData >= `$INSTANCE_NAME`_FIRST_EE_ARRAYID) &&
                               (btldrData <= `$INSTANCE_NAME`_LAST_EE_ARRAYID))
                            {
                                /* Size of EEPROM row */
                                dataOffset = CY_EEPROM_SIZEOF_ROW;
                            }
                            else
                            {
                                /* Size of FLASH row (depends on ECC configuration) */
                                dataOffset = `$INSTANCE_NAME`_FROW_SIZE;
                            }
                        #else
                            /* Size of FLASH row (no ECC available) */
                            dataOffset = `$INSTANCE_NAME`_FROW_SIZE;
                        #endif  /* (!CY_PSOC4) */

                        #if(CY_PSOC3)
                            (void) memset(dataBuffer, (char8) 0, (int16) dataOffset);
                        #else
                            (void) memset(dataBuffer, 0, dataOffset);
                        #endif  /* (CY_PSOC3) */
                    }
                    else
                    {
                        break;
                    }
                }

        #endif  /* (0u != `$INSTANCE_NAME`_CMD_ERASE_ROW_AVAIL) */


                if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize >= 3u))
                {

                    /* The command may be sent along with the last block of data, to program the row. */
                    #if(CY_PSOC3)
                        (void) memcpy(&dataBuffer[dataOffset],
                                      &packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 3u],
                                      ( int16 )pktSize - 3);
                    #else
                        (void) memcpy(&dataBuffer[dataOffset],
                                      &packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 3u],
                                      pktSize - 3u);
                    #endif  /* (CY_PSOC3) */

                    dataOffset += (pktSize - 3u);

                    #if(!CY_PSOC4)
                        if((btldrData >= `$INSTANCE_NAME`_FIRST_EE_ARRAYID) &&
                           (btldrData <= `$INSTANCE_NAME`_LAST_EE_ARRAYID))
                        {

                            CyEEPROM_Start();

                            /* Size of EEPROM row */
                            pktSize = CY_EEPROM_SIZEOF_ROW;
                        }
                        else
                        {
                            /* Size of FLASH row (depends on ECC configuration) */
                            pktSize = `$INSTANCE_NAME`_FROW_SIZE;
                        }
                    #else
                        /* Size of FLASH row (no ECC available) */
                        pktSize = `$INSTANCE_NAME`_FROW_SIZE;
                    #endif  /* (!CY_PSOC4) */


                    /* Check if we have all data to program */
                    if(dataOffset == pktSize)
                    {
                        /* Get FLASH/EEPROM row number */
                        dataOffset = ((uint16)((uint16)packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 2u] << 8u)) |
                                              packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 1u];

                        #if(!CY_PSOC4)
                            if(btldrData <= `$INSTANCE_NAME`_LAST_FLASH_ARRAYID)
                            {
                        #endif  /* (!CY_PSOC4) */

                        #if(0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

                            if(0u == clearedMetaData)
                            {
                                /* Metadata section must be filled with zeroes */

                                uint8 erase[`$INSTANCE_NAME`_FROW_SIZE];

                                #if(CY_PSOC3)
                                    (void) memset(erase, (char8) 0, (int16) `$INSTANCE_NAME`_FROW_SIZE);
                                #else
                                    (void) memset(erase, 0, `$INSTANCE_NAME`_FROW_SIZE);
                                #endif  /* (CY_PSOC3) */

                                #if(CY_PSOC4)
                                    (void) CySysFlashWriteRow(`$INSTANCE_NAME`_MD_ROW, erase);
                                #else
                                    (void) CyWriteRowFull((uint8)  `$INSTANCE_NAME`_MD_FLASH_ARRAY_NUM,
                                                          (uint16) `$INSTANCE_NAME`_MD_ROW,
                                                                    erase,
                                                                    `$INSTANCE_NAME`_FROW_SIZE);
                                #endif  /* (CY_PSOC4) */

                                /* Set up flag that metadata was cleared */
                                clearedMetaData = 1u;
                            }

                        #else

                            if(`$INSTANCE_NAME`_activeApp < `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_NONE)
                            {
                                /* First active bootloadable application row */
                                uint16 firstRow = (uint16) 1u +
                                    (uint16) `$INSTANCE_NAME`_GetMetadata(`$INSTANCE_NAME`_GET_METADATA_BTLDR_LAST_ROW,
                                                                          `$INSTANCE_NAME`_activeApp);

                                #if(CY_PSOC4)
                                    uint16 row = dataOffset;
                                #else
                                    uint16 row = (uint16)(btldrData * (CYDEV_FLS_SECTOR_SIZE / CYDEV_FLS_ROW_SIZE)) +
                                                  dataOffset;
                                #endif  /* (CY_PSOC4) */


                                /*******************************************************************************
                                * Last row is equal to the first row plus the number of rows available for each
                                * app. To compute this, we first subtract the number of appliaction images from
                                * the total flash rows: (CY_FLASH_NUMBER_ROWS - 2u).
                                *
                                * Then subtract off the first row:
                                * App Rows = (CY_FLASH_NUMBER_ROWS - 2u - firstRow)
                                * Then divide that number by the number of application that must fit within the
                                * space, if we are app1 then that number is 2, if app2 then 1.  Our divisor is
                                * then: (2u - `$INSTANCE_NAME`_activeApp).
                                *
                                * Adding this number to firstRow gives the address right beyond our valid range
                                * so we subtract 1.
                                *******************************************************************************/
                                uint16 lastRow = (firstRow - 1u) +
                                                  ((uint16)((CYDEV_FLASH_SIZE / CYDEV_FLS_ROW_SIZE) - 2u - firstRow) /
                                                  ((uint16)2u - (uint16)`$INSTANCE_NAME`_activeApp));


                                /*******************************************************************************
                                * Check to see if the row to program is within the range of the active
                                * application, or if it maches the active application's metadata row.  If so,
                                * refuse to program as it would corrupt the active app.
                                *******************************************************************************/
                                if(((row >= firstRow) && (row <= lastRow)) ||
                                   ((btldrData == `$INSTANCE_NAME`_MD_FLASH_ARRAY_NUM) &&
                                   (dataOffset == `$INSTANCE_NAME`_MD_ROW_NUM(`$INSTANCE_NAME`_activeApp))))
                                {
                                    ackCode = `$INSTANCE_NAME`_ERR_ACTIVE;
                                    dataOffset = 0u;
                                    break;
                                }
                            }

                        #endif  /* (0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */

                        #if(!CY_PSOC4)
                            }
                        #endif  /* (!CY_PSOC4) */

                        #if(CY_PSOC4)

                            ackCode = (CYRET_SUCCESS != CySysFlashWriteRow((uint32) dataOffset, dataBuffer)) \
                                ? `$INSTANCE_NAME`_ERR_ROW \
                                : CYRET_SUCCESS;

                        #else

                            ackCode = (CYRET_SUCCESS != CyWriteRowFull(btldrData, dataOffset, dataBuffer, pktSize)) \
                                ? `$INSTANCE_NAME`_ERR_ROW \
                                : CYRET_SUCCESS;

                        #endif  /* (CY_PSOC4) */

                    }
                    else
                    {
                        ackCode = `$INSTANCE_NAME`_ERR_LENGTH;
                    }

                    dataOffset = 0u;
                }
                break;


            /***************************************************************************
            *   Sync bootloader
            ***************************************************************************/
            #if(0u != `$INSTANCE_NAME`_CMD_SYNC_BOOTLOADER_AVAIL)

            case `$INSTANCE_NAME`_COMMAND_SYNC:

                if(`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState)
                {
                    /* If something failed the host would send this command to reset the bootloader. */
                    dataOffset = 0u;

                    /* Don't ack the packet, just get ready to accept the next one */
                    continue;
                }
                break;

            #endif  /* (0u != `$INSTANCE_NAME`_CMD_SYNC_BOOTLOADER_AVAIL) */


            /***************************************************************************
            *   Set active application
            ***************************************************************************/
            #if(0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)

                case `$INSTANCE_NAME`_COMMAND_APP_ACTIVE:

                    if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 1u))
                    {
                        if(CYRET_SUCCESS == `$INSTANCE_NAME`_ValidateBootloadable(btldrData))
                        {
                            uint8 CYDATA idx;

                            for(idx = 0u; idx < `$INSTANCE_NAME`_MAX_NUM_OF_BTLDB; idx++)
                            {
                                `$INSTANCE_NAME`_SetFlashByte((uint32) `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_OFFSET(idx),
                                                              (uint8 )(idx == btldrData));
                            }
                            `$INSTANCE_NAME`_activeApp = btldrData;
                            ackCode = CYRET_SUCCESS;
                        }
                        else
                        {
                            ackCode = `$INSTANCE_NAME`_ERR_APP;
                        }
                    }
                    break;

            #endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */


            /***************************************************************************
            *   Send data
            ***************************************************************************/
            #if (0u != `$INSTANCE_NAME`_CMD_SEND_DATA_AVAIL)

                case `$INSTANCE_NAME`_COMMAND_DATA:

                    if(`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState)
                    {
                        /*  Make sure that dataOffset is valid before copying the data */
                        if((dataOffset + pktSize) <= `$INSTANCE_NAME`_SIZEOF_COMMAND_BUFFER)
                        {
                            ackCode = CYRET_SUCCESS;

                            #if(CY_PSOC3)
                                (void) memcpy(&dataBuffer[dataOffset],
                                              &packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                              ( int16 )pktSize);
                            #else
                                (void) memcpy(&dataBuffer[dataOffset],
                                              &packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                              pktSize);
                            #endif  /* (CY_PSOC3) */

                            dataOffset += pktSize;
                        }
                        else
                        {
                            ackCode = `$INSTANCE_NAME`_ERR_LENGTH;
                        }
                    }

                    break;

            #endif  /* (0u != `$INSTANCE_NAME`_CMD_SEND_DATA_AVAIL) */


            /***************************************************************************
            *   Enter bootloader
            ***************************************************************************/
            case `$INSTANCE_NAME`_COMMAND_ENTER:

                if(pktSize == 0u)
                {
                    #if(CY_PSOC3)

                        `$INSTANCE_NAME`_ENTER CYDATA BtldrVersion =
                            {CYSWAP_ENDIAN32(CYDEV_CHIP_JTAG_ID), CYDEV_CHIP_REV_EXPECT, `$INSTANCE_NAME`_VERSION};

                    #else

                        `$INSTANCE_NAME`_ENTER CYDATA BtldrVersion =
                            {CYDEV_CHIP_JTAG_ID, CYDEV_CHIP_REV_EXPECT, `$INSTANCE_NAME`_VERSION};

                    #endif  /* (CY_PSOC3) */

                    communicationState = `$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE;

                    rspSize = sizeof(`$INSTANCE_NAME`_ENTER);

                    #if(CY_PSOC3)
                        (void) memcpy(&packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                      &BtldrVersion,
                                      ( int16 )rspSize);
                    #else
                        (void) memcpy(&packetBuffer[`$INSTANCE_NAME`_DATA_ADDR],
                                      &BtldrVersion,
                                      rspSize);
                    #endif  /* (CY_PSOC3) */

                    ackCode = CYRET_SUCCESS;
                }
                break;


            /***************************************************************************
            *   Verify row
            ***************************************************************************/
            case `$INSTANCE_NAME`_COMMAND_VERIFY:

                if((`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState) && (pktSize == 3u))
                {
                    /* Get FLASH/EEPROM row number */
                    uint16 CYDATA rowNum = ((uint16)((uint16)packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 2u] << 8u)) |
                                                    packetBuffer[`$INSTANCE_NAME`_DATA_ADDR + 1u];

                    #if(!CY_PSOC4)

                        uint32 CYDATA rowAddr;
                        uint8 CYDATA checksum;

                        if((btldrData >= `$INSTANCE_NAME`_FIRST_EE_ARRAYID) &&
                           (btldrData <= `$INSTANCE_NAME`_LAST_EE_ARRAYID))
                        {
                            /* EEPROM */
                            /* Both PSoC 3 and PSoC 5LP architectures have one EEPROM array. */
                            rowAddr = (uint32)rowNum * CYDEV_EEPROM_ROW_SIZE;

                            checksum = `$INSTANCE_NAME`_Calc8BitEepromSum(rowAddr, CYDEV_EEPROM_ROW_SIZE);
                        }
                        else
                        {
                            /* FLASH */
                            rowAddr = ((uint32)btldrData * CYDEV_FLS_SECTOR_SIZE)
                                       + ((uint32)rowNum * CYDEV_FLS_ROW_SIZE);

                            checksum = `$INSTANCE_NAME`_Calc8BitFlashSum(rowAddr, CYDEV_FLS_ROW_SIZE);
                        }

                    #else

                        uint32 CYDATA rowAddr = ((uint32)btldrData * CYDEV_FLS_SECTOR_SIZE)
                                            + ((uint32)rowNum * CYDEV_FLS_ROW_SIZE);

                        uint8 CYDATA checksum = `$INSTANCE_NAME`_Calc8BitFlashSum(rowAddr, CYDEV_FLS_ROW_SIZE);

                    #endif  /* (!CY_PSOC4) */


                    /* Calculate checksum on data from ECC */
                    #if(!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0u)

                        if(btldrData <= `$INSTANCE_NAME`_LAST_FLASH_ARRAYID)
                        {
                            uint16 CYDATA tmpIndex;

                            rowAddr = CYDEV_ECC_BASE + ((uint32)btldrData * (CYDEV_FLS_SECTOR_SIZE / 8u))
                                        + ((uint32)rowNum * CYDEV_ECC_ROW_SIZE);

                            for(tmpIndex = 0u; tmpIndex < CYDEV_ECC_ROW_SIZE; tmpIndex++)
                            {
                                checksum += CY_GET_XTND_REG8((uint8 CYFAR *)(rowAddr + tmpIndex));
                            }
                        }

                    #endif  /* (!CY_PSOC4) && (CYDEV_ECC_ENABLE == 0u) */


                    /*******************************************************************************
                    * App Verified & App Active are information that is updated in flash at runtime
                    * remove these items from the checksum to allow the host to verify everything is
                    * correct.
                     ******************************************************************************/
                    if((`$INSTANCE_NAME`_MD_FLASH_ARRAY_NUM == btldrData) &&
                       (`$INSTANCE_NAME`_CONTAIN_METADATA(rowNum)))
                    {
                        checksum -= `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_VALUE  (`$INSTANCE_NAME`_GET_APP_ID(rowNum));
                        checksum -= `$INSTANCE_NAME`_MD_BTLDB_VERIFIED_VALUE(`$INSTANCE_NAME`_GET_APP_ID(rowNum));
                    }

                    packetBuffer[`$INSTANCE_NAME`_DATA_ADDR] = (uint8)1u + (uint8)(~checksum);
                    ackCode = CYRET_SUCCESS;
                    rspSize = 1u;
                }
                break;


            /***************************************************************************
            *   Exit bootloader
            ***************************************************************************/
            case `$INSTANCE_NAME`_COMMAND_EXIT:

                if(CYRET_SUCCESS == `$INSTANCE_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_activeApp))
                {
                    `$INSTANCE_NAME`_SET_RUN_TYPE(`$INSTANCE_NAME`_START_APP);
                }

                CySoftwareReset();

                /* Will never get here */
                break;


            /***************************************************************************
            *   Unsupported command
            ***************************************************************************/
            default:
                ackCode = `$INSTANCE_NAME`_ERR_CMD;
                break;
            }
        }

        /* ?CK the packet and function. */
        (void) `$INSTANCE_NAME`_WritePacket(ackCode, packetBuffer, rspSize);

    } while ((0u == timeOut) || (`$INSTANCE_NAME`_COMMUNICATION_STATE_ACTIVE == communicationState));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WritePacket
********************************************************************************
*
* Summary:
*  Creates a bootloader responce packet and transmits it back to the bootloader
*  host application over the already established communications protocol.
*
* Parameters:
*  status:
*      The status code to pass back as the second byte of the packet
*  buffer:
*      The buffer containing the data portion of the packet
*  size:
*      The number of bytes contained within the buffer to pass back
*
* Return:
*   CYRET_SUCCESS if successful.
*   CYRET_UNKNOWN if there was an error tranmitting the packet.
*
*******************************************************************************/
static cystatus `$INSTANCE_NAME`_WritePacket(uint8 status, uint8 buffer[], uint16 size) CYSMALL \
                                            `=ReentrantKeil("`$INSTANCE_NAME`_WritePacket")`
{
    uint16 CYDATA checksum;

    /* Start of the packet. */
    buffer[`$INSTANCE_NAME`_SOP_ADDR]      = `$INSTANCE_NAME`_SOP;
    buffer[`$INSTANCE_NAME`_CMD_ADDR]      = status;
    buffer[`$INSTANCE_NAME`_SIZE_ADDR]     = LO8(size);
    buffer[`$INSTANCE_NAME`_SIZE_ADDR + 1u] = HI8(size);

    /* Compute the checksum. */
    checksum = `$INSTANCE_NAME`_CalcPacketChecksum(buffer, size + `$INSTANCE_NAME`_DATA_ADDR);

    buffer[`$INSTANCE_NAME`_CHK_ADDR(size)]     = LO8(checksum);
    buffer[`$INSTANCE_NAME`_CHK_ADDR(1u + size)] = HI8(checksum);
    buffer[`$INSTANCE_NAME`_EOP_ADDR(size)]     = `$INSTANCE_NAME`_EOP;

    /* Start the packet transmit. */
    return(CyBtldrCommWrite(buffer, size + `$INSTANCE_NAME`_MIN_PKT_SIZE, &size, 150u));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFlashByte
********************************************************************************
*
* Summary:
*  Writes byte a flash memory location
*
* Parameters:
*  address:
*      Address in Flash memory where data will be written
*
*  runType:
*      Byte to be written
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFlashByte(uint32 address, uint8 runType) `=ReentrantKeil("`$INSTANCE_NAME`_SetFlashByte")`
{
    uint32 flsAddr = address - CYDEV_FLASH_BASE;
    uint8  rowData[CYDEV_FLS_ROW_SIZE];

    #if !(CY_PSOC4)
        uint8 arrayId = ( uint8 )(flsAddr / CYDEV_FLS_SECTOR_SIZE);
    #endif  /* !(CY_PSOC4) */

    uint16 rowNum = ( uint16 )((flsAddr % CYDEV_FLS_SECTOR_SIZE) / CYDEV_FLS_ROW_SIZE);
    uint32 baseAddr = address - (address % CYDEV_FLS_ROW_SIZE);
    uint16 idx;

    for(idx = 0u; idx < CYDEV_FLS_ROW_SIZE; idx++)
    {
        rowData[idx] = `$INSTANCE_NAME`_GET_CODE_BYTE(baseAddr + idx);
    }

    rowData[address % CYDEV_FLS_ROW_SIZE] = runType;

    #if(CY_PSOC4)
        (void) CySysFlashWriteRow((uint32) rowNum, rowData);
    #else
        (void) CyWriteRowData(arrayId, rowNum, rowData);
    #endif  /* (CY_PSOC4) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMetadata
********************************************************************************
*
* Summary:
*  Returns value of the multi-byte field.
*
* Parameters:
*  fieldName:
*   The field to get data from:
*     `$INSTANCE_NAME`_GET_METADATA_BTLDB_ADDR
*     `$INSTANCE_NAME`_GET_METADATA_BTLDR_LAST_ROW
*     `$INSTANCE_NAME`_GET_METADATA_BTLDB_LENGTH
*     `$INSTANCE_NAME`_GET_METADATA_BTLDR_APP_VERSION
*     `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_VERSION
*     `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_ID
*     `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_CUST_ID
*
*  appId:
*   Number of the bootlodable application.
*
* Return:
*  None
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_GetMetadata(uint8 fieldName, uint8 appId)`=ReentrantKeil("`$INSTANCE_NAME`_GetMetadata")`
{
    uint32 fieldPtr;
    uint8  fieldSize = 2u;
    uint32 result;

    switch (fieldName)
    {
    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_CUST_ID:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDB_APP_CUST_ID_OFFSET(appId);
        fieldSize = 4u;
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDR_APP_VERSION:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDR_APP_VERSION_OFFSET(appId);
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_ADDR:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDB_ADDR_OFFSET(appId);
    #if(!CY_PSOC3)
        fieldSize = 4u;
    #endif  /* (!CY_PSOC3) */
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDR_LAST_ROW:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDR_LAST_ROW_OFFSET(appId);
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_LENGTH:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDB_LENGTH_OFFSET(appId);
    #if(!CY_PSOC3)
        fieldSize = 4u;
    #endif  /* (!CY_PSOC3) */
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_VERSION:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDB_APP_VERSION_OFFSET(appId);
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_APP_ID:
        fieldPtr  = `$INSTANCE_NAME`_MD_BTLDB_APP_ID_OFFSET(appId);
        break;

    default:
        /* Should never be here */
        CYASSERT(0u != 0u);
        fieldPtr  = 0u;
        break;
    }


    /* Read all fields as big-endian */
    if (2u == fieldSize)
    {
        result =  (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 1u));
        result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *) fieldPtr      ) <<  8u;
    }
    else
    {
        result =  (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 3u));
        result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 2u)) <<  8u;
        result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr + 1u)) << 16u;
        result |= (uint32) CY_GET_XTND_REG8((volatile uint8 *)(fieldPtr     )) << 24u;
    }

    /* Following fields should be little-endian */
#if(!CY_PSOC3)
    switch (fieldName)
    {
    case `$INSTANCE_NAME`_GET_METADATA_BTLDR_LAST_ROW:
        result = CYSWAP_ENDIAN16(result);
        break;

    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_ADDR:
    case `$INSTANCE_NAME`_GET_METADATA_BTLDB_LENGTH:
        result = CYSWAP_ENDIAN32(result);
        break;

    default:
        break;
    }

#endif  /* (!CY_PSOC3) */

    return (result);
}


/* [] END OF FILE */
