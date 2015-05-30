/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the  Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START `$INSTANCE_NAME`_ISR_INTC` */

/* `#END` */

/* Extern functions declarations, Start and Compete scan */
extern void `$INSTANCE_NAME`_PreScan(uint32 sensor);
extern void `$INSTANCE_NAME`_PostScan(uint32 sensor);

extern uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex);
 
/* Global variables and arrays */
extern volatile uint8 `$INSTANCE_NAME`_csdStatusVar;
extern volatile uint8 `$INSTANCE_NAME`_sensorIndex;

static uint8 `$INSTANCE_NAME`_snsIndexTmp;

extern volatile uint8 `$INSTANCE_NAME`_sensorEnableMask[];
extern uint8 `$INSTANCE_NAME`_sensorEnableMaskBackup[];

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window 
*  depends on the sensor scan resolution parameter. 
*  The ISR has two modes: 
*   1. Scans a single sensor and stores the measure result.
*   2. Stores the result of the current measure and starts the next scan till all 
*      the enabled sensors are scanned.
*  This interrupt handler is only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csv - used to provide the status and mode of the scanning process.
*   Mode - a single scan or scan of all the enabled sensors.
*   Status - scan is in progress or ready for new scan.
*  `$INSTANCE_NAME`_sensorIndex - used to store a sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_ISR)
{	
	/*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_ISR_ENTER` */

    /* `#END` */

	CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    
    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;

    `$INSTANCE_NAME`_PostScan((uint32)`$INSTANCE_NAME`_sensorIndex);
            
    if ((`$INSTANCE_NAME`_csdStatusVar & `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        `$INSTANCE_NAME`_csdStatusVar &= (uint8)~`$INSTANCE_NAME`_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        `$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_FindNextSensor(`$INSTANCE_NAME`_sensorIndex);
        
        /* Check end of scan */
        if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
        {
            `$INSTANCE_NAME`_PreScan((uint32)`$INSTANCE_NAME`_sensorIndex);
        }
        else
        {
            `$INSTANCE_NAME`_csdStatusVar &= (uint8)~`$INSTANCE_NAME`_SW_STS_BUSY;

			 /* Check if widget has been scanned */
			if((`$INSTANCE_NAME`_csdStatusVar & `$INSTANCE_NAME`_SW_CTRL_WIDGET_SCAN) != 0u)
			{
			    /* Restore sensorEnableMask array */
				for(`$INSTANCE_NAME`_snsIndexTmp = 0u; 
				    `$INSTANCE_NAME`_snsIndexTmp < `$INSTANCE_NAME`_TOTAL_SENSOR_MASK; 
					`$INSTANCE_NAME`_snsIndexTmp++)
				{
					/* Backup sensorEnableMask array */
					`$INSTANCE_NAME`_sensorEnableMask[`$INSTANCE_NAME`_snsIndexTmp] = `$INSTANCE_NAME`_sensorEnableMaskBackup[`$INSTANCE_NAME`_snsIndexTmp];
				}
			}
        } 
    }
    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
	
	/*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_ISR_EXIT` */

    /* `#END` */
}

/* [] END OF FILE */
