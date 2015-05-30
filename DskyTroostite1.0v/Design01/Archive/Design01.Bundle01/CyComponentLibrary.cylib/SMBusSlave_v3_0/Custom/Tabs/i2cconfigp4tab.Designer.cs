namespace SMBusSlave_v3_0
{
    partial class CyI2cConfigP4Tab
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
            this.lblOversamplingFactor = new System.Windows.Forms.Label();
            this.chbClockFromTerminal = new System.Windows.Forms.CheckBox();
            this.chbMedianFilter = new System.Windows.Forms.CheckBox();
            this.numOvsFactor = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numOvsFactor)).BeginInit();
            this.SuspendLayout();
            // 
            // lblOversamplingFactor
            // 
            this.lblOversamplingFactor.AutoSize = true;
            this.lblOversamplingFactor.Location = new System.Drawing.Point(4, 11);
            this.lblOversamplingFactor.Name = "lblOversamplingFactor";
            this.lblOversamplingFactor.Size = new System.Drawing.Size(104, 13);
            this.lblOversamplingFactor.TabIndex = 0;
            this.lblOversamplingFactor.Text = "Oversampling factor:";
            // 
            // chbClockFromTerminal
            // 
            this.chbClockFromTerminal.AutoSize = true;
            this.chbClockFromTerminal.Location = new System.Drawing.Point(7, 35);
            this.chbClockFromTerminal.Name = "chbClockFromTerminal";
            this.chbClockFromTerminal.Size = new System.Drawing.Size(115, 17);
            this.chbClockFromTerminal.TabIndex = 1;
            this.chbClockFromTerminal.Text = "Clock from terminal";
            this.chbClockFromTerminal.UseVisualStyleBackColor = true;
            this.chbClockFromTerminal.CheckedChanged += new System.EventHandler(this.chbClockFromTerminal_CheckedChanged);
            // 
            // chbMedianFilter
            // 
            this.chbMedianFilter.AutoSize = true;
            this.chbMedianFilter.Location = new System.Drawing.Point(7, 58);
            this.chbMedianFilter.Name = "chbMedianFilter";
            this.chbMedianFilter.Size = new System.Drawing.Size(83, 17);
            this.chbMedianFilter.TabIndex = 2;
            this.chbMedianFilter.Text = "Median filter";
            this.chbMedianFilter.UseVisualStyleBackColor = true;
            this.chbMedianFilter.CheckedChanged += new System.EventHandler(this.chbMedianFilter_CheckedChanged);
            // 
            // numOvsFactor
            // 
            this.numOvsFactor.Location = new System.Drawing.Point(114, 9);
            this.numOvsFactor.Name = "numOvsFactor";
            this.numOvsFactor.Size = new System.Drawing.Size(50, 20);
            this.numOvsFactor.TabIndex = 0;
            // 
            // CyI2cConfigP4Tab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.numOvsFactor);
            this.Controls.Add(this.chbMedianFilter);
            this.Controls.Add(this.chbClockFromTerminal);
            this.Controls.Add(this.lblOversamplingFactor);
            this.Name = "CyI2cConfigP4Tab";
            this.Size = new System.Drawing.Size(311, 286);
            ((System.ComponentModel.ISupportInitialize)(this.numOvsFactor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblOversamplingFactor;
        private System.Windows.Forms.CheckBox chbClockFromTerminal;
        private System.Windows.Forms.CheckBox chbMedianFilter;
        private System.Windows.Forms.NumericUpDown numOvsFactor;
    }
}
