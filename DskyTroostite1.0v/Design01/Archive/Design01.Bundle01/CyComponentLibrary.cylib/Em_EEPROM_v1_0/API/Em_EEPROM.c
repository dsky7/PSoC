/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to API for the Emulated EEPROM Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other
*  components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil("`$INSTANCE_NAME`_Start")`
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other
*  components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil("`$INSTANCE_NAME`_Stop")`
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write
********************************************************************************
*
* Summary:
*  Writes the specified number of bytes from the source buffer in SRAM to the
*  emulated EEPROM array in flash, without modifying other data in flash.
*
* Parameters:
*  srcBuf:    Pointer to the SRAM buffer holding the data to write.
*  eepromPtr: Pointer to the array or variable in flash representing
*             the emulated EEPROM.
*  byteCount: Number of bytes to write from srcBuf to eepromPtr.
*
* Return:
*    CYRET_SUCCESS     Successful write.
*    CYRET_BAD_PARAM   eepromPtr is out of range of flash memory.
*    CYRET_UNKNOWN     Other error in writing flash.
*
*******************************************************************************/
#if (!CY_PSOC3)
    cystatus `$INSTANCE_NAME`_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount)
                                                                            `=ReentrantKeil("`$INSTANCE_NAME`_Write")`
#else
    cystatus `$INSTANCE_NAME`_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint16 byteCount)
                                                                            `=ReentrantKeil("`$INSTANCE_NAME`_Write")`
#endif /* (!CY_PSOC3) */
{
    uint8 writeBuffer[CY_FLASH_SIZEOF_ROW];
    uint32 arrayNumber;
    uint32 rowNumber;
    uint32 rowOffset;
    uint32 byteIndex;
    uint32 readSrcIndex;
    cystatus returnCode;

    #if (!CY_PSOC4)
        uint8 rowBuffer[CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE];
    #endif /* (!CY_PSOC4) */

    #if (!CY_PSOC3)
        uint32 dataAddress = (uint32) eepromPtr;
    #else
        uint32 dataAddress = (uint32) eepromPtr & `$INSTANCE_NAME`_CODE_ADDR_MASK;
    #endif /* (!CY_PSOC3) */

    /* Make sure, that eepromPtr[] points to ROM */
    #if (!CY_PSOC3)
        if (((uint32)eepromPtr + byteCount) < `$INSTANCE_NAME`_FLASH_END_ADDR)
    #else
        if (((uint32)eepromPtr >= `$INSTANCE_NAME`_CODE_ADDR_OFFSET) &&
            (((uint32)eepromPtr + byteCount) <= `$INSTANCE_NAME`_CODE_ADDR_END))
    #endif /* (!CY_PSOC3) */
    {
        returnCode = CYRET_SUCCESS;

        #if (!CY_PSOC4)
            (void)CySetTemp();
            (void)CySetFlashEEBuffer(rowBuffer);
        #endif /* (!CY_PSOC4) */

        rowNumber = dataAddress / CY_FLASH_SIZEOF_ROW;
        arrayNumber = rowNumber / ((CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW) - 1u);
        rowOffset = dataAddress - (CY_FLASH_SIZEOF_ROW * rowNumber);
        readSrcIndex = 0u;

        while (readSrcIndex < byteCount)
        {
            for(byteIndex = 0u; byteIndex < CY_FLASH_SIZEOF_ROW; byteIndex++)
            {
                if ( (byteIndex >= rowOffset) && (readSrcIndex < byteCount) )
                {
                    writeBuffer[byteIndex] = srcBuf[readSrcIndex];
                    readSrcIndex++;
                }
                else
                {
                    #if (!CY_PSOC3)
                        writeBuffer[byteIndex] = *((uint8 *) (CYDEV_FLASH_BASE +
                                (CY_FLASH_SIZEOF_ARRAY * arrayNumber) + (CY_FLASH_SIZEOF_ROW * rowNumber) + byteIndex));
                    #else
                        writeBuffer[byteIndex] = CY_GET_XTND_REG8(CYDEV_FLASH_BASE +
                                (CY_FLASH_SIZEOF_ARRAY * arrayNumber) + (CY_FLASH_SIZEOF_ROW * rowNumber) + byteIndex);
                    #endif /* (!CY_PSOC3) */
                }
            }
            #if (CY_PSOC4)
                returnCode = CySysFlashWriteRow(rowNumber, writeBuffer);
            #else
                returnCode = CyWriteRowData((uint8)arrayNumber, (uint16)rowNumber, writeBuffer);
            #endif /* (CY_PSOC4) */

            if (CYRET_SUCCESS != returnCode)
            {
                break;
            }

            rowNumber++;

            #if (CY_FLASH_NUMBER_ARRAYS > 1)
                if (rowNumber >= (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW))
                {

                    arrayNumber++;
                    rowNumber = 0u;
                }
            #endif /* (CY_FLASH_NUMBER_ARRAYS > 1) */

            rowOffset = 0u;
        }
    }
    else
    {
        returnCode = CYRET_BAD_PARAM;
    }

    /* Mask return codes from flash, if they are not supported */
    if ((CYRET_SUCCESS != returnCode) && (CYRET_BAD_PARAM != returnCode))
    {
        returnCode = CYRET_UNKNOWN;
    }

    return (returnCode);
}


/* [] END OF FILE */
