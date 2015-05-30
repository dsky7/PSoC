/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Forms;

namespace USBFS_v2_70
{
    public partial class CyDetailsInterface : UserControl
    {
        private const byte CLASS_NONE_ITEM = 0;
        private const byte CLASS_HID_ITEM = 1;
        private const byte CLASS_VENDORSPEC_ITEM = 2;

        private readonly CyInterfaceDescriptor m_descriptor;
        private readonly CyUSBFSParameters m_parameters;
        private readonly CyDeviceDescriptorPage m_parentFrm;

        public event EventHandler RemoveClassNodeEvent;

        private bool m_internalChanges = false;

        public CyDetailsInterface(CyInterfaceDescriptor descriptor, CyUSBFSParameters parameters,
                                  CyDeviceDescriptorPage parentForm)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            m_parentFrm = parentForm;
            InitFields();
        }

        protected void OnRemoveClassNodeEvent()
        {
            if (RemoveClassNodeEvent != null)
                RemoveClassNodeEvent(this, EventArgs.Empty);
        }

        private void InitFields()
        {
            m_internalChanges = true;
            FillStrings();
            labelInterfaceNumber.Text = m_descriptor.bInterfaceNumber.ToString();
            labelAlternateSettings.Text = m_descriptor.bAlternateSetting.ToString();

            switch (m_descriptor.bInterfaceClass)
            {
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE:
                    comboBoxClass.SelectedIndex = CLASS_NONE_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_HID:
                    comboBoxClass.SelectedIndex = CLASS_HID_ITEM;
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO:
                    comboBoxClass.Text = m_descriptor.bInterfaceClass.ToString("X2");
                    if (m_descriptor is CyAudioInterfaceDescriptor)
                    {
                        groupBoxParams.Enabled = false;
                    }
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC:
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_DATA:
                    comboBoxClass.Text = m_descriptor.bInterfaceClass.ToString("X2");
                    if (m_descriptor is CyCDCInterfaceDescriptor)
                    {
                       groupBoxParams.Enabled = false;
                    }
                    break;
                case (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_VENDORSPEC:
                    comboBoxClass.SelectedIndex = CLASS_VENDORSPEC_ITEM;
                    break;
                default:
                    comboBoxClass.Text = m_descriptor.bInterfaceClass.ToString("X2");
                    break;
            }

            // Interface string
            if (m_descriptor.iwInterface > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(m_descriptor.iwInterface);
                CyDescriptorNode node = m_parameters.m_stringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    comboBoxInterfaceString.SelectedItem = node.m_value;
                }
            }
            else
            {
                comboBoxInterfaceString.Text = "";
            }

            if (comboBoxSubclass.Items.Count >= m_descriptor.bInterfaceSubClass + 1)
                comboBoxSubclass.SelectedIndex = m_descriptor.bInterfaceSubClass;
            else
                comboBoxSubclass.Text = m_descriptor.bInterfaceSubClass.ToString("X2");

            numUpDownProtocol.Value = m_descriptor.bInterfaceProtocol;
            m_internalChanges = false;
        }

        private void FillStrings()
        {
            comboBoxInterfaceString.Items.Clear();
            List<CyStringDescriptor> strList = m_parameters.GetStringDescList();
            comboBoxInterfaceString.Items.AddRange(strList.ToArray());
                
        }

        private void comboBoxClass_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Set Subclasses
            comboBoxSubclass.Items.Clear();
            comboBoxSubclass.Items.Add("No subclass");
            switch (comboBoxClass.SelectedIndex)
            {
                case CLASS_NONE_ITEM:
                    break;
                case CLASS_HID_ITEM:
                    comboBoxSubclass.Items.Add("Boot Interface Subclass");
                    break;
                case CLASS_VENDORSPEC_ITEM:
                    break;
                default:
                    break;
            }

            //Save
            bool changed = false;

            // If class was changed from HID or Audio to another, remove class descriptor
            bool needDeleteClass = false;
            if ((m_descriptor.bInterfaceClass == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_HID) &&
                (comboBoxClass.SelectedIndex != CLASS_HID_ITEM))
            {
                needDeleteClass = true;
            }

            switch (comboBoxClass.SelectedIndex)
            {
                case CLASS_NONE_ITEM:
                    if (m_descriptor.bInterfaceClass != (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE)
                    {
                        m_descriptor.bInterfaceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_NONE;
                        changed = true;
                    }
                    break;
                case CLASS_HID_ITEM:
                    if (m_descriptor.bInterfaceClass != (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_HID)
                    {
                        m_descriptor.bInterfaceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_HID;
                        changed = true;
                    }
                    break;
                case CLASS_VENDORSPEC_ITEM:
                    if (m_descriptor.bInterfaceClass != (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_VENDORSPEC)
                    {
                        m_descriptor.bInterfaceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_VENDORSPEC;
                        changed = true;
                    }
                    break;
                default:
                    break;
            }
            if (comboBoxClass.SelectedIndex >= 0)
            {
                errorProvider.SetError(comboBoxClass, "");
            }
            if (changed)
            {
                if (comboBoxSubclass.Items.Count >= m_descriptor.bInterfaceSubClass + 1)
                    comboBoxSubclass.SelectedIndex = m_descriptor.bInterfaceSubClass;
                else
                    comboBoxSubclass.Text = m_descriptor.bInterfaceSubClass.ToString("X2");

                if (needDeleteClass)
                    OnRemoveClassNodeEvent();
                if (comboBoxClass.SelectedIndex == CLASS_HID_ITEM)
                {
                    m_parentFrm.AddNode(CyUSBDescriptorType.HID);
                }
            }
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBoxSubclass_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Save
            if (comboBoxSubclass.SelectedIndex >= 0)
            {
                m_descriptor.bInterfaceSubClass = (byte)comboBoxSubclass.SelectedIndex;
                errorProvider.SetError(comboBoxSubclass, "");
            }
            else
            {
                m_descriptor.bInterfaceSubClass = 0;
            }
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        #region Validation

        private void comboBoxInterfaceString_Validated(object sender, EventArgs e)
        {
            m_descriptor.iwInterface = CyUSBFSParameters.SaveStringDescriptor(comboBoxInterfaceString, m_parameters);
            m_descriptor.sInterface = comboBoxInterfaceString.Text;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }

        private void comboBox_Validating(object sender, System.ComponentModel.CancelEventArgs e)
        {
            byte res;
            ComboBox cb = (ComboBox) sender;
            string text = cb.Text;
            if (text.StartsWith("0x")) 
                text = text.Remove(0, 2);
            if (cb.SelectedIndex < 0)
            {
                if (Byte.TryParse(text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out res))
                {
                    if (sender == comboBoxClass)
                        m_descriptor.bInterfaceClass = res;
                    else if (sender == comboBoxSubclass)
                        m_descriptor.bInterfaceSubClass = res;

                    m_parameters.ParamDeviceTreeChanged();
                }

            }
            if (!String.IsNullOrEmpty(errorProvider.GetError(cb)))
                e.Cancel = true;
        }

        /// <summary>
        /// Used for Class and Subclass comboboxes to set errorProvider
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox_TextChanged(object sender, EventArgs e)
        {
            byte res;
            ComboBox cb = (ComboBox)sender;
            string text = cb.Text;
            if (text.StartsWith("0x"))
                text = text.Remove(0, 2);
            if ((cb.SelectedIndex < 0) || (!cb.Items.Contains(text)))
            {
                if (Byte.TryParse(text, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out res))
                    errorProvider.SetError(cb, "");
                else
                    errorProvider.SetError(cb, 
                                           String.Format(Properties.Resources.MSG_INCORRECT_VALUE_RANGE, "00", "FF"));
            }
            else
            {
                errorProvider.SetError(cb, "");
            }
        }

        #endregion Validation

        private void numUpDownProtocol_ValueChanged(object sender, EventArgs e)
        {
            m_descriptor.bInterfaceProtocol = (byte)numUpDownProtocol.Value;
            if (!m_internalChanges)
                m_parameters.ParamDeviceTreeChanged();
        }
    }
}
