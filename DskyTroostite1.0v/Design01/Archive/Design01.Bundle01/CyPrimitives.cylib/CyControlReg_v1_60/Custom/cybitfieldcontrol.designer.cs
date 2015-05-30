namespace CyCustomizer.CyControlReg_v1_60
{
    partial class CyBitfieldControl
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
            this.m_dgvBitFieldConfigure = new System.Windows.Forms.DataGridView();
            this.m_bClearAll = new System.Windows.Forms.Button();
            this.m_nudInputs = new System.Windows.Forms.NumericUpDown();
            this.m_lblInputs = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_reset = new System.Windows.Forms.CheckBox();
            this.ClearBitValue = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfigure)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudInputs)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_dgvBitFieldConfigure
            // 
            this.m_dgvBitFieldConfigure.AllowDrop = true;
            this.m_dgvBitFieldConfigure.AllowUserToResizeColumns = false;
            this.m_dgvBitFieldConfigure.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvBitFieldConfigure.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.m_dgvBitFieldConfigure.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvBitFieldConfigure.DefaultCellStyle = dataGridViewCellStyle2;
            this.m_dgvBitFieldConfigure.Location = new System.Drawing.Point(9, 19);
            this.m_dgvBitFieldConfigure.Name = "m_dgvBitFieldConfigure";
            this.m_dgvBitFieldConfigure.RowTemplate.Height = 24;
            this.m_dgvBitFieldConfigure.Size = new System.Drawing.Size(215, 223);
            this.m_dgvBitFieldConfigure.TabIndex = 5;
            this.m_dgvBitFieldConfigure.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.m_dgvBitFieldConfigure_EditingControlShowing);
            this.m_dgvBitFieldConfigure.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_dgvBitFieldConfigure_CellContentClick);
            // 
            // m_bClearAll
            // 
            this.m_bClearAll.Location = new System.Drawing.Point(60, 72);
            this.m_bClearAll.Name = "m_bClearAll";
            this.m_bClearAll.Size = new System.Drawing.Size(112, 23);
            this.m_bClearAll.TabIndex = 3;
            this.m_bClearAll.Text = "Set All DirectMode";
            this.m_bClearAll.UseVisualStyleBackColor = true;
            this.m_bClearAll.Click += new System.EventHandler(this.m_bClearAll_Click_1);
            // 
            // m_nudInputs
            // 
            this.m_nudInputs.BackColor = System.Drawing.Color.White;
            this.m_nudInputs.Location = new System.Drawing.Point(112, 31);
            this.m_nudInputs.Margin = new System.Windows.Forms.Padding(2);
            this.m_nudInputs.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.m_nudInputs.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.m_nudInputs.Name = "m_nudInputs";
            this.m_nudInputs.Size = new System.Drawing.Size(34, 20);
            this.m_nudInputs.TabIndex = 1;
            this.m_nudInputs.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.m_nudInputs.ValueChanged += new System.EventHandler(this.m_nudInputs_ValueChanged);
            this.m_nudInputs.KeyUp += new System.Windows.Forms.KeyEventHandler(this.m_nudInputs_KeyUp);
            // 
            // m_lblInputs
            // 
            this.m_lblInputs.Location = new System.Drawing.Point(60, 33);
            this.m_lblInputs.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblInputs.Name = "m_lblInputs";
            this.m_lblInputs.Size = new System.Drawing.Size(44, 21);
            this.m_lblInputs.TabIndex = 4;
            this.m_lblInputs.Text = "Outputs:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.m_dgvBitFieldConfigure);
            this.groupBox1.Location = new System.Drawing.Point(60, 102);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(232, 256);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "ModeMask/BitValue";
            // 
            // m_reset
            // 
            this.m_reset.AutoSize = true;
            this.m_reset.Location = new System.Drawing.Point(197, 32);
            this.m_reset.Name = "m_reset";
            this.m_reset.Size = new System.Drawing.Size(95, 17);
            this.m_reset.TabIndex = 2;
            this.m_reset.Text = "External Reset";
            this.m_reset.UseVisualStyleBackColor = true;
            this.m_reset.Validating += new System.ComponentModel.CancelEventHandler(this.m_reset_Validating);
            this.m_reset.CheckedChanged += new System.EventHandler(this.m_reset_CheckedChanged);
            // 
            // ClearBitValue
            // 
            this.ClearBitValue.Location = new System.Drawing.Point(192, 72);
            this.ClearBitValue.Name = "ClearBitValue";
            this.ClearBitValue.Size = new System.Drawing.Size(100, 23);
            this.ClearBitValue.TabIndex = 4;
            this.ClearBitValue.Text = "Clear All BitValue";
            this.ClearBitValue.UseVisualStyleBackColor = true;
            this.ClearBitValue.Click += new System.EventHandler(this.ClearBitValue_Click);
            // 
            // CyBitfieldControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Controls.Add(this.ClearBitValue);
            this.Controls.Add(this.m_reset);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.m_lblInputs);
            this.Controls.Add(this.m_nudInputs);
            this.Controls.Add(this.m_bClearAll);
            this.Name = "CyBitfieldControl";
            this.Size = new System.Drawing.Size(337, 400);
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfigure)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudInputs)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView m_dgvBitFieldConfigure;
        private System.Windows.Forms.Button m_bClearAll;
        private System.Windows.Forms.NumericUpDown m_nudInputs;
        private System.Windows.Forms.Label m_lblInputs;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox m_reset;
        private System.Windows.Forms.Button ClearBitValue;
    }
}
