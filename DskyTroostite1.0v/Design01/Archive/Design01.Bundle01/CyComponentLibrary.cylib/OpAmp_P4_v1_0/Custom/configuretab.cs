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

namespace OpAmp_P4_v1_0
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        public string TabName
        {
            get { return "Configure"; }
        }

        CyParameters m_params;

        #region Constructor(s)
        public CyConfigureTab(CyParameters parameters)
        {
            m_params = parameters;
            InitializeComponent();

            rbModeOpamp.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbModeFollower.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbOutput1mA.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbOutput10mA.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedSlow.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedMedium.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedHigh.CheckedChanged += new EventHandler(rb_CheckedChanged);
            m_rbHighSpeed.CheckedChanged += new EventHandler(rb_CheckedChanged);
            m_rbBalanced.CheckedChanged += new EventHandler(rb_CheckedChanged);
            m_rbHighStability.CheckedChanged += new EventHandler(rb_CheckedChanged);
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string paramName in m_params.m_inst.GetParamNames())
            {
                CyCompDevParam param = m_params.m_inst.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            rbModeOpamp.Checked = (m_params.Mode == CyEModeType.OPAMP);
            rbModeFollower.Checked = !rbModeOpamp.Checked;

            rbOutput1mA.Checked = (m_params.OutputCurrent == CyEOutputType.OPAMP_STANDARD_1MA);
            rbOutput10mA.Checked = !rbOutput1mA.Checked;

            rbSpeedSlow.Checked = (m_params.Power == CyEPowerType.OPAMP_LOW_POWER);
            rbSpeedMedium.Checked = (m_params.Power == CyEPowerType.OPAMP_MED_POWER);
            rbSpeedHigh.Checked = (m_params.Power == CyEPowerType.OPAMP_HIGH_POWER);

            m_rbHighSpeed.Checked = (m_params.Compensation == CyECompensationType.HighSpeed);
            m_rbBalanced.Checked = (m_params.Compensation == CyECompensationType.Balanced);
            m_rbHighStability.Checked = (m_params.Compensation == CyECompensationType.HighStability);
        }
        #endregion

        #region Event handlers
        void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false)
                return;

            else if (rb == rbModeOpamp)
                m_params.Mode = CyEModeType.OPAMP;
            else if (rb == rbModeFollower)
                m_params.Mode = CyEModeType.FOLLOWER;

            else if (rb == rbOutput1mA)
                m_params.OutputCurrent = CyEOutputType.OPAMP_STANDARD_1MA;
            else if (rb == rbOutput10mA)
                m_params.OutputCurrent = CyEOutputType.OPAMP_HIGH_10MA;

            else if (rb == rbSpeedSlow)
                m_params.Power = CyEPowerType.OPAMP_LOW_POWER;
            else if (rb == rbSpeedMedium)
                m_params.Power = CyEPowerType.OPAMP_MED_POWER;
            else if (rb == rbSpeedHigh)
                m_params.Power = CyEPowerType.OPAMP_HIGH_POWER;

            else if (rb == m_rbHighSpeed)
                m_params.Compensation = CyECompensationType.HighSpeed;
            else if (rb == m_rbBalanced)
                m_params.Compensation = CyECompensationType.Balanced;
            else if (rb == m_rbHighStability)
                m_params.Compensation = CyECompensationType.HighStability;
        }
        #endregion Event handlers
    }
}
