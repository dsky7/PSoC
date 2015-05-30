namespace MDIO_Interface_v1_10
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
            this.gbConfiguration = new System.Windows.Forms.GroupBox();
            this.rbAdvancedConfig = new System.Windows.Forms.RadioButton();
            this.rbBasicConfig = new System.Windows.Forms.RadioButton();
            this.gbPhysicalAddress = new System.Windows.Forms.GroupBox();
            this.lbl0x = new System.Windows.Forms.Label();
            this.labelPhysicalAddress = new System.Windows.Forms.Label();
            this.tbPhysicalAddress = new System.Windows.Forms.TextBox();
            this.rbFirmware = new System.Windows.Forms.RadioButton();
            this.rbHardware = new System.Windows.Forms.RadioButton();
            this.cbDeviceAddress = new System.Windows.Forms.ComboBox();
            this.lblDeviceAddress = new System.Windows.Forms.Label();
            this.chbEnableExternalOE = new System.Windows.Forms.CheckBox();
            this.gbConfiguration.SuspendLayout();
            this.gbPhysicalAddress.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbConfiguration
            // 
            this.gbConfiguration.Controls.Add(this.rbAdvancedConfig);
            this.gbConfiguration.Controls.Add(this.rbBasicConfig);
            this.gbConfiguration.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbConfiguration.Location = new System.Drawing.Point(3, 3);
            this.gbConfiguration.Name = "gbConfiguration";
            this.gbConfiguration.Size = new System.Drawing.Size(177, 69);
            this.gbConfiguration.TabIndex = 0;
            this.gbConfiguration.TabStop = false;
            this.gbConfiguration.Text = "Configuration";
            // 
            // rbAdvancedConfig
            // 
            this.rbAdvancedConfig.AutoSize = true;
            this.rbAdvancedConfig.Checked = true;
            this.rbAdvancedConfig.Location = new System.Drawing.Point(6, 42);
            this.rbAdvancedConfig.Name = "rbAdvancedConfig";
            this.rbAdvancedConfig.Size = new System.Drawing.Size(74, 17);
            this.rbAdvancedConfig.TabIndex = 1;
            this.rbAdvancedConfig.TabStop = true;
            this.rbAdvancedConfig.Text = "Advanced";
            this.rbAdvancedConfig.UseVisualStyleBackColor = true;
            this.rbAdvancedConfig.CheckedChanged += new System.EventHandler(this.rbConfig_CheckedChanged);
            // 
            // rbBasicConfig
            // 
            this.rbBasicConfig.AutoSize = true;
            this.rbBasicConfig.Location = new System.Drawing.Point(6, 19);
            this.rbBasicConfig.Name = "rbBasicConfig";
            this.rbBasicConfig.Size = new System.Drawing.Size(51, 17);
            this.rbBasicConfig.TabIndex = 0;
            this.rbBasicConfig.Text = "Basic";
            this.rbBasicConfig.UseVisualStyleBackColor = true;
            this.rbBasicConfig.CheckedChanged += new System.EventHandler(this.rbConfig_CheckedChanged);
            // 
            // gbPhysicalAddress
            // 
            this.gbPhysicalAddress.Controls.Add(this.lbl0x);
            this.gbPhysicalAddress.Controls.Add(this.labelPhysicalAddress);
            this.gbPhysicalAddress.Controls.Add(this.tbPhysicalAddress);
            this.gbPhysicalAddress.Controls.Add(this.rbFirmware);
            this.gbPhysicalAddress.Controls.Add(this.rbHardware);
            this.gbPhysicalAddress.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbPhysicalAddress.Location = new System.Drawing.Point(3, 78);
            this.gbPhysicalAddress.Name = "gbPhysicalAddress";
            this.gbPhysicalAddress.Size = new System.Drawing.Size(177, 95);
            this.gbPhysicalAddress.TabIndex = 1;
            this.gbPhysicalAddress.TabStop = false;
            this.gbPhysicalAddress.Text = "Physical address";
            // 
            // lbl0x
            // 
            this.lbl0x.AutoSize = true;
            this.lbl0x.Location = new System.Drawing.Point(78, 68);
            this.lbl0x.Name = "lbl0x";
            this.lbl0x.Size = new System.Drawing.Size(18, 13);
            this.lbl0x.TabIndex = 3;
            this.lbl0x.Text = "0x";
            // 
            // labelPhysicalAddress
            // 
            this.labelPhysicalAddress.AutoSize = true;
            this.labelPhysicalAddress.Location = new System.Drawing.Point(23, 68);
            this.labelPhysicalAddress.Name = "labelPhysicalAddress";
            this.labelPhysicalAddress.Size = new System.Drawing.Size(48, 13);
            this.labelPhysicalAddress.TabIndex = 2;
            this.labelPhysicalAddress.Text = "Address:";
            // 
            // tbPhysicalAddress
            // 
            this.tbPhysicalAddress.Location = new System.Drawing.Point(97, 65);
            this.tbPhysicalAddress.Name = "tbPhysicalAddress";
            this.tbPhysicalAddress.Size = new System.Drawing.Size(49, 20);
            this.tbPhysicalAddress.TabIndex = 2;
            this.tbPhysicalAddress.TextChanged += new System.EventHandler(this.tbPhysicalAddress_TextChanged);
            // 
            // rbFirmware
            // 
            this.rbFirmware.AutoSize = true;
            this.rbFirmware.Checked = true;
            this.rbFirmware.Location = new System.Drawing.Point(6, 42);
            this.rbFirmware.Name = "rbFirmware";
            this.rbFirmware.Size = new System.Drawing.Size(67, 17);
            this.rbFirmware.TabIndex = 1;
            this.rbFirmware.TabStop = true;
            this.rbFirmware.Text = "Firmware";
            this.rbFirmware.UseVisualStyleBackColor = true;
            this.rbFirmware.CheckedChanged += new System.EventHandler(this.rbPhAddress_CheckedChanged);
            // 
            // rbHardware
            // 
            this.rbHardware.AutoSize = true;
            this.rbHardware.Location = new System.Drawing.Point(6, 19);
            this.rbHardware.Name = "rbHardware";
            this.rbHardware.Size = new System.Drawing.Size(71, 17);
            this.rbHardware.TabIndex = 0;
            this.rbHardware.Text = "Hardware";
            this.rbHardware.UseVisualStyleBackColor = true;
            this.rbHardware.CheckedChanged += new System.EventHandler(this.rbPhAddress_CheckedChanged);
            // 
            // cbDeviceAddress
            // 
            this.cbDeviceAddress.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDeviceAddress.FormattingEnabled = true;
            this.cbDeviceAddress.Location = new System.Drawing.Point(96, 179);
            this.cbDeviceAddress.Name = "cbDeviceAddress";
            this.cbDeviceAddress.Size = new System.Drawing.Size(84, 21);
            this.cbDeviceAddress.TabIndex = 2;
            this.cbDeviceAddress.SelectedIndexChanged += new System.EventHandler(this.cbDeviceAddress_SelectedIndexChanged);
            // 
            // lblDeviceAddress
            // 
            this.lblDeviceAddress.AutoSize = true;
            this.lblDeviceAddress.Location = new System.Drawing.Point(6, 182);
            this.lblDeviceAddress.Name = "lblDeviceAddress";
            this.lblDeviceAddress.Size = new System.Drawing.Size(84, 13);
            this.lblDeviceAddress.TabIndex = 4;
            this.lblDeviceAddress.Text = "Device address:";
            // 
            // chbEnableExternalOE
            // 
            this.chbEnableExternalOE.AutoSize = true;
            this.chbEnableExternalOE.Location = new System.Drawing.Point(9, 208);
            this.chbEnableExternalOE.Name = "chbEnableExternalOE";
            this.chbEnableExternalOE.Size = new System.Drawing.Size(117, 17);
            this.chbEnableExternalOE.TabIndex = 3;
            this.chbEnableExternalOE.Text = "Enable external OE";
            this.chbEnableExternalOE.UseVisualStyleBackColor = true;
            this.chbEnableExternalOE.CheckedChanged += new System.EventHandler(this.chbEnableExternalOE_CheckedChanged);
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.chbEnableExternalOE);
            this.Controls.Add(this.lblDeviceAddress);
            this.Controls.Add(this.cbDeviceAddress);
            this.Controls.Add(this.gbPhysicalAddress);
            this.Controls.Add(this.gbConfiguration);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(436, 255);
            this.gbConfiguration.ResumeLayout(false);
            this.gbConfiguration.PerformLayout();
            this.gbPhysicalAddress.ResumeLayout(false);
            this.gbPhysicalAddress.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbPhysicalAddress;
        private System.Windows.Forms.Label labelPhysicalAddress;
        private System.Windows.Forms.TextBox tbPhysicalAddress;
        private System.Windows.Forms.RadioButton rbFirmware;
        private System.Windows.Forms.RadioButton rbHardware;
        private System.Windows.Forms.GroupBox gbConfiguration;
        private System.Windows.Forms.RadioButton rbAdvancedConfig;
        private System.Windows.Forms.RadioButton rbBasicConfig;
        private System.Windows.Forms.ComboBox cbDeviceAddress;
        private System.Windows.Forms.Label lblDeviceAddress;
        private System.Windows.Forms.CheckBox chbEnableExternalOE;
        private System.Windows.Forms.Label lbl0x;
    }
}
