/*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Diagnostics;
using System.Text.RegularExpressions;
using CyDesigner.Extensions.Gde;

namespace CyCustomizer.CyControlReg_v1_60
{
    public partial class CyBitfieldControl : UserControl
    {
        public const int MIN_OUTPUTS = 0;
        public const int MAX_OUTPUTS = 8;
        public const int OUTPUT_ROWS_START = 0;
        public const int FIRST_COLUMN_INDEX = 1;
        public const int SECOND_COLUMN_INDEX = 2;
        public const int THIRD_COLUMN_INDEX = 2;
        public const int NUMOUTPUT_MAX = 8;

        public const int OUTPUT_ROWS_END = OUTPUT_ROWS_START + MAX_OUTPUTS - 1;
        public const int DEFAULT_BITMODE = 0;
        public const int DEFAULT_INDEX = 0;
        public const int DEFAULT_OUTPUT = 0;
        public const int MAX_BITVAL = 2;
        public const int FIRST_ROW_INDEX = 0;
        public const int SECOND_ROW_INDEX = 1;
        public const int THIRD_ROW_INDEX = 2;
        public const int FORTH_ROW_INDEX = 3;
        public const int FIFTH_ROW_INDEX = 4;
        public const int SIXTH_ROW_INDEX = 5;
        public const int SEVENTH_ROW_INDEX = 6;
        public const int EIGHTH_ROW_INDEX = 7;
        public const int DEFAULT_BITVALUE = 0;
       

        public ICyInstEdit_v1 m_Component = null;
        public const string DIRECTMODE = "DirectMode";
        public const string SYNCMODE = "SyncMode";
        public const string PULSEMODE = "PulseMode";
        public const string BITVALUE = "BitValue";
        public const string BIT = "Bit";
        public const string MODE = "Mode";

        public CyBitfieldControl(ICyInstEdit_v1 inst)
        {
            int val;
            m_Component = inst;
            InitializeComponent();
            m_dgvBitFieldConfigure.RowHeadersVisible = false;
            m_dgvBitFieldConfigure.AllowUserToAddRows = false;
            m_dgvBitFieldConfigure.AllowUserToOrderColumns = false;
            m_dgvBitFieldConfigure.AllowUserToResizeColumns = false;
            m_dgvBitFieldConfigure.AllowUserToResizeRows = false;

            // Set the max and minimum values of output
            m_nudInputs.Minimum = 1;
            m_nudInputs.Maximum = MAX_OUTPUTS;

            // Configures columns of DataGridView control
            SetupColumns(inst);                    

            m_dgvBitFieldConfigure.EditMode = DataGridViewEditMode.EditOnEnter;

            // Populate the combo box drop-down list with Bitmode Name, combo box buttons with bit value         
            string[] modeName = { DIRECTMODE, SYNCMODE, PULSEMODE, PULSEMODE };
            val = Convert.ToInt16(m_Component.GetCommittedParam(BITVALUE).Value.ToString());
            for (int i = OUTPUT_ROWS_START; i < MAX_OUTPUTS; i++)
            {
                Object[] rowobs = new object[3];
                rowobs[OUTPUT_ROWS_START + FIRST_ROW_INDEX] = "       " + i.ToString();
                try
                {
                    rowobs[OUTPUT_ROWS_START + SECOND_ROW_INDEX] = modeName[(int)(Convert.ToInt16(m_Component.GetCommittedParam(BIT + i.ToString() + MODE).Value))];
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }

                rowobs[OUTPUT_ROWS_START + THIRD_ROW_INDEX] = ((int)val & 0x01);
                val = val >> 1;
                m_dgvBitFieldConfigure.Rows.Add(rowobs);
            }
            UpdateFormFromParams(inst);
        }

        void SetupColumns(ICyInstEdit_v1 inst)
        {
            // Configures first and second column of DataGridView control
            // Add a TextBox column
            DataGridViewTextBoxColumn hexColumn = new DataGridViewTextBoxColumn();
            hexColumn.HeaderText = String.Format(Resources.BIT_NAME);
            hexColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            hexColumn.ReadOnly = true;
            hexColumn.CellTemplate = new DataGridViewTextBoxCell();
            hexColumn.CellTemplate.Style.BackColor = Color.LightGray;
            m_dgvBitFieldConfigure.Columns.Add(hexColumn);

            // Add a comboBox column
            DataGridViewComboBoxColumn outputColumn = new DataGridViewComboBoxColumn();
            
            // Set the BitMode from Enums
            IEnumerable<string> Bit0ModeEnums = inst.GetPossibleEnumValues(CyControlReg_v1_60.ControlRegParameters.BIT0MODE);
            foreach (string str in Bit0ModeEnums)
            {
                outputColumn.Items.Add(str);
            }
            outputColumn.HeaderText = String.Format(Resources.MODE_NAME);
            m_dgvBitFieldConfigure.Columns.Add(outputColumn);

            // Configures third column of DataGridView control
            DataGridViewButtonColumn outputColumn1 = new DataGridViewButtonColumn();
            outputColumn1.HeaderText = String.Format(BITVALUE);
            outputColumn1.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            outputColumn1.FlatStyle = FlatStyle.Flat;
            m_dgvBitFieldConfigure.Columns.Add(outputColumn1);
            m_dgvBitFieldConfigure.Rows.Clear();
        }

        // Set Row visibility for displaying the Rows
        private void SetRowsVisible(UInt16 startRowIndex, UInt16 endRowIndex)
        {
            for (int index = startRowIndex; index <= endRowIndex; index++)
            {
                m_dgvBitFieldConfigure.Rows[index].Visible = true;
            }
        }

        // Hide the Rows
        private void SetRowsInVisible(UInt16 startRowIndex, UInt16 endRowIndex)
        {
            for (int index = startRowIndex; index <= endRowIndex; index++)
            {
                m_dgvBitFieldConfigure.Rows[index].Visible = false;
            }
        }

        private void SetColumnsVisibility(ICyInstEdit_v1 inst)
        {
            int result = 1;

            if (!Int32.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS).Value, out result))
            {
                //Minimum number of output
                result = 1;
            }
            result = ValidateNumOutputsLimit(result);

            SetRowsVisible(FIRST_ROW_INDEX, (ushort) (result - 1));
			if (result <= EIGHTH_ROW_INDEX)
			{
                SetRowsInVisible((ushort)(result), (ushort) EIGHTH_ROW_INDEX);
			}

            m_dgvBitFieldConfigure.Height = ((UInt16) m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height) * (result + 1);
            groupBox1.Height = ((UInt16) m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height) * (result + 2);

            // Populate the combo box drop-down list with Bitmode Name, combo box buttons with bit value         
            string[] modeName = { DIRECTMODE, SYNCMODE, PULSEMODE, PULSEMODE };

            for (int i = OUTPUT_ROWS_START; i < result; i++)
            {
                short bitValue = 0;
                Int16.TryParse( m_Component.GetCommittedParam(BIT + i.ToString() + MODE).Value, out bitValue);      
                m_dgvBitFieldConfigure.Rows[i].Cells[OUTPUT_ROWS_START + SECOND_ROW_INDEX].Value = modeName[bitValue];
            }
        } // END OF SetColumnsVisibility


        private void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            int outputs = 01;
            bool resetValue = false;
            bool extResetValue = false;

            if (!Int32.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS).Value, out outputs))
            {
                //Minimum number of output
                outputs = 1;
            }

            //limit the numberoutput paramter , wrong value may come from older version of Control register.
            outputs = ValidateNumOutputsLimit(outputs);

            // Set value for Output
            m_nudInputs.Value = outputs;

            // External reset check box
            bool.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.EXTERNALRESET).Value, out extResetValue);
            m_reset.Checked = extResetValue;

            SetColumnsVisibility(inst);

            Boolean.TryParse(m_Component.GetCommittedParam("ResetCheck").Value, out resetValue);
            m_reset.Enabled = !resetValue;
        }

        private void ClearAllButtonValues()
        {
            // Set all BitMode value to DIRECTMODE
            for (int j = OUTPUT_ROWS_END; j >= OUTPUT_ROWS_START; j--)
            {
                m_dgvBitFieldConfigure.Rows[j].Cells[FIRST_COLUMN_INDEX].Value = DIRECTMODE;
                m_Component.SetParamExpr(BIT + (7 - j) + MODE, DIRECTMODE);
                m_Component.CommitParamExprs();
            }      
		    
            // Validating External reset parameter
            ValidatingExternalReset();
		}              
        
        private void SaveParameters()
        {
            // Saves the NUMOUTPUTS and EXTERNALRESET
            m_Component.SetParamExpr(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS, m_nudInputs.Value.ToString());
            m_Component.CommitParamExprs();

            SetColumnsVisibility(m_Component);
        }

        // Saves the OUTPUT value assigned to the control
        private void m_nudInputs_ValueChanged(object sender, EventArgs e)
        {
            int bitval = DEFAULT_BITVALUE;
            int val = 0;
            int paramoutputs = DEFAULT_OUTPUT;

            try
            {
                paramoutputs = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS).Value);
            }
            catch (Exception) { }

            //limit the numberoutput paramter 
            paramoutputs = ValidateNumOutputsLimit(paramoutputs);

            if (paramoutputs != m_nudInputs.Value)
            {
                SaveParameters();
            }
            ValidatingExternalReset();

            // Gets and saves the BitValue
            for (int col = MIN_OUTPUTS; col < paramoutputs; col++)
            {
                val = Convert.ToInt16(((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Value);
                val = val << col;
                bitval = bitval | val;
            }
            m_Component.SetParamExpr(BITVALUE, bitval.ToString());
            m_Component.CommitParamExprs();
        }

        public void UpdateFormFromInst(ICyInstEdit_v1 inst)
        {
            UpdateFormFromParams(inst);
        }

        private void m_bClearAll_Click_1(object sender, EventArgs e)
        {
            // Set all BitMode param to DIRECTMODE
            ClearAllButtonValues();	
        }

        // Save OUTPUT value on Key release
        // Handles keyboard events
        private void m_nudInputs_KeyUp(object sender, KeyEventArgs e)
        {
            int bitval = DEFAULT_BITVALUE;
            int val = 0;
            int paramoutputs = DEFAULT_OUTPUT;

            try
            {
                paramoutputs = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS).Value);
            }
            catch (Exception) { }

            //limit the numberoutput paramter 
            paramoutputs = ValidateNumOutputsLimit(paramoutputs);
            if (paramoutputs != m_nudInputs.Value)
            {
                SaveParameters();
            }
            
            ValidatingExternalReset();

            // Gets and saves the BitValue
            for (int col = MIN_OUTPUTS; col < paramoutputs; col++)
            {
                val = Convert.ToInt16(((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Value);
                val = val << col;
                bitval = bitval | val;
            }
            m_Component.SetParamExpr(BITVALUE, bitval.ToString());
            m_Component.CommitParamExprs();
        }

        private int ValidateNumOutputsLimit(int paramoutputs)
        {
            int returnValue = paramoutputs >= NUMOUTPUT_MAX ? NUMOUTPUT_MAX : paramoutputs;
            return returnValue;
        }

        // Check for the ExternalReset validity
        private void ValidatingExternalReset()
        {
            bool resetValue = false;
            Boolean.TryParse(m_Component.GetCommittedParam("ResetCheck").Value, out resetValue);
            m_reset.Enabled = !resetValue;
        }

        private void m_reset_Validating(object sender, CancelEventArgs e)
        {
            // Validates the external reset parameter
            ValidatingExternalReset();
        }

        private void m_reset_CheckedChanged(object sender, EventArgs e)
        {
            // save the changes to the symbol parameter
            if (m_reset.Checked == true)
            {
                m_Component.SetParamExpr(CyControlReg_v1_60.ControlRegParameters.EXTERNALRESET, Resources.TRUE);
            }
            else
            {
                m_Component.SetParamExpr(CyControlReg_v1_60.ControlRegParameters.EXTERNALRESET, Resources.FALSE);
            }
            m_Component.CommitParamExprs();
        }

        private void m_dgvBitFieldConfigure_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            int bitval = DEFAULT_BITVALUE;
            int val = 0;
            int outputs = DEFAULT_OUTPUT;

            if (e.RowIndex != -1)
            {
                // Updates the BitValue for a specified row
                if ((e.ColumnIndex == SECOND_COLUMN_INDEX) && (e.RowIndex >= OUTPUT_ROWS_START))
                {
                    if (((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value.ToString() == Resources.BITVALUE_ONE)
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = Resources.BITVALUE_ZERO;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                    }
                    else
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = Resources.BITVALUE_ONE;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                    }

                    // Gets and saves the BitValue
                    if (!Int32.TryParse(m_Component.GetCommittedParam(CyControlReg_v1_60.ControlRegParameters.NUMOUTPUTS).Value, out outputs))
                    {
                        //Minimum number of output
                        outputs = 1;
                    }
                    for (int col = MIN_OUTPUTS; col < outputs; col++)
                    {
                        val = Convert.ToInt16(((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Value);
                        val = val << col;
                        bitval = bitval | val;
                    }

                    m_Component.SetParamExpr(BITVALUE, bitval.ToString());
                    m_Component.CommitParamExprs();
                }
            }
        }

        // Set all BitValue to Zero
        private void ClearBitValue_Click(object sender, EventArgs e)
        {
            int bitval = DEFAULT_BITVALUE;
            for (int j = OUTPUT_ROWS_END; j >= OUTPUT_ROWS_START; j--)
            {
                m_dgvBitFieldConfigure.Rows[j].Cells[THIRD_COLUMN_INDEX].Value = DEFAULT_BITVALUE;
                m_Component.SetParamExpr(BITVALUE, bitval.ToString());
                m_Component.CommitParamExprs();
            }
        }
        
        private void m_dgvBitFieldConfigure_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            ComboBox cb = e.Control as ComboBox;            
            if (cb != null)
            {
                // first remove event handler to keep from attaching multiple: 
                cb.SelectedIndexChanged -= new EventHandler(cb_SelectedIndexChanged);

                // now attach the event handler 
                cb.SelectedIndexChanged += new EventHandler(cb_SelectedIndexChanged);
            }
        }

        // Validate BitxMode and Provide ERROR if set to DIRECTMODE when ExternalReset is checked
        void cb_Validating(object sender, CancelEventArgs e)
        {
            ValidatingExternalReset();
        }

        // Handling BitxMode selection
        void cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int currentIndex = DEFAULT_INDEX;
            cb.Validating -= new CancelEventHandler(cb_Validating);
            {
                if (m_dgvBitFieldConfigure[FIRST_COLUMN_INDEX, m_dgvBitFieldConfigure.CurrentRow.Index].Selected == true)
                {
                    if (cb != null)
                    {
                        IEnumerable<string> Bit0ModeEnums = m_Component.GetPossibleEnumValues(CyControlReg_v1_60.ControlRegParameters.BIT0MODE);
                      
                        foreach (string str in Bit0ModeEnums)
                        {
                            // Save the current BitxMode selection
                            if (cb.SelectedIndex == currentIndex)
                            {
                                m_Component.SetParamExpr(BIT + (m_dgvBitFieldConfigure.CurrentRow.Index) + MODE, str);
                                m_Component.CommitParamExprs();

                                break;
                            }
                            currentIndex++;
                        }
                        ValidatingExternalReset();
                    }
                }
            }
        }

        
    }
}


