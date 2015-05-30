/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Sleep APIs for CRC component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

`$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    0x00u, /* enableState; */
   
    /* Save D0 and D1 registers are none-retention for Leopard ES2 and Panther ES1 */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)                      
        
        #if(`$INSTANCE_NAME`_CRC_SIZE <= 32u)
            `$INSTANCE_NAME`_DEFAULT_POLYNOM, /* polynomial; */
            
        #else
            `$INSTANCE_NAME`_DEFAULT_POLYNOM_UPPER, /* polynomialUpper; */
            `$INSTANCE_NAME`_DEFAULT_POLYNOM_LOWER,  /* polynomialLower; */
            
        #endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */
        
    #endif  /* End (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
};

#if (`$INSTANCE_NAME`_CRC_SIZE <= 32u) /* 8-32 bits CRC */
    extern void `$INSTANCE_NAME`_ResetSeedInit(`$RegSizeReplacementString` seed)
                                               `=ReentrantKeil($INSTANCE_NAME . "_ResetSeedInit")`;
#else
    extern void `$INSTANCE_NAME`_ResetSeedInitUpper(uint32 seed) 
                                                     `=ReentrantKeil($INSTANCE_NAME . "_ResetSeedInitUpper")`;
    extern void `$INSTANCE_NAME`_ResetSeedInitLower(uint32 seed) 
                                                      `=ReentrantKeil($INSTANCE_NAME . "_ResetSeedInitLower")`;
#endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves seed and polynomial registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{       
    /* Save D0 and D1 registers are none-retention for Leopard ES2 and Panther ES1 */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
    
        #if(`$INSTANCE_NAME`_CRC_SIZE <= 32u)
            `$INSTANCE_NAME`_backup.polynomial = `$INSTANCE_NAME`_ReadPolynomial();
            
        #else
            `$INSTANCE_NAME`_backup.polynomialUpper = `$INSTANCE_NAME`_ReadPolynomialUpper();
            `$INSTANCE_NAME`_backup.polynomialLower = `$INSTANCE_NAME`_ReadPolynomialLower();
            
        #endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */
        
    #endif  /* End (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stops CRC computation and saves CRC configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global Variables:
*  `$INSTANCE_NAME`_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    /* Store CRC enable state */
    if(`$INSTANCE_NAME`_IS_CRC_ENABLE(`$INSTANCE_NAME`_CONTROL_REG))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
        `$INSTANCE_NAME`_Stop();
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
    
    `$INSTANCE_NAME`_SaveConfig();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores seed and polynomial registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{      
    /* Restore D0 and D1 registers are none-retention for Leopard ES2 and Panther ES1 */
    #if (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1)
    
        #if(`$INSTANCE_NAME`_CRC_SIZE <= 32u)
            `$INSTANCE_NAME`_WritePolynomial(`$INSTANCE_NAME`_backup.polynomial);
            
        #else
            `$INSTANCE_NAME`_WritePolynomialUpper(`$INSTANCE_NAME`_backup.polynomialUpper);
            `$INSTANCE_NAME`_WritePolynomialLower(`$INSTANCE_NAME`_backup.polynomialLower);
            
        #endif  /* End (`$INSTANCE_NAME`_PSOC3_ES2 || `$INSTANCE_NAME`_PSOC5_ES1) */
        
    #endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */
    
    #if (`$INSTANCE_NAME`_CRC_SIZE <= 32u)
		`$INSTANCE_NAME`_WriteSeed(`$INSTANCE_NAME`_DEFAULT_SEED);                        
    #else
        `$INSTANCE_NAME`_WriteSeedUpper(`$INSTANCE_NAME`_DEFAULT_SEED_UPPER);
        `$INSTANCE_NAME`_WriteSeedLower(`$INSTANCE_NAME`_DEFAULT_SEED_LOWER); 
    #endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */
	
	#if (`$INSTANCE_NAME`_CRC_SIZE <= 32u)
		`$INSTANCE_NAME`_ResetSeedInit(`$INSTANCE_NAME`_DEFAULT_SEED);                        
    #else
        `$INSTANCE_NAME`_ResetSeedInitUpper(`$INSTANCE_NAME`_DEFAULT_SEED_UPPER);
        `$INSTANCE_NAME`_ResetSeedInitLower(`$INSTANCE_NAME`_DEFAULT_SEED_LOWER); 
    #endif  /* End (`$INSTANCE_NAME`_CRC_SIZE <= 32u) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores CRC configuration and starts CRC computation. 
*
* Parameters:
*  void
*
* Return:
*  void
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`
{
    `$INSTANCE_NAME`_RestoreConfig();
    
    /* Restore CRC enable state */
    if (`$INSTANCE_NAME`_backup.enableState != 0u)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
