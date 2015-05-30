/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



namespace USBFS_v2_60
{
    partial class CyAdvancedPage
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panelVbus = new System.Windows.Forms.Panel();
            this.radioButtonVbusInternal = new System.Windows.Forms.RadioButton();
            this.radioButtonVbusExternal = new System.Windows.Forms.RadioButton();
            this.label3 = new System.Windows.Forms.Label();
            this.labelExtVbusDesc = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBoxExtClass = new System.Windows.Forms.CheckBox();
            this.checkBoxSofOutput = new System.Windows.Forms.CheckBox();
            this.checkBoxExtVendor = new System.Windows.Forms.CheckBox();
            this.checkBoxVBusMon = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.panelVbus.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.panelVbus);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.checkBoxExtClass);
            this.groupBox1.Controls.Add(this.checkBoxSofOutput);
            this.groupBox1.Controls.Add(this.checkBoxExtVendor);
            this.groupBox1.Controls.Add(this.checkBoxVBusMon);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.MinimumSize = new System.Drawing.Size(165, 110);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(599, 305);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Parameters";
            // 
            // panelVbus
            // 
            this.panelVbus.Controls.Add(this.radioButtonVbusInternal);
            this.panelVbus.Controls.Add(this.radioButtonVbusExternal);
            this.panelVbus.Controls.Add(this.label3);
            this.panelVbus.Controls.Add(this.labelExtVbusDesc);
            this.panelVbus.Location = new System.Drawing.Point(22, 140);
            this.panelVbus.Name = "panelVbus";
            this.panelVbus.Size = new System.Drawing.Size(571, 100);
            this.panelVbus.TabIndex = 12;
            // 
            // radioButtonVbusInternal
            // 
            this.radioButtonVbusInternal.AutoSize = true;
            this.radioButtonVbusInternal.Location = new System.Drawing.Point(3, 3);
            this.radioButtonVbusInternal.Name = "radioButtonVbusInternal";
            this.radioButtonVbusInternal.Size = new System.Drawing.Size(92, 17);
            this.radioButtonVbusInternal.TabIndex = 10;
            this.radioButtonVbusInternal.TabStop = true;
            this.radioButtonVbusInternal.Text = "Internal VBUS";
            this.radioButtonVbusInternal.UseVisualStyleBackColor = true;
            this.radioButtonVbusInternal.CheckedChanged += new System.EventHandler(this.radioButtonVbus_CheckedChanged);
            // 
            // radioButtonVbusExternal
            // 
            this.radioButtonVbusExternal.AutoSize = true;
            this.radioButtonVbusExternal.Location = new System.Drawing.Point(3, 59);
            this.radioButtonVbusExternal.Name = "radioButtonVbusExternal";
            this.radioButtonVbusExternal.Size = new System.Drawing.Size(95, 17);
            this.radioButtonVbusExternal.TabIndex = 11;
            this.radioButtonVbusExternal.TabStop = true;
            this.radioButtonVbusExternal.Text = "External VBUS";
            this.radioButtonVbusExternal.UseVisualStyleBackColor = true;
            this.radioButtonVbusExternal.CheckedChanged += new System.EventHandler(this.radioButtonVbus_CheckedChanged);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label3.Location = new System.Drawing.Point(18, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(512, 28);
            this.label3.TabIndex = 6;
            this.label3.Text = "This option adds a single VBUS monitor pin to the design. This pin must be connec" +
    "ted to VBUS and must be assigned in the pin editor.";
            // 
            // labelExtVbusDesc
            // 
            this.labelExtVbusDesc.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.labelExtVbusDesc.AutoSize = true;
            this.labelExtVbusDesc.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelExtVbusDesc.Location = new System.Drawing.Point(18, 79);
            this.labelExtVbusDesc.Name = "labelExtVbusDesc";
            this.labelExtVbusDesc.Size = new System.Drawing.Size(222, 13);
            this.labelExtVbusDesc.TabIndex = 9;
            this.labelExtVbusDesc.Text = "This option enables external VBUSDET input.";
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label4.Location = new System.Drawing.Point(21, 270);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(428, 17);
            this.label4.TabIndex = 7;
            this.label4.Text = "This parameter enables Start-of-Frame output.";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label2.Location = new System.Drawing.Point(21, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(518, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "This parameter allows for user or other component to implement his own handler fo" +
    "r Vendor specific requests.";
            // 
            // checkBoxExtClass
            // 
            this.checkBoxExtClass.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxExtClass.Location = new System.Drawing.Point(6, 19);
            this.checkBoxExtClass.Name = "checkBoxExtClass";
            this.checkBoxExtClass.Size = new System.Drawing.Size(143, 17);
            this.checkBoxExtClass.TabIndex = 0;
            this.checkBoxExtClass.Text = "External Class";
            this.checkBoxExtClass.UseVisualStyleBackColor = true;
            this.checkBoxExtClass.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxSofOutput
            // 
            this.checkBoxSofOutput.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxSofOutput.Location = new System.Drawing.Point(6, 250);
            this.checkBoxSofOutput.Name = "checkBoxSofOutput";
            this.checkBoxSofOutput.Size = new System.Drawing.Size(143, 17);
            this.checkBoxSofOutput.TabIndex = 3;
            this.checkBoxSofOutput.Text = "Enable SOF Output";
            this.checkBoxSofOutput.UseVisualStyleBackColor = true;
            this.checkBoxSofOutput.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxExtVendor
            // 
            this.checkBoxExtVendor.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxExtVendor.Location = new System.Drawing.Point(6, 70);
            this.checkBoxExtVendor.Name = "checkBoxExtVendor";
            this.checkBoxExtVendor.Size = new System.Drawing.Size(143, 17);
            this.checkBoxExtVendor.TabIndex = 1;
            this.checkBoxExtVendor.Text = "External Vendor";
            this.checkBoxExtVendor.UseVisualStyleBackColor = true;
            this.checkBoxExtVendor.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // checkBoxVBusMon
            // 
            this.checkBoxVBusMon.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBoxVBusMon.Location = new System.Drawing.Point(6, 121);
            this.checkBoxVBusMon.Name = "checkBoxVBusMon";
            this.checkBoxVBusMon.Size = new System.Drawing.Size(143, 17);
            this.checkBoxVBusMon.TabIndex = 2;
            this.checkBoxVBusMon.Text = "Enable VBUS Monitoring";
            this.checkBoxVBusMon.UseVisualStyleBackColor = true;
            this.checkBoxVBusMon.CheckedChanged += new System.EventHandler(this.checkBoxExtClass_CheckedChanged);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label1.Location = new System.Drawing.Point(21, 39);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(470, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "This parameter allows for user or other component to implement his own handler fo" +
    "r Class requests.";
            // 
            // CyAdvancedPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBox1);
            this.Name = "CyAdvancedPage";
            this.Size = new System.Drawing.Size(622, 329);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panelVbus.ResumeLayout(false);
            this.panelVbus.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox checkBoxSofOutput;
        private System.Windows.Forms.CheckBox checkBoxVBusMon;
        private System.Windows.Forms.CheckBox checkBoxExtVendor;
        private System.Windows.Forms.CheckBox checkBoxExtClass;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label labelExtVbusDesc;
        private System.Windows.Forms.RadioButton radioButtonVbusExternal;
        private System.Windows.Forms.RadioButton radioButtonVbusInternal;
        private System.Windows.Forms.Panel panelVbus;
    }
}
