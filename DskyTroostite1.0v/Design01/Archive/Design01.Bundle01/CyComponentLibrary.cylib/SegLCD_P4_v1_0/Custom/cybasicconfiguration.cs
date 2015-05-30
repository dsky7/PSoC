/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SegLCD_P4_v1_0
{
    public partial class CyBasicConfiguration : CyEditingWrapperControl
    {
        #region Fields
        private bool m_updateComboboxLocked = true;
        #endregion Fields

        #region Constructors
        public CyBasicConfiguration()
        {
            InitializeComponent();
        }

        public CyBasicConfiguration(CyLCDParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            errProvider.SetIconAlignment(labelNoClock, ErrorIconAlignment.MiddleLeft);

            m_parameters.m_cyBasicConfigurationTab = this;

            InitComboBoxes();
            LoadValuesFromParameters();
        }

        private void CyBasicConfiguration_Load(object sender, EventArgs e)
        {
            if (m_parameters.m_termQuery != null)
            {
                m_parameters.UpdateClock(m_parameters.m_inst, m_parameters.m_termQuery);
            }
        }
        #endregion Constructors

        #region CyEditingWrapperControl overriden functions
        public override string TabName
        {
            get { return "General"; }
        }
        #endregion CyEditingWrapperControl overriden functions

        #region Initialization
        public void LoadValuesFromParameters()
        {
            numUpDownNumCommonLines.Value = m_parameters.NumCommonLines;
            numUpDownNumSegmentLines.Value = m_parameters.NumSegmentLines;

            comboBoxDrivingMode.SelectedIndex = (byte)m_parameters.DrivingMode;
            comboBoxBiasType.SelectedIndex = (byte)m_parameters.BiasType;
            comboBoxWaveformType.SelectedIndex = (byte)m_parameters.WaveformType;
            comboBoxLCDMode.SelectedIndex = (byte)m_parameters.LCDMode;
        }

        private void InitComboBoxes()
        {
            comboBoxDrivingMode.DataSource =
                CyLCDParameters.GetEnumValuesDescription(typeof(CyLCDParameters.CyDrivingModeType));
            comboBoxBiasType.DataSource =
                CyLCDParameters.GetEnumValuesDescription(typeof(CyLCDParameters.CyBiasTypes));
            comboBoxWaveformType.DataSource =
                CyLCDParameters.GetEnumValuesDescription(typeof(CyLCDParameters.CyWaveformTypes));
            comboBoxLCDMode.DataSource =
                CyLCDParameters.GetEnumValuesDescription(typeof(CyLCDParameters.CyLCDModeType));

            InitFrameRateCombobox();
            InitContrastCombobox();
        }

        private void InitFrameRateCombobox()
        {
            m_updateComboboxLocked = true;
            string lastValue = m_parameters.FrameRate.ToString();

            if (m_parameters.ExternalClockHz <= 0)
            {
                comboBoxFrameRate.DataSource = null;
            }
            else
            {
                comboBoxFrameRate.DataSource = m_parameters.UpdateFrameRateRange();

                if (comboBoxFrameRate.Items.Count == 0)
                {
                    errProvider.SetError(comboBoxFrameRate, Properties.Resources.EMPTY_FRAMERATE_LIST);
                }
                else
                {
                    errProvider.SetError(comboBoxFrameRate, "");
                }
            }

            if (comboBoxFrameRate.Items.Contains(lastValue))
                comboBoxFrameRate.Text = lastValue;
            else
                comboBoxFrameRate.SelectedIndex = comboBoxFrameRate.Items.Count - 1;
            m_updateComboboxLocked = false;
        }

        private void InitContrastCombobox()
        {
            m_updateComboboxLocked = true;
            string lastValue = m_parameters.Contrast.ToString();
            if (m_parameters.ExternalClockHz <= 0)
            {
                comboBoxContrast.DataSource = null;
            }
            else
            {
                comboBoxContrast.DataSource = m_parameters.UpdateContrastRange();
            }

            if (comboBoxContrast.Items.Contains(lastValue))
                comboBoxContrast.Text = lastValue;
            else
                comboBoxContrast.SelectedIndex = comboBoxContrast.Items.Count - 1;
            m_updateComboboxLocked = false;
        }

        #endregion Initialization

        #region Event handlers
        private void numUpDownNumLines_ValueChanged(object sender, EventArgs e)
        {
            bool isCommonChanged = sender == numUpDownNumCommonLines;
            NumericUpDown numUpDown = (NumericUpDown)sender;
            byte paramValue = isCommonChanged ? m_parameters.NumCommonLines : m_parameters.NumSegmentLines;

            if (isCommonChanged)
            {
                numUpDownNumSegmentLines.Maximum = CyParamRange.COM_SEG_MAX - (int)numUpDownNumCommonLines.Value;
            }

            bool updateHelpers = numUpDown.Value != paramValue;

            if (paramValue != (byte)numUpDown.Value)
            {
                if (isCommonChanged)
                {
                    m_parameters.NumCommonLines = (byte)numUpDown.Value;

                    InitFrameRateCombobox();
                    InitContrastCombobox();
                }
                else
                    m_parameters.NumSegmentLines = (byte)numUpDown.Value;
            }

            //Update Empty helper
            if (updateHelpers)
            {
                m_parameters.m_cyHelpersTab.ComSegLinesNumChanged();
            }
        }

        private void comboBoxDrivingMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.DrivingMode = (CyLCDParameters.CyDrivingModeType)comboBoxDrivingMode.SelectedIndex;

            comboBoxBiasType.Enabled = (m_parameters.DrivingMode == CyLCDParameters.CyDrivingModeType.PWM);
        }

        private void comboBoxWaveformType_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.WaveformType = (CyLCDParameters.CyWaveformTypes)comboBoxWaveformType.SelectedIndex;
        }

        private void comboBoxBiasType_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.BiasType = (CyLCDParameters.CyBiasTypes)comboBoxBiasType.SelectedIndex;
        }

        private void comboBoxLCDMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.LCDMode = (CyLCDParameters.CyLCDModeType)comboBoxLCDMode.SelectedIndex;
            m_parameters.m_desiredLCDMode = m_parameters.LCDMode;

            ClockUpdated();
        }

        private void comboBoxFrameRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxFrameRate.SelectedIndex < 0)
                return;

            m_parameters.FrameRate = Convert.ToByte(comboBoxFrameRate.Text);

            if (m_updateComboboxLocked == false)
            {
                InitContrastCombobox();
            }
        }

        private void comboBoxContrast_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxContrast.SelectedIndex < 0)
                return;

            m_parameters.Contrast = Convert.ToByte(comboBoxContrast.Text);

            if (m_updateComboboxLocked == false)
            {
                InitFrameRateCombobox();
            }
        }

        public void ClockUpdated()
        {
            InitFrameRateCombobox();
            InitContrastCombobox();

            labelNoClock.Visible = (m_parameters.ExternalClockHz <= 0);
            errProvider.SetError(labelNoClock, labelNoClock.Visible ? " ": "");
        }
        #endregion Event handlers
    }
}
