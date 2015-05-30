namespace OpAmp_P4_v1_0
{
    partial class CyConfigureTab
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
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.gbOutput = new System.Windows.Forms.GroupBox();
            this.rbOutput10mA = new System.Windows.Forms.RadioButton();
            this.rbOutput1mA = new System.Windows.Forms.RadioButton();
            this.gbPower = new System.Windows.Forms.GroupBox();
            this.rbSpeedHigh = new System.Windows.Forms.RadioButton();
            this.rbSpeedMedium = new System.Windows.Forms.RadioButton();
            this.rbSpeedSlow = new System.Windows.Forms.RadioButton();
            this.gbMode = new System.Windows.Forms.GroupBox();
            this.rbModeFollower = new System.Windows.Forms.RadioButton();
            this.rbModeOpamp = new System.Windows.Forms.RadioButton();
            this.m_grpCompensation = new System.Windows.Forms.GroupBox();
            this.m_rbHighSpeed = new System.Windows.Forms.RadioButton();
            this.m_rbBalanced = new System.Windows.Forms.RadioButton();
            this.m_rbHighStability = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.gbOutput.SuspendLayout();
            this.gbPower.SuspendLayout();
            this.gbMode.SuspendLayout();
            this.m_grpCompensation.SuspendLayout();
            this.SuspendLayout();
            // 
            // errorProvider
            // 
            this.errorProvider.ContainerControl = this;
            // 
            // gbOutput
            // 
            this.gbOutput.Controls.Add(this.rbOutput10mA);
            this.gbOutput.Controls.Add(this.rbOutput1mA);
            this.gbOutput.Location = new System.Drawing.Point(13, 167);
            this.gbOutput.Name = "gbOutput";
            this.gbOutput.Size = new System.Drawing.Size(158, 65);
            this.gbOutput.TabIndex = 7;
            this.gbOutput.TabStop = false;
            this.gbOutput.Text = "Output";
            // 
            // rbOutput10mA
            // 
            this.rbOutput10mA.AutoSize = true;
            this.rbOutput10mA.Location = new System.Drawing.Point(6, 42);
            this.rbOutput10mA.Name = "rbOutput10mA";
            this.rbOutput10mA.Size = new System.Drawing.Size(55, 17);
            this.rbOutput10mA.TabIndex = 1;
            this.rbOutput10mA.Text = "10 mA";
            this.rbOutput10mA.UseVisualStyleBackColor = true;
            // 
            // rbOutput1mA
            // 
            this.rbOutput1mA.AutoSize = true;
            this.rbOutput1mA.Checked = true;
            this.rbOutput1mA.Location = new System.Drawing.Point(6, 19);
            this.rbOutput1mA.Name = "rbOutput1mA";
            this.rbOutput1mA.Size = new System.Drawing.Size(49, 17);
            this.rbOutput1mA.TabIndex = 0;
            this.rbOutput1mA.TabStop = true;
            this.rbOutput1mA.Text = "1 mA";
            this.rbOutput1mA.UseVisualStyleBackColor = true;
            // 
            // gbPower
            // 
            this.gbPower.Controls.Add(this.rbSpeedHigh);
            this.gbPower.Controls.Add(this.rbSpeedMedium);
            this.gbPower.Controls.Add(this.rbSpeedSlow);
            this.gbPower.Location = new System.Drawing.Point(13, 74);
            this.gbPower.Name = "gbPower";
            this.gbPower.Size = new System.Drawing.Size(158, 87);
            this.gbPower.TabIndex = 8;
            this.gbPower.TabStop = false;
            this.gbPower.Text = "Power";
            // 
            // rbSpeedHigh
            // 
            this.rbSpeedHigh.AutoSize = true;
            this.rbSpeedHigh.Location = new System.Drawing.Point(6, 65);
            this.rbSpeedHigh.Name = "rbSpeedHigh";
            this.rbSpeedHigh.Size = new System.Drawing.Size(47, 17);
            this.rbSpeedHigh.TabIndex = 2;
            this.rbSpeedHigh.Text = "High";
            this.rbSpeedHigh.UseVisualStyleBackColor = true;
            // 
            // rbSpeedMedium
            // 
            this.rbSpeedMedium.AutoSize = true;
            this.rbSpeedMedium.Location = new System.Drawing.Point(6, 42);
            this.rbSpeedMedium.Name = "rbSpeedMedium";
            this.rbSpeedMedium.Size = new System.Drawing.Size(62, 17);
            this.rbSpeedMedium.TabIndex = 1;
            this.rbSpeedMedium.Text = "Medium";
            this.rbSpeedMedium.UseVisualStyleBackColor = true;
            // 
            // rbSpeedSlow
            // 
            this.rbSpeedSlow.AutoSize = true;
            this.rbSpeedSlow.Checked = true;
            this.rbSpeedSlow.Location = new System.Drawing.Point(6, 19);
            this.rbSpeedSlow.Name = "rbSpeedSlow";
            this.rbSpeedSlow.Size = new System.Drawing.Size(45, 17);
            this.rbSpeedSlow.TabIndex = 0;
            this.rbSpeedSlow.TabStop = true;
            this.rbSpeedSlow.Text = "Low";
            this.rbSpeedSlow.UseVisualStyleBackColor = true;
            // 
            // gbMode
            // 
            this.gbMode.Controls.Add(this.rbModeFollower);
            this.gbMode.Controls.Add(this.rbModeOpamp);
            this.gbMode.Location = new System.Drawing.Point(13, 3);
            this.gbMode.Name = "gbMode";
            this.gbMode.Size = new System.Drawing.Size(158, 65);
            this.gbMode.TabIndex = 6;
            this.gbMode.TabStop = false;
            this.gbMode.Text = "Mode";
            // 
            // rbModeFollower
            // 
            this.rbModeFollower.AutoSize = true;
            this.rbModeFollower.Location = new System.Drawing.Point(6, 42);
            this.rbModeFollower.Name = "rbModeFollower";
            this.rbModeFollower.Size = new System.Drawing.Size(64, 17);
            this.rbModeFollower.TabIndex = 2;
            this.rbModeFollower.Text = "Follower";
            this.rbModeFollower.UseVisualStyleBackColor = true;
            // 
            // rbModeOpamp
            // 
            this.rbModeOpamp.AutoSize = true;
            this.rbModeOpamp.Checked = true;
            this.rbModeOpamp.Location = new System.Drawing.Point(6, 19);
            this.rbModeOpamp.Name = "rbModeOpamp";
            this.rbModeOpamp.Size = new System.Drawing.Size(60, 17);
            this.rbModeOpamp.TabIndex = 0;
            this.rbModeOpamp.TabStop = true;
            this.rbModeOpamp.Text = "OpAmp";
            this.rbModeOpamp.UseVisualStyleBackColor = true;
            // 
            // m_grpCompensation
            // 
            this.m_grpCompensation.Controls.Add(this.m_rbHighStability);
            this.m_grpCompensation.Controls.Add(this.m_rbBalanced);
            this.m_grpCompensation.Controls.Add(this.m_rbHighSpeed);
            this.m_grpCompensation.Location = new System.Drawing.Point(177, 3);
            this.m_grpCompensation.Name = "m_grpCompensation";
            this.m_grpCompensation.Size = new System.Drawing.Size(132, 88);
            this.m_grpCompensation.TabIndex = 9;
            this.m_grpCompensation.TabStop = false;
            this.m_grpCompensation.Text = "Compensation";
            // 
            // m_rbHighSpeed
            // 
            this.m_rbHighSpeed.AutoSize = true;
            this.m_rbHighSpeed.Location = new System.Drawing.Point(6, 19);
            this.m_rbHighSpeed.Name = "m_rbHighSpeed";
            this.m_rbHighSpeed.Size = new System.Drawing.Size(79, 17);
            this.m_rbHighSpeed.TabIndex = 0;
            this.m_rbHighSpeed.TabStop = true;
            this.m_rbHighSpeed.Text = "High speed";
            this.m_rbHighSpeed.UseVisualStyleBackColor = true;
            // 
            // m_rbBalanced
            // 
            this.m_rbBalanced.AutoSize = true;
            this.m_rbBalanced.Location = new System.Drawing.Point(6, 42);
            this.m_rbBalanced.Name = "m_rbBalanced";
            this.m_rbBalanced.Size = new System.Drawing.Size(70, 17);
            this.m_rbBalanced.TabIndex = 1;
            this.m_rbBalanced.TabStop = true;
            this.m_rbBalanced.Text = "Balanced";
            this.m_rbBalanced.UseVisualStyleBackColor = true;
            // 
            // m_rbHighStability
            // 
            this.m_rbHighStability.AutoSize = true;
            this.m_rbHighStability.Location = new System.Drawing.Point(6, 65);
            this.m_rbHighStability.Name = "m_rbHighStability";
            this.m_rbHighStability.Size = new System.Drawing.Size(84, 17);
            this.m_rbHighStability.TabIndex = 2;
            this.m_rbHighStability.TabStop = true;
            this.m_rbHighStability.Text = "High stability";
            this.m_rbHighStability.UseVisualStyleBackColor = true;
            // 
            // CyConfigureTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpCompensation);
            this.Controls.Add(this.gbOutput);
            this.Controls.Add(this.gbPower);
            this.Controls.Add(this.gbMode);
            this.Name = "CyConfigureTab";
            this.Size = new System.Drawing.Size(466, 284);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.gbOutput.ResumeLayout(false);
            this.gbOutput.PerformLayout();
            this.gbPower.ResumeLayout(false);
            this.gbPower.PerformLayout();
            this.gbMode.ResumeLayout(false);
            this.gbMode.PerformLayout();
            this.m_grpCompensation.ResumeLayout(false);
            this.m_grpCompensation.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.GroupBox gbOutput;
        private System.Windows.Forms.RadioButton rbOutput10mA;
        private System.Windows.Forms.RadioButton rbOutput1mA;
        private System.Windows.Forms.GroupBox gbPower;
        private System.Windows.Forms.RadioButton rbSpeedHigh;
        private System.Windows.Forms.RadioButton rbSpeedMedium;
        private System.Windows.Forms.RadioButton rbSpeedSlow;
        private System.Windows.Forms.GroupBox gbMode;
        private System.Windows.Forms.RadioButton rbModeFollower;
        private System.Windows.Forms.RadioButton rbModeOpamp;
        private System.Windows.Forms.GroupBox m_grpCompensation;
        private System.Windows.Forms.RadioButton m_rbHighSpeed;
        private System.Windows.Forms.RadioButton m_rbHighStability;
        private System.Windows.Forms.RadioButton m_rbBalanced;
    }
}
