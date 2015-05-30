/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for CapSense CSD component.
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

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START `$INSTANCE_NAME`_ISR_INTC` */

/* `#END` */

/* Extern functions declarations, Start and Compete the scan */
extern void `$INSTANCE_NAME`_PreScan(uint8 sensor);
extern void `$INSTANCE_NAME`_PostScan(uint8 sensor);

extern uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex);
 
/* Global variables and arrays */
extern volatile uint8 `$INSTANCE_NAME`_csv;
extern volatile uint8 `$INSTANCE_NAME`_sensorIndex;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when measure window is closed. The measure window 
*  depends on scan resolution parameter of sensor. 
*  The ISR has two modes: 
*   1. Scans single sensor and stores measure result.
*   2. Stores result of current measure and starts next scan till all 
*      enabled sensors will be scanned.
*  This interrupt handler only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csv - used to provide status and mode of scanning process.
*   Mode - single scan or scan of all enabled sensors.
*   Status - scan in progress or ready for new scan.
*  `$INSTANCE_NAME`_sensorIndex - used to store sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_ISR)
{
    uint8 interruptState;
	
	/*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_ISR_ENTER` */

    /* `#END` */

    /* Save results and disable sensor */
    
    interruptState = CyEnterCriticalSection();
    
    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;

    `$INSTANCE_NAME`_PostScan(`$INSTANCE_NAME`_sensorIndex);
            
    if ((`$INSTANCE_NAME`_csv & `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        `$INSTANCE_NAME`_csv &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
    }
    else
    {
        /* Proceed the scanning */
        `$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_FindNextSensor(`$INSTANCE_NAME`_sensorIndex);
        
        /* Check end of scan */
        if(`$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_TOTAL_SENSOR_COUNT)
        {
            `$INSTANCE_NAME`_PreScan(`$INSTANCE_NAME`_sensorIndex);
        }
        else
        {
            `$INSTANCE_NAME`_csv &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
        } 
    }
    CyExitCriticalSection(interruptState);
	
	/*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_ISR_EXIT` */

    /* `#END` */
}

/* [] END OF FILE */
