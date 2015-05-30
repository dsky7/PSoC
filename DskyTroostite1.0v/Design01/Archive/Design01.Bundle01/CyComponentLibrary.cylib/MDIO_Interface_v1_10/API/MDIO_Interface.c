/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the MDIO Slave component.
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

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

    #include "`$INSTANCE_NAME`_REG.h"
    #include "`$INSTANCE_NAME`_StartAddrDMA_dma.h"
    #include "`$INSTANCE_NAME`_EndAddrDMA_dma.h"
    #include "`$INSTANCE_NAME`_AddrDMA_dma.h"
    #include "`$INSTANCE_NAME`_InfoDMA_dma.h"
    #include "`$INSTANCE_NAME`_RdDMA_dma.h"
    #include "`$INSTANCE_NAME`_WrDMA_dma.h"
    #include "`$INSTANCE_NAME`_CfgDMA1_dma.h"
    #include "`$INSTANCE_NAME`_CfgDMA2_dma.h"
    #include "`$INSTANCE_NAME`_FwDMA1_dma.h"
    #if(CY_PSOC5)
        #include "`$INSTANCE_NAME`_FwDMA2_dma.h"
    #endif /* CY_PSOC5 */

`$StartAddresses`
`$EndAddresses`

    /* Register page start address DMA */
    static uint8 `$INSTANCE_NAME`_pageStartAddrDMA_Chan;
    static uint8 `$INSTANCE_NAME`_pageStartAddr_TD[1u];

    /* Register page end address DMA */
    static uint8 `$INSTANCE_NAME`_pageEndAddrDMA_Chan;
    static uint8 `$INSTANCE_NAME`_pageEndAddr_TD[1u];

    /* Register physical memory address DMA */
    static uint8 `$INSTANCE_NAME`_regAddrDMA_Chan;
    static uint8 `$INSTANCE_NAME`_regAddrDMA_TD[7u];

    /* Register page info DMA */
    static uint8 `$INSTANCE_NAME`_pageInfoDMA_Chan;
    static uint8 `$INSTANCE_NAME`_pageInfoDMA_TD[1u];

    /* Read DMA */
    static uint8 `$INSTANCE_NAME`_rdDMA_Chan;
    static uint8 `$INSTANCE_NAME`_rdDMA_TD[1u];

    /* Write DMA */
    static uint8 `$INSTANCE_NAME`_wrDMA_Chan;
    static uint8 `$INSTANCE_NAME`_wrDMA_TD[1u];

    /* Register configuration DMA */
    static uint8 `$INSTANCE_NAME`_cfgDMA1_Chan;
    static uint8 `$INSTANCE_NAME`_cfgDMA1_TD[1u];
    static uint8 `$INSTANCE_NAME`_cfgDMA2_Chan;
    static uint8 `$INSTANCE_NAME`_cfgDMA2_TD[2u];

    /* DMA used for data transfer from APIs */
    static uint8 `$INSTANCE_NAME`_fwDMA1_Chan;
    #if(CY_PSOC3)
        static uint8 `$INSTANCE_NAME`_fwDMA1_TD[2u];
    #else /* PSoC 5 requires one more DMA */
        static uint8 `$INSTANCE_NAME`_fwDMA1_TD[1u];
        static uint8 `$INSTANCE_NAME`_fwDMA2_Chan;
        static uint8 `$INSTANCE_NAME`_fwDMA2_TD[1u];
    #endif /* CY_PSOC5 */

    /* List of DMA channels used by the component */
    static uint8 `$INSTANCE_NAME`_dmaChannelList[`$INSTANCE_NAME`_NUMBER_OF_CHANNELS];

    /* Address list of all register space data and configuration arrays */
    static uint32 `$INSTANCE_NAME`_pageAddrList[`$INSTANCE_NAME`_NUMBER_OF_PAGES];
    uint32 `$INSTANCE_NAME`_pageInfoList[`$INSTANCE_NAME`_PAGE_INFO_SIZE];

    /* Function prototype to configure/release DMA */
    static void  `$INSTANCE_NAME`_DmaInit(void)                     `=ReentrantKeil($INSTANCE_NAME . "_DmaInit")`;
    static void  `$INSTANCE_NAME`_DmaEnable(void)                   `=ReentrantKeil($INSTANCE_NAME . "_DmaEnable")`;
    static void  `$INSTANCE_NAME`_DmaDisable(void)                  `=ReentrantKeil($INSTANCE_NAME . "_DmaDisable")`;
    static uint8 `$INSTANCE_NAME`_DmaIsComplete(uint8 channel)      `=ReentrantKeil($INSTANCE_NAME . "_DmaIsComplete")`;

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

uint8 `$INSTANCE_NAME`_initVar = 0u;
static uint8 `$INSTANCE_NAME`_phyAddress;
static uint8 `$INSTANCE_NAME`_devAddress;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the MDIO Slave hardware.
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
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Bit counter enabling */
    `$INSTANCE_NAME`_BCNT_AUX_CTL_REG   |= `$INSTANCE_NAME`_BCNT_EN;
    CyExitCriticalSection(enableInterrupts);

    #if(`$INSTANCE_NAME`_ADVANCED_MODE)
        `$INSTANCE_NAME`_DmaEnable();
    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

    /* Enable interrupts */
    `$INSTANCE_NAME`_EnableInt();

    /* Enable the component hardware */
    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the component, sets the physical and device address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    #if(`$INSTANCE_NAME`_ADVANCED_MODE)
        static uint8 `$INSTANCE_NAME`_dmaInitDone = 0u;
    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */
    uint8 enableInterrupts;

    /* Set the device address */
    `$INSTANCE_NAME`_SetDevAddress(`$INSTANCE_NAME`_INIT_DEVADDR);
    /* Set the physical address */
    `$INSTANCE_NAME`_UpdatePhyAddress();

    enableInterrupts = CyEnterCriticalSection();
    /* Set Read FIFO in the Single Buffer Mode */
    `$INSTANCE_NAME`_FP_AUX_CTL0_REG |= `$INSTANCE_NAME`_F0_CLEAR;
    `$INSTANCE_NAME`_FP_AUX_CTL1_REG |= `$INSTANCE_NAME`_F0_CLEAR;
    CyExitCriticalSection(enableInterrupts);

    /* Set bit counter period */
    `$INSTANCE_NAME`_BCNT_PERIOD_REG = `$INSTANCE_NAME`_BCNT_PER;

    #if(`$INSTANCE_NAME`_ADVANCED_MODE)

        /* Set the size of register page info */
        CY_SET_REG16(`$INSTANCE_NAME`_INFO_INC_PTR, `$INSTANCE_NAME`_PAGE_INFO_INC);
        /* Set the lower 16-bit address of the page info array */
        CY_SET_REG16(`$INSTANCE_NAME`_INFO_BASE_PTR, LO16((uint32)`$INSTANCE_NAME`_pageInfoList));
        /* Set memory type of the each register page */
        `$INSTANCE_NAME`_MEM_TYPE_REG   = `$INSTANCE_NAME`_PAGE_MEM_TYPE;
        /* Set data width of the each register page */
        `$INSTANCE_NAME`_PAGE_WIDTH_REG = `$INSTANCE_NAME`_PAGE_DATA_WIDTH;
        /* Initialize Address analyzer DMAs */
        if(0u == `$INSTANCE_NAME`_dmaInitDone)
        {
            `$INSTANCE_NAME`_DmaInit();
            `$INSTANCE_NAME`_dmaInitDone = 1u;
        }

    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Enables the component. Calls the Init() API if the component has not been
*  initialized before. Calls the Enable() API.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the MDIO interface.
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
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;

    `$INSTANCE_NAME`_CONTROL_REG &= (uint8) ~`$INSTANCE_NAME`_EN;

    /* Disable the interrupt terminal */
    `$INSTANCE_NAME`_DisableInt();

    /* Disable Address analyzer DMAs */
    #if(`$INSTANCE_NAME`_ADVANCED_MODE)
        `$INSTANCE_NAME`_DmaDisable();
    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

    enableInterrupts = CyEnterCriticalSection();
    /* Disable Bit counter */
    `$INSTANCE_NAME`_BCNT_AUX_CTL_REG  &= (uint8) ~`$INSTANCE_NAME`_BCNT_EN;

    #if(`$INSTANCE_NAME`_ADVANCED_MODE)
        /* Clear start and end address FIFO buffers */
        `$INSTANCE_NAME`_AC_AUX_CTL0_REG |= `$INSTANCE_NAME`_FX_CLEAR;
        `$INSTANCE_NAME`_AC_AUX_CTL0_REG &= (uint8) ~`$INSTANCE_NAME`_FX_CLEAR;
        `$INSTANCE_NAME`_AC_AUX_CTL1_REG |= `$INSTANCE_NAME`_FX_CLEAR;
        `$INSTANCE_NAME`_AC_AUX_CTL1_REG &= (uint8) ~`$INSTANCE_NAME`_FX_CLEAR;
    #endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

    /* Clear Write FIFO buffer */
    `$INSTANCE_NAME`_FP_AUX_CTL0_REG |= `$INSTANCE_NAME`_F1_CLEAR;
    `$INSTANCE_NAME`_FP_AUX_CTL0_REG &= (uint8) ~`$INSTANCE_NAME`_F1_CLEAR;
    `$INSTANCE_NAME`_FP_AUX_CTL1_REG |= `$INSTANCE_NAME`_F1_CLEAR;
    `$INSTANCE_NAME`_FP_AUX_CTL1_REG &= (uint8) ~`$INSTANCE_NAME`_F1_CLEAR;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableInt
********************************************************************************
*
* Summary:
*  Enables the terminal output interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`
{
    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_INT_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableInt
********************************************************************************
*
* Summary:
*  Enables the terminal output interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`
{
    `$INSTANCE_NAME`_CONTROL_REG &= (uint8) ~`$INSTANCE_NAME`_INT_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDevAddress
********************************************************************************
* Summary:
*  Sets the 5 bits device address for the MDIO slave.
*
* Parameters:
*  Byte containing the constant for the MDIO device address.
*   `$INSTANCE_NAME`_PMA_PMD
*   `$INSTANCE_NAME`_WIS
*   `$INSTANCE_NAME`_PCS
*   `$INSTANCE_NAME`_PHY_XS
*   `$INSTANCE_NAME`_DTE_XS
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
********************************************************************************/
void `$INSTANCE_NAME`_SetDevAddress(uint8 devAddr) `=ReentrantKeil($INSTANCE_NAME . "_SetDevAddress")`
{
    /* Update the address pattern with the device address */
    CY_SET_REG16(`$INSTANCE_NAME`_ADDR_PTRN_PTR, `$INSTANCE_NAME`_ADDR_PATTERN |
                 (uint16)((uint16)`$INSTANCE_NAME`_phyAddress << `$INSTANCE_NAME`_PHYADDR_POS) | devAddr);
    `$INSTANCE_NAME`_devAddress = devAddr;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPhyAddress
********************************************************************************
* Summary:
*  Sets the 5 bits physical address for the MDIO slave device.
*
* Parameters:
*  The physical address for the MDIO Slave.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
********************************************************************************/
void `$INSTANCE_NAME`_SetPhyAddress(uint8 phyAddr) `=ReentrantKeil($INSTANCE_NAME . "_SetPhyAddress")`
{
    /* Update the address pattern with the physical address */
    CY_SET_REG16(`$INSTANCE_NAME`_ADDR_PTRN_PTR, `$INSTANCE_NAME`_ADDR_PATTERN |
                 (uint16)((uint16) phyAddr << `$INSTANCE_NAME`_PHYADDR_POS) | `$INSTANCE_NAME`_devAddress);

    `$INSTANCE_NAME`_phyAddress = phyAddr;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdatePhyAddress
********************************************************************************
* Summary:
*  Updates the physical address based on the current phy_addr[4:0] input.
*  If the physical address mode is configured to firmware, the physical address
*  is set equal to the default value from the customizer.
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
********************************************************************************/
void `$INSTANCE_NAME`_UpdatePhyAddress(void) `=ReentrantKeil($INSTANCE_NAME . "_UpdatePhyAddress")`
{
    #if(`$INSTANCE_NAME`_PHYADDR_HARDWARE)
        `$INSTANCE_NAME`_SetPhyAddress(`$INSTANCE_NAME`_PHYADDR_REG);
    #else
        `$INSTANCE_NAME`_SetPhyAddress(`$INSTANCE_NAME`_INIT_PHYADDR);
    #endif /* `$INSTANCE_NAME`_PHYADDR_HARDWARE */
}

#if (`$INSTANCE_NAME`_BASIC_MODE)


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutData
    ****************************************************************************
    * Summary:
    *  Writes the given data in the internal FIFO, which will be transmitted to
    *  the host in the next frame.
    *
    * Parameters:
    *  Data to be transmitted.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    ****************************************************************************/
    void `$INSTANCE_NAME`_PutData(uint16 regData) `=ReentrantKeil($INSTANCE_NAME . "_PutData")`
    {
        CY_SET_REG16(`$INSTANCE_NAME`_FP_FIFO0_PTR, regData);
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ProcessFrame
    ****************************************************************************
    * Summary:
    *  Process and parse the the last frame received from the host.
    *
    * Parameters:
    *  opCode: operational code.
    *  regData: register data received.
    *
    * Return:
    *  None.
    *
    ****************************************************************************/
    void `$INSTANCE_NAME`_ProcessFrame(uint8 * opCode, uint16 * regData)
                                                                     `=ReentrantKeil($INSTANCE_NAME . "_ProcessFrame")`
    {
        uint16 controlBits;

        /* Get the control bits */
        controlBits = CY_GET_REG16(`$INSTANCE_NAME`_FP_FIFO1_PTR);

        /* Get the data */
        *regData = CY_GET_REG16(`$INSTANCE_NAME`_FP_FIFO1_PTR);

        /* Parse the Control bits to obtain the operation code */
        *opCode = (((uint8)(controlBits >> `$INSTANCE_NAME`_OPCODE_POS)) & `$INSTANCE_NAME`_OPCODE_MASK);
    }

#endif /* `$INSTANCE_NAME`_BASIC_MODE */

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAddress
    ****************************************************************************
    * Summary:
    *  Returns the last address written by the MDIO host.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  16-bit address.
    *
    ***************************************************************************/
    uint16 `$INSTANCE_NAME`_GetAddress(void)    `=ReentrantKeil($INSTANCE_NAME . "_GetAddress")`
    {
        return(CY_GET_REG16(`$INSTANCE_NAME`_LAST_ADDR_PTR));
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetData
    ****************************************************************************
    * Summary:
    *  Returns numWords values starting from the given address. If any address
    *  does not belong to the allocated register space, it returns an error.
    *
    * Parameters:
    *  uint16  address: address to be accessed.
    *  uint16 *regData: array with the read data.
    *  uint8  numWords: number of words to be read.
    *
    * Return:
    *  CYRET_SUCCESS  : Operation is successful.
    *  CYRET_BAD_PARAM: One or more invalid parameters.
    *  CYRET_TIMEOUT  : Operation timed out.
    *
    * Side Effects:
    *  The word count of zero will be interpreted as a request for indefinite
    *  transfer.
    *
    ****************************************************************************/
    uint8 `$INSTANCE_NAME`_GetData(uint16 address, uint16 * regData, uint16 numWords)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetData")`
    {
        uint8  i;
        uint8  result = CYRET_BAD_PARAM;
        uint16 idx;
        uint32 memAddr;

        for(i = 0u; (i < `$INSTANCE_NAME`_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
        {
            /* Check if the address belongs to one of the register spaces */
            if((address >= `$INSTANCE_NAME`_pageStartAddr[i]) && (address <= `$INSTANCE_NAME`_pageEndAddr[i]))
            {
                /* Check whether there is enough data to be read */
                #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                    #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                    if(`$INSTANCE_NAME`_REG_SPACE_IS_8BIT(i))
                    #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */
                    {
                        numWords += numWords;
                    }
                #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */

                if(numWords <= ((`$INSTANCE_NAME`_pageEndAddr[i] - address) + 1u))
                {
                    idx = address - `$INSTANCE_NAME`_pageStartAddr[i];

                    #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                        #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                        if(`$INSTANCE_NAME`_REG_SPACE_IS_16BIT(i))
                        #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */
                        {
                            /* If a 16-bit space is accessed */
                            idx += idx;
                            numWords += numWords;
                        }
                    #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */

                    memAddr = `$INSTANCE_NAME`_pageAddrList[i] + idx;

                    /* Configure DMA transfer */
                    `$INSTANCE_NAME`_fwDMA1_Chan = `$INSTANCE_NAME`_FwDMA1_DmaInitialize(
                        `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST,
                        HI16(memAddr), HI16(CYDEV_SRAM_BASE));
                    #if(CY_PSOC5)
                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u], numWords, DMA_INVALID_TD,
                                                   TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN);
                    #else
                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u], numWords, DMA_INVALID_TD,
                                                   TD_INC_SRC_ADR | TD_INC_DST_ADR);
                    #endif /* CY_PSOC5 */
                    (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fwDMA1_TD[0u], LO16(memAddr), LO16((uint32)regData));
                    (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_fwDMA1_Chan, `$INSTANCE_NAME`_fwDMA1_TD[0u]);
                    (void) CyDmaChSetRequest(`$INSTANCE_NAME`_fwDMA1_Chan, CPU_REQ);

                    result = `$INSTANCE_NAME`_DmaIsComplete(`$INSTANCE_NAME`_fwDMA1_Chan);
                }
            }
        }
        return(result);
    }

    #if(!`$INSTANCE_NAME`_ALL_PAGES_IN_FLASH)

        /***************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetData
        ****************************************************************************
        * Summary:
        *  Writes numWords values starting from the given address. If any address
        *  does not belong to the allocated register space, it returns an error.
        *
        * Parameters:
        *  uint16 address : address to be accessed.
        *  uint16 *regData: array with the written data.
        *  uint8  numWords: number of words to be written.
        *
        * Return:
        *  CYRET_SUCCESS  : Operation is successful.
        *  CYRET_BAD_PARAM: One or more invalid parameters.
        *  CYRET_TIMEOUT  : Operation timed out.
        *
        * Side Effects:
        *  The word count of zero will be interpreted as a request for indefinite
        *  transfer.
        *
        ***************************************************************************/
        uint8 `$INSTANCE_NAME`_SetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetData")`
        {
            uint8 result = CYRET_BAD_PARAM;
            uint8 i;
            uint16 idx;
            uint32 memAddr;

            for(i = 0u; (i < `$INSTANCE_NAME`_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
            {
                /* Check if the address belongs to one of the register spaces */
                if((address >= `$INSTANCE_NAME`_pageStartAddr[i]) && (address <= `$INSTANCE_NAME`_pageEndAddr[i]))
                {
                    #if(!`$INSTANCE_NAME`_ALL_PAGES_IN_SRAM)
                    /* Check whether the current space is writable */
                    if(`$INSTANCE_NAME`_REG_SPACE_IS_SRAM(i))
                    #endif /* !`$INSTANCE_NAME`_ALL_PAGES_IN_SRAM */
                    {
                        /* Check whether there is enough space to be written */
                        #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                            #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                            if(`$INSTANCE_NAME`_REG_SPACE_IS_8BIT(i))
                            #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */
                            {
                                numWords += numWords;
                            }
                        #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */

                        if(numWords <= ((`$INSTANCE_NAME`_pageEndAddr[i] - address) + 1u))
                        {
                            idx = address - `$INSTANCE_NAME`_pageStartAddr[i];

                            #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                                #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                                if(`$INSTANCE_NAME`_REG_SPACE_IS_16BIT(i))
                                #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */
                                {
                                    /* If a 16-bit space is accessed */
                                    idx += idx;
                                    numWords += numWords;
                                }
                            #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */

                            memAddr = `$INSTANCE_NAME`_pageAddrList[i] + idx;

                            /* Configure DMA transfer */
                            `$INSTANCE_NAME`_fwDMA1_Chan = `$INSTANCE_NAME`_FwDMA1_DmaInitialize(
                                `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST,
                                HI16(CYDEV_SRAM_BASE), HI16(CYDEV_SRAM_BASE));

                            #if(CY_PSOC5)
                                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u], numWords, DMA_INVALID_TD,
                                                                TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN);
                            #else
                                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u], numWords, DMA_INVALID_TD,
                                                                TD_INC_SRC_ADR | TD_INC_DST_ADR);
                            #endif /* CY_PSOC5 */

                            (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fwDMA1_TD[0u], LO16((uint32)regData),
                                                                                     LO16(memAddr));
                            (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_fwDMA1_Chan, `$INSTANCE_NAME`_fwDMA1_TD[0u]);
                            (void) CyDmaChSetRequest(`$INSTANCE_NAME`_fwDMA1_Chan, CPU_REQ);

                            result = `$INSTANCE_NAME`_DmaIsComplete(`$INSTANCE_NAME`_fwDMA1_Chan);
                        }
                    }
                }
            }
            return(result);
        }


        /***************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetBits
        ****************************************************************************
        * Summary:
        *  Set at the given address only the given bits. The operation should be an
        *  OR write.
        *
        * Parameters:
        *  uint16 address: address to be accessed.
        *  uint16 regBits: bits to be set.
        *
        * Return:
        *  CYRET_SUCCESS  : Operation is successful.
        *  CYRET_BAD_PARAM: One or more invalid parameters.
        *  CYRET_TIMEOUT  : Operation timed out.
        *
        ***************************************************************************/
        uint8 `$INSTANCE_NAME`_SetBits(uint16 address, uint16 regBits) `=ReentrantKeil($INSTANCE_NAME . "_SetBits")`
        {
            uint8  result = CYRET_BAD_PARAM;
            uint8  i;
            uint16 idx;
            uint32 memAddr;
            /* Assuming 16-bit register space by default */
            uint8  numWords = `$INSTANCE_NAME`_NUM_OF_16BIT_REGS;

            for(i = 0u; (i < `$INSTANCE_NAME`_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
            {
                /* Check if the address belongs to one of the register spaces */
                if((address >= `$INSTANCE_NAME`_pageStartAddr[i]) && (address <= `$INSTANCE_NAME`_pageEndAddr[i]))
                {
                    #if(!`$INSTANCE_NAME`_ALL_PAGES_IN_SRAM)
                    /* Check whether the current space is writable */
                    if(`$INSTANCE_NAME`_REG_SPACE_IS_SRAM(i))
                    #endif /* !`$INSTANCE_NAME`_ALL_PAGES_IN_SRAM */
                    {
                        /* Check whether there is enough space to be written */
                        #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                            #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                            if(`$INSTANCE_NAME`_REG_SPACE_IS_8BIT(i))
                            #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */
                            {
                                numWords = `$INSTANCE_NAME`_NUM_OF_8BIT_REGS;
                            }
                        #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */

                        if(numWords <= ((`$INSTANCE_NAME`_pageEndAddr[i] - address) + 1u))
                        {
                            idx = address - `$INSTANCE_NAME`_pageStartAddr[i];

                            #if(!`$INSTANCE_NAME`_ALL_PAGES_8BIT)
                                #if(!`$INSTANCE_NAME`_ALL_PAGES_16BIT)
                                if(`$INSTANCE_NAME`_REG_SPACE_IS_16BIT(i))
                                #endif /* !`$INSTANCE_NAME`_ALL_PAGES_16BIT */
                                {
                                    /* If a 16-bit space is accessed */
                                    idx += idx;
                                }
                            #endif /* !`$INSTANCE_NAME`_ALL_PAGES_8BIT */

                            memAddr = `$INSTANCE_NAME`_pageAddrList[i] + idx;

                            /* Write bits to set to A1 reg of the FwAlu datapath */
                            CY_SET_REG16(`$INSTANCE_NAME`_REG_BITS_PTR, regBits);

                            /* Two bytes transfer in a single burst */
                            `$INSTANCE_NAME`_fwDMA1_Chan = `$INSTANCE_NAME`_FwDMA1_DmaInitialize(
                                `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST,
                                HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

                            #if(CY_PSOC3)
                                /* Single DMA channel with two associated TDs to
                                * transfer from SRAM to UDB and vice versa.
                                */
                                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u],
                                    `$INSTANCE_NAME`_FW_DMA_TD_SIZE,`$INSTANCE_NAME`_fwDMA1_TD[1u], TD_INC_SRC_ADR |
                                    TD_AUTO_EXEC_NEXT | TD_SWAP_EN | `$INSTANCE_NAME`_FwDMA1__TD_TERMOUT_EN);

                                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[1u],
                                    `$INSTANCE_NAME`_FW_DMA_TD_SIZE, DMA_INVALID_TD, TD_SWAP_EN | TD_INC_DST_ADR);

                                /* Result of OR operation from the FwAlu datapath to
                                * the register memory.
                                */
                                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fwDMA1_TD[1u],
                                    LO16((uint32)`$INSTANCE_NAME`_REG_VAL_PTR), LO16(memAddr));
                            #else
                                /* Two DMA channels, each channel uses one TD.
                                * Ch1: from the register memory to the FwAlu;
                                * Ch2: from the FwAlu to the register memory.
                                */
                                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA1_TD[0u],
                                    `$INSTANCE_NAME`_FW_DMA_TD_SIZE, DMA_INVALID_TD,
                                    TD_SWAP_EN | `$INSTANCE_NAME`_FwDMA1__TD_TERMOUT_EN);

                                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fwDMA2_TD[0u],
                                    LO16((uint32)`$INSTANCE_NAME`_REG_VAL_PTR), LO16(memAddr));
                            #endif /* CY_PSOC3 */

                            /* From the register memory to the FwAlu datapath */
                            (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fwDMA1_TD[0u], LO16(memAddr),
                                LO16((uint32)`$INSTANCE_NAME`_REG_VAL_PTR));
                            (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_fwDMA1_Chan, `$INSTANCE_NAME`_fwDMA1_TD[0u]);

                            /* Trigger the DMA */
                            `$INSTANCE_NAME`_CONTROL_REG ^= `$INSTANCE_NAME`_TRIG_DMA;

                            result = `$INSTANCE_NAME`_DmaIsComplete(`$INSTANCE_NAME`_fwDMA1_Chan);

                            #if(CY_PSOC5)
                                /* Check this channel only if the previous one has completed
                                * successfully.
                                */
                                if(result == CYRET_SUCCESS)
                                {
                                    result = `$INSTANCE_NAME`_DmaIsComplete(`$INSTANCE_NAME`_fwDMA2_Chan);
                                }
                            #endif /* CY_PSOC5 */
                        }
                    }
                }
            }
            return(result);
        }

    #endif /* `$INSTANCE_NAME`_ALL_PAGES_IN_FLASH */


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetConfiguration
    ****************************************************************************
    * Summary:
    *  Returns a pointer to the configuration array of the given regSpace.
    *
    * Parameters:
    *  uint8 regSpace: register space index.
    *
    * Return:
    *  Pointer to the configuration array if successful.
    *  NULL pointer if regSpace is invalid.
    *
    ***************************************************************************/
    uint8 * `$INSTANCE_NAME`_GetConfiguration(uint8 regSpace)   `=ReentrantKeil($INSTANCE_NAME . "_GetConfiguration")`
    {
        uint8 * config;
        config = NULL;

        if((regSpace > 0u) && (regSpace <= `$INSTANCE_NAME`_NUMBER_OF_PAGES))
        {
            regSpace += regSpace;
            regSpace--;
            config = (uint8 *)`$INSTANCE_NAME`_pageInfoList[regSpace];
        }
        return(config);
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_DmaComplete
    ****************************************************************************
    *
    * Summary:
    *  Determines whether a specified DMA channel has completed the transfer.
    *
    * Parameters:
    *  channel: DMA channel to check.
    *
    * Return:
    *  CYRET_SUCCESS: transfer has completed.
    *  CYRET_TIMEOUT: transfer has not completed and 255 us timeout expired.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    static uint8 `$INSTANCE_NAME`_DmaIsComplete(uint8 channel)
    {
        uint8 timer;

        timer = `$INSTANCE_NAME`_TIMEOUT_PERIOD;

        while(`$INSTANCE_NAME`_DMA_ACTIVE(channel) && (timer != 0u))
        {
            /* Channel is currently being serviced by DMAC and timeout period
            * is not elapsed.
            */
            timer--;
            CyDelayUs(1u);
        }
        return((timer != 0u) ? CYRET_SUCCESS : CYRET_TIMEOUT);
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_DmaEnable
    ****************************************************************************
    *
    * Summary:
    *  Enables Address Analyzer DMAs.
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
    ***************************************************************************/
    static void `$INSTANCE_NAME`_DmaEnable(void)   `=ReentrantKeil($INSTANCE_NAME . "_DmaEnable")`
    {
        uint8 i;

        /* Set initial TDs and enable address analyzer DMAs */
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_pageStartAddrDMA_Chan, `$INSTANCE_NAME`_pageStartAddr_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_pageEndAddrDMA_Chan,   `$INSTANCE_NAME`_pageEndAddr_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_pageInfoDMA_Chan,      `$INSTANCE_NAME`_pageInfoDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_regAddrDMA_Chan,       `$INSTANCE_NAME`_regAddrDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_rdDMA_Chan,            `$INSTANCE_NAME`_rdDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_wrDMA_Chan,            `$INSTANCE_NAME`_wrDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_cfgDMA1_Chan,          `$INSTANCE_NAME`_cfgDMA1_TD[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_cfgDMA2_Chan,          `$INSTANCE_NAME`_cfgDMA2_TD[0u]);

        for(i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_CHANNELS; i++)
        {
            (void) CyDmaChEnable(`$INSTANCE_NAME`_dmaChannelList[i], 1u);
        }

        /* Set initial TDs and enable firmware DMAs */
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_fwDMA1_Chan,           `$INSTANCE_NAME`_fwDMA1_TD[0u]);
        (void) CyDmaChEnable(`$INSTANCE_NAME`_fwDMA1_Chan, 1u);

        #if(CY_PSOC5)
            (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_fwDMA2_Chan,       `$INSTANCE_NAME`_fwDMA2_TD[0u]);
            (void) CyDmaChEnable(`$INSTANCE_NAME`_fwDMA2_Chan, 1u);
        #endif /* CY_PSOC5 */
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_DmaDisable
    ****************************************************************************
    *
    * Summary:
    *  Disable Address Analyzer DMAs.
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
    ***************************************************************************/
    static void `$INSTANCE_NAME`_DmaDisable(void)   `=ReentrantKeil($INSTANCE_NAME . "_DmaDisable")`
    {
        uint8 i;
        uint8 channel;

        for(i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_CHANNELS; i++)
        {
            channel = `$INSTANCE_NAME`_dmaChannelList[i];
            (void) CyDmaChDisable(channel);

            /* Clear any potential DMA requests and re-reset TD pointers */
            while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
            {
                ; /* Wait for to be cleared */
            }

            (void) CyDmaChSetRequest(channel, CY_DMA_CPU_TERM_CHAIN);
            (void) CyDmaChEnable    (channel, 1u);

            while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
            {
                ; /* Wait for to be cleared */
            }
        }
        /* Firmware DMAs do not transfer data when the Stop() API is called,
        * therefore they do not need to be reseted.
        */
        (void) CyDmaChDisable(`$INSTANCE_NAME`_fwDMA1_Chan);
        #if(CY_PSOC5)
            (void) CyDmaChDisable(`$INSTANCE_NAME`_fwDMA2_Chan);
        #endif /* CY_PSOC5 */
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_DmaInit
    ****************************************************************************
    *
    * Summary:
    *  Inits Address Analyzer DMAs.
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
    ***************************************************************************/
    static void `$INSTANCE_NAME`_DmaInit(void)      `=ReentrantKeil($INSTANCE_NAME . "_DmaInit")`
    {
        uint8 idx;
        static uint32 `$INSTANCE_NAME`_regConfig;

        /* For PSoC 3 the data are stored in a big endian ordering. However, the
        *  registers are laid out in little endian order. The byte ordering must
        *  be considered when use DMA to transfer between memory and registers.
        *  The upper 16 bits of the address must be 0 for SRAM and CYDEV_FLS_BASE
        *  for Flash.
        */
        #if(CY_PSOC3)
            uint8 pageMask = 0x01u;
            for(idx = 0u; idx < `$INSTANCE_NAME`_PAGE_INFO_SIZE; idx += 2u)
            {
                `$INSTANCE_NAME`_pageInfoList[idx] = (uint32)`$INSTANCE_NAME`_pageInfoPtr[idx] &
                                                        `$INSTANCE_NAME`_LO16_ADDR_MASK;
                if(0u == (`$INSTANCE_NAME`_PAGE_MEM_TYPE & pageMask))
                {
                    `$INSTANCE_NAME`_pageInfoList[idx] |= CYDEV_FLS_BASE;
                }
                `$INSTANCE_NAME`_pageAddrList[idx>>1u] = `$INSTANCE_NAME`_pageInfoList[idx];
                `$INSTANCE_NAME`_pageInfoList[idx] = CYSWAP_ENDIAN32(`$INSTANCE_NAME`_pageInfoList[idx]);

                `$INSTANCE_NAME`_pageInfoList[idx+1u] = (uint32)`$INSTANCE_NAME`_pageInfoPtr[idx+1u] &
                                                        `$INSTANCE_NAME`_LO16_ADDR_MASK;
                if(0u == (`$INSTANCE_NAME`_CFG_MEM_TYPE & pageMask))
                {
                    `$INSTANCE_NAME`_pageInfoList[idx+1u] |= CYDEV_FLS_BASE;
                }
                `$INSTANCE_NAME`_pageInfoList[idx+1u] = CYSWAP_ENDIAN32(`$INSTANCE_NAME`_pageInfoList[idx+1u]);
                pageMask = (uint8)(pageMask << 1u);
            }
        #endif /* CY_PSOC3 */

        /* 0x1FFF8000-0x1FFFFFFF needs to use alias at 0x20008000-0x2000FFFF */
        #if(CY_PSOC5)
            for(idx = 0u; idx < `$INSTANCE_NAME`_PAGE_INFO_SIZE; idx += 2u)
            {
                `$INSTANCE_NAME`_pageInfoList[idx] = (uint32)`$INSTANCE_NAME`_pageInfoPtr[idx];
                if(`$INSTANCE_NAME`_CPU_SRAM_BASE <= `$INSTANCE_NAME`_pageInfoList[idx])
                {
                    `$INSTANCE_NAME`_pageInfoList[idx] &= `$INSTANCE_NAME`_LO16_ADDR_MASK;
                    `$INSTANCE_NAME`_pageInfoList[idx] |= `$INSTANCE_NAME`_DMA_SRAM_BASE;
                }

                `$INSTANCE_NAME`_pageAddrList[idx>>1u] = `$INSTANCE_NAME`_pageInfoList[idx];

                `$INSTANCE_NAME`_pageInfoList[idx+1u] = (uint32)`$INSTANCE_NAME`_pageInfoPtr[idx+1u];
                if(`$INSTANCE_NAME`_CPU_SRAM_BASE <= `$INSTANCE_NAME`_pageInfoList[idx+1u])
                {
                    `$INSTANCE_NAME`_pageInfoList[idx+1u] &= `$INSTANCE_NAME`_LO16_ADDR_MASK;
                    `$INSTANCE_NAME`_pageInfoList[idx+1u] |= `$INSTANCE_NAME`_DMA_SRAM_BASE;
                }
            }
        #endif /* CY_PSOC5 */


        /***********************************************************************
        *       Register space start and end address DMAs
        ***********************************************************************/

        /* Transfer register space start and end addresses from SRAM to UDB,
        *  two byte transfer, each transfer requires a request.
        */
        `$INSTANCE_NAME`_pageStartAddrDMA_Chan = `$INSTANCE_NAME`_StartAddrDMA_DmaInitialize(
            `$INSTANCE_NAME`_PAGE_ADDR_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_PAGE_ADDR_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE),   HI16(CYDEV_PERIPH_BASE));

        `$INSTANCE_NAME`_pageEndAddrDMA_Chan   = `$INSTANCE_NAME`_EndAddrDMA_DmaInitialize(
            `$INSTANCE_NAME`_PAGE_ADDR_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_PAGE_ADDR_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE),   HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel numbers */
        `$INSTANCE_NAME`_dmaChannelList[0u] = `$INSTANCE_NAME`_pageStartAddrDMA_Chan;
        `$INSTANCE_NAME`_dmaChannelList[1u] = `$INSTANCE_NAME`_pageEndAddrDMA_Chan;

        `$INSTANCE_NAME`_pageStartAddr_TD[0u] = CyDmaTdAllocate();
        `$INSTANCE_NAME`_pageEndAddr_TD[0u]   = CyDmaTdAllocate();

        /* One TD looping on itself, increment the source address, but not the
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_pageStartAddr_TD[0u], `$INSTANCE_NAME`_PAGE_ADDR_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_pageStartAddr_TD[0u], `$INSTANCE_NAME`_PAGE_ADDR_DMA_CFG);
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_pageEndAddr_TD[0u],   `$INSTANCE_NAME`_PAGE_ADDR_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_pageEndAddr_TD[0u],   `$INSTANCE_NAME`_PAGE_ADDR_DMA_CFG);

        /* Move register space boundaries from the regPageStartAddr and
        *  regPageEndAddr arrays in SRAM to the address comparison block FIFO 0
        *  and FIFO 1 correspondingly.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_pageStartAddr_TD[0u], LO16((uint32)`$INSTANCE_NAME`_pageStartAddr),
                                                                        LO16((uint32)`$INSTANCE_NAME`_PAGE_START_PTR));
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_pageEndAddr_TD[0u],   LO16((uint32)`$INSTANCE_NAME`_pageEndAddr),
                                                                        LO16((uint32)`$INSTANCE_NAME`_PAGE_END_PTR));


        /***********************************************************************
        *                   Register page info DMA
        ***********************************************************************/

        /* Transfer a register page info from SRAM to the address calculation
        *  datapath, two byte transfer, all subsequent bursts after the first
        *  burst will be automatically requested and carried out.
        */
        `$INSTANCE_NAME`_pageInfoDMA_Chan = `$INSTANCE_NAME`_InfoDMA_DmaInitialize(
            `$INSTANCE_NAME`_PAGE_INFO_DMA_BYTES_PER_BURST,  `$INSTANCE_NAME`_PAGE_INFO_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        `$INSTANCE_NAME`_dmaChannelList[2u] = `$INSTANCE_NAME`_pageInfoDMA_Chan;

        `$INSTANCE_NAME`_pageInfoDMA_TD[0u] = CyDmaTdAllocate();
        /* One TD looping on itself, increment the source address, but not the
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_pageInfoDMA_TD[0u], `$INSTANCE_NAME`_PAGE_INFO_DMA_TD_SIZE,
            `$INSTANCE_NAME`_pageInfoDMA_TD[0u], TD_INC_SRC_ADR | `$INSTANCE_NAME`_InfoDMA__TD_TERMOUT_EN);

        /* Move a register page info from the SRAM to the address calculation
        *  datapath FIFO 0. The source address of this TD is set to 0, since it
        *  is configured later in run-time by the AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_pageInfoDMA_TD[0u], LO16((uint32)0u),
                                    LO16((uint32)`$INSTANCE_NAME`_PAGE_INFO_PTR));


        /***********************************************************************
        *                          Read DMA
        ***********************************************************************/

        /* Transfer the register data from SRAM/Flash to FIFO 0 of the MDIO
        *  frame processing block. The source address is set to 0u, since it
        *  is updated in run-time by the Address DMA.
        */
        `$INSTANCE_NAME`_rdDMA_Chan = `$INSTANCE_NAME`_RdDMA_DmaInitialize(
            `$INSTANCE_NAME`_REG_MEM_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_REG_MEM_DMA_REQUEST_PER_BURST,
            0u, HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        `$INSTANCE_NAME`_dmaChannelList[3u] = `$INSTANCE_NAME`_rdDMA_Chan;

        `$INSTANCE_NAME`_rdDMA_TD[0u] = CyDmaTdAllocate();

        /* One TD looping on itself, increment the source address, but not the
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_rdDMA_TD[0u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                    `$INSTANCE_NAME`_rdDMA_TD[0u], `$INSTANCE_NAME`_RdDMA__TD_TERMOUT_EN | TD_INC_SRC_ADR | TD_SWAP_EN);

        /* Move a register data from the SRAM or Flash to the FIFO 0 register
        *  of the frame processing block. The source address of this TD is set
        *  to 0, since it is configured later in run-time by the AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_rdDMA_TD[0u], LO16((uint32)0u),
                                                                LO16((uint32)`$INSTANCE_NAME`_FP_FIFO0_PTR));


        /***********************************************************************
        *                           Write DMA
        ***********************************************************************/

        /* Transfer a register data from the FIFO 1 of the MDIO frame processing
        *  block to the register memory in SRAM.
        */
        `$INSTANCE_NAME`_wrDMA_Chan = `$INSTANCE_NAME`_WrDMA_DmaInitialize(
            `$INSTANCE_NAME`_REG_MEM_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_REG_MEM_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));

        /* Update channel list with allocated channel number */
        `$INSTANCE_NAME`_dmaChannelList[4u] = `$INSTANCE_NAME`_wrDMA_Chan;

        `$INSTANCE_NAME`_wrDMA_TD[0u] = CyDmaTdAllocate();

        /* One TD looping on itself, increment the destination address, but not
        *  the source address.
        */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_wrDMA_TD[0u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                    `$INSTANCE_NAME`_wrDMA_TD[0u], `$INSTANCE_NAME`_WrDMA__TD_TERMOUT_EN | TD_INC_DST_ADR | TD_SWAP_EN);

        /* Move a register data from the FIFO 1 register of the frame processing
        *  block to the register memory in SRAM. The destination address of this
        *  TD is set to 0, since it is configured later in run-time by the
        *  AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_wrDMA_TD[0u], LO16((uint32)`$INSTANCE_NAME`_FP_FIFO1_PTR),
                                                                LO16((uint32)0u));


        /***********************************************************************
        *               Register configuration DMAs
        ***********************************************************************/

        /* CfgDMA1 transfers a register configuration data (mask and attributes)
        * from the configuration memory in Flash/SRAM to the fixed memory
        * location. Then the CfgDMA2 moves the configuration from this location
        * into the UDB array. The source address of CfgDMA1 is set to 0u, since
        * it is updated in run-time by the Address DMA.
        */
        `$INSTANCE_NAME`_cfgDMA1_Chan = `$INSTANCE_NAME`_CfgDMA1_DmaInitialize(
            `$INSTANCE_NAME`_CFG_DMA1_BYTES_PER_BURST, `$INSTANCE_NAME`_CFG_DMA1_REQUEST_PER_BURST,
            HI16(0u), HI16(CYDEV_SRAM_BASE));

        `$INSTANCE_NAME`_cfgDMA2_Chan = `$INSTANCE_NAME`_CfgDMA2_DmaInitialize(
            `$INSTANCE_NAME`_CFG_DMA2_BYTES_PER_BURST, `$INSTANCE_NAME`_CFG_DMA2_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        `$INSTANCE_NAME`_dmaChannelList[5u] = `$INSTANCE_NAME`_cfgDMA1_Chan;
        `$INSTANCE_NAME`_dmaChannelList[6u] = `$INSTANCE_NAME`_cfgDMA2_Chan;

        `$INSTANCE_NAME`_cfgDMA1_TD[0u] = CyDmaTdAllocate();
        `$INSTANCE_NAME`_cfgDMA2_TD[0u] = CyDmaTdAllocate();
        `$INSTANCE_NAME`_cfgDMA2_TD[1u] = CyDmaTdAllocate();

        /* TD looped on itself, increment the source and destination
        *  address address. Increment is required for PSoC3 if the data
        *  are not aligned.
        */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_cfgDMA1_TD[0u], `$INSTANCE_NAME`_CFG_DMA1_TD_SIZE,
            `$INSTANCE_NAME`_cfgDMA1_TD[0u], `$INSTANCE_NAME`_CFG_DMA1_CFG);

        /* Two TD chain. Last TD in the chain looped on the first one. */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_cfgDMA2_TD[0u], `$INSTANCE_NAME`_CFG_DMA2_TD1_SIZE,
                                `$INSTANCE_NAME`_cfgDMA2_TD[1u], TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT);
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_cfgDMA2_TD[1u], `$INSTANCE_NAME`_CFG_DMA2_TD2_SIZE,
                                `$INSTANCE_NAME`_cfgDMA2_TD[0u], `$INSTANCE_NAME`_CfgDMA2__TD_TERMOUT_EN);

        /* Move a register configuration from the Flash or SRAM into the fixed
        *  memory location in SRAM. The source address of this TD is set to 0,
        *  since it is configured later in run-time by the AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_cfgDMA1_TD[0u], LO16((uint32)0u),
                                                                  LO16((uint32)&`$INSTANCE_NAME`_regConfig));

        /* Move a register mask from memory to the D1 register of the MDIO frame
        *  processing datapath.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_cfgDMA2_TD[0u], LO16((uint32)&`$INSTANCE_NAME`_regConfig),
                                                                  LO16((uint32)`$INSTANCE_NAME`_REG_MASK_PTR));

        /* Move a register attributes from memory to the regCfg control register
        *  of the Address analyzer block.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_cfgDMA2_TD[1u],
                        LO16((uint32)&`$INSTANCE_NAME`_regConfig + `$INSTANCE_NAME`_CTRL_BITS_OFFSET),
                        LO16((uint32)`$INSTANCE_NAME`_REG_ATTR_PTR));


        /***********************************************************************
        *               Register physical memory address DMA
        ***********************************************************************/

        /* Transfer the data between UDB registers and DMAC config memory,
        *  two byte transfer, each transfer requires a request.
        */
        `$INSTANCE_NAME`_regAddrDMA_Chan  = `$INSTANCE_NAME`_AddrDMA_DmaInitialize(
            `$INSTANCE_NAME`_REG_MEM_DMA_BYTES_PER_BURST,  `$INSTANCE_NAME`_REG_MEM_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        `$INSTANCE_NAME`_dmaChannelList[7u] = `$INSTANCE_NAME`_regAddrDMA_Chan;

        for(idx = 0u; idx < `$INSTANCE_NAME`_REG_MEM_ADDR_DMA_TD_NUM; idx++)
        {
            `$INSTANCE_NAME`_regAddrDMA_TD[idx] = CyDmaTdAllocate();
        }

        /* Configure the TD chain */
        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[0u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[1u], TD_AUTO_EXEC_NEXT);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[1u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[2u], `$INSTANCE_NAME`_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[2u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[3u], TD_AUTO_EXEC_NEXT);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[3u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[4u], `$INSTANCE_NAME`_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[4u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[5u], `$INSTANCE_NAME`_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[5u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[6u], `$INSTANCE_NAME`_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_regAddrDMA_TD[6u], `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE,
                                       `$INSTANCE_NAME`_regAddrDMA_TD[0u], `$INSTANCE_NAME`_AddrDMA__TD_TERMOUT_EN);

        /* Transfer the address of a register space info (register space memory
        *  base address and register space config base address) from the address
        *  calculation datapath to the source address of the InfoDMA TD.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[0u], LO16((uint32)`$INSTANCE_NAME`_INFO_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[`$INSTANCE_NAME`_pageInfoDMA_TD[0u]].TD1[0u]));

        /* Move the register index from the A0 register of the address
        *  comparison datapath to the address calculation datapath.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[1u], LO16((uint32)`$INSTANCE_NAME`_REG_IDX_PTR),
                                                                     LO16((uint32)`$INSTANCE_NAME`_REG_OFFSET_PTR));

        /* Move the lower 16 bits of the register address from the A0 of the
        *  address calculation datapath to the source address of the RdDMA TD
        *  and destination address of the WrDMA TD.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[2u], LO16((uint32)`$INSTANCE_NAME`_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[`$INSTANCE_NAME`_rdDMA_TD[0u]].TD1[0u]));
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[3u], LO16((uint32)`$INSTANCE_NAME`_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[`$INSTANCE_NAME`_wrDMA_TD[0u]].TD1[2u]));

        /* Move the upper 16 bits of the register address from the A0 of the
        *  address calculation datapath to the upper 16-bit source address of
        *  the RdDMA TD.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[4u], LO16((uint32)`$INSTANCE_NAME`_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_CFGMEM_STRUCT_PTR[`$INSTANCE_NAME`_rdDMA_Chan].CFG1[0u]));

        /* Move the lower and the upper 16 bits of the register config address
        *  from the A0 of the address calculation datapath to the source address
        *  of the CfgDMA1 TD.
        */
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[5u], LO16((uint32)`$INSTANCE_NAME`_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[`$INSTANCE_NAME`_cfgDMA1_TD[0u]].TD1[0u]));
        (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_regAddrDMA_TD[6u], LO16((uint32)`$INSTANCE_NAME`_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_CFGMEM_STRUCT_PTR[`$INSTANCE_NAME`_cfgDMA1_Chan].CFG1[0u]));


        /***********************************************************************
        *               Firmware DMA (Used from APIs)
        ***********************************************************************/

        /* Partial configuration of FwDMA1 DMA. The rest configuration is done
        *  in the SetData, GetData and SetBits APIs.
        */
        `$INSTANCE_NAME`_fwDMA1_Chan = `$INSTANCE_NAME`_FwDMA1_DmaInitialize(
            `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_SRAM_BASE));

        `$INSTANCE_NAME`_fwDMA1_TD[0u] = CyDmaTdAllocate();
        #if(CY_PSOC3)
            `$INSTANCE_NAME`_fwDMA1_TD[1u] = CyDmaTdAllocate();
        #endif /* CY_PSOC3 */

        #if(CY_PSOC5)
            /* Configure FwDMA2 DMA. Two bytes transfer in a single burst */
            `$INSTANCE_NAME`_fwDMA2_Chan = `$INSTANCE_NAME`_FwDMA2_DmaInitialize(
                `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST,
                HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));

            `$INSTANCE_NAME`_fwDMA2_TD[0u] = CyDmaTdAllocate();
            /* Single two byte transfer */
            (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fwDMA2_TD[0u], 2u, DMA_INVALID_TD, TD_SWAP_EN);
        #endif /* CY_PSOC5 */
    }

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */


/* [] END OF FILE */
