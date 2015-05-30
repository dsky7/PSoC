/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Diagnostics;

namespace TrimMargin_v1_20
{
    public partial class CyHardwareTab : CyEditingWrapperControl
    {
        private int m_dataGridRowCount;
        private List<int> m_editableCols;
        private byte m_previousPWMResolution;

        #region Class properties
        public override string TabName
        {
            get { return CyCustomizer.HARDWARE_TAB_NAME; }
        }

        public int DataGridRowCount
        {
            get { return m_dataGridRowCount; }
            set
            {
                m_dataGridRowCount = value;
                dgvHardware.RowCount = m_dataGridRowCount;
            }
        }

        public int DataGridFirstSelectedRow
        {
            get { return GetLessSelectedRow(dgvHardware.SelectedRows); }
        }
        #endregion

        #region Constructor(s)
        public CyHardwareTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params.m_hardwareTab = this;

            InitializeComponent();

            // Initialize toolstrip
            cyToolStrip1.SetParameters(param);
            cyToolStrip1.m_dgv = dgvHardware;

            // Initialize wrapper objects
            m_wrapperToolStrip = cyToolStrip1;
            m_wrapperDataGridView = dgvHardware;

            // Initialize data grid view
            CyParameters.InitializeDataGrid(dgvHardware);

            pictureBox1.Image = Resources.trim_margin;

            m_editableCols = new List<int>(new int[]
            {
                colPolarity.Index,
                colVddio.Index,
                colControlVoltage.Index,
                colR1.Index,
                colR2.Index,
                colR3.Index,
                colR4.Index,
                colMaxRipple.Index,
                colC1.Index
            });

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            numPWMResolution.TextChanged += new EventHandler(numPWMResolution_TextChanged);
            numPWMResolution.Minimum = 0;
            numPWMResolution.Maximum = decimal.MaxValue;

            CyParameters.HardwareHeader_v2_0 = CyParameters.GetColNames(dgvHardware);

            UpdateUI();
            // Fill data grid view
            UpdateUIFromTable();
        }
        #endregion

        #region dgvVoltages events
        void numPWMResolution_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentControl = (NumericUpDown)sender;
            byte value = 0;
            try
            {
                value = byte.Parse(currentControl.Text);

                if (value < CyParamRanges.PWM_RESOLUTION_MIN || value > CyParamRanges.PWM_RESOLUTION_MAX)
                    throw new Exception();
                m_errorProvider.SetError(currentControl, string.Empty);
            }
            catch (Exception)
            {
                m_errorProvider.SetError(currentControl, string.Format(Resources.NumPWMResolutionError,
                    CyParamRanges.PWM_RESOLUTION_MIN, CyParamRanges.PWM_RESOLUTION_MAX));
            }
            m_params.PWMResolution = value;

            // Do not allow to change table if not edit mode
            if (m_params.GlobalEditMode == false) return;

            if (string.IsNullOrEmpty(m_errorProvider.GetError(currentControl)))
            {
                if (m_previousPWMResolution >= CyParamRanges.PWM_RESOLUTION_MIN &&
                        m_previousPWMResolution <= CyParamRanges.PWM_RESOLUTION_MAX)
                {
                    if (value > m_previousPWMResolution)
                    {
                        if (m_params.m_hardwareTab != null)
                            m_params.m_hardwareTab.UpdateUIFromTable();
                    }
                }
            }
            m_previousPWMResolution = value;
            // Validate number of converters
            m_params.m_voltagesTab.UpdateNumConvertersControl();
        }

        private void dgvHardware_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_editableCols.Contains(e.ColumnIndex))
                {
                    UpdateTableFromUI();

                    // Update calculated values if something was changed
                    m_params.CalculateTableValues(e.RowIndex);
                    UpdateUIFromTable(e.RowIndex);

                    m_params.SetHardwareTable();

                    ValidateRow(e.RowIndex);
                }

                if (e.ColumnIndex == colControlVoltage.Index || e.ColumnIndex == colR1.Index ||
                    e.ColumnIndex == colR2.Index || e.ColumnIndex == colR3.Index || e.ColumnIndex == colR4.Index ||
                    e.ColumnIndex == colC1.Index)
                {
                    m_params.m_voltagesTab.UpdateCalculatedValues(e.RowIndex);
                }
            }
        }

        private void dgvHardware_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(dgvHardware);
        }

        private void dgvHardware_SelectionChanged(object sender, EventArgs e)
        {
            cyToolStrip1.ChangeCopyPasteEnabling(dgvHardware.SelectedRows.Count > 0);
        }
        #endregion dgvVoltages events

        #region Validation
        public bool ValidateAllTable()
        {
            bool prev_edit_mode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;
            bool isOk = true;

            for (int i = 0; i < m_params.NumConverters; i++)
            {
                isOk &= ValidateRow(i);
            }
            m_params.GlobalEditMode = prev_edit_mode;
            return isOk;
        }

        private bool ValidateRow(int rowIndex)
        {
            bool isOk = true;

            // Range check
            foreach (int index in m_editableCols)
            {
                isOk &= RangeCheck(rowIndex, index);
            }
            return isOk;
        }

        private bool RangeCheck(int rowIndex, int colIndex)
        {
            double min = CyParamRanges.VOLTAGE_MIN;
            double max = CyParamRanges.VOLTAGE_MAX;
            string message = string.Empty;
            double? currCellValue = null;

            if (colIndex == colVddio.Index)
            {
                min = CyParamRanges.VDDIO_MIN;
                max = CyParamRanges.VDDIO_MAX;
                message = Resources.VDDIOVoltageError;
                currCellValue = m_params.HardwareTable[rowIndex].m_vddio;
            }
            else if (colIndex == colControlVoltage.Index)
            {
                min = CyParamRanges.CONTROL_VOLTAGE_MIN;
                max = CyParamRanges.CONTROL_VOLTAGE_MAX;
                message = Resources.ControlVoltageError;
                currCellValue = m_params.HardwareTable[rowIndex].m_controlVoltage;
            }
            else if (colIndex == colR1.Index)
            {
                min = CyParamRanges.RESISTOR_MIN;
                max = CyParamRanges.RESISTOR_MAX;
                message = Resources.R1ResistorError;
                currCellValue = m_params.HardwareTable[rowIndex].m_r1;
            }
            else if (colIndex == colR2.Index)
            {
                min = CyParamRanges.RESISTOR_MIN;
                max = CyParamRanges.RESISTOR_MAX;
                message = Resources.R2ResistorError;
                currCellValue = m_params.HardwareTable[rowIndex].m_r2;
            }
            else if (colIndex == colR3.Index)
            {
                min = CyParamRanges.RESISTOR_MIN;
                max = CyParamRanges.RESISTOR_MAX;
                message = Resources.R3ResistorError;
                currCellValue = m_params.HardwareTable[rowIndex].m_r3;
            }
            else if (colIndex == colMaxRipple.Index)
            {
                min = CyParamRanges.MAX_RIPPLE_MIN;
                max = CyParamRanges.MAX_RIPPLE_MAX;
                message = Resources.MaxRippleError;
                currCellValue = m_params.HardwareTable[rowIndex].m_maxRipple;
            }
            else if (colIndex == colR4.Index)
            {
                min = CyParamRanges.RESISTOR_MIN;
                max = CyParamRanges.RESISTOR_MAX;
                message = Resources.R4ResistorError;
                currCellValue = m_params.HardwareTable[rowIndex].m_r4;
            }
            // C1 column is not checked

            if (m_editableCols.Contains(colIndex) && dgvHardware.Columns[colIndex].ReadOnly == false)
            {
                message = CyParameters.IsValueInRange(currCellValue, dgvHardware[colIndex, rowIndex].Value, min, max,
                    message);
            }
            else
            {
                message = string.Empty;
            }
            dgvHardware[colIndex, rowIndex].ErrorText = message;

            return String.IsNullOrEmpty(message);
        }

        public bool CheckTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < m_params.NumConverters; i++)
            {
                if ((m_params.VoltagesTable[i].m_nominalVoltage == null) ||
                    (m_params.VoltagesTable[i].m_minVoltage == null) ||
                    (m_params.VoltagesTable[i].m_maxVoltage == null) ||
                    (m_params.VoltagesTable[i].MarginLow == null) ||
                    (m_params.VoltagesTable[i].MarginHigh == null))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }
        #endregion Validation

        public void UpdateClockDependedValues(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            if (m_params == null) return;

            UpdateUIFromTable();
        }

        public void UpdateUI()
        {
            numPWMResolution.Value = m_params.PWMResolution;
            m_previousPWMResolution = m_params.PWMResolution;
        }

        public void UpdateUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            bool dgSizeNeedsUpdate = false;
            m_dataGridRowCount = m_params.NumConverters;

            if (dgvHardware.Rows.Count != m_params.NumConverters)
                dgSizeNeedsUpdate = true;
            
            dgvHardware.Rows.Clear();
            dgvHardware.Rows.Add(m_dataGridRowCount);
           
            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                UpdateUIFromTable(i);
            }

            if (dgSizeNeedsUpdate)
                CyParameters.UpdateDGVHeight(dgvHardware);

            panelGraph.Top = dgvHardware.Top + dgvHardware.Height + 5;

            UpdatePWMFrequency();

            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateUIFromTable(int index)
        {
            m_params.CalculateTableValues(index);

            dgvHardware[colConverterOutput.Index, index].Value = CyVoltagesTableRow.GetVoltageIndexStr(index + 1);
            dgvHardware[colConverterName.Index, index].Value = m_params.VoltagesTable[index].m_converterName;
            dgvHardware[colNominalVoltage.Index, index].Value = m_params.VoltagesTable[index].m_nominalVoltage;
            dgvHardware[colPolarity.Index, index].Value = CyEnumConverter.GetEnumDesc(
                m_params.HardwareTable[index].m_polarity);
            dgvHardware[colVddio.Index, index].Value = m_params.HardwareTable[index].m_vddio;
            dgvHardware[colControlVoltage.Index, index].Value = m_params.HardwareTable[index].m_controlVoltage;
            dgvHardware[colR1.Index, index].Value = m_params.HardwareTable[index].m_r1;
            dgvHardware[colR2.Index, index].Value = m_params.HardwareTable[index].m_r2;
            dgvHardware[colCalcR2.Index, index].Value = m_params.HardwareTable[index].m_calcR2;
            dgvHardware[colCalcR3.Index, index].Value = m_params.HardwareTable[index].m_calcR3;
            dgvHardware[colR3.Index, index].Value = m_params.HardwareTable[index].m_r3;
            dgvHardware[colCalcR4.Index, index].Value = m_params.HardwareTable[index].m_calcR4;
            dgvHardware[colR4.Index, index].Value = m_params.HardwareTable[index].m_r4;
            dgvHardware[colMaxRipple.Index, index].Value = m_params.HardwareTable[index].m_maxRipple;
            dgvHardware[colCalcVRipple.Index, index].Value = m_params.HardwareTable[index].m_calcVRipple;
            dgvHardware[colCalcC1.Index, index].Value = m_params.HardwareTable[index].m_calcC1;
            dgvHardware[colC1.Index, index].Value = m_params.HardwareTable[index].m_c1;
            dgvHardware[colNomPWM.Index, index].Value = m_params.HardwareTable[index].m_nominalPWM;
            dgvHardware[colResolution.Index, index].Value = m_params.HardwareTable[index].m_calcResolution;
        }


        public void UpdateTableFromUI()
        {
            for (int i = 0; i < m_dataGridRowCount; i++)
            {
                m_params.HardwareTable[i].m_polarity = (CyPWMPolarityType)CyEnumConverter.GetEnumValue(
                            dgvHardware.Rows[i].Cells[colPolarity.Name].Value, typeof(CyPWMPolarityType));

                m_params.HardwareTable[i].m_vddio = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colVddio.Name].Value));

                m_params.HardwareTable[i].m_controlVoltage = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colControlVoltage.Name].Value));

                m_params.HardwareTable[i].m_r1 = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colR1.Name].Value));

                m_params.HardwareTable[i].m_r2 = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colR2.Name].Value));

                m_params.HardwareTable[i].m_r3 = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colR3.Name].Value));

                m_params.HardwareTable[i].m_maxRipple = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colMaxRipple.Name].Value));

                m_params.HardwareTable[i].m_c1 = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colC1.Name].Value));

               m_params.HardwareTable[i].m_r4 = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colR4.Name].Value));

                m_params.HardwareTable[i].m_calcResolution = CyParameters.ParseNullableDouble(
                            CyParameters.CellToString(dgvHardware.Rows[i].Cells[colResolution.Name].Value));
            }
        }

        public void SelectDataGridViewRows(int fromRow, int toRow)
        {
            SelectRows(dgvHardware, fromRow, toRow);
        }

        /// <summary>
        /// Updates label "PWM frequency"
        /// </summary>
        private void UpdatePWMFrequency()
        {
            double? pwmFrequency = m_params.GetPWMFrequency();
            if (pwmFrequency.HasValue)
            {
                labelPWMFreqValue.Text = (pwmFrequency.Value / 1000).ToString("f3") + " kHz";
            }
            else
            {
                labelPWMFreqValue.Text = "Unknown";
            }
        }
    }
}
