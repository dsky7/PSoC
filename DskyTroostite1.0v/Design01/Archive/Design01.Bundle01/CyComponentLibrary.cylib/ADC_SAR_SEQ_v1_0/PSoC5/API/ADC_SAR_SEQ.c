/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the API functionality of the ADC SAR Sequencer Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_SAR.h"
#if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
    #include <`$INSTANCE_NAME`_IRQ.H>
#endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */

static void `$INSTANCE_NAME`_TempBufDmaInit(void);
static void `$INSTANCE_NAME`_TempBufDmaRelease(void);

static void `$INSTANCE_NAME`_FinalBufDmaInit(void);
static void `$INSTANCE_NAME`_FinalBufDmaRelease(void);

static int16 `$INSTANCE_NAME`_tempArray[`$INSTANCE_NAME`_NUMBER_OF_CHANNELS];
int16  `$INSTANCE_NAME`_finalArray[`$INSTANCE_NAME`_NUMBER_OF_CHANNELS];
uint32 `$INSTANCE_NAME`_initVar = 0u;
static uint8 `$INSTANCE_NAME`_tempChan;
static uint8 `$INSTANCE_NAME`_finalChan;
static uint8 `$INSTANCE_NAME`_tempTD;
static uint8 `$INSTANCE_NAME`_finalTD;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TempBufDmaInit()
********************************************************************************
*
* Summary:
*  Provides initialization procedure for the TempBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_TempBufDmaInit(void)
{
    `$INSTANCE_NAME`_tempTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the destination address, but not the source address
    */
    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_tempTD, `$INSTANCE_NAME`_TEMP_TRANSFER_COUNT,
        `$INSTANCE_NAME`_tempTD, ((uint8)`$INSTANCE_NAME`_TempBuf__TD_TERMOUT_EN | (uint8)TD_INC_DST_ADR));

    /* From the SAR to the TempArray */
    (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_tempTD, (uint16)(LO16((uint32)`$INSTANCE_NAME`_SAR_DATA_ADDR_0)),
        (uint16)(LO16((uint32)`$INSTANCE_NAME`_tempArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_tempChan, `$INSTANCE_NAME`_tempTD);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TempBufDmaRelease()
********************************************************************************
*
* Summary:
*  Provides release procedure for the TempBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_TempBufDmaRelease(void)
{
    (void) CyDmaChDisable(`$INSTANCE_NAME`_tempChan);

    /* Clear any potential DMA requests and re-reset TD pointers */
    while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_tempChan].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
    {
        ; /* Wait for to be cleared */
    }

    (void) CyDmaChSetRequest(`$INSTANCE_NAME`_tempChan, CY_DMA_CPU_TERM_CHAIN);
    (void) CyDmaChEnable    (`$INSTANCE_NAME`_tempChan, 1u);

    while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_tempChan].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

    /* Release allocated TD and mark it as invalid */
    CyDmaTdFree(`$INSTANCE_NAME`_tempTD);
    `$INSTANCE_NAME`_tempTD = CY_DMA_INVALID_TD;

}


/****************************************************************************
* Function Name: `$INSTANCE_NAME`_FinalBufDmaInit()
*****************************************************************************
*
* Summary:
*  Provides initialization procedure for the FinalBuf DMA
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
static void `$INSTANCE_NAME`_FinalBufDmaInit(void)
{
    `$INSTANCE_NAME`_finalTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - The TD is looping on itself
    *  - Increment the source and destination address
    */
    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_finalTD, ((uint16)`$INSTANCE_NAME`_FINAL_BYTES_PER_BURST),
        `$INSTANCE_NAME`_finalTD, ((uint8)(`$INSTANCE_NAME`_FinalBuf__TD_TERMOUT_EN) | (uint8)TD_INC_SRC_ADR |
            (uint8)TD_INC_DST_ADR));

    /* From the the TempArray to Final Array */
    (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_finalTD, (uint16)(LO16((uint32)`$INSTANCE_NAME`_tempArray)),
        (uint16)(LO16((uint32)`$INSTANCE_NAME`_finalArray)));

    /* Associate the TD with the channel */
    (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_finalChan, `$INSTANCE_NAME`_finalTD);
}


/****************************************************************************
* Function Name: `$INSTANCE_NAME`_FinalBufDmaRelease()
*****************************************************************************
*
* Summary:
*  Provides release procedure for the FinalBuf DMA.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
static void `$INSTANCE_NAME`_FinalBufDmaRelease(void)
{
    (void) CyDmaChDisable(`$INSTANCE_NAME`_finalChan);

    /* Clear any potential DMA requests and re-reset TD pointers */
    while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_finalChan].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
    {
        ; /* Wait for to be cleared */
    }

    (void) CyDmaChSetRequest(`$INSTANCE_NAME`_finalChan, CY_DMA_CPU_TERM_CHAIN);
    (void) CyDmaChEnable    (`$INSTANCE_NAME`_finalChan, 1u);

    while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_finalChan].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

    /* Release allocated TD and mark it as invalid */
    CyDmaTdFree(`$INSTANCE_NAME`_finalTD);
    `$INSTANCE_NAME`_finalTD = CY_DMA_INVALID_TD;
}


/****************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable()
*****************************************************************************
*
* Summary:
*  Disables the component without disabling the ADC SAR.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
****************************************************************************/
void `$INSTANCE_NAME`_Disable(void)
{
    uint8 enableInterrupts;

    `$INSTANCE_NAME`_CONTROL_REG &= ((uint8)(~`$INSTANCE_NAME`_BASE_COMPONENT_ENABLE));

    /* Disable Counter */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CYCLE_COUNTER_AUX_CONTROL_REG &= ((uint8)(~`$INSTANCE_NAME`_CYCLE_COUNTER_ENABLE));
    CyExitCriticalSection(enableInterrupts);
    `$INSTANCE_NAME`_COUNT_REG = 0u;

    `$INSTANCE_NAME`_TempBufDmaRelease();
    `$INSTANCE_NAME`_FinalBufDmaRelease();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Inits channels for DMA transfer. Provides loading period to the AMUX address
*  selection counter
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    /* Init DMA, 2 bytes bursts, each burst requires a request */
    `$INSTANCE_NAME`_tempChan = `$INSTANCE_NAME`_TempBuf_DmaInitialize(`$INSTANCE_NAME`_TEMP_BYTES_PER_BURST,
        `$INSTANCE_NAME`_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_PERIPH_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    /* Init DMA, (`$INSTANCE_NAME`_NUMBER_OF_CHANNELS << 1u) bytes bursts, each burst requires a request */
    `$INSTANCE_NAME`_finalChan = `$INSTANCE_NAME`_FinalBuf_DmaInitialize(`$INSTANCE_NAME`_FINAL_BYTES_PER_BURST,
        `$INSTANCE_NAME`_REQUEST_PER_BURST, (uint16)(HI16(CYDEV_SRAM_BASE)), (uint16)(HI16(CYDEV_SRAM_BASE)));

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Set the ISR to point to the ADC_SAR_SEQ_1_IRQ Interrupt. */
        `$INSTANCE_NAME`_IRQ_SetVector(&`$INSTANCE_NAME`_ISR);
        /* Set the priority. */
        `$INSTANCE_NAME`_IRQ_SetPriority((uint8)`$INSTANCE_NAME`_INTC_NUMBER);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables DMA channels, address selection counter and FSM of Base component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 enableInterrupts;

    `$INSTANCE_NAME`_FinalBufDmaInit();
    `$INSTANCE_NAME`_TempBufDmaInit();

    (void) CyDmaChEnable(`$INSTANCE_NAME`_tempChan, 1u);
    (void) CyDmaChEnable(`$INSTANCE_NAME`_finalChan, 1u);

    /* Enable Counter and give Enable pulse to set an address of the last channel */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CYCLE_COUNTER_AUX_CONTROL_REG |= ((uint8)(`$INSTANCE_NAME`_CYCLE_COUNTER_ENABLE));
    CyExitCriticalSection(enableInterrupts);

    /* Enable FSM of the Base Component */
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint8)(`$INSTANCE_NAME`_BASE_COMPONENT_ENABLE));
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint8)(`$INSTANCE_NAME`_LOAD_COUNTER_PERIOD));

    #if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(`$INSTANCE_NAME`_INTC_NUMBER);
    #endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
    `$INSTANCE_NAME`_SAR_Start();
    (void) CY_GET_REG8(`$INSTANCE_NAME`_STATUS_PTR);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_SAR_Stop();
    `$INSTANCE_NAME`_Disable();
}

#if(`$INSTANCE_NAME`_SAMPLE_MODE != `$INSTANCE_NAME`_SAMPLE_MODE_HW_TRIGGERED)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  When the Sample Mode parameter is set to 'Free Running', the component will
    * operate in a continuous mode. The channels will be scanned continuously until
    * _StopConvert()or  _Stop() is called
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_StartConvert(void)
    {
        #if(`$INSTANCE_NAME`_SAMPLE_MODE != `$INSTANCE_NAME`_SAMPLE_MODE_FREE_RUNNING)

            `$INSTANCE_NAME`_CONTROL_REG |= ((uint8)(`$INSTANCE_NAME`_SOFTWARE_SOC_PULSE));

        #else

            `$INSTANCE_NAME`_SAR_StartConvert();

        #endif /* 
                #if(`$INSTANCE_NAME`_SAMPLE_MODE != 
                `$INSTANCE_NAME`_SAMPLE_MODE_FREE_RUNNING) 
               */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the component to stop all conversions
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_StopConvert(void)
    {
        `$INSTANCE_NAME`_SAR_StopConvert();
    }

#endif /* `$INSTANCE_NAME`_SAMPLE_MODE != `$INSTANCE_NAME`_SAMPLE_MODE_HW_TRIGGERED */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
********************************************************************************
*
* Summary:
*  Checks for ADC end of conversion for the case one channel and end of scan
*  for the case of multiple channels
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
      status = `$INSTANCE_NAME`_STATUS_REG;
    } while ((status == 0u) && (retMode == `$INSTANCE_NAME`_WAIT_FOR_RESULT));

    return((uint32)status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult16
********************************************************************************
*
* Summary:
*  Returns the ADC result for channel 'chan
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetResult16(uint16 chan)
{
    return (`$INSTANCE_NAME`_finalArray[`$INSTANCE_NAME`_GET_RESULT_INDEX_OFFSET - chan] - `$INSTANCE_NAME`_SAR_shift);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAdcResult
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA register, not the results buffer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_GetAdcResult(void)
{
    return (`$INSTANCE_NAME`_SAR_GetResult16());
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset which is used by the functions _CountsTo_uVolts(),
*  _CountsTo_mVolts() and _CountsTo_Volts() to substract the offset from the
*  given reading before calculating the voltage conversion
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOffset(int32 offset)
{
    `$INSTANCE_NAME`_SAR_SetOffset((int16)offset);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*  This function does not affect the actual conversion with PSoC5 ES1 silicon.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC_SAR_Seq resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_SAR_Seq_StopConvert(), change the resolution, then restart the
*  conversions with ADC_SAR_Seq_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_SAR_Seq_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SAR_Seq_SetResolution() is called before data is valid again.
*  Affects ADC_SAR_Seq_CountsTo_Volts(), ADC_SAR_Seq_CountsTo_mVolts(), and
*  ADC_SAR_Seq_CountsTo_uVolts() by calculating the correct conversion between
*  ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetResolution(uint8 resolution)
{
    `$INSTANCE_NAME`_SAR_SetResolution(resolution);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetGain(int32 adcGain)
{
    `$INSTANCE_NAME`_SAR_SetGain((int16)adcGain);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to mVolts as a 32-bit integer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_mVolts(int16 adcCounts)
{
    return ((int32) `$INSTANCE_NAME`_SAR_CountsTo_mVolts(adcCounts));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to uVolts as a 32-bit integer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_uVolts(int16 adcCounts)
{
    return (`$INSTANCE_NAME`_SAR_CountsTo_uVolts(adcCounts));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to Volts as a floating point number
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_CountsTo_Volts(int16 adcCounts)
{
    return (`$INSTANCE_NAME`_SAR_CountsTo_Volts(adcCounts));
}


/* [] END OF FILE */
