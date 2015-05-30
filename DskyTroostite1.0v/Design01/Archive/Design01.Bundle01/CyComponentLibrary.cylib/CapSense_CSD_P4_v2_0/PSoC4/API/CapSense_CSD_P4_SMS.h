/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the declarations of the wrapper between the CapSense CSD component 
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
	#include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

#define `$INSTANCE_NAME`_CALIBRATION_RESOLUTION	(0x0FFF0000u)

#define `$INSTANCE_NAME`_THRESHOLD_1                (220u)
#define `$INSTANCE_NAME`_THRESHOLD_2                (237u)
#define `$INSTANCE_NAME`_THRESHOLD_3                (245u)
#define `$INSTANCE_NAME`_THRESHOLD_4                (250u)

#define `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ		(3000u)
#define `$INSTANCE_NAME`_CALIBRATION_MD  		    (`$ModulatorDiv`u)

#if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
	#define `$INSTANCE_NAME`_CALIBRATION_ASD		(CYDEV_BCLK__HFCLK__KHZ /\
													 `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ)
#else
	#define `$INSTANCE_NAME`_MIN_IMO_FREQ_KHZ		(6000u)
	#if(CYDEV_BCLK__HFCLK__KHZ < `$INSTANCE_NAME`_MIN_IMO_FREQ_KHZ)
		#define `$INSTANCE_NAME`_CALIBRATION_ASD			(1u)
	#else
		#define `$INSTANCE_NAME`_CALIBRATION_ASD	(CYDEV_BCLK__HFCLK__KHZ / `$INSTANCE_NAME`_CALIBRATION_MD /\
												 	 `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ)
	#endif /* (CYDEV_BCLK__HFCLK__KHZ < `$INSTANCE_NAME`_MIN_IMO_FREQ_KHZ) */
#endif /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

#define `$INSTANCE_NAME`_SENSITIVITY_MASK        	(0x0Fu)
#define `$INSTANCE_NAME`_FLEXIBLE_THRESHOLDS_EN  	(`$ThresholdMode`u)
#define `$INSTANCE_NAME`_CAL_RAW_COUNT           	(3482u)

void `$INSTANCE_NAME`_AutoTune(void);
void `$INSTANCE_NAME`_UpdateThresholds(uint32 sensor);
void `$INSTANCE_NAME`_SetSensitivity(uint32 sensor, uint32 value);
void `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect(void);
uint16 `$INSTANCE_NAME`_GetNoiseEnvelope(uint32 sensor);
void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr);
uint8 `$INSTANCE_NAME`_GetSensitivityCoefficient(uint32 sensor);
uint16 `$INSTANCE_NAME`_GetNormalizedDiffCountData(uint32 sensor);


/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define baNoiseEnvelope			noiseEnvelopeTbl
#define baRunningDifference		runningDifferenceTbl
#define baSignRegister			signRegisterTbl
#define waSampleMin				sampleMinTbl
#define waSampleMax				sampleMaxTbl
#define waPreviousSample		previousSampleTbl
#define baK						kValueTbl   			
#define baSpeed					scanSpeedTbl			


#endif  /* (CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
