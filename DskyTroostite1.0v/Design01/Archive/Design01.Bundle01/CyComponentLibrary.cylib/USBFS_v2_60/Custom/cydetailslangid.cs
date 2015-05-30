/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Windows.Forms;

namespace USBFS_v2_60
{
    public partial class CyDetailsLangID : UserControl
    {
        public CyStringZeroDescriptor m_descriptor;
        private CyUSBFSParameters m_parameters;

        public CyDetailsLangID(CyStringZeroDescriptor descriptor, CyUSBFSParameters parameters)
        {
            InitializeComponent();
            m_descriptor = descriptor;
            m_parameters = parameters;
            for (int i = 0; i < CyUsbConst.LangIDNames.Length; i++)
            {
                comboBoxLangID.Items.Add(CyUsbConst.LangIDNames[i]);
            }
        }

        private void CyDetailsLangID_Load(object sender, EventArgs e)
        {
            int index = Array.IndexOf(CyUsbConst.LANG_ID_TABLE, m_descriptor.wLANGID);
            comboBoxLangID.Text = comboBoxLangID.Items[index].ToString();
        }

        private void comboBoxLangID_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((comboBoxLangID.SelectedIndex >= 0) &&
                (m_descriptor.wLANGID != CyUsbConst.LANG_ID_TABLE[comboBoxLangID.SelectedIndex]))
            {
                m_descriptor.wLANGID = CyUsbConst.LANG_ID_TABLE[comboBoxLangID.SelectedIndex];
                m_parameters.ParamStringTreeChanged();
            }
        }
    }
}