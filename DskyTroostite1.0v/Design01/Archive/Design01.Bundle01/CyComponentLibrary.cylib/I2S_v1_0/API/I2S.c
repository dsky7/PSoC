/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the I2S
*  component.  
*
* Note: 
*
*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include <CyLib.h>
#include "`$INSTANCE_NAME`.h"  


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts the I2S interface.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_RST; 
    `$INSTANCE_NAME`_CONTROL &= ~`$INSTANCE_NAME`_RST;
    `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_CNTR_EN;
    `$INSTANCE_NAME`_AUX_CONTROL |= `$INSTANCE_NAME`_CNTR7_EN;
    `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_CNTR_LD;
    `$INSTANCE_NAME`_CONTROL &= ~`$INSTANCE_NAME`_CNTR_LD;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the I2S interface.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_CONTROL &= ~`$INSTANCE_NAME`_CNTR_EN;
    `$INSTANCE_NAME`_AUX_CONTROL &= ~`$INSTANCE_NAME`_CNTR7_EN;

#if ((`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__TX) || (`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX_AND_TX))
	`$INSTANCE_NAME`_DisableTx();
#endif /* `$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__TX*/

#if ((`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX) || (`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX_AND_TX))
	`$INSTANCE_NAME`_DisableRx();	
#endif /* `$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX */
}

#if ((`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__TX) || (`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX_AND_TX))

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableTx
********************************************************************************
*
* Summary:
*  Enables the Tx direction of the I2S interface.  At the next word
*  select falling edge transmission will begin.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableTx(void)
{
    `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_TX_EN;
    `$INSTANCE_NAME`_TX_STATUS_AUX_CONTROL |= `$INSTANCE_NAME`_TX_INT_EN;
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableTx
********************************************************************************
*
* Summary:
*  Disables the Tx direction of the I2S interface.  At the next word 
*  select falling edge transmission of data will stop and a constant 0 value will 
*  be transmitted.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableTx(void)
{
    `$INSTANCE_NAME`_CONTROL &= ~`$INSTANCE_NAME`_TX_EN;
    `$INSTANCE_NAME`_TX_STATUS_AUX_CONTROL &= ~`$INSTANCE_NAME`_TX_INT_EN;
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt source for the I2S Tx direction interrupt.
*
* Parameters:
*  Byte containing the constant for the selected interrupt sources.
*   `$INSTANCE_NAME`_TX_FIFO_UNDEFLOW         
*   `$INSTANCE_NAME`_TX_FIFO_0_NOT_FULL        
*   `$INSTANCE_NAME`_TX_FIFO_1_NOT_FULL       
*
* Return:
*  void
*
*******************************************************************************/	
void `$INSTANCE_NAME`_SetTxInterruptMode(uint8 interruptSource)
{
    `$INSTANCE_NAME`_TX_STATUS_MASK |= (interruptSource & `$INSTANCE_NAME`_TX_ST_MASK); 
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadTxStatus
********************************************************************************
*
* Summary:
*  Returns state in the I2S Tx status register.
*
* Parameters:
*  void
*
* Return:
*  State of the I2S Tx status register
*   `$INSTANCE_NAME`_RET_TX_FIFO_UNDEFLOW     
*   `$INSTANCE_NAME`_RET_TX_FIFO_0_NOT_FULL    
*   `$INSTANCE_NAME`_RET_TX_FIFO_1_NOT_FULL   
*
* Side Effects: 
*  Clears the I2S Tx status register
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadTxStatus(void)
{
    return (`$INSTANCE_NAME`_TX_STATUS & `$INSTANCE_NAME`_TX_ST_MASK);
}	
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteByte
********************************************************************************
*
* Summary:
*  Writes a single byte into the Tx FIFO.
*
* Parameters:
*  Data: Byte containing the data to transmit.
*  wordSelect: Indicates to write to the Left (0) or Right (1) channel.  In the 
*  interleaved mode this parameter is ignored
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteByte(uint8 wrData, uint8 wordSelect)
{
    wordSelect &= `$INSTANCE_NAME`_WORD_SEL_MASK;
    
#if(`$INSTANCE_NAME`_TX_DATA_INTERLEAVING == `$INSTANCE_NAME`__INTERLEAVED)
    CY_SET_REG8(`$INSTANCE_NAME`_TX_FIFO_0_PTR, wrData);
#else
    if(wordSelect == `$INSTANCE_NAME`_TX_LEFT_CHANNEL)
        CY_SET_REG8(`$INSTANCE_NAME`_TX_FIFO_0_PTR, wrData); 
    else
        CY_SET_REG8(`$INSTANCE_NAME`_TX_FIFO_1_PTR, wrData);    
#endif /* `$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__INTERLEAVED */
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFIFO
********************************************************************************
*
* Summary:
*  Clears out the Tx FIFO.  Any data present in the FIFO will not be
*  sent. This call should be made only when the Tx direction is disabled.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearTxFIFO(void)
{
    `$INSTANCE_NAME`_TX_AUX_CONTROL |=  `$INSTANCE_NAME`_TX_FIFO_0_CLR;
    `$INSTANCE_NAME`_TX_AUX_CONTROL &= ~`$INSTANCE_NAME`_TX_FIFO_0_CLR;
    
#if(`$INSTANCE_NAME`_TX_DATA_INTERLEAVING == `$INSTANCE_NAME`__SEPARATE)
    `$INSTANCE_NAME`_TX_AUX_CONTROL |=  `$INSTANCE_NAME`_TX_FIFO_1_CLR;
    `$INSTANCE_NAME`_TX_AUX_CONTROL &= ~`$INSTANCE_NAME`_TX_FIFO_1_CLR;    
#endif /* `$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__SEPARATE */   
}

#endif /* `$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__TX */ 


#if ((`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX) || (`$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX_AND_TX)) 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableRx
********************************************************************************
*
* Summary:
*  Enables the Rx direction of the I2S interface.  At the next word
*  select falling edge reception of data will begin.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/	
void `$INSTANCE_NAME`_EnableRx(void)
{
    `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_RX_EN;
    `$INSTANCE_NAME`_RX_STATUS_AUX_CONTROL |= `$INSTANCE_NAME`_RX_INT_EN;
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableRxRx
********************************************************************************
*
* Summary:
*  Disables the Rx direction of the I2S interface.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/	
void `$INSTANCE_NAME`_DisableRx(void)
{
    `$INSTANCE_NAME`_CONTROL &= ~`$INSTANCE_NAME`_RX_EN;
    `$INSTANCE_NAME`_RX_STATUS_AUX_CONTROL &= ~`$INSTANCE_NAME`_RX_INT_EN;
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt source for the I2S Rx direction interrupt.
*
* Parameters:
*  Byte containing the constant for the selected interrupt sources.
*   `$INSTANCE_NAME`_RX_FIFO_OVERFLOW          
*   `$INSTANCE_NAME`_RX_FIFO_0_NOT_EMPTY       
*   `$INSTANCE_NAME`_RX_FIFO_1_NOT_EMPTY       
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRxInterruptMode(uint8 interruptSource)
{
    `$INSTANCE_NAME`_RX_STATUS_MASK |= (interruptSource & `$INSTANCE_NAME`_RX_ST_MASK); 
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadRxStatus
********************************************************************************
*
* Summary:
*  Returns state in the I2S Rx status register.
*
* Parameters:
*  void
*
* Return:
*  State of the I2S Rx status register
*   `$INSTANCE_NAME`_RET_RX_FIFO_OVERFLOW      
*   `$INSTANCE_NAME`_RET_RX_FIFO_0_NOT_EMPTY   
*   `$INSTANCE_NAME`_RET_RX_FIFO_1_NOT_EMPTY   
*
* Side Effects: 
*  Clears the I2S Rx status register
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadRxStatus(void)
{
    return (`$INSTANCE_NAME`_RX_STATUS & `$INSTANCE_NAME`_RX_ST_MASK);
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadByte
********************************************************************************
*
* Summary:
*  Returns a single byte from the Rx FIFO.
*
* Parameters:
*  wordSelect: Indicates to read from the Left (0) or Right (1) channel. In the 
*  interleaved mode this parameter is ignored.
*
* Return:
*  Byte containing the data received.
*
*******************************************************************************/	
uint8 `$INSTANCE_NAME`_ReadByte(uint8 wordSelect)
{
	uint8 result;
    
    wordSelect &= `$INSTANCE_NAME`_WORD_SEL_MASK;
    
#if(`$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__INTERLEAVED)
    result = CY_GET_REG8(`$INSTANCE_NAME`_RX_FIFO_0_PTR);
#else
    if(wordSelect == `$INSTANCE_NAME`_RX_LEFT_CHANNEL)
        result = CY_GET_REG8(`$INSTANCE_NAME`_RX_FIFO_0_PTR); 
    else
        result = CY_GET_REG8(`$INSTANCE_NAME`_RX_FIFO_1_PTR);    
#endif /* `$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__INTERLEAVED */

    return (result);
}
	
	
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFIFO
********************************************************************************
*
* Summary:
*  Clears out the Rx FIFO.  Any data present in the FIFO will be lost.
*  This call should be made only when the Rx direction is disabled.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearRxFIFO(void)
{
    `$INSTANCE_NAME`_RX_AUX_CONTROL |=  `$INSTANCE_NAME`_RX_FIFO_0_CLR;
    `$INSTANCE_NAME`_RX_AUX_CONTROL &= ~`$INSTANCE_NAME`_RX_FIFO_0_CLR;
    
#if(`$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__SEPARATE)
    `$INSTANCE_NAME`_RX_AUX_CONTROL |=  `$INSTANCE_NAME`_RX_FIFO_1_CLR;
    `$INSTANCE_NAME`_RX_AUX_CONTROL &= ~`$INSTANCE_NAME`_RX_FIFO_1_CLR;    
#endif /* `$INSTANCE_NAME`_RX_DATA_INTERLEAVING == `$INSTANCE_NAME`__SEPARATE */   
}

#endif	/* `$INSTANCE_NAME`_DIRECTION == `$INSTANCE_NAME`__RX */


/* [] END OF FILE */
