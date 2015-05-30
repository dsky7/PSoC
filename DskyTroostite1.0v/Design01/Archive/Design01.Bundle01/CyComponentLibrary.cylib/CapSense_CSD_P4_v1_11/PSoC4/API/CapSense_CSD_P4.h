/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semicondu)ctor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end u)ser license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice_trm.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "`$INSTANCE_NAME`_SenseClk.h"
#include "`$INSTANCE_NAME`_SampleClk.h"


/* Interrupt handler */
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);


/***************************************
*   Condition compilation parameters
***************************************/

#define `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS       (`$ConnectInactiveSensors`u)
#define `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS       (`$IsComplexScanSlots`u)

#define `$INSTANCE_NAME`_IDAC_CNT                   (`$IDACsCount`u)
#define `$INSTANCE_NAME`_IDAC1_POLARITY             (`$CurrentSource`u)
#define `$INSTANCE_NAME`_IDAC1_RANGE_VALUE          (`$IDACRange`u)
#define `$INSTANCE_NAME`_IDAC2_RANGE_VALUE          (`$IDACRange`u)

#define `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET     (`$SensorsFreqSettingsInd`u)

#define `$INSTANCE_NAME`_PRS_OPTIONS                (`$PrsOptions`u)

#define `$INSTANCE_NAME`_WATER_PROOF                (`$WaterProofingEnabled`u)

#define `$INSTANCE_NAME`_TUNING_METHOD              (`$TuningMethod`u)
#define `$INSTANCE_NAME`_TUNER_API_GENERATE         (`$EnableTuneHelper`u)


#define `$INSTANCE_NAME`_CMOD_PREGARGE_OPTION       (`$CmodPrecharge`u)
#define `$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION   (`$Csh_tankPrecharge`u)
#define `$INSTANCE_NAME`_IS_SHIELD_ENABLE           (`$ShieldEnable`u)
#define `$INSTANCE_NAME`_CSH_TANK_ENABLE            (`$ShieldTankEnable`u)

#define `$INSTANCE_NAME`_SHIELD_DELAY               (`$ShieldDelay`u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
`#cy_declare_enum IDACOptions`
`#cy_declare_enum IDACRangeOptions`
`#cy_declare_enum PrsOptions`
/* Connection of inactive sensors definitions */
`#cy_declare_enum CISOptions`

/* Precharge options definitions */
`#cy_declare_enum CapacitorPrechargeOptions`
/* Method of tunning */
`#cy_declare_enum TuningMethodOptions`

#define `$INSTANCE_NAME`_TUNING_NONE 0
#define `$INSTANCE_NAME`_MANUAL_TUNING 1
#define `$INSTANCE_NAME`_AUTO_TUNING 2

/* Defitition of the time interval that enough for charging 100nF capacitor */
#define `$INSTANCE_NAME`_MAX_CHARGE_TIME_US				(100u)
#define `$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP			(5u)
#define `$INSTANCE_NAME`_PRECHARGE_WATCHDOG_CYCLES_NUM	(((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_MAX_CHARGE_TIME_US)) /\
														 (`$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP)) 

/* Scan type definitions */
#define `$INSTANCE_NAME`_SELF_CAPACITANCE           (0u)
#define `$INSTANCE_NAME`_MUTUAL_CAPACITANCE         (1u)

#define `$INSTANCE_NAME`_CSD_SENSE_PORT_MODE        (4u)
#define `$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE       (5u)
#define `$INSTANCE_NAME`_CSD_PIN_MODE_MASK          (0x00000007u)
#define `$INSTANCE_NAME`_CSD_HSIOM_MASK             (0x0000000Fu)
#define `$INSTANCE_NAME`_CSD_PIN_DRIVE_MASK         (0x00000001u)

#define `$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK   (0x00000F00)
#define `$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK  (0x0000F000)

#define `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A      (0x00000600)
#define `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_B      (0x00000700)

#define `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_A     (0x00006000)
#define `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_B     (0x00007000)

#define  `$INSTANCE_NAME`_CSD_CMOD_PC_MASK          (0x000001C0u)
#define  `$INSTANCE_NAME`_CSD_CTANK_PC_MASK         (0x00000E00u)

#define  `$INSTANCE_NAME`_CMOD_PC_STRONG_MODE       (0x00000180u)
#define  `$INSTANCE_NAME`_CMOD_PC_HIGH_Z_MODE       (0x00000000u)

#define  `$INSTANCE_NAME`_CTANK_PC_STRONG_MODE      (0x00000C00u)
#define  `$INSTANCE_NAME`_CTANK_PC_HIGH_Z_MODE      (0x00000000u)

#define  `$INSTANCE_NAME`_CMOD_DR_VSSIO 			(0x04u)
#define  `$INSTANCE_NAME`_CMOD_DR_VDDIO				(0x00u)
#define  `$INSTANCE_NAME`_CMOD_DR_MASK				(0x04u)

#define  `$INSTANCE_NAME`_CTANK_DR_VSSIO 			(0x08u)
#define  `$INSTANCE_NAME`_CTANK_DR_VDDIO			(0x00u)
#define  `$INSTANCE_NAME`_CTANK_DR_MASK 			(0x08u)

/* Structure to save registers before go to sleep */
typedef struct _`$INSTANCE_NAME`_BACKUP_STRUCT
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Wakeup(void);
uint8 `$INSTANCE_NAME`_IsBusy(void);
void `$INSTANCE_NAME`_ScanSensor(uint8 sensor);
void `$INSTANCE_NAME`_ScanEnabledWidgets(void);
__INLINE void `$INSTANCE_NAME`_SetScanSlotSettings(uint8 slot);
uint16 `$INSTANCE_NAME`_ReadSensorRaw(uint8 sensor);
void `$INSTANCE_NAME`_ClearSensors(void);
__INLINE void `$INSTANCE_NAME`_EnableSensor(uint8 sensor);
__INLINE void `$INSTANCE_NAME`_DisableSensor(uint8 sensor);

void `$INSTANCE_NAME`_SetShieldDelay(uint32 delay);

uint32 `$INSTANCE_NAME`_GetResolutionIndex(uint32 widgetResolution);
void `$INSTANCE_NAME`_Calc_PRS_Resolution(void);

/* Interrupt handler */
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);


/***************************************
*           API Constants
***************************************/

`$DefineConstants`


/* PWM Resolution */
#define `$INSTANCE_NAME`_WINDOW_APPEND          (0xFFFE0000u)
#define `$INSTANCE_NAME`_RESOLUTION_8_BITS      (0x00FF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_9_BITS      (0x01FF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_10_BITS     (0x03FF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_11_BITS     (0x07FF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_12_BITS     (0x0FFF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_13_BITS     (0x1FFF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_14_BITS     (0x3FFF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_15_BITS     (0x7FFF0000u)
#define `$INSTANCE_NAME`_RESOLUTION_16_BITS     (0xFFFF0000u)

#define `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET  (24u)

/* Software Status Register Bit Masks */
#define `$INSTANCE_NAME`_SW_STS_BUSY                (0x01u)
/* Software Status Register Bit Masks */
#define `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN        (0x80u)
/* Flag of complex scan slot */
#define `$INSTANCE_NAME`_COMPLEX_SS_FLAG            (0x80u)


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_CSD_ID_REG             (*(reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_ID)
#define `$INSTANCE_NAME`_CSD_ID_PTR             ( (reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_ID)

#define `$INSTANCE_NAME`_CSD_CFG_REG            (*(reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_CONFIG)
#define `$INSTANCE_NAME`_CSD_CFG_PTR            ( (reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_CONFIG)

#define `$INSTANCE_NAME`_CSD_IDAC_REG           (*(reg32 *)  CYREG_CSD_IDAC)
#define `$INSTANCE_NAME`_CSD_IDAC_PTR           ( (reg32 *)  CYREG_CSD_IDAC)

#define `$INSTANCE_NAME`_CSD_CNT_REG            (*(reg32 *) CYREG_CSD_COUNTER)
#define `$INSTANCE_NAME`_CSD_CNT_PTR            ( (reg32 *) CYREG_CSD_COUNTER)

#define `$INSTANCE_NAME`_CSD_STAT_REG           (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_STATUS)
#define `$INSTANCE_NAME`_CSD_STAT_PTR           ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_STATUS)

#define `$INSTANCE_NAME`_CSD_INTR_REG           (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR)
#define `$INSTANCE_NAME`_CSD_INTR_PTR           ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR)

#define `$INSTANCE_NAME`_CSD_INTR_SET_REG       (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR_SET)
#define `$INSTANCE_NAME`_CSD_INTR_SET_PTR       ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR_SET)

#define `$INSTANCE_NAME`_CSD_TRIM1_REG          (*(reg32 *) CYREG_CSD_TRIM1)
#define `$INSTANCE_NAME`_CSD_TRIM1_PTR          ( (reg32 *) CYREG_CSD_TRIM1)

#define `$INSTANCE_NAME`_CSD_TRIM2_REG          (*(reg32 *) CYREG_CSD_TRIM2)
#define `$INSTANCE_NAME`_CSD_TRIM2_PTR          ( (reg32 *) CYREG_CSD_TRIM2)

#define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
#define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

#define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)

/* Port function select */
#define `$INSTANCE_NAME`_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define `$INSTANCE_NAME`_PORT_SEL0_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define `$INSTANCE_NAME`_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define `$INSTANCE_NAME`_PORT_SEL1_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define `$INSTANCE_NAME`_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define `$INSTANCE_NAME`_PORT_SEL2_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define `$INSTANCE_NAME`_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define `$INSTANCE_NAME`_PORT_SEL3_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define `$INSTANCE_NAME`_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define `$INSTANCE_NAME`_PORT_SEL4_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL4 )

/* Port DR and PC registers */
#define `$INSTANCE_NAME`_PORT0_DR_REG           (*(reg32 *) CYREG_PRT0_DR )
#define `$INSTANCE_NAME`_PORT0_DR_PTR           ( (reg32 *) CYREG_PRT0_DR )

#define `$INSTANCE_NAME`_PORT1_DR_REG           (*(reg32 *) CYREG_PRT1_DR )
#define `$INSTANCE_NAME`_PORT1_DR_PTR           ( (reg32 *) CYREG_PRT1_DR )

#define `$INSTANCE_NAME`_PORT2_DR_REG           (*(reg32 *) CYREG_PRT2_DR )
#define `$INSTANCE_NAME`_PORT2_DR_PTR           ( (reg32 *) CYREG_PRT2_DR )

#define `$INSTANCE_NAME`_PORT3_DR_REG           (*(reg32 *) CYREG_PRT3_DR )
#define `$INSTANCE_NAME`_PORT3_DR_PTR           ( (reg32 *) CYREG_PRT3_DR )

#define `$INSTANCE_NAME`_PORT4_DR_REG           (*(reg32 *) CYREG_PRT4_DR )
#define `$INSTANCE_NAME`_PORT4_DR_PTR           ( (reg32 *) CYREG_PRT4_DR )


/* Port DR and PC registers */
#define `$INSTANCE_NAME`_PORT0_PC_REG           (*(reg32 *) CYREG_PRT0_PC )
#define `$INSTANCE_NAME`_PORT0_PC_PTR           ( (reg32 *) CYREG_PRT0_PC )

#define `$INSTANCE_NAME`_PORT1_PC_REG           (*(reg32 *) CYREG_PRT1_PC )
#define `$INSTANCE_NAME`_PORT1_PC_PTR           ( (reg32 *) CYREG_PRT1_PC )

#define `$INSTANCE_NAME`_PORT2_PC_REG           (*(reg32 *) CYREG_PRT2_PC )
#define `$INSTANCE_NAME`_PORT2_PC_PTR           ( (reg32 *) CYREG_PRT2_PC )

#define `$INSTANCE_NAME`_PORT3_PC_REG           (*(reg32 *) CYREG_PRT3_PC )
#define `$INSTANCE_NAME`_PORT3_PC_PTR           ( (reg32 *) CYREG_PRT3_PC )

#define `$INSTANCE_NAME`_PORT4_PC_REG           (*(reg32 *) CYREG_PRT4_PC )
#define `$INSTANCE_NAME`_PORT4_PC_PTR           ( (reg32 *) CYREG_PRT4_PC )


/* ISR Number and Priority to work with CyLib functions */
#define `$INSTANCE_NAME`_ISR_NUMBER        (`$INSTANCE_NAME`_ISR__INTC_NUMBER)
#define `$INSTANCE_NAME`_ISR_PRIORITY      (`$INSTANCE_NAME`_ISR__INTC_PRIOR_NUM)


/***************************************
*       Register Constants
***************************************/

/* ID register fields position */
#define `$INSTANCE_NAME`_CSD_ID_ID__POS              (0x00u)
#define `$INSTANCE_NAME`_CSD_ID_REV__POS             (0x10u)

#define `$INSTANCE_NAME`_CSD_ID_ID                   (0xFFLu << `$INSTANCE_NAME`_CSD_ID_ID__POS)
#define `$INSTANCE_NAME`_CSD_ID_REV                  (0xFFLu << `$INSTANCE_NAME`_CSD_ID_REV__POS)


/* CONFIG register fields position */
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN__POS  (0x00u)
#define `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC__POS    (0x01u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR__POS      (0x05u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT__POS     (0x06u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_12_8__POS       (0x07u)
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN__POS   (0x08u)
#define `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY__POS   (0x09u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW__POS  (0x0Bu)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_EN__POS       (0x0Cu)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN__POS      (0x0Du)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_MODE__POS      (0x0Eu)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_PIN__POS       (0x0Fu)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY__POS       (0x10u)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY2__POS      (0x11u)
#define `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP__POS     (0x12u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN__POS  (0x13u)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_BOOST__POS   (0x14u)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL__POS  (0x15u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL__POS    (0x16u)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTSEL__POS        (0x1Au)
#define `$INSTANCE_NAME`_CSD_CFG_ADFTEN__POS         (0x1Du)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP__POS       (0x1Eu)
#define `$INSTANCE_NAME`_CSD_CFG_ENABLE__POS         (0x1Fu)

#define `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN       (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC         (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC__POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR__POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT__POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_12_8            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_12_8__POS)
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN        (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY        (0x03Lu << `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW       (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_EN            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_EN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_MODE           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_COMP_MODE__POS)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_PIN            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_COMP_PIN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_POLARITY__POS)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY2           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_POLARITY2__POS)
#define `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN       (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_BOOST        (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_REFBUF_BOOST__POS)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL       (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL__POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL         (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL__POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTSEL             (0x07Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTSEL__POS)
#define `$INSTANCE_NAME`_CSD_CFG_ADFTEN              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_ADFTEN__POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP__POS)
#define `$INSTANCE_NAME`_CSD_CFG_ENABLE              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_ENABLE__POS)

/* STATUS register fields position */
#define `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE__POS    (0x00Lu)
#define `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE__POS     (0x01Lu)
#define `$INSTANCE_NAME`_CSD_STAT_COMP_OUT__POS      (0x02Lu)
#define `$INSTANCE_NAME`_CSD_STAT_SAMPLE__POS        (0x03Lu)

#define `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE         (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE__POS)
#define `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE          (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE__POS)
#define `$INSTANCE_NAME`_CSD_STAT_COMP_OUT           (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_COMP_OUT__POS)
#define `$INSTANCE_NAME`_CSD_STAT_SAMPLE             (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_SAMPLE__POS)

/* Init Idac current */
#define `$INSTANCE_NAME`_TURN_OFF_IDAC               (0x00u)
#define `$INSTANCE_NAME`_PRECHARGE_IDAC1_VAL		 (0xFAu)

/* CSD config constants */
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK          (0x00000300u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_OFF           (0x00000000u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED         (0x00000100u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE      (0x00000200u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_DSI           (0x00000300u)
#define `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X           (0x00000400u)
#define `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK          (0x000000FFu)

#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK          (0x03000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_OFF           (0x00000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_ON            (0x00000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED         (0x01000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE      (0x02000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_DSI           (0x03000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X           (0x04000000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK          (0x007F0000u)
#define `$INSTANCE_NAME`_CSD_IDAC2_DATA_OFFSET        (16u)

#define `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK          (0xFFFFFFF0u)
#define `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK          (0xFFFFFF0Fu)

#define `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK      (0x0F)
#define `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK      (0xF0)

#define `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG	  (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED |\
													   `$INSTANCE_NAME`_PRECHARGE_IDAC1_VAL)	

#define `$INSTANCE_NAME`_CSD_PRS_SELECT_DIV2          (0x00000000u)  
#define `$INSTANCE_NAME`_CSD_PRS_SELECT_PRS           (`$INSTANCE_NAME`_CSD_CFG_PRS_SELECT)  

#define `$INSTANCE_NAME`_CSD_PRS_8_BIT                (0x00000000u)
#define `$INSTANCE_NAME`_CSD_PRS_12_BIT               (`$INSTANCE_NAME`_CSD_CFG_PRS_12_8)

#define `$INSTANCE_NAME`_CSD_SENSE_COMP_BW_LOW        (0x00000000u)
#define `$INSTANCE_NAME`_CSD_SENSE_COMP_BW_HIGH       (`$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW)

#define  `$INSTANCE_NAME`_CSD_REFBUF_ENABLE           (`$INSTANCE_NAME`_CSD_CFG_REFBUF_EN)
#define  `$INSTANCE_NAME`_CSD_REFBUF_DISABLE          (0x00000000u)

#define  `$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXA         (0x00000000u)
#define  `$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXB         (`$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL)

#define `$INSTANCE_NAME`_CSD_COMP_MODE_CARGE_BUF      (0x00000000u)
#define `$INSTANCE_NAME`_CSD_COMP_MODE_CHARGE_IO      (`$INSTANCE_NAME`_CSD_CFG_COMP_MODE)

#define `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL1        (0x00000000u)  
#define `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL2        (`$INSTANCE_NAME`_CSD_CFG_COMP_PIN)  

#define `$INSTANCE_NAME`_CSD_POLARITY_VSSIO           (0x00000000u)
#define `$INSTANCE_NAME`_CSD_POLARITY_VDDIO           (`$INSTANCE_NAME`_CSD_CFG_POLARITY)

#define `$INSTANCE_NAME`_CSD_POLARITY2_VSSIO          (0x00000000u)
#define `$INSTANCE_NAME`_CSD_POLARITY2_VDDIO          (`$INSTANCE_NAME`_CSD_CFG_POLARITY2)

#define `$INSTANCE_NAME`_CSD_SENSE_CHANNEL1           (0x00000000u)
#define `$INSTANCE_NAME`_CSD_SENSE_AMUXA              (`$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL)

#define `$INSTANCE_NAME`_CSD_REFBUF_OFF               (0x00000000u)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_1             (0x00800000u)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_2             (0x01000000u)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_3             (0x01800000u)

/* COUNTER register fields position */
#define `$INSTANCE_NAME`_CSD_CNT_COUNTER__POS        (0x00u)
#define `$INSTANCE_NAME`_CSD_CNT_PERIOD__POS         (0x10u)

#define `$INSTANCE_NAME`_CSD_CNT_COUNTER             (0xFFLu << `$INSTANCE_NAME`_CSD_CNT_COUNTER__POS )
#define `$INSTANCE_NAME`_CSD_CNT_PERIOD              (0xFFLu << `$INSTANCE_NAME`_CSD_CNT_PERIOD__POS)


/* Set PRS */
#if (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_8BITS)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT

#elif (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_12BITS)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE	`$INSTANCE_NAME`_CSD_CFG_PRS_12_8 |\
														`$INSTANCE_NAME`_CSD_CFG_PRS_SELECT
#else
	#define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE	(0u)
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`_PRS_8BITS) */

/* Set IDAC ranges */
#if (`$INSTANCE_NAME`_IDAC1_RANGE_VALUE == `$INSTANCE_NAME`__IDAC_8X)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE    `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X
    #define `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE    `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X
#else
    #define `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE    (0u)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE    (0u)
#endif /* (`$INSTANCE_NAME`_IDAC1_RANGE_VALUE == `$INSTANCE_NAME`_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY	`$INSTANCE_NAME`_CSD_POLARITY_VDDIO
	#define `$INSTANCE_NAME`_CMOD_DR_CONFIG			 `$INSTANCE_NAME`_CMOD_DR_VDDIO	
	#define `$INSTANCE_NAME`_CTANK_DR_CONFIG	     `$INSTANCE_NAME`_CTANK_DR_VDDIO
#else

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY	 (0u)
	#define `$INSTANCE_NAME`_CMOD_DR_CONFIG			 `$INSTANCE_NAME`_CMOD_DR_VSSIO	
	#define `$INSTANCE_NAME`_CTANK_DR_CONFIG	     `$INSTANCE_NAME`_CTANK_DR_VSSIO 
#endif /* (`$INSTANCE_NAME`_IDAC_OPTIONS == `$INSTANCE_NAME`_IDAC_SINK) */

/* Inactive sensors connection configuration */
#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__GROUND)
    #define `$INSTANCE_NAME`_CSD_INACTIVE_CONNECT       (6u)
#else
    #define `$INSTANCE_NAME`_CSD_INACTIVE_CONNECT       (0u)
#endif /* `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__GROUND */


/* Defining the default CSD configuration according to settingd in customizer. */
#define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG             (`$INSTANCE_NAME`_DEFAULT_MODULATION_MODE |\
                                                         `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW |\
                                                         `$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                         `$INSTANCE_NAME`_CSD_REFBUF_DRV_3)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (`$INSTANCE_NAME`_IDAC_CNT == 1u)
#define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG        (`$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE |\
                                                         `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE)
#else
#define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG        (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED |\
                                                         `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE |\
                                                         `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE |\
                                                         `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE)
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 1u) */


/* Defining mask that intended to clearing bits that related to precharging options. */
#define `$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK			(`$INSTANCE_NAME`_CSD_CFG_COMP_MODE |\
														 `$INSTANCE_NAME`_CSD_CFG_COMP_PIN  |\
														 `$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
														 `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL)

/* Cmod precharge mode configuration */
#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)

	#define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG 		(`$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
														 `$INSTANCE_NAME`_CSD_COMP_MODE_CARGE_BUF |\
														 `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL2 |\
														 `$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXA)
														 
#else

	#define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG 		(`$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXB |\
														 `$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
														 `$INSTANCE_NAME`_CSD_COMP_MODE_CHARGE_IO |\
														 `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL1)
														 
#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF) */


/* Ctank precharge mode configuration */
#if(`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)
	
	#if(0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE)
		#define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG	(`$INSTANCE_NAME`_CSD_COMP_MODE_CARGE_BUF |\
															 `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL1 |\
															 `$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
															 `$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXB)
	#else
		#define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG	(`$INSTANCE_NAME`_CSD_COMP_MODE_CARGE_BUF |\
															 `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL1 |\
															 `$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXB)
	#endif /* (0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE) */													 
#else

	#define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG	(`$INSTANCE_NAME`_CSD_REFBUF_TO_AMUXB |\
														 `$INSTANCE_NAME`_CSD_REFBUF_ENABLE |\
														 `$INSTANCE_NAME`_CSD_COMP_MODE_CHARGE_IO |\
														 `$INSTANCE_NAME`_CSD_COMP_PIN_CHANNEL2)
#endif /* (`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

						
#endif /* CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  `$INSTANCE_NAME`_PrescalersTuningDone         `$INSTANCE_NAME`_prescalersTuningDone
#define  `$INSTANCE_NAME`_SensorRaw	                   `$INSTANCE_NAME`_sensorRaw
#define  `$INSTANCE_NAME`_PRSResolutionTbl             `$INSTANCE_NAME`_prsResolutionTbl
#define  `$INSTANCE_NAME`_SensorEnableMask             `$INSTANCE_NAME`_sensorEnableMask
#define  `$INSTANCE_NAME`_Clk1DividerVal               `$INSTANCE_NAME`_senseClkDividerVal
#define  `$INSTANCE_NAME`_Clk2DividerVal               `$INSTANCE_NAME`_sampleClkDividerVal
#define  `$INSTANCE_NAME`_PrtSelTbl                    `$INSTANCE_NAME`_prtSelTbl
#define  `$INSTANCE_NAME`_PrtCfgTbl                    `$INSTANCE_NAME`_prtCfgTbl
#define  `$INSTANCE_NAME`_PrtDRTbl                     `$INSTANCE_NAME`_prtDRTbl


 /* [] END OF FILE */
