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

namespace TCPWM_P4_v1_0
{
    public partial class CyConfigTab : CyEditingWrapperControl
    {
        public override string TabName
        {
            get { return "Configuration"; }
        }

        public CyConfigTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();
            UpdateFormFromParams();
        }

        public void UpdateFormFromParams()
        {
            switch (m_prms.TCPWMConfig)
            {
                case CyTCPWMConfig.UNCONFIG:
                    rbUnconfigured.Checked = true;
                    break;
                case CyTCPWMConfig.TIMER:
                    rbTimerCounter.Checked = true;
                    break;
                case CyTCPWMConfig.QUAD:
                    rbQuadDec.Checked = true;
                    break;
                case CyTCPWMConfig.PWM_SEL:
                    rbPWM.Checked = true;
                    break;
                default:
                    break;
            }
        }

        private void rbconfig_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false)  
            {
                return;
            }

            if (rb == rbTimerCounter)
                m_prms.TCPWMConfig = CyTCPWMConfig.TIMER;
            else if (rb == rbPWM)
                m_prms.TCPWMConfig = CyTCPWMConfig.PWM_SEL;
            else if (rb == rbQuadDec)
                m_prms.TCPWMConfig = CyTCPWMConfig.QUAD;
            else 
                m_prms.TCPWMConfig = CyTCPWMConfig.UNCONFIG;

            m_prms.UpdateTabVisibility();
        }
    }
}
