/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the code that operates during the ADC_DelSig interrupt 
*  service routine.  
*
* Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"  


/*******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following 
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */


/*****************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR1
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ISR1)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR1`  */
    
    
    /* `#END`  */
    
    /* Stop the conversion if conversion mode is single sample and resolution
       is above 16 bits. 
    */
    #if(`$INSTANCE_NAME`_DEFAULT_RESOLUTION > 16 && \
        `$INSTANCE_NAME`_DEFAULT_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
        `$INSTANCE_NAME`_StopConvert(); 
    #endif           
    
    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (`$INSTANCE_NAME`_IRQ__ES2_PATCH ))      
            `$INSTANCE_NAME`_ISR_PATCH();
        #endif
    #endif    
    
}


/*****************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR2
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ISR2)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR2`  */
    

    /* `#END`  */
    
    /* Stop the conversion conversion mode is single sample and resolution
       is above 16 bits.
    */
    #if(`$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG2 > 16 && \
        `$INSTANCE_NAME`_CONVMODE_CFG2 == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
        `$INSTANCE_NAME`_StopConvert(); 
    #endif
    
    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (`$INSTANCE_NAME`_IRQ__ES2_PATCH ))      
            `$INSTANCE_NAME`_ISR_PATCH();
        #endif
    #endif    
    
}


/*****************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR3
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ISR3)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR3`  */
    

    /* `#END`  */

    /* Stop the conversion if conversion mode is set to single sample and 
       resolution is above 16 bits. 
    */
    #if(`$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG3 > 16 && \
        `$INSTANCE_NAME`_CONVMODE_CFG3 == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
        `$INSTANCE_NAME`_StopConvert(); 
    #endif   
    
    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (`$INSTANCE_NAME`_IRQ__ES2_PATCH ))      
            `$INSTANCE_NAME`_ISR_PATCH();
        #endif
    #endif       
}


/*****************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR4
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ISR4)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR4`  */
    

    /* `#END`  */
    
    /* Stop the conversion if conversion mode is set to single sample and 
       resolution is above 16 bits. 
    */
    #if(`$INSTANCE_NAME`_DEFAULT_RESOLUTION_CFG4 > 16 && \
        `$INSTANCE_NAME`_CONVMODE_CFG4 == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE) 
        `$INSTANCE_NAME`_StopConvert(); 
    #endif
    
    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (`$INSTANCE_NAME`_IRQ__ES2_PATCH ))      
            `$INSTANCE_NAME`_ISR_PATCH();
        #endif
    #endif             
}


/* [] END OF FILE */
