namespace TrimMargin_v1_20
{
    partial class CyToolStrip
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbCopy = new System.Windows.Forms.ToolStripButton();
            this.tsbPaste = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbOpenConfig = new System.Windows.Forms.ToolStripButton();
            this.tsbSaveConfig = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbImport = new System.Windows.Forms.ToolStripButton();
            this.tsbExport = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbImportAll = new System.Windows.Forms.ToolStripButton();
            this.tsbExportAll = new System.Windows.Forms.ToolStripButton();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.BackColor = System.Drawing.SystemColors.Control;
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbCopy,
            this.tsbPaste,
            this.toolStripSeparator1,
            this.tsbOpenConfig,
            this.tsbSaveConfig,
            this.toolStripSeparator3,
            this.tsbImport,
            this.tsbExport,
            this.toolStripSeparator2,
            this.tsbImportAll,
            this.tsbExportAll});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(552, 25);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbCopy
            // 
            this.tsbCopy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbCopy.Image = global::TrimMargin_v1_20.Resources.Copy;
            this.tsbCopy.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbCopy.Name = "tsbCopy";
            this.tsbCopy.Size = new System.Drawing.Size(23, 22);
            this.tsbCopy.Text = "Copy rows (Ctrl + C)";
            this.tsbCopy.Click += new System.EventHandler(this.tsbCopy_Click);
            // 
            // tsbPaste
            // 
            this.tsbPaste.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbPaste.Image = global::TrimMargin_v1_20.Resources.Paste;
            this.tsbPaste.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbPaste.Name = "tsbPaste";
            this.tsbPaste.Size = new System.Drawing.Size(23, 22);
            this.tsbPaste.Text = "Paste rows (Ctrl + V)";
            this.tsbPaste.Click += new System.EventHandler(this.tsbPaste_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbOpenConfig
            // 
            this.tsbOpenConfig.Image = global::TrimMargin_v1_20.Resources.Open;
            this.tsbOpenConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbOpenConfig.Name = "tsbOpenConfig";
            this.tsbOpenConfig.Size = new System.Drawing.Size(128, 22);
            this.tsbOpenConfig.Text = "Load configuration";
            this.tsbOpenConfig.Click += new System.EventHandler(this.tsbOpenConfig_Click);
            // 
            // tsbSaveConfig
            // 
            this.tsbSaveConfig.Image = global::TrimMargin_v1_20.Resources.Save;
            this.tsbSaveConfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSaveConfig.Name = "tsbSaveConfig";
            this.tsbSaveConfig.Size = new System.Drawing.Size(126, 22);
            this.tsbSaveConfig.Text = "Save configuration";
            this.tsbSaveConfig.Click += new System.EventHandler(this.tsbSaveConfig_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbImport
            // 
            this.tsbImport.Image = global::TrimMargin_v1_20.Resources.Import;
            this.tsbImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbImport.Name = "tsbImport";
            this.tsbImport.Size = new System.Drawing.Size(92, 22);
            this.tsbImport.Text = "Import table";
            this.tsbImport.ToolTipText = "Import table (Ctrl + M)";
            this.tsbImport.Click += new System.EventHandler(this.tsbImport_Click);
            // 
            // tsbExport
            // 
            this.tsbExport.Image = global::TrimMargin_v1_20.Resources.Export;
            this.tsbExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExport.Name = "tsbExport";
            this.tsbExport.Size = new System.Drawing.Size(89, 22);
            this.tsbExport.Text = "Export table";
            this.tsbExport.ToolTipText = "Export table (Ctrl + R)";
            this.tsbExport.Click += new System.EventHandler(this.tsbExport_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbImportAll
            // 
            this.tsbImportAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbImportAll.Name = "tsbImportAll";
            this.tsbImportAll.Size = new System.Drawing.Size(62, 19);
            this.tsbImportAll.Text = "Import all";
            this.tsbImportAll.ToolTipText = "Import all (Ctrl + Alt + M)";
            this.tsbImportAll.Click += new System.EventHandler(this.tsbImportAll_Click);
            // 
            // tsbExportAll
            // 
            this.tsbExportAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbExportAll.Name = "tsbExportAll";
            this.tsbExportAll.Size = new System.Drawing.Size(59, 19);
            this.tsbExportAll.Text = "Export all";
            this.tsbExportAll.ToolTipText = "Export all (Ctrl + Alt + R)";
            this.tsbExportAll.Click += new System.EventHandler(this.tsbExportAll_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // CyToolStrip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.toolStrip1);
            this.Name = "CyToolStrip";
            this.Size = new System.Drawing.Size(552, 25);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbCopy;
        private System.Windows.Forms.ToolStripButton tsbPaste;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton tsbImport;
        private System.Windows.Forms.ToolStripButton tsbExport;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ToolStripButton tsbExportAll;
        private System.Windows.Forms.ToolStripButton tsbImportAll;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton tsbOpenConfig;
        private System.Windows.Forms.ToolStripButton tsbSaveConfig;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
    }
}
