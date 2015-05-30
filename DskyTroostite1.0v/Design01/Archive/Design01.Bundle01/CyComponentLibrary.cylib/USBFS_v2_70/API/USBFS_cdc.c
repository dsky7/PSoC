/*******************************************************************************
* File Name: `$INSTANCE_NAME`_cdc.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  USB CDC class request handler.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)

#include "`$INSTANCE_NAME`_cdc.h"
#include "`$INSTANCE_NAME`_pvt.h"


/***************************************
*    CDC Variables
***************************************/

volatile uint8 `$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_SIZE] =
{
    0x00u, 0xC2u, 0x01u, 0x00u,     /* Data terminal rate 115200 */
    0x00u,                          /* 1 Stop bit */
    0x00u,                          /* None parity */
    0x08u                           /* 8 data bits */
};
volatile uint8 `$INSTANCE_NAME`_lineChanged;
volatile uint16 `$INSTANCE_NAME`_lineControlBitmap;
volatile uint8 `$INSTANCE_NAME`_cdc_data_in_ep;
volatile uint8 `$INSTANCE_NAME`_cdc_data_out_ep;


/***************************************
*     Static Function Prototypes
***************************************/
#if (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u)
    static uint16 `$INSTANCE_NAME`_StrLen(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_StrLen")`;
#endif /* (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u) */


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DispatchCDCClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches CDC class requests.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   `$INSTANCE_NAME`_lineCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   `$INSTANCE_NAME`_lineControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   `$INSTANCE_NAME`_lineChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_DispatchCDCClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchCDCClassRqst")`
{
    uint8 requestHandled = `$INSTANCE_NAME`_FALSE;

    if ((CY_GET_REG8(`$INSTANCE_NAME`_bmRequestType) & `$INSTANCE_NAME`_RQST_DIR_MASK) == `$INSTANCE_NAME`_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(`$INSTANCE_NAME`_bRequest))
        {
            case `$INSTANCE_NAME`_CDC_GET_LINE_CODING:
                `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_LINE_CODING_SIZE;
                `$INSTANCE_NAME`_currentTD.pData = `$INSTANCE_NAME`_lineCoding;
                requestHandled  = `$INSTANCE_NAME`_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(`$INSTANCE_NAME`_bmRequestType) & `$INSTANCE_NAME`_RQST_DIR_MASK) == \
                                                                            `$INSTANCE_NAME`_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(`$INSTANCE_NAME`_bRequest))
        {
            case `$INSTANCE_NAME`_CDC_SET_LINE_CODING:
                `$INSTANCE_NAME`_currentTD.count = `$INSTANCE_NAME`_LINE_CODING_SIZE;
                `$INSTANCE_NAME`_currentTD.pData = `$INSTANCE_NAME`_lineCoding;
                `$INSTANCE_NAME`_lineChanged |= `$INSTANCE_NAME`_LINE_CODING_CHANGED;
                requestHandled = `$INSTANCE_NAME`_InitControlWrite();
                break;

            case `$INSTANCE_NAME`_CDC_SET_CONTROL_LINE_STATE:
                `$INSTANCE_NAME`_lineControlBitmap = CY_GET_REG8(`$INSTANCE_NAME`_wValueLo);
                `$INSTANCE_NAME`_lineChanged |= `$INSTANCE_NAME`_LINE_CONTROL_CHANGED;
                requestHandled = `$INSTANCE_NAME`_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (`$INSTANCE_NAME`_ENABLE_CDC_CLASS_API != 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CDC_Init
    ********************************************************************************
    *
    * Summary:
    *  This function initialize the CDC interface to be ready for the receive data
    *  from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_lineChanged: Initialized to zero.
    *   `$INSTANCE_NAME`_cdc_data_out_ep: Used as an OUT endpoint number.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_CDC_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_CDC_Init")`
    {
        `$INSTANCE_NAME`_lineChanged = 0u;
        `$INSTANCE_NAME`_EnableOutEP(`$INSTANCE_NAME`_cdc_data_out_ep);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutData
    ********************************************************************************
    *
    * Summary:
    *  This function sends a specified number of bytes from the location specified
    *  by a pointer to the PC. The `$INSTANCE_NAME`_CDCIsReady() function should be
    *  called before sending new data, to be sure that the previous data has
    *  finished sending.
    *  If the last sent packet is less than maximum packet size the USB transfer
    *  of this short packet will identify the end of the segment. If the last sent
    *  packet is exactly maximum packet size, it shall be followed by a zero-length
    *  packet (which is a short packet) to assure the end of segment is properly
    *  identified. To send zero-length packet, use `$INSTANCE_NAME`_PutData() API
    *  with length parameter set to zero.
    *
    * Parameters:
    *  pData: pointer to the buffer containing data to be sent.
    *  length: Specifies the number of bytes to send from the pData
    *  buffer. Maximum length will be limited by the maximum packet
    *  size for the endpoint. Data will be lost if length is greater than Max
    *  Packet Size.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutData(const uint8* pData, uint16 length) `=ReentrantKeil($INSTANCE_NAME . "_PutData")`
    {
        /* Limits length to maximum packet size for the EP */
        if(length > `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].bufferSize)
        {
            /* Caution: Data will be lost if length is greater than Max Packet Length */
            length = `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].bufferSize;
             /* Halt CPU in debug mode */
            CYASSERT(0u != 0u);
        }
        `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdc_data_in_ep, pData, length);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StrLen
    ********************************************************************************
    *
    * Summary:
    *  Calculates length of a null terminated string.
    *
    * Parameters:
    *  string: pointer to the string.
    *
    * Return:
    *  Length of the string
    *
    *******************************************************************************/
    static uint16 `$INSTANCE_NAME`_StrLen(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_StrLen")`
    {
        uint16 len = 0u;

        while (string[len] != (char8)0)
        {
            len++;
        }

        return (len);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutString
    ********************************************************************************
    *
    * Summary:
    *  This function sends a null terminated string to the PC. This function will
    *  block if there is not enough memory to place the whole string. It will block
    *  until the entire string has been written to the transmit buffer.
    *  The USBUART_CDCIsReady() function should be called before sending data with
    *  a new call to `$INSTANCE_NAME`_PutString(), to be sure that the previous data
    *  has finished sending.
    *
    * Parameters:
    *  string: pointer to the string to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutString(const char8 string[]) `=ReentrantKeil($INSTANCE_NAME . "_PutString")`
    {
        uint16 strLength;
        uint16 sendLength;
        uint16 bufIndex = 0u;

        /* Get length of the null terminated string */
        strLength = `$INSTANCE_NAME`_StrLen(string);
        do
        {
            /* Limits length to maximum packet size for the EP */
            sendLength = (strLength > `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].bufferSize) ?
                          `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].bufferSize : strLength;
             /* Enable IN transfer */
            `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdc_data_in_ep, (const uint8 *)&string[bufIndex], sendLength);
            strLength -= sendLength;

            /* If more data are present to send or full packet was sent */
            if((strLength > 0u) || (sendLength == `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].bufferSize))
            {
                bufIndex += sendLength;
                /* Wait for the Host to read it. */
                while(`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].apiEpState ==
                                          `$INSTANCE_NAME`_IN_BUFFER_FULL)
                {
                    ;
                }
                /* If the last sent packet is exactly maximum packet size, 
                *  it shall be followed by a zero-length packet to assure the
                *  end of segment is properly identified by the terminal.
                */
                if(strLength == 0u)
                {
                    `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdc_data_in_ep, NULL, 0u);
                }
            }
        }while(strLength > 0u);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Writes a single character to the PC.
    *
    * Parameters:
    *  txDataByte: Character to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutChar(char8 txDataByte) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`
    {
        uint8 dataByte;
        dataByte = (uint8)txDataByte;

        `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdc_data_in_ep, &dataByte, 1u);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Sends a carriage return (0x0D) and line feed (0x0A) to the PC
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutCRLF(void) `=ReentrantKeil($INSTANCE_NAME . "_PutCRLF")`
    {
        const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

        `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_cdc_data_in_ep, (const uint8 *)txData, 2u);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCount
    ********************************************************************************
    *
    * Summary:
    *  This function returns the number of bytes that were received from the PC.
    *  The returned length value should be passed to `$INSTANCE_NAME`_GetData() as
    *  a parameter to read all received data. If all of the received data is not
    *  read at one time by the `$INSTANCE_NAME`_GetData() API, the unread data will
    *  be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of received bytes. The maximum amount of received data at
    *  a time is limited by the maximum packet size for the endpoint.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCount")`
    {
        uint16 bytesCount;

        if (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_out_ep].apiEpState == `$INSTANCE_NAME`_OUT_BUFFER_FULL)
        {
            bytesCount = `$INSTANCE_NAME`_GetEPCount(`$INSTANCE_NAME`_cdc_data_out_ep);
        }
        else
        {
            bytesCount = 0u;
        }

        return(bytesCount);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DataIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component received data or received
    *  zero-length packet. The `$INSTANCE_NAME`_GetAll() or
    *  `$INSTANCE_NAME`_GetData() API should be called to read data from the buffer
    *  and re-init OUT endpoint even when zero-length packet received.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the OUT packet received this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_DataIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_DataIsReady")`
    {
        return(`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_out_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CDCIsReady
    ********************************************************************************
    *
    * Summary:
    *  This function returns a nonzero value if the component is ready to send more
    *  data to the PC; otherwise, it returns zero. The function should be called
    *  before sending new data when using any of the following APIs:
    *  `$INSTANCE_NAME`_PutData(),`$INSTANCE_NAME`_PutString(),
    *  `$INSTANCE_NAME`_PutChar or `$INSTANCE_NAME`_PutCRLF(),
    *  to be sure that the previous data has finished sending.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the buffer can accept new data, this function returns a nonzero value.
    *  Otherwise, it returns zero.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_in_ep: CDC IN endpoint number used.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_CDCIsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_CDCIsReady")`
    {
        return(`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_in_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetData
    ********************************************************************************
    *
    * Summary:
    *  This function gets a specified number of bytes from the input buffer and
    *  places them in a data array specified by the passed pointer.
    *  The `$INSTANCE_NAME`_DataIsReady() API should be called first, to be sure
    *  that data is received from the host. If all received data will not be read at
    *  once, the unread data will be lost. The `$INSTANCE_NAME`_GetData() API should
    *  be called to get the number of bytes that were received.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *  Length: Number of bytes to read into the data array from the RX buffer.
    *          Maximum length is limited by the the number of received bytes.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetData(uint8* pData, uint16 length) `=ReentrantKeil($INSTANCE_NAME . "_GetData")`
    {
        return(`$INSTANCE_NAME`_ReadOutEP(`$INSTANCE_NAME`_cdc_data_out_ep, pData, length));
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAll
    ********************************************************************************
    *
    * Summary:
    *  Gets all bytes of received data from the input buffer and places it into a
    *  specified data array. `$INSTANCE_NAME`_DataIsReady() API should be called
    *  before, to be sure that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_out_ep: CDC OUT endpoint number used.
    *   `$INSTANCE_NAME`_EP[].bufferSize: EP max packet size is used as a length
    *     to read all data from the EP buffer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetAll(uint8* pData) `=ReentrantKeil($INSTANCE_NAME . "_GetAll")`
    {
        return (`$INSTANCE_NAME`_ReadOutEP(`$INSTANCE_NAME`_cdc_data_out_ep, pData,
                                           `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_cdc_data_out_ep].bufferSize));
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetChar
    ********************************************************************************
    *
    * Summary:
    *  This function reads one byte of received data from the buffer. If more than
    *  one byte has been received from the host, the rest of the data will be lost.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received one character.
    *
    * Global variables:
    *   `$INSTANCE_NAME`_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetChar(void) `=ReentrantKeil($INSTANCE_NAME . "_GetChar")`
    {
         uint8 rxData;

        (void) `$INSTANCE_NAME`_ReadOutEP(`$INSTANCE_NAME`_cdc_data_out_ep, &rxData, 1u);

        return(rxData);
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IsLineChanged
    ********************************************************************************
    *
    * Summary:
    *  This function returns clear on read status of the line. It returns not zero
    *  value when the host sends updated coding or control information to the
    *  device. The `$INSTANCE_NAME`_GetDTERate(), `$INSTANCE_NAME`_GetCharFormat()
    *  or `$INSTANCE_NAME`_GetParityType() or `$INSTANCE_NAME`_GetDataBits() API
    *  should be called to read data coding information.
    *  The `$INSTANCE_NAME`_GetLineControl() API should be called to read line
    *  control information.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE requests are received, it
    *  returns a nonzero value. Otherwise, it returns zero.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_transferState: it is checked to be sure then OUT data
    *    phase has been complete, and data written to the lineCoding or Control
    *    Bitmap buffer.
    *  `$INSTANCE_NAME`_lineChanged: used as a flag to be aware that Host has been
    *    sent request for changing Line Coding or Control Bitmap.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_IsLineChanged(void) `=ReentrantKeil($INSTANCE_NAME . "_IsLineChanged")`
    {
        uint8 state = 0u;

        /* transferState is checked to be sure then OUT data phase has been complete */
        if(`$INSTANCE_NAME`_transferState == `$INSTANCE_NAME`_TRANS_STATE_IDLE)
        {
            if(`$INSTANCE_NAME`_lineChanged != 0u)
            {
                state = `$INSTANCE_NAME`_lineChanged;
                `$INSTANCE_NAME`_lineChanged = 0u;
            }
        }

        return(state);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetDTERate
    ********************************************************************************
    *
    * Summary:
    *  Returns the data terminal rate set for this port in bits per second.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a uint32 value of the data rate in bits per second.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_lineCoding: First four bytes converted to uint32
    *    depend on compiler, and returned as a data rate.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetDTERate(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDTERate")`
    {
        uint32 rate;

        rate = `$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_RATE + 3u];
        rate = (rate << 8u) | `$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_RATE + 2u];
        rate = (rate << 8u) | `$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_RATE + 1u];
        rate = (rate << 8u) | `$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_RATE];

        return(rate);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCharFormat
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of stop bits.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of stop bits.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCharFormat(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCharFormat")`
    {
        return(`$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_STOP_BITS]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetParityType
    ********************************************************************************
    *
    * Summary:
    *  Returns the parity type for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the parity type.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetParityType(void) `=ReentrantKeil($INSTANCE_NAME . "_GetParityType")`
    {
        return(`$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_PARITY]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of data bits for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of data bits.
    *  The number of data bits can be 5, 6, 7, 8 or 16.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetDataBits(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDataBits")`
    {
        return(`$INSTANCE_NAME`_lineCoding[`$INSTANCE_NAME`_LINE_CODING_DATA_BITS]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetLineControl
    ********************************************************************************
    *
    * Summary:
    *  Returns Line control bitmap.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns Line control bitmap.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_lineControlBitmap: used to get a parameter.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetLineControl(void) `=ReentrantKeil($INSTANCE_NAME . "_GetLineControl")`
    {
        return(`$INSTANCE_NAME`_lineControlBitmap);
    }

#endif  /*  `$INSTANCE_NAME`_ENABLE_CDC_CLASS_API*/


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  `$INSTANCE_NAME`_ENABLE_CDC_CLASS*/


/* [] END OF FILE */
