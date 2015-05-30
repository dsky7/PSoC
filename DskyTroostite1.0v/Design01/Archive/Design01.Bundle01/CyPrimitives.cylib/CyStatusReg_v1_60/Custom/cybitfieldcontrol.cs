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

namespace CyCustomizer.CyStatusReg_v1_60
{
    public partial class CyBitfieldControl : UserControl
    {
        public const int MIN_INPUTS = 1;
        public const int MAX_INPUTS = 8;        
        public const int INPUT_ROWS_START = 0; 
        public const int INPUT_ROWS_END = INPUT_ROWS_START + MAX_INPUTS - 1;
        public const string TRANSPARENT = "Transparent";
        public const string STICKY = "Sticky";
        public const int DEFAULT_NUMINPUT = 1;
        public const int FIRST_ROW_INDEX = 1;
        
        public ICyInstEdit_v1 m_Component = null;
                
        public CyBitfieldControl(ICyInstEdit_v1 inst)
        {
            m_Component = inst;
            InitializeComponent();
            m_dgvBitFieldConfigure.RowHeadersVisible = false;
            m_dgvBitFieldConfigure.AllowUserToAddRows = false;
            m_dgvBitFieldConfigure.AllowUserToOrderColumns = false;
            m_dgvBitFieldConfigure.AllowUserToResizeColumns = false;
            m_dgvBitFieldConfigure.AllowUserToResizeRows = false;
            SetupColumns(inst);
            m_nudInputs.Minimum = 1;
            m_nudInputs.Maximum = MAX_INPUTS;
            UpdateFormFromParams(inst);
        }

        void SetupColumns(ICyInstEdit_v1 inst)
        {
            DataGridViewTextBoxColumn hexColumn = new DataGridViewTextBoxColumn();
            hexColumn.HeaderText = String.Format("     Bit"); 
            hexColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            hexColumn.ReadOnly = true;
            hexColumn.CellTemplate = new DataGridViewTextBoxCell();
            hexColumn.CellTemplate.Style.BackColor = Color.LightGray;
            m_dgvBitFieldConfigure.Columns.Add(hexColumn);

            DataGridViewButtonColumn outputColumn = new DataGridViewButtonColumn();
            outputColumn.HeaderText = String.Format("          Mode");
            //outputColumn.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            outputColumn.FlatStyle = FlatStyle.Flat;
            m_dgvBitFieldConfigure.Columns.Add(outputColumn);
           
        }

        private void SetColumnsVisibility(ICyInstEdit_v1 inst)
        {

            m_dgvBitFieldConfigure.Rows.Clear();
            string[] modeName = { CyBitfieldControl.TRANSPARENT, CyBitfieldControl.STICKY };
            StatusRegParameters prms = new StatusRegParameters(inst);
            
            for (int i = 0; i < 8; i++)
            {
                Object[] rowobs = new object[2];
                rowobs[INPUT_ROWS_START + 0] = "       " + i.ToString();
                try
                {
                    rowobs[INPUT_ROWS_START + 1] = modeName[(int)(Convert.ToInt16(m_Component.GetCommittedParam("Bit" + i.ToString() + "Mode").Value))];
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
                m_dgvBitFieldConfigure.Rows.Add(rowobs);
            }           
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 4].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 5].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 6].Visible = false;
            m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 7].Visible = false;
            try
            {
                m_dgvBitFieldConfigure.Height = Convert.ToInt16(m_dgvBitFieldConfigure.Rows[0].Height.ToString()) * (Convert.ToInt16(prms.NumInputs.Value) + 1);
            }
            catch(Exception e)
            {
                MessageBox.Show(e.ToString());
            }

            switch (Convert.ToInt16(prms.NumInputs.Value))
            {
                case 1:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    break;
                case 2:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    break;
                case 3:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    break;
                case 4:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = true;
                    break;
                case 5:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 4].Visible = true;
                    break;
                case 6:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 4].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 5].Visible = true;
                    break;
                case 7:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 4].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 5].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 6].Visible = true;
                    break; 
                case 8:
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 0].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 1].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 2].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 3].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 4].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 5].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 6].Visible = true;
                    m_dgvBitFieldConfigure.Rows[INPUT_ROWS_START + 7].Visible = true;
                    break;
            }
        }

        private void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            StatusRegParameters prms = new StatusRegParameters(inst);
            int inputs = DEFAULT_NUMINPUT;
            try
            {
                inputs = Convert.ToInt16(prms.NumInputs.Value);
            }
            catch (Exception) { }

            if (inputs > MAX_INPUTS || inputs < MIN_INPUTS) 
            {
                return;
            }
            m_nudInputs.Value = inputs;
            SetColumnsVisibility(inst);
        }
        
        private void ClearAllButtonValues()
        {                        
            //set all the buttons to 0 - Transparent value
            for (int j = INPUT_ROWS_END; j >= INPUT_ROWS_START; j--)
            {
                m_dgvBitFieldConfigure.Rows[j].Cells[FIRST_ROW_INDEX].Value = TRANSPARENT;
                m_Component.SetParamExpr("Bit" + (7 - j) + "Mode", CyBitfieldControl.TRANSPARENT);
                m_Component.CommitParamExprs();
            }
        }
          
        private void SetAllButtonValues()
        {
            //set all the buttons to 1 - "Sticky" value           
            for (int j = INPUT_ROWS_END; j >= INPUT_ROWS_START; j--)
            {
                m_dgvBitFieldConfigure.Rows[j].Cells[FIRST_ROW_INDEX].Value = STICKY;
                m_Component.SetParamExpr("Bit" + (7 - j) + "Mode", CyBitfieldControl.STICKY);
                m_Component.CommitParamExprs();
            }
        }
        
        private void m_dgvBitFieldConfigure_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {            
            if (e.RowIndex != -1)
            {
                if ((e.ColumnIndex <= INPUT_ROWS_END) && (e.ColumnIndex >= INPUT_ROWS_START + 1))
                {

                    if ((string)((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value == CyBitfieldControl.TRANSPARENT)
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = CyBitfieldControl.STICKY;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                        m_Component.SetParamExpr("Bit" + (e.RowIndex) + "Mode", CyBitfieldControl.STICKY);
                        m_Component.CommitParamExprs();   
                    }
                    else if ((string)((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value == CyBitfieldControl.STICKY)
                    {
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Value = CyBitfieldControl.TRANSPARENT;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.BackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionBackColor = Color.White;
                        ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Style.SelectionForeColor = Color.Black;
                        m_Component.SetParamExpr("Bit" + (e.RowIndex) + "Mode", CyBitfieldControl.TRANSPARENT);
                        m_Component.CommitParamExprs();
                    }
                    ((DataGridViewButtonCell)m_dgvBitFieldConfigure.Rows[e.RowIndex].Cells[e.ColumnIndex]).Selected = false;
                    }
                }
            }
        
                
        private void CyBitfieldControl_VisibleChanged(object sender, EventArgs e)
        {
            if (!this.Visible)
            {
                m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS, m_nudInputs.Value.ToString());
                m_Component.CommitParamExprs();
            }
            else
            {
                try
                {
                    m_nudInputs.Value = Convert.ToInt16(m_Component.GetCommittedParam(CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS).Value);
                }
                catch (Exception) { }
            }
        }

        /*Saves the NUMINPUTS.*/
        private void SaveParameters()
        {
            m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS, m_nudInputs.Value.ToString());
            m_Component.CommitParamExprs();
        }

        private void CyBitfieldControl_Leave(object sender, EventArgs e)
        {
            SaveParameters();
        }
                
		private void CheckAndSaveInputValue()
		{
			int paraminputs = DEFAULT_NUMINPUT;
            try
            {
                paraminputs = Convert.ToInt16(m_Component.GetCommittedParam(CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS).Value);
            }
            catch (Exception) { }
            if (paraminputs != m_nudInputs.Value)
            {
                SaveParameters();
            }
            UpdateFormFromParams(m_Component);
		}
		
        private void m_nudInputs_ValueChanged(object sender, EventArgs e)
        {
            CheckAndSaveInputValue();
        }
        
        public void UpdateFormFromInst(ICyInstEdit_v1 inst)
        {
           UpdateFormFromParams(inst);
        }
        
        private void m_bSetAll_Click(object sender, EventArgs e)
        {
            SetAllButtonValues();
        }
        
        private void m_bClearAll_Click(object sender, EventArgs e)
        {
            ClearAllButtonValues();
        }

        private void m_nudInputs_KeyUp(object sender, KeyEventArgs e)
        {
			CheckAndSaveInputValue();
        }
    }
}


