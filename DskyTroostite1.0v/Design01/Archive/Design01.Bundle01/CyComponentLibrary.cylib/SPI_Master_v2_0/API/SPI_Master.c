/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all API functionality of the SPI Master component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"

#if(`$INSTANCE_NAME`_InternalClockUsed)

    #include "`$INSTANCE_NAME`_IntClock.h"
    
#endif /* `$INSTANCE_NAME`_InternalClockUsed */

#if (`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)

    volatile `$RegSizeReplacementString` `$INSTANCE_NAME`_TXBUFFER[`$INSTANCE_NAME`_TXBUFFERSIZE] = {0u};
    volatile uint8 `$INSTANCE_NAME`_txBufferRead = 0u;
    volatile uint8 `$INSTANCE_NAME`_txBufferWrite = 0u;    
    
#endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */

#if (`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)

    volatile `$RegSizeReplacementString` `$INSTANCE_NAME`_RXBUFFER[`$INSTANCE_NAME`_RXBUFFERSIZE] = {0u};
    volatile uint8 `$INSTANCE_NAME`_rxBufferRead = 0u;
    volatile uint8 `$INSTANCE_NAME`_rxBufferWrite = 0u;
    uint8 `$INSTANCE_NAME`_rxBufferFull = 0u;
    
#endif /* `$INSTANCE_NAME`_RXBUFFERSIZE > 4u */

uint8 `$INSTANCE_NAME`_initVar = 0u;

extern volatile uint8 `$INSTANCE_NAME`_swStatusTx;
extern volatile uint8 `$INSTANCE_NAME`_swStatusRx;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIM configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the 
*  interrupt service routine, configuring the bit-counter parameters and 
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{    
    /* Initialize the Bit counter */
    `$INSTANCE_NAME`_COUNTER_PERIOD_REG = `$INSTANCE_NAME`_BITCTR_INIT;
    
    /* ISR initialization  */  
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_TX_ISR_NUMBER);

        /* Set the ISR to point to the `$INSTANCE_NAME`_isr Interrupt. */
        CyIntSetVector(`$INSTANCE_NAME`_TX_ISR_NUMBER, `$INSTANCE_NAME`_TX_ISR);

        /* Set the priority. */
        CyIntSetPriority(`$INSTANCE_NAME`_TX_ISR_NUMBER, `$INSTANCE_NAME`_TX_ISR_PRIORITY);
        
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */                                
    
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_RX_ISR_NUMBER);

        /* Set the ISR to point to the `$INSTANCE_NAME`_isr Interrupt. */
        CyIntSetVector(`$INSTANCE_NAME`_RX_ISR_NUMBER, `$INSTANCE_NAME`_RX_ISR);

        /* Set the priority. */
        CyIntSetPriority(`$INSTANCE_NAME`_RX_ISR_NUMBER, `$INSTANCE_NAME`_RX_ISR_PRIORITY);
        
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */
    
    /* Clear any stray data from the RX and TX FIFO */    
	`$INSTANCE_NAME`_ClearFIFO();
	
	#if(`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)
    
        `$INSTANCE_NAME`_rxBufferRead = 0u;
        `$INSTANCE_NAME`_rxBufferWrite = 0u;

    #endif /* `$INSTANCE_NAME`_RXBUFFERSIZE > 4u */
	
    #if(`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)
    
        `$INSTANCE_NAME`_txBufferRead = 0u;
        `$INSTANCE_NAME`_txBufferWrite = 0u;

    #endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */
    
    (void) `$INSTANCE_NAME`_ReadTxStatus(); /* Clear any pending status bits */
    (void) `$INSTANCE_NAME`_ReadRxStatus(); /* Clear any pending status bits */
	
	/* Configure the Initial interrupt mask */
    #if (`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)
        `$INSTANCE_NAME`_TX_STATUS_MASK_REG  = `$INSTANCE_NAME`_TX_INIT_INTERRUPTS_MASK & 
                                                ~`$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL;                    
	#else /* `$INSTANCE_NAME`_TXBUFFERSIZE < 4u */    
        `$INSTANCE_NAME`_TX_STATUS_MASK_REG  = `$INSTANCE_NAME`_TX_INIT_INTERRUPTS_MASK;       
	#endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */
    
    `$INSTANCE_NAME`_RX_STATUS_MASK_REG  = `$INSTANCE_NAME`_RX_INIT_INTERRUPTS_MASK; 
}
  
    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enable SPIM component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{             
    uint8 enableInterrupts = 0u;    
    
    enableInterrupts = CyEnterCriticalSection();
    
    `$INSTANCE_NAME`_COUNTER_CONTROL_REG |= `$INSTANCE_NAME`_CNTR_ENABLE;
    `$INSTANCE_NAME`_TX_STATUS_ACTL_REG |= `$INSTANCE_NAME`_INT_ENABLE;
    `$INSTANCE_NAME`_RX_STATUS_ACTL_REG |= `$INSTANCE_NAME`_INT_ENABLE;
    
    CyExitCriticalSection(enableInterrupts);
    
    #if(`$INSTANCE_NAME`_InternalClockUsed)   
    
        `$INSTANCE_NAME`_IntClock_Enable();
        
    #endif /* `$INSTANCE_NAME`_InternalClockUsed */
    
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)
    
        CyIntEnable(`$INSTANCE_NAME`_TX_ISR_NUMBER);
        
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */
    
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)
    
        CyIntEnable(`$INSTANCE_NAME`_RX_ISR_NUMBER);
        
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
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
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Master component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the clock input to enable operation.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts = 0u;    
    
    enableInterrupts = CyEnterCriticalSection();
    
    `$INSTANCE_NAME`_TX_STATUS_ACTL_REG &= ~`$INSTANCE_NAME`_INT_ENABLE;
    `$INSTANCE_NAME`_RX_STATUS_ACTL_REG &= ~`$INSTANCE_NAME`_INT_ENABLE;
    
    CyExitCriticalSection(enableInterrupts);
    
    #if(`$INSTANCE_NAME`_InternalClockUsed)
    
        `$INSTANCE_NAME`_IntClock_Disable();
        
    #endif /* `$INSTANCE_NAME`_InternalClockUsed */
    
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_TX_ISR_NUMBER);
        
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */
    
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_RX_ISR_NUMBER);
        
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableTxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableTxInt")`
{       
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)
    
        CyIntEnable(`$INSTANCE_NAME`_TX_ISR_NUMBER);              
    
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */     
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableRxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableRxInt")`
{       
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)
            
        CyIntEnable(`$INSTANCE_NAME`_RX_ISR_NUMBER);           
    
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */     
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableTxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableTxInt")`
{
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_TX_ISR_NUMBER);        
        
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableRxInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableRxInt")`
{
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)
    
        CyIntDisable(`$INSTANCE_NAME`_RX_ISR_NUMBER);
        
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the 
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTxInterruptMode(uint8 intSrc) `=ReentrantKeil($INSTANCE_NAME . "_SetTxInterruptMode")`
{
    `$INSTANCE_NAME`_TX_STATUS_MASK_REG  = intSrc;    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the 
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRxInterruptMode(uint8 intSrc) `=ReentrantKeil($INSTANCE_NAME . "_SetRxInterruptMode")`
{
    `$INSTANCE_NAME`_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  `$INSTANCE_NAME`_swStatusTx - used to store in software status register, 
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadTxStatus(void)
{
    uint8 tmpStatus = 0u;
        
    #if (`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)
    
        `$INSTANCE_NAME`_DisableTxInt();
        
        tmpStatus = `$INSTANCE_NAME`_GET_STATUS_TX(`$INSTANCE_NAME`_swStatusTx);                    
        
        `$INSTANCE_NAME`_swStatusTx = 0u;        
        
        /* Enable Interrupts */
        `$INSTANCE_NAME`_EnableTxInt();
        
    #else /* (`$INSTANCE_NAME`_TXBUFFERSIZE < 4u) */
    
        tmpStatus = `$INSTANCE_NAME`_TX_STATUS_REG;
        
    #endif /* (`$INSTANCE_NAME`_TXBUFFERSIZE > 4u) */
    
    return(tmpStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  `$INSTANCE_NAME`_swStatusRx - used to store in software Rx status register, 
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error 
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadRxStatus(void)
{
    uint8 tmpStatus = 0u;
        
    #if (`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)
    
        `$INSTANCE_NAME`_DisableRxInt();
        
        tmpStatus = `$INSTANCE_NAME`_GET_STATUS_RX(`$INSTANCE_NAME`_swStatusRx);
               
        `$INSTANCE_NAME`_swStatusRx = 0u;
        
        /* Enable Interrupts */
        `$INSTANCE_NAME`_EnableRxInt();
        
    #else /* (`$INSTANCE_NAME`_RXBUFFERSIZE < 4u) */
    
        tmpStatus = `$INSTANCE_NAME`_RX_STATUS_REG;
        
    #endif /* (`$INSTANCE_NAME`_RXBUFFERSIZE > 4u) */
    
    return(tmpStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  `$INSTANCE_NAME`_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  `$INSTANCE_NAME`_TXBUFFER[`$INSTANCE_NAME`_TXBUFFERSIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteTxData(`$RegSizeReplacementString` txData)
{    
    #if(`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)

        int16 tmpTxBufferRead = 0;
                
        /* Block if buffer is full, so we don't overwrite. */
        do
        {
            tmpTxBufferRead = `$INSTANCE_NAME`_txBufferRead - 1;
            if (tmpTxBufferRead < 0)
            {
                tmpTxBufferRead = `$INSTANCE_NAME`_TXBUFFERSIZE - 1u;        
            }    
        } while(tmpTxBufferRead == `$INSTANCE_NAME`_txBufferWrite);               
                   
        /* Disable Interrupt to protect variables that could change on interrupt. */
        `$INSTANCE_NAME`_DisableTxInt();
        
        `$INSTANCE_NAME`_swStatusTx = `$INSTANCE_NAME`_GET_STATUS_TX(`$INSTANCE_NAME`_swStatusTx);
        
        if((`$INSTANCE_NAME`_txBufferRead == `$INSTANCE_NAME`_txBufferWrite) &&
            ((`$INSTANCE_NAME`_swStatusTx & `$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL) != 0u))
        {
            /* Add directly to the FIFO. */
            `$CySetRegReplacementString`(`$INSTANCE_NAME`_TXDATA_PTR, txData);
        }
        else
        {
            /* Add to the software buffer. */
            `$INSTANCE_NAME`_txBufferWrite++;
            if(`$INSTANCE_NAME`_txBufferWrite >= `$INSTANCE_NAME`_TXBUFFERSIZE)
            {
                `$INSTANCE_NAME`_txBufferWrite = 0u;
            }    
    
            `$INSTANCE_NAME`_TXBUFFER[`$INSTANCE_NAME`_txBufferWrite] = txData;
            
            `$INSTANCE_NAME`_TX_STATUS_MASK_REG |= `$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL;            
        }                         
        
        /* Enable Interrupt. */
        `$INSTANCE_NAME`_EnableTxInt();                        

    #else /* `$INSTANCE_NAME`_TXBUFFERSIZE <= 4u */

        /* Block while FIFO is full */
        while((`$INSTANCE_NAME`_TX_STATUS_REG & `$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL) == 0u);
        
        /* Then write the byte */
        `$CySetRegReplacementString`(`$INSTANCE_NAME`_TXDATA_PTR, txData);

    #endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  `$INSTANCE_NAME`_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  `$INSTANCE_NAME`_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  `$INSTANCE_NAME`_RXBUFFER[`$INSTANCE_NAME`_RXBUFFERSIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty. The user should Call 
*  GetRxBufferSize() and if it returns a non-zero value then it is safe to call 
*  ReadByte() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
`$RegSizeReplacementString` `$INSTANCE_NAME`_ReadRxData(void)
{
    `$RegSizeReplacementString` rxData = 0u;

    #if(`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)
    
        /* Disable Interrupt to protect variables that could change on interrupt. */
        `$INSTANCE_NAME`_DisableRxInt();
        
        if(`$INSTANCE_NAME`_rxBufferRead != `$INSTANCE_NAME`_rxBufferWrite)
        {      
            if(`$INSTANCE_NAME`_rxBufferFull == 0u)
            {
                `$INSTANCE_NAME`_rxBufferRead++;
                if(`$INSTANCE_NAME`_rxBufferRead >= `$INSTANCE_NAME`_RXBUFFERSIZE)
                {
                    `$INSTANCE_NAME`_rxBufferRead = 0u;
                }
            }
            else
            {
                `$INSTANCE_NAME`_rxBufferFull = 0u;
            }
        }    
        
        rxData = `$INSTANCE_NAME`_RXBUFFER[`$INSTANCE_NAME`_rxBufferRead];
                           
        /* Enable Interrupt. */
        `$INSTANCE_NAME`_EnableRxInt();
    
    #else /* `$INSTANCE_NAME`_RXBUFFERSIZE <= 4u */
    
        rxData = `$CyGetRegReplacementString`(`$INSTANCE_NAME`_RXDATA_PTR);
    
    #endif /* `$INSTANCE_NAME`_RXBUFFERSIZE > 4u */

	return (rxData);
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if 
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  `$INSTANCE_NAME`_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  `$INSTANCE_NAME`_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetRxBufferSize(void) `=ReentrantKeil($INSTANCE_NAME . "_GetRxBufferSize")`
{
    uint8 size = 0u;

    #if(`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)
    
        /* Disable Interrupt to protect variables that could change on interrupt. */
        `$INSTANCE_NAME`_DisableRxInt();
    
        if(`$INSTANCE_NAME`_rxBufferRead == `$INSTANCE_NAME`_rxBufferWrite)
        {
            size = 0u; /* No data in RX buffer */
        }
        else if(`$INSTANCE_NAME`_rxBufferRead < `$INSTANCE_NAME`_rxBufferWrite)
        {
            size = (`$INSTANCE_NAME`_rxBufferWrite - `$INSTANCE_NAME`_rxBufferRead);
        }
        else
        {
            size = (`$INSTANCE_NAME`_RXBUFFERSIZE - `$INSTANCE_NAME`_rxBufferRead) + `$INSTANCE_NAME`_rxBufferWrite;
        }
    
        /* Enable interrupt. */
        `$INSTANCE_NAME`_EnableRxInt();
    
    #else /* `$INSTANCE_NAME`_RXBUFFERSIZE <= 4u */
    
        /* We can only know if there is data in the fifo. */
        size = (`$INSTANCE_NAME`_RX_STATUS_REG & `$INSTANCE_NAME`_STS_RX_FIFO_NOT_EMPTY) ? 1u : 0u;
    
    #endif /* `$INSTANCE_NAME`_RXBUFFERSIZE < 4u */

    return (size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if 
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  `$INSTANCE_NAME`_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  `$INSTANCE_NAME`_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  `$INSTANCE_NAME`_GetTxBufferSize(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTxBufferSize")`
{
    uint8 size = 0u;

    #if(`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)
    
        /* Disable Interrupt to protect variables that could change on interrupt. */
        `$INSTANCE_NAME`_DisableTxInt();
    
        if(`$INSTANCE_NAME`_txBufferRead == `$INSTANCE_NAME`_txBufferWrite)
        {
            size = 0u;
        }
        else if(`$INSTANCE_NAME`_txBufferRead < `$INSTANCE_NAME`_txBufferWrite)
        {
            size = (`$INSTANCE_NAME`_txBufferWrite - `$INSTANCE_NAME`_txBufferRead);
        }
        else
        {
            size = (`$INSTANCE_NAME`_TXBUFFERSIZE - `$INSTANCE_NAME`_txBufferRead) + `$INSTANCE_NAME`_txBufferWrite;
        }
    
        /* Enable Interrupt. */
        `$INSTANCE_NAME`_EnableTxInt();
    
    #else /* `$INSTANCE_NAME`_TXBUFFERSIZE <= 4u */
    
        size = `$INSTANCE_NAME`_TX_STATUS_REG;
    
        /* Is the fifo is full. */
        if(size & `$INSTANCE_NAME`_STS_TX_FIFO_EMPTY)
        {
            size = 0u;
        }
        else if(size & `$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL)
        {
            size = 1u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 4u;
        }
    
    #endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */

    return (size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function 
*  call - resets to zero.
*  `$INSTANCE_NAME`_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to 
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearRxBuffer(void)
{
	/* Clear Hardware RX FIFO */
    while((!(`$INSTANCE_NAME`_RX_STATUS_REG & `$INSTANCE_NAME`_STS_RX_FIFO_NOT_EMPTY)) == 0u)
    {
        `$CyGetRegReplacementString`(`$INSTANCE_NAME`_RXDATA_PTR);
    }
	
    #if(`$INSTANCE_NAME`_RXBUFFERSIZE > 4u)
    
        /* Disable interrupt to protect variables that could change on interrupt. */        
        `$INSTANCE_NAME`_DisableRxInt();
    
        `$INSTANCE_NAME`_rxBufferRead = 0u;
        `$INSTANCE_NAME`_rxBufferWrite = 0u;
    
        /* Enable Rx interrupt. */
        `$INSTANCE_NAME`_EnableRxInt();
        
    #endif /* `$INSTANCE_NAME`_RXBUFFERSIZE > 4u */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  `$INSTANCE_NAME`_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to 
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when 
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearTxBuffer(void)
{
    uint8 enableInterrupts = 0u;
    
    /* Clear Hardware TX FIFO */       
    enableInterrupts = CyEnterCriticalSection();
    
    #if(`$INSTANCE_NAME`_DataWidth <= 8u)
    
        /* Clear TX FIFO */
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
    
    #else
    
        /* Clear TX FIFO */
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP1_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP1_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
        
    #endif /* `$INSTANCE_NAME`_DataWidth > 8u */
    
    CyExitCriticalSection(enableInterrupts);
	
    #if(`$INSTANCE_NAME`_TXBUFFERSIZE > 4u)
    
        /* Disable Interrupt to protect variables that could change on interrupt. */
        `$INSTANCE_NAME`_DisableTxInt();
    
        `$INSTANCE_NAME`_txBufferRead = 0u;
        `$INSTANCE_NAME`_txBufferWrite = 0u;
    
        /* If Buffer is empty then disable TX FIFO status interrupt */
        `$INSTANCE_NAME`_TX_STATUS_MASK_REG &= ~`$INSTANCE_NAME`_STS_TX_FIFO_NOT_FULL;

        /* Enable Interrupt. */
        `$INSTANCE_NAME`_EnableTxInt();
    
    #endif /* `$INSTANCE_NAME`_TXBUFFERSIZE > 4u */
}


#if (`$INSTANCE_NAME`_BidirectionalMode == 1u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_TxEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_TxEnable")`
    {
        `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_TX_SIGNAL_EN;
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI master is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_TxDisable(void) `=ReentrantKeil($INSTANCE_NAME . "_TxDisable")`
    {
        `$INSTANCE_NAME`_CONTROL_REG &= ~`$INSTANCE_NAME`_CTRL_TX_SIGNAL_EN;
    }
    
#endif /* `$INSTANCE_NAME`_BidirectionalMode == 1u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutArray
********************************************************************************                       
*
* Summary:
*  Write available data from ROM/RAM to the TX buffer while space is available 
*  in the TX buffer. Keep trying until all data is passed to the TX buffer.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutArray(`$RegSizeReplacementString` *buffer, uint8 byteCount)
{
    while(byteCount > 0u)
    {
        `$INSTANCE_NAME`_WriteTxData(*buffer++);
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`
{
    uint8 enableInterrupts = 0u;
    
    while((!(`$INSTANCE_NAME`_RX_STATUS_REG & `$INSTANCE_NAME`_STS_RX_FIFO_NOT_EMPTY)) == 0u)
    {
        `$CyGetRegReplacementString`(`$INSTANCE_NAME`_RXDATA_PTR);
    }
    
    enableInterrupts = CyEnterCriticalSection();
    
    #if(`$INSTANCE_NAME`_DataWidth <= 8u)
    
        /* Clear TX FIFO */
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
    
    #else
    
        /* Clear TX FIFO */
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP0_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP1_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_AUX_CONTROL_DP1_REG &= ~`$INSTANCE_NAME`_FIFO_CLR;
        
    #endif /* `$INSTANCE_NAME`_DataWidth > 8u */
    
    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`
{       
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)    
        CyIntEnable(`$INSTANCE_NAME`_TX_ISR_NUMBER);
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */                                
    
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)           
        CyIntEnable(`$INSTANCE_NAME`_RX_ISR_NUMBER);
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */     
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`
{
    #if(`$INSTANCE_NAME`_InternalTxInterruptEnabled)    
        CyIntDisable(`$INSTANCE_NAME`_TX_ISR_NUMBER);
    #endif /* `$INSTANCE_NAME`_InternalTxInterruptEnabled */
    
    #if(`$INSTANCE_NAME`_InternalRxInterruptEnabled)           
        CyIntDisable(`$INSTANCE_NAME`_RX_ISR_NUMBER);
    #endif /* `$INSTANCE_NAME`_InternalRxInterruptEnabled */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the 
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint8 intSrc) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`
{
    `$INSTANCE_NAME`_TX_STATUS_MASK_REG  = intSrc & ~(1u << `$INSTANCE_NAME`_STS_SPI_IDLE_SHIFT);
    `$INSTANCE_NAME`_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  `$INSTANCE_NAME`_swStatus - used to store in software status register, 
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadStatus(void)
{
    uint8 tmpStatus;
        
    #if ((`$INSTANCE_NAME`_TXBUFFERSIZE > 4u) || (`$INSTANCE_NAME`_RXBUFFERSIZE > 4u))
    
        `$INSTANCE_NAME`_DisableInt();
        
        tmpStatus = (`$INSTANCE_NAME`_GET_STATUS_TX(`$INSTANCE_NAME`_swStatusTx) & 
                      ~(1u << `$INSTANCE_NAME`_STS_SPI_IDLE_SHIFT)) | 
                      `$INSTANCE_NAME`_GET_STATUS_RX(`$INSTANCE_NAME`_swStatusRx);
        
        `$INSTANCE_NAME`_swStatusTx = 0u;
        `$INSTANCE_NAME`_swStatusRx = 0u;
        
        /* Enable Interrupts */
        `$INSTANCE_NAME`_EnableInt();
        
    #else /* (`$INSTANCE_NAME`_TXBUFFERSIZE < 4u) && (`$INSTANCE_NAME`_RXBUFFERSIZE < 4u) */
    
        tmpStatus = (`$INSTANCE_NAME`_TX_STATUS_REG & ~(1u << `$INSTANCE_NAME`_STS_SPI_IDLE_SHIFT)) |
                     `$INSTANCE_NAME`_RX_STATUS_REG;
        
    #endif /* (`$INSTANCE_NAME`_TXBUFFERSIZE > 4u) || (`$INSTANCE_NAME`_RXBUFFERSIZE > 4u) */
    
    return(tmpStatus);
}


/* [] END OF FILE */
