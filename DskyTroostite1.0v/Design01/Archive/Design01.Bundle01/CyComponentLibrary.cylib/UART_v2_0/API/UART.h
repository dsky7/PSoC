/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#include "cytypes.h"
#include "cyfitter.h"

#if !defined(CY_UART_`$INSTANCE_NAME`_H)
#define CY_UART_`$INSTANCE_NAME`_H


/***************************************
* Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_RX_ENABLED                     (`$Enable_RX`u)
#define `$INSTANCE_NAME`_TX_ENABLED                     (`$Enable_TX`u)
#define `$INSTANCE_NAME`_HD_ENABLED                     (`$HalfDuplexEn`u)
#define `$INSTANCE_NAME`_RX_INTERRUPT_ENABLED           (`$Enable_RXIntInterrupt`u)
#define `$INSTANCE_NAME`_TX_INTERRUPT_ENABLED           (`$Enable_TXIntInterrupt`u)
#define `$INSTANCE_NAME`_INTERNAL_CLOCK_USED            (`$InternalClockUsed`u)
#define `$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED           (`$EnableHWAddress`u)
#define `$INSTANCE_NAME`_OVER_SAMPLE_COUNT              (`$OverSamplingRate`u)
#define `$INSTANCE_NAME`_PARITY_TYPE                    (`$ParityType`u)
#define `$INSTANCE_NAME`_PARITY_TYPE_SW                 (`$ParityTypeSw`u)
#define `$INSTANCE_NAME`_BREAK_DETECT                   (`$BreakDetect`u)
#define `$INSTANCE_NAME`_BREAK_BITS_TX                  (`$BreakBitsTX`u)
#define `$INSTANCE_NAME`_BREAK_BITS_RX                  (`$BreakBitsRX`u)
#define `$INSTANCE_NAME`_TXCLKGEN_DP                    (`$TXBitClkGenDP`u)
#define `$INSTANCE_NAME`_USE23POLLING                   (`$Use23Polling`u)

/* PSoC3 ES2 or early */
#define `$INSTANCE_NAME`_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES1 or early */
#define `$INSTANCE_NAME`_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define `$INSTANCE_NAME`_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES2 or later */
#define `$INSTANCE_NAME`_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

#if(`$INSTANCE_NAME`_PSOC3_ES2 && (`$INSTANCE_NAME`_RX_INTERRUPT_ENABLED || `$INSTANCE_NAME`_TX_INTERRUPT_ENABLED))
    #include <intrins.h>
    #define `$INSTANCE_NAME`_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
#endif /* End PSOC3_ES2 */

#ifdef `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG
    #define `$INSTANCE_NAME`_CONTROL_REG_REMOVED            (0u)
#else
    #define `$INSTANCE_NAME`_CONTROL_REG_REMOVED            (1u)
#endif /* End `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _`$INSTANCE_NAME`_backupStruct
{
    uint8 enableState;

    #if(`$INSTANCE_NAME`_CONTROL_REG_REMOVED == 0u)
        uint8 cr;            
    #endif /* End `$INSTANCE_NAME`_CONTROL_REG_REMOVED */    
    #if( (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )
        uint8 rx_period;
        #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 rx_mask;
            #if (`$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End `$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED */
        #endif /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif  /* End (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED)*/

    #if(`$INSTANCE_NAME`_TX_ENABLED)
        #if(`$INSTANCE_NAME`_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
                uint8 tx_clk_compl;
            #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
        #else
            uint8 tx_period;
        #endif /*End `$INSTANCE_NAME`_TXCLKGEN_DP */
        #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) /* PSoC3 ES2 or early, PSoC5 ES1*/
            uint8 tx_mask;
        #endif  /* End PSOC3_ES2 || PSOC5_ES1 */
    #endif /*End `$INSTANCE_NAME`_TX_ENABLED */
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
uint8 `$INSTANCE_NAME`_ReadControlRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadControlRegister")`;
void `$INSTANCE_NAME`_WriteControlRegister(uint8 control) `=ReentrantKeil($INSTANCE_NAME . "_WriteControlRegister")`;

void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);

/* Only if RX is enabled */
#if( (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )

    #if(`$INSTANCE_NAME`_RX_INTERRUPT_ENABLED)
        void  `$INSTANCE_NAME`_EnableRxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableRxInt")`;
        void  `$INSTANCE_NAME`_DisableRxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableRxInt")`;
        CY_ISR_PROTO(`$INSTANCE_NAME`_RXISR);
    #endif /* `$INSTANCE_NAME`_RX_INTERRUPT_ENABLED */

    #if (`$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED)
        void `$INSTANCE_NAME`_SetRxAddressMode(uint8 addressMode) 
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetRxAddressMode")`;
        void `$INSTANCE_NAME`_SetRxAddress1(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetRxAddress1")`;
        void `$INSTANCE_NAME`_SetRxAddress2(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetRxAddress2")`;
    #endif /* End `$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED */

    void  `$INSTANCE_NAME`_SetRxInterruptMode(uint8 intSrc) `=ReentrantKeil($INSTANCE_NAME . "_SetRxInterruptMode")`;
    uint8 `$INSTANCE_NAME`_ReadRxData(void);
    uint8 `$INSTANCE_NAME`_ReadRxStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadRxStatus")`;
    uint8 `$INSTANCE_NAME`_GetChar(void);
    uint16 `$INSTANCE_NAME`_GetByte(void);
    `$RxBuffRegSizeReplacementString` `$INSTANCE_NAME`_GetRxBufferSize(void);
    void `$INSTANCE_NAME`_ClearRxBuffer(void);

    /* Obsolete functions, defines for backward compatible */
    #define `$INSTANCE_NAME`_GetRxInterruptSource   `$INSTANCE_NAME`_ReadRxStatus

#endif /* End (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) */

/* Only if TX is enabled */
#if(`$INSTANCE_NAME`_TX_ENABLED || `$INSTANCE_NAME`_HD_ENABLED)

    #if(`$INSTANCE_NAME`_TX_INTERRUPT_ENABLED)
        void `$INSTANCE_NAME`_EnableTxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableTxInt")`;
        void `$INSTANCE_NAME`_DisableTxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableTxInt")`;
        CY_ISR_PROTO(`$INSTANCE_NAME`_TXISR);
    #endif /* `$INSTANCE_NAME`_TX_INTERRUPT_ENABLED */

    void `$INSTANCE_NAME`_SetTxInterruptMode(uint8 intSrc) `=ReentrantKeil($INSTANCE_NAME . "_SetTxInterruptMode")`;
    void `$INSTANCE_NAME`_WriteTxData(uint8 txDataByte);
    uint8 `$INSTANCE_NAME`_ReadTxStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadTxStatus")`;
    void `$INSTANCE_NAME`_PutChar(uint8 txDataByte);
    void `$INSTANCE_NAME`_PutString(uint8* string);
    void `$INSTANCE_NAME`_PutArray(uint8* string, `$TxBuffRegSizeReplacementString` byteCount);
    void `$INSTANCE_NAME`_PutCRLF(uint8 txDataByte);
    void `$INSTANCE_NAME`_ClearTxBuffer(void);
    void `$INSTANCE_NAME`_SetTxAddressMode(uint8 addressMode) `=ReentrantKeil($INSTANCE_NAME . "_SetTxAddressMode")`;
    void `$INSTANCE_NAME`_SendBreak(uint8 retMode);
    `$TxBuffRegSizeReplacementString` `$INSTANCE_NAME`_GetTxBufferSize(void);
    /* Obsolete functions, defines for backward compatible */
    #define `$INSTANCE_NAME`_PutStringConst         `$INSTANCE_NAME`_PutString
    #define `$INSTANCE_NAME`_PutArrayConst          `$INSTANCE_NAME`_PutArray
    #define `$INSTANCE_NAME`_GetTxInterruptSource   `$INSTANCE_NAME`_ReadTxStatus
    
#endif /* End `$INSTANCE_NAME`_TX_ENABLED || `$INSTANCE_NAME`_HD_ENABLED */

#if(`$INSTANCE_NAME`_HD_ENABLED)
    void `$INSTANCE_NAME`_LoadRxConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_LoadRxConfig")`;
    void `$INSTANCE_NAME`_LoadTxConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_LoadTxConfig")`;
#endif /* End `$INSTANCE_NAME`_HD_ENABLED */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define `$INSTANCE_NAME`_SET_SPACE                              (0x00u)
#define `$INSTANCE_NAME`_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (`$INSTANCE_NAME`_TX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )
    #if(`$INSTANCE_NAME`_TX_INTERRUPT_ENABLED)
        #define `$INSTANCE_NAME`_TX_VECT_NUM                `$INSTANCE_NAME`_TXInternalInterrupt__INTC_NUMBER
        #define `$INSTANCE_NAME`_TX_PRIOR_NUM               `$INSTANCE_NAME`_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* `$INSTANCE_NAME`_TX_INTERRUPT_ENABLED */
    #if(`$INSTANCE_NAME`_TX_ENABLED) 
        #define `$INSTANCE_NAME`_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define `$INSTANCE_NAME`_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define `$INSTANCE_NAME`_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define `$INSTANCE_NAME`_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* `$INSTANCE_NAME`_TX_ENABLED */
    #if(`$INSTANCE_NAME`_HD_ENABLED) 
        #define `$INSTANCE_NAME`_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define `$INSTANCE_NAME`_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define `$INSTANCE_NAME`_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define `$INSTANCE_NAME`_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* `$INSTANCE_NAME`_HD_ENABLED */
    #define `$INSTANCE_NAME`_TX_STS_COMPLETE                (0x01u << `$INSTANCE_NAME`_TX_STS_COMPLETE_SHIFT)
    #define `$INSTANCE_NAME`_TX_STS_FIFO_EMPTY              (0x01u << `$INSTANCE_NAME`_TX_STS_FIFO_EMPTY_SHIFT)
    #define `$INSTANCE_NAME`_TX_STS_FIFO_FULL               (0x01u << `$INSTANCE_NAME`_TX_STS_FIFO_FULL_SHIFT)
    #define `$INSTANCE_NAME`_TX_STS_FIFO_NOT_FULL           (0x01u << `$INSTANCE_NAME`_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (`$INSTANCE_NAME`_TX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED)*/

#if( (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )
    #if(`$INSTANCE_NAME`_RX_INTERRUPT_ENABLED)
        #define `$INSTANCE_NAME`_RX_VECT_NUM                `$INSTANCE_NAME`_RXInternalInterrupt__INTC_NUMBER
        #define `$INSTANCE_NAME`_RX_PRIOR_NUM               `$INSTANCE_NAME`_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* `$INSTANCE_NAME`_RX_INTERRUPT_ENABLED */
    #define `$INSTANCE_NAME`_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define `$INSTANCE_NAME`_RX_STS_BREAK_SHIFT             (0x01u)
    #define `$INSTANCE_NAME`_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define `$INSTANCE_NAME`_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define `$INSTANCE_NAME`_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define `$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define `$INSTANCE_NAME`_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define `$INSTANCE_NAME`_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define `$INSTANCE_NAME`_RX_STS_MRKSPC                  (0x01u << `$INSTANCE_NAME`_RX_STS_MRKSPC_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_BREAK                   (0x01u << `$INSTANCE_NAME`_RX_STS_BREAK_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_PAR_ERROR               (0x01u << `$INSTANCE_NAME`_RX_STS_PAR_ERROR_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_STOP_ERROR              (0x01u << `$INSTANCE_NAME`_RX_STS_STOP_ERROR_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_OVERRUN                 (0x01u << `$INSTANCE_NAME`_RX_STS_OVERRUN_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY           (0x01u << `$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_ADDR_MATCH              (0x01u << `$INSTANCE_NAME`_RX_STS_ADDR_MATCH_SHIFT)
    #define `$INSTANCE_NAME`_RX_STS_SOFT_BUFF_OVER          (0x01u << `$INSTANCE_NAME`_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define `$INSTANCE_NAME`_RX_HW_MASK                     (0x7Fu)
#endif /* End (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) */

/* Control Register definitions */
#define `$INSTANCE_NAME`_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define `$INSTANCE_NAME`_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define `$INSTANCE_NAME`_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define `$INSTANCE_NAME`_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define `$INSTANCE_NAME`_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define `$INSTANCE_NAME`_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define `$INSTANCE_NAME`_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define `$INSTANCE_NAME`_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define `$INSTANCE_NAME`_CTRL_HD_SEND                       (0x01u << `$INSTANCE_NAME`_CTRL_HD_SEND_SHIFT)
#define `$INSTANCE_NAME`_CTRL_HD_SEND_BREAK                 (0x01u << `$INSTANCE_NAME`_CTRL_HD_SEND_BREAK_SHIFT)
#define `$INSTANCE_NAME`_CTRL_MARK                          (0x01u << `$INSTANCE_NAME`_CTRL_MARK_SHIFT)
#define `$INSTANCE_NAME`_CTRL_PARITY_TYPE_MASK              (0x03u << `$INSTANCE_NAME`_CTRL_PARITY_TYPE0_SHIFT)
#define `$INSTANCE_NAME`_CTRL_RXADDR_MODE_MASK              (0x07u << `$INSTANCE_NAME`_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define `$INSTANCE_NAME`_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define `$INSTANCE_NAME`_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define `$INSTANCE_NAME`_SEND_BREAK                         (0x00u)
#define `$INSTANCE_NAME`_WAIT_FOR_COMLETE_REINIT            (0x01u)
#define `$INSTANCE_NAME`_REINIT                             (0x02u)
#define `$INSTANCE_NAME`_SEND_WAIT_REINIT                   (0x03u)

#define `$INSTANCE_NAME`_OVER_SAMPLE_8                      (8u)
#define `$INSTANCE_NAME`_OVER_SAMPLE_16                     (16u)

#define `$INSTANCE_NAME`_BIT_CENTER                         (`$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u)

#define `$INSTANCE_NAME`_FIFO_LENGTH                        (4u)
#define `$INSTANCE_NAME`_NUMBER_OF_START_BIT                (1u)

/* 8X always for count7 implementation*/
#define `$INSTANCE_NAME`_TXBITCTR_BREAKBITS8X   (`$INSTANCE_NAME`_BREAK_BITS_TX * `$INSTANCE_NAME`_OVER_SAMPLE_8 - 1u)
/* 8X or 16X for DP implementation*/
#define `$INSTANCE_NAME`_TXBITCTR_BREAKBITS   (`$INSTANCE_NAME`_BREAK_BITS_TX * `$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u)

#if (`$INSTANCE_NAME`_OVER_SAMPLE_COUNT == `$INSTANCE_NAME`_OVER_SAMPLE_8)
    #define `$INSTANCE_NAME`_HD_TXBITCTR_INIT   ((`$INSTANCE_NAME`_BREAK_BITS_TX + \
        `$INSTANCE_NAME`_NUMBER_OF_START_BIT) * `$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u)
    /* This parameter is increased on the 1 in 2 out of 3 mode to sample voting in the middle */
    #define `$INSTANCE_NAME`_HD_RXBITCTR_INIT   ((`$INSTANCE_NAME`_BREAK_BITS_RX + \
    `$INSTANCE_NAME`_NUMBER_OF_START_BIT) * `$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u + \
    (`$INSTANCE_NAME`_OVER_SAMPLE_COUNT / 2u) + (`$INSTANCE_NAME`_USE23POLLING * 2u) - 1u)
#else /* `$INSTANCE_NAME`_OVER_SAMPLE_COUNT == `$INSTANCE_NAME`_OVER_SAMPLE_16 */
    #define `$INSTANCE_NAME`_HD_TXBITCTR_INIT   (8u * `$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u)
    #define `$INSTANCE_NAME`_HD_RXBITCTR_INIT   (7u * `$INSTANCE_NAME`_OVER_SAMPLE_COUNT - 1u  +  \
       (`$INSTANCE_NAME`_OVER_SAMPLE_COUNT / 2u) + (`$INSTANCE_NAME`_USE23POLLING * 2u) - 1u)
#endif /* End `$INSTANCE_NAME`_OVER_SAMPLE_COUNT */


/***************************************
* Enumerated Types and Parameters
***************************************/

`#cy_declare_enum B_UART__AddressModes`
`#cy_declare_enum B_UART__Parity_Type_revB`

/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_TXBUFFERSIZE           (`$TXBufferSize`u)
#define `$INSTANCE_NAME`_RXBUFFERSIZE           (`$RXBufferSize`u)
/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define `$INSTANCE_NAME`_NUMBER_OF_DATA_BITS    ((`$NumDataBits`u > 8u) ? 8u : `$NumDataBits`u)
#define `$INSTANCE_NAME`_NUMBER_OF_STOP_BITS    (`$NumStopBits`u)

#if (`$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED)
    #define `$INSTANCE_NAME`_RXAddressMode      (`$RXAddressMode`u)
    #define `$INSTANCE_NAME`_RXHWADDRESS1       (`$Address1`u)
    #define `$INSTANCE_NAME`_RXHWADDRESS2       (`$Address2`u)
#endif /* End EnableHWAddress */

#define `$INSTANCE_NAME`_INIT_RX_INTERRUPTS_MASK \
                                          (`$InterruptOnByteRcvd` << `$INSTANCE_NAME`_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (`$InterruptOnAddDetect` << `$INSTANCE_NAME`_RX_STS_MRKSPC_SHIFT) \
                                        | (`$InterruptOnAddressMatch` << `$INSTANCE_NAME`_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (`$InterruptOnParityError` << `$INSTANCE_NAME`_RX_STS_PAR_ERROR_SHIFT) \
                                        | (`$InterruptOnStopError` << `$INSTANCE_NAME`_RX_STS_STOP_ERROR_SHIFT) \
                                        | (`$InterruptOnBreak` << `$INSTANCE_NAME`_RX_STS_BREAK_SHIFT) \
                                        | (`$InterruptOnOverrunError` << `$INSTANCE_NAME`_RX_STS_OVERRUN_SHIFT)

#define `$INSTANCE_NAME`_INIT_TX_INTERRUPTS_MASK \
                                          (`$InterruptOnTXComplete` << `$INSTANCE_NAME`_TX_STS_COMPLETE_SHIFT) \
                                        | (`$InterruptOnTXFifoEmpty` << `$INSTANCE_NAME`_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (`$InterruptOnTXFifoFull` << `$INSTANCE_NAME`_TX_STS_FIFO_FULL_SHIFT) \
                                        | (`$InterruptOnTXFifoNotFull` << `$INSTANCE_NAME`_TX_STS_FIFO_NOT_FULL_SHIFT)


/***************************************
*              Registers
***************************************/

#ifdef `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG
    #define `$INSTANCE_NAME`_CONTROL_REG \
                            (* (reg8 *) `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG )
    #define `$INSTANCE_NAME`_CONTROL_PTR \
                            (  (reg8 *) `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG )
#endif /* End `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG */

#if(`$INSTANCE_NAME`_TX_ENABLED)
    #define `$INSTANCE_NAME`_TXDATA_REG          (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxShifter_u0__F0_REG)
    #define `$INSTANCE_NAME`_TXDATA_PTR          (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxShifter_u0__F0_REG)

    #define `$INSTANCE_NAME`_TXSTATUS_REG        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__STATUS_REG)
    #define `$INSTANCE_NAME`_TXSTATUS_PTR        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__STATUS_REG)
    #define `$INSTANCE_NAME`_TXSTATUS_MASK_REG   (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__MASK_REG)
    #define `$INSTANCE_NAME`_TXSTATUS_MASK_PTR   (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__MASK_REG)
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL_REG   (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL_PTR   (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(`$INSTANCE_NAME`_TXCLKGEN_DP)
        #define `$INSTANCE_NAME`_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define `$INSTANCE_NAME`_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define `$INSTANCE_NAME`_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define `$INSTANCE_NAME`_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define `$INSTANCE_NAME`_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define `$INSTANCE_NAME`_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define `$INSTANCE_NAME`_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define `$INSTANCE_NAME`_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define `$INSTANCE_NAME`_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define `$INSTANCE_NAME`_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* `$INSTANCE_NAME`_TXCLKGEN_DP */

#endif /* End `$INSTANCE_NAME`_TX_ENABLED */

#if(`$INSTANCE_NAME`_HD_ENABLED)

    #define `$INSTANCE_NAME`_TXDATA_REG             (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__F1_REG )
    #define `$INSTANCE_NAME`_TXDATA_PTR             (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__F1_REG )

    #define `$INSTANCE_NAME`_TXSTATUS_REG           (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_REG )
    #define `$INSTANCE_NAME`_TXSTATUS_PTR           (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_REG )
    #define `$INSTANCE_NAME`_TXSTATUS_MASK_REG      (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__MASK_REG )
    #define `$INSTANCE_NAME`_TXSTATUS_MASK_PTR      (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__MASK_REG )
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL_REG      (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL_PTR      (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End `$INSTANCE_NAME`_HD_ENABLED */

#if( (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )
    #define `$INSTANCE_NAME`_RXDATA_REG             (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__F0_REG )
    #define `$INSTANCE_NAME`_RXDATA_PTR             (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__F0_REG )
    #define `$INSTANCE_NAME`_RXADDRESS1_REG         (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__D0_REG )
    #define `$INSTANCE_NAME`_RXADDRESS1_PTR         (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__D0_REG )
    #define `$INSTANCE_NAME`_RXADDRESS2_REG         (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__D1_REG )
    #define `$INSTANCE_NAME`_RXADDRESS2_PTR         (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxShifter_u0__D1_REG )

    #define `$INSTANCE_NAME`_RXBITCTR_PERIOD_REG    (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define `$INSTANCE_NAME`_RXBITCTR_PERIOD_PTR    (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define `$INSTANCE_NAME`_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define `$INSTANCE_NAME`_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define `$INSTANCE_NAME`_RXBITCTR_COUNTER_REG   (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__COUNT_REG )
    #define `$INSTANCE_NAME`_RXBITCTR_COUNTER_PTR   (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxBitCounter__COUNT_REG )

    #define `$INSTANCE_NAME`_RXSTATUS_REG           (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_REG )
    #define `$INSTANCE_NAME`_RXSTATUS_PTR           (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_REG )
    #define `$INSTANCE_NAME`_RXSTATUS_MASK_REG      (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__MASK_REG )
    #define `$INSTANCE_NAME`_RXSTATUS_MASK_PTR      (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__MASK_REG )
    #define `$INSTANCE_NAME`_RXSTATUS_ACTL_REG      (* (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define `$INSTANCE_NAME`_RXSTATUS_ACTL_PTR      (  (reg8 *) `$INSTANCE_NAME`_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) */

#if(`$INSTANCE_NAME`_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define `$INSTANCE_NAME`_INTCLOCK_CLKEN_REG     (* (reg8 *) `$INSTANCE_NAME`_IntClock__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_INTCLOCK_CLKEN_PTR     (  (reg8 *) `$INSTANCE_NAME`_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define `$INSTANCE_NAME`_INTCLOCK_CLKEN_MASK    `$INSTANCE_NAME`_IntClock__PM_ACT_MSK
#endif /* End `$INSTANCE_NAME`_INTERNAL_CLOCK_USED */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/

#define `$INSTANCE_NAME`_initvar                    `$INSTANCE_NAME`_initVar

#define `$INSTANCE_NAME`_RX_Enabled                 `$INSTANCE_NAME`_RX_ENABLED
#define `$INSTANCE_NAME`_TX_Enabled                 `$INSTANCE_NAME`_TX_ENABLED
#define `$INSTANCE_NAME`_HD_Enabled                 `$INSTANCE_NAME`_HD_ENABLED
#define `$INSTANCE_NAME`_RX_IntInterruptEnabled     `$INSTANCE_NAME`_RX_INTERRUPT_ENABLED
#define `$INSTANCE_NAME`_TX_IntInterruptEnabled     `$INSTANCE_NAME`_TX_INTERRUPT_ENABLED
#define `$INSTANCE_NAME`_InternalClockUsed          `$INSTANCE_NAME`_INTERNAL_CLOCK_USED
#define `$INSTANCE_NAME`_RXHW_Address_Enabled       `$INSTANCE_NAME`_RXHW_ADDRESS_ENABLED
#define `$INSTANCE_NAME`_OverSampleCount            `$INSTANCE_NAME`_OVER_SAMPLE_COUNT
#define `$INSTANCE_NAME`_ParityType                 `$INSTANCE_NAME`_PARITY_TYPE

#if( `$INSTANCE_NAME`_TX_ENABLED && (`$INSTANCE_NAME`_TXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH))
    #define `$INSTANCE_NAME`_TXBUFFER               `$INSTANCE_NAME`_txBuffer
    #define `$INSTANCE_NAME`_TXBUFFERREAD           `$INSTANCE_NAME`_txBufferRead 
    #define `$INSTANCE_NAME`_TXBUFFERWRITE          `$INSTANCE_NAME`_txBufferWrite 
#endif /* End `$INSTANCE_NAME`_TX_ENABLED */
#if( ( `$INSTANCE_NAME`_RX_ENABLED || `$INSTANCE_NAME`_HD_ENABLED ) && \
     (`$INSTANCE_NAME`_RXBUFFERSIZE > `$INSTANCE_NAME`_FIFO_LENGTH) )
    #define `$INSTANCE_NAME`_RXBUFFER               `$INSTANCE_NAME`_rxBuffer
    #define `$INSTANCE_NAME`_RXBUFFERREAD           `$INSTANCE_NAME`_rxBufferRead 
    #define `$INSTANCE_NAME`_RXBUFFERWRITE          `$INSTANCE_NAME`_rxBufferWrite 
    #define `$INSTANCE_NAME`_RXBUFFERLOOPDETECT     `$INSTANCE_NAME`_rxBufferLoopDetect
    #define `$INSTANCE_NAME`_RXBUFFER_OVERFLOW      `$INSTANCE_NAME`_rxBufferOverflow
#endif /* End `$INSTANCE_NAME`_RX_ENABLED */

#ifdef `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG
    #define `$INSTANCE_NAME`_CONTROL                `$INSTANCE_NAME`_CONTROL_REG 
#endif /* End `$INSTANCE_NAME`_BUART_sCR_`$CtrlModeReplacementString`_CtrlReg__CONTROL_REG */

#if(`$INSTANCE_NAME`_TX_ENABLED)
    #define `$INSTANCE_NAME`_TXDATA                 `$INSTANCE_NAME`_TXDATA_REG
    #define `$INSTANCE_NAME`_TXSTATUS               `$INSTANCE_NAME`_TXSTATUS_REG
    #define `$INSTANCE_NAME`_TXSTATUS_MASK          `$INSTANCE_NAME`_TXSTATUS_MASK_REG   
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL          `$INSTANCE_NAME`_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(`$INSTANCE_NAME`_TXCLKGEN_DP)
        #define `$INSTANCE_NAME`_TXBITCLKGEN_CTR        `$INSTANCE_NAME`_TXBITCLKGEN_CTR_REG
        #define `$INSTANCE_NAME`_TXBITCLKTX_COMPLETE    `$INSTANCE_NAME`_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define `$INSTANCE_NAME`_TXBITCTR_PERIOD        `$INSTANCE_NAME`_TXBITCTR_PERIOD_REG
        #define `$INSTANCE_NAME`_TXBITCTR_CONTROL       `$INSTANCE_NAME`_TXBITCTR_CONTROL_REG
        #define `$INSTANCE_NAME`_TXBITCTR_COUNTER       `$INSTANCE_NAME`_TXBITCTR_COUNTER_REG
    #endif /* `$INSTANCE_NAME`_TXCLKGEN_DP */
#endif /* End `$INSTANCE_NAME`_TX_ENABLED */

#if(`$INSTANCE_NAME`_HD_ENABLED)
    #define `$INSTANCE_NAME`_TXDATA                 `$INSTANCE_NAME`_TXDATA_REG
    #define `$INSTANCE_NAME`_TXSTATUS               `$INSTANCE_NAME`_TXSTATUS_REG
    #define `$INSTANCE_NAME`_TXSTATUS_MASK          `$INSTANCE_NAME`_TXSTATUS_MASK_REG   
    #define `$INSTANCE_NAME`_TXSTATUS_ACTL          `$INSTANCE_NAME`_TXSTATUS_ACTL_REG
#endif /* End `$INSTANCE_NAME`_HD_ENABLED */

#if( (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) )
    #define `$INSTANCE_NAME`_RXDATA                 `$INSTANCE_NAME`_RXDATA_REG             
    #define `$INSTANCE_NAME`_RXADDRESS1             `$INSTANCE_NAME`_RXADDRESS1_REG
    #define `$INSTANCE_NAME`_RXADDRESS2             `$INSTANCE_NAME`_RXADDRESS2_REG
    #define `$INSTANCE_NAME`_RXBITCTR_PERIOD        `$INSTANCE_NAME`_RXBITCTR_PERIOD_REG
    #define `$INSTANCE_NAME`_RXBITCTR_CONTROL       `$INSTANCE_NAME`_RXBITCTR_CONTROL_REG
    #define `$INSTANCE_NAME`_RXBITCTR_COUNTER       `$INSTANCE_NAME`_RXBITCTR_COUNTER_REG
    #define `$INSTANCE_NAME`_RXSTATUS               `$INSTANCE_NAME`_RXSTATUS_REG
    #define `$INSTANCE_NAME`_RXSTATUS_MASK          `$INSTANCE_NAME`_RXSTATUS_MASK_REG
    #define `$INSTANCE_NAME`_RXSTATUS_ACTL          `$INSTANCE_NAME`_RXSTATUS_ACTL_REG
#endif /* End  (`$INSTANCE_NAME`_RX_ENABLED) || (`$INSTANCE_NAME`_HD_ENABLED) */

#if(`$INSTANCE_NAME`_INTERNAL_CLOCK_USED)
    #define `$INSTANCE_NAME`_INTCLOCK_CLKEN         `$INSTANCE_NAME`_INTCLOCK_CLKEN_REG
#endif /* End `$INSTANCE_NAME`_INTERNAL_CLOCK_USED */

#endif  /* CY_UART_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
