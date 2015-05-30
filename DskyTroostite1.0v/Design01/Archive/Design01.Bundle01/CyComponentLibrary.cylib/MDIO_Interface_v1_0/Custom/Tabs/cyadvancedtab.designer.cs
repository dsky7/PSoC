namespace MDIO_Interface_v1_0
{
    partial class CyAdvancedTab
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
            this.components = new System.ComponentModel.Container();
            this.dgvRegisters = new System.Windows.Forms.DataGridView();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listBoxRegSpaces = new MDIO_Interface_v1_0.CyRefreshingListBox();
            this.toolStripRegSpace = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonAdd = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonRemove = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonImport = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonExport = new System.Windows.Forms.ToolStripButton();
            this.gbRegisters = new System.Windows.Forms.GroupBox();
            this.gbRegSpaceSettings = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblRegisterName = new System.Windows.Forms.Label();
            this.lblMemoryType = new System.Windows.Forms.Label();
            this.tbName = new System.Windows.Forms.TextBox();
            this.cbMemoryType = new System.Windows.Forms.ComboBox();
            this.tbStartAddress = new System.Windows.Forms.TextBox();
            this.lblConfigType = new System.Windows.Forms.Label();
            this.lblStartAddress = new System.Windows.Forms.Label();
            this.cbConfigType = new System.Windows.Forms.ComboBox();
            this.tbEndAddress = new System.Windows.Forms.TextBox();
            this.lblDataWidth = new System.Windows.Forms.Label();
            this.lblEndAddress = new System.Windows.Forms.Label();
            this.cbDataWidth = new System.Windows.Forms.ComboBox();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.toolStripRegSpace.SuspendLayout();
            this.gbRegisters.SuspendLayout();
            this.gbRegSpaceSettings.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvRegisters
            // 
            this.dgvRegisters.AllowUserToAddRows = false;
            this.dgvRegisters.AllowUserToDeleteRows = false;
            this.dgvRegisters.AllowUserToResizeColumns = false;
            this.dgvRegisters.AllowUserToResizeRows = false;
            this.dgvRegisters.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvRegisters.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvRegisters.Location = new System.Drawing.Point(3, 16);
            this.dgvRegisters.Name = "dgvRegisters";
            this.dgvRegisters.RowHeadersVisible = false;
            this.dgvRegisters.RowHeadersWidth = 20;
            this.dgvRegisters.Size = new System.Drawing.Size(412, 224);
            this.dgvRegisters.TabIndex = 0;
            this.dgvRegisters.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgvRegisters_CellFormatting);
            this.dgvRegisters.CellPainting += new System.Windows.Forms.DataGridViewCellPaintingEventHandler(this.dgvRegisters_CellPainting);
            this.dgvRegisters.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRegisters_CellValueChanged);
            this.dgvRegisters.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvRegisters_CurrentCellDirtyStateChanged);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listBoxRegSpaces);
            this.splitContainer1.Panel1.Controls.Add(this.toolStripRegSpace);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Panel2.Controls.Add(this.gbRegisters);
            this.splitContainer1.Panel2.Controls.Add(this.gbRegSpaceSettings);
            this.splitContainer1.Size = new System.Drawing.Size(567, 341);
            this.splitContainer1.SplitterDistance = 145;
            this.splitContainer1.TabIndex = 1;
            // 
            // listBoxRegSpaces
            // 
            this.listBoxRegSpaces.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listBoxRegSpaces.FormattingEnabled = true;
            this.listBoxRegSpaces.IntegralHeight = false;
            this.listBoxRegSpaces.Location = new System.Drawing.Point(0, 25);
            this.listBoxRegSpaces.Name = "listBoxRegSpaces";
            this.listBoxRegSpaces.Size = new System.Drawing.Size(145, 316);
            this.listBoxRegSpaces.TabIndex = 1;
            this.listBoxRegSpaces.SelectedIndexChanged += new System.EventHandler(this.listBoxRegSpaces_SelectedIndexChanged);
            this.listBoxRegSpaces.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.listBoxRegSpaces_Format);
            // 
            // toolStripRegSpace
            // 
            this.toolStripRegSpace.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStripRegSpace.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonAdd,
            this.toolStripButtonRemove,
            this.toolStripSeparator1,
            this.toolStripButtonImport,
            this.toolStripButtonExport});
            this.toolStripRegSpace.Location = new System.Drawing.Point(0, 0);
            this.toolStripRegSpace.Name = "toolStripRegSpace";
            this.toolStripRegSpace.Size = new System.Drawing.Size(145, 25);
            this.toolStripRegSpace.TabIndex = 0;
            this.toolStripRegSpace.Text = "toolStrip1";
            // 
            // toolStripButtonAdd
            // 
            this.toolStripButtonAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonAdd.Image = global::MDIO_Interface_v1_0.Resources.Add;
            this.toolStripButtonAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonAdd.Name = "toolStripButtonAdd";
            this.toolStripButtonAdd.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonAdd.Text = "Add new register space (Alt+D)";
            this.toolStripButtonAdd.Click += new System.EventHandler(this.toolStripButtonAdd_Click);
            // 
            // toolStripButtonRemove
            // 
            this.toolStripButtonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Image = global::MDIO_Interface_v1_0.Resources.DeleteHS;
            this.toolStripButtonRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonRemove.Name = "toolStripButtonRemove";
            this.toolStripButtonRemove.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonRemove.Text = "Remove register space (Alt+R)";
            this.toolStripButtonRemove.Click += new System.EventHandler(this.toolStripButtonRemove_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButtonImport
            // 
            this.toolStripButtonImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonImport.Image = global::MDIO_Interface_v1_0.Resources.Import;
            this.toolStripButtonImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonImport.Name = "toolStripButtonImport";
            this.toolStripButtonImport.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonImport.Text = "Import from file (Ctrl+M)";
            this.toolStripButtonImport.Click += new System.EventHandler(this.toolStripButtonImport_Click);
            // 
            // toolStripButtonExport
            // 
            this.toolStripButtonExport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonExport.Image = global::MDIO_Interface_v1_0.Resources.Export;
            this.toolStripButtonExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonExport.Name = "toolStripButtonExport";
            this.toolStripButtonExport.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonExport.Text = "Export to file (Ctrl+R)";
            this.toolStripButtonExport.Click += new System.EventHandler(this.toolStripButtonExport_Click);
            // 
            // gbRegisters
            // 
            this.gbRegisters.Controls.Add(this.dgvRegisters);
            this.gbRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbRegisters.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbRegisters.Location = new System.Drawing.Point(0, 98);
            this.gbRegisters.Name = "gbRegisters";
            this.gbRegisters.Size = new System.Drawing.Size(418, 243);
            this.gbRegisters.TabIndex = 2;
            this.gbRegisters.TabStop = false;
            this.gbRegisters.Text = "Register settings";
            // 
            // gbRegSpaceSettings
            // 
            this.gbRegSpaceSettings.Controls.Add(this.panel1);
            this.gbRegSpaceSettings.Dock = System.Windows.Forms.DockStyle.Top;
            this.gbRegSpaceSettings.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbRegSpaceSettings.Location = new System.Drawing.Point(0, 0);
            this.gbRegSpaceSettings.Name = "gbRegSpaceSettings";
            this.gbRegSpaceSettings.Size = new System.Drawing.Size(418, 98);
            this.gbRegSpaceSettings.TabIndex = 1;
            this.gbRegSpaceSettings.TabStop = false;
            this.gbRegSpaceSettings.Text = "Register space settings";
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.lblRegisterName);
            this.panel1.Controls.Add(this.lblMemoryType);
            this.panel1.Controls.Add(this.tbName);
            this.panel1.Controls.Add(this.cbMemoryType);
            this.panel1.Controls.Add(this.tbStartAddress);
            this.panel1.Controls.Add(this.lblConfigType);
            this.panel1.Controls.Add(this.lblStartAddress);
            this.panel1.Controls.Add(this.cbConfigType);
            this.panel1.Controls.Add(this.tbEndAddress);
            this.panel1.Controls.Add(this.lblDataWidth);
            this.panel1.Controls.Add(this.lblEndAddress);
            this.panel1.Controls.Add(this.cbDataWidth);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 16);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(412, 79);
            this.panel1.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(81, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(18, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "0x";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(81, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(18, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "0x";
            // 
            // lblRegisterName
            // 
            this.lblRegisterName.AutoSize = true;
            this.lblRegisterName.Location = new System.Drawing.Point(3, 4);
            this.lblRegisterName.Name = "lblRegisterName";
            this.lblRegisterName.Size = new System.Drawing.Size(38, 13);
            this.lblRegisterName.TabIndex = 1;
            this.lblRegisterName.Text = "Name:";
            // 
            // lblMemoryType
            // 
            this.lblMemoryType.AutoSize = true;
            this.lblMemoryType.Location = new System.Drawing.Point(174, 4);
            this.lblMemoryType.Name = "lblMemoryType";
            this.lblMemoryType.Size = new System.Drawing.Size(92, 13);
            this.lblMemoryType.TabIndex = 11;
            this.lblMemoryType.Text = "Register stored in:";
            // 
            // tbName
            // 
            this.tbName.Location = new System.Drawing.Point(44, 1);
            this.tbName.MaxLength = 24;
            this.tbName.Name = "tbName";
            this.tbName.Size = new System.Drawing.Size(117, 20);
            this.tbName.TabIndex = 0;
            this.tbName.Text = "REGISTER_SPACE_1";
            this.tbName.TextChanged += new System.EventHandler(this.tbName_TextChanged);
            this.tbName.Validated += new System.EventHandler(this.tbName_Validated);
            // 
            // cbMemoryType
            // 
            this.cbMemoryType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbMemoryType.FormattingEnabled = true;
            this.cbMemoryType.Location = new System.Drawing.Point(272, 1);
            this.cbMemoryType.Name = "cbMemoryType";
            this.cbMemoryType.Size = new System.Drawing.Size(62, 21);
            this.cbMemoryType.TabIndex = 3;
            this.cbMemoryType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // tbStartAddress
            // 
            this.tbStartAddress.Location = new System.Drawing.Point(100, 27);
            this.tbStartAddress.Name = "tbStartAddress";
            this.tbStartAddress.Size = new System.Drawing.Size(54, 20);
            this.tbStartAddress.TabIndex = 1;
            this.tbStartAddress.Text = "0000";
            this.tbStartAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbStartAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblConfigType
            // 
            this.lblConfigType.AutoSize = true;
            this.lblConfigType.Location = new System.Drawing.Point(174, 57);
            this.lblConfigType.Name = "lblConfigType";
            this.lblConfigType.Size = new System.Drawing.Size(83, 13);
            this.lblConfigType.TabIndex = 9;
            this.lblConfigType.Text = "Config stored in:";
            // 
            // lblStartAddress
            // 
            this.lblStartAddress.AutoSize = true;
            this.lblStartAddress.Location = new System.Drawing.Point(3, 30);
            this.lblStartAddress.Name = "lblStartAddress";
            this.lblStartAddress.Size = new System.Drawing.Size(72, 13);
            this.lblStartAddress.TabIndex = 3;
            this.lblStartAddress.Text = "Start address:";
            // 
            // cbConfigType
            // 
            this.cbConfigType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbConfigType.FormattingEnabled = true;
            this.cbConfigType.Location = new System.Drawing.Point(272, 54);
            this.cbConfigType.Name = "cbConfigType";
            this.cbConfigType.Size = new System.Drawing.Size(62, 21);
            this.cbConfigType.TabIndex = 5;
            this.cbConfigType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // tbEndAddress
            // 
            this.tbEndAddress.Location = new System.Drawing.Point(100, 53);
            this.tbEndAddress.Name = "tbEndAddress";
            this.tbEndAddress.Size = new System.Drawing.Size(54, 20);
            this.tbEndAddress.TabIndex = 2;
            this.tbEndAddress.Text = "0000";
            this.tbEndAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbEndAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblDataWidth
            // 
            this.lblDataWidth.AutoSize = true;
            this.lblDataWidth.Location = new System.Drawing.Point(174, 30);
            this.lblDataWidth.Name = "lblDataWidth";
            this.lblDataWidth.Size = new System.Drawing.Size(61, 13);
            this.lblDataWidth.TabIndex = 7;
            this.lblDataWidth.Text = "Data width:";
            // 
            // lblEndAddress
            // 
            this.lblEndAddress.AutoSize = true;
            this.lblEndAddress.Location = new System.Drawing.Point(3, 56);
            this.lblEndAddress.Name = "lblEndAddress";
            this.lblEndAddress.Size = new System.Drawing.Size(69, 13);
            this.lblEndAddress.TabIndex = 5;
            this.lblEndAddress.Text = "End address:";
            // 
            // cbDataWidth
            // 
            this.cbDataWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDataWidth.FormattingEnabled = true;
            this.cbDataWidth.Location = new System.Drawing.Point(272, 27);
            this.cbDataWidth.Name = "cbDataWidth";
            this.cbDataWidth.Size = new System.Drawing.Size(62, 21);
            this.cbDataWidth.TabIndex = 4;
            this.cbDataWidth.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // CyAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.splitContainer1);
            this.Name = "CyAdvancedTab";
            this.Size = new System.Drawing.Size(567, 341);
            this.Load += new System.EventHandler(this.CyAdvancedTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.toolStripRegSpace.ResumeLayout(false);
            this.toolStripRegSpace.PerformLayout();
            this.gbRegisters.ResumeLayout(false);
            this.gbRegSpaceSettings.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvRegisters;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ToolStrip toolStripRegSpace;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.GroupBox gbRegSpaceSettings;
        private System.Windows.Forms.Label lblRegisterName;
        private System.Windows.Forms.TextBox tbName;
        private System.Windows.Forms.Label lblStartAddress;
        private System.Windows.Forms.TextBox tbStartAddress;
        private System.Windows.Forms.Label lblEndAddress;
        private System.Windows.Forms.TextBox tbEndAddress;
        private System.Windows.Forms.Label lblDataWidth;
        private System.Windows.Forms.ComboBox cbDataWidth;
        private System.Windows.Forms.Label lblMemoryType;
        private System.Windows.Forms.ComboBox cbMemoryType;
        private System.Windows.Forms.Label lblConfigType;
        private System.Windows.Forms.ComboBox cbConfigType;
        private System.Windows.Forms.GroupBox gbRegisters;
        private System.Windows.Forms.ToolStripButton toolStripButtonAdd;
        private System.Windows.Forms.ToolStripButton toolStripButtonRemove;
        private System.Windows.Forms.ToolStripButton toolStripButtonImport;
        private System.Windows.Forms.ToolStripButton toolStripButtonExport;
        private CyRefreshingListBox listBoxRegSpaces;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}
