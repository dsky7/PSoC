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

namespace TCPWM_P4_v1_0
{
    public partial class CyTimerCounterTab : CyEditingWrapperControl
    {
        enum CySignals
        {
            [Description("reload")]
            RELOAD,
            [Description("start")]
            START,
            [Description("stop")]
            STOP,
            [Description("capture")]
            CAPTURE,
            [Description("count")]
            COUNT
        };

        private CyImageTC m_counterGraph;

        public override string TabName
        {
            get { return "Timer/Counter"; }
        }

        #region Constructor(s)
        public CyTimerCounterTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();

            m_prms.m_tcTab = this;
            registerGrid.m_prms = prms;

            CyParameters.FillComboFromEnum(m_cbCounterMode, typeof(CyCounterMode));
            CyParameters.FillComboFromEnum(m_cbCompareCapture, typeof(CyCompCapMode));
            CyParameters.FillComboFromEnum(m_cbRunMode, typeof(CyRunMode));
            m_cbPrescaler.Items.Clear();
            m_cbPrescaler.Items.AddRange(CyParameters.PRESCALER_ITEMS_LIST);

            InitAdvTable();

            m_counterGraph = new CyImageTC();
            m_pbCounterGraph.Image = m_counterGraph.m_bmp;
            m_pbCounterGraph.SizeMode = PictureBoxSizeMode.Normal;

            m_cbPrescaler.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                if ((sender as ComboBox).SelectedIndex != -1)
                    m_prms.Prescaler = (byte)(sender as ComboBox).SelectedIndex;
            };
            m_cbCounterMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.CountingModes = CyParameters.GetEnum<CyCounterMode>((sender as Control).Text);
                UpdateCounterGraph();
            };
            m_cbCompareCapture.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.CompCapMode = CyParameters.GetEnum<CyCompCapMode>((sender as Control).Text);
                registerGrid.ValidatePeriodVsCompare();
                UpdateVisibility();
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
            CyParameters.SetComboValue(m_cbCounterMode, m_prms.CountingModes);
            CyParameters.SetComboValue(m_cbCompareCapture, m_prms.CompCapMode);
            CyParameters.SetComboValue(m_cbRunMode, m_prms.RunMode);

            bool both = m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.RELOAD].Value = m_prms.ReloadPresent;
            dgvAdvanced[1, (int)CySignals.START].Value = m_prms.StartPresent;
            dgvAdvanced[1, (int)CySignals.STOP].Value = m_prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.CAPTURE].Value = m_prms.CapturePresent;
            dgvAdvanced[1, (int)CySignals.COUNT].Value = m_prms.CountPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.RELOAD], m_prms.ReloadMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.START], m_prms.StartMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], m_prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.CAPTURE], m_prms.CaptureMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.COUNT], m_prms.CountMode);

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
        }

        private void UpdateVisibility()
        {
            if (m_prms == null) return;
            registerGrid.UpdateVisibility();
            m_prms.DisableRow(dgvAdvanced.Rows[(int)CySignals.CAPTURE], m_prms.CompCapMode == CyCompCapMode.Compare);
        }

        private void UpdateCounterGraph()
        {
            m_counterGraph.m_counterMode = m_prms.CountingModes;
            m_counterGraph.m_period = m_prms.Period1;
            m_counterGraph.m_compare1 = m_prms.Compare1;
            m_counterGraph.m_compare2 = m_prms.Compare2;
            m_counterGraph.m_swapCompare = m_prms.CompareSwap == CySwapEnable.SWAP_ENABLE;
            m_counterGraph.m_cmpCapMode = m_prms.CompCapMode;
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
                    case CySignals.CAPTURE:
                        m_prms.CapturePresent = selValue;
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
                    case CySignals.CAPTURE:
                        m_prms.CaptureMode = selValue;
                        break;
                    case CySignals.COUNT:
                        m_prms.CountMode = selValue;
                        break;
                    default:
                        break;
                }
            }
        }

        void registerGrid_DataChanged(object sender, EventArgs e)
        {
            UpdateCounterGraph();
        }
        #endregion Event handlers
    }
}

