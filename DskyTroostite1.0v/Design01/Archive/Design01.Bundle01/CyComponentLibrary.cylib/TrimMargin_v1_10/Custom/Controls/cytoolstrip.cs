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
using System.IO;

namespace TrimMargin_v1_10
{
    public partial class CyToolStrip : UserControl
    {
        public CyParameters m_params;
        public DataGridView m_dgv;
        const string FILTER = "CSV files (*.csv)|*.csv|All files (*.*)|*.*";
        const string FILE_EXTENSION = "csv";

        public CyToolStrip()
        {
            InitializeComponent();
            tsbImportAll.Image = Resources.Import;
            tsbExportAll.Image = Resources.Export;
        }
        public void SetParameters(CyParameters param)
        {
            m_params = param;
        }

        private void tsbExport_Click(object sender, EventArgs e)
        {
            ExportRows();
        }

        public void ExportRows()
        {
            saveFileDialog.Title = Resources.ExportDialogHeader;
            saveFileDialog.DefaultExt = FILE_EXTENSION;
            saveFileDialog.Filter = FILTER;
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (Parent is CyVoltagesTab)
                    CyImportExport.SaveToFile(saveFileDialog.FileName, CyImportExport.Export(m_params.VoltagesTable, CyParameters.VoltagesHeader));
                else if (Parent is CyHardwareTab)
                    CyImportExport.SaveToFile(saveFileDialog.FileName, CyImportExport.Export(
                        m_params.HardwareTable, m_params.VoltagesTable,CyParameters.HardwareHeader));
            }
        }

        private void tsbImport_Click(object sender, EventArgs e)
        {
            ImportRows();
        }

        public void ImportRows()
        {
            openFileDialog.Title = Resources.ImportDialogHeader;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.DefaultExt = FILE_EXTENSION;
            openFileDialog.Filter = FILTER;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                DialogResult dr = MessageBox.Show(Resources.ImportConfirmation, m_params.m_inst.ComponentName,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (dr == DialogResult.Yes)
                {
                    string fileContent = CyImportExport.GetFileText(openFileDialog.FileName);


                    m_params.Import(this.Parent, fileContent, false);
                }
            }
        }

        private void tsbCopy_Click(object sender, EventArgs e)
        {
            CopyRows();
        }

        public void CopyRows()
        {
            if (this.Parent is CyVoltagesTab)
            {
                List<CyVoltagesTableRow> exportTable = new List<CyVoltagesTableRow>();
                for (int i = 0; i < m_dgv.RowCount; i++)
                {
                    if (m_dgv.Rows[i].Selected == true)
                        exportTable.Add(m_params.VoltagesTable[i]);
                }
                Clipboard.SetText(CyImportExport.Export(exportTable, CyParameters.GetColNames(m_dgv)));
            }
            if (this.Parent is CyHardwareTab)
            {
                List<CyHardwareTableRow> exportTable = new List<CyHardwareTableRow>();
                for (int i = 0; i < m_dgv.RowCount; i++)
                {
                    if (m_dgv.Rows[i].Selected == true)
                        exportTable.Add(m_params.HardwareTable[i]);
                }
                Clipboard.SetText(CyImportExport.Export(exportTable, m_params.VoltagesTable,
                    CyParameters.GetColNames(m_dgv)));
            }
        }

        private void tsbPaste_Click(object sender, EventArgs e)
        {
            PasteRows();
        }

        public void PasteRows()
        {
            string content = Clipboard.GetText();
            m_params.Import(this.Parent, content, true);
        }

        public void ChangeCopyPasteEnabling(bool copyPasteButtonsEnabled)
        {
            tsbCopy.Enabled = copyPasteButtonsEnabled;
            tsbPaste.Enabled = copyPasteButtonsEnabled;
        }

        public void tsbImportAll_Click(object sender, EventArgs e)
        {
            openFileDialog.Title = Resources.ImportAllTitle;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.DefaultExt = FILE_EXTENSION;
            openFileDialog.Filter = FILTER;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                DialogResult dr = MessageBox.Show(Resources.ImportConfirmation, m_params.m_inst.ComponentName,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                if (dr == DialogResult.Yes)
                {
                    List<StringBuilder> listTables = CyImportExport.GetTables(CyImportExport.GetFileText(openFileDialog.FileName));

                    if (listTables.Count >= 2)
                    {
                        m_params.Import(m_params.m_voltagesTab, listTables[0].ToString(), false);

                        m_params.Import(m_params.m_hardwareTab, listTables[1].ToString(), false);
                    }
                    else
                        MessageBox.Show(Resources.InvalidDataFormat, "Error", MessageBoxButtons.OK,
                            MessageBoxIcon.Warning);
                }
            }
        }
        public void tsbExportAll_Click(object sender, EventArgs e)
        {
            saveFileDialog.Title = Resources.ExportAllTitle;
            saveFileDialog.DefaultExt = FILE_EXTENSION;
            saveFileDialog.Filter = FILTER;
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.FileName = m_params.m_inst.InstanceName;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string voltagesTab = CyImportExport.Export(m_params.VoltagesTable, 
                    CyParameters.VoltagesHeader);

                string hardwareTab = CyImportExport.Export(m_params.HardwareTable, m_params.VoltagesTable,
                    CyParameters.HardwareHeader);

                CyImportExport.SaveToFile(saveFileDialog.FileName, string.Format("{0}\r\n{1}", voltagesTab, 
                    hardwareTab));
            }
        }
    }
}
