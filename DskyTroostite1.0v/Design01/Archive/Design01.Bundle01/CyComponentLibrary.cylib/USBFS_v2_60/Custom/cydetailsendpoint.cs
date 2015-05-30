/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Windows.Forms;
using System.Collections.Generic;

namespace USBFS_v2_60
{
    public partial class CyDetailsEndpoint : UserControl
    {
        private CyEndpointDescriptor m_descriptor;
        private CyUSBFSParameters m_parameters;

        private const int TRANSFERTYPE_CONTROL_ITEM = 0;
        private const int TRANSFERTYPE_ISOCHRONOUS_ITEM = 3;
        private const int TRANSFERTYPE_BULK_ITEM = 2;
        private const int TRANSFERTYPE_INTERRUPT_ITEM = 1;

        private const int SYNCHTYPE_NOSYNCH_ITEM = 0;
        private const int SYNCHTYPE_ASYNCH_ITEM = 1;
        private const int SYNCHTYPE_ADAPTIVE_ITEM = 2;
        private const int SYNCHTYPE_SYNCH_ITEM = 3;

        private const int USAGETYPE_DATAEP_ITEM = 0;
        private const int USAGETYPE_FEEDBACKEP_ITEM = 1;
        private const int USAGETYPE_IMPLICITEEP_ITEM = 2;

        private bool m_internalChanges = false;
        private bool m_enabled;

        public CyDetailsEndpoint(CyEndpointDescriptor descriptor, CyUSBFSParameters parameters, bool enabled)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            m_enabled = enabled;
            InitFields();
        }

        private void InitFields()
        {
            m_internalChanges = true;
            comboBoxEndpointNum.Items.Clear();
            for (int i = 0; i < CyEndpointDescriptor.MAX_EP_NUM; i++)
            {
                comboBoxEndpointNum.Items.Add("EP" + (i + 1));
            }

            byte endpointNum = (byte)(m_descriptor.EndpointNum);
            byte direction = (byte) (m_descriptor.Direction);
            comboBoxEndpointNum.SelectedIndex = endpointNum - 1;
            if (endpointNum - 1 < 0)
                comboBoxEndpointNum.SelectedIndex = 0;
            comboBoxDirection.SelectedIndex = 1 - direction;

            switch (m_descriptor.TransferType)
            {
                case CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_CONTROL:
                    comboBoxTransferType.SelectedIndex = TRANSFERTYPE_CONTROL_ITEM;
                    break;
                case CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS:
                    comboBoxTransferType.SelectedIndex = TRANSFERTYPE_ISOCHRONOUS_ITEM;
                    switch (m_descriptor.SynchType)
                    {
                        case CyUSBOtherTypes.CyEndptSynchType.NOSYNCH:
                            comboBoxSynchType.SelectedIndex = SYNCHTYPE_NOSYNCH_ITEM;
                            break;
                        case CyUSBOtherTypes.CyEndptSynchType.ASYNCH:
                            comboBoxSynchType.SelectedIndex = SYNCHTYPE_ASYNCH_ITEM;
                            break;
                        case CyUSBOtherTypes.CyEndptSynchType.ADAPTIVE:
                            comboBoxSynchType.SelectedIndex = SYNCHTYPE_ADAPTIVE_ITEM;
                            break;
                        case CyUSBOtherTypes.CyEndptSynchType.SYNCH:
                            comboBoxSynchType.SelectedIndex = SYNCHTYPE_SYNCH_ITEM;
                            break;
                        default:
                            comboBoxSynchType.SelectedIndex = 0;
                            break;
                    }
                    switch (m_descriptor.UsageType)
                    {
                        case CyUSBOtherTypes.CyEndptUsageType.DATAEP:
                            comboBoxUsageType.SelectedIndex = USAGETYPE_DATAEP_ITEM;
                            break;
                        case CyUSBOtherTypes.CyEndptUsageType.FEEDBACKEP:
                            comboBoxUsageType.SelectedIndex = USAGETYPE_FEEDBACKEP_ITEM;
                            break;
                        case CyUSBOtherTypes.CyEndptUsageType.IMPLICITEEP:
                            comboBoxUsageType.SelectedIndex = USAGETYPE_IMPLICITEEP_ITEM;
                            break;
                        default:
                            comboBoxUsageType.SelectedIndex = 0;
                            break;
                    }
                    break;
                case CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK:
                    comboBoxTransferType.SelectedIndex = TRANSFERTYPE_BULK_ITEM;
                    break;
                case CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT:
                    comboBoxTransferType.SelectedIndex = TRANSFERTYPE_INTERRUPT_ITEM;
                    break;
                default:
                    break;
            }
            numUpDownInterval.Value = m_descriptor.bInterval;
            
            if (m_descriptor.wMaxPacketSize > numUpDownMaxPacketSize.Maximum)
            {
                m_descriptor.wMaxPacketSize = (ushort)numUpDownMaxPacketSize.Maximum;
            }
            numUpDownMaxPacketSize.Value = m_descriptor.wMaxPacketSize;
            
            checkBoxDoubleBuffer.Checked = m_descriptor.DoubleBuffer;

            if (!m_enabled)
                groupBoxParams.Enabled = false;

            CheckEPMaxPacketSize();

            m_internalChanges = false;
        }

        private void comboBoxTransferType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxTransferType.SelectedIndex == TRANSFERTYPE_ISOCHRONOUS_ITEM)
            {
                labelSynchType.Visible = true;
                labelUsageType.Visible = true;
                comboBoxSynchType.Visible = true;
                comboBoxUsageType.Visible = true;
                comboBoxSynchType.SelectedIndex = 0;
                comboBoxUsageType.SelectedIndex = 0;
                numUpDownMaxPacketSize.Maximum = CyEndpointDescriptor.MAX_PACKET_SIZE_ISOC;
                groupBoxParams.Height = comboBoxUsageType.Top + comboBoxUsageType.Height + groupBoxParams.Height -
                                        (numUpDownMaxPacketSize.Top + numUpDownMaxPacketSize.Height) +
                                        (numUpDownMaxPacketSize.Top - numUpDownInterval.Top)*2;
                checkBoxDoubleBuffer.Top = groupBoxParams.Top + groupBoxParams.Height + 7;
            }
            else
            {
                labelSynchType.Visible = false;
                labelUsageType.Visible = false;
                comboBoxSynchType.Visible = false;
                comboBoxUsageType.Visible = false;
                numUpDownMaxPacketSize.Maximum = CyEndpointDescriptor.MAX_PACKET_SIZE_GEN;
                groupBoxParams.Height = comboBoxUsageType.Top + comboBoxUsageType.Height + groupBoxParams.Height -
                                        (numUpDownMaxPacketSize.Top + numUpDownMaxPacketSize.Height);
                checkBoxDoubleBuffer.Top = groupBoxParams.Top + groupBoxParams.Height + 7;
            }

            if (!m_internalChanges)
                numUpDownMaxPacketSize_Validated(this, EventArgs.Empty);

            if (comboBoxTransferType.SelectedIndex == TRANSFERTYPE_BULK_ITEM)
            {
                numUpDownInterval.Enabled = false;
            }
            else
            {
                numUpDownInterval.Enabled = true;
            }
        }

        private void CheckEPMaxPacketSize()
        {
            if ((m_parameters.EPMemoryMgmt != CyUSBFSParameters.CyMemoryManagement.EP_DMAauto) &&
                (numUpDownMaxPacketSize.Value > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA))
            {
                errProvider.SetError(numUpDownMaxPacketSize, Properties.Resources.ERR_EP_MAXPACKETSIZE);
            }
            else if ((comboBoxTransferType.SelectedIndex == TRANSFERTYPE_BULK_ITEM) &&
                 (CyEndpointDescriptor.PossibleMaxPacketValues.Contains((ushort)numUpDownMaxPacketSize.Value) == false))
            {
                errProvider.SetError(numUpDownMaxPacketSize, Properties.Resources.MSG_BULK_MAXPACKETSIZE);
            }
            else
            {
                errProvider.SetError(numUpDownMaxPacketSize, String.Empty);
            }
        }

        #region Validation

        private void comboBoxEndpointNum_Validated(object sender, EventArgs e)
        {
            if ((comboBoxEndpointNum.SelectedIndex >= 0) && (comboBoxDirection.SelectedIndex >= 0))
            {
                byte endpointNum = (byte) (comboBoxEndpointNum.SelectedIndex + 1);
                byte direction = (byte) (1 - comboBoxDirection.SelectedIndex);
                m_descriptor.bEndpointAddress = (byte)(endpointNum | 
                                                      (direction << CyEndpointDescriptor.EP_DIRECTION_BIT));
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
        }

        private void comboBoxTransferType_Validated(object sender, EventArgs e)
        {
            byte synchType, usageType;
            switch (comboBoxTransferType.SelectedIndex)
            {
                case TRANSFERTYPE_CONTROL_ITEM:
                    m_descriptor.bmAttributes = (byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_CONTROL; 
                    break;
                case TRANSFERTYPE_ISOCHRONOUS_ITEM:
                    switch (comboBoxSynchType.SelectedIndex)
                    {
                        case SYNCHTYPE_NOSYNCH_ITEM:
                            synchType = (byte)CyUSBOtherTypes.CyEndptSynchType.NOSYNCH;
                            break;
                        case SYNCHTYPE_ASYNCH_ITEM:
                            synchType = (byte)CyUSBOtherTypes.CyEndptSynchType.ASYNCH;
                            break;
                        case SYNCHTYPE_ADAPTIVE_ITEM:
                            synchType = (byte)CyUSBOtherTypes.CyEndptSynchType.ADAPTIVE;
                            break;
                        case SYNCHTYPE_SYNCH_ITEM:
                            synchType = (byte)CyUSBOtherTypes.CyEndptSynchType.SYNCH;
                            break;
                        default:
                            synchType = 0;
                            break;
                    }
                    switch (comboBoxUsageType.SelectedIndex)
                    {
                        case USAGETYPE_DATAEP_ITEM:
                            usageType = (byte)CyUSBOtherTypes.CyEndptUsageType.DATAEP;
                            break;
                        case USAGETYPE_FEEDBACKEP_ITEM:
                            usageType = (byte)CyUSBOtherTypes.CyEndptUsageType.FEEDBACKEP;
                            break;
                        case USAGETYPE_IMPLICITEEP_ITEM:
                            usageType = (byte)CyUSBOtherTypes.CyEndptUsageType.IMPLICITEEP;
                            break;
                        default:
                            usageType = 0;
                            break;
                    }
                    m_descriptor.bmAttributes = (byte)
                                            ((byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS | 
                                            (synchType << CyEndpointDescriptor.SYNCH_TYPE_BIT) | 
                                            (usageType << CyEndpointDescriptor.USAGE_TYPE_BIT));
                    break;
                case TRANSFERTYPE_BULK_ITEM:
                    m_descriptor.bmAttributes = (byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK;
                    break;
                case TRANSFERTYPE_INTERRUPT_ITEM:
                    m_descriptor.bmAttributes = (byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT;
                    break;
                default:
                    break;
            }
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void checkBoxDoubleBuffer_CheckedChanged(object sender, EventArgs e)
        {
            m_descriptor.DoubleBuffer = checkBoxDoubleBuffer.Checked;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void numUpDownInterval_Validated(object sender, EventArgs e)
        {
            if (m_descriptor.bInterval != Convert.ToByte(numUpDownInterval.Value))
            {
                m_descriptor.bInterval = Convert.ToByte(numUpDownInterval.Value);
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
        }

        private void numUpDownMaxPacketSize_Validated(object sender, EventArgs e)
        {
            if (m_descriptor.wMaxPacketSize != Convert.ToUInt16(numUpDownMaxPacketSize.Value))
            {
                m_descriptor.wMaxPacketSize = Convert.ToUInt16(numUpDownMaxPacketSize.Value);
                if (!m_internalChanges)
                    m_parameters.ParamDeviceTreeChanged();
            }
            CheckEPMaxPacketSize();
        }

        #endregion Validation
    }
}
