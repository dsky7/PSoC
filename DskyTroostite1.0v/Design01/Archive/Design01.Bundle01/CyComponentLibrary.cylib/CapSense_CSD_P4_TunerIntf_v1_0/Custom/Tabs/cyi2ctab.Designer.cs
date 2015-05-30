namespace CapSense_CSD_P4_TunerIntf_v1_0
{
    partial class CyI2CTab
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
            this.m_rbNoWaitStates = new System.Windows.Forms.RadioButton();
            this.m_rbWaitStates = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.m_panInternalClockConfig = new System.Windows.Forms.Panel();
            this.m_chbClkFromTerm = new System.Windows.Forms.CheckBox();
            this.m_numOvsFactor = new System.Windows.Forms.NumericUpDown();
            this.m_lblDataRate = new System.Windows.Forms.Label();
            this.m_lblOvsFactor = new System.Windows.Forms.Label();
            this.m_cbDataRate = new System.Windows.Forms.ComboBox();
            this.m_lblActualDataRate = new System.Windows.Forms.Label();
            this.m_chbEnMedianFilter = new System.Windows.Forms.CheckBox();
            this.m_cbClkMode = new System.Windows.Forms.ComboBox();
            this.m_lblClkMode = new System.Windows.Forms.Label();
            this.m_grpCollideBehavior = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.m_chbEnableWakeup = new System.Windows.Forms.CheckBox();
            this.m_grpWakeUp = new System.Windows.Forms.GroupBox();
            this.m_rbAddressAck = new System.Windows.Forms.RadioButton();
            this.m_rbAddressNack = new System.Windows.Forms.RadioButton();
            this.m_binaryGridSlaveAddressMask = new CapSense_CSD_P4_TunerIntf_v1_0.CyBinaryGrid();
            this.m_binaryGridSlaveAddress = new CapSense_CSD_P4_TunerIntf_v1_0.CyBinaryGrid();
            this.m_lblSlaveAddress = new System.Windows.Forms.Label();
            this.m_lblBit0 = new System.Windows.Forms.Label();
            this.m_lblSeparator = new System.Windows.Forms.Label();
            this.m_lblBit1 = new System.Windows.Forms.Label();
            this.m_tbSlaveAddress = new System.Windows.Forms.TextBox();
            this.m_lblSlaveAddrMask = new System.Windows.Forms.Label();
            this.m_lblBit7 = new System.Windows.Forms.Label();
            this.m_lblBit = new System.Windows.Forms.Label();
            this.m_tbSlaveAddressMask = new System.Windows.Forms.TextBox();
            this.m_lblBit2 = new System.Windows.Forms.Label();
            this.m_lblBit6 = new System.Windows.Forms.Label();
            this.m_lblBit5 = new System.Windows.Forms.Label();
            this.m_lblBit3 = new System.Windows.Forms.Label();
            this.m_lblBit4 = new System.Windows.Forms.Label();
            this.m_lblSeparator1 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.m_panInternalClockConfig.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).BeginInit();
            this.m_grpCollideBehavior.SuspendLayout();
            this.panel2.SuspendLayout();
            this.m_grpWakeUp.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_rbNoWaitStates
            // 
            this.m_rbNoWaitStates.AutoSize = true;
            this.m_rbNoWaitStates.Location = new System.Drawing.Point(8, 52);
            this.m_rbNoWaitStates.Margin = new System.Windows.Forms.Padding(4);
            this.m_rbNoWaitStates.Name = "m_rbNoWaitStates";
            this.m_rbNoWaitStates.Size = new System.Drawing.Size(117, 21);
            this.m_rbNoWaitStates.TabIndex = 1;
            this.m_rbNoWaitStates.TabStop = true;
            this.m_rbNoWaitStates.Text = "No wait states";
            this.m_rbNoWaitStates.UseVisualStyleBackColor = true;
            // 
            // m_rbWaitStates
            // 
            this.m_rbWaitStates.AutoSize = true;
            this.m_rbWaitStates.Location = new System.Drawing.Point(8, 23);
            this.m_rbWaitStates.Margin = new System.Windows.Forms.Padding(4);
            this.m_rbWaitStates.Name = "m_rbWaitStates";
            this.m_rbWaitStates.Size = new System.Drawing.Size(99, 21);
            this.m_rbWaitStates.TabIndex = 0;
            this.m_rbWaitStates.TabStop = true;
            this.m_rbWaitStates.Text = "Wait states";
            this.m_rbWaitStates.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.m_panInternalClockConfig);
            this.panel1.Controls.Add(this.m_cbClkMode);
            this.panel1.Controls.Add(this.m_lblClkMode);
            this.panel1.Location = new System.Drawing.Point(4, 4);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(563, 153);
            this.panel1.TabIndex = 0;
            // 
            // m_panInternalClockConfig
            // 
            this.m_panInternalClockConfig.Controls.Add(this.m_chbClkFromTerm);
            this.m_panInternalClockConfig.Controls.Add(this.m_numOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_cbDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblActualDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_chbEnMedianFilter);
            this.m_panInternalClockConfig.Location = new System.Drawing.Point(4, 30);
            this.m_panInternalClockConfig.Margin = new System.Windows.Forms.Padding(4);
            this.m_panInternalClockConfig.Name = "m_panInternalClockConfig";
            this.m_panInternalClockConfig.Size = new System.Drawing.Size(555, 123);
            this.m_panInternalClockConfig.TabIndex = 2;
            // 
            // m_chbClkFromTerm
            // 
            this.m_chbClkFromTerm.AutoSize = true;
            this.m_chbClkFromTerm.Location = new System.Drawing.Point(4, 73);
            this.m_chbClkFromTerm.Margin = new System.Windows.Forms.Padding(4);
            this.m_chbClkFromTerm.Name = "m_chbClkFromTerm";
            this.m_chbClkFromTerm.Size = new System.Drawing.Size(150, 21);
            this.m_chbClkFromTerm.TabIndex = 3;
            this.m_chbClkFromTerm.Text = "Clock from terminal";
            this.m_chbClkFromTerm.UseVisualStyleBackColor = true;
            // 
            // m_numOvsFactor
            // 
            this.m_numOvsFactor.Location = new System.Drawing.Point(147, 41);
            this.m_numOvsFactor.Margin = new System.Windows.Forms.Padding(4);
            this.m_numOvsFactor.Name = "m_numOvsFactor";
            this.m_numOvsFactor.Size = new System.Drawing.Size(72, 22);
            this.m_numOvsFactor.TabIndex = 2;
            // 
            // m_lblDataRate
            // 
            this.m_lblDataRate.AutoSize = true;
            this.m_lblDataRate.Location = new System.Drawing.Point(0, 11);
            this.m_lblDataRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblDataRate.Name = "m_lblDataRate";
            this.m_lblDataRate.Size = new System.Drawing.Size(115, 17);
            this.m_lblDataRate.TabIndex = 0;
            this.m_lblDataRate.Text = "Data rate (kbps):";
            // 
            // m_lblOvsFactor
            // 
            this.m_lblOvsFactor.AutoSize = true;
            this.m_lblOvsFactor.Location = new System.Drawing.Point(0, 43);
            this.m_lblOvsFactor.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblOvsFactor.Name = "m_lblOvsFactor";
            this.m_lblOvsFactor.Size = new System.Drawing.Size(139, 17);
            this.m_lblOvsFactor.TabIndex = 0;
            this.m_lblOvsFactor.Text = "Oversampling factor:";
            // 
            // m_cbDataRate
            // 
            this.m_cbDataRate.FormattingEnabled = true;
            this.m_cbDataRate.Items.AddRange(new object[] {
            "50",
            "100",
            "400",
            "1000"});
            this.m_cbDataRate.Location = new System.Drawing.Point(147, 7);
            this.m_cbDataRate.Margin = new System.Windows.Forms.Padding(4);
            this.m_cbDataRate.Name = "m_cbDataRate";
            this.m_cbDataRate.Size = new System.Drawing.Size(72, 24);
            this.m_cbDataRate.TabIndex = 1;
            // 
            // m_lblActualDataRate
            // 
            this.m_lblActualDataRate.AutoSize = true;
            this.m_lblActualDataRate.Location = new System.Drawing.Point(239, 11);
            this.m_lblActualDataRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblActualDataRate.Name = "m_lblActualDataRate";
            this.m_lblActualDataRate.Size = new System.Drawing.Size(233, 17);
            this.m_lblActualDataRate.TabIndex = 0;
            this.m_lblActualDataRate.Text = "Actual data rate (kbps): UNKNOWN";
            // 
            // m_chbEnMedianFilter
            // 
            this.m_chbEnMedianFilter.AutoSize = true;
            this.m_chbEnMedianFilter.Location = new System.Drawing.Point(4, 101);
            this.m_chbEnMedianFilter.Margin = new System.Windows.Forms.Padding(4);
            this.m_chbEnMedianFilter.Name = "m_chbEnMedianFilter";
            this.m_chbEnMedianFilter.Size = new System.Drawing.Size(107, 21);
            this.m_chbEnMedianFilter.TabIndex = 4;
            this.m_chbEnMedianFilter.Text = "Median filter";
            this.m_chbEnMedianFilter.UseVisualStyleBackColor = true;
            // 
            // m_cbClkMode
            // 
            this.m_cbClkMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbClkMode.Enabled = false;
            this.m_cbClkMode.FormattingEnabled = true;
            this.m_cbClkMode.Location = new System.Drawing.Point(151, 4);
            this.m_cbClkMode.Margin = new System.Windows.Forms.Padding(4);
            this.m_cbClkMode.Name = "m_cbClkMode";
            this.m_cbClkMode.Size = new System.Drawing.Size(151, 24);
            this.m_cbClkMode.TabIndex = 1;
            // 
            // m_lblClkMode
            // 
            this.m_lblClkMode.AutoSize = true;
            this.m_lblClkMode.Enabled = false;
            this.m_lblClkMode.Location = new System.Drawing.Point(4, 7);
            this.m_lblClkMode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblClkMode.Name = "m_lblClkMode";
            this.m_lblClkMode.Size = new System.Drawing.Size(114, 17);
            this.m_lblClkMode.TabIndex = 0;
            this.m_lblClkMode.Text = "Operation mode:";
            // 
            // m_grpCollideBehavior
            // 
            this.m_grpCollideBehavior.Controls.Add(this.m_rbNoWaitStates);
            this.m_grpCollideBehavior.Controls.Add(this.m_rbWaitStates);
            this.m_grpCollideBehavior.Location = new System.Drawing.Point(309, 114);
            this.m_grpCollideBehavior.Margin = new System.Windows.Forms.Padding(4);
            this.m_grpCollideBehavior.Name = "m_grpCollideBehavior";
            this.m_grpCollideBehavior.Padding = new System.Windows.Forms.Padding(4);
            this.m_grpCollideBehavior.Size = new System.Drawing.Size(167, 86);
            this.m_grpCollideBehavior.TabIndex = 6;
            this.m_grpCollideBehavior.TabStop = false;
            this.m_grpCollideBehavior.Text = "Collide behavior";
            this.m_grpCollideBehavior.Visible = false;
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.Controls.Add(this.m_chbEnableWakeup);
            this.panel2.Controls.Add(this.m_grpWakeUp);
            this.panel2.Controls.Add(this.m_grpCollideBehavior);
            this.panel2.Controls.Add(this.m_binaryGridSlaveAddressMask);
            this.panel2.Controls.Add(this.m_binaryGridSlaveAddress);
            this.panel2.Controls.Add(this.m_lblSlaveAddress);
            this.panel2.Controls.Add(this.m_lblBit0);
            this.panel2.Controls.Add(this.m_lblSeparator);
            this.panel2.Controls.Add(this.m_lblBit1);
            this.panel2.Controls.Add(this.m_tbSlaveAddress);
            this.panel2.Controls.Add(this.m_lblSlaveAddrMask);
            this.panel2.Controls.Add(this.m_lblBit7);
            this.panel2.Controls.Add(this.m_lblBit);
            this.panel2.Controls.Add(this.m_tbSlaveAddressMask);
            this.panel2.Controls.Add(this.m_lblBit2);
            this.panel2.Controls.Add(this.m_lblBit6);
            this.panel2.Controls.Add(this.m_lblBit5);
            this.panel2.Controls.Add(this.m_lblBit3);
            this.panel2.Controls.Add(this.m_lblBit4);
            this.panel2.Location = new System.Drawing.Point(4, 166);
            this.panel2.Margin = new System.Windows.Forms.Padding(4);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(563, 213);
            this.panel2.TabIndex = 1;
            // 
            // m_chbEnableWakeup
            // 
            this.m_chbEnableWakeup.AutoSize = true;
            this.m_chbEnableWakeup.Location = new System.Drawing.Point(15, 114);
            this.m_chbEnableWakeup.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.m_chbEnableWakeup.Name = "m_chbEnableWakeup";
            this.m_chbEnableWakeup.Size = new System.Drawing.Size(237, 21);
            this.m_chbEnableWakeup.TabIndex = 4;
            this.m_chbEnableWakeup.Text = "Enable wakeup from Sleep Mode";
            this.m_chbEnableWakeup.UseVisualStyleBackColor = true;
            this.m_chbEnableWakeup.Visible = false;
            // 
            // m_grpWakeUp
            // 
            this.m_grpWakeUp.Controls.Add(this.m_rbAddressAck);
            this.m_grpWakeUp.Controls.Add(this.m_rbAddressNack);
            this.m_grpWakeUp.Location = new System.Drawing.Point(4, 117);
            this.m_grpWakeUp.Margin = new System.Windows.Forms.Padding(4);
            this.m_grpWakeUp.Name = "m_grpWakeUp";
            this.m_grpWakeUp.Padding = new System.Windows.Forms.Padding(4);
            this.m_grpWakeUp.Size = new System.Drawing.Size(271, 84);
            this.m_grpWakeUp.TabIndex = 5;
            this.m_grpWakeUp.TabStop = false;
            this.m_grpWakeUp.Visible = false;
            // 
            // m_rbAddressAck
            // 
            this.m_rbAddressAck.AutoSize = true;
            this.m_rbAddressAck.Location = new System.Drawing.Point(23, 25);
            this.m_rbAddressAck.Margin = new System.Windows.Forms.Padding(4);
            this.m_rbAddressAck.Name = "m_rbAddressAck";
            this.m_rbAddressAck.Size = new System.Drawing.Size(110, 21);
            this.m_rbAddressAck.TabIndex = 0;
            this.m_rbAddressAck.TabStop = true;
            this.m_rbAddressAck.Text = "Clock stretch";
            this.m_rbAddressAck.UseVisualStyleBackColor = false;
            // 
            // m_rbAddressNack
            // 
            this.m_rbAddressNack.AutoSize = true;
            this.m_rbAddressNack.Location = new System.Drawing.Point(23, 53);
            this.m_rbAddressNack.Margin = new System.Windows.Forms.Padding(4);
            this.m_rbAddressNack.Name = "m_rbAddressNack";
            this.m_rbAddressNack.Size = new System.Drawing.Size(122, 21);
            this.m_rbAddressNack.TabIndex = 1;
            this.m_rbAddressNack.TabStop = true;
            this.m_rbAddressNack.Text = "Address NACK";
            this.m_rbAddressNack.UseVisualStyleBackColor = true;
            // 
            // m_binaryGridSlaveAddressMask
            // 
            this.m_binaryGridSlaveAddressMask.Bits = new string[] {
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0"};
            this.m_binaryGridSlaveAddressMask.Location = new System.Drawing.Point(309, 69);
            this.m_binaryGridSlaveAddressMask.Margin = new System.Windows.Forms.Padding(5);
            this.m_binaryGridSlaveAddressMask.Name = "m_binaryGridSlaveAddressMask";
            this.m_binaryGridSlaveAddressMask.NumberOfBits = 8;
            this.m_binaryGridSlaveAddressMask.Size = new System.Drawing.Size(221, 25);
            this.m_binaryGridSlaveAddressMask.TabIndex = 3;
            this.m_binaryGridSlaveAddressMask.TabStop = false;
            // 
            // m_binaryGridSlaveAddress
            // 
            this.m_binaryGridSlaveAddress.Bits = new string[] {
        "1",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "X"};
            this.m_binaryGridSlaveAddress.Location = new System.Drawing.Point(309, 33);
            this.m_binaryGridSlaveAddress.Margin = new System.Windows.Forms.Padding(5);
            this.m_binaryGridSlaveAddress.Name = "m_binaryGridSlaveAddress";
            this.m_binaryGridSlaveAddress.NumberOfBits = 8;
            this.m_binaryGridSlaveAddress.Size = new System.Drawing.Size(221, 25);
            this.m_binaryGridSlaveAddress.TabIndex = 1;
            this.m_binaryGridSlaveAddress.TabStop = false;
            // 
            // m_lblSlaveAddress
            // 
            this.m_lblSlaveAddress.AutoSize = true;
            this.m_lblSlaveAddress.Location = new System.Drawing.Point(5, 37);
            this.m_lblSlaveAddress.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSlaveAddress.Name = "m_lblSlaveAddress";
            this.m_lblSlaveAddress.Size = new System.Drawing.Size(151, 17);
            this.m_lblSlaveAddress.TabIndex = 0;
            this.m_lblSlaveAddress.Text = "Slave address (7-bits):";
            // 
            // m_lblBit0
            // 
            this.m_lblBit0.AutoSize = true;
            this.m_lblBit0.Location = new System.Drawing.Point(507, 14);
            this.m_lblBit0.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit0.Name = "m_lblBit0";
            this.m_lblBit0.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit0.TabIndex = 0;
            this.m_lblBit0.Text = "0";
            // 
            // m_lblSeparator
            // 
            this.m_lblSeparator.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSeparator.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator.Location = new System.Drawing.Point(0, 105);
            this.m_lblSeparator.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSeparator.Name = "m_lblSeparator";
            this.m_lblSeparator.Size = new System.Drawing.Size(563, 2);
            this.m_lblSeparator.TabIndex = 6;
            this.m_lblSeparator.Visible = false;
            // 
            // m_lblBit1
            // 
            this.m_lblBit1.AutoSize = true;
            this.m_lblBit1.Location = new System.Drawing.Point(479, 14);
            this.m_lblBit1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit1.Name = "m_lblBit1";
            this.m_lblBit1.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit1.TabIndex = 0;
            this.m_lblBit1.Text = "1";
            // 
            // m_tbSlaveAddress
            // 
            this.m_tbSlaveAddress.Location = new System.Drawing.Point(175, 33);
            this.m_tbSlaveAddress.Margin = new System.Windows.Forms.Padding(4);
            this.m_tbSlaveAddress.Name = "m_tbSlaveAddress";
            this.m_tbSlaveAddress.Size = new System.Drawing.Size(65, 22);
            this.m_tbSlaveAddress.TabIndex = 0;
            // 
            // m_lblSlaveAddrMask
            // 
            this.m_lblSlaveAddrMask.AutoSize = true;
            this.m_lblSlaveAddrMask.Location = new System.Drawing.Point(5, 73);
            this.m_lblSlaveAddrMask.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSlaveAddrMask.Name = "m_lblSlaveAddrMask";
            this.m_lblSlaveAddrMask.Size = new System.Drawing.Size(139, 17);
            this.m_lblSlaveAddrMask.TabIndex = 0;
            this.m_lblSlaveAddrMask.Text = "Slave address mask:";
            // 
            // m_lblBit7
            // 
            this.m_lblBit7.AutoSize = true;
            this.m_lblBit7.Location = new System.Drawing.Point(311, 14);
            this.m_lblBit7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit7.Name = "m_lblBit7";
            this.m_lblBit7.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit7.TabIndex = 0;
            this.m_lblBit7.Text = "7";
            // 
            // m_lblBit
            // 
            this.m_lblBit.AutoSize = true;
            this.m_lblBit.Location = new System.Drawing.Point(276, 14);
            this.m_lblBit.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit.Name = "m_lblBit";
            this.m_lblBit.Size = new System.Drawing.Size(24, 17);
            this.m_lblBit.TabIndex = 0;
            this.m_lblBit.Text = "Bit";
            // 
            // m_tbSlaveAddressMask
            // 
            this.m_tbSlaveAddressMask.Location = new System.Drawing.Point(175, 69);
            this.m_tbSlaveAddressMask.Margin = new System.Windows.Forms.Padding(4);
            this.m_tbSlaveAddressMask.MaxLength = 5;
            this.m_tbSlaveAddressMask.Name = "m_tbSlaveAddressMask";
            this.m_tbSlaveAddressMask.Size = new System.Drawing.Size(65, 22);
            this.m_tbSlaveAddressMask.TabIndex = 2;
            // 
            // m_lblBit2
            // 
            this.m_lblBit2.AutoSize = true;
            this.m_lblBit2.Location = new System.Drawing.Point(451, 14);
            this.m_lblBit2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit2.Name = "m_lblBit2";
            this.m_lblBit2.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit2.TabIndex = 0;
            this.m_lblBit2.Text = "2";
            // 
            // m_lblBit6
            // 
            this.m_lblBit6.AutoSize = true;
            this.m_lblBit6.Location = new System.Drawing.Point(339, 14);
            this.m_lblBit6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit6.Name = "m_lblBit6";
            this.m_lblBit6.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit6.TabIndex = 0;
            this.m_lblBit6.Text = "6";
            // 
            // m_lblBit5
            // 
            this.m_lblBit5.AutoSize = true;
            this.m_lblBit5.Location = new System.Drawing.Point(367, 14);
            this.m_lblBit5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit5.Name = "m_lblBit5";
            this.m_lblBit5.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit5.TabIndex = 0;
            this.m_lblBit5.Text = "5";
            // 
            // m_lblBit3
            // 
            this.m_lblBit3.AutoSize = true;
            this.m_lblBit3.Location = new System.Drawing.Point(423, 14);
            this.m_lblBit3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit3.Name = "m_lblBit3";
            this.m_lblBit3.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit3.TabIndex = 0;
            this.m_lblBit3.Text = "3";
            // 
            // m_lblBit4
            // 
            this.m_lblBit4.AutoSize = true;
            this.m_lblBit4.Location = new System.Drawing.Point(395, 14);
            this.m_lblBit4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblBit4.Name = "m_lblBit4";
            this.m_lblBit4.Size = new System.Drawing.Size(16, 17);
            this.m_lblBit4.TabIndex = 0;
            this.m_lblBit4.Text = "4";
            // 
            // m_lblSeparator1
            // 
            this.m_lblSeparator1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblSeparator1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_lblSeparator1.Location = new System.Drawing.Point(4, 160);
            this.m_lblSeparator1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.m_lblSeparator1.Name = "m_lblSeparator1";
            this.m_lblSeparator1.Size = new System.Drawing.Size(563, 2);
            this.m_lblSeparator1.TabIndex = 1;
            // 
            // CyEZBufferedI2CTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.m_lblSeparator1);
            this.Controls.Add(this.panel2);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyEZBufferedI2CTab";
            this.Size = new System.Drawing.Size(571, 383);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.m_panInternalClockConfig.ResumeLayout(false);
            this.m_panInternalClockConfig.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).EndInit();
            this.m_grpCollideBehavior.ResumeLayout(false);
            this.m_grpCollideBehavior.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.m_grpWakeUp.ResumeLayout(false);
            this.m_grpWakeUp.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RadioButton m_rbNoWaitStates;
        private System.Windows.Forms.RadioButton m_rbWaitStates;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label m_lblActualDataRate;
        private System.Windows.Forms.CheckBox m_chbEnMedianFilter;
        private System.Windows.Forms.Panel panel2;
        private CyBinaryGrid m_binaryGridSlaveAddressMask;
        private CyBinaryGrid m_binaryGridSlaveAddress;
        private System.Windows.Forms.Label m_lblSlaveAddress;
        private System.Windows.Forms.Label m_lblBit0;
        private System.Windows.Forms.RadioButton m_rbAddressNack;
        private System.Windows.Forms.Label m_lblBit1;
        private System.Windows.Forms.RadioButton m_rbAddressAck;
        private System.Windows.Forms.TextBox m_tbSlaveAddress;
        public System.Windows.Forms.CheckBox m_chbEnableWakeup;
        private System.Windows.Forms.Label m_lblSlaveAddrMask;
        private System.Windows.Forms.Label m_lblBit7;
        private System.Windows.Forms.Label m_lblBit;
        public System.Windows.Forms.TextBox m_tbSlaveAddressMask;
        private System.Windows.Forms.Label m_lblBit2;
        private System.Windows.Forms.Label m_lblBit6;
        private System.Windows.Forms.Label m_lblBit5;
        private System.Windows.Forms.Label m_lblBit3;
        private System.Windows.Forms.Label m_lblBit4;
        private System.Windows.Forms.Label m_lblSeparator1;
        private System.Windows.Forms.GroupBox m_grpCollideBehavior;
        private System.Windows.Forms.ComboBox m_cbClkMode;
        private System.Windows.Forms.Label m_lblClkMode;
        private System.Windows.Forms.CheckBox m_chbClkFromTerm;
        private System.Windows.Forms.ComboBox m_cbDataRate;
        private System.Windows.Forms.Label m_lblDataRate;
        private System.Windows.Forms.NumericUpDown m_numOvsFactor;
        private System.Windows.Forms.Label m_lblOvsFactor;
        private System.Windows.Forms.Panel m_panInternalClockConfig;
        private System.Windows.Forms.GroupBox m_grpWakeUp;
        private System.Windows.Forms.Label m_lblSeparator;
    }
}
