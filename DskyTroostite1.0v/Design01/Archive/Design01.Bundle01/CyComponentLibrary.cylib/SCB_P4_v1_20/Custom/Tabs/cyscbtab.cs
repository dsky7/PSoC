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
    public partial class CySCBTab : CyTabControlWrapper
    {
        private List<CheckBox> m_sfDisabledControls = new List<CheckBox>();

        public override string TabName
        {
            get
            {
                return "SCB";
            }
        }

        public CySCBTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params = param;
            m_params.m_scbTab = this;

            InitializeComponent();

            InitSFDisabledControls();

            m_chbSPI_CLK.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_SclkEnabled = (sender as CheckBox).Checked;
                VisibilityUpdate();
            };
            m_chbRxWake.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_RxWake = (sender as CheckBox).Checked;
                VisibilityUpdate();
            };
            m_chbSPI_MISO.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_MisoSdaTxEnabled = (sender as CheckBox).Checked;
            };
            m_chbSPI_MOSI.CheckedChanged += delegate(object sender, EventArgs e)
            {
                if (m_params.SCB_MosiSclRxEnabled && ((sender as CheckBox).Checked == false))
                {
                    m_chbRxWake.Checked = false;
                }
                m_params.SCB_MosiSclRxEnabled = (sender as CheckBox).Checked;
                
                VisibilityUpdate();
            };
            m_chbSPI_SS0.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_Ss0Enabled = (sender as CheckBox).Checked;
                VisibilityUpdate();
            }; 
            m_chbSPI_SS1.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_Ss1Enabled = (sender as CheckBox).Checked;
                VisibilityUpdate();
            };
            m_chbSPI_SS2.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_Ss2Enabled = (sender as CheckBox).Checked;
                VisibilityUpdate();
            };
            m_chbSPI_SS3.CheckedChanged += delegate(object sender, EventArgs e)
            {
                m_params.SCB_Ss3Enabled = (sender as CheckBox).Checked;
                VisibilityUpdate();
            };

            VisibilityUpdate();
        }

        public void VisibilityUpdate()
        {
            m_chbRxWake.Enabled = m_params.SCB_MosiSclRxEnabled;

            if (m_params.IsScbIPV1)
            {
                // Disable unavailable options
                foreach (CheckBox chb in m_sfDisabledControls)
                {
                    chb.Enabled = false;
                    m_errorProvider.SetError(chb, String.Empty);
                }

                labelSFMsg.Visible = true;

                m_chbSPI_MOSI.Text = "I2C SCL";
                m_chbSPI_MISO.Text = "I2C SDA";

                // If disabled option is already selected, enable it and display an error
                foreach (CheckBox chb in m_sfDisabledControls)
                {
                    if (chb.Checked)
                    {
                        chb.Enabled = true;
                        m_errorProvider.SetError(chb, String.Format(Resources.SFSettingsError, chb.Text));
                    }
                }
            }
        }

        public override void UpdateUI()
        {
            if (m_params == null)
                return;

            m_chbSPI_CLK.Checked = m_params.SCB_SclkEnabled;
            m_chbRxWake.Checked = m_params.SCB_RxWake;
            m_chbSPI_MISO.Checked = m_params.SCB_MisoSdaTxEnabled;
            m_chbSPI_MOSI.Checked = m_params.SCB_MosiSclRxEnabled;
            m_chbSPI_SS0.Checked = m_params.SCB_Ss0Enabled;
            m_chbSPI_SS1.Checked = m_params.SCB_Ss1Enabled;
            m_chbSPI_SS2.Checked = m_params.SCB_Ss2Enabled;
            m_chbSPI_SS3.Checked = m_params.SCB_Ss3Enabled;

            VisibilityUpdate();
        }

        private void InitSFDisabledControls()
        {
            m_sfDisabledControls = new List<CheckBox>();
            m_sfDisabledControls.Add(m_chbRxWake);
            m_sfDisabledControls.Add(m_chbSPI_CLK);
            m_sfDisabledControls.Add(m_chbSPI_SS0);
            m_sfDisabledControls.Add(m_chbSPI_SS1);
            m_sfDisabledControls.Add(m_chbSPI_SS2);
            m_sfDisabledControls.Add(m_chbSPI_SS3);
        }
    }
}
