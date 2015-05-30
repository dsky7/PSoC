/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of scanning APIs for the CapSense CSD 
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE)
    #define `$INSTANCE_NAME`_SHIELD_PORT_NUMBER `$INSTANCE_NAME`_Shield__PORT
    #define `$INSTANCE_NAME`_SHIELD_PIN_NUMBER  `$INSTANCE_NAME`_Shield__SHIFT
#endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    extern __INLINE void `$INSTANCE_NAME`_EnableScanSlot(uint8 slot);
    extern __INLINE void `$INSTANCE_NAME`_DisableScanSlot(uint8 slot);
#else
    #define `$INSTANCE_NAME`_EnableScanSlot(slot)   `$INSTANCE_NAME`_EnableSensor(slot)
    #define `$INSTANCE_NAME`_DisableScanSlot(slot)  `$INSTANCE_NAME`_DisableSensor(slot)
#endif  /* End `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

/* Find next sensor for One Channel design */
uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex);

/* Start and Compete the scan */
void `$INSTANCE_NAME`_PreScan(uint8 sensor);
void `$INSTANCE_NAME`_PostScan(uint8 sensor);

extern __INLINE void `$INSTANCE_NAME`_CmodPrecharge(void);
extern __INLINE void `$INSTANCE_NAME`_SetScanSlotSettings(uint8 slot);
extern __INLINE void `$INSTANCE_NAME`_EnableSensor(uint8 sensor);
extern __INLINE void `$INSTANCE_NAME`_DisableSensor(uint8 sensor);


/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
    uint8 `$INSTANCE_NAME`_lowLevelTuningDone = 0u;
    extern void `$INSTANCE_NAME`_AutoTune(void);
#endif /* End (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
	uint8 `$INSTANCE_NAME`_prescalersTuningDone = 0u;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

uint8 `$INSTANCE_NAME`_initVar = 0u;
            
/* Global software variables */
volatile uint8 `$INSTANCE_NAME`_csv = 0u;            /* CapSense CSD status, control variable */
volatile uint8 `$INSTANCE_NAME`_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT] = {0u};

/* Global array of PRS resolutions */
uint32 `$INSTANCE_NAME`_prsResolutionTbl[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT] = {0u};

/* Backup variables for trim registers*/

#if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
	uint8 `$INSTANCE_NAME`_csdTrim2;   
#else
    uint8 `$INSTANCE_NAME`_csdTrim1;	
#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */


`$writerCVariables`



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Inits default CapSense configuration provided with customizer that defines 
*  mode of component operations and resets all sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
	uint32 newRegValue;
#if ( ( `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) || (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )

    uint8 snsNumber;

    for(snsNumber = 0u; snsNumber < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; snsNumber++)  
    {  
        `$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal[snsNumber]);
        `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal[snsNumber]);
    }
#else
    `$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal);
    `$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal);
#endif /* (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
      (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */
      
    /* Clear all sensors */
    `$INSTANCE_NAME`_ClearSensors();
    
#if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE)
    *`$INSTANCE_NAME`_prtCfgTbl[`$INSTANCE_NAME`_SHIELD_PORT_NUMBER] &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << (`$INSTANCE_NAME`_SHIELD_PIN_NUMBER * 3u));
    *`$INSTANCE_NAME`_prtSelTbl[`$INSTANCE_NAME`_SHIELD_PORT_NUMBER] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << (`$INSTANCE_NAME`_SHIELD_PIN_NUMBER << 2u));
    *`$INSTANCE_NAME`_prtSelTbl[`$INSTANCE_NAME`_SHIELD_PORT_NUMBER] |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << (`$INSTANCE_NAME`_SHIELD_PIN_NUMBER << 2u));
	
	#if((`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) || (`$INSTANCE_NAME`_CSH_TANK_ENABLE))
		`$INSTANCE_NAME`_PORT_SEL4_REG &= ~(`$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK);
		`$INSTANCE_NAME`_PORT_SEL4_REG |= `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_B;
	#endif /* */
	
	#if(`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
		`$INSTANCE_NAME`_PORT4_PC_REG &= ~(`$INSTANCE_NAME`_CSD_CTANK_PC_MASK);
		`$INSTANCE_NAME`_PORT4_PC_REG |= `$INSTANCE_NAME`_CTANK_PC_STRONG_MODE;
		
		`$INSTANCE_NAME`_PORT4_DR_REG &= ~(`$INSTANCE_NAME`_CTANK_DR_MASK);
		`$INSTANCE_NAME`_PORT4_DR_REG |= `$INSTANCE_NAME`_CTANK_DR_CONFIG;
	#endif/* (`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

#endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

    /* Set trim registers for CSD Mode */ 
    #if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
		/* iDAC1 Sinking Mode */ 
		`$INSTANCE_NAME`_csdTrim2 = `$INSTANCE_NAME`_CSD_TRIM2_REG;
		newRegValue = `$INSTANCE_NAME`_csdTrim2;
		newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
		newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK); 
		
		#if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
		     /* iDAC2 Sinking Mode */ 
			newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
			newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK); 
		#endif
		`$INSTANCE_NAME`_CSD_TRIM2_REG = newRegValue;
    #else   
		/* iDAC1 Sourcing Mode */ 
		`$INSTANCE_NAME`_csdTrim1 = `$INSTANCE_NAME`_CSD_TRIM1_REG;
		newRegValue = `$INSTANCE_NAME`_csdTrim1;
		newRegValue &= `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK;
		newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK);
		#if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
		     /* iDAC2 Sourcing Mode */ 
			newRegValue &= `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK;
			newRegValue |= (uint32)(`$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG & `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK);
		#endif		
		`$INSTANCE_NAME`_CSD_TRIM1_REG = newRegValue;
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */

    `$INSTANCE_NAME`_CSD_CFG_REG = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG;
    `$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG;   
    `$INSTANCE_NAME`_SetShieldDelay(`$INSTANCE_NAME`_SHIELD_DELAY ); 

    `$INSTANCE_NAME`_PORT_SEL4_REG &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
    `$INSTANCE_NAME`_PORT_SEL4_REG |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
    
    /* Setup ISR */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR);
    CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables active mode power template bits for number of component used within 
*  CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    /* Enable the Clocks */
    `$INSTANCE_NAME`_SenseClk_Start();
    `$INSTANCE_NAME`_SampleClk_Start();
    
	`$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_ENABLE;
	
    `$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN;
    `$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_SENSE_EN;

    /* Enable interrupt */
    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
	
	`$INSTANCE_NAME`_CmodPrecharge();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Initializes registers and starts the CSD method of CapSense component. Reset 
*  all sensors to an inactive state. Enables interrupts for sensors scanning.
*  When Auto Tuning (SmartSense) mode is selected the tuning procedure is 
*  applied for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on 
*  first function call.
*  `$INSTANCE_NAME`_lowLevelTuningDone - used to notify the Tuner GUI that 
*  tuning of scanning parameters are done.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
    
    /* AutoTunning start */
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
        /* AutoTune by sensor basis */
        `$INSTANCE_NAME`_AutoTune();
        `$INSTANCE_NAME`_lowLevelTuningDone = 1u;
	#else
        #if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO)
            `$INSTANCE_NAME`_Calc_PRS_Resolution();
        #endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO) */     
    #endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */	
	
	`$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_SENSE_AMUXA;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops the sensors scanner, disables internal interrupts, and resets all 
*  sensors to an inactive state. Disables Active mode power template bits for 
*  number of component used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This function should be called after scans will be completed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    /* Clear all sensors */
    `$INSTANCE_NAME`_ClearSensors();

    /* Disable the Clocks */
    `$INSTANCE_NAME`_SenseClk_Stop();
    `$INSTANCE_NAME`_SampleClk_Stop();
	
    /* Restore trim registers */ 
    #if (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
		/* iDAC Sinking Mode */ 
		`$INSTANCE_NAME`_CSD_TRIM2_REG = `$INSTANCE_NAME`_csdTrim2; 
    #else   
		/* iDAC Sourcing Mode */ 
		`$INSTANCE_NAME`_CSD_TRIM1_REG = `$INSTANCE_NAME`_csdTrim1;
    #endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FindNextSensor
********************************************************************************
*
* Summary:
*  Finds next sensor to scan. 
*
* Parameters:
*  snsIndex:  Current index of sensor.
*
* Return:
*  Returns the next sensor index to scan.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorEnableMask[ ] - used to store bit masks of enabled 
*  sensors.
*  `$INSTANCE_NAME`_sensorEnableMask[0] contains the masked bits for sensors 0
*  through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  `$INSTANCE_NAME`_sensorEnableMask[1] contains the masked bits for sensors 
*  8 through 15 (if needed), and so on.
*    0 - sensor doesn't scan by `$INSTANCE_NAME`_ScanEnabledWidgets().
*    1 - sensor scans by `$INSTANCE_NAME`_ScanEnabledWidgets().
*
* Note: 
*  This function has effect on current scanning scanning and should not
*  be used outisde of component.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex)
{
    uint8 pos;
    uint8 enMask;
    
    /* Check if sensor enabled */
    do
    {
        /* Proceed with the next sensor */
        snsIndex++;
        if(snsIndex == `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        pos = (snsIndex >> 3u);
        enMask = 0x01u << (snsIndex & 0x07u);
    }    
    while((`$INSTANCE_NAME`_sensorEnableMask[pos] & enMask) == 0u);
    
    return snsIndex;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetScanSlotSettings
********************************************************************************
*
* Summary:
*  Sets the scan settings of the selected scan slot (sensor or pair of sensors). 
*  The scan settings incorporate IDAC value (for IDAC configurations) for every 
*  sensor and resolution. The resolution is the same for all sensors within 
*  widget.
*
* Parameters:
*  slot:  Scan slot number (sensor or pair of sensors).
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_idacSettings[] - used to store idac value for every sensor.
*  `$INSTANCE_NAME`_widgetResolution[] - used to store scan resolution of every 
*  widget.
*
*******************************************************************************/
__INLINE void `$INSTANCE_NAME`_SetScanSlotSettings(uint8 slot)
{
    uint32 newRegisterValue;

	
	/* Set Idac Value */
    newRegisterValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
    
	newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK);
    newRegisterValue |= `$INSTANCE_NAME`_idac1Settings[slot];
    
    #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
        newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK);
        newRegisterValue |= (`$INSTANCE_NAME`_idac2Settings[slot] 
                                           << `$INSTANCE_NAME`_CSD_IDAC2_DATA_OFFSET);                               
    #endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */
	
	`$INSTANCE_NAME`_CSD_IDAC_REG = newRegisterValue;

    #if ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
          (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )
		`$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal[slot]);
		`$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal[slot]);
    #else
		`$INSTANCE_NAME`_SenseClk_SetDividerValue(`$INSTANCE_NAME`_senseClkDividerVal);
		`$INSTANCE_NAME`_SampleClk_SetDividerValue(`$INSTANCE_NAME`_sampleClkDividerVal);
    #endif /* ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
                (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )
           */
		   
	#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
	
		#if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)
			if(`$INSTANCE_NAME`_prescalersTuningDone != 0u)
			{
		#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) */
				
				newRegisterValue = `$INSTANCE_NAME`_CSD_CFG_REG;
				newRegisterValue |= `$INSTANCE_NAME`_CSD_PRS_SELECT_PRS;
				
				#if(`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO)

					newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PRS_12_BIT);
					newRegisterValue |= `$INSTANCE_NAME`_prsResolutionTbl[slot];	
				#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_AUTO) */
				
				`$INSTANCE_NAME`_CSD_CFG_REG = newRegisterValue;
				
		#if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING)	
			}
		#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE) */

	#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */
	
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanSensor
********************************************************************************
*
* Summary:
*  Sets scan settings and starts scanning a sensor or pair of combined sensors
*  on each channel. If two channels are configured, two sensors may be scanned 
*  at the same time. After scanning is complete the isr copies the measured 
*  sensor raw data to the global array. Use of the isr ensures this function 
*  is non-blocking. Each sensor has a unique number within the sensor array. 
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and mode of scan as single scan.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one.
*  `$INSTANCE_NAME`_sensorIndex - used to store sensor scanning sensor number.
*  Sets to provided sensor argument.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_ScanSensor(uint8 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    `$INSTANCE_NAME`_csv = 0u;
    `$INSTANCE_NAME`_sensorIndex = sensor;
    
    /* Start of sensor scan */
    `$INSTANCE_NAME`_csv = (`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN);
    `$INSTANCE_NAME`_PreScan(sensor);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  Scans all of the enabled widgets. Starts scanning a sensor or pair of sensors 
*  within enabled widget. The isr proceeding scanning next sensor or pair till 
*  all enabled widgets will be scanned. Use of the isr ensures this function is 
*  non-blocking. All widgets are enabled by default except proximity widgets. 
*  Proximity widgets must be manually enabled as their long scan time is 
*  incompatible with fast response desired of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and clears single scan mode.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one. 
*  `$INSTANCE_NAME`_sensorIndex - used to store sensor scanning sensor number.
*  Sets to 0xFF and provided to function `$INSTANCE_NAME`_FindNextSensor or
*  `$INSTANCE_NAME`_FindNextPair, these functions starts with sensor index
*  increment and overflow of uint8 gives desired index 0.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    `$INSTANCE_NAME`_csv = 0u;
    `$INSTANCE_NAME`_sensorIndex = 0xFFu;
    
    /* Find next sensor */
    `$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_FindNextSensor(`$INSTANCE_NAME`_sensorIndex);

    /* Check end of scan condition */
    if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
    {
        `$INSTANCE_NAME`_csv |= `$INSTANCE_NAME`_SW_STS_BUSY;
        `$INSTANCE_NAME`_PreScan(`$INSTANCE_NAME`_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of CapSense component. The 1 means that scanning in 
*  progress and 0 means that scanning is complete.
*
* Parameters:
*  None
*
* Return:
*  Returns the state of scanning. 1 - scanning in progress, 0 - scanning 
*  completed.
*
* Global Variables:
*  `$INSTANCE_NAME`_csv - used to provide status and mode of scanning process. 
*  Checks the busy status.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_IsBusy(void)
{
    return ((`$INSTANCE_NAME`_csv & `$INSTANCE_NAME`_SW_STS_BUSY) == 
             `$INSTANCE_NAME`_SW_STS_BUSY) ? 1u : 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns scan sensor raw data from the `$INSTANCE_NAME`_sensorRaw[] array. 
*  Each scan sensor has a unique number within the sensor array. This number 
*  is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_ReadSensorRaw(uint8 sensor)
{
    return `$INSTANCE_NAME`_sensorRaw[sensor];
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all sensors to the non-sampling state by sequentially disconnecting
*  all sensors from Analog MUX Bus and putting them to inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearSensors(void)
{
    uint8 i;
   
    for (i = 0u; i < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; i++)
    {
        `$INSTANCE_NAME`_DisableScanSlot(i);
    }
}


#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement 
    *  cycle. The corresponding pin/pins are set to Analog High-Z mode and 
    *  connected to the Analog Mux Bus. This also enables the comparator function.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Constants:
    *  `$INSTANCE_NAME`_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  `$INSTANCE_NAME`_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  `$INSTANCE_NAME`_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The bit 7 (msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    __INLINE void `$INSTANCE_NAME`_EnableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = `$INSTANCE_NAME`_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (signle) */
            `$INSTANCE_NAME`_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[snsType];
            snsNumber = `$INSTANCE_NAME`_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                `$INSTANCE_NAME`_EnableSensor(index[j]);
            }
        } 
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pis is/are disconnected 
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  `$INSTANCE_NAME`_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  `$INSTANCE_NAME`_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The 7bit(msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    __INLINE void `$INSTANCE_NAME`_DisableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = `$INSTANCE_NAME`_portTable[slot];
        
        /* Check if sensor is complex */
        if ((snsType & `$INSTANCE_NAME`_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (signle) */
            `$INSTANCE_NAME`_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~`$INSTANCE_NAME`_COMPLEX_SS_FLAG;
            index = &`$INSTANCE_NAME`_indexTable[snsType];
            snsNumber = `$INSTANCE_NAME`_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                `$INSTANCE_NAME`_DisableSensor(index[j]);
            }
        } 
    }
#endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableSensor
********************************************************************************
*
* Summary:
*  Configures the selected sensor to measure during the next measurement cycle.
*  The corresponding pins are set to Analog High-Z mode and connected to the
*  Analog Mux Bus. This also enables the comparator function.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store position of pin that 
*  configured as sensor in port. 
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM 
*  registers for every port. 
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config 
*  registers for every port.
*
*******************************************************************************/
__INLINE void `$INSTANCE_NAME`_EnableSensor(uint8 sensor)
{
	uint32 newRegisterValue;
	
    uint32 port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    uint8  pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * 3u;
    uint8  pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * 4u;

	newRegisterValue = *`$INSTANCE_NAME`_prtSelTbl[port];
	newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);
	newRegisterValue |= (`$INSTANCE_NAME`_CSD_SENSE_PORT_MODE << pinHSIOMShift);
   
    *`$INSTANCE_NAME`_prtCfgTbl[port] &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
    *`$INSTANCE_NAME`_prtSelTbl[port] = newRegisterValue;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z or Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  `$INSTANCE_NAME`_pinShiftTbl[] - used to store position of pin that 
*  configured as sensor in port. 
*  `$INSTANCE_NAME`_prtSelTbl[] - Contains pointers to the HSIOM 
*  registers for every port. 
*  `$INSTANCE_NAME`_PrtCfgTb[] - Contains pointers to the port config 
*  registers for every port.
*
*******************************************************************************/
__INLINE void `$INSTANCE_NAME`_DisableSensor(uint8 sensor)
{
    uint32 port = (uint32) `$INSTANCE_NAME`_portTable[sensor];
    uint8  pinHSIOMShift = `$INSTANCE_NAME`_pinShiftTbl[sensor] * 4u;
#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS != `$INSTANCE_NAME`__SHIELD)
	uint32 newRegisterValue;
    uint8  pinModeShift = `$INSTANCE_NAME`_pinShiftTbl[sensor]  * 3u;
#endif

    *`$INSTANCE_NAME`_prtSelTbl[port] &= ~(`$INSTANCE_NAME`_CSD_HSIOM_MASK << pinHSIOMShift);
        
#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD)
    *`$INSTANCE_NAME`_prtSelTbl[port] |= (`$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
#else

	newRegisterValue = *`$INSTANCE_NAME`_prtCfgTbl[port];
	newRegisterValue &= ~(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK << pinModeShift);
	newRegisterValue |=  (`$INSTANCE_NAME`_CSD_INACTIVE_CONNECT << pinModeShift);
    *`$INSTANCE_NAME`_prtCfgTbl[port] =  newRegisterValue;
    
	*`$INSTANCE_NAME`_prtDRTbl[port]  &=  ~(1u << `$INSTANCE_NAME`_pinShiftTbl[sensor]);  
    
#endif /* `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__SHIELD */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PreScan
********************************************************************************
*
* Summary:
*  Set required settings, enable sensor, remove Vref from AMUX and start the 
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*
*******************************************************************************/
void `$INSTANCE_NAME`_PreScan(uint8 sensor)
{
    uint8 widget;
    uint8 interruptState;
	uint32 regValue;
    
    interruptState = CyEnterCriticalSection();

    /* Define widget sensor belongs to */
    widget = `$INSTANCE_NAME`_widgetNumber[sensor];

    /* Set Sensor Settings */
    `$INSTANCE_NAME`_SetScanSlotSettings(sensor);

    /* Enable Sensor */
    `$INSTANCE_NAME`_EnableScanSlot(sensor);
	
#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
	regValue = `$INSTANCE_NAME`_PORT_SEL4_REG;
	regValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
	regValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A;
	`$INSTANCE_NAME`_PORT_SEL4_REG = regValue;
	
	regValue = `$INSTANCE_NAME`_PORT4_PC_REG;
	regValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_PC_MASK);
	regValue |= `$INSTANCE_NAME`_CMOD_PC_HIGH_Z_MODE;
	`$INSTANCE_NAME`_PORT4_PC_REG = regValue;
#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */
	
	regValue = `$INSTANCE_NAME`_CSD_CFG_REG;
	regValue &= ~(`$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK);
	regValue |= `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG;
	
	`$INSTANCE_NAME`_CSD_CFG_REG = regValue;
	
#if(`$INSTANCE_NAME`_PRS_OPTIONS  != `$INSTANCE_NAME`__PRS_NONE)
	`$INSTANCE_NAME`_CSD_CFG_REG |= `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS  != `$INSTANCE_NAME`__PRS_NONE) */
    
    `$INSTANCE_NAME`_CSD_CNT_REG = `$INSTANCE_NAME`_widgetResolution[widget];
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PostScan
********************************************************************************
*
* Summary:
*  Store results of measurament in `$INSTANCE_NAME`_SensorResult[] array,
*  sets scan sensor in none sampling state, turn off Idac(Current Source IDAC),
*  disconnect IDAC(Sink mode) or bleed resistor (Rb) and apply Vref on AMUX.
*  Only one channel designs.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_sensorRaw[] - used to store sensors raw data.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PostScan(uint8 sensor)
{	
	`$INSTANCE_NAME`_CmodPrecharge();
	
    /* Read SlotResult from Raw Counter */
    `$INSTANCE_NAME`_sensorRaw[sensor]  = `$INSTANCE_NAME`_CSD_CNT_REG;
    /* Disable Sensor */
    `$INSTANCE_NAME`_DisableScanSlot(sensor);
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetShieldDelay
********************************************************************************
*
* Summary:
*  Sets plarity for IDAC2.
*
* Parameters:
*  delay:  shield delya value:
*                               0 - no delay
*                               1 - 1 tact delay
*                               2 - 2 tacts delay
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetShieldDelay(uint32 delay)
{
    `$INSTANCE_NAME`_CSD_CFG_REG &= ~`$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY;
    delay &= 0x03u;
    `$INSTANCE_NAME`_CSD_CFG_REG |= (delay << `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY__POS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResolutionIndex
********************************************************************************
*
* Summary:
*  Recalculating the counter value tu the resolution.
*
* Parameters:
*	sensor: Sensor number.
*
* Return:
*  Returns scanning resolution for the selected sensor.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetResolutionIndex(uint32 sensor)
{
	uint32 widgetResolution;
	uint32 result = 0u;
	uint32 mask = 1u;
	
	uint8 widget;
	
	widget = `$INSTANCE_NAME`_widgetNumber[sensor];
	widgetResolution = `$INSTANCE_NAME`_widgetResolution[widget];
	
	widgetResolution >>= 16u;
	
	while(widgetResolution & mask)
	{
		result++;
		mask <<= 1u;
	}
	
	return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Calc_PRS_Resolution
********************************************************************************
*
* Summary:
*  Calculates the PRS resolution if the PRS-Auto mode is selected.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Calc_PRS_Resolution(void)
{
	uint32 curSensor;
	uint32 widgetResolution;
    
    uint8 senseClk;
    uint8 sampleClk;
	
    for(curSensor = 0u; curSensor < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT; curSensor++)
	{
    
        #if ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
              (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) )
            senseClk = `$INSTANCE_NAME`_senseClkDividerVal[curSensor];
            sampleClk = `$INSTANCE_NAME`_sampleClkDividerVal[curSensor];
        #else
            senseClk = `$INSTANCE_NAME`_senseClkDividerVal;
            sampleClk = `$INSTANCE_NAME`_sampleClkDividerVal;
        #endif /* ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
                    (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`_AUTO_TUNING) ) */
        
		if(senseClk > 1u)
		{
			senseClk >>= 1u;
		}
		
		widgetResolution = `$INSTANCE_NAME`_GetResolutionIndex(curSensor);
		
		if((sampleClk + widgetResolution) > (12u + senseClk))
		{
			`$INSTANCE_NAME`_prsResolutionTbl[curSensor] = `$INSTANCE_NAME`_CSD_PRS_12_BIT;
		}
		else
		{
			`$INSTANCE_NAME`_prsResolutionTbl[curSensor] = `$INSTANCE_NAME`_CSD_PRS_8_BIT;
		}
	}
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CmodPrecharge
********************************************************************************
*
* Summary:
*  This is internal API which precharges the Modulator Capacitor before scan.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
__INLINE void `$INSTANCE_NAME`_CmodPrecharge(void)
{
	uint32 regValue;
	
	#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)	
		uint32 watchdogCounter;
	#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF) */
	
	#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF)
		regValue = `$INSTANCE_NAME`_PORT_SEL4_REG;
		regValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK);
		regValue |= `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_B;
		`$INSTANCE_NAME`_PORT_SEL4_REG = regValue;
		
		regValue = `$INSTANCE_NAME`_PORT4_PC_REG;
		regValue &= ~(`$INSTANCE_NAME`_CSD_CMOD_PC_MASK);
		regValue |= `$INSTANCE_NAME`_CMOD_PC_STRONG_MODE;
		`$INSTANCE_NAME`_PORT4_PC_REG = regValue;
			
		`$INSTANCE_NAME`_PORT4_DR_REG &= ~(`$INSTANCE_NAME`_CMOD_DR_MASK);
		`$INSTANCE_NAME`_PORT4_DR_REG |= `$INSTANCE_NAME`_CMOD_DR_CONFIG;
	#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

		regValue = `$INSTANCE_NAME`_CSD_CFG_REG;
		regValue &= ~(`$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK);
		regValue |= `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG;
		`$INSTANCE_NAME`_CSD_CFG_REG = regValue;

	#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)	
		regValue = `$INSTANCE_NAME`_CSD_IDAC_REG;
		`$INSTANCE_NAME`_CSD_IDAC_REG = `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG;
		
	#if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)	
		`$INSTANCE_NAME`_CSD_CFG_REG &= ~(`$INSTANCE_NAME`_CSD_CFG_POLARITY);
	#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */	
		
		watchdogCounter = `$INSTANCE_NAME`_PRECHARGE_WATCHDOG_CYCLES_NUM;
		while((0u == (`$INSTANCE_NAME`_CSD_STAT_REG & `$INSTANCE_NAME`_CSD_STAT_SAMPLE)) && (0u != watchdogCounter))
	    {
	    	watchdogCounter--;
	    }
		
	#if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)
		`$INSTANCE_NAME`_CSD_CFG_REG |= (`$INSTANCE_NAME`_CSD_CFG_POLARITY);
	#endif /* (`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK) */	
		
		`$INSTANCE_NAME`_CSD_IDAC_REG = regValue;
		
	#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF) */	
}

/* [] END OF FILE */
