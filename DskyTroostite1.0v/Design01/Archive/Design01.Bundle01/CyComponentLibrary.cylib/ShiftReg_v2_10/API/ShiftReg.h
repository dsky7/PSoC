/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#ifndef CY_SHIFTREG_`$INSTANCE_NAME`_H
#define CY_SHIFTREG_`$INSTANCE_NAME`_H

#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_FIFO_SIZE                (`$FifoSize`u)
#define `$INSTANCE_NAME`_USE_INPUT_FIFO           (`$UseInputFifo`u)
#define `$INSTANCE_NAME`_USE_OUTPUT_FIFO          (`$UseOutputFifo`u)
#define `$INSTANCE_NAME`_SR_SIZE                  (`$Length`u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */

typedef struct _`$INSTANCE_NAME`_backupStruct
{    
    uint8 enableState;
    
    `$RegSizeReplacementString` saveSrA0Reg;
    `$RegSizeReplacementString` saveSrA1Reg;

    #if(CY_UDB_V0) /* CY_UDB_V0 */
        `$RegSizeReplacementString` saveSrIntMask;
    #endif /* CY_UDB_V0 */

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`; 
void  `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`; 
void  `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void  `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void  `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void  `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`; 
void  `$INSTANCE_NAME`_EnableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`;
void  `$INSTANCE_NAME`_DisableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`;
void  `$INSTANCE_NAME`_SetIntMode(uint8 interruptSource) `=ReentrantKeil($INSTANCE_NAME . "_SetIntMode")`;
uint8 `$INSTANCE_NAME`_GetIntStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetIntStatus")`;
void  `$INSTANCE_NAME`_WriteRegValue(`$RegSizeReplacementString` shiftData) \
                    `=ReentrantKeil($INSTANCE_NAME . "_WriteRegValue")`;
`$RegSizeReplacementString` `$INSTANCE_NAME`_ReadRegValue(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadRegValue")`;
uint8    `$INSTANCE_NAME`_GetFIFOStatus(uint8 fifoId) `=ReentrantKeil($INSTANCE_NAME . "_GetFIFOStatus")`;

#if (`$INSTANCE_NAME`_USE_INPUT_FIFO == 1u)
    uint8 `$INSTANCE_NAME`_WriteData(`$RegSizeReplacementString` shiftData)\
                    `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`;
#endif/*(`$INSTANCE_NAME`_USE_INPUT_FIFO == 1u)*/
#if (`$INSTANCE_NAME`_USE_OUTPUT_FIFO == 1u)
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadData(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadData")`;
#endif/*(`$INSTANCE_NAME`_USE_OUTPUT_FIFO == 1u)*/


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_LOAD                     (0x01u)
#define `$INSTANCE_NAME`_STORE                    (0x02u)
#define `$INSTANCE_NAME`_RESET                    (0x04u)

#define `$INSTANCE_NAME`_IN_FIFO                  (0x01u)
#define `$INSTANCE_NAME`_OUT_FIFO                 (0x02u)

#define `$INSTANCE_NAME`_RET_FIFO_FULL            (0x00u)
#define `$INSTANCE_NAME`_RET_FIFO_NOT_EMPTY       (0x01u)
#define `$INSTANCE_NAME`_RET_FIFO_EMPTY           (0x02u)

#define `$INSTANCE_NAME`_RET_FIFO_NOT_DEFINED     (0xFEu)
#define `$INSTANCE_NAME`_RET_FIFO_BAD_PARAM       (0xFFu)

/***************************************
*    Enumerated Types and Parameters
***************************************/

`#cy_declare_enum Direction`


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_SR_MASK                  (`$SR_MASK`)
#define `$INSTANCE_NAME`_INT_SRC                  (`$InterruptSource`u)
#define `$INSTANCE_NAME`_DIRECTION                (`$Direction`u)


/***************************************
*             Registers
***************************************/

/* Shift Register control register */

#define `$INSTANCE_NAME`_SR_CONTROL_REG       (* (reg8 *) \
    `$INSTANCE_NAME`_bSR_`$ControlRegUsageReplacemetString`_CtrlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_SR_CONTROL_PTR       (  (reg8 *) \
    `$INSTANCE_NAME`_bSR_`$ControlRegUsageReplacemetString`_CtrlReg__CONTROL_REG)

/* Obsolete control reg name*/
#define `$INSTANCE_NAME`_SR_CONTROL               `$INSTANCE_NAME`_SR_CONTROL_REG

/* Shift Regisster interupt status register */

#define `$INSTANCE_NAME`_SR_STATUS_REG            (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_REG)
#define `$INSTANCE_NAME`_SR_STATUS_PTR            (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_REG)
#define `$INSTANCE_NAME`_SR_STATUS_MASK_REG       (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__MASK_REG)
#define `$INSTANCE_NAME`_SR_STATUS_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__MASK_REG)
#define `$INSTANCE_NAME`_SR_AUX_CONTROL_REG       (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_AUX_CTL_REG)
#define `$INSTANCE_NAME`_SR_AUX_CONTROL_PTR       (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_AUX_CTL_REG)

/* Obsolete names */
#define `$INSTANCE_NAME`_SR_STATUS                `$INSTANCE_NAME`_SR_STATUS_REG
#define `$INSTANCE_NAME`_SR_STATUS_MASK           `$INSTANCE_NAME`_SR_STATUS_MASK_REG
#define `$INSTANCE_NAME`_SR_AUX_CONTROL           `$INSTANCE_NAME`_SR_AUX_CONTROL_REG


#define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR      ((`$RegDefReplacementString` *) \
    `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F0_REG )
#define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR        ((`$RegDefReplacementString` *) \
    `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A0_REG )
#define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR  ((`$RegDefReplacementString` *) \
    `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A1_REG )
#define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR     ((`$RegDefReplacementString` *) \
    `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F1_REG )

/***************************************
*       Register Constants
***************************************/

#define `$INSTANCE_NAME`_INTERRUPTS_ENABLE        (0x10u)
#define `$INSTANCE_NAME`_LOAD_INT_EN              (0x01u)
#define `$INSTANCE_NAME`_STORE_INT_EN             (0x02u)
#define `$INSTANCE_NAME`_RESET_INT_EN             (0x04u)
#define `$INSTANCE_NAME`_CLK_EN                   (0x01u)

#define `$INSTANCE_NAME`_RESET_INT_EN_MASK        (0xFBu)
#define `$INSTANCE_NAME`_LOAD_INT_EN_MASK         (0xFEu)
#define `$INSTANCE_NAME`_STORE_INT_EN_MASK        (0xFDu)
#define `$INSTANCE_NAME`_INTS_EN_MASK             (0x07u)

#define `$INSTANCE_NAME`_OUT_FIFO_CLR_BIT         (0x02u)

#if (`$INSTANCE_NAME`_USE_INPUT_FIFO == 1u)

    #define `$INSTANCE_NAME`_IN_FIFO_MASK         (0x18u)

    #define `$INSTANCE_NAME`_IN_FIFO_FULL         (0x00u)
    #define `$INSTANCE_NAME`_IN_FIFO_EMPTY        (0x01u)
    #define `$INSTANCE_NAME`_IN_FIFO_NOT_EMPTY    (0x02u)
    
#endif/*(`$INSTANCE_NAME`_USE_INPUT_FIFO == 1u)*/

#define `$INSTANCE_NAME`_OUT_FIFO_MASK            (0x60u)

#define `$INSTANCE_NAME`_OUT_FIFO_EMPTY           (0x00u)
#define `$INSTANCE_NAME`_OUT_FIFO_FULL            (0x01u)
#define `$INSTANCE_NAME`_OUT_FIFO_NOT_EMPTY       (0x02u)
#define `$INSTANCE_NAME`_IN_FIFO_SHFT_MASK        (0x03u)
#define `$INSTANCE_NAME`_OUT_FIFO_SHFT_MASK       (0x05u)

#endif /* CY_SHIFTREG_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
