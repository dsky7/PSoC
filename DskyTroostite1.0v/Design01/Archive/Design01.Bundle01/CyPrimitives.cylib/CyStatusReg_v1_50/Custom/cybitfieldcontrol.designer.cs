namespace CyCustomizer.CyStatusReg_v1_50
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
            this.m_dgvBitFieldConfigure = new System.Windows.Forms.DataGridView();
            this.m_bClearAll = new System.Windows.Forms.Button();
            this.m_bSetAll = new System.Windows.Forms.Button();
            this.m_nudInputs = new System.Windows.Forms.NumericUpDown();
            this.m_lblInputs = new System.Windows.Forms.Label();
            this.m_lbBitMasks = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfigure)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudInputs)).BeginInit();
            this.SuspendLayout();
            // 
            // m_dgvBitFieldConfigure
            // 
            this.m_dgvBitFieldConfigure.AllowUserToResizeColumns = false;
            this.m_dgvBitFieldConfigure.AllowUserToResizeRows = false;
            this.m_dgvBitFieldConfigure.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_dgvBitFieldConfigure.Location = new System.Drawing.Point(97, 72);
            this.m_dgvBitFieldConfigure.Name = "m_dgvBitFieldConfigure";
            this.m_dgvBitFieldConfigure.RowTemplate.Height = 24;
            this.m_dgvBitFieldConfigure.Size = new System.Drawing.Size(138, 47);
            this.m_dgvBitFieldConfigure.TabIndex = 0;
            this.m_dgvBitFieldConfigure.CellContentDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_dgvBitFieldConfigure_CellContentClick);
            this.m_dgvBitFieldConfigure.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_dgvBitFieldConfigure_CellContentClick);
            // 
            // m_bClearAll
            // 
            this.m_bClearAll.Location = new System.Drawing.Point(330, 100);
            this.m_bClearAll.Name = "m_bClearAll";
            this.m_bClearAll.Size = new System.Drawing.Size(125, 23);
            this.m_bClearAll.TabIndex = 1;
            this.m_bClearAll.Text = "Set All Transparent";
            this.m_bClearAll.UseVisualStyleBackColor = true;
            this.m_bClearAll.Click += new System.EventHandler(this.m_bClearAll_Click);
            // 
            // m_bSetAll
            // 
            this.m_bSetAll.Location = new System.Drawing.Point(330, 75);
            this.m_bSetAll.Name = "m_bSetAll";
            this.m_bSetAll.Size = new System.Drawing.Size(125, 23);
            this.m_bSetAll.TabIndex = 2;
            this.m_bSetAll.Text = "Set All Sticky";
            this.m_bSetAll.UseVisualStyleBackColor = true;
            this.m_bSetAll.Click += new System.EventHandler(this.m_bSetAll_Click);
            // 
            // m_nudInputs
            // 
            this.m_nudInputs.BackColor = System.Drawing.Color.White;
            this.m_nudInputs.Location = new System.Drawing.Point(97, 36);
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
            this.m_nudInputs.TabIndex = 3;
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
            this.m_lblInputs.AutoSize = true;
            this.m_lblInputs.Location = new System.Drawing.Point(32, 38);
            this.m_lblInputs.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lblInputs.Name = "m_lblInputs";
            this.m_lblInputs.Size = new System.Drawing.Size(36, 13);
            this.m_lblInputs.TabIndex = 4;
            this.m_lblInputs.Text = "Inputs";
            // 
            // m_lbBitMasks
            // 
            this.m_lbBitMasks.AutoSize = true;
            this.m_lbBitMasks.Location = new System.Drawing.Point(32, 88);
            this.m_lbBitMasks.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.m_lbBitMasks.Name = "m_lbBitMasks";
            this.m_lbBitMasks.Size = new System.Drawing.Size(60, 13);
            this.m_lbBitMasks.TabIndex = 5;
            this.m_lbBitMasks.Text = "ModeMask";
            // 
            // CyBitfieldControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Controls.Add(this.m_lbBitMasks);
            this.Controls.Add(this.m_lblInputs);
            this.Controls.Add(this.m_nudInputs);
            this.Controls.Add(this.m_bSetAll);
            this.Controls.Add(this.m_bClearAll);
            this.Controls.Add(this.m_dgvBitFieldConfigure);
            this.MinimumSize = new System.Drawing.Size(721, 195);
            this.Name = "CyBitfieldControl";
            this.Size = new System.Drawing.Size(717, 191);
            this.VisibleChanged += new System.EventHandler(this.CyBitfieldControl_VisibleChanged);
            this.Leave += new System.EventHandler(this.CyBitfieldControl_Leave);
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvBitFieldConfigure)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudInputs)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView m_dgvBitFieldConfigure;
        private System.Windows.Forms.Button m_bClearAll;
        private System.Windows.Forms.Button m_bSetAll;
        private System.Windows.Forms.NumericUpDown m_nudInputs;
        private System.Windows.Forms.Label m_lblInputs;
        private System.Windows.Forms.Label m_lbBitMasks;
    }
}
