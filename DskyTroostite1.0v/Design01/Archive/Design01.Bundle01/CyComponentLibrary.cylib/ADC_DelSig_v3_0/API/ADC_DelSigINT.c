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
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Custom Declarations and Variables
* - add user include files, prototypes and variables between the following
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */


#if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)


    /*****************************************************************************
    * Function Name: `$INSTANCE_NAME`_ISR1
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
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
    *****************************************************************************/
    CY_ISR( `$INSTANCE_NAME`_ISR1)
    {
        /**************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR1`  */


        /* `#END`  */

        /* Stop the conversion if conversion mode is single sample and resolution
        *  is above 16 bits.
        */
        #if(`$INSTANCE_NAME`_`$Config1_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config1_Name`_CONV_MODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
            `$INSTANCE_NAME`_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            `$INSTANCE_NAME`_convDone = `$INSTANCE_NAME`_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

    }


    /*****************************************************************************
    * Function Name: `$INSTANCE_NAME`_ISR2
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
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
        *  is above 16 bits.
        */
        #if(`$INSTANCE_NAME`_`$Config2_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config2_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
            `$INSTANCE_NAME`_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *   resolution is above 16 bits and conversion mode is single sample 
			*/
            `$INSTANCE_NAME`_convDone = `$INSTANCE_NAME`_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

    }


    /*****************************************************************************
    * Function Name: `$INSTANCE_NAME`_ISR3
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
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
        *  resolution is above 16 bits.
        */
        #if(`$INSTANCE_NAME`_`$Config3_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config3_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
            `$INSTANCE_NAME`_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            `$INSTANCE_NAME`_convDone = `$INSTANCE_NAME`_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */
    }


    /*****************************************************************************
    * Function Name: `$INSTANCE_NAME`_ISR4
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
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
        *  resolution is above 16 bits.
        */
        #if(`$INSTANCE_NAME`_`$Config4_Name`_RESOLUTION > 16 && \
            `$INSTANCE_NAME`_`$Config4_Name`_CONVMODE == `$INSTANCE_NAME`_MODE_SINGLE_SAMPLE)
            `$INSTANCE_NAME`_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            `$INSTANCE_NAME`_convDone = `$INSTANCE_NAME`_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */
    }

#endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */


/* [] END OF FILE */
