/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace USBFS_v2_70
{
    public partial class CyAdvancedPage : CyEditingWrapperControl
    {
        public CyAdvancedPage()
        {
            InitializeComponent();
        }

        public CyAdvancedPage(CyUSBFSParameters parameters)
            : base(parameters)
        {
            InitializeComponent();
            InitFields();
        }

        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PAPAM_TAB_NAME_ADVANCED; }
        }
        #endregion

        public void InitFields()
        {
            checkBoxExtClass.Checked = m_parameters.Extern_cls;
            checkBoxExtVendor.Checked = m_parameters.Extern_vnd;
            checkBoxVBusMon.Checked = m_parameters.Mon_vbus;
            checkBoxSofOutput.Checked = m_parameters.Out_sof;

            radioButtonVbusInternal.Checked = !m_parameters.Extern_vbus;
            radioButtonVbusExternal.Checked = m_parameters.Extern_vbus;
            panelVbus.Enabled = checkBoxVBusMon.Checked;
        }

        private void checkBoxExtClass_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == checkBoxExtClass)
            {
                m_parameters.Extern_cls = ((CheckBox)sender).Checked;
            }
            else if (sender == checkBoxExtVendor)
            {
                m_parameters.Extern_vnd = ((CheckBox)sender).Checked;
            }
            else if (sender == checkBoxVBusMon)
            {
                m_parameters.Mon_vbus = ((CheckBox)sender).Checked;
                panelVbus.Enabled = checkBoxVBusMon.Checked;
            }
            else if (sender == checkBoxSofOutput)
            {
                m_parameters.Out_sof = ((CheckBox)sender).Checked;
            }
        }

        private void radioButtonVbus_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            m_parameters.Extern_vbus = (rb == radioButtonVbusExternal);
        }
    }
}
