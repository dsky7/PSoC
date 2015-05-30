/*******************************************************************************
* File Name: `$INSTANCE_NAME`_IP.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file defined information about hardware IP blocks, available in silicone.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_IP_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_IP_`$INSTANCE_NAME`_H

#include "cyfitter.h"

#if defined(CYIPBLOCK_m0s8gpio2_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8GPIO2_BLOCK		(1u)
	#define `$INSTANCE_NAME`_M0S8GPIO2_BLOCK_VER	(CYIPBLOCK_m0s8gpio2_VERSION)
#else
	#define `$INSTANCE_NAME`_IS_M0S8GPIO2_BLOCK		(0u)
	#define `$INSTANCE_NAME`_M0S8GPIO2_BLOCK_VER	(0u)
#endif /* (CYIPBLOCK_m0s8gpio2_VERSION) */


#if defined(CYIPBLOCK_m0s8hsiom4a_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8HSIOM4A_BLOCK	(1u)
	#define `$INSTANCE_NAME`_M0S8HSIOM4A_BLOCK_VER	(CYIPBLOCK_m0s8hsiom4a_VERSION)
#else
	#define `$INSTANCE_NAME`_IS_M0S8HSIOM4A_BLOCK	(0u)
	#define `$INSTANCE_NAME`_M0S8HSIOM4A_BLOCK_VER	(0u)
#endif /* (CYIPBLOCK_m0s8hsiom4a_VERSION) */


#if defined(CYIPBLOCK_m0s8ioss_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8IOSS_BLOCK		(1u)
	#define `$INSTANCE_NAME`_M0S8IOSS_BLOCK_VER		(CYIPBLOCK_m0s8ioss_VERSION)
#else
	#define `$INSTANCE_NAME`_IS_M0S8IOSS_BLOCK		(0u)
	#define `$INSTANCE_NAME`_M0S8IOSS_BLOCK_VER		(0u)
#endif /* (CYIPBLOCK_m0s8ioss_VERSION) */


#if defined(CYIPBLOCK_m0s8pclk_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8PCLK_BLOCK		(1u)
	#define `$INSTANCE_NAME`_M0S8PCLK_BLOCK_VER		(CYIPBLOCK_m0s8pclk_VERSION)
#else
	#define `$INSTANCE_NAME`_IS_M0S8PCLK_BLOCK		(0u)
	#define `$INSTANCE_NAME`_M0S8PCLK_BLOCK_VER		(0u)
#endif /* (CYIPBLOCK_m0s8pclk_VERSION) */


#if defined(CYIPBLOCK_m0s8peri_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK		(1u)
	#define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER		((CYIPBLOCK_m0s8peri_VERSION))
#else
	#define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK		(0u)
	#define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER		(0u)
#endif /* (CYIPBLOCK_m0s8peri_VERSION) */


#if defined(CYIPBLOCK_m0s8csd_VERSION)
	#define `$INSTANCE_NAME`_IS_M0S8CSD_BLOCK		(1u)
	#define `$INSTANCE_NAME`_M0S8CSD_BLOCK_VER		(CYIPBLOCK_m0s8csd_VERSION)
#else
	#define `$INSTANCE_NAME`_IS_M0S8CSD_BLOCK		(0u)
	#define `$INSTANCE_NAME`_M0S8CSD_BLOCK_VER		(0u)
#endif /* (CYIPBLOCK_m0s8csd_VERSION) */


#endif /* CY_CAPSENSE_CSD_IP_`$INSTANCE_NAME`_H */

/* [] END OF FILE */