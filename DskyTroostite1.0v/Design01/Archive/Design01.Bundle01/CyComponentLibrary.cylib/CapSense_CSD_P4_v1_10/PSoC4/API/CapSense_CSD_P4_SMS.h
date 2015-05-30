/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the declarations of wrapper between CapSense CSD component 
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"

#define `$INSTANCE_NAME`_FRACT_DIVIDERS_ENABLED (0u)

typedef struct
{
    uint8 totalScanslotsNum;
	uint8 totalWidgetsNum;
    uint8 *idac1LevelsTbl;
    uint8 *idac2LevelsTbl;
    const uint8 *sensetivityTbl;
    uint8 *chargeDivTbl;
    uint8 *modDivTbl;
    uint8  *widgetNubmersTbl;
    uint32 *resolutionsTbl;
	uint8  *rawDataIndex;
	uint8  *numberOfSensors;
    uint16 IMOFreq_MHz;
    uint16 (*ptrGetRaw)(uint8 sensor, uint8 avgSamples);
	uint16 sensetivitySeed;
	uint8 prsEn;
}`$INSTANCE_NAME`_ConfigType;

void `$INSTANCE_NAME`_AutoTune(void);
void `$INSTANCE_NAME`_CalculateThresholds(uint8 sensor);

void `$INSTANCE_NAME`_DisableBaselineIDAC(void);
void `$INSTANCE_NAME`_EnableBaselineIDAC(`$INSTANCE_NAME`_ConfigType *config);

void `$INSTANCE_NAME`_SetAnalogSwitchesSrc_Prescaler(void);

uint16  `$INSTANCE_NAME`_GetSensorRaw(uint8 sensor, uint8 avgSamples);

void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr);

void TunePrescalers(`$INSTANCE_NAME`_ConfigType *config);
void TuneSensitivity(`$INSTANCE_NAME`_ConfigType *config);
void CalculateThresholds(const uint8 bSensorNumber, const uint16 *rawData, const uint8 widget, uint8 *bFingerThres, uint8 *bNoiseThres);
void CalibrateSensors(`$INSTANCE_NAME`_ConfigType *config, uint16 rawLevel);

#endif  /* (CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H) */

//[] END OF FILE
