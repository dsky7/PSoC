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
using CyDesigner.Extensions.Scc;

namespace TCPWM_P4_v1_10
{
    public partial class CyPWMTab : CyEditingWrapperControl
    {
        enum CySignals
        {
            [Description("reload")]
            RELOAD,
            [Description("start")]
            START,
            [Description("stop")]
            STOP,
            [Description("switch")]
            SWITCH,
            [Description("count")]
            COUNT
        };
        
        private CyImagePWM m_counterGraph;

        public override string TabName
        {
            get { return "PWM"; }
        }

        #region Constructor(s)
        public CyPWMTab(CyParameters prms)
            :base(prms)
        {
            InitializeComponent();

            m_prms.m_pwmTab = this;
            registerGrid.m_prms = prms;

            CyParameters.FillComboFromEnum(m_cbPwmMode, typeof(CyPWMMode));
            CyParameters.FillComboFromEnum(m_cbKillEvent, typeof(CyPWMEvent));
            CyParameters.FillComboFromEnum(m_cbStopEvent, typeof(CyPWMStop));
            CyParameters.FillComboFromEnum(m_cbOutCCInvert, typeof(CyPWMInvert));
            CyParameters.FillComboFromEnum(m_cbOutLineInvert, typeof(CyPWMInvert));
            CyParameters.FillComboFromEnum(m_cbAlign, typeof(CyPWMAlign));
            CyParameters.FillComboFromEnum(m_cbRunMode, typeof(CyRunMode));

            m_cbPrescaler.Items.Clear();
            m_cbPrescaler.Items.AddRange(CyParameters.PRESCALER_ITEMS_LIST);

            InitAdvTable();

            m_counterGraph = new CyImagePWM();
            m_pbCounterGraph.Image = m_counterGraph.m_bmp;
            m_pbCounterGraph.SizeMode = PictureBoxSizeMode.Normal;

            m_cbPrescaler.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                if ((sender as ComboBox).SelectedIndex != -1)
                    m_prms.Prescaler = (byte)(sender as ComboBox).SelectedIndex;
            };
            m_cbPwmMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMMode = CyParameters.GetEnum<CyPWMMode>((sender as Control).Text);

                // If PWM Mode is "PWM_DT", Prescaler value is fixed "1x"
                if (m_prms.PWMMode == CyPWMMode.PWM_DT)
                {
                    m_cbPrescaler.SelectedIndex = 0;
                }

                UpdateVisibility();
                UpdateCounterGraph();
            };
            m_cbKillEvent.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMKillEvent = CyParameters.GetEnum<CyPWMEvent>((sender as Control).Text);
            };
            m_cbStopEvent.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMStopEvent = CyParameters.GetEnum<CyPWMStop>((sender as Control).Text);
                UpdateVisibility();
            };
            m_cbOutCCInvert.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMOutCCInvert = CyParameters.GetEnum<CyPWMInvert>((sender as Control).Text);
                UpdateCounterGraph();
            };
            m_cbOutLineInvert.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMOutInvert = CyParameters.GetEnum<CyPWMInvert>((sender as Control).Text);
                UpdateCounterGraph();
            };
            m_cbAlign.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMSetAlign = CyParameters.GetEnum<CyPWMAlign>((sender as Control).Text);
                UpdateCounterGraph();
            };
            m_cbRunMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.RunMode = CyParameters.GetEnum<CyRunMode>((sender as Control).Text);
            };
            m_pbCounterGraph.SizeChanged += delegate(object sender, EventArgs e)
            {
                UpdateCounterGraph();
            };

            numUpDownDeadTime.ValueChanged += delegate(object sender, EventArgs e)
            {
                m_prms.PWMDeadTimeCycle = (byte)numUpDownDeadTime.Value;
                UpdateCounterGraph();
            };

            EventHandler interruptCheckChanged = delegate(object sender, EventArgs e)
            {
                if (m_cbInterruptOnCC.Checked && m_cbInterruptOnTC.Checked)
                    m_prms.InterruptMask = CyInterruptMask.INTR_MASK_TC_CC;
                else if (m_cbInterruptOnCC.Checked)
                    m_prms.InterruptMask = CyInterruptMask.INTR_MASK_CC_MATCH;
                else if (m_cbInterruptOnTC.Checked)
                    m_prms.InterruptMask = CyInterruptMask.INTR_MASK_TC;
                else
                    m_prms.InterruptMask = CyInterruptMask.INTR_MASK_NONE;
            };
            m_cbInterruptOnCC.CheckedChanged += interruptCheckChanged;
            m_cbInterruptOnTC.CheckedChanged += interruptCheckChanged;

            dgvAdvanced.CellValueChanged += new DataGridViewCellEventHandler(dgvAdvanced_CellValueChanged);
        }
        #endregion Constructor(s)

        #region Public functions
        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>(base.GetErrors());
            errs.AddRange(registerGrid.GetErrors());
            return errs;
        }
       
        public void UpdateFormFromParams()
        {
            if (m_prms == null) return;

            try
            {
                m_cbPrescaler.SelectedIndex = (int)m_prms.Prescaler;
            }
            catch
            {
                m_cbPrescaler.SelectedIndex = 0;
            }

            CyParameters.SetComboValue(m_cbPwmMode, m_prms.PWMMode);
            CyParameters.SetComboValue(m_cbKillEvent, m_prms.PWMKillEvent);
            CyParameters.SetComboValue(m_cbStopEvent, m_prms.PWMStopEvent);
            CyParameters.SetComboValue(m_cbOutCCInvert, m_prms.PWMOutCCInvert);
            CyParameters.SetComboValue(m_cbOutLineInvert, m_prms.PWMOutInvert);
            CyParameters.SetComboValue(m_cbAlign, m_prms.PWMSetAlign);
            CyParameters.SetComboValue(m_cbRunMode, m_prms.RunMode);

            numUpDownDeadTime.Value = m_prms.PWMDeadTimeCycle;

            bool both = m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.RELOAD].Value = m_prms.ReloadPresent;
            dgvAdvanced[1, (int)CySignals.START].Value = m_prms.StartPresent;
            dgvAdvanced[1, (int)CySignals.STOP].Value = m_prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.COUNT].Value = m_prms.CountPresent;
            dgvAdvanced[1, (int)CySignals.SWITCH].Value = m_prms.SwitchPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.RELOAD], m_prms.ReloadMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.START], m_prms.StartMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], m_prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.COUNT], m_prms.CountMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.SWITCH], m_prms.SwitchMode);

            registerGrid.UpdateFromParams();

            UpdateVisibility();
        }
        #endregion Public functions

        #region Private functions
        private void InitAdvTable()
        {
            ColumnMode.Items.AddRange(CyParameters.GetDescriptionList(typeof(CyTriggerMode)));

            string[] signals = CyParameters.GetDescriptionList(typeof(CySignals));
            for (int i = 0; i < signals.Length; i++)
            {
                dgvAdvanced.Rows.Add(signals[i], false, ColumnMode.Items[0]);
            }
            DataGridViewComboBoxCell switchModeCell = (DataGridViewComboBoxCell)
                                                dgvAdvanced.Rows[(int)CySignals.SWITCH].Cells[ColumnMode.Index];
            // Remove "Level" option for switch signal
            switchModeCell.Items.RemoveAt(3);
        }

        private void UpdateVisibility()
        {
            if (m_prms == null) return;

            numUpDownDeadTime.Enabled = m_prms.PWMMode == CyPWMMode.PWM_DT;
            labelDtCycle.Visible = m_prms.PWMMode != CyPWMMode.PWM_PR;
            numUpDownDeadTime.Visible = m_prms.PWMMode != CyPWMMode.PWM_PR;
            m_labelRunMode.Visible = m_prms.PWMMode == CyPWMMode.PWM_PR;
            m_cbRunMode.Visible = m_prms.PWMMode == CyPWMMode.PWM_PR;

            m_cbPrescaler.Enabled = m_prms.PWMMode != CyPWMMode.PWM_DT;
            m_cbAlign.Enabled = (m_prms.PWMMode != CyPWMMode.PWM_PR);
            m_cbKillEvent.Enabled = (m_prms.PWMMode != CyPWMMode.PWM_PR);

            dgvAdvanced[0, (int)CySignals.STOP].Value = (m_prms.PWMMode == CyPWMMode.PWM_DT) ? "kill" : "stop";
            m_prms.DisableRow(dgvAdvanced.Rows[(int)CySignals.COUNT], m_prms.PWMMode == CyPWMMode.PWM_PR);

            registerGrid.UpdateVisibility();
        }

        private void UpdateCounterGraph()
        {
            if (m_prms.PWMMode == CyPWMMode.PWM_PR)
            {
                m_pbCounterGraph.Image = null;
                m_pbCounterGraph.BackColor = SystemColors.Control;
                return; 
            }
            m_pbCounterGraph.BackColor = Color.White;
            m_counterGraph.m_align = m_prms.PWMSetAlign;
            m_counterGraph.m_period = m_prms.Period1;
            m_counterGraph.m_period2 = m_prms.Period2;
            m_counterGraph.m_swapPeriod = m_prms.PeriodSwap == CySwapEnable.SWAP_ENABLE;
            m_counterGraph.m_compare1 = m_prms.Compare1;
            m_counterGraph.m_compare2 = m_prms.Compare2;
            m_counterGraph.m_swapCompare = m_prms.CompareSwap == CySwapEnable.SWAP_ENABLE;
            m_counterGraph.m_pwmMode = m_prms.PWMMode;
            m_counterGraph.m_deadTime = m_prms.PWMDeadTimeCycle;
            m_counterGraph.m_outInvert = m_prms.PWMOutInvert;
            m_counterGraph.m_outCCInvert = m_prms.PWMOutCCInvert;
            m_counterGraph.m_imageSize = m_pbCounterGraph.Size;
            m_counterGraph.UpdateBmp();
            m_pbCounterGraph.Image = m_counterGraph.m_bmp;
        }
        #endregion Private functions

        #region Event handlers
        void dgvAdvanced_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == ColumnPresent.Index)
            {
                bool selValue = (bool)((DataGridViewCheckBoxCell)dgvAdvanced[e.ColumnIndex, e.RowIndex]).Value;
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.RELOAD:
                        m_prms.ReloadPresent = selValue;
                        break;
                    case CySignals.START:
                        m_prms.StartPresent = selValue;
                        break;
                    case CySignals.STOP:
                        m_prms.StopPresent = selValue;
                        break;
                    case CySignals.SWITCH:
                        m_prms.SwitchPresent = selValue;
                        break;
                    case CySignals.COUNT:
                        m_prms.CountPresent = selValue;
                        break;
                    default:
                        break;
                }
            }
            else if (e.ColumnIndex == ColumnMode.Index)
            {
                CyTriggerMode selValue = CyParameters.GetEnum<CyTriggerMode>(
                                               dgvAdvanced[e.ColumnIndex, e.RowIndex].Value.ToString());
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.RELOAD:
                        m_prms.ReloadMode = selValue;
                        break;
                    case CySignals.START:
                        m_prms.StartMode = selValue;
                        break;
                    case CySignals.STOP:
                        m_prms.StopMode = selValue;
                        break;
                    case CySignals.SWITCH:
                        m_prms.SwitchMode = selValue;
                        break;
                    case CySignals.COUNT:
                        m_prms.CountMode = selValue;
                        break;
                    default:
                        break;
                }
            }
        }

        private void registerGrid_DataChanged(object sender, EventArgs e)
        {
            UpdateCounterGraph();
        }
        #endregion Event handlers    
    }
}

