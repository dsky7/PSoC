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

namespace TCPWM_P4_v1_10
{
    public partial class CyTCPWMTab : CyEditingWrapperControl
    {
        public override string TabName
        {
            get { return "TCPWM"; }
        }

        public CyTCPWMTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();
            m_prms.m_tcpwmTab = this;
        }

        public void UpdateFormFromParams()
        {
            cbSignalReload.Checked = m_prms.ReloadPresent;
            cbSignalCount.Checked = m_prms.CountPresent;
            cbSignalStart.Checked = m_prms.StartPresent;
            cbSignalStop.Checked = m_prms.StopPresent;
            cbSignalCapture.Checked = m_prms.CapturePresent;
        }

        private void cbSignal_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == cbSignalReload)
                m_prms.ReloadPresent = cbSignalReload.Checked;

            else if (sender == cbSignalCount)
                m_prms.CountPresent = cbSignalCount.Checked;

            else if (sender == cbSignalStart)
                m_prms.StartPresent = cbSignalStart.Checked;

            else if (sender == cbSignalStop)
                m_prms.StopPresent = cbSignalStop.Checked;

            else if (sender == cbSignalCapture)
                m_prms.CapturePresent = cbSignalCapture.Checked;

        }
    }
}
