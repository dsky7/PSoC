/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component 
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
#include "`$INSTANCE_NAME`_SMS.h"
#include "`$INSTANCE_NAME`_CSHL.h"

#include "cytypes.h"

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)

/* Declaration the sensetivity seed */
#if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
	#if(CYDEV_VDDA_MV == 5000u)
		#define `$INSTANCE_NAME`_SENSETIVITY_SEED (4801u)
	#else
		#define `$INSTANCE_NAME`_SENSETIVITY_SEED (2653u)
	#endif/* (CYDEV_VDDA_MV == 5000u) */
#else
	#define `$INSTANCE_NAME`_SENSETIVITY_SEED (1156u)
#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
	extern uint8 `$INSTANCE_NAME`_prescalersTuningDone;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

#define `$INSTANCE_NAME`_CAL_RAW_COUNT           (1024u)
#define `$INSTANCE_NAME`_CAL_RAW_COUNT_SPLIT     (1740u)

#if(CYDEV_BCLK__HFCLK__MHZ > 12u)
	#define `$INSTANCE_NAME`_IDAC2_MAX      (127u)
#elif(CYDEV_BCLK__HFCLK__MHZ > 6u)
	#define `$INSTANCE_NAME`_IDAC2_MAX      (63u)
#else
	#define `$INSTANCE_NAME`_IDAC2_MAX      (31u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

static `$INSTANCE_NAME`_ConfigType `$INSTANCE_NAME`_config;

extern uint16 `$INSTANCE_NAME`_sensorRaw[];

extern uint32 `$INSTANCE_NAME`_widgetResolution[];
extern uint8 `$INSTANCE_NAME`_widgetNumber[];
extern uint8 `$INSTANCE_NAME`_rawDataIndex[];
extern uint8 `$INSTANCE_NAME`_numberOfSensors[];
extern uint32 `$INSTANCE_NAME`_prsResolutionTbl[];

extern uint8 `$INSTANCE_NAME`_idac1Settings[];
extern uint8 `$INSTANCE_NAME`_idac2Settings[];

extern uint8 `$INSTANCE_NAME`_senseClkDividerVal[];
extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal[];

extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[];
extern `$SizeReplacementString` `$INSTANCE_NAME`_noiseThreshold[];
extern `$SizeReplacementString` `$INSTANCE_NAME`_hysteresis[];

uint8 baNoiseEnvelope[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT]; 
uint8 baRunningDifference[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint8 baSignRegister[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMin[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMax[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint16 waPreviousSample[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint8 baK[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];              
uint8 baNoiseResetCounter[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
uint8 waSnsResult[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];

`$writerCAutoSensitivity`

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AutoTune
********************************************************************************
*
* Summary:
*  Provides tunning procedure for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_AutoTune(void)
{
	uint8 curSensor;
    uint8 widget;
    
    `$INSTANCE_NAME`_config.totalScanslotsNum = `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT;
	`$INSTANCE_NAME`_config.totalWidgetsNum = `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX;
    `$INSTANCE_NAME`_config.idac1LevelsTbl = `$INSTANCE_NAME`_idac1Settings;
    `$INSTANCE_NAME`_config.idac2LevelsTbl = `$INSTANCE_NAME`_idac2Settings;
    `$INSTANCE_NAME`_config.sensetivityTbl = `$INSTANCE_NAME`_sensorSensitivity;
    `$INSTANCE_NAME`_config.chargeDivTbl = `$INSTANCE_NAME`_senseClkDividerVal;
    `$INSTANCE_NAME`_config.modDivTbl = `$INSTANCE_NAME`_sampleClkDividerVal;
    `$INSTANCE_NAME`_config.widgetNubmersTbl = `$INSTANCE_NAME`_widgetNumber;
    `$INSTANCE_NAME`_config.resolutionsTbl = `$INSTANCE_NAME`_widgetResolution;
	`$INSTANCE_NAME`_config.rawDataIndex = `$INSTANCE_NAME`_rawDataIndex;
	`$INSTANCE_NAME`_config.numberOfSensors = `$INSTANCE_NAME`_numberOfSensors; 
    `$INSTANCE_NAME`_config.ptrGetRaw = `$INSTANCE_NAME`_GetSensorRaw;
	`$INSTANCE_NAME`_config.IMOFreq_MHz = CYDEV_BCLK__HFCLK__MHZ;
	`$INSTANCE_NAME`_config.sensetivitySeed = `$INSTANCE_NAME`_SENSETIVITY_SEED;
	
	#if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE)	
		`$INSTANCE_NAME`_config.prsEn = 0u;
	#else
		`$INSTANCE_NAME`_config.prsEn = 1u;
	#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */
	
	`$INSTANCE_NAME`_SetAnalogSwitchesSrc_Prescaler();
    
    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        
        widget = `$INSTANCE_NAME`_widgetNumber[curSensor];
        `$INSTANCE_NAME`_widgetResolution[widget] = `$INSTANCE_NAME`_RESOLUTION_11_BITS;
    }
    
    `$INSTANCE_NAME`_DisableBaselineIDAC();
	
    CalibrateSensors_v1_11(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT);
	
    TunePrescalers_v1_11(&`$INSTANCE_NAME`_config);
	
	#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
		`$INSTANCE_NAME`_prescalersTuningDone = 1u;
	#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */
	
	`$INSTANCE_NAME`_NormalizeWidgets(`$INSTANCE_NAME`_END_OF_WIDGETS_INDEX, `$INSTANCE_NAME`_senseClkDividerVal);
	
    #if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO)
        `$INSTANCE_NAME`_Calc_PRS_Resolution();
    #endif/* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO) */
    
	`$INSTANCE_NAME`_EnableBaselineIDAC(&`$INSTANCE_NAME`_config);
    
    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        widget = `$INSTANCE_NAME`_widgetNumber[curSensor];
        
		#if(`$INSTANCE_NAME`_FRACT_DIVIDERS_ENABLED == 1u)
			`$INSTANCE_NAME`_widgetResolution[widget] = 0x09D80000;
		#else
			`$INSTANCE_NAME`_widgetResolution[widget] = `$INSTANCE_NAME`_RESOLUTION_11_BITS;
		#endif /* (`$INSTANCE_NAME`_FRACT_DIVIDERS_ENABLED == 1u) */
    }
    
    CalibrateSensors_v1_11(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_CAL_RAW_COUNT_SPLIT);
    
    TuneSensitivity_v1_11(&`$INSTANCE_NAME`_config);
    
    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        `$INSTANCE_NAME`_CalculateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalculateThresholds
********************************************************************************
*
* Summary:
*  Computes the noise and finger thresholds based on the high frequency noise
*  found in Noise_Calc and the amplitude of the signal from a recent finger
*  press.
*
* Parameters:
*  sensor: Sensor number.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_CalculateThresholds(uint8 sensor)
{
	uint32 fingerThleshold;
	uint8 widget;
	
	widget = `$INSTANCE_NAME`_widgetNumber[sensor];
	
    CalculateThresholds_v1_11(sensor, `$INSTANCE_NAME`_sensorRaw, widget, 
                        `$INSTANCE_NAME`_fingerThreshold, `$INSTANCE_NAME`_noiseThreshold);
	
	fingerThleshold = `$INSTANCE_NAME`_fingerThreshold[widget];
	
	if(fingerThleshold < 220u)
	{
		`$INSTANCE_NAME`_hysteresis[widget] = fingerThleshold >> 3u;
	}
	else if(fingerThleshold <  237u)
	{
		`$INSTANCE_NAME`_hysteresis[widget] = fingerThleshold >> 4u;
	}
	else if(fingerThleshold <  245u)
	{
		`$INSTANCE_NAME`_hysteresis[widget] = fingerThleshold >> 5u;
	}
	else if(fingerThleshold <  250)
	{
		`$INSTANCE_NAME`_hysteresis[widget] = fingerThleshold >> 6u;
	}
	else
	{
		`$INSTANCE_NAME`_hysteresis[widget] = 0u;
	}                 
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableBaselineIDAC
********************************************************************************
*
* Summary:
*  Intended to disabling the baselining IDAC. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableBaselineIDAC(void)
{
	`$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK);
    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
    
	`$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE;
    `$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_CSD_IDAC2_MODE_OFF;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAnalogSwitchesSrc_PRS
********************************************************************************
*
* Summary:
*  Intended to enabling the baselining IDAC. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void  `$INSTANCE_NAME`_EnableBaselineIDAC(`$INSTANCE_NAME`_ConfigType *config)
{
    uint8 curSensor;
    
    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        config->idac2LevelsTbl[curSensor] = `$INSTANCE_NAME`_IDAC2_MAX;
    }
    
	`$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK);
    `$INSTANCE_NAME`_CSD_IDAC_REG &= ~(`$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK);
    
	`$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED;
    `$INSTANCE_NAME`_CSD_IDAC_REG |= `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorRaw
********************************************************************************
*
* Summary:
*  Intended to updatind and riding uprated raw data from sensor.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
*******************************************************************************/
uint16  `$INSTANCE_NAME`_GetSensorRaw(uint8 sensor, uint8 avgSamples)
{
	uint8 curSample;
	uint32 avgVal = 0u;
	
	for(curSample = 0u; curSample < avgSamples; curSample++)
	{
    
		`$INSTANCE_NAME`_ScanSensor(sensor);
	    while(`$INSTANCE_NAME`_IsBusy());
		avgVal += `$INSTANCE_NAME`_ReadSensorRaw(sensor);
	}
    
    return(avgVal / avgSamples);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NormalizeWidgets
********************************************************************************
*
* Summary:
*  Intended to align all parameters of widget to maximum paramrter.
*
* Parameters:
*  widgetsNum - Number of widgets.
*  datsPrt - pointer ro array with widget parameters.	
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr)
{
	uint32 currentWidget;
	uint32 currentSensor = 0u;
	uint32 lastSensor = 0u;
	uint32 sensorsPerWidget;
	uint32 maxPerWidget;
	
	
	for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
	{
		maxPerWidget = 0u;
		
		sensorsPerWidget = `$INSTANCE_NAME`_numberOfSensors[currentWidget];
		currentSensor = `$INSTANCE_NAME`_rawDataIndex[currentWidget];
		lastSensor = currentSensor + sensorsPerWidget;
		
		while(currentSensor < lastSensor)
		{
			if(maxPerWidget < dataPtr[currentSensor])
			{
				maxPerWidget = dataPtr[currentSensor];
			}
			currentSensor++;
		}
		
		currentSensor = `$INSTANCE_NAME`_rawDataIndex[currentWidget];
		
		while(currentSensor < lastSensor)
		{
			dataPtr[currentSensor] = maxPerWidget;
			currentSensor++;
		}
	}
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAnalogSwitchesSrc_Prescaler
********************************************************************************
*
* Summary:
*  Intedned to switching charge clock source to prescaler. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAnalogSwitchesSrc_Prescaler(void)
{
	`$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_PRS_SELECT);
}

#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */

/* [] END OF FILE */
