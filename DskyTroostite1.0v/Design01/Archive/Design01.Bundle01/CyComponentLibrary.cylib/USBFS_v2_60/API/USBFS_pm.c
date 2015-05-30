/*******************************************************************************
* File Name: `$INSTANCE_NAME`_pm.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "project.h"
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_pvt.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;


#if(`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(`$INSTANCE_NAME`_DP_INTSTAT_PTR);
    }

#endif /* (`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
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
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
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
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    if(`$INSTANCE_NAME`_configuration != 0u)
    {
        `$INSTANCE_NAME`_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power donwn mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Suspend(void) `=ReentrantKeil($INSTANCE_NAME . "_Suspend")`
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if((CY_GET_REG8(`$INSTANCE_NAME`_CR0_PTR) & `$INSTANCE_NAME`_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        `$INSTANCE_NAME`_backup.enableState = 1u;

        #if(`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL)
            `$INSTANCE_NAME`_Stop_DMA(`$INSTANCE_NAME`_MAX_EP);     /* Stop all DMAs */
        #endif   /* End `$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL */

        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        `$INSTANCE_NAME`_USBIO_CR0_REG &= (uint8)~`$INSTANCE_NAME`_USBIO_CR0_TEN;
        CyDelayUs(0u);  /*~50ns delay */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        `$INSTANCE_NAME`_PM_USB_CR0_REG &=
                                (uint8)~(`$INSTANCE_NAME`_PM_USB_CR0_PD_N | `$INSTANCE_NAME`_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE */
        `$INSTANCE_NAME`_CR0_REG &= (uint8)~`$INSTANCE_NAME`_CR0_ENABLE;

        CyDelayUs(0u);  /*~50ns delay */
        /* Store mode and Disable VRegulator*/
        `$INSTANCE_NAME`_backup.mode = `$INSTANCE_NAME`_CR1_REG & `$INSTANCE_NAME`_CR1_REG_ENABLE;
        `$INSTANCE_NAME`_CR1_REG &= (uint8)~`$INSTANCE_NAME`_CR1_REG_ENABLE;

        CyDelayUs(1u);  /* 0.5 us min delay */
        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        `$INSTANCE_NAME`_PM_USB_CR0_REG &= (uint8)~`$INSTANCE_NAME`_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
        `$INSTANCE_NAME`_USBIO_CR1_REG |= `$INSTANCE_NAME`_USBIO_CR1_IOMODE;

        /* Disable USB in ACT PM */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG &= (uint8)~`$INSTANCE_NAME`_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8)~`$INSTANCE_NAME`_PM_STBY_EN_FSUSB;
        CyDelayUs(1u); /* min  0.5us delay required */

    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if(`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u)
        (void) CyIntSetVector(`$INSTANCE_NAME`_DP_INTC_VECT_NUM,   &`$INSTANCE_NAME`_DP_ISR);
        CyIntSetPriority(`$INSTANCE_NAME`_DP_INTC_VECT_NUM, `$INSTANCE_NAME`_DP_INTC_PRIOR);
        CyIntClearPending(`$INSTANCE_NAME`_DP_INTC_VECT_NUM);
        CyIntEnable(`$INSTANCE_NAME`_DP_INTC_VECT_NUM);
    #endif /* (`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u) */

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Resume(void) `=ReentrantKeil($INSTANCE_NAME . "_Resume")`
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if(`$INSTANCE_NAME`_backup.enableState != 0u)
    {
        #if(`$INSTANCE_NAME`_DP_ISR_REMOVE == 0u)
            CyIntDisable(`$INSTANCE_NAME`_DP_INTC_VECT_NUM);
        #endif /* End `$INSTANCE_NAME`_DP_ISR_REMOVE */

        /* Enable USB block */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        `$INSTANCE_NAME`_USB_CLK_EN_REG |= `$INSTANCE_NAME`_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_REF_EN;
        /* The reference will be available ~40us after power restored */
        CyDelayUs(40u);
        /* Return VRegulator*/
        `$INSTANCE_NAME`_CR1_REG |= `$INSTANCE_NAME`_backup.mode;
        CyDelayUs(0u);  /*~50ns delay */
        /* Enable USBIO */
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_PD_N;
        CyDelayUs(2u);
        /* Set the USBIO pull-up enable */
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_PD_PULLUP_N;

        /* Reinit Arbiter configuration for DMA transfers */
        #if(`$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL)
            /* usb arb interrupt enable */
            `$INSTANCE_NAME`_ARB_INT_EN_REG = `$INSTANCE_NAME`_ARB_INT_MASK;
            #if(`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAMANUAL)
                `$INSTANCE_NAME`_ARB_CFG_REG = `$INSTANCE_NAME`_ARB_CFG_MANUAL_DMA;
            #endif   /* End `$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAMANUAL */
            #if(`$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                `$INSTANCE_NAME`_ARB_CFG_REG = `$INSTANCE_NAME`_ARB_CFG_AUTO_DMA | `$INSTANCE_NAME`_ARB_CFG_AUTO_MEM;
            #endif   /* End `$INSTANCE_NAME`_EP_MM == `$INSTANCE_NAME`__EP_DMAAUTO */
        #endif   /* End `$INSTANCE_NAME`_EP_MM != `$INSTANCE_NAME`__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(`$INSTANCE_NAME`_EP0_CR_PTR, `$INSTANCE_NAME`_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        `$INSTANCE_NAME`_CR0_REG |= `$INSTANCE_NAME`_CR0_ENABLE;
        CyDelayCycles(1u);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(`$INSTANCE_NAME`_USBIO_CR1_PTR, `$INSTANCE_NAME`_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        `$INSTANCE_NAME`_RestoreConfig();

    }
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
