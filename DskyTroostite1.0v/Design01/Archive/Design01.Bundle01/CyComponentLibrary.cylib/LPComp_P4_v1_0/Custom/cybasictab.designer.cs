namespace LPComp_P4_v1_0
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
            this.rbFilterDisable = new System.Windows.Forms.RadioButton();
            this.rbFilterEnable = new System.Windows.Forms.RadioButton();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.rbInterruptBoth = new System.Windows.Forms.RadioButton();
            this.rbInterruptFalling = new System.Windows.Forms.RadioButton();
            this.rbInterruptRising = new System.Windows.Forms.RadioButton();
            this.rbInterruptDisabled = new System.Windows.Forms.RadioButton();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            this.pbGraph = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
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
            this.groupBox2.Size = new System.Drawing.Size(158, 109);
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
            this.rbSpeedSlow.Size = new System.Drawing.Size(92, 17);
            this.rbSpeedSlow.TabIndex = 0;
            this.rbSpeedSlow.TabStop = true;
            this.rbSpeedSlow.Text = "Slow/ultra low";
            this.rbSpeedSlow.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rbFilterDisable);
            this.groupBox3.Controls.Add(this.rbFilterEnable);
            this.groupBox3.Location = new System.Drawing.Point(167, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(158, 65);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Digital filter";
            // 
            // rbFilterDisable
            // 
            this.rbFilterDisable.AutoSize = true;
            this.rbFilterDisable.Location = new System.Drawing.Point(6, 42);
            this.rbFilterDisable.Name = "rbFilterDisable";
            this.rbFilterDisable.Size = new System.Drawing.Size(60, 17);
            this.rbFilterDisable.TabIndex = 1;
            this.rbFilterDisable.Text = "Disable";
            this.rbFilterDisable.UseVisualStyleBackColor = true;
            // 
            // rbFilterEnable
            // 
            this.rbFilterEnable.AutoSize = true;
            this.rbFilterEnable.Checked = true;
            this.rbFilterEnable.Location = new System.Drawing.Point(6, 19);
            this.rbFilterEnable.Name = "rbFilterEnable";
            this.rbFilterEnable.Size = new System.Drawing.Size(58, 17);
            this.rbFilterEnable.TabIndex = 0;
            this.rbFilterEnable.TabStop = true;
            this.rbFilterEnable.Text = "Enable";
            this.rbFilterEnable.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.rbInterruptBoth);
            this.groupBox4.Controls.Add(this.rbInterruptFalling);
            this.groupBox4.Controls.Add(this.rbInterruptRising);
            this.groupBox4.Controls.Add(this.rbInterruptDisabled);
            this.groupBox4.Location = new System.Drawing.Point(167, 74);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(158, 109);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Interrupt";
            // 
            // rbInterruptBoth
            // 
            this.rbInterruptBoth.AutoSize = true;
            this.rbInterruptBoth.Location = new System.Drawing.Point(6, 88);
            this.rbInterruptBoth.Name = "rbInterruptBoth";
            this.rbInterruptBoth.Size = new System.Drawing.Size(79, 17);
            this.rbInterruptBoth.TabIndex = 3;
            this.rbInterruptBoth.Text = "Both edges";
            this.rbInterruptBoth.UseVisualStyleBackColor = true;
            // 
            // rbInterruptFalling
            // 
            this.rbInterruptFalling.AutoSize = true;
            this.rbInterruptFalling.Location = new System.Drawing.Point(6, 65);
            this.rbInterruptFalling.Name = "rbInterruptFalling";
            this.rbInterruptFalling.Size = new System.Drawing.Size(82, 17);
            this.rbInterruptFalling.TabIndex = 2;
            this.rbInterruptFalling.Text = "Falling edge";
            this.rbInterruptFalling.UseVisualStyleBackColor = true;
            // 
            // rbInterruptRising
            // 
            this.rbInterruptRising.AutoSize = true;
            this.rbInterruptRising.Location = new System.Drawing.Point(6, 42);
            this.rbInterruptRising.Name = "rbInterruptRising";
            this.rbInterruptRising.Size = new System.Drawing.Size(81, 17);
            this.rbInterruptRising.TabIndex = 1;
            this.rbInterruptRising.Text = "Rising edge";
            this.rbInterruptRising.UseVisualStyleBackColor = true;
            // 
            // rbInterruptDisabled
            // 
            this.rbInterruptDisabled.AutoSize = true;
            this.rbInterruptDisabled.Checked = true;
            this.rbInterruptDisabled.Location = new System.Drawing.Point(6, 19);
            this.rbInterruptDisabled.Name = "rbInterruptDisabled";
            this.rbInterruptDisabled.Size = new System.Drawing.Size(66, 17);
            this.rbInterruptDisabled.TabIndex = 0;
            this.rbInterruptDisabled.TabStop = true;
            this.rbInterruptDisabled.Text = "Disabled";
            this.rbInterruptDisabled.UseVisualStyleBackColor = true;
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
            this.pbGraph.Location = new System.Drawing.Point(3, 189);
            this.pbGraph.Name = "pbGraph";
            this.pbGraph.Size = new System.Drawing.Size(428, 210);
            this.pbGraph.TabIndex = 5;
            this.pbGraph.TabStop = false;
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pbGraph);
            this.Controls.Add(this.pbSymbol);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(447, 409);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
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
        private System.Windows.Forms.RadioButton rbFilterDisable;
        private System.Windows.Forms.RadioButton rbFilterEnable;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton rbInterruptRising;
        private System.Windows.Forms.RadioButton rbInterruptDisabled;
        private System.Windows.Forms.RadioButton rbSpeedHigh;
        private System.Windows.Forms.PictureBox pbSymbol;
        private System.Windows.Forms.PictureBox pbGraph;
        private System.Windows.Forms.RadioButton rbInterruptBoth;
        private System.Windows.Forms.RadioButton rbInterruptFalling;

    }
}
