/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;

namespace MDIO_Interface_v1_10
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        #region Class properties
        public override string TabName
        {
            get { return CyCustomizer.GENERAL_TAB_NAME; }
        }
        #endregion

        #region Constructor(s)
        public CyBasicTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            m_params = param;
            m_params.m_basicTab = this;

            // Initialize combobox
            cbDeviceAddress.Items.Clear();
            cbDeviceAddress.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyDeviceAddressType)));
        }
        #endregion

        #region Initialization
        public void UpdateUI()
        {
            rbBasicConfig.Checked = (m_params.OperationMode == CyOperationModeType.BASIC);
            rbAdvancedConfig.Checked = (m_params.OperationMode == CyOperationModeType.ADVANCED);
            rbHardware.Checked = (m_params.PhysicalAddressMode == CyPhysicalAddressType.HARDWARE);
            rbFirmware.Checked = (m_params.PhysicalAddressMode == CyPhysicalAddressType.FIRMWARE);
            tbPhysicalAddress.Text = CyParameters.ConvertDecToHexWithoutPrefix(m_params.PhysicalAddress);
            chbEnableExternalOE.Checked = m_params.EnableExternOE;
            // Update Device Address combobox with Expression View handling
            string errorMessage = string.Empty;
            if (string.IsNullOrEmpty(CyEnumConverter.GetEnumDesc(m_params.DeviceAddress)) == false)
            {
                cbDeviceAddress.SelectedItem = CyEnumConverter.GetEnumDesc(m_params.DeviceAddress);
                RemoveEmptyItem(cbDeviceAddress);
            }
            else
            {
                errorMessage = string.Format(Resources.UnrecognizableFormat, CyParamNames.DEVICE_ADDRESS);
                SetEmptyItem(cbDeviceAddress);
            }
            m_errorProvider.SetError(cbDeviceAddress, errorMessage);
        }

        private void SetEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(string.Empty) == false)
            {
                comboBox.Items.Insert(0, string.Empty);
                bool currentGEM = m_params.GlobalEditMode;
                m_params.GlobalEditMode = false;
                comboBox.SelectedIndex = 0;
                m_params.GlobalEditMode = currentGEM;
            }
        }

        private void RemoveEmptyItem(ComboBox comboBox)
        {
            if (comboBox.Items.Contains(string.Empty))
                comboBox.Items.Remove(string.Empty);
        }
        #endregion

        #region Event Handlers
        private void cbDeviceAddress_SelectedIndexChanged(object sender, EventArgs e)
        {
            object devAddressEnumValue = CyEnumConverter.GetEnumValue(cbDeviceAddress.SelectedItem,
                                                                          typeof(CyDeviceAddressType));
            if (devAddressEnumValue != null)
            {
                m_params.DeviceAddress = (CyDeviceAddressType)devAddressEnumValue;
                RemoveEmptyItem(cbDeviceAddress);
                m_errorProvider.SetError(cbDeviceAddress, string.Empty);
            }
        }

        private void rbConfig_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioBox = (RadioButton)sender;
            if (radioBox.Checked == false)
            {
                return;
            }
            if (radioBox == rbBasicConfig)
            {
                m_params.OperationMode = CyOperationModeType.BASIC;
                m_params.m_editor.HideCustomPage(Resources.AdvancedTabDisplayName);
            }
            else
            {
                m_params.OperationMode = CyOperationModeType.ADVANCED;
                m_params.m_editor.ShowCustomPage(Resources.AdvancedTabDisplayName);
            }
        }

        private void rbPhAddress_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioBox = (RadioButton)sender;
            if (radioBox.Checked == false)
            {
                return;
            }
            if (radioBox == rbHardware)
            {
                m_params.PhysicalAddressMode = CyPhysicalAddressType.HARDWARE;
            }
            else
            {
                m_params.PhysicalAddressMode = CyPhysicalAddressType.FIRMWARE;
            }
            tbPhysicalAddress.Enabled = (m_params.PhysicalAddressMode == CyPhysicalAddressType.FIRMWARE);
            lbl0x.Enabled = tbPhysicalAddress.Enabled;
            labelPhysicalAddress.Enabled = tbPhysicalAddress.Enabled;
        }

        private void chbEnableExternalOE_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableExternOE = ((CheckBox)sender).Checked;
        }

        private void tbPhysicalAddress_TextChanged(object sender, EventArgs e)
        {
            byte? value;
            try
            {
                value = (byte)CyParameters.ConvertHexToDec(tbPhysicalAddress.Text, false);
            }
            catch (Exception)
            {
                value = null;
            }
            string message = string.Format(Resources.PhysicalAddressOutOfRange,
                                           CyParameters.ConvertDecToHex(CyParamRanges.PHYS_ADDRESS_MIN),
                                           CyParameters.ConvertDecToHex(CyParamRanges.PHYS_ADDRESS_MAX));
            if (value != null)
            {

                if (value < CyParamRanges.PHYS_ADDRESS_MIN || value > CyParamRanges.PHYS_ADDRESS_MAX)
                {
                    m_errorProvider.SetError(tbPhysicalAddress, message);
                }
                else
                {
                    m_errorProvider.SetError(tbPhysicalAddress, string.Empty);
                }
            }
            else
            {
                m_errorProvider.SetError(tbPhysicalAddress, message);
            }
            m_params.PhysicalAddress = value;
        }
        #endregion
    }
}
