namespace TrimMargin_v1_20
{
    partial class CyVoltagesTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle8 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle9 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle10 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle11 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle12 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dgvVoltages = new System.Windows.Forms.DataGridView();
            this.cyToolStrip1 = new TrimMargin_v1_20.CyToolStrip();
            this.numNumConverters = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.colConverterOutput = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colConverterName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colNominalOutputVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMinVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_colCalcMinVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMaxVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_colCalcMaxVoltage = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_colVStartup = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMarginLowPercent = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMarginHighPercent = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMarginLow = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colMarginHigh = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dgvVoltages)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvVoltages
            // 
            this.dgvVoltages.AllowUserToAddRows = false;
            this.dgvVoltages.AllowUserToDeleteRows = false;
            this.dgvVoltages.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvVoltages.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgvVoltages.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dgvVoltages.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvVoltages.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colConverterOutput,
            this.colConverterName,
            this.colNominalOutputVoltage,
            this.colMinVoltage,
            this.m_colCalcMinVoltage,
            this.colMaxVoltage,
            this.m_colCalcMaxVoltage,
            this.m_colVStartup,
            this.colMarginLowPercent,
            this.colMarginHighPercent,
            this.colMarginLow,
            this.colMarginHigh});
            this.dgvVoltages.Location = new System.Drawing.Point(0, 58);
            this.dgvVoltages.Name = "dgvVoltages";
            this.dgvVoltages.RowHeadersWidth = 20;
            this.dgvVoltages.Size = new System.Drawing.Size(1100, 292);
            this.dgvVoltages.TabIndex = 0;
            this.dgvVoltages.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvVoltages_CellValueChanged);
            this.dgvVoltages.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgvVoltages_CurrentCellDirtyStateChanged);
            this.dgvVoltages.SelectionChanged += new System.EventHandler(this.dgvVoltages_SelectionChanged);
            // 
            // cyToolStrip1
            // 
            this.cyToolStrip1.BackColor = System.Drawing.SystemColors.Control;
            this.cyToolStrip1.Dock = System.Windows.Forms.DockStyle.Top;
            this.cyToolStrip1.Location = new System.Drawing.Point(0, 0);
            this.cyToolStrip1.Margin = new System.Windows.Forms.Padding(4);
            this.cyToolStrip1.Name = "cyToolStrip1";
            this.cyToolStrip1.Size = new System.Drawing.Size(1104, 25);
            this.cyToolStrip1.TabIndex = 1;
            // 
            // numNumConverters
            // 
            this.numNumConverters.Location = new System.Drawing.Point(158, 7);
            this.numNumConverters.Maximum = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.numNumConverters.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numNumConverters.Name = "numNumConverters";
            this.numNumConverters.Size = new System.Drawing.Size(60, 20);
            this.numNumConverters.TabIndex = 12;
            this.numNumConverters.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Number of converters:";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.numNumConverters);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1104, 33);
            this.panel1.TabIndex = 17;
            // 
            // colConverterOutput
            // 
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.colConverterOutput.DefaultCellStyle = dataGridViewCellStyle2;
            this.colConverterOutput.HeaderText = "Converter";
            this.colConverterOutput.Name = "colConverterOutput";
            this.colConverterOutput.ReadOnly = true;
            // 
            // colConverterName
            // 
            this.colConverterName.HeaderText = "Name";
            this.colConverterName.MaxInputLength = 16;
            this.colConverterName.Name = "colConverterName";
            // 
            // colNominalOutputVoltage
            // 
            dataGridViewCellStyle3.Format = "N2";
            dataGridViewCellStyle3.NullValue = null;
            this.colNominalOutputVoltage.DefaultCellStyle = dataGridViewCellStyle3;
            this.colNominalOutputVoltage.HeaderText = "Nominal voltage (V)";
            this.colNominalOutputVoltage.Name = "colNominalOutputVoltage";
            // 
            // colMinVoltage
            // 
            dataGridViewCellStyle4.Format = "N2";
            dataGridViewCellStyle4.NullValue = null;
            this.colMinVoltage.DefaultCellStyle = dataGridViewCellStyle4;
            this.colMinVoltage.HeaderText = "Trim/margin range Min voltage (V)";
            this.colMinVoltage.Name = "colMinVoltage";
            // 
            // m_colCalcMinVoltage
            // 
            dataGridViewCellStyle5.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle5.Format = "N2";
            this.m_colCalcMinVoltage.DefaultCellStyle = dataGridViewCellStyle5;
            this.m_colCalcMinVoltage.HeaderText = "Calculated Min voltage (V)";
            this.m_colCalcMinVoltage.Name = "m_colCalcMinVoltage";
            this.m_colCalcMinVoltage.ReadOnly = true;
            // 
            // colMaxVoltage
            // 
            dataGridViewCellStyle6.Format = "N2";
            dataGridViewCellStyle6.NullValue = null;
            this.colMaxVoltage.DefaultCellStyle = dataGridViewCellStyle6;
            this.colMaxVoltage.HeaderText = "Trim/margin range Max voltage (V)";
            this.colMaxVoltage.Name = "colMaxVoltage";
            // 
            // m_colCalcMaxVoltage
            // 
            dataGridViewCellStyle7.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle7.Format = "N2";
            this.m_colCalcMaxVoltage.DefaultCellStyle = dataGridViewCellStyle7;
            this.m_colCalcMaxVoltage.HeaderText = "Calculated Max voltage (V)";
            this.m_colCalcMaxVoltage.Name = "m_colCalcMaxVoltage";
            this.m_colCalcMaxVoltage.ReadOnly = true;
            // 
            // m_colVStartup
            // 
            dataGridViewCellStyle8.Format = "N2";
            this.m_colVStartup.DefaultCellStyle = dataGridViewCellStyle8;
            this.m_colVStartup.HeaderText = "Startup voltage (V)";
            this.m_colVStartup.Name = "m_colVStartup";
            // 
            // colMarginLowPercent
            // 
            dataGridViewCellStyle9.Format = "N2";
            dataGridViewCellStyle9.NullValue = null;
            this.colMarginLowPercent.DefaultCellStyle = dataGridViewCellStyle9;
            this.colMarginLowPercent.HeaderText = "Margin low (%)";
            this.colMarginLowPercent.Name = "colMarginLowPercent";
            // 
            // colMarginHighPercent
            // 
            dataGridViewCellStyle10.Format = "N2";
            dataGridViewCellStyle10.NullValue = null;
            this.colMarginHighPercent.DefaultCellStyle = dataGridViewCellStyle10;
            this.colMarginHighPercent.HeaderText = "Margin high (%)";
            this.colMarginHighPercent.Name = "colMarginHighPercent";
            // 
            // colMarginLow
            // 
            dataGridViewCellStyle11.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle11.Format = "N3";
            dataGridViewCellStyle11.NullValue = null;
            this.colMarginLow.DefaultCellStyle = dataGridViewCellStyle11;
            this.colMarginLow.HeaderText = "Margin low (V)";
            this.colMarginLow.Name = "colMarginLow";
            this.colMarginLow.ReadOnly = true;
            // 
            // colMarginHigh
            // 
            dataGridViewCellStyle12.BackColor = System.Drawing.SystemColors.ControlLight;
            dataGridViewCellStyle12.Format = "N3";
            dataGridViewCellStyle12.NullValue = null;
            this.colMarginHigh.DefaultCellStyle = dataGridViewCellStyle12;
            this.colMarginHigh.HeaderText = "Margin high (V)";
            this.colMarginHigh.Name = "colMarginHigh";
            this.colMarginHigh.ReadOnly = true;
            // 
            // CyVoltagesTab
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoScroll = true;
            this.Controls.Add(this.dgvVoltages);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.cyToolStrip1);
            this.Name = "CyVoltagesTab";
            this.Size = new System.Drawing.Size(1104, 438);
            ((System.ComponentModel.ISupportInitialize)(this.dgvVoltages)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numNumConverters)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvVoltages;
        private CyToolStrip cyToolStrip1;
        private System.Windows.Forms.NumericUpDown numNumConverters;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridViewTextBoxColumn colConverterOutput;
        private System.Windows.Forms.DataGridViewTextBoxColumn colConverterName;
        private System.Windows.Forms.DataGridViewTextBoxColumn colNominalOutputVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMinVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_colCalcMinVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMaxVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_colCalcMaxVoltage;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_colVStartup;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMarginLowPercent;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMarginHighPercent;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMarginLow;
        private System.Windows.Forms.DataGridViewTextBoxColumn colMarginHigh;
    }
}
