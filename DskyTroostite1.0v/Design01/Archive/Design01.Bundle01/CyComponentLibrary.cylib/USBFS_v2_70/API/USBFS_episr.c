/*******************************************************************************
* File Name: `$INSTANCE_NAME`_episr.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Data endpoint Interrupt Service Routines
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
#include "`$INSTANCE_NAME`_pvt.h"
#if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u))
    #include "`$INSTANCE_NAME`_midi.h"
#endif /* (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && (`$INSTANCE_NAME`_ENABLE_MIDI_API != 0u)) */
#if ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
    #include "`$INSTANCE_NAME`_EP8_DMA_Done_SR.h"
    #include "`$INSTANCE_NAME`_EP17_DMA_Done_SR.h"
#endif /* (`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if(`$INSTANCE_NAME`_EP1_ISR_REMOVE == 0u)


    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_1_ISR
    *******************************************************************************
    *
    * Summary:
    *  Endpoint 1 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    ******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_1_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT)  && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP1_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR) &
                                                                    (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP1_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP1)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */
    }

#endif   /*  `$INSTANCE_NAME`_EP1_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP2_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_2_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 2 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_2_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP2_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP2_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP2)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */
    }

#endif   /*  `$INSTANCE_NAME`_EP2_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP3_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_3_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 3 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_3_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3 */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP3_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP3_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP3)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  `$INSTANCE_NAME`_EP3_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP4_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_4_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 4 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_4_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP4_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP4_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP4)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  `$INSTANCE_NAME`_EP4_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP5_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_5_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 5 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_5_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP5_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP5_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP5)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }
#endif   /*  `$INSTANCE_NAME`_EP5_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP6_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_6_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 6 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_6_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP6_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP6_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP6)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  `$INSTANCE_NAME`_EP6_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP7_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_7_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 7 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_7_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP7_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP7_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP7)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  `$INSTANCE_NAME`_EP7_ISR_REMOVE */


#if(`$INSTANCE_NAME`_EP8_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_8_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 8 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_8_ISR)
    {
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */

        CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP8_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].attrib & `$INSTANCE_NAME`_EP_TYPE_MASK) !=
                                                                                    `$INSTANCE_NAME`_EP_TYPE_ISOC)
        {
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
        }
        `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        CY_SET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR, CY_GET_REG8(`$INSTANCE_NAME`_SIE_EP_INT_SR_PTR)
                                                                        & (uint8)~`$INSTANCE_NAME`_SIE_EP_INT_EP8_MASK);

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP8)
            {
                `$INSTANCE_NAME`_MIDI_OUT_EP_Service();
            }
        #endif /*  `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                     `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT  */
    }

#endif   /*  `$INSTANCE_NAME`_EP8_ISR_REMOVE */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SOF_ISR
********************************************************************************
*
* Summary:
*  Start of Frame Interrupt Service Routine
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_SOF_ISR)
{
    /* `#START SOF_USER_CODE` Place your code here */

    /* `#END` */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BUS_RESET_ISR
********************************************************************************
*
* Summary:
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_BUS_RESET_ISR)
{
    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    `$INSTANCE_NAME`_ReInitComponent();
}


#if((`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL) && (`$INSTANCE_NAME`_ARB_ISR_REMOVE == 0u))


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ARB_ISR
    ********************************************************************************
    *
    * Summary:
    *  Arbiter Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side effect:
    *  Search for EP8 int_status will be much slower than search for EP1 int_status.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_ARB_ISR)
    {
        uint8 int_status;
        uint8 ep_status;
        uint8 ep = `$INSTANCE_NAME`_EP1;
        uint8 ptr = 0u;

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        int_status = `$INSTANCE_NAME`_ARB_INT_SR_REG;                   /* read Arbiter Status Register */
        `$INSTANCE_NAME`_ARB_INT_SR_REG = int_status;                   /* Clear Serviced Interrupts */

        while(int_status != 0u)
        {
            if((int_status & 1u) != 0u)  /* If EpX interrupt present */
            {   /* read Endpoint Status Register */
                ep_status  = CY_GET_REG8((reg8 *)(`$INSTANCE_NAME`_ARB_EP1_SR_IND + ptr));
                /* If In Buffer Full */
                if((ep_status & `$INSTANCE_NAME`_ARB_EPX_SR_IN_BUF_FULL) != 0u)
                {
                    if((`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN) != 0u)
                    {
                        /* Clear Data ready status */
                        *(reg8 *)(`$INSTANCE_NAME`_ARB_EP1_CFG_IND + ptr) &=
                                                                    (uint8)~`$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY;
                        #if((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
                            /* Setup common area DMA with rest of the data */
                            if(`$INSTANCE_NAME`_inLength[ep] > `$INSTANCE_NAME`_DMA_BYTES_PER_BURST)
                            {
                                `$INSTANCE_NAME`_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                `$INSTANCE_NAME`_inBufFull[ep] = 1u;
                            }
                        #endif /* ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */
                        /* Write the Mode register */
                        CY_SET_REG8((reg8 *)(`$INSTANCE_NAME`_SIE_EP1_CR0_IND + ptr), `$INSTANCE_NAME`_EP[ep].epMode);
                        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_IN)
                            if(ep == `$INSTANCE_NAME`_midi_in_ep)
                            {   /* Clear MIDI input pointer */
                                `$INSTANCE_NAME`_midiInPointer = 0u;
                            }
                        #endif /*  `$INSTANCE_NAME`_ENABLE_MIDI_STREAMING*/
                    }
                }
                /* (re)arm Out EP only for mode2 */
                #if(`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_DMAAUTO)
                    /* If DMA Grant */
                    if((ep_status & `$INSTANCE_NAME`_ARB_EPX_SR_DMA_GNT) != 0u)
                    {
                        if((`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN) == 0u)
                        {
                                `$INSTANCE_NAME`_EP[ep].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;
                                /* Write the Mode register */
                                CY_SET_REG8((reg8 *)(`$INSTANCE_NAME`_SIE_EP1_CR0_IND + ptr),
                                                                                    `$INSTANCE_NAME`_EP[ep].epMode);
                        }
                    }
                #endif /*  `$INSTANCE_NAME`_EP_MM */

                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

                CY_SET_REG8((reg8 *)(`$INSTANCE_NAME`_ARB_EP1_SR_IND + ptr), ep_status);   /* Clear Serviced events */
            }
            ptr += `$INSTANCE_NAME`_EPX_CNTX_ADDR_OFFSET;               /* prepare pointer for next EP */
            ep++;
            int_status >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */
    }

#endif /*  `$INSTANCE_NAME`_EP_MM */

#if ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_DMA_DONE_ISR
    *******************************************************************************
    *
    * Summary:
    *  Endpoint 1 DMA Done Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    ******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_DMA_DONE_ISR)
    {
        uint8 int8Status;
        uint8 int17Status;
        uint8 ep_status;
        uint8 ep = `$INSTANCE_NAME`_EP1;
        uint8 ptr = 0u;

        /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Read clear on read status register with the EP source of interrupt */
        int17Status = `$INSTANCE_NAME`_EP17_DMA_Done_SR_Read() & `$INSTANCE_NAME`_EP17_SR_MASK;
        int8Status = `$INSTANCE_NAME`_EP8_DMA_Done_SR_Read() & `$INSTANCE_NAME`_EP8_SR_MASK;

        while(int8Status != 0u)
        {
            while(int17Status != 0u)
            {
                if((int17Status & 1u) != 0u)  /* If EpX interrupt present */
                {
                    /* Read Endpoint Status Register */
                    ep_status = CY_GET_REG8((reg8 *)(`$INSTANCE_NAME`_ARB_EP1_SR_IND + ptr));
                    if( ((ep_status & `$INSTANCE_NAME`_ARB_EPX_SR_IN_BUF_FULL) == 0u) &&
                        (`$INSTANCE_NAME`_inBufFull[ep] == 0u))
                    {
                        /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                        /* `#END` */

                        CY_SET_REG8((reg8 *)(`$INSTANCE_NAME`_ARB_RW1_WA_MSB_IND + ptr), 0x00u);
                        /* repeat 2 last bytes to prefetch endpoint area */
                        CY_SET_REG8((reg8 *)(`$INSTANCE_NAME`_ARB_RW1_WA_IND + ptr),
                                    `$INSTANCE_NAME`_DMA_BYTES_PER_BURST * ep - `$INSTANCE_NAME`_DMA_BYTES_REPEAT);
                        `$INSTANCE_NAME`_LoadNextInEP(ep, 1);
                        /* Set Data ready status, This will generate DMA request */
                        * (reg8 *)(`$INSTANCE_NAME`_ARB_EP1_CFG_IND + ptr) |= `$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY;
                    }
                }
                ptr += `$INSTANCE_NAME`_EPX_CNTX_ADDR_OFFSET;               /* prepare pointer for next EP */
                ep++;
                int17Status >>= 1u;
            }
            int8Status >>= 1u;
            if(int8Status != 0)
            {
                /* Prepare pointer for EP8 */
                ptr = ((`$INSTANCE_NAME`_EP8 - `$INSTANCE_NAME`_EP1) << `$INSTANCE_NAME`_EPX_CNTX_ADDR_SHIFT);
                ep = `$INSTANCE_NAME`_EP8;
                int17Status = int8Status & 0x01u;
            }
        }

        /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

        /* `#END` */
    }
#endif /* ((`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO) && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */


/* [] END OF FILE */
