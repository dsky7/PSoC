/*******************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace SCB_P4_v1_20
{
    public partial class CyGeneralTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "Configuration";
            }
        }
        #endregion

        #region Constructor(s)
        public CyGeneralTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params = param;
            m_params.m_generalTab = this;

            InitializeComponent();

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            switch (m_params.SCBMode)
            {
                case CyESCBMode.UNCONFIG:
                    m_rbUnconfig.Checked = true;
                    break;
                case CyESCBMode.I2C:
                    m_rbI2C.Checked = true;
                    break;
                case CyESCBMode.UART:
                    m_rbUart.Checked = true;
                    break;
                case CyESCBMode.SPI:
                    m_rbSpi.Checked = true;
                    break;
                case CyESCBMode.EZI2C:
                    m_rbEZI2C.Checked = true;
                    break;
            }
            UpdateSFDependencies();
        }

        private void UpdateSFDependencies()
        {
            if (m_params.IsScbIPV1 == false)
                return;
            labelSFMsg.Visible = true;
            m_rbSpi.Enabled = false;
            m_rbUart.Enabled = false;
            m_errorProvider.SetError(m_rbSpi, "");
            m_errorProvider.SetError(m_rbUart, "");

            if (m_params.SCBMode == CyESCBMode.SPI)
            {
                m_rbSpi.Enabled = true;
                m_errorProvider.SetError(m_rbSpi, String.Format(Resources.SFModeError, m_rbSpi.Text));
            }

            if (m_params.SCBMode == CyESCBMode.UART)
            {
                m_rbUart.Enabled = true;
                m_errorProvider.SetError(m_rbUart, String.Format(Resources.SFModeError, m_rbUart.Text));
            }
        }
        #endregion

        #region Event handlers
        private void rbconfig_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_rbI2C)
                {
                    m_params.SCBMode = CyESCBMode.I2C;
                }
                else if (sender == m_rbUart)
                {
                    m_params.SCBMode = CyESCBMode.UART;
                }
                else if (sender == m_rbSpi)
                {
                    m_params.SCBMode = CyESCBMode.SPI;
                }
                else if (sender == m_rbUnconfig)
                {
                    m_params.SCBMode = CyESCBMode.UNCONFIG;
                }
                else if (sender == m_rbEZI2C)
                {
                    m_params.SCBMode = CyESCBMode.EZI2C;
                }

                UpdateSFDependencies();
                m_params.UpdateTabVisibility();
            }
        }
        #endregion
    }
}
