/*******************************************************************************
* File Name: `$INSTANCE_NAME_pvt`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_pvt_H)
#define CY_USBFS_`$INSTANCE_NAME`_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
`$APIGEN_FUNCDECL`

extern const uint8 CYCODE `$INSTANCE_NAME`_MSOS_DESCRIPTOR[`$INSTANCE_NAME`_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE `$INSTANCE_NAME`_MSOS_CONFIGURATION_DESCR[`$INSTANCE_NAME`_MSOS_CONF_DESCR_LENGTH];
#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    extern uint8 `$INSTANCE_NAME`_idSerialNumberStringDescriptor[`$INSTANCE_NAME`_IDSN_DESCR_LENGTH];
#endif /* `$INSTANCE_NAME`_ENABLE_IDSN_STRING */

extern volatile uint8 `$INSTANCE_NAME`_interfaceNumber;
extern volatile uint8 `$INSTANCE_NAME`_interfaceSetting[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern volatile uint8 `$INSTANCE_NAME`_interfaceSetting_last[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern volatile uint8 `$INSTANCE_NAME`_deviceAddress;
extern volatile uint8 `$INSTANCE_NAME`_interfaceStatus[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *`$INSTANCE_NAME`_interfaceClass;

extern volatile T_`$INSTANCE_NAME`_EP_CTL_BLOCK `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_MAX_EP];
extern volatile T_`$INSTANCE_NAME`_TD `$INSTANCE_NAME`_currentTD;

#if(`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL)
    extern uint8 `$INSTANCE_NAME`_DmaChan[`$INSTANCE_NAME`_MAX_EP];
    extern uint8 `$INSTANCE_NAME`_DmaTd[`$INSTANCE_NAME`_MAX_EP];
#endif /*  `$INSTANCE_NAME`_EP_MM */
#if((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
    extern uint8 `$INSTANCE_NAME`_DmaNextTd[`$INSTANCE_NAME`_MAX_EP];
    extern volatile uint16 `$INSTANCE_NAME`_inLength[`$INSTANCE_NAME`_MAX_EP];
    extern const uint8 *`$INSTANCE_NAME`_inDataPointer[`$INSTANCE_NAME`_MAX_EP];
    extern volatile uint8 `$INSTANCE_NAME`_inBufFull[`$INSTANCE_NAME`_MAX_EP];
#endif /*  ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */

extern volatile uint8 `$INSTANCE_NAME`_ep0Toggle;
extern volatile uint8 `$INSTANCE_NAME`_lastPacketSize;
extern volatile uint8 `$INSTANCE_NAME`_ep0Mode;
extern volatile uint8 `$INSTANCE_NAME`_ep0Count;
extern volatile uint16 `$INSTANCE_NAME`_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  `$INSTANCE_NAME`_ReInitComponent(void) `=ReentrantKeil($INSTANCE_NAME . "_ReInitComponent")`;
void  `$INSTANCE_NAME`_HandleSetup(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleSetup")`;
void  `$INSTANCE_NAME`_HandleIN(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleIN")`;
void  `$INSTANCE_NAME`_HandleOUT(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleOUT")`;
void  `$INSTANCE_NAME`_LoadEP0(void) `=ReentrantKeil($INSTANCE_NAME . "_LoadEP0")`;
uint8 `$INSTANCE_NAME`_InitControlRead(void) `=ReentrantKeil($INSTANCE_NAME . "_InitControlRead")`;
uint8 `$INSTANCE_NAME`_InitControlWrite(void) `=ReentrantKeil($INSTANCE_NAME . "_InitControlWrite")`;
void  `$INSTANCE_NAME`_ControlReadDataStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlReadDataStage")`;
void  `$INSTANCE_NAME`_ControlReadStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlReadStatusStage")`;
void  `$INSTANCE_NAME`_ControlReadPrematureStatus(void)
                                                `=ReentrantKeil($INSTANCE_NAME . "_ControlReadPrematureStatus")`;
uint8 `$INSTANCE_NAME`_InitControlWrite(void) `=ReentrantKeil($INSTANCE_NAME . "_InitControlWrite")`;
uint8 `$INSTANCE_NAME`_InitZeroLengthControlTransfer(void)
                                                `=ReentrantKeil($INSTANCE_NAME . "_InitZeroLengthControlTransfer")`;
void  `$INSTANCE_NAME`_ControlWriteDataStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteDataStage")`;
void  `$INSTANCE_NAME`_ControlWriteStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteStatusStage")`;
void  `$INSTANCE_NAME`_ControlWritePrematureStatus(void)
                                                `=ReentrantKeil($INSTANCE_NAME . "_ControlWritePrematureStatus")`;
uint8 `$INSTANCE_NAME`_InitNoDataControlTransfer(void) `=ReentrantKeil($INSTANCE_NAME . "_InitNoDataControlTransfer")`;
void  `$INSTANCE_NAME`_NoDataControlStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_NoDataControlStatusStage")`;
void  `$INSTANCE_NAME`_InitializeStatusBlock(void) `=ReentrantKeil($INSTANCE_NAME . "_InitializeStatusBlock")`;
void  `$INSTANCE_NAME`_UpdateStatusBlock(uint8 completionCode) `=ReentrantKeil($INSTANCE_NAME . "_UpdateStatusBlock")`;
uint8 `$INSTANCE_NAME`_DispatchClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchClassRqst")`;

void `$INSTANCE_NAME`_Config(uint8 clearAltSetting) `=ReentrantKeil($INSTANCE_NAME . "_Config")`;
void `$INSTANCE_NAME`_ConfigAltChanged(void) `=ReentrantKeil($INSTANCE_NAME . "_ConfigAltChanged")`;
void `$INSTANCE_NAME`_ConfigReg(void) `=ReentrantKeil($INSTANCE_NAME . "_ConfigReg")`;

const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetConfigTablePtr(uint8 confIndex)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetConfigTablePtr")`;
const T_`$INSTANCE_NAME`_LUT CYCODE *`$INSTANCE_NAME`_GetDeviceTablePtr(void)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetDeviceTablePtr")`;
const uint8 CYCODE *`$INSTANCE_NAME`_GetInterfaceClassTablePtr(void)
                                                    `=ReentrantKeil($INSTANCE_NAME . "_GetInterfaceClassTablePtr")`;
uint8 `$INSTANCE_NAME`_ClearEndpointHalt(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearEndpointHalt")`;
uint8 `$INSTANCE_NAME`_SetEndpointHalt(void) `=ReentrantKeil($INSTANCE_NAME . "_SetEndpointHalt")`;
uint8 `$INSTANCE_NAME`_ValidateAlternateSetting(void) `=ReentrantKeil($INSTANCE_NAME . "_ValidateAlternateSetting")`;

void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

#if ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
    void `$INSTANCE_NAME`_LoadNextInEP(uint8 epNumber, uint8 mode) `=ReentrantKeil($INSTANCE_NAME . "_LoadNextInEP")`;
#endif /* (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */
    
#if defined(`$INSTANCE_NAME`_ENABLE_IDSN_STRING)
    void `$INSTANCE_NAME`_ReadDieID(uint8 descr[]) `=ReentrantKeil($INSTANCE_NAME . "_ReadDieID")`;
#endif /* `$INSTANCE_NAME`_ENABLE_IDSN_STRING */

#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchHIDClassRqst(void);
#endif /*  `$INSTANCE_NAME`_ENABLE_HID_CLASS */
#if defined(`$INSTANCE_NAME`_ENABLE_AUDIO_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchAUDIOClassRqst(void);
#endif /*  `$INSTANCE_NAME`_ENABLE_HID_CLASS */
#if defined(`$INSTANCE_NAME`_ENABLE_CDC_CLASS)
    uint8 `$INSTANCE_NAME`_DispatchCDCClassRqst(void);
#endif /*  `$INSTANCE_NAME`_ENABLE_CDC_CLASS */

CY_ISR_PROTO(`$INSTANCE_NAME`_EP_0_ISR);
#if(`$INSTANCE_NAME`_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_1_ISR);
#endif /*  `$INSTANCE_NAME`_EP1_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_2_ISR);
#endif /*  `$INSTANCE_NAME`_EP2_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_3_ISR);
#endif /*  `$INSTANCE_NAME`_EP3_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_4_ISR);
#endif /*  `$INSTANCE_NAME`_EP4_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_5_ISR);
#endif /*  `$INSTANCE_NAME`_EP5_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_6_ISR);
#endif /*  `$INSTANCE_NAME`_EP6_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_7_ISR);
#endif /*  `$INSTANCE_NAME`_EP7_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_8_ISR);
#endif /*  `$INSTANCE_NAME`_EP8_ISR_REMOVE */
CY_ISR_PROTO(`$INSTANCE_NAME`_BUS_RESET_ISR);
#if(`$INSTANCE_NAME`_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_SOF_ISR);
#endif /*  `$INSTANCE_NAME`_SOF_ISR_REMOVE */
#if(`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL)
    CY_ISR_PROTO(`$INSTANCE_NAME`_ARB_ISR);
#endif /*  `$INSTANCE_NAME`_EP_MM */
#if(`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(`$INSTANCE_NAME`_DP_ISR);
#endif /*  `$INSTANCE_NAME`_DP_ISR_REMOVE */
#if ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
    CY_ISR_PROTO(`$INSTANCE_NAME`_EP_DMA_DONE_ISR);
#endif /* (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */

/***************************************
* Request Handlers
***************************************/

uint8 `$INSTANCE_NAME`_HandleStandardRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleStandardRqst")`;
uint8 `$INSTANCE_NAME`_DispatchClassRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_DispatchClassRqst")`;
uint8 `$INSTANCE_NAME`_HandleVendorRqst(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleVendorRqst")`;


/***************************************
*    HID Internal references
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_HID_CLASS)
    void `$INSTANCE_NAME`_FindReport(void) `=ReentrantKeil($INSTANCE_NAME . "_FindReport")`;
    void `$INSTANCE_NAME`_FindReportDescriptor(void) `=ReentrantKeil($INSTANCE_NAME . "_FindReportDescriptor")`;
    void `$INSTANCE_NAME`_FindHidClassDecriptor(void) `=ReentrantKeil($INSTANCE_NAME . "_FindHidClassDecriptor")`;
#endif /* `$INSTANCE_NAME`_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING)
    void `$INSTANCE_NAME`_MIDI_IN_EP_Service(void) `=ReentrantKeil($INSTANCE_NAME . "_MIDI_IN_EP_Service")`;
#endif /* `$INSTANCE_NAME`_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_`$INSTANCE_NAME`_pvt_H */


/* [] END OF FILE */
