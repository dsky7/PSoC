/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace CyCustomizer.CyControlReg_v1_50
{
    public partial class CyBitfieldControl : UserControl
    {
        public const int MIN_OUTPUTS = 1;
        public const int MAX_OUTPUTS = 8;
        public const int OUTPUT_ROWS_START = 0;
        public const int FIRST_COLUMN_INDEX = 1;
        public const int SECOND_COLUMN_INDEX = 2;

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
        public const int THIRD_COLUMN_INDEX = 2;        

        public ICyInstEdit_v1 m_Component = null;
        public const string DIRECTMODE = "DirectMode";
        public const string SYNCMODE = "SyncMode";
        public const string PULSEMODE = "PulseMode";
        public const string BITVALUE = "BitValue";
        public const string BIT = "Bit";
        public const string MODE = "Mode";
        public const string directMode = "0";
        const string TRUE = "true";
        const string FALSE = "false";
        public const string BITVALUE_ONE = "1";
        public const string BITVALUE_ZERO = "0";
        public const string BIT_NAME = "    Bit ";
        public const string MODE_NAME = "     Mode ";


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

            // Configures first and second column of DataGridView control
            SetupColumns(inst);                    

            // Configures third column of DataGridView control
            DataGridViewButtonColumn outputColumn1 = new DataGridViewButtonColumn();
            outputColumn1.HeaderText = String.Format(BITVALUE);
            outputColumn1.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            outputColumn1.FlatStyle = FlatStyle.Flat;
            m_dgvBitFieldConfigure.Columns.Add(outputColumn1);
            m_dgvBitFieldConfigure.Rows.Clear();

            // Populate the combo box drop-down list with Bitmode Name, combo box buttons with bit value         
            string[] modeName = { DIRECTMODE, SYNCMODE, PULSEMODE, PULSEMODE };
            val = Convert.ToInt16(m_Component.GetCommittedParam(BITVALUE).Value.ToString());
            for (int i = OUTPUT_ROWS_START; i < MAX_OUTPUTS; i++)
            {
                Object[] rowobs = new object[3];
                rowobs[OUTPUT_ROWS_START + FIRST_ROW_INDEX] = BIT + i.ToString() + MODE;
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
            // Add a TextBox column
            DataGridViewTextBoxColumn hexColumn = new DataGridViewTextBoxColumn();
            hexColumn.HeaderText = String.Format(BIT_NAME);
            hexColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            hexColumn.ReadOnly = true;
            hexColumn.CellTemplate = new DataGridViewTextBoxCell();
            hexColumn.CellTemplate.Style.BackColor = Color.LightGray;
            m_dgvBitFieldConfigure.Columns.Add(hexColumn);

            // Add a comboBox column
            DataGridViewComboBoxColumn outputColumn = new DataGridViewComboBoxColumn();
            
            // Set the BitMode from Enums
            IEnumerable<string> Bit0ModeEnums = inst.GetPossibleEnumValues(CyControlReg_v1_50.ControlRegParameters.BIT0MODE);
            foreach (string str in Bit0ModeEnums)
            {
                outputColumn.Items.Add(str);
            }
            outputColumn.HeaderText = String.Format(MODE_NAME);
            m_dgvBitFieldConfigure.Columns.Add(outputColumn);
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
            int result = DEFAULT_OUTPUT;

            try
            {
                result = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }

            switch (result)
            {
                case 1:
                    SetRowsVisible(FIRST_ROW_INDEX, FIRST_ROW_INDEX);
                    SetRowsInVisible(SECOND_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);

                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 2:
                    SetRowsVisible(FIRST_ROW_INDEX, SECOND_ROW_INDEX);
                    SetRowsInVisible(THIRD_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);

                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 3:
                    SetRowsVisible(FIRST_ROW_INDEX, THIRD_ROW_INDEX);
                    SetRowsInVisible(FORTH_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 4:
                    SetRowsVisible(FIRST_ROW_INDEX, FORTH_ROW_INDEX);
                    SetRowsInVisible(FIFTH_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 5:
                    SetRowsVisible(FIRST_ROW_INDEX, FIFTH_ROW_INDEX);
                    SetRowsInVisible(SIXTH_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 6:
                    SetRowsVisible(FIRST_ROW_INDEX, SIXTH_ROW_INDEX);
                    SetRowsInVisible(SEVENTH_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 7:
                    SetRowsVisible(FIRST_ROW_INDEX, SEVENTH_ROW_INDEX);
                    SetRowsInVisible(EIGHTH_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
                case 8:
                    SetRowsVisible(FIRST_ROW_INDEX, EIGHTH_ROW_INDEX);
                    try
                    {
                        m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[OUTPUT_ROWS_START + FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 1);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.ToString());
                    }
                    groupBox1.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[FIRST_ROW_INDEX].Height.ToString()) * (Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value) + 2);
                    break;
            } // END OF switch (result)
        } // END OF SetColumnsVisibility


        private void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            int bitval = DEFAULT_BITVALUE;
            int val = 0;            
            int outputs = 0;
            
            try
            {
                outputs = Convert.ToInt16(m_Component.GetCommittedParam("NumOutputs").Value);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }   
            // Set value for Output
            m_nudInputs.Value = outputs;

            // External reset check box
            string paramcompare = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.EXTERNALRESET).Value;
            if (paramcompare.Contains(TRUE))
            {
                m_reset.Checked = true;
            }
            else
            {
                m_reset.Checked = false;
            }
            
            SetColumnsVisibility(inst);
            // Set BitValue
            val = Convert.ToInt16(m_Component.GetCommittedParam(BITVALUE).Value);
            for (int col = MAX_OUTPUTS - 1; col >= DEFAULT_OUTPUT; col--)
            {
                
                if ((m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Visible == true)
                {
                    bitval = val & 0x01;
                    val = val >> 1;
                }                
            }           
        }       

        
        private void ClearAllButtonValues()
        {
            // Set all BitMode value to DIRECTMODE
            for (int j = OUTPUT_ROWS_END; j >= OUTPUT_ROWS_START; j--)
            {
                m_dgvBitFieldConfigure.Rows[j].Cells[FIRST_COLUMN_INDEX].Value = DIRECTMODE;
                m_Component.SetParamExpr(BIT + (7 - j) + MODE, DIRECTMODE);
                m_Component.CommitParamExprs();
                ValidatingExternalReset();
            }           
        }              
        
        private void SaveParameters()
        {
            // Saves the NUMOUTPUTS and EXTERNALRESET
            m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS, m_nudInputs.Value.ToString());
            // commit the changes
            m_Component.CommitParamExprs();
            SetColumnsVisibility(m_Component);
        }

        // Saves the OUTPUT value assigned to the control
        private void m_nudInputs_ValueChanged(object sender, EventArgs e)
        {
            int paramoutputs = DEFAULT_OUTPUT;
            try
            {
                paramoutputs = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value);
            }
            catch (Exception) { }

            if (paramoutputs != m_nudInputs.Value)
            {
                SaveParameters();
            }
            UpdateFormFromParams(m_Component);
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
            int paramoutputs = DEFAULT_OUTPUT;
            try
            {
                paramoutputs = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value);
            }
            catch (Exception) { }

            if (paramoutputs != m_nudInputs.Value)
            {
                SaveParameters();
            }
            UpdateFormFromParams(m_Component);
        }

        // Check for the ExternalReset validity
        private void ValidatingExternalReset()
        {
            string val1 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT0MODE).Value;
            string val2 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT1MODE).Value;
            string val3 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT2MODE).Value;
            string val4 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT3MODE).Value;
            string val5 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT4MODE).Value;
            string val6 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT5MODE).Value;
            string val7 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT6MODE).Value;
            string val8 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT7MODE).Value;
            // Verifies whether ExternalReset is checked when all BitxMode is set to DIRECTMODE
            if (m_reset.Checked == true)
            {
                if (val1 == directMode && val2 == directMode && val3 == directMode && val4 == directMode && val5 == directMode && val6 == directMode && val7 == directMode && val8 == directMode)
                {
                    ep_Errors.SetError(m_reset, String.Format("External Reset parameter is not valid when all BitMode parameter is set to DirectMode"));
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.EXTERNALRESET, TRUE);
                    //e.Cancel = true;
                }
                else
                {
                    ep_Errors.SetError(m_reset, "");
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.EXTERNALRESET, TRUE);
                }
            }
            else
            {
                ep_Errors.SetError(m_reset, "");
                m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.EXTERNALRESET, FALSE);
            }
            m_Component.CommitParamExprs();
        }

        private void m_reset_Validating(object sender, CancelEventArgs e)
        {
            // Gets and sets ExternalReset value
            ValidatingExternalReset();           
        }

        private void m_reset_CheckedChanged(object sender, EventArgs e)
        {
            // Removes all ERROR provider 
            ep_Errors.SetError(m_reset, string.Empty);
            // Gets and sets ExternalReset value
            m_reset_Validating(sender, new CancelEventArgs());
        }

        private void m_dgvBitFieldConfigure_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            int bitval = DEFAULT_BITVALUE;
            int val = 0;

            if (e.RowIndex != -1)
            {
                // Updates the BitValue for a specified row
                if ((e.ColumnIndex == SECOND_COLUMN_INDEX) && (e.RowIndex >= OUTPUT_ROWS_START))
                {
                    if (((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value.ToString() == BITVALUE_ONE)
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = BITVALUE_ZERO;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.LightGray;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.LightGray;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                    }
                    else
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = BITVALUE_ONE;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                    }
                    // Gets and saves the BitValue
                    for (int col = MAX_OUTPUTS - 1; col >= DEFAULT_OUTPUT; col--)
                    {
                        if ((m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Visible == true)
                        {                            
                            val = Convert.ToInt16(((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[col].Cells[THIRD_COLUMN_INDEX]).Value);
                            bitval = bitval << 1 | val;
                        }
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
            string val1 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT0MODE).Value;
            string val2 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT1MODE).Value;
            string val3 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT2MODE).Value;
            string val4 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT3MODE).Value;
            string val5 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT4MODE).Value;
            string val6 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT5MODE).Value;
            string val7 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT6MODE).Value;
            string val8 = m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.BIT7MODE).Value;
            if (m_reset.Checked == true && val1 == directMode && val2 == directMode && val3 == directMode && val4 == directMode && val5 == directMode && val6 == directMode && val7 == directMode && val8 == directMode)
            {
                ep_Errors.SetError(m_reset, string.Format("External Reset parameter is not valid when all BitMode parameter is set to DirectMode"));
                //e.Cancel = true;                
            }
            else
            {
                ep_Errors.SetError(m_reset, string.Empty);
            }
            UpdateFormFromParams(m_Component);
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
                        IEnumerable<string> Bit0ModeEnums = m_Component.GetPossibleEnumValues(CyControlReg_v1_50.ControlRegParameters.BIT0MODE);
                      
                        foreach (string str in Bit0ModeEnums)
                        {
                            // Save the current BitxMode selection
                            if (cb.SelectedIndex == currentIndex)
                            {
                                m_Component.SetParamExpr(BIT + (m_dgvBitFieldConfigure.CurrentRow.Index) + MODE, str);
                                m_Component.CommitParamExprs();
                                // If selection is DIRECTMODE then validate whether ExternalReset is checked
                                if (cb.SelectedItem.ToString() == DIRECTMODE)
                                {                                    
                                    cb.Validating += new CancelEventHandler(cb_Validating);
                                }
                                else
                                {
                                    ep_Errors.SetError(m_reset, string.Empty);
                                }                                
                                UpdateFormFromParams(m_Component);
                                break;
                            }
                            currentIndex++;
                        }
                    }
                }
            }
        }
    }
}


