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
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_CSHL.h"

/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
    extern void `$INSTANCE_NAME`_CalculateThresholds(uint8 SensorNumber);
#endif /* End (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */

/* Median filter function prototype */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) )
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3) \
    `=ReentrantKeil($INSTANCE_NAME . "_MedianFilter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* Averaging filter function prototype */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) )
    uint16 `$INSTANCE_NAME`_AveragingFilter(uint16 x1, uint16 x2, uint16 x3) \
    `=ReentrantKeil($INSTANCE_NAME . "_AveragingFilter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER) )
uint16 `$INSTANCE_NAME`_IIR2Filter(uint16 x1, uint16 x2) `=ReentrantKeil($INSTANCE_NAME . "_IIR2Filter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER) )
    uint16 `$INSTANCE_NAME`_IIR4Filter(uint16 x1, uint16 x2) `=ReentrantKeil($INSTANCE_NAME . "_IIR4Filter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)
    uint16 `$INSTANCE_NAME`_IIR8Filter(uint16 x1, uint16 x2) `=ReentrantKeil($INSTANCE_NAME . "_IIR8Filter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER)
    uint16 `$INSTANCE_NAME`_IIR16Filter(uint16 x1, uint16 x2) `=ReentrantKeil($INSTANCE_NAME . "_IIR16Filter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER) )
    uint16 `$INSTANCE_NAME`_JitterFilter(uint16 x1, uint16 x2) `=ReentrantKeil($INSTANCE_NAME . "_JitterFilter")`;
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */

/* Storage of filters data */
#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
      (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) )

    uint16 `$INSTANCE_NAME`_rawFilterData1[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    uint16 `$INSTANCE_NAME`_rawFilterData2[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#elif ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)   || \
        (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)   || \
        (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER) || \
        (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)   || \
        (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER) )
        
    uint16 `$INSTANCE_NAME`_rawFilterData1[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

#else
    /* No Raw filters */
#endif  /* End `$INSTANCE_NAME`_RAW_FILTER_MASK */

extern uint16 `$INSTANCE_NAME`_SensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8 `$INSTANCE_NAME`_SensorEnableMask[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
extern const uint8 CYCODE `$INSTANCE_NAME`_widgetNumber[];

uint16 `$INSTANCE_NAME`_SensorBaseline[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
uint8 `$INSTANCE_NAME`_SensorBaselineLow[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
`$SignalSizeReplacementString` `$INSTANCE_NAME`_SensorSignal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};
uint8 `$INSTANCE_NAME`_SensorOnMask[(((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {0u};

/* Helps while centroid calulation */
#if (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
    static `$SignalSizeReplacementString` `$INSTANCE_NAME`_centroid[3];
#endif  /* End (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */


`$writerCSHLCVariables`

#if (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT)
    uint8 `$INSTANCE_NAME`_position[`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT] = {0xFFu};
#endif  /* End (`$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BaseInit
********************************************************************************
*
* Summary:
*  Loads the `$INSTANCE_NAME`_SensorBaseline[sensor] array element with an 
*  initial value which qual raw count value. 
*  Resets to zero `$INSTANCE_NAME`_SensorBaselineLow[senesor] and 
*  `$INSTANCE_NAME`_SensorSignal[sensor] array element.
*  Loads `$INSTANCE_NAME`_debounceCounter[sensor] array element with initial 
*  value equal `$INSTANCE_NAME`_debounce[].
*  Loads the `$INSTANCE_NAME`_rawFilterData2[sensor] and 
*  `$INSTANCE_NAME`_rawFilterData2[sensor] array element with an 
*  initial value which qual raw count value if raw data filter is enabled.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorBaseline[]    - used to store baseline value.
*  `$INSTANCE_NAME`_SensorBaselineLow[] - used to store fraction byte of 
*  baseline value.
*  `$INSTANCE_NAME`_SensorSignal[]      - used to store diffence between 
*  current value of raw data and previous value of baseline.
*  `$INSTANCE_NAME`_debounceCounter[]   - used to store current debounce 
*  counter of sensor. Widget which has this parameter are buttons, matrix 
*  buttons, proximity, guard. All other widgets haven't debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  `$INSTANCE_NAME`_rawFilterData1[]    - used to store previous sample of 
*  any enabled raw data filter.
*  `$INSTANCE_NAME`_rawFilterData2[]    - used to store before previous sample
*  of enabled raw data filter. Only required for median or average filters.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_BaseInit(uint8 sensor)
{
    #if ((`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT) || (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) || \
         (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT))
        uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    #endif /* ((`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) || (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)) */
    
    #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8 debounceIndex;
    #endif  /* End (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT != 0u) */
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
        {
    #endif  /* End `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
    
    /* Initialize Baseline */
    `$INSTANCE_NAME`_SensorBaseline[sensor] = `$INSTANCE_NAME`_SensorRaw[sensor];
    `$INSTANCE_NAME`_SensorBaselineLow[sensor] = 0u;
    `$INSTANCE_NAME`_SensorSignal[sensor] = 0u;
        
`$writerCSHLDebounceInit`
    
    #if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
          (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) )
    
        `$INSTANCE_NAME`_rawFilterData1[sensor] = `$INSTANCE_NAME`_SensorRaw[sensor];
        `$INSTANCE_NAME`_rawFilterData2[sensor] = `$INSTANCE_NAME`_SensorRaw[sensor];
    
    #elif ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER)   || \
            (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER)   || \
            (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER) || \
            (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)   || \
            (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER) )
            
        `$INSTANCE_NAME`_rawFilterData1[sensor] = `$INSTANCE_NAME`_SensorRaw[sensor];
    
    #else
        /* No Raw filters */
    #endif  /* End `$INSTANCE_NAME`_RAW_FILTER_MASK */
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* End `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeSensorBaseline
********************************************************************************
*
* Summary:
*  Loads the `$INSTANCE_NAME`_SensorBaseline[sensor] array element with an 
*  initial value by scanning the selected sensor (one channel design) or pair 
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
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeSensorBaseline(uint8 sensor)
{
    /* Scan sensor */
    `$INSTANCE_NAME`_ScanSensor(sensor);
        while(`$INSTANCE_NAME`_IsBusy() != 0u) {;}
    
    #if (`$INSTANCE_NAME`_DESIGN_TYPE == `$INSTANCE_NAME`_ONE_CHANNEL_DESIGN)
        /* Initialize Baseline, Signal and debounce counters */       
        `$INSTANCE_NAME`_BaseInit(sensor);
        
    #else
    
        if(sensor < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT__CH0)
        {
            /* Initialize Baseline, Signal and debounce counters */ 
            `$INSTANCE_NAME`_BaseInit(sensor);
        }
        
        if(sensor < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT__CH1)
        {
            /* Initialize Baseline, Signal and debounce counters */
            `$INSTANCE_NAME`_BaseInit(sensor + `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT__CH0);
        }
    
    #endif  /* End (`$INSTANCE_NAME`_DESIGN_TYPE == `$INSTANCE_NAME`_ONE_CHANNEL_DESIGN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeAllBaselines
********************************************************************************
*
* Summary:
*  Uses the `$INSTANCE_NAME`_InitializeSensorBaseline function to loads the 
*  `$INSTANCE_NAME`_SensorBaseline[] array with an initial values by scanning 
*  all sensors. The raw count values are copied into the baseline array for 
*  all sensors. The raw data filters are initialized if enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeAllBaselines(void)
{
    uint8 i;
    
    /* The baseline initialize by sensor of sensor pair */
    for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT; i++)
    {
        `$INSTANCE_NAME`_InitializeSensorBaseline(i);
    }
}


#if (`$INSTANCE_NAME`_DESIGN_TYPE == `$INSTANCE_NAME`_TWO_CHANNELS_DESIGN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitializeEnabledBaselines
    ********************************************************************************
    *
    * Summary:
    *  Scans all enabled widgets and the raw count values are copied into the 
    *  baseline array for all sensors enabled in scanning process. Baselines 
    *  initialize with zero values for sensors disabled from scanning process. 
    *  The raw data filters are initialized if enabled.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_InitializeEnabledBaselines(void)
    {
        uint8 i;
        uint8 pos;
        uint8 enMask;
        
        `$INSTANCE_NAME`_ScanEnabledWidgets();
        while(`$INSTANCE_NAME`_IsBusy() != 0u){;}
        
        for(i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
        {
            pos = (i >> 3u);
            enMask = 0x01u << (i & 0x07u);
            
            /* Clear raw data if sensor is disabled from scanning process */
            if((`$INSTANCE_NAME`_SensorEnableMask[pos] & enMask) == 0u)
            {
                `$INSTANCE_NAME`_SensorRaw[i] = 0u;
            }
            
            /* Initialize baselines */
            `$INSTANCE_NAME`_BaseInit(i);
        }
    }  
#endif  /* End (`$INSTANCE_NAME`_DESIGN_TYPE == `$INSTANCE_NAME`_TWO_CHANNELS_DESIGN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateSensorBaseline
********************************************************************************
*
* Summary:
*  Updates the `$INSTANCE_NAME`_SensorBaseline[sensor] array element using the 
*  LP filter with k = 256. The signal calculates the difference of count by 
*  subtracting the previous baseline from the current raw count value and stores
*  it in `$INSTANCE_NAME`_SensorSignal[sensor]. 
*  If auto reset option is enabled the baseline updated regards noise threshold. 
*  If auto reset option is disabled the baseline stops updating if signal is 
*  greater that zero and baseline loads with raw count value if signal is less 
*  that noise threshold.
*  Raw data filters are applied to the values if enabled before baseline 
*  calculation.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorBaseline[]    - used to store baseline value.
*  `$INSTANCE_NAME`_SensorBaselineLow[] - used to store fraction byte of 
*  baseline value.
*  `$INSTANCE_NAME`_SensorSignal[]      - used to store diffence between 
*  current value of raw data and previous value of baseline.
*  `$INSTANCE_NAME`_rawFilterData1[]    - used to store previous sample of 
*  any enabled raw data filter.
*  `$INSTANCE_NAME`_rawFilterData2[]    - used to store before previous sample
*  of enabled raw data filter. Only required for median or average filters.
*
* Reentrant:
*  No
*
*******************************************************************************/
 void `$INSTANCE_NAME`_UpdateSensorBaseline(uint8 sensor)
{
    uint32 calc;
    uint16 tempRaw;
    uint16 filteredRawData;
    uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    uint8 noiseThreshold = `$INSTANCE_NAME`_noiseThreshold[widget];
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        if(widget < `$INSTANCE_NAME`_END_OF_WIDGETS_INDEX)
        {
    #endif  /* End `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
    
    filteredRawData = `$INSTANCE_NAME`_SensorRaw[sensor];
    
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
    #endif  /* End `$INSTANCE_NAME`_RAW_FILTER_MASK */
    
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
        `$INSTANCE_NAME`_CalculateThresholds(sensor);
    #endif /* End (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */
    
    /* Baseline calculation */
    #if (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE)
        
        /* Calculate difference RawData[cur] - Baseline[prev] */
        if(filteredRawData >= `$INSTANCE_NAME`_SensorBaseline[sensor])
        {
            tempRaw = filteredRawData - `$INSTANCE_NAME`_SensorBaseline[sensor];
            widget = 1u;        /* Positive difference */
        }
        else
        {
            tempRaw = `$INSTANCE_NAME`_SensorBaseline[sensor] - filteredRawData;
            widget = 0u;        /* Negative difference */
        }
        
        /* Update Baseline if lower that noiseThreshold */
        if (tempRaw <= (uint16) noiseThreshold)
        {
            /* Make full Baseline 23 bits */
            calc = (uint32) `$INSTANCE_NAME`_SensorBaseline[sensor] << 8u;
            calc |= (uint32) `$INSTANCE_NAME`_SensorBaselineLow[sensor];
            
            /* Add Raw Data to Baseline */
            calc += filteredRawData;
            
            /* Sub the high Baseline */
            calc -= `$INSTANCE_NAME`_SensorBaseline[sensor];
            
            /* Put Baseline and BaselineLow */
            `$INSTANCE_NAME`_SensorBaseline[sensor] = ((uint16) (calc >> 8u));
            `$INSTANCE_NAME`_SensorBaselineLow[sensor] = ((uint8) calc);
            
            /* Signal is zero */
            `$INSTANCE_NAME`_SensorSignal[sensor] = 0u;
        }
        /* Calculate Signal if possitive difference > noiseThreshold */
        else if (widget != 0u)
        {
            #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
                /* Over flow defence for uint8 */
                if (tempRaw > 0xFFu)
                {
                    `$INSTANCE_NAME`_SensorSignal[sensor] = 0xFFu;
                }    
                else 
                {
                    `$INSTANCE_NAME`_SensorSignal[sensor] = ((uint8) tempRaw);
                }
            #else
                `$INSTANCE_NAME`_SensorSignal[sensor] = ((uint16) tempRaw);
                
            #endif  /* End `$INSTANCE_NAME`_SIGNAL_SIZE */
        }
        /* Reinitialize if negative difference > noiseThreshold */
        else
        {
            /* Baseline and BaselineLow re-init */
            `$INSTANCE_NAME`_SensorBaseline[sensor] = filteredRawData;
            `$INSTANCE_NAME`_SensorBaselineLow[sensor] = 0u;
            
            /* Signal is zero */
            `$INSTANCE_NAME`_SensorSignal[sensor] = 0u;
        }
    
    #else
        /* Calculate difference RawData[cur] - Baseline[prev] */
        if(filteredRawData >= `$INSTANCE_NAME`_SensorBaseline[sensor])
        {
            tempRaw = filteredRawData - `$INSTANCE_NAME`_SensorBaseline[sensor];
            widget = 1u;    /* Calculate the Signal */
        }
        else
        {
            tempRaw = `$INSTANCE_NAME`_SensorBaseline[sensor] - filteredRawData;
            widget = 0u;    /* Do NOT calculate the Signal */
        }
        
        if((tempRaw > (uint16) noiseThreshold) && (widget != 0u))
        {
            #if (`$INSTANCE_NAME`_SIGNAL_SIZE == `$INSTANCE_NAME`_SIGNAL_SIZE_UINT8)
                /* Over flow defence for uint8 */
                if (tempRaw > 0xFFu)
                {
                    `$INSTANCE_NAME`_SensorSignal[sensor] = 0xFFu;
                }    
                else 
                {
                    `$INSTANCE_NAME`_SensorSignal[sensor] = ((uint8) tempRaw);
                }
            #else
                `$INSTANCE_NAME`_SensorSignal[sensor] = ((uint16) tempRaw);
                
            #endif  /* End `$INSTANCE_NAME`_SIGNAL_SIZE */
        }
        else
        {
            /* Signal is zero */
            `$INSTANCE_NAME`_SensorSignal[sensor] = 0u;
        }
        
        /* Update Baseline */
        /* Make full Baseline 23 bits */
        calc = (uint32) `$INSTANCE_NAME`_SensorBaseline[sensor] << 8u;
        calc |= (uint32) `$INSTANCE_NAME`_SensorBaselineLow[sensor];
        
        /* Add Raw Data to Baseline */
        calc += filteredRawData;
        
        /* Sub the high Baseline */
        calc -= `$INSTANCE_NAME`_SensorBaseline[sensor];
        
        /* Put Baseline and BaselineLow */
        `$INSTANCE_NAME`_SensorBaseline[sensor] = ((uint16) (calc >> 8u));
        `$INSTANCE_NAME`_SensorBaselineLow[sensor] = ((uint8) calc);
     
    #endif  /* End (`$INSTANCE_NAME`_AUTO_RESET == `$INSTANCE_NAME`_AUTO_RESET_DISABLE) */
    
    #if (`$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)
        /* Exclude generic widget */
        }
    #endif  /* End `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateEnabledBaselines
********************************************************************************
*
* Summary:
*  Checks `$INSTANCE_NAME`_SensorEnableMask[] array and calls the 
*  `$INSTANCE_NAME`_UpdateSensorBaseline function to update the baselines 
*  for enabled sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_SensorEnableMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_SensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
*
* Reentrant:
*  No
*
*******************************************************************************/
 void `$INSTANCE_NAME`_UpdateEnabledBaselines(void)
{
    uint8 i;
    uint8 pos;
    uint8 enMask;
    
    for(i = 0; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        pos = (i >> 3u);
        enMask = 0x01u << (i & 0x07u);
        if((`$INSTANCE_NAME`_SensorEnableMask[pos] & enMask) != 0u)
        {
            `$INSTANCE_NAME`_UpdateSensorBaseline(i);
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsSensorActive
********************************************************************************
*
* Summary:
*  Compares the `$INSTANCE_NAME`_SensorSignal[sensor] array element to finger
*  threshold of widget it belongs to. The hysteresis and debounce are taken into 
*  account. The hysteresis is added or subtracted from the finger threshold 
*  based on whether the sensor is currently active. 
*  If the sensor is active, the threshold is lowered by the hysteresis amount.
*  If the sensor is inactive, the threshold is raised by the hysteresis amount.
*  The debounce counter added to the sensor active transition.
*  This function updates `$INSTANCE_NAME`_SensorOnMask[] array element.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns sensor state 1 if active, 0 if not active.
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorSignal[]      - used to store diffence between 
*  current value of raw data and previous value of baseline.
*  `$INSTANCE_NAME`_debounceCounter[]   - used to store current debounce 
*  counter of sensor. Widget which has this parameter are buttons, matrix 
*  buttons, proximity, guard. All other widgets haven't debounce parameter
*  and use the last element of this array with value 0 (it means no debounce).
*  `$INSTANCE_NAME`_SensorOnMask[] - used to store sensors on/off state.
*  `$INSTANCE_NAME`_SensorOnMask[0] contains the masked bits for sensors 
*   0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_SensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor is inactive.
*  1 - sensor is active.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CheckIsSensorActive(uint8 sensor)
{
    uint8 debounceIndex;
    /* Get On/Off mask */
    uint8 pos = (sensor >> 3u);
    uint8 onMask = 0x01u << (sensor & 0x07u);
    /* Prepare to find debounce counter index */
    uint8 widget = `$INSTANCE_NAME`_widgetNumber[sensor];
    uint8 fingerThreshold = `$INSTANCE_NAME`_fingerThreshold[widget];
    uint8 hysteresis = `$INSTANCE_NAME`_hysteresis[widget];
    uint8 debounce = `$INSTANCE_NAME`_debounce[widget];
    
`$writerCSHLIsSensor`
    
    /* Was on */
    if (`$INSTANCE_NAME`_SensorOnMask[pos] & onMask)
    {
        /* Hysteresis minus */
        if (`$INSTANCE_NAME`_SensorSignal[sensor] < (fingerThreshold - hysteresis))
        {
            `$INSTANCE_NAME`_SensorOnMask[pos] &= ~onMask;
            `$INSTANCE_NAME`_debounceCounter[debounceIndex] = debounce; 
        }
    }
    else    /* Was off */
    {
        /* Hysteresis plus */
        if (`$INSTANCE_NAME`_SensorSignal[sensor] > (fingerThreshold + hysteresis))
        {
            /* Sensor active, decrement debounce counter */
            if (`$INSTANCE_NAME`_debounceCounter[debounceIndex]-- == 0)
            {
                `$INSTANCE_NAME`_SensorOnMask[pos] |= onMask; 
            }
        }
        else
        {
            /* Sensor inactive - reset Debounce counter */
            `$INSTANCE_NAME`_debounceCounter[debounceIndex] = debounce;
        }
    }
    
    return (`$INSTANCE_NAME`_SensorOnMask[pos] & onMask) ? 1u : 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsWidgetActive
********************************************************************************
*
* Summary:
*  Use function `$INSTANCE_NAME`_CheckIsSensorActive() to update 
*  `$INSTANCE_NAME`_SensorOnMask[] for all sensors within the widget.
*  If one of sensors within widget is active the function return that widget is 
*  active.
*  The touch pad and matrix buttons widgets need to have active sensor within 
*  col and row to return widget active status.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns widget sensor state 1 if one or more sensors within widget is/are 
*  active, 0 if all sensors within widget are inactive.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CheckIsWidgetActive(uint8 widget)
{
    uint8 rawIndex = `$INSTANCE_NAME`_rawDataIndex[widget];
    uint8 numberOfSensors = `$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
    uint8 state = 0u;

    /* Check all sensors of the widget */
    do
    {
        if(`$INSTANCE_NAME`_CheckIsSensorActive(rawIndex) != 0u)
        {
            state = `$INSTANCE_NAME`_SENSOR_1_IS_ACTIVE;
        }
        rawIndex++;
    }
    while(rawIndex < numberOfSensors);
    
`$writerCSHLIsWidget`
    
    return state;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckIsAnyWidgetActive
********************************************************************************
*
* Summary:
*  Compares all sensors of the `$INSTANCE_NAME`_Signal[] array to their finger 
*  threshold. Calls `$INSTANCE_NAME`_CheckIsWidgetActive() for each widget so 
*  the `$INSTANCE_NAME`_SensorOnMask[] array is up to date after calling this 
*  function.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  Returns 1 if any widget is active, 0 none of widgets are active.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CheckIsAnyWidgetActive(void)
{
`$writerCSHLIsAnyWidget`
    return state;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableWidget
********************************************************************************
*
* Summary:
*  Enable all widget elements (sensors) to scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_SensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_SensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableWidget(uint8 widget)
{
    uint8 pos;
    uint8 enMask;
    uint8 rawIndex = `$INSTANCE_NAME`_rawDataIndex[widget];
    uint8 numberOfSensors = `$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
    
    /* Enable all sensors of the widget */
    do
    {
        pos = (rawIndex >> 3u);
        enMask = 0x01u << (rawIndex & 0x07u);
        
        `$INSTANCE_NAME`_SensorEnableMask[pos] |= enMask;
        rawIndex++;
    }
    while(rawIndex < numberOfSensors);
    
`$writerCSHLEnWidget`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableWidget
********************************************************************************
*
* Summary:
*  Disable all widget elements (sensors) from scanning process.
*
* Parameters:
*  widget:  widget number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_SensorEnableMask[] - used to store the sensor scanning 
*  state.
*  `$INSTANCE_NAME`_SensorEnableMask[0] contains the masked bits for sensors 
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_SensorEnableMask[1] contains the masked bits for 
*  sensors 8 through 15 (if needed), and so on.
*  0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*  1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableWidget(uint8 widget)
{
    uint8 pos;
    uint8 enMask;
    uint8 rawIndex = `$INSTANCE_NAME`_rawDataIndex[widget];
    uint8 numberOfSensors = `$INSTANCE_NAME`_numberOfSensors[widget] + rawIndex;
   
    /* Disable all sensors of the widget */
    do
    {
        pos = (rawIndex >> 3u);
        enMask = 0x01u << (rawIndex & 0x07u);
        
        `$INSTANCE_NAME`_SensorEnableMask[pos] &= ~enMask;
        rawIndex++;
    }
    while(rawIndex < numberOfSensors);
    
`$writerCSHLDisWidget`
}


`$writerCSHLCCode`

#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_MEDIAN_FILTER) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_MedianFilter
    ********************************************************************************
    *
    * Summary:
    *  Median filter function. 
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
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3) \
                                         `=ReentrantKeil($INSTANCE_NAME . "_MedianFilter")`
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
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */


#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_AVERAGING_FILTER) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_AveragingFilter
    ********************************************************************************
    *
    * Summary:
    *  Averaging filter function.
    *  The averaging filter looks at the three most recent samples of position and
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
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_AveragingFilter(uint16 x1, uint16 x2, uint16 x3) \
                                            `=ReentrantKeil($INSTANCE_NAME . "_AveragingFilter")`
    {
        uint32 tmp = ((uint32)x1 + (uint32)x2 + (uint32)x3) / 3u;
        
        return ((uint16) tmp);
    }
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */


#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR2_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR2_FILTER) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR2Filter
    ********************************************************************************
    *
    * Summary:
    *  IIR1/2 filter function. IIR1/2 = 1/2current + 1/2previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR2Filter(uint16 x1, uint16 x2) \
                                       `=ReentrantKeil($INSTANCE_NAME . "_IIR2Filter")`
    {
        uint32 tmp;
        
        /* IIR = 1/2 Current Value+ 1/2 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp >>= 1u;
    
        return ((uint16) tmp);
    }
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */


#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR4_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_IIR4_FILTER) )
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR4Filter
    ********************************************************************************
    *
    * Summary:
    *  IIR1/4 filter function. IIR1/4 = 1/4current + 3/4previous.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR4Filter(uint16 x1, uint16 x2) \
                                       `=ReentrantKeil($INSTANCE_NAME . "_IIR4Filter")`
    {
        uint32 tmp;
        
        /* IIR = 1/4 Current Value + 3/4 Previous Value */
        tmp = (uint32)x1 + (uint32)x2;
        tmp += ((uint32)x2 << 1u);
        tmp >>= 2u;
        
        return ((uint16) tmp);
    }
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */


#if ( (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_JITTER_FILTER) || \
      (`$INSTANCE_NAME`_POS_FILTERS_MASK & `$INSTANCE_NAME`_JITTER_FILTER) )
    /*******************************************************************************
    * Function Name: uint16 `$INSTANCE_NAME`_JitterFilter
    ********************************************************************************
    *
    * Summary:
    *  Jitter filter function.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_JitterFilter(uint16 x1, uint16 x2) \
                                         `=ReentrantKeil($INSTANCE_NAME . "_JitterFilter")`
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
#endif /* End `$INSTANCE_NAME`_RAW_FILTER_MASK && `$INSTANCE_NAME`_POS_FILTERS_MASK */


#if (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR8Filter
    ********************************************************************************
    *
    * Summary:
    *  IIR1/8 filter function. IIR1/8 = 1/8current + 7/8previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR8Filter(uint16 x1, uint16 x2) \
                                       `=ReentrantKeil($INSTANCE_NAME . "_IIR8Filter")`
    {
        uint32 tmp;
        
        /* IIR = 1/8 Current Value + 7/8 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 3u) - ((uint32)x2));
        tmp >>= 3u;
    
        return ((uint16) tmp);
    }
#endif /* End (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR8_FILTER) */


#if (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_IIR16Filter
    ********************************************************************************
    *
    * Summary:
    *  IIR1/16 filter function. IIR1/16 = 1/16current + 15/16previous.
    *  Only applies for raw data.
    *
    * Parameters:
    *  x1:  Current value.
    *  x2:  Previous value.
    *
    * Return:
    *  Returns filtered value.
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_IIR16Filter(uint16 x1, uint16 x2) \
                                        `=ReentrantKeil($INSTANCE_NAME . "_IIR16Filter")`
    {
        uint32 tmp;
        
        /* IIR = 1/16 Current Value + 15/16 Previous Value */
        tmp = (uint32)x1;
        tmp += (((uint32)x2 << 4u) - ((uint32)x2));
        tmp >>= 4u;
        
        return ((uint16) tmp);
    }
#endif /* End (`$INSTANCE_NAME`_RAW_FILTER_MASK & `$INSTANCE_NAME`_IIR16_FILTER) */


/* [] END OF FILE */
