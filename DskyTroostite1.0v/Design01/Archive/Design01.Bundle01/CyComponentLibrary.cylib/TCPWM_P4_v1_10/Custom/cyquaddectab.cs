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
    public partial class CyQuadDecTab : CyEditingWrapperControl
    {
        enum CySignals  
        {
            [Description("stop")]
            STOP,
            [Description("index")]
            INDEX,
            [Description("phiA")]
            PHIA,
            [Description("phiB")]
            PHIB
        };

        public override string TabName
        {
            get { return "QuadDec"; }
        }

        public CyQuadDecTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();

            m_prms.m_quaddecTab = this;

            CyParameters.FillComboFromEnum(m_cbEncodingMode, typeof(CyQuadMode));
            InitAdvTable();

            m_cbEncodingMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                m_prms.QuadEncodingModes = CyParameters.GetEnum<CyQuadMode>((sender as Control).Text);
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

        private void InitAdvTable()
        {
            DataGridViewCellStyle readOnlyCellStyle = new DataGridViewCellStyle();
            readOnlyCellStyle.BackColor = SystemColors.Control;
            readOnlyCellStyle.SelectionBackColor = SystemColors.Control;
            
            ColumnMode.Items.AddRange(CyParameters.GetDescriptionList(typeof(CyTriggerMode)));

            string[] signals = CyParameters.GetDescriptionList(typeof(CySignals));
            for (int i = 0; i < signals.Length; i++)
            {
                dgvAdvanced.Rows.Add(signals[i], false, ColumnMode.Items[0]);
            }
            dgvAdvanced[1, (int)CySignals.PHIA].ReadOnly = true;
            dgvAdvanced[1, (int)CySignals.PHIB].ReadOnly = true;
            dgvAdvanced[1, (int)CySignals.PHIA].Style = readOnlyCellStyle;
            dgvAdvanced[1, (int)CySignals.PHIB].Style = readOnlyCellStyle;
            dgvAdvanced[1, (int)CySignals.PHIA].Value = true;
            dgvAdvanced[1, (int)CySignals.PHIB].Value = true;
        }

        public void UpdateFormFromParams()
        {
            CyParameters.SetComboValue(m_cbEncodingMode, m_prms.QuadEncodingModes);

            bool both = m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (m_prms.InterruptMask == CyInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.STOP].Value = m_prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.INDEX].Value = m_prms.IndexPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], m_prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.INDEX], m_prms.IndexMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.PHIA], m_prms.PhiAMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.PHIB], m_prms.PhiBMode);
        }

        void dgvAdvanced_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == ColumnPresent.Index)
            {
                bool selValue = (bool)((DataGridViewCheckBoxCell)dgvAdvanced[e.ColumnIndex, e.RowIndex]).Value;
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.STOP:
                        m_prms.StopPresent = selValue;
                        break;
                    case CySignals.INDEX:
                        m_prms.IndexPresent = selValue;
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
                    case CySignals.STOP:
                        m_prms.StopMode = selValue;
                        break;
                    case CySignals.INDEX:
                        m_prms.IndexMode = selValue;
                        break;
                    case CySignals.PHIA:
                        m_prms.PhiAMode = selValue;
                        break;
                    case CySignals.PHIB:
                        m_prms.PhiBMode = selValue;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
