namespace Comp_P4_v1_0
{
    partial class CyBasicTab
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

                if (m_symbol != null)
                {
                    m_symbol.Dispose();
                }
                if (m_graph != null)
                {
                    m_graph.Dispose();
                }
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbHysteresisDisable = new System.Windows.Forms.RadioButton();
            this.rbHysteresisEnable = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rbSpeedHigh = new System.Windows.Forms.RadioButton();
            this.rbSpeedMedium = new System.Windows.Forms.RadioButton();
            this.rbSpeedSlow = new System.Windows.Forms.RadioButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rbPolarityInv = new System.Windows.Forms.RadioButton();
            this.rbPolarityNonInv = new System.Windows.Forms.RadioButton();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            this.pbGraph = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbHysteresisDisable);
            this.groupBox1.Controls.Add(this.rbHysteresisEnable);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(158, 65);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Hysteresis";
            // 
            // rbHysteresisDisable
            // 
            this.rbHysteresisDisable.AutoSize = true;
            this.rbHysteresisDisable.Location = new System.Drawing.Point(6, 42);
            this.rbHysteresisDisable.Name = "rbHysteresisDisable";
            this.rbHysteresisDisable.Size = new System.Drawing.Size(60, 17);
            this.rbHysteresisDisable.TabIndex = 2;
            this.rbHysteresisDisable.Text = "Disable";
            this.rbHysteresisDisable.UseVisualStyleBackColor = true;
            // 
            // rbHysteresisEnable
            // 
            this.rbHysteresisEnable.AutoSize = true;
            this.rbHysteresisEnable.Checked = true;
            this.rbHysteresisEnable.Location = new System.Drawing.Point(6, 19);
            this.rbHysteresisEnable.Name = "rbHysteresisEnable";
            this.rbHysteresisEnable.Size = new System.Drawing.Size(58, 17);
            this.rbHysteresisEnable.TabIndex = 0;
            this.rbHysteresisEnable.TabStop = true;
            this.rbHysteresisEnable.Text = "Enable";
            this.rbHysteresisEnable.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rbSpeedHigh);
            this.groupBox2.Controls.Add(this.rbSpeedMedium);
            this.groupBox2.Controls.Add(this.rbSpeedSlow);
            this.groupBox2.Location = new System.Drawing.Point(3, 74);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(158, 87);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Speed/power";
            // 
            // rbSpeedHigh
            // 
            this.rbSpeedHigh.AutoSize = true;
            this.rbSpeedHigh.Location = new System.Drawing.Point(6, 65);
            this.rbSpeedHigh.Name = "rbSpeedHigh";
            this.rbSpeedHigh.Size = new System.Drawing.Size(70, 17);
            this.rbSpeedHigh.TabIndex = 2;
            this.rbSpeedHigh.Text = "Fast/high";
            this.rbSpeedHigh.UseVisualStyleBackColor = true;
            // 
            // rbSpeedMedium
            // 
            this.rbSpeedMedium.AutoSize = true;
            this.rbSpeedMedium.Location = new System.Drawing.Point(6, 42);
            this.rbSpeedMedium.Name = "rbSpeedMedium";
            this.rbSpeedMedium.Size = new System.Drawing.Size(103, 17);
            this.rbSpeedMedium.TabIndex = 1;
            this.rbSpeedMedium.Text = "Medium/medium";
            this.rbSpeedMedium.UseVisualStyleBackColor = true;
            // 
            // rbSpeedSlow
            // 
            this.rbSpeedSlow.AutoSize = true;
            this.rbSpeedSlow.Checked = true;
            this.rbSpeedSlow.Location = new System.Drawing.Point(6, 19);
            this.rbSpeedSlow.Name = "rbSpeedSlow";
            this.rbSpeedSlow.Size = new System.Drawing.Size(69, 17);
            this.rbSpeedSlow.TabIndex = 0;
            this.rbSpeedSlow.TabStop = true;
            this.rbSpeedSlow.Text = "Slow/low";
            this.rbSpeedSlow.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rbPolarityInv);
            this.groupBox3.Controls.Add(this.rbPolarityNonInv);
            this.groupBox3.Location = new System.Drawing.Point(167, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(158, 65);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Polarity";
            // 
            // rbPolarityInv
            // 
            this.rbPolarityInv.AutoSize = true;
            this.rbPolarityInv.Location = new System.Drawing.Point(6, 42);
            this.rbPolarityInv.Name = "rbPolarityInv";
            this.rbPolarityInv.Size = new System.Drawing.Size(66, 17);
            this.rbPolarityInv.TabIndex = 1;
            this.rbPolarityInv.Text = "Inverting";
            this.rbPolarityInv.UseVisualStyleBackColor = true;
            // 
            // rbPolarityNonInv
            // 
            this.rbPolarityNonInv.AutoSize = true;
            this.rbPolarityNonInv.Checked = true;
            this.rbPolarityNonInv.Location = new System.Drawing.Point(6, 19);
            this.rbPolarityNonInv.Name = "rbPolarityNonInv";
            this.rbPolarityNonInv.Size = new System.Drawing.Size(88, 17);
            this.rbPolarityNonInv.TabIndex = 0;
            this.rbPolarityNonInv.TabStop = true;
            this.rbPolarityNonInv.Text = "Non-inverting";
            this.rbPolarityNonInv.UseVisualStyleBackColor = true;
            // 
            // pbSymbol
            // 
            this.pbSymbol.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbSymbol.Location = new System.Drawing.Point(331, 10);
            this.pbSymbol.Name = "pbSymbol";
            this.pbSymbol.Size = new System.Drawing.Size(100, 100);
            this.pbSymbol.TabIndex = 4;
            this.pbSymbol.TabStop = false;
            // 
            // pbGraph
            // 
            this.pbGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbGraph.Location = new System.Drawing.Point(3, 167);
            this.pbGraph.Name = "pbGraph";
            this.pbGraph.Size = new System.Drawing.Size(428, 166);
            this.pbGraph.TabIndex = 5;
            this.pbGraph.TabStop = false;
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pbGraph);
            this.Controls.Add(this.pbSymbol);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(465, 348);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbHysteresisDisable;
        private System.Windows.Forms.RadioButton rbHysteresisEnable;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rbSpeedMedium;
        private System.Windows.Forms.RadioButton rbSpeedSlow;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton rbPolarityInv;
        private System.Windows.Forms.RadioButton rbPolarityNonInv;
        private System.Windows.Forms.RadioButton rbSpeedHigh;
        private System.Windows.Forms.PictureBox pbSymbol;
        private System.Windows.Forms.PictureBox pbGraph;

    }
}
