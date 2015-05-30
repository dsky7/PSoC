/*******************************************************************************
* File Name: `$INSTANCE_NAME`_CSHL.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the High Level APIs for the CapSesne
*  CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_CSHL.h"
#include "`$INSTANCE_NAME`_PVT.h"

/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    extern void `$INSTANCE_NAME`_UpdateThresholds(uint32 sensor);
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

/* Median filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)))
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* Averaging filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
    uint16 `$INSTANCE_NAME`_AveragingFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) )
    uint16 `$INSTANCE_NAME`_IIR2Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) )
    uint16 `$INSTANCE_NAME`_IIR4Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER))
    uint16 `$INSTANCE_NAME`_IIR8Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER))
    uint16 `$INSTANCE_NAME`_IIR16Filter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) )
    uint16 `$INSTANCE_NAME`_JitterFilter(uint16 x1, uint16 x2);
#endif /* `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* Storage of filters data */
#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) )

    uint16 `$INSTANCE_NAME`_rawFilterData1[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    uint16 `$INSTANCE_NAME`_rawFilterData2[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#elif ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER))   || \
        (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER))   || \
        (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
        (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER))   || \
        (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER)) )
        
    uint16 `$INSTANCE_NAME`_rawFilterData1[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
#endif  /* ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
        *    (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) )
        */

extern uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8 `$INSTANCE_NAME`_sensorEnableMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];
extern const uint8 `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
	extern uint32 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];	
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */

uint16 `$INSTANCE_NAME`_sensorBaseline[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
uint8 `$INSTANCE_NAME`_sensorBaselineLow[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
`$SizeReplacementString` `$INSTANCE_NAME`_sensorSignal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
uint8 `$INSTANCE_NAME`_sensorOnMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK] = {0u};

uint8 `$INSTANCE_NAME`_lowBaselineResetCnt[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
`$LowBaselineResetArray`

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
	extern `$INSTANCE_NAME`_CONFIG_TYPE_P4_v2_0 `$INSTANCE_NAME`_config;
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

/* Generated by Customizer */
`$writerCSHLCVariables`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BaseInit
********************************************************************************
*
* Summary:
*  Loads the `$INSTANCE_NAME`_sensorBaseline[sensor] array element with an 
*  initial value which is equal to the raw count value. 
*  Resets to zero `$INSTANCE_NAME`_sensorBaselineLow[sensor] and 
*  `$INSTANCE_NAME`_sensorSignal[sensor] array element.
*  Loads the `$INSTANCE_NAME`_debounceCounter[sensor] array element with the initial 
*  value equal `$INSTANCE_NAME`_debounce[].
*  Loads the `$INSTANCE_NAME`_rawFilterData2[sensor] and 
*  `$INSTANCE_NAME`_rawFilterData2[sensor] array element with an 
*  initial value which is equal to the raw count value if the raw data filter is enabled.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorBaseline[]    - used to store the baseline value.
*  `$INSTANCE_NAME`_sensorBaselineLow[] - used to store the fraction byte of 
*  the baseline value.
*  `$INSTANCE_NAME`_sensorSignal[]      - used to store a difference between 
*  the current value of raw data and the previous value of the baseline.
*  `$INSTANCE_NAME`_debounceCounter[]   - used to store the current debounce 
*  counter of the sensor. The widgets which have this parameter are buttons, matrix 
*  buttons, proximity, and guard. All other widgets don't have the  debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  `$INSTANCE_NAME`_rawFilterData1[]    - used to store a previous sample of 
*  any enabled raw data filter.
*  `$INSTANCE_NAME`_rawFilterData2[]    - used to store before a previous sample
*  of the enabled raw data filter. Required only for median or average filters.
*
* Side Effects:
*  None
* 
*******************************************************************************/
void `$INSTANCE_NAME`_BaseInit(uint32 sensor)
{
    #if ((`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT) || (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) || \
         (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT))
        uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    #endif /* ((`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) || (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)) */
    
    #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8 debounceIndex;
    #endif  /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
        {
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
    
    /* Initialize Baseline */
    `$INSTANCE_NAME`_sensorBaseline[sensor] = `$INSTANCE_NAME`_sensorRaw[sensor];
    `$INSTANCE_NAME`_sensorBaselineLow[sensor] = 0u;
    `$INSTANCE_NAME`_sensorSignal[sensor] = 0u;
        
`$writerCSHLDebounceInit`
    
    #if ((0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) ||\
         (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)))

        `$INSTANCE_NAME`_rawFilterData1[sensor] = `$INSTANCE_NAME`_sensorRaw[sensor];
        `$INSTANCE_NAME`_rawFilterData2[sensor] = `$INSTANCE_NAME`_sensorRaw[sensor];
    
    #elif ((`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER) ||\
           (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER) ||\
           (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER) ||\
           (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER) ||\
           (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER))
            
        `$INSTANCE_NAME`_rawFilterData1[sensor] = `$INSTANCE_NAME`_sensorRaw[sensor];
    
    #else
        /* No Raw filters */
    #endif  /* ((`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
            *   (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER))
            */
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeSensorBaseline
********************************************************************************
*
* Summary:
*  Loads the `$INSTANCE_NAME`_sensorBaseline[sensor] array element with an 
*  initial value by scanning the selected sensor (one channel design) or a pair 
*  of sensors (two channels designs). The raw count value is copied into the 
*  baseline array for each sensor. The raw data filters are initialized if 
*  enabled.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
* 
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeSensorBaseline(uint32 sensor)
{
    /* Scan sensor */
    `$INSTANCE_NAME`_ScanSensor(sensor);
    while(`$INSTANCE_NAME`_IsBusy() != 0u)
    {
        /* Wait while sensor is busy */
    }
    
    /* Initialize Baseline, Signal and debounce counters */       
    `$INSTANCE_NAME`_BaseInit(sensor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeAllBaselines
********************************************************************************
*
* Summary:
*  Uses the `$INSTANCE_NAME`_InitializeSensorBaseline function to load the 
*  `$INSTANCE_NAME`_sensorBaseline[] array with an initial values by scanning 
*  all the sensors. The raw count values are copied into the baseline array for 
*  all the sensors. The raw data filters are initialized if enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
* 
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeAllBaselines(void)
{
    uint32 i;
    
	for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; i++)
	{
    	`$INSTANCE_NAME`_InitializeSensorBaseline(i);
	}
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeEnabledBaselines
********************************************************************************
*
* Summary:
*  Scans all the enabled widgets and the raw count values are copied into the 
*  baseline array for all the sensors enabled in the scanning process. The baselines 
*  are initialized with zero values for sensors disabled from the scanning process. 
*  The raw data filters are initialized if enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store the sensors raw data.
*  `$INSTANCE_NAME`_sensorEnableMask[ ] - used to store bit masks of the enabled sensors.
*
* Side Effects:
*  None
* 
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeEnabledBaselines(void)
{
    uint32 i;
    uint32 isSensorEnabled;
    
    `$INSTANCE_NAME`_ScanEnabledWidgets();
    while(`$INSTANCE_NAME`_IsBusy() != 0u)
    {
        /* Wait while sensor is busy */
    }
    
    for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        isSensorEnabled = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorEnableMask, i);
        
        /* Clear raw data if sensor is disabled from scanning process */
        if(isSensorEnabled != 0u)
        {
            /* Initialize baselines */
            `$INSTANCE_NAME`_BaseInit(i);
        }
    }
}  


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateBaselineNoThreshold
********************************************************************************
*
* Summary:
*  Updates the `$INSTANCE_NAME`_sensorBaseline[sensor] array element using the 
*  LP filter with k = 256. The signal calculates the difference of count by 
*  subtracting the previous baseline from the current raw count value and stores
*  it in `$INSTANCE_NAME`_sensorSignal[sensor]. 
*  If the auto reset option is enabled, the baseline updated regards the noise threshold. 
*  If the auto reset option is disabled, the baseline stops updating; baseline is loaded 
*  with a raw count value if a signal is greater than zero and if signal is less 
*  than noise threshold.
*  Raw data filters are applied to the values if enabled before baseline 
*  calculation.
*
*  This API does not update the thresholds in the Smartsense Mode.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[]  - stores widget numbers.
*  `$INSTANCE_NAME`_sensorBaseline[]    - used to store baseline value.
*  `$INSTANCE_NAME`_sensorBaselineLow[] - used to store fraction byte of 
*  baseline value.
*  `$INSTANCE_NAME`_sensorSignal[]      - used to store difference between 
*  current value of raw data and previous value of baseline.
*  `$INSTANCE_NAME`_rawFilterData1[]    - used to store previous sample of 
*  any enabled raw data filter.
*  `$INSTANCE_NAME`_rawFilterData2[]    - used to store before previous sample
*  of enabled raw data filter. Only required for median or average filters.
* 
* Side Effects:
*  None
* 
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateBaselineNoThreshold(uint32 sensor)
{
    uint32 calc;
	uint32 sign;
    uint16 tempRaw;
    uint16 filteredRawData;
    uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    `$SizeReplacementString` noiseThreshold = `$INSTANCE_NAME`_noiseThreshold[widget];
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
        {
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
    
    filteredRawData = `$INSTANCE_NAME`_sensorRaw[sensor];
    
    #if (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)
        tempRaw = filteredRawData;
        filteredRawData = `$INSTANCE_NAME`_MedianFilter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor], 
                                                        `$INSTANCE_NAME`_rawFilterData2[sensor]);
        `$INSTANCE_NAME`_rawFilterData2[sensor] = `$INSTANCE_NAME`_rawFilterData1[sensor];
        `$INSTANCE_NAME`_rawFilterData1[sensor] = tempRaw;
        
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)
        tempRaw = filteredRawData;
        filteredRawData = `$INSTANCE_NAME`_AveragingFilter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor],
                                                           `$INSTANCE_NAME`_rawFilterData2[sensor]);
        `$INSTANCE_NAME`_rawFilterData2[sensor] = `$INSTANCE_NAME`_rawFilterData1[sensor];
        `$INSTANCE_NAME`_rawFilterData1[sensor] = tempRaw;
        
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)
        filteredRawData = `$INSTANCE_NAME`_IIR2Filter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor]);
        `$INSTANCE_NAME`_rawFilterData1[sensor] = filteredRawData;
        
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)
        filteredRawData = `$INSTANCE_NAME`_IIR4Filter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor]);
        `$INSTANCE_NAME`_rawFilterData1[sensor] = filteredRawData;
            
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)
        filteredRawData = `$INSTANCE_NAME`_JitterFilter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor]);
        `$INSTANCE_NAME`_rawFilterData1[sensor] = filteredRawData;
        
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)
        filteredRawData = `$INSTANCE_NAME`_IIR8Filter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor]);
        `$INSTANCE_NAME`_rawFilterData1[sensor] = filteredRawData;
        
    #elif (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER)
        filteredRawData = `$INSTANCE_NAME`_IIR16Filter(filteredRawData, `$INSTANCE_NAME`_rawFilterData1[sensor]);
        `$INSTANCE_NAME`_rawFilterData1[sensor] = filteredRawData;
        
    #else
        /* No Raw filters */
    #endif  /* (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) */

	#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
	    MeasureNoiseEnvelope_P4_v2_0(&`$INSTANCE_NAME`_config, (uint8)sensor, `$INSTANCE_NAME`_sensorRaw);
	#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

    /* Baseline calculation */
    /* Calculate difference RawData[cur] - Baseline[prev] */
    if(filteredRawData >= `$INSTANCE_NAME`_sensorBaseline[sensor])
    {
		`$INSTANCE_NAME`_lowBaselineResetCnt[sensor] = 0u;	
        tempRaw = filteredRawData - `$INSTANCE_NAME`_sensorBaseline[sensor];
        sign = 1u;    /* Positive difference - Calculate the Signal */
    }
    else
    {
        tempRaw = `$INSTANCE_NAME`_sensorBaseline[sensor] - filteredRawData;
        sign = 0u;    /* Negative difference - Do NOT calculate the Signal */
    }

	#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
	if((sign == 0u) && (tempRaw > (uint16) `$INSTANCE_NAME`_negativeNoiseThreshold[widget]))
	#else
	if((sign == 0u) && (tempRaw > (uint16) `$INSTANCE_NAME`_NEGATIVE_NOISE_THRESHOLD))
	#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */ 
    {
        if(`$INSTANCE_NAME`_lowBaselineResetCnt[sensor] >= `$INSTANCE_NAME`_LOW_BASELINE_RESET)
        {
            `$INSTANCE_NAME`_BaseInit(sensor);
            `$INSTANCE_NAME`_lowBaselineResetCnt[sensor] = 0u;
        }
        else
        {
            `$INSTANCE_NAME`_lowBaselineResetCnt[sensor]++;
        }
    }
    else
    {
        #if (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE)
		#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)			
			/* Update Baseline if lower than noiseThreshold */
			if ( (tempRaw <= noiseThreshold) || 
			 ((tempRaw < (uint16) `$INSTANCE_NAME`_negativeNoiseThreshold[widget])
			   && (sign == 0u)))
			{
		#else
			/* Update Baseline if lower than noiseThreshold */
			if ( (tempRaw <= noiseThreshold) || 
				 ((tempRaw < (uint16) `$INSTANCE_NAME`_NEGATIVE_NOISE_THRESHOLD)
				   && (sign == 0u)))
			{
		#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */ 
        #endif /* (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE) */
                /* Make full Baseline 23 bits */
                calc = (uint32) `$INSTANCE_NAME`_sensorBaseline[sensor] << 8u;
                calc |= (uint32) `$INSTANCE_NAME`_sensorBaselineLow[sensor];

                /* Add Raw Data to Baseline */
                calc += filteredRawData;

                /* Sub the high Baseline */
                calc -= `$INSTANCE_NAME`_sensorBaseline[sensor];

                /* Put Baseline and BaselineLow */
                `$INSTANCE_NAME`_sensorBaseline[sensor] = ((uint16) (calc >> 8u));
                `$INSTANCE_NAME`_sensorBaselineLow[sensor] = ((uint8) calc);

                `$INSTANCE_NAME`_lowBaselineResetCnt[sensor] = 0u;
        #if (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE)
            }
        #endif /* (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE) */
    }

    /* Calculate Signal if positive difference > noiseThreshold */
    if((tempRaw > (uint16) noiseThreshold) && (sign != 0u))
    {
        #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
            /* Over flow defence for uint8 */
            if (tempRaw > 0xFFu)
            {
                `$INSTANCE_NAME`_sensorSignal[sensor] = 0xFFu;
            }    
            else 
            {
                `$INSTANCE_NAME`_sensorSignal[sensor] = ((uint8) tempRaw);
            }
        #else
            `$INSTANCE_NAME`_sensorSignal[sensor] = ((uint16) tempRaw);
        #endif  /* (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8) */
    }
    else
    {
        /* Signal is zero */
        `$INSTANCE_NAME`_sensorSignal[sensor] = 0u;
    }

    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateSensorBaseline
********************************************************************************
*
* Summary:
*  Updates the `$INSTANCE_NAME`_sensorBaseline[sensor] array element using the 
*  LP filter with k = 256. The signal calculates the difference of count by 
*  subtracting the previous baseline from the current raw count value and stores
*  it in `$INSTANCE_NAME`_sensorSignal[sensor]. 
*  If the auto reset option is enabled, the baseline updated regards the noise threshold. 
*  If the auto reset option is disabled, the baseline stops updating. 
*  Baseline is loaded with raw count value if a signal is greater than zero and  
*  if signal is less than noise threshold.
*  Raw data filters are applied to the values if enabled before baseline 
*  calculation.
*  This API updates the thresholds in the Smartsense Mode.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[]  - stores widget numbers.
* 
* Side Effects:
*  None
* 
*******************************************************************************/
 void `$INSTANCE_NAME`_UpdateSensorBaseline(uint32 sensor)
{
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
		uint32 widget;
		
		widget = `$INSTANCE_NAME`_widgetNumber[sensor];
	
        /* Exclude generic widget */
        if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
        {
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */

    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    	`$INSTANCE_NAME`_UpdateThresholds(sensor);
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

    `$INSTANCE_NAME`_UpdateBaselineNoThreshold(sensor);
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateEnabledBaselines
********************************************************************************
*
* Summary:
*  Checks `$INSTANCE_NAME`_sensorEnableMask[] array and calls the 
*  `$INSTANCE_NAME`_UpdateSensorBaseline function to update the baselines 
*  for the enabled sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_sensorEnableMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
* 
* Side Effects:
*  None
* 
*******************************************************************************/
 void `$INSTANCE_NAME`_UpdateEnabledBaselines(void)
{
    uint32 i;
    uint32 isSensorEnabled;
    
    for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        isSensorEnabled = `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorEnableMask, i);
        
        if(0u != isSensorEnabled)
        {
            `$INSTANCE_NAME`_UpdateSensorBaseline(i);
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetBaselineData
********************************************************************************
*
* Summary:
*  This function reads the sensor baseline from the component.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns the baseline value of the sensor indicated by an argument.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorBaseline[] - the array with an initial values by scanning
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetBaselineData(uint32 sensor)
{
	return (`$INSTANCE_NAME`_sensorBaseline[sensor]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBaselineData
********************************************************************************
*
* Summary:
*  This API writes the data value passed as an argument to the sensor baseline array.
*
* Parameters:
*  sensor:  Sensor number.
*  data:    Sensor baseline.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorBaseline[] - the array with initial values by scanning
* 
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBaselineData(uint32 sensor, uint16 data)
{
	`$INSTANCE_NAME`_sensorBaseline[sensor] = data;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDiffCountData
********************************************************************************
*
* Summary:
*  This function returns the Sensor Signal from the component.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns the difference count value of the sensor indicated by the 
*  argument. 
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorSignal[] - the array with difference counts for sensors
* 
* Side Effects:
*  None
*
*******************************************************************************/
`$SizeReplacementString` `$INSTANCE_NAME`_GetDiffCountData(uint32 sensor)
{
	return (`$INSTANCE_NAME`_sensorSignal[sensor]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDiffCountData
********************************************************************************
*
* Summary:
*  This API writes the data value passed as an argument to the sensor signal array.
*
* Parameters:
*  sensor:  Sensor number.
*  value:   Sensor signal.
*
* Return:
*  None. 
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorSignal[] - the array with difference counts for sensors
* 
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetDiffCountData(uint32 sensor, `$SizeReplacementString` value)
{
    `$INSTANCE_NAME`_sensorSignal[sensor] = value;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFingerThreshold
********************************************************************************
*
* Summary:
*  This function reads the finger threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the finger threshold of the widget indicated by the argument. 
*
* Global Variables:
*  `$INSTANCE_NAME`_fingerThreshold[] - This array contains the level of signal 
*  for each widget that is determined if a finger is present on the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
`$SizeReplacementString` `$INSTANCE_NAME`_GetFingerThreshold(uint32 widget)
{
	return(`$INSTANCE_NAME`_fingerThreshold[widget]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNoiseThreshold
********************************************************************************
*
* Summary:
*  This function reads the noise threshold from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the noise threshold of the widget indicated by the argument. 
*
* Global Variables:
*  `$INSTANCE_NAME`_noiseThreshold[] - This array contains the level of signal 
*  for each widget that determines the level of noise in the capacitive scan.
* 
* Side Effects:
*  None
*
*******************************************************************************/
`$SizeReplacementString` `$INSTANCE_NAME`_GetNoiseThreshold(uint32 widget)
{
	return (`$INSTANCE_NAME`_noiseThreshold[widget]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFingerHysteresis
********************************************************************************
*
* Summary:
*  This function reads the Hysteresis value from the component.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  This API returns the Hysteresis of the widget indicated by the argument. 
*
* Global Variables:
*  `$INSTANCE_NAME`_hysteresis[] - This array contains the hysteresis value 
*   for each widget.
*  `$INSTANCE_NAME`_widgetNumberSld - structure with dynamic sliders' parameters.
*
* Side Effects:
*  None
*
*******************************************************************************/
`$SizeReplacementString` `$INSTANCE_NAME`_GetFingerHysteresis(uint32 widget)
{
	return(`$INSTANCE_NAME`_hysteresis[widget]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNegativeNoiseThreshold
********************************************************************************
*
* Summary:
*  This function reads the negative noise threshold from the component.
*
* Parameters: 
*  None.
*
* Return Value: 
*  This API returns the negative noise threshold
*
* Global Variables:
*  `$INSTANCE_NAME`_negativeNoiseThreshold - This variable specifies the negative 
*   difference between the raw count and baseline levels for Baseline resetting
*   to the raw count level.
* 
* Side Effects:
*  None
*
*******************************************************************************/
`$SizeReplacementString` `$INSTANCE_NAME`_GetNegativeNoiseThreshold(uint32 widget)
{
#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
	return(`$INSTANCE_NAME`_negativeNoiseThreshold[widget]);
#else
	return(`$INSTANCE_NAME`_NEGATIVE_NOISE_THRESHOLD);
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */ 
}


#if(`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetFingerThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the finger threshold value for a widget. 
	*
	* Parameters: 
	*  sensorNumber:  widget index. 
	*  value:  Finger threshold value for the widget.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_fingerThreshold[] - This array contains the level of signal 
	*   for each widget that determines if a finger is present on the widget.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetFingerThreshold(uint32 widget, `$SizeReplacementString` value)
	{	
		`$INSTANCE_NAME`_fingerThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetNoiseThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the Noise Threshold value for each widget.
	*
	* Parameters:
	*  widget:  Sensor index number.
	*  value:   Noise Threshold value for widget.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_noiseThreshold[] - This array contains the level of signal 
	*   for each widget that determines the level of noise in the capacitive scan.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetNoiseThreshold(uint32 widget, `$SizeReplacementString` value)
	{
		`$INSTANCE_NAME`_noiseThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetFingerHysteresis
	********************************************************************************
	*
	* Summary:
	*  This API sets the Hysteresis value of a widget
	*
	* Parameters: 
	*  value:  Hysteresis value for widgets.
	*  widget:  widget number
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_hysteresis[] - This array contains the hysteresis value for each widget.
	*  `$INSTANCE_NAME`_widgetNumberSld - structure with dynamic sliders' parameters.
	*
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetFingerHysteresis(uint32 widget, `$SizeReplacementString` value)
	{
		`$INSTANCE_NAME`_hysteresis[widget] = value;
	}


	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetNegativeNoiseThreshold
	********************************************************************************
	*
	* Summary:
	*  This API sets the Negative Noise Threshold value of a widget
	*
	* Parameters: 
	*  value:  Negative Noise Threshold value for widgets.
	*  widget: widget number
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_negativeNoiseThreshold  - This parameter specifies the negative 
	*   difference between the raw count and baseline levels for Baseline resetting to 
	*   the raw count level.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetNegativeNoiseThreshold(uint32 widget, `$SizeReplacementString` value)
	{
		`$INSTANCE_NAME`_negativeNoiseThreshold[widget] = value;
	}


	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetDebounce
	********************************************************************************
	*
	* Summary:
	*  This API sets the debounce value for a widget.
	*
	* Parameters: 
	*  value:  Debounce value for widget.
	*  widget: widget index.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_debounce[] - This array contains the debounce value for each widget.
	*  `$INSTANCE_NAME`_widgetNumberSld - structure with dynamic sliders' parameters.
	*
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetDebounce(uint32 widget, uint8 value)
	{
		`$INSTANCE_NAME`_debounce[widget] = value;
	}


	/*******************************************************************************
	* Function Name: `$INSTANCE_NAME`_SetLowBaselineReset
	********************************************************************************
	*
	* Summary:
	*  This API sets the low baseline reset threshold value for the sensor.
	*
	* Parameters: 
	*  value: low baseline reset threshold value.
	*  sensor: Sensor index.
	*
	* Return Value: 
	*  None
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_lowBaselineReset[] - This array contains the Baseline update 
	*  threshold value for each sensor.
	* 
	* Side Effects:
	*  None
	*
	*******************************************************************************/
	void `$INSTANCE_NAME`_SetLowBaselineReset(uint32 sensor, uint8 value)
	{
		`$INSTANCE_NAME`_lowBaselineReset[sensor] = value;
	}
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsSensorActive
********************************************************************************
*
* Summary:
*  Compares the `$INSTANCE_NAME`_sensorSignal[sensor] array element to the finger
*  threshold of the widget it belongs to. The hysteresis and debounce are taken into 
*  account. The hysteresis is added or subtracted from the finger threshold 
*  based on whether the sensor is currently active. 
*  If the sensor is active, the threshold is lowered by the hysteresis amount.
*  If the sensor is inactive, the threshold is raised by the hysteresis amount.
*  The debounce counter is added to the sensor active transition.
*  This function updates the `$INSTANCE_NAME`_sensorOnMask[] array element.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns sensor state 1 if active, 0 if not active.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorSignal[] - used to store the difference between 
*  the current value of raw data and a previous value of the baseline.
*  `$INSTANCE_NAME`_debounceCounter[]   - used to store the current debounce 
*  counter of the sensor. the widget which have this parameter are buttons, matrix 
*  buttons, proximity, and guard. All other widgets don't have the  debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  `$INSTANCE_NAME`_sensorOnMask[] - used to store the sensors on/off state.
*  `$INSTANCE_NAME`_sensorOnMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor is inactive.
*  1 - sensor is active.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckIsSensorActive(uint32 sensor)
{	
	uint8 widget;
	uint8 debounce;
	uint8 debounceIndex;
    
	`$SizeReplacementString` fingerThreshold;
	`$SizeReplacementString` hysteresis;
	
    /* Prepare to find debounce counter index */
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];
	
    fingerThreshold = `$INSTANCE_NAME`_fingerThreshold[widget];
	hysteresis = `$INSTANCE_NAME`_hysteresis[widget];
	debounce = `$INSTANCE_NAME`_debounce[widget];	
	
	`$writerCSHLIsSensor`
	
    /* Was on */
    if (0u != `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorOnMask, sensor))
    {
        /* Hysteresis minus */
        if (`$INSTANCE_NAME`_sensorSignal[sensor] < (fingerThreshold - hysteresis))
        {
	   		`$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorOnMask, sensor, 0u);
			/* Sensor inactive - reset Debounce counter */
            `$INSTANCE_NAME`_debounceCounter[debounceIndex] = debounce;
        }
    }
    else    /* Was off */
    {
        /* Hysteresis plus */
        if (`$INSTANCE_NAME`_sensorSignal[sensor] >= (fingerThreshold + hysteresis))
        {
			`$INSTANCE_NAME`_debounceCounter[debounceIndex]--;
            /* Sensor active, decrement debounce counter */
            if(`$INSTANCE_NAME`_debounceCounter[debounceIndex] == 0u)
            {
                `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorOnMask, sensor, 1u); 
            }
        }
        else
        {
            /* Sensor inactive - reset Debounce counter */
            `$INSTANCE_NAME`_debounceCounter[debounceIndex] = debounce;
        }
    }
    
    return ((uint32)((0u != `$INSTANCE_NAME`_GetBitValue(`$INSTANCE_NAME`_sensorOnMask, sensor)) ? 1u : 0u));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsWidgetActive
********************************************************************************
*
* Summary:
*  Compares the CapSense_sensorSignal[] array element to the finger threshold of 
* the widget it belongs to. The hysteresis and debounce are taken into account. 
* The hysteresis is added or subtracted from the finger threshold based on whether
*  the sensor is currently active. If the sensor is active, the threshold is 
*  lowered by the hysteresis amount. If the sensor is inactive, the threshold 
*  is raised by the hysteresis amount. 
* The debounce counter added to the sensor active transition. 
* This function updates CapSense_sensorOnMask[] array element
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns widget sensor state 1 if one or more sensors within widget is/are 
*  active, 0 if all sensors within widget are inactive.
*
* Global Variables:
*  rawDataIndex[] – Contains the  1st sensor position in the widget
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckIsWidgetActive(uint32 widget)
{
    uint32 rawIndex = (uint32)`$INSTANCE_NAME`_rawDataIndex[widget];
    uint32 numOfSensors = (uint32)`$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
    uint32 state = 0u;

    /* Check all sensors of widget */
    do
    {
        if(`$INSTANCE_NAME`_CheckIsSensorActive((uint32)rawIndex) != 0u)
        {
            state = `$INSTANCE_NAME`_SENSOR_IS_ACTIVE;
        }
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
    
`$writerCSHLIsWidget`
    
    return state;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsAnyWidgetActive
********************************************************************************
*
* Summary:
*  Compares all the sensors of the `$INSTANCE_NAME`_Signal[] array to their finger 
*  threshold. Calls `$INSTANCE_NAME`_CheckIsWidgetActive() for each widget so 
*  the `$INSTANCE_NAME`_sensorOnMask[] array is up to date after calling this 
*  function.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns 1 if any widget is active, 0 none of widgets are active.
*
* Global Variables:
*  None
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckIsAnyWidgetActive(void)
{

	`$writerCSHLIsAnyWidget`

    return state;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableWidget
********************************************************************************
*
* Summary:
*  Enables all the widget elements (sensors) to the scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_sensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
* 
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableWidget(uint32 widget)
{

    uint8 rawIndex = `$INSTANCE_NAME`_rawDataIndex[widget];
    uint8 numOfSensors = `$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
    
    /* Enable all sensors of widget */
    do
    {
        `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, (uint32)rawIndex, 1u);
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableWidget
********************************************************************************
*
* Summary:
*  Disables all the widget elements (sensors) from the scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_sensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_sensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor isn't scanned by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor is scanned by `$INSTANCE_NAME`_ScanEnabledWidgets().
* 
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableWidget(uint32 widget)
{
    uint8 rawIndex = `$INSTANCE_NAME`_rawDataIndex[widget];
    uint8 numOfSensors = `$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
   
    /* Disable all sensors of widget */
    do
    {

        `$INSTANCE_NAME`_SetBitValue(`$INSTANCE_NAME`_sensorEnableMask, (uint32)rawIndex, 0u);
        rawIndex++;
    }
    while(rawIndex < numOfSensors);
}


#if(`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_FindMaximum
    ********************************************************************************
    *
    * Summary:
    *  Finds the index of the maximum element within a defined centroid. Checks 
    *  `$INSTANCE_NAME`_sensorSignal[] within a defined centroid and 
    *  returns the index of the maximum element. The values below the finger threshold are 
    *  ignored.
    *  The centroid is defined by offset of the first element and a number of elements - count.
    *  The diplexed centroid requires at least two consecutive elements above
    *  FingerThreshold to find the index of the maximum element.
    * 
    * Parameters:
    *  offset:  Start index of centroid in `$INSTANCE_NAME`_sensorSignal[] array.
    *  count:   number of elements within centroid.
    *  fingerThreshold:  Finger threshold.
    *  diplex:   pointer to diplex table.
    * 
    * Return:
    *  Returns the index of the maximum element within a defined centroid.
    *  If the index of the maximum element isn't found it returns 0xFF.
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_startOfSlider[] - contains the index of the first slider element
	* 
	* Side Effects: 
	*  None
	* 
    *******************************************************************************/
	#if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
		uint8 `$INSTANCE_NAME`_FindMaximum(uint8 offset, uint8 count, `$SizeReplacementString` fingerThreshold, const uint8 *diplex)
	#else 
		uint8 `$INSTANCE_NAME`_FindMaximum(uint8 offset, uint8 count, `$SizeReplacementString` fingerThreshold)
	#endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
    {
        uint8 i;
        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)        
            uint8 curPos = 0u;
            /* No centroid at Start */
            uint8 curCntrdSize = 0u;
            uint8 curCtrdStartPos = `$INSTANCE_NAME`_MAXIMUM_CENTROID;
            /* Biggest centroid is zero */
            uint8 biggestCtrdSize = 0u;
            uint8 biggestCtrdStartPos = 0u;
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
        uint8 maximum = `$INSTANCE_NAME`_MAXIMUM_CENTROID;
		
        `$SizeReplacementString` temp = 0u;
        `$SizeReplacementString` *startOfSlider = &`$INSTANCE_NAME`_sensorSignal[offset];

        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)        
            if(diplex != 0u)
            {
                /* Initialize */
                i = 0u;
                
                /* Make slider x2 as Diplexed */
                count <<= 1u;
                while(1u)
                { 
                    if (startOfSlider[curPos] > 0u)    /* Looking for centroids */
                    {
                        if (curCtrdStartPos == `$INSTANCE_NAME`_MAXIMUM_CENTROID)
                        {
                            /* Start of centroid */
                            curCtrdStartPos = i;
                            curCntrdSize++;
                        }
                        else
                        {
                            curCntrdSize++;
                        }
                    }
                    else   /* Select biggest and indicate zero start */
                    {          
                        if(curCntrdSize > 0u)
                        {
                            /* We are at the end of current */
                            if(curCntrdSize > biggestCtrdSize)
                            {
                                biggestCtrdSize = curCntrdSize;
                                biggestCtrdStartPos = curCtrdStartPos;
                            }
                            
                            curCntrdSize = 0u;
                            curCtrdStartPos = `$INSTANCE_NAME`_MAXIMUM_CENTROID;
                        }
                    }
                    
                    i++; 
                    curPos = diplex[i];
                    if(i == count)
                    {
                        break;
                    }            
                }
                    
                    /* Find biggest centroid if two are same size, last one wins
                       We are at the end of current */
                if (curCntrdSize >= biggestCtrdSize) 
                {
                    biggestCtrdSize = curCntrdSize;
                    biggestCtrdStartPos = curCtrdStartPos;
                }
            }
            else
            {
                /* Without diplexing */ 
                biggestCtrdSize = count;
            }
                        

            /* Check centroid size */
            #if (`$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER)
                if((biggestCtrdSize >= 2u) || ((biggestCtrdSize == 1u) && (diplex == 0u)))
            #else                    
                if(biggestCtrdSize >= 2u)
            #endif /* (`$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER) */
                {
                    for (i = biggestCtrdStartPos; i < (biggestCtrdStartPos + biggestCtrdSize); i++)
                    {
                        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER && `$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER)
                            if (diplex == 0u)
                            {
                                curPos = i;
                            }
                            else
                            {
                                curPos = diplex[i];
                            }                    
                        #elif (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)                    
                            curPos = diplex[i];                    
                        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER && `$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER) */
                        /* Looking for greater element within centroid */
                        if(startOfSlider[curPos] > fingerThreshold)
                        {
                            if(startOfSlider[curPos] > temp)
                            {
                                maximum = i;
                                temp = startOfSlider[curPos];
                            }
                        }
                    }
                } 
        #else
            for (i = 0u; i < count; i++)
            {                      
                /* Looking for greater element within centroid */
                if(startOfSlider[i] > fingerThreshold)
                {
                    if(startOfSlider[i] > temp)
                    {
                        maximum = i;
                        temp = startOfSlider[i];
                    }
                }
            }    
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
        return (maximum);
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalcCentroid
    ********************************************************************************
    *
    * Summary:
    *  Returns a position value calculated according to the index of the maximum element and API
    *  resolution.
    *
    * Parameters:
    *  type:  widget type.
    *  diplex:  pointer to diplex table.
    *  maximum:  Index of maximum element within centroid.
    *  offset:   Start index of centroid in `$INSTANCE_NAME`_sensorSignal[] array.
    *  count:    Number of elements within centroid.
    *  resolution:  multiplicator calculated according to centroid type and
    *  API resolution.
    *  noiseThreshold:  Noise threshold.
    * 
    * Return:
    *  Returns a position value of the slider.
	*
	* Side Effects: 
	*  None
	* 
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidPrototypeCallReplacementString`uint8 maximum, uint8 offset, 
                                        uint8 count, uint16 resolution, `$SizeReplacementString` noiseThreshold)
    {
        #if ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u))
            uint8 posPrev;
            uint8 posNext;
        #endif /* ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT>0u) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT>0u)) */
        
        /* Helps during centroid calculation */
        #if (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
		    static `$SizeReplacementString` `$INSTANCE_NAME`_centroid[3u];
        #endif  /* (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */
               
        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)                
            uint8 pos;
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

        uint8 position;
        uint32 numerator;
        int32 denominator;
		
		`$SizeReplacementString`  *startOfSlider = &`$INSTANCE_NAME`_sensorSignal[offset];
		
        #if ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u))
            posPrev = 0u;
            posNext = 0u;
        #endif /* ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT>0u) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT>0u)) */
     
        #if (`$INSTANCE_NAME`_ADD_SLIDER_TYPE)
            if(type == `$INSTANCE_NAME`_TYPE_RADIAL_SLIDER)
            {
        #endif /* (`$INSTANCE_NAME`_ADD_SLIDER_TYPE) */

            #if (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u)                
                /* Copy Signal to the centroid array */
                `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS] = startOfSlider[maximum];
                 
                /* Check borders for ROTARY Slider */
                if (maximum == 0u)                   /* Start of centroid */
                { 
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = startOfSlider[count - 1u];
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = startOfSlider[1u];
                }
                else if (maximum == (count - 1u))    /* End of centroid */
                {
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = startOfSlider[maximum - 1u];
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = startOfSlider[0u];
                }
                else                                /* Not first Not last */
                {
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = startOfSlider[maximum - 1u];
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = startOfSlider[maximum + 1u];
                }
            #endif /* (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) */

        #if (`$INSTANCE_NAME`_ADD_SLIDER_TYPE)
            }
            else
            {
        #endif /* (`$INSTANCE_NAME`_ADD_SLIDER_TYPE) */

            #if ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u))
                #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER && `$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER)                    
                    /* Calculate next and previous near to maximum */
                    if(diplex == 0u)
                    {
                        pos     = maximum;
                        posPrev = maximum - 1u;
                        posNext = maximum + 1u; 
                    }
                    else
                    {
                        pos     = diplex[maximum];
                        posPrev = diplex[maximum - 1u];
                        posNext = diplex[maximum + 1u];
                        count <<= 1u;
                    }                    
                #elif (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
                    /* Calculate next and previous near to maximum */
                    pos     = diplex[maximum];
                    posPrev = diplex[maximum - 1u];
                    posNext = diplex[maximum + 1u];
                    count <<= 1u;                    
                #else                    
                    /* Calculate next and previous near to maximum */
                    if (maximum >= 1u)
                    {
                        posPrev = maximum - 1u;
                    }
                    posNext = maximum + 1u;
                #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER && `$INSTANCE_NAME`_IS_NON_DIPLEX_SLIDER) */
                        
                /* Copy Signal to the centroid array */
                #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS] = startOfSlider[pos];
                #else
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS] = startOfSlider[maximum];
                #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
                    
                /* Check borders for LINEAR Slider */
                if (maximum == 0u)                   /* Start of centroid */
                { 
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = 0u;
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = startOfSlider[posNext];
                }
                else if (maximum == ((count) - 1u)) /* End of centroid */
                {
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = startOfSlider[posPrev];
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = 0u;
                }
                else                                /* Not first Not last */
                {
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = startOfSlider[posPrev];
                    `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = startOfSlider[posNext];
                }
            #endif /* ((`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT>0u)||(`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT>0u))*/

        #if (`$INSTANCE_NAME`_ADD_SLIDER_TYPE)
            }
        #endif /* (`$INSTANCE_NAME`_ADD_SLIDER_TYPE) */
    
        /* Subtract noiseThreshold */
        if(`$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] > noiseThreshold)
        {
            `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] -= noiseThreshold;
        }
        else
        {
            `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] = 0u;
        }
        
        /* Maximum always greater than fingerThreshold, so greater than noiseThreshold */
        `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS] -= noiseThreshold;
        
        /* Subtract noiseThreshold */
        if(`$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] > noiseThreshold)
        {
            `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] -= noiseThreshold;
        }
        else
        {
            `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] = 0u;
        }
        
        
        /* Si+1 - Si-1 */
        numerator = (uint32) `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT] -
                    (uint32) `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV];

        /* Si+1 + Si + Si-1 */
        denominator = (int32) `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_PREV] + 
                      (int32) `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS] + 
                      (int32) `$INSTANCE_NAME`_centroid[`$INSTANCE_NAME`_POS_NEXT];
        
        /* (numerator/denominator) + maximum */
        denominator = (((int32)(uint32)((uint32)numerator << 8u)/denominator) + (int32)(uint32)((uint32) maximum << 8u));

        #if(`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u)
            /* Only required for RADIAL Slider */
            if(denominator < 0)
            {
                denominator += (int32)((uint16)((uint16) count << 8u));
            }
        #endif /* (`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) */
        
        denominator *= (int16)resolution;
        
        /* Round result and put it to uint8 */
        position = ((uint8) HI16((uint32)denominator + `$INSTANCE_NAME`_CENTROID_ROUND_VALUE));

        return (position);
    }    
#endif /* (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */


#if((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  Checks the `$INSTANCE_NAME`_Signal[ ] array for a centroid within
    *  a slider specified range. The centroid position is calculated according to the resolution
    *  specified in the CapSense customizer. The position filters are applied to the
    *  result if enabled.
    *
    * Parameters:
    *  widget:  Widget number.
    *  For every linear slider widget there are defines in this format:
    *  #define `$INSTANCE_NAME`_"widget_name"__LS           5
    * 
    * Return:
    *  Returns a position value of the linear slider.
	*
	* Global Variables:
	*  None
	*
    * Side Effects:
    *  If any sensor within the slider widget is active, the function returns values
    *  from zero to the API resolution value set in the CapSense customizer. If no
    *  sensors are active, the function returns 0xFFFF. If an error occurs during
    *  execution of the centroid/diplexing algorithm, the function returns 0xFFFF.
    *  There are no checks of the widget type argument provided to this function.
    *  The unproper widget type provided will cause unexpected position calculations.
    *
    * Note:
    *  If noise counts on the slider segments are greater than the noise
    *  threshold, this subroutine may generate a false centroid result. The noise
    *  threshold should be set carefully (high enough above the noise level) so
    *  that noise will not generate a false centroid.
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetCentroidPos(uint32 widget)
    {
        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
            const uint8 *diplex;
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
                
        #if (0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)
            uint8 posIndex;
            uint8 firstTimeIndex = `$INSTANCE_NAME`_posFiltersData[widget];
            uint8 posFiltersMask = `$INSTANCE_NAME`_posFiltersMask[widget];  
        #endif /* (0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK) */

        #if ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
             (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)))
            uint8 tempPos;
        #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
               *   (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)))
               */

        uint8 maximum;
        uint16 position;
        uint8 offset = `$INSTANCE_NAME`_rawDataIndex[widget];
        uint8 count = `$INSTANCE_NAME`_numberOfSensors[widget];
                        
        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
            if(widget < `$INSTANCE_NAME`_TOTAL_DIPLEXED_SLIDERS_COUNT)
            {
                maximum = `$INSTANCE_NAME`_diplexTable[widget];
                diplex = &`$INSTANCE_NAME`_diplexTable[maximum];
            }
            else
            {
                diplex = 0u;
            }
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

		/* Find Maximum within centroid */      
		#if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)        
			maximum = `$INSTANCE_NAME`_FindMaximum(offset, count, (`$SizeReplacementString`)`$INSTANCE_NAME`_fingerThreshold[widget], diplex);
		#else
			maximum = `$INSTANCE_NAME`_FindMaximum(offset, count, (`$SizeReplacementString`)`$INSTANCE_NAME`_fingerThreshold[widget]);
		#endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

        if (maximum != 0xFFu)
        {
            /* Calculate centroid */
            position = (uint16) `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidLinearSliderCallReplacementString`maximum, 
                         offset, count, `$INSTANCE_NAME`_centroidMult[widget], `$INSTANCE_NAME`_noiseThreshold[widget]);

            #if (0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)
                /* Check if this linear slider has enabled filters */
                if (0u != (posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER))
                {
                    /* Calculate position to store filters data */
                    posIndex  = firstTimeIndex + 1u;
                    
                    if (0u == `$INSTANCE_NAME`_posFiltersData[firstTimeIndex])
                    {
                        /* Init filters */
                        `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                        #if ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                                     `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
                             (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                     `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)))

                            if ( (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER)) || 
                                 (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
                            {
                                `$INSTANCE_NAME`_posFiltersData[posIndex + 1u] = (uint8) position;
                            }
                        #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                               *           `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)) || \
                               *   (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                               *           `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)))
                               */
                        
                        `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 1u;
                    }
                    else
                    {
                        /* Do filtering */
                        #if (0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = `$INSTANCE_NAME`_MedianFilter(position,
                                                                (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex],
                                                                (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex + 1u]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex + 1u] =
                                                                             `$INSTANCE_NAME`_posFiltersData[posIndex];
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /*(0u != (`$INSTANCE_NAME`_MEDIAN_FILTER &
                               *         `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if(0u!=(`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER)) 
                            {
                                tempPos = (uint8) position;
                                position = `$INSTANCE_NAME`_AveragingFilter(position,
                                                                (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex],
                                                                (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex + 1u]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex+1u]=`$INSTANCE_NAME`_posFiltersData[posIndex];
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                               *           `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_IIR2_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)) 
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR2_FILTER)) 
                            {
                                position = `$INSTANCE_NAME`_IIR2Filter(position,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_IIR2_FILTER & \
                               *          `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_IIR4_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR4_FILTER))
                            {
                                position = `$INSTANCE_NAME`_IIR4Filter(position,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }                                
                        #endif /* (0u != (`$INSTANCE_NAME`_IIR4_FILTER & \
                               *          `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_JITTER_FILTER & `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_JITTER_FILTER))
                            {
                                position = `$INSTANCE_NAME`_JitterFilter(position,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_JITTER_FILTER & \
                               *           `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK))
                               */
                    }
                }
            #endif /* (0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK) */

        }
        else
        {
            /* Maximum wasn't found */
            position = 0xFFFFu;

            #if(0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK)
                /* Reset filters */
                if(0u != (posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER))
                {
                    `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 0u;
                }
            #endif /* (0u != `$INSTANCE_NAME`_LINEAR_SLIDERS_POS_FILTERS_MASK) */
        }

        
        return (position);
    }
#endif /* ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */


#if((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetRadialCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  Checks the `$INSTANCE_NAME`_Signal[ ] array for a centroid within
    *  a slider specified range. The centroid position is calculated according to the resolution
    *  specified in the CapSense customizer. The position filters are applied to the
    *  result if enabled.
    *
    * Parameters:
    *  widget:  Widget number.
    *  For every radial slider widget there are defines in this format:
    *  #define `$INSTANCE_NAME`_"widget_name"__RS           5
    * 
    * Return:
    *  Returns a position value of the radial slider.
    *
	* Global Variables:
	*  None.
	*
    * Side Effects:
    *  If any sensor within the slider widget is active, the function returns values
    *  from zero to the API resolution value set in the CapSense customizer. If no
    *  sensors are active, the function returns 0xFFFF.
    *  There are no checks of the widget type argument provided to this function.
    *  The unproper widget type provided will cause unexpected position calculations.
    *
    * Note:
    *  If noise counts on the slider segments are greater than the noise
    *  threshold, this subroutine may generate a false centroid result. The noise
    *  threshold should be set carefully (high enough above the noise level) so 
    *  that noise will not generate a false centroid.
    *
    *******************************************************************************/
     uint16 `$INSTANCE_NAME`_GetRadialCentroidPos(uint32 widget)
    {
        #if (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)
            uint8 posIndex;
            uint8 firstTimeIndex = `$INSTANCE_NAME`_posFiltersData[widget];
            uint8 posFiltersMask = `$INSTANCE_NAME`_posFiltersMask[widget]; 
        #endif /* (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK) */

        #if ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
             (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)))
            uint8 tempPos;
        #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
               *   (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)))
               */

        uint8 maximum;
        uint16 position;
        uint8 offset = `$INSTANCE_NAME`_rawDataIndex[widget];
        uint8 count = `$INSTANCE_NAME`_numberOfSensors[widget];

		/* Find Maximum within centroid */      
		#if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)        
			maximum = `$INSTANCE_NAME`_FindMaximum(offset, count, (`$SizeReplacementString`)`$INSTANCE_NAME`_fingerThreshold[widget], 0u);
		#else
			maximum = `$INSTANCE_NAME`_FindMaximum(offset, count, (`$SizeReplacementString`)`$INSTANCE_NAME`_fingerThreshold[widget]);
		#endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */
        
        if (maximum != `$INSTANCE_NAME`_MAXIMUM_CENTROID)
        {
            /* Calculate centroid */
            position = (uint16) `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidRadialSliderCallReplacementString`maximum, 
                         offset, count, `$INSTANCE_NAME`_centroidMult[widget], `$INSTANCE_NAME`_noiseThreshold[widget]);

            #if (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)
                /* Check if this Radial slider has enabled filters */
                if (0u != (posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER))
                {
                    /* Calculate position to store filters data */
                    posIndex  = firstTimeIndex + 1u;
                    
                    if (0u == `$INSTANCE_NAME`_posFiltersData[firstTimeIndex])
                    {
                        /* Init filters */
                        `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                        #if ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                                     `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
                             (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                     `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)))

                            if ( (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER))  || 
                                 (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
                            {
                                `$INSTANCE_NAME`_posFiltersData[posIndex + 1u] = (uint8) position;
                            }
                        #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                               *           `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)) || \
                               *   (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                               *           `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)))
                               */
                        
                        `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 1u;
                    }
                    else
                    {
                        /* Do filtering */
                        #if (0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = `$INSTANCE_NAME`_MedianFilter(position,
                                                                        `$INSTANCE_NAME`_posFiltersData[posIndex],
                                                                        `$INSTANCE_NAME`_posFiltersData[posIndex + 1u]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex + 1u] = 
                                                                              `$INSTANCE_NAME`_posFiltersData[posIndex];
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & 
                               *          `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                    `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER))
                            {
                                tempPos = (uint8) position;
                                position = `$INSTANCE_NAME`_AveragingFilter(position, 
                                                                       `$INSTANCE_NAME`_posFiltersData[posIndex],
                                                                       `$INSTANCE_NAME`_posFiltersData[posIndex + 1u]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex+1u]= `$INSTANCE_NAME`_posFiltersData[posIndex];
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = tempPos;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                               *          `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_IIR2_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR2_FILTER))
                            {
                                position = `$INSTANCE_NAME`_IIR2Filter(position,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_IIR2_FILTER & 
                               *          `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_IIR4_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR4_FILTER))
                            {
                                position = `$INSTANCE_NAME`_IIR4Filter(position,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_IIR4_FILTER & 
                               *          `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */

                        #if (0u != (`$INSTANCE_NAME`_JITTER_FILTER & `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                            if (0u != (posFiltersMask & `$INSTANCE_NAME`_JITTER_FILTER))
                            {
                                position = `$INSTANCE_NAME`_JitterFilter(position, 
                                                                         `$INSTANCE_NAME`_posFiltersData[posIndex]);
                                `$INSTANCE_NAME`_posFiltersData[posIndex] = (uint8) position;
                            }
                        #endif /* (0u != (`$INSTANCE_NAME`_JITTER_FILTER &
                               *           `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK))
                               */
                    }
                }
            #endif /* (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK) */

        }
        else
        {
            /* Maximum wasn't found?? */
            position = 0xFFFFu;

            #if (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK)
                /* Reset filters */
                if((posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER) != 0u)
                {
                    `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 0u;
                }
            #endif /* (0u != `$INSTANCE_NAME`_RADIAL_SLIDERS_POS_FILTERS_MASK) */
        }
        
        return (position);
    }
#endif /* ((`$INSTANCE_NAME`_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (`$INSTANCE_NAME`_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */


#if(`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetTouchCentroidPos
    ********************************************************************************
    *
    * Summary:
    *  If a finger is present on a touchpad, this function calculates the X and Y
    *  position of the finger by calculating the centroids within touchpad specified
    *  range. The X and Y positions are calculated according to the API resolutions set in the
    *  CapSense customizer. Returns 1 if a finger is on the touchpad.
    *  The position filter is applied to the result if enabled.
    *  This function is available only if a touch pad is defined by the CapSense
    *  customizer.
    *
    * Parameters:
    *  widget:  Widget number. 
    *  For every touchpad widget there are defines in this format:
    *  #define `$INSTANCE_NAME`_"widget_name"__TP            5
    *
    *  pos:     Pointer to the array of two uint16 elements, where result
    *  result of calculation of X and Y position are stored.
    *  pos[0u]  - position of X
    *  pos[1u]  - position of Y
    *
    * Return:
    *  Returns a 1 if a finger is on the touch pad, 0 - if not.
	*
	* Global Variables:
	*  None.
	*
    * Side Effects:
    *   There are no checks of the widget type argument provided to this function.
    *   The unproper widget type provided will cause unexpected position
    *   calculations.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetTouchCentroidPos(uint32 widget, uint16* pos)
    {
        #if (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)
            uint8 posXIndex;
            uint8 posYIndex;
            uint8 firstTimeIndex = `$INSTANCE_NAME`_posFiltersData[widget];
            uint8 posFiltersMask = `$INSTANCE_NAME`_posFiltersMask[widget];
        #endif /* (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK) */

        #if ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)) || \
             (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)))
            uint16 tempPos;
        #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)) || \
               *   (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)))
               */

        uint8 MaxX;
        uint8 MaxY;
        uint8 posX;
        uint8 posY;
        uint32 touch = 0u;
        uint8 offset = `$INSTANCE_NAME`_rawDataIndex[widget];
        uint8 count = `$INSTANCE_NAME`_numberOfSensors[widget];
        
        /* Find Maximum within X centroid */
        #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
            MaxX = `$INSTANCE_NAME`_FindMaximum(offset, count, `$INSTANCE_NAME`_fingerThreshold[widget], 0u);
        #else
            MaxX = `$INSTANCE_NAME`_FindMaximum(offset, count, `$INSTANCE_NAME`_fingerThreshold[widget]);
        #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

        if (MaxX != `$INSTANCE_NAME`_MAXIMUM_CENTROID)
        {
            offset = `$INSTANCE_NAME`_rawDataIndex[widget + 1u];
            count = `$INSTANCE_NAME`_numberOfSensors[widget + 1u];

            /* Find Maximum within Y centroid */
            #if (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER)
                MaxY = `$INSTANCE_NAME`_FindMaximum(offset, count, `$INSTANCE_NAME`_fingerThreshold[widget + 1u], 0u);
            #else
                MaxY = `$INSTANCE_NAME`_FindMaximum(offset, count, `$INSTANCE_NAME`_fingerThreshold[widget + 1u]);
            #endif /* (`$INSTANCE_NAME`_IS_DIPLEX_SLIDER) */

            if (MaxY != `$INSTANCE_NAME`_MAXIMUM_CENTROID)
            {
                /* X and Y maximums are found = true touch */
                touch = 1u;
                
                /* Calculate Y centroid */
                posY = `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidTouchPadCallReplacementString`MaxY, offset, count, 
                            `$INSTANCE_NAME`_centroidMult[widget + 1u], `$INSTANCE_NAME`_noiseThreshold[widget + 1u]);
                
                /* Calculate X centroid */
                offset = `$INSTANCE_NAME`_rawDataIndex[widget];
                count = `$INSTANCE_NAME`_numberOfSensors[widget];
                
                posX = `$INSTANCE_NAME`_CalcCentroid(`$CalcCentroidTouchPadCallReplacementString`MaxX, offset, count, 
                            `$INSTANCE_NAME`_centroidMult[widget],`$INSTANCE_NAME`_noiseThreshold[widget]);
    
                #if (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)
                    /* Check if this TP has enabled filters */
                    if (0u != (posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER))
                    {
                        /* Calculate position to store filters data */
                        posXIndex  = firstTimeIndex + 1u;
                        posYIndex  = `$INSTANCE_NAME`_posFiltersData[widget + 1u];
                        
                        if (0u == `$INSTANCE_NAME`_posFiltersData[firstTimeIndex])
                        {
                            /* Init filters */
                            `$INSTANCE_NAME`_posFiltersData[posXIndex] = posX;
                            `$INSTANCE_NAME`_posFiltersData[posYIndex] = posY;

                            #if((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                                        `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))|| \
                                (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                        `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)))

                                if ( (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER)) || 
                                     (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
                                {
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex + 1u] = posX;
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex + 1u] = posY;
                                }
                            #endif /* ((0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                                   *           `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)) || \
                                   *    (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                   *            `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)))
                                   */
                            
                            `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 1u;
                        }
                        else
                        {
                            /* Do filtering */
                            #if (0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & `$INSTANCE_NAME`_MEDIAN_FILTER))
                                {
                                    tempPos = posX;
                                    posX = (uint8) `$INSTANCE_NAME`_MedianFilter(posX,
                                                                      `$INSTANCE_NAME`_posFiltersData[posXIndex],
                                                                      `$INSTANCE_NAME`_posFiltersData[posXIndex + 1u]);
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex + 1u] = 
                                                                             `$INSTANCE_NAME`_posFiltersData[posXIndex];
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex] = tempPos;
                                    
                                    tempPos = posY;
                                    posY = (uint8) `$INSTANCE_NAME`_MedianFilter(posY,
                                                                       `$INSTANCE_NAME`_posFiltersData[posYIndex], 
                                                                       `$INSTANCE_NAME`_posFiltersData[posYIndex + 1u]);
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex + 1u] = 
                                                                             `$INSTANCE_NAME`_posFiltersData[posYIndex];
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex] = tempPos;
                                }
                                
                            #endif /* (0u != (`$INSTANCE_NAME`_MEDIAN_FILTER & \
                                   *          `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if(0u !=(`$INSTANCE_NAME`_AVERAGING_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & `$INSTANCE_NAME`_AVERAGING_FILTER))
                                {
                                    tempPos = posX;
                                    posX = (uint8) `$INSTANCE_NAME`_AveragingFilter(posX,
                                                                       `$INSTANCE_NAME`_posFiltersData[posXIndex], 
                                                                       `$INSTANCE_NAME`_posFiltersData[posXIndex + 1u]);
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex + 1u] = 
                                                                             `$INSTANCE_NAME`_posFiltersData[posXIndex];
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex] = tempPos;
                                    
                                    tempPos = posY;
                                    posY = (uint8) `$INSTANCE_NAME`_AveragingFilter(posY, 
                                                                      `$INSTANCE_NAME`_posFiltersData[posYIndex], 
                                                                      `$INSTANCE_NAME`_posFiltersData[posYIndex + 1u]);
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex + 1u] = 
                                                                            `$INSTANCE_NAME`_posFiltersData[posYIndex];
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex] = tempPos;
                                }

                            #endif /* (0u != (`$INSTANCE_NAME`_AVERAGING_FILTER & \
                                   *           `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (`$INSTANCE_NAME`_IIR2_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR2_FILTER))
                                {
                                    posX = (uint8) `$INSTANCE_NAME`_IIR2Filter(posX, 
                                                                           `$INSTANCE_NAME`_posFiltersData[posXIndex]);
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex] = posX;
                                    
                                    posY = (uint8) `$INSTANCE_NAME`_IIR2Filter(posY, 
                                                                            `$INSTANCE_NAME`_posFiltersData[posYIndex]);
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex] = posY;
                                }
                                
                            #endif /* (0u != (`$INSTANCE_NAME`_IIR2_FILTER & \
                                   *          `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (`$INSTANCE_NAME`_IIR4_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & `$INSTANCE_NAME`_IIR4_FILTER))
                                {
                                    posX = (uint8) `$INSTANCE_NAME`_IIR4Filter((uint16)posX,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posXIndex]);
                                    `$INSTANCE_NAME`_posFiltersData[posXIndex] = posX;

                                    posY = (uint8) `$INSTANCE_NAME`_IIR4Filter((uint16)posY,
                                                                    (uint16)`$INSTANCE_NAME`_posFiltersData[posYIndex]);
                                    `$INSTANCE_NAME`_posFiltersData[posYIndex] = posY;
                                }
                                
                            #endif /* (0u != (`$INSTANCE_NAME`_IIR4_FILTER & \
                                   *           `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                   */

                            #if (0u != (`$INSTANCE_NAME`_JITTER_FILTER & `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                if (0u != (posFiltersMask & `$INSTANCE_NAME`_JITTER_FILTER))
                                    {
                                        posX = (uint8) `$INSTANCE_NAME`_JitterFilter(posX, 
                                                                            `$INSTANCE_NAME`_posFiltersData[posXIndex]);
                                        `$INSTANCE_NAME`_posFiltersData[posXIndex] = posX;
                                        
                                        posY = (uint8) `$INSTANCE_NAME`_JitterFilter(posY, 
                                                                            `$INSTANCE_NAME`_posFiltersData[posYIndex]);
                                        `$INSTANCE_NAME`_posFiltersData[posYIndex] = posY;
                                    }
                            #endif /* (0u != (`$INSTANCE_NAME`_JITTER_FILTER & \
                                   *           `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK))
                                   */
                        }
                    }
                #endif /* (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK) */

                /* Save positions */
                pos[0u] = posX;
                pos[1u] = posY;
            }
        }

        #if (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK)
            if(touch == 0u)
            {
                /* Reset filters */
                if ((posFiltersMask & `$INSTANCE_NAME`_ANY_POS_FILTER) != 0u)
                {
                    `$INSTANCE_NAME`_posFiltersData[firstTimeIndex] = 0u;
                }
            }
        #endif /* (0u != `$INSTANCE_NAME`_TOUCH_PADS_POS_FILTERS_MASK) */
        
        return (touch);
    }
#endif /* (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT > 0u) */


#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_MedianFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Median filter function. 
    *  The median filter looks at the three most recent samples and reports the 
    *  median value.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *  x3:  Before previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3)
    {
        uint16 tmp;
        
        if (x1 > x2)
        {
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        
        if (x2 > x3)
        {
            x2 = x3;
        }
        
        return ((x1 > x2) ? x1 : x2);
    }
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER)) || \
      ((`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)) ) */


#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER)) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_AveragingFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Averaging filter function.
    *  The averaging filter looks at the three most recent samples of a position and
    *  reports the averaging value.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *  x3:  Before previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_AveragingFilter(uint16 x1, uint16 x2, uint16 x3)
    {
        uint32 tmp = ((uint32)x1 + (uint32)x2 + (uint32)x3) / 3u;
        
        return ((uint16) tmp);
    }
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) ) */


#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR2Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/2 filter function. IIR1/2 = 1/2current + 1/2previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR2Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/2 Current Value+ 1/2 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp >>= 1u;
    
        return ((uint16) tmp);
    }
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) || \
       *    (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER)) )
       */


#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR4Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/4 filter function. IIR1/4 = 1/4current + 3/4previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns a filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR4Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/4 Current Value + 3/4 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp += ((uint32)x2 << 1u);
        tmp >>= 2u;
        
        return ((uint16) tmp);
    }
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) || \
       *    (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER)) )
       */


#if ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
      (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) )
    /*******************************************************************************
    * Function Name: uint16 `$INSTANCE_NAME`_JitterFilter
    ********************************************************************************
    *
    * Summary:
    *  This is the Jitter filter function.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_JitterFilter(uint16 x1, uint16 x2)
    {
        if (x1 > x2)
        {
            x1--;
        }
        else
        {
            if (x1 < x2)
            {
                x1++;
            }
        }
    
        return x1;
    }
#endif /* ( (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) || \
       *    (0u != (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER)) )
       */


#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR8Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/8 filter function. IIR1/8 = 1/8current + 7/8previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR8Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/8 Current Value + 7/8 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 3u) - ((uint32)x2));
        tmp >>= 3u;
    
        return ((uint16) tmp);
    }
#endif /* (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)) */


#if (0u != (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR16Filter
    ********************************************************************************
    *
    * Summary:
    *  This is the IIR1/16 filter function. IIR1/16 = 1/16current + 15/16previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
	*
	* Global Variables:
	*  None.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR16Filter(uint16 x1, uint16 x2)
    {
        uint32 tmp;
        
        /* IIR = 1/16 Current Value + 15/16 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 4u) - ((uint32)x2));
        tmp >>= 4u;
        
        return ((uint16) tmp);
    }
#endif /* (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER) */


#if (0u != (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT))

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetMatrixButtonPos
    ********************************************************************************
    *
    * Summary:
    *  Function calculates and returns a touch position (column and row) for the matrix
    *  button widget.
    *
    * Parameters:
    *  widget:  widget number;
    *  pos:     pointer to an array of two uint8, where touch position will be 
    *           stored:
    *           pos[0] - column position;
    *           pos[1] - raw position.
    *
    * Return:
    *  Returns 1 if row and column sensors of matrix button are active, 0 - in other
    *  cases.
	*
	* Global Variables:
	*  `$INSTANCE_NAME`_fingerThreshold[ ] – used to store the finger threshold for all widgets.
	*  `$INSTANCE_NAME`_sensorSignal[ ] – used to store a difference between the current value of 
	*  raw data and a previous value of the baseline.
	*
	* Side Effects:
	*  None
	* 
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetMatrixButtonPos(uint32 widget, uint8* pos)
    {
        uint8 i;
        uint32 retVal = 0u;
        uint16 row_sig_max = 0u;
        uint16 col_sig_max = 0u;
        uint8 row_ind = 0u;
        uint8 col_ind = 0u;

        if (`$INSTANCE_NAME`_CheckIsWidgetActive(widget) == 1u)
        {
            /* Find row number with maximal signal value */
            for(i = `$INSTANCE_NAME`_rawDataIndex[widget]; i < (`$INSTANCE_NAME`_rawDataIndex[widget] + \
                 `$INSTANCE_NAME`_numberOfSensors[widget]); i++)
            {
                if (`$INSTANCE_NAME`_sensorSignal[i] > col_sig_max)
                {
                    col_ind = i;
                    col_sig_max = `$INSTANCE_NAME`_sensorSignal[i];
                }
            }

            /* Find row number with maximal signal value */
            for(i = `$INSTANCE_NAME`_rawDataIndex[widget+1u]; i < (`$INSTANCE_NAME`_rawDataIndex[widget+1u] + \
                 `$INSTANCE_NAME`_numberOfSensors[widget+1u]); i++)
            {
                if (`$INSTANCE_NAME`_sensorSignal[i] > row_sig_max)
                {
                    row_ind = i;
                    row_sig_max = `$INSTANCE_NAME`_sensorSignal[i];
                }
            }

            if((col_sig_max >= `$INSTANCE_NAME`_fingerThreshold[widget]) && \
               (row_sig_max >= `$INSTANCE_NAME`_fingerThreshold[widget+1u]))
            {
                pos[0u] = col_ind - `$INSTANCE_NAME`_rawDataIndex[widget];
                pos[1u] = row_ind - `$INSTANCE_NAME`_rawDataIndex[widget+1u];
                retVal = 1u;
            }
        }
        return (retVal);
    }

#endif /* (0u != (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetWidgetNumber
********************************************************************************
*
* Summary:
*  This API returns the widget number for the sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the widget number for the sensor. 
*
* Global Variables:
*  `$INSTANCE_NAME`_widgetNumber[]  - stores widget numbers.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetWidgetNumber(uint32 sensor)
{
	return((uint32)`$INSTANCE_NAME`_widgetNumber[sensor]);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetLowBaselineReset
********************************************************************************
*
* Summary:
*  This API returns the low baseline reset threshold value for the  sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  low baseline reset threshold value a sensor.
*
* Global Variables:
*  `$INSTANCE_NAME`_lowBaselineReset[]  - stores low baseline reset values.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetLowBaselineReset(uint32 sensor)
{
	return(`$INSTANCE_NAME`_lowBaselineReset[sensor]);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDebounce
********************************************************************************
*
* Summary:
*  This API returns a debounce value.
*
* Parameters:
*  sensor: sensor index. The value of index can be 
*  from 0 to (`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  Debounce value 
*
* Global Variables:
*  `$INSTANCE_NAME`_debounce[]  - stores the debounce value.
* 
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetDebounce(uint32 widget)
{
	return(`$INSTANCE_NAME`_debounce[widget]);
}

/* [] END OF FILE */
