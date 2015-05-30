namespace MDIO_Interface_v1_10
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
            this.addressDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.initValueDisplayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.maskDisplayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.clearOnReadDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.writeOnlyDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.triggerOnWriteDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.triggerOnReadDataGridViewCheckBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.auxBitsDataGridViewColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.cyRegAddressBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listBoxRegSpaces = new MDIO_Interface_v1_10.CyRefreshingListBox();
            this.toolStripRegSpace = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonAdd = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonRemove = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonImport = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonExport = new System.Windows.Forms.ToolStripButton();
            this.chbEnableAuxBits = new System.Windows.Forms.CheckBox();
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
            this.panelBottom = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cyRegAddressBindingSource)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.toolStripRegSpace.SuspendLayout();
            this.gbRegisters.SuspendLayout();
            this.gbRegSpaceSettings.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panelBottom.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvRegisters
            // 
            this.dgvRegisters.AllowUserToAddRows = false;
            this.dgvRegisters.AllowUserToDeleteRows = false;
            this.dgvRegisters.AllowUserToResizeColumns = false;
            this.dgvRegisters.AllowUserToResizeRows = false;
            this.dgvRegisters.AutoGenerateColumns = false;
            this.dgvRegisters.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvRegisters.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRegisters.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.addressDataGridViewTextBoxColumn,
            this.initValueDisplayDataGridViewTextBoxColumn,
            this.maskDisplayDataGridViewTextBoxColumn,
            this.clearOnReadDataGridViewCheckBoxColumn,
            this.writeOnlyDataGridViewCheckBoxColumn,
            this.triggerOnWriteDataGridViewCheckBoxColumn,
            this.triggerOnReadDataGridViewCheckBoxColumn,
            this.auxBitsDataGridViewColumn});
            this.dgvRegisters.DataSource = this.cyRegAddressBindingSource;
            this.dgvRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvRegisters.Location = new System.Drawing.Point(4, 19);
            this.dgvRegisters.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dgvRegisters.Name = "dgvRegisters";
            this.dgvRegisters.RowHeadersVisible = false;
            this.dgvRegisters.RowHeadersWidth = 20;
            this.dgvRegisters.Size = new System.Drawing.Size(681, 269);
            this.dgvRegisters.TabIndex = 0;
            this.dgvRegisters.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.dgvRegisters_CellFormatting);
            this.dgvRegisters.CellPainting += new System.Windows.Forms.DataGridViewCellPaintingEventHandler(this.dgvRegisters_CellPainting);
            this.dgvRegisters.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRegisters_CellValueChanged);
            this.dgvRegisters.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvRegisters_CurrentCellDirtyStateChanged);
            // 
            // addressDataGridViewTextBoxColumn
            // 
            this.addressDataGridViewTextBoxColumn.DataPropertyName = "Address";
            this.addressDataGridViewTextBoxColumn.HeaderText = "Address";
            this.addressDataGridViewTextBoxColumn.Name = "addressDataGridViewTextBoxColumn";
            // 
            // initValueDisplayDataGridViewTextBoxColumn
            // 
            this.initValueDisplayDataGridViewTextBoxColumn.DataPropertyName = "InitValueDisplay";
            this.initValueDisplayDataGridViewTextBoxColumn.HeaderText = "Initial value";
            this.initValueDisplayDataGridViewTextBoxColumn.Name = "initValueDisplayDataGridViewTextBoxColumn";
            // 
            // maskDisplayDataGridViewTextBoxColumn
            // 
            this.maskDisplayDataGridViewTextBoxColumn.DataPropertyName = "MaskDisplay";
            this.maskDisplayDataGridViewTextBoxColumn.HeaderText = " ";
            this.maskDisplayDataGridViewTextBoxColumn.Name = "maskDisplayDataGridViewTextBoxColumn";
            // 
            // clearOnReadDataGridViewCheckBoxColumn
            // 
            this.clearOnReadDataGridViewCheckBoxColumn.DataPropertyName = "ClearOnRead";
            this.clearOnReadDataGridViewCheckBoxColumn.HeaderText = " ";
            this.clearOnReadDataGridViewCheckBoxColumn.Name = "clearOnReadDataGridViewCheckBoxColumn";
            // 
            // writeOnlyDataGridViewCheckBoxColumn
            // 
            this.writeOnlyDataGridViewCheckBoxColumn.DataPropertyName = "WriteOnly";
            this.writeOnlyDataGridViewCheckBoxColumn.HeaderText = " ";
            this.writeOnlyDataGridViewCheckBoxColumn.Name = "writeOnlyDataGridViewCheckBoxColumn";
            // 
            // triggerOnWriteDataGridViewCheckBoxColumn
            // 
            this.triggerOnWriteDataGridViewCheckBoxColumn.DataPropertyName = "TriggerOnWrite";
            this.triggerOnWriteDataGridViewCheckBoxColumn.HeaderText = " ";
            this.triggerOnWriteDataGridViewCheckBoxColumn.Name = "triggerOnWriteDataGridViewCheckBoxColumn";
            // 
            // triggerOnReadDataGridViewCheckBoxColumn
            // 
            this.triggerOnReadDataGridViewCheckBoxColumn.DataPropertyName = "TriggerOnRead";
            this.triggerOnReadDataGridViewCheckBoxColumn.HeaderText = " ";
            this.triggerOnReadDataGridViewCheckBoxColumn.Name = "triggerOnReadDataGridViewCheckBoxColumn";
            // 
            // auxBitsDataGridViewColumn
            // 
            this.auxBitsDataGridViewColumn.DataPropertyName = "AuxBitsDisplay";
            this.auxBitsDataGridViewColumn.HeaderText = "Aux bits";
            this.auxBitsDataGridViewColumn.MaxInputLength = 4;
            this.auxBitsDataGridViewColumn.Name = "auxBitsDataGridViewColumn";
            // 
            // cyRegAddressBindingSource
            // 
            this.cyRegAddressBindingSource.DataSource = typeof(MDIO_Interface_v1_10.CyRegAddress);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listBoxRegSpaces);
            this.splitContainer1.Panel1.Controls.Add(this.panelBottom);
            this.splitContainer1.Panel1.Controls.Add(this.toolStripRegSpace);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Panel2.Controls.Add(this.gbRegisters);
            this.splitContainer1.Panel2.Controls.Add(this.gbRegSpaceSettings);
            this.splitContainer1.Size = new System.Drawing.Size(852, 421);
            this.splitContainer1.SplitterDistance = 158;
            this.splitContainer1.SplitterWidth = 5;
            this.splitContainer1.TabIndex = 1;
            // 
            // listBoxRegSpaces
            // 
            this.listBoxRegSpaces.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listBoxRegSpaces.FormattingEnabled = true;
            this.listBoxRegSpaces.IntegralHeight = false;
            this.listBoxRegSpaces.ItemHeight = 16;
            this.listBoxRegSpaces.Location = new System.Drawing.Point(0, 25);
            this.listBoxRegSpaces.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listBoxRegSpaces.Name = "listBoxRegSpaces";
            this.listBoxRegSpaces.Size = new System.Drawing.Size(158, 361);
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
            this.toolStripRegSpace.Size = new System.Drawing.Size(158, 25);
            this.toolStripRegSpace.TabIndex = 0;
            this.toolStripRegSpace.Text = "toolStrip1";
            // 
            // toolStripButtonAdd
            // 
            this.toolStripButtonAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonAdd.Image = global::MDIO_Interface_v1_10.Resources.Add;
            this.toolStripButtonAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonAdd.Name = "toolStripButtonAdd";
            this.toolStripButtonAdd.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonAdd.Text = "Add new register space (Alt+D)";
            this.toolStripButtonAdd.Click += new System.EventHandler(this.toolStripButtonAdd_Click);
            // 
            // toolStripButtonRemove
            // 
            this.toolStripButtonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Image = global::MDIO_Interface_v1_10.Resources.DeleteHS;
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
            this.toolStripButtonImport.Image = global::MDIO_Interface_v1_10.Resources.Import;
            this.toolStripButtonImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonImport.Name = "toolStripButtonImport";
            this.toolStripButtonImport.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonImport.Text = "Import from file (Ctrl+M)";
            this.toolStripButtonImport.Click += new System.EventHandler(this.toolStripButtonImport_Click);
            // 
            // toolStripButtonExport
            // 
            this.toolStripButtonExport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonExport.Image = global::MDIO_Interface_v1_10.Resources.Export;
            this.toolStripButtonExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonExport.Name = "toolStripButtonExport";
            this.toolStripButtonExport.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonExport.Text = "Export to file (Ctrl+R)";
            this.toolStripButtonExport.Click += new System.EventHandler(this.toolStripButtonExport_Click);
            // 
            // chbEnableAuxBits
            // 
            this.chbEnableAuxBits.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.chbEnableAuxBits.AutoSize = true;
            this.chbEnableAuxBits.Location = new System.Drawing.Point(4, 8);
            this.chbEnableAuxBits.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chbEnableAuxBits.Name = "chbEnableAuxBits";
            this.chbEnableAuxBits.Size = new System.Drawing.Size(155, 21);
            this.chbEnableAuxBits.TabIndex = 6;
            this.chbEnableAuxBits.Text = "Enable auxiliary bits";
            this.chbEnableAuxBits.UseVisualStyleBackColor = true;
            this.chbEnableAuxBits.CheckedChanged += new System.EventHandler(this.chbEnableAuxBits_CheckedChanged);
            // 
            // gbRegisters
            // 
            this.gbRegisters.Controls.Add(this.dgvRegisters);
            this.gbRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbRegisters.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbRegisters.Location = new System.Drawing.Point(0, 129);
            this.gbRegisters.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbRegisters.Name = "gbRegisters";
            this.gbRegisters.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbRegisters.Size = new System.Drawing.Size(689, 292);
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
            this.gbRegSpaceSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbRegSpaceSettings.Name = "gbRegSpaceSettings";
            this.gbRegSpaceSettings.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbRegSpaceSettings.Size = new System.Drawing.Size(689, 129);
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
            this.panel1.Location = new System.Drawing.Point(4, 19);
            this.panel1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(681, 106);
            this.panel1.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(108, 73);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 17);
            this.label2.TabIndex = 13;
            this.label2.Text = "0x";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(108, 41);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 17);
            this.label1.TabIndex = 12;
            this.label1.Text = "0x";
            // 
            // lblRegisterName
            // 
            this.lblRegisterName.AutoSize = true;
            this.lblRegisterName.Location = new System.Drawing.Point(4, 9);
            this.lblRegisterName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRegisterName.Name = "lblRegisterName";
            this.lblRegisterName.Size = new System.Drawing.Size(49, 17);
            this.lblRegisterName.TabIndex = 1;
            this.lblRegisterName.Text = "Name:";
            // 
            // lblMemoryType
            // 
            this.lblMemoryType.AutoSize = true;
            this.lblMemoryType.Location = new System.Drawing.Point(232, 9);
            this.lblMemoryType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblMemoryType.Name = "lblMemoryType";
            this.lblMemoryType.Size = new System.Drawing.Size(124, 17);
            this.lblMemoryType.TabIndex = 11;
            this.lblMemoryType.Text = "Register stored in:";
            // 
            // tbName
            // 
            this.tbName.Location = new System.Drawing.Point(59, 5);
            this.tbName.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbName.MaxLength = 24;
            this.tbName.Name = "tbName";
            this.tbName.Size = new System.Drawing.Size(155, 22);
            this.tbName.TabIndex = 0;
            this.tbName.Text = "REGISTER_SPACE_1";
            this.tbName.TextChanged += new System.EventHandler(this.tbName_TextChanged);
            this.tbName.Validated += new System.EventHandler(this.tbName_Validated);
            // 
            // cbMemoryType
            // 
            this.cbMemoryType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbMemoryType.FormattingEnabled = true;
            this.cbMemoryType.Location = new System.Drawing.Point(363, 5);
            this.cbMemoryType.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbMemoryType.Name = "cbMemoryType";
            this.cbMemoryType.Size = new System.Drawing.Size(81, 24);
            this.cbMemoryType.TabIndex = 3;
            this.cbMemoryType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // tbStartAddress
            // 
            this.tbStartAddress.Location = new System.Drawing.Point(133, 37);
            this.tbStartAddress.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbStartAddress.Name = "tbStartAddress";
            this.tbStartAddress.Size = new System.Drawing.Size(71, 22);
            this.tbStartAddress.TabIndex = 1;
            this.tbStartAddress.Text = "0000";
            this.tbStartAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbStartAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblConfigType
            // 
            this.lblConfigType.AutoSize = true;
            this.lblConfigType.Location = new System.Drawing.Point(232, 74);
            this.lblConfigType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblConfigType.Name = "lblConfigType";
            this.lblConfigType.Size = new System.Drawing.Size(111, 17);
            this.lblConfigType.TabIndex = 9;
            this.lblConfigType.Text = "Config stored in:";
            // 
            // lblStartAddress
            // 
            this.lblStartAddress.AutoSize = true;
            this.lblStartAddress.Location = new System.Drawing.Point(4, 41);
            this.lblStartAddress.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblStartAddress.Name = "lblStartAddress";
            this.lblStartAddress.Size = new System.Drawing.Size(97, 17);
            this.lblStartAddress.TabIndex = 3;
            this.lblStartAddress.Text = "Start address:";
            // 
            // cbConfigType
            // 
            this.cbConfigType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbConfigType.FormattingEnabled = true;
            this.cbConfigType.Location = new System.Drawing.Point(363, 70);
            this.cbConfigType.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbConfigType.Name = "cbConfigType";
            this.cbConfigType.Size = new System.Drawing.Size(81, 24);
            this.cbConfigType.TabIndex = 5;
            this.cbConfigType.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // tbEndAddress
            // 
            this.tbEndAddress.Location = new System.Drawing.Point(133, 69);
            this.tbEndAddress.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbEndAddress.Name = "tbEndAddress";
            this.tbEndAddress.Size = new System.Drawing.Size(71, 22);
            this.tbEndAddress.TabIndex = 2;
            this.tbEndAddress.Text = "0000";
            this.tbEndAddress.TextChanged += new System.EventHandler(this.tbStartEndAddress_TextChanged);
            this.tbEndAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbStartEndAddress_KeyPress);
            // 
            // lblDataWidth
            // 
            this.lblDataWidth.AutoSize = true;
            this.lblDataWidth.Location = new System.Drawing.Point(232, 41);
            this.lblDataWidth.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDataWidth.Name = "lblDataWidth";
            this.lblDataWidth.Size = new System.Drawing.Size(78, 17);
            this.lblDataWidth.TabIndex = 7;
            this.lblDataWidth.Text = "Data width:";
            // 
            // lblEndAddress
            // 
            this.lblEndAddress.AutoSize = true;
            this.lblEndAddress.Location = new System.Drawing.Point(4, 73);
            this.lblEndAddress.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblEndAddress.Name = "lblEndAddress";
            this.lblEndAddress.Size = new System.Drawing.Size(92, 17);
            this.lblEndAddress.TabIndex = 5;
            this.lblEndAddress.Text = "End address:";
            // 
            // cbDataWidth
            // 
            this.cbDataWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDataWidth.FormattingEnabled = true;
            this.cbDataWidth.Location = new System.Drawing.Point(363, 37);
            this.cbDataWidth.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDataWidth.Name = "cbDataWidth";
            this.cbDataWidth.Size = new System.Drawing.Size(81, 24);
            this.cbDataWidth.TabIndex = 4;
            this.cbDataWidth.SelectedIndexChanged += new System.EventHandler(this.cbComboBoxes_SelectedIndexChanged);
            // 
            // panelBottom
            // 
            this.panelBottom.Controls.Add(this.chbEnableAuxBits);
            this.panelBottom.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelBottom.Location = new System.Drawing.Point(0, 386);
            this.panelBottom.Name = "panelBottom";
            this.panelBottom.Size = new System.Drawing.Size(158, 35);
            this.panelBottom.TabIndex = 7;
            // 
            // CyAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.splitContainer1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "CyAdvancedTab";
            this.Size = new System.Drawing.Size(852, 421);
            this.Load += new System.EventHandler(this.CyAdvancedTab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cyRegAddressBindingSource)).EndInit();
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
            this.panelBottom.ResumeLayout(false);
            this.panelBottom.PerformLayout();
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
        private System.Windows.Forms.CheckBox chbEnableAuxBits;
        private System.Windows.Forms.BindingSource cyRegAddressBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn addressDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn initValueDisplayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn maskDisplayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn clearOnReadDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn writeOnlyDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn triggerOnWriteDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn triggerOnReadDataGridViewCheckBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn auxBitsDataGridViewColumn;
        private System.Windows.Forms.Panel panelBottom;
    }
}
