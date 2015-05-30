/*******************************************************************************
* Copyright 2011-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace ADC_SAR_SEQ_P4_v1_0
{
    partial class CyGeneralTab
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
            this.m_groupBoxTiming = new System.Windows.Forms.GroupBox();
            this.m_lblUnknownActualRate = new System.Windows.Forms.Label();
            this.m_lblActualSampleRate = new System.Windows.Forms.Label();
            this.m_lblActualSRText = new System.Windows.Forms.Label();
            this.m_lblUnknownFreq = new System.Windows.Forms.Label();
            this.m_lblUnknownRate = new System.Windows.Forms.Label();
            this.m_rbClkFreq = new System.Windows.Forms.RadioButton();
            this.m_numClkFreq = new System.Windows.Forms.NumericUpDown();
            this.m_rbSampleRate = new System.Windows.Forms.RadioButton();
            this.m_numScanRate = new System.Windows.Forms.NumericUpDown();
            this.m_groupBoxSampleMode = new System.Windows.Forms.GroupBox();
            this.m_rbHardwareSOC = new System.Windows.Forms.RadioButton();
            this.m_rbFreeRun = new System.Windows.Forms.RadioButton();
            this.m_groupBoxClkSrc = new System.Windows.Forms.GroupBox();
            this.m_rbExternal = new System.Windows.Forms.RadioButton();
            this.m_rbInternal = new System.Windows.Forms.RadioButton();
            this.m_groupBoxInputRange = new System.Windows.Forms.GroupBox();
            this.m_labelSingleEndModeRangeValue = new System.Windows.Forms.Label();
            this.m_labelDiffModeRangeValue = new System.Windows.Forms.Label();
            this.m_labelSingleEndModeRange = new System.Windows.Forms.Label();
            this.m_labelDiffModeRange = new System.Windows.Forms.Label();
            this.m_cbSingleEndNegInput = new System.Windows.Forms.ComboBox();
            this.m_labelSingleEndNegInput = new System.Windows.Forms.Label();
            this.m_numVrefVal = new System.Windows.Forms.NumericUpDown();
            this.m_labelVrefVal = new System.Windows.Forms.Label();
            this.m_cbInputBufGain = new System.Windows.Forms.ComboBox();
            this.m_labelInputBufGain = new System.Windows.Forms.Label();
            this.m_cbVrefSel = new System.Windows.Forms.ComboBox();
            this.m_labelVrefSel = new System.Windows.Forms.Label();
            this.m_groupBoxLimits = new System.Windows.Forms.GroupBox();
            this.m_cbCompareMode = new System.Windows.Forms.ComboBox();
            this.m_labelCompareMode = new System.Windows.Forms.Label();
            this.m_numHighLimit = new System.Windows.Forms.NumericUpDown();
            this.m_labelHighLimit = new System.Windows.Forms.Label();
            this.m_numLowLimit = new System.Windows.Forms.NumericUpDown();
            this.m_labelLowLimit = new System.Windows.Forms.Label();
            this.m_groupBoxResultDataFormat = new System.Windows.Forms.GroupBox();
            this.m_cbSampleAveraged = new System.Windows.Forms.ComboBox();
            this.m_cbAverageMode = new System.Windows.Forms.ComboBox();
            this.m_cbAlterResolution = new System.Windows.Forms.ComboBox();
            this.m_labelAlterResolution = new System.Windows.Forms.Label();
            this.m_labelAverageMode = new System.Windows.Forms.Label();
            this.m_labelSampleAveraged = new System.Windows.Forms.Label();
            this.m_labelDataFormatJustify = new System.Windows.Forms.Label();
            this.m_cbDataFormatJustify = new System.Windows.Forms.ComboBox();
            this.m_cbSingleEndResultFormat = new System.Windows.Forms.ComboBox();
            this.m_labelSingleEndResultFormat = new System.Windows.Forms.Label();
            this.m_cbDiffResultFormat = new System.Windows.Forms.ComboBox();
            this.m_labelDiffResultFormat = new System.Windows.Forms.Label();
            this.m_groupBoxTiming.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClkFreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numScanRate)).BeginInit();
            this.m_groupBoxSampleMode.SuspendLayout();
            this.m_groupBoxClkSrc.SuspendLayout();
            this.m_groupBoxInputRange.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefVal)).BeginInit();
            this.m_groupBoxLimits.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numHighLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numLowLimit)).BeginInit();
            this.m_groupBoxResultDataFormat.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_groupBoxTiming
            // 
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownActualRate);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualSampleRate);
            this.m_groupBoxTiming.Controls.Add(this.m_lblActualSRText);
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_lblUnknownRate);
            this.m_groupBoxTiming.Controls.Add(this.m_rbClkFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_numClkFreq);
            this.m_groupBoxTiming.Controls.Add(this.m_rbSampleRate);
            this.m_groupBoxTiming.Controls.Add(this.m_numScanRate);
            this.m_groupBoxTiming.Location = new System.Drawing.Point(3, 3);
            this.m_groupBoxTiming.Name = "m_groupBoxTiming";
            this.m_groupBoxTiming.Size = new System.Drawing.Size(275, 95);
            this.m_groupBoxTiming.TabIndex = 0;
            this.m_groupBoxTiming.TabStop = false;
            this.m_groupBoxTiming.Text = "Timing";
            // 
            // m_lblUnknownActualRate
            // 
            this.m_lblUnknownActualRate.AutoSize = true;
            this.m_lblUnknownActualRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownActualRate.Location = new System.Drawing.Point(151, 73);
            this.m_lblUnknownActualRate.Name = "m_lblUnknownActualRate";
            this.m_lblUnknownActualRate.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownActualRate.TabIndex = 6;
            this.m_lblUnknownActualRate.Text = "UNKNOWN RATE";
            // 
            // m_lblActualSampleRate
            // 
            this.m_lblActualSampleRate.AutoSize = true;
            this.m_lblActualSampleRate.Location = new System.Drawing.Point(153, 73);
            this.m_lblActualSampleRate.Name = "m_lblActualSampleRate";
            this.m_lblActualSampleRate.Size = new System.Drawing.Size(13, 13);
            this.m_lblActualSampleRate.TabIndex = 5;
            this.m_lblActualSampleRate.Text = "0";
            this.m_lblActualSampleRate.Visible = false;
            // 
            // m_lblActualSRText
            // 
            this.m_lblActualSRText.AutoSize = true;
            this.m_lblActualSRText.Location = new System.Drawing.Point(22, 73);
            this.m_lblActualSRText.Name = "m_lblActualSRText";
            this.m_lblActualSRText.Size = new System.Drawing.Size(127, 13);
            this.m_lblActualSRText.TabIndex = 4;
            this.m_lblActualSRText.Text = "Actual sample rate (SPS):";
            // 
            // m_lblUnknownFreq
            // 
            this.m_lblUnknownFreq.AutoSize = true;
            this.m_lblUnknownFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownFreq.Location = new System.Drawing.Point(151, 47);
            this.m_lblUnknownFreq.Name = "m_lblUnknownFreq";
            this.m_lblUnknownFreq.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownFreq.TabIndex = 3;
            this.m_lblUnknownFreq.Text = "UNKNOWN FREQ";
            // 
            // m_lblUnknownRate
            // 
            this.m_lblUnknownRate.AutoSize = true;
            this.m_lblUnknownRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.m_lblUnknownRate.Location = new System.Drawing.Point(151, 21);
            this.m_lblUnknownRate.Name = "m_lblUnknownRate";
            this.m_lblUnknownRate.Size = new System.Drawing.Size(109, 13);
            this.m_lblUnknownRate.TabIndex = 2;
            this.m_lblUnknownRate.Text = "UNKNOWN RATE";
            // 
            // m_rbClkFreq
            // 
            this.m_rbClkFreq.AutoSize = true;
            this.m_rbClkFreq.Location = new System.Drawing.Point(6, 45);
            this.m_rbClkFreq.Name = "m_rbClkFreq";
            this.m_rbClkFreq.Size = new System.Drawing.Size(133, 17);
            this.m_rbClkFreq.TabIndex = 0;
            this.m_rbClkFreq.TabStop = true;
            this.m_rbClkFreq.Text = "Clock frequency (kHz):";
            this.m_rbClkFreq.UseVisualStyleBackColor = true;
            // 
            // m_numClkFreq
            // 
            this.m_numClkFreq.DecimalPlaces = 3;
            this.m_numClkFreq.Location = new System.Drawing.Point(154, 45);
            this.m_numClkFreq.Name = "m_numClkFreq";
            this.m_numClkFreq.Size = new System.Drawing.Size(86, 20);
            this.m_numClkFreq.TabIndex = 1;
            // 
            // m_rbSampleRate
            // 
            this.m_rbSampleRate.AutoSize = true;
            this.m_rbSampleRate.Location = new System.Drawing.Point(6, 19);
            this.m_rbSampleRate.Name = "m_rbSampleRate";
            this.m_rbSampleRate.Size = new System.Drawing.Size(114, 17);
            this.m_rbSampleRate.TabIndex = 0;
            this.m_rbSampleRate.TabStop = true;
            this.m_rbSampleRate.Text = "Sample rate (SPS):";
            this.m_rbSampleRate.UseVisualStyleBackColor = true;
            this.m_rbSampleRate.CheckedChanged += new System.EventHandler(this.rbScanRate_CheckedChanged);
            // 
            // m_numScanRate
            // 
            this.m_numScanRate.Location = new System.Drawing.Point(154, 19);
            this.m_numScanRate.Name = "m_numScanRate";
            this.m_numScanRate.Size = new System.Drawing.Size(86, 20);
            this.m_numScanRate.TabIndex = 1;
            // 
            // m_groupBoxSampleMode
            // 
            this.m_groupBoxSampleMode.Controls.Add(this.m_rbHardwareSOC);
            this.m_groupBoxSampleMode.Controls.Add(this.m_rbFreeRun);
            this.m_groupBoxSampleMode.Location = new System.Drawing.Point(416, 3);
            this.m_groupBoxSampleMode.Name = "m_groupBoxSampleMode";
            this.m_groupBoxSampleMode.Size = new System.Drawing.Size(126, 65);
            this.m_groupBoxSampleMode.TabIndex = 3;
            this.m_groupBoxSampleMode.TabStop = false;
            this.m_groupBoxSampleMode.Text = "Sample mode";
            // 
            // m_rbHardwareSOC
            // 
            this.m_rbHardwareSOC.AutoSize = true;
            this.m_rbHardwareSOC.Location = new System.Drawing.Point(6, 42);
            this.m_rbHardwareSOC.Name = "m_rbHardwareSOC";
            this.m_rbHardwareSOC.Size = new System.Drawing.Size(103, 17);
            this.m_rbHardwareSOC.TabIndex = 1;
            this.m_rbHardwareSOC.TabStop = true;
            this.m_rbHardwareSOC.Text = "Hardware trigger";
            this.m_rbHardwareSOC.UseVisualStyleBackColor = true;
            this.m_rbHardwareSOC.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // m_rbFreeRun
            // 
            this.m_rbFreeRun.AutoSize = true;
            this.m_rbFreeRun.Location = new System.Drawing.Point(6, 19);
            this.m_rbFreeRun.Name = "m_rbFreeRun";
            this.m_rbFreeRun.Size = new System.Drawing.Size(84, 17);
            this.m_rbFreeRun.TabIndex = 0;
            this.m_rbFreeRun.TabStop = true;
            this.m_rbFreeRun.Text = "Free running";
            this.m_rbFreeRun.UseVisualStyleBackColor = true;
            this.m_rbFreeRun.CheckedChanged += new System.EventHandler(this.rbSampleMode_CheckedChanged);
            // 
            // m_groupBoxClkSrc
            // 
            this.m_groupBoxClkSrc.Controls.Add(this.m_rbExternal);
            this.m_groupBoxClkSrc.Controls.Add(this.m_rbInternal);
            this.m_groupBoxClkSrc.Location = new System.Drawing.Point(284, 3);
            this.m_groupBoxClkSrc.Name = "m_groupBoxClkSrc";
            this.m_groupBoxClkSrc.Size = new System.Drawing.Size(126, 65);
            this.m_groupBoxClkSrc.TabIndex = 2;
            this.m_groupBoxClkSrc.TabStop = false;
            this.m_groupBoxClkSrc.Text = "Clock source";
            // 
            // m_rbExternal
            // 
            this.m_rbExternal.AutoSize = true;
            this.m_rbExternal.Location = new System.Drawing.Point(6, 42);
            this.m_rbExternal.Name = "m_rbExternal";
            this.m_rbExternal.Size = new System.Drawing.Size(63, 17);
            this.m_rbExternal.TabIndex = 1;
            this.m_rbExternal.TabStop = true;
            this.m_rbExternal.Text = "External";
            this.m_rbExternal.UseVisualStyleBackColor = true;
            this.m_rbExternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_rbInternal
            // 
            this.m_rbInternal.AutoSize = true;
            this.m_rbInternal.Location = new System.Drawing.Point(6, 19);
            this.m_rbInternal.Name = "m_rbInternal";
            this.m_rbInternal.Size = new System.Drawing.Size(60, 17);
            this.m_rbInternal.TabIndex = 0;
            this.m_rbInternal.TabStop = true;
            this.m_rbInternal.Text = "Internal";
            this.m_rbInternal.UseVisualStyleBackColor = true;
            this.m_rbInternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_groupBoxInputRange
            // 
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndModeRangeValue);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelDiffModeRangeValue);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndModeRange);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelDiffModeRange);
            this.m_groupBoxInputRange.Controls.Add(this.m_cbSingleEndNegInput);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelSingleEndNegInput);
            this.m_groupBoxInputRange.Controls.Add(this.m_numVrefVal);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelVrefVal);
            this.m_groupBoxInputRange.Controls.Add(this.m_cbInputBufGain);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelInputBufGain);
            this.m_groupBoxInputRange.Controls.Add(this.m_cbVrefSel);
            this.m_groupBoxInputRange.Controls.Add(this.m_labelVrefSel);
            this.m_groupBoxInputRange.Location = new System.Drawing.Point(3, 104);
            this.m_groupBoxInputRange.Name = "m_groupBoxInputRange";
            this.m_groupBoxInputRange.Size = new System.Drawing.Size(339, 181);
            this.m_groupBoxInputRange.TabIndex = 4;
            this.m_groupBoxInputRange.TabStop = false;
            this.m_groupBoxInputRange.Text = "Input range";
            // 
            // m_labelSingleEndModeRangeValue
            // 
            this.m_labelSingleEndModeRangeValue.AutoSize = true;
            this.m_labelSingleEndModeRangeValue.Location = new System.Drawing.Point(154, 155);
            this.m_labelSingleEndModeRangeValue.Name = "m_labelSingleEndModeRangeValue";
            this.m_labelSingleEndModeRangeValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelSingleEndModeRangeValue.TabIndex = 0;
            this.m_labelSingleEndModeRangeValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_labelDiffModeRangeValue
            // 
            this.m_labelDiffModeRangeValue.AutoSize = true;
            this.m_labelDiffModeRangeValue.Location = new System.Drawing.Point(154, 129);
            this.m_labelDiffModeRangeValue.Name = "m_labelDiffModeRangeValue";
            this.m_labelDiffModeRangeValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelDiffModeRangeValue.TabIndex = 0;
            this.m_labelDiffModeRangeValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_labelSingleEndModeRange
            // 
            this.m_labelSingleEndModeRange.AutoSize = true;
            this.m_labelSingleEndModeRange.Location = new System.Drawing.Point(6, 155);
            this.m_labelSingleEndModeRange.Name = "m_labelSingleEndModeRange";
            this.m_labelSingleEndModeRange.Size = new System.Drawing.Size(131, 13);
            this.m_labelSingleEndModeRange.TabIndex = 0;
            this.m_labelSingleEndModeRange.Text = "Single ended mode range:";
            // 
            // m_labelDiffModeRange
            // 
            this.m_labelDiffModeRange.AutoSize = true;
            this.m_labelDiffModeRange.Location = new System.Drawing.Point(6, 129);
            this.m_labelDiffModeRange.Name = "m_labelDiffModeRange";
            this.m_labelDiffModeRange.Size = new System.Drawing.Size(119, 13);
            this.m_labelDiffModeRange.TabIndex = 0;
            this.m_labelDiffModeRange.Text = "Differential mode range:";
            // 
            // m_cbSingleEndNegInput
            // 
            this.m_cbSingleEndNegInput.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSingleEndNegInput.FormattingEnabled = true;
            this.m_cbSingleEndNegInput.Location = new System.Drawing.Point(154, 99);
            this.m_cbSingleEndNegInput.Name = "m_cbSingleEndNegInput";
            this.m_cbSingleEndNegInput.Size = new System.Drawing.Size(63, 21);
            this.m_cbSingleEndNegInput.TabIndex = 4;
            this.m_cbSingleEndNegInput.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelSingleEndNegInput
            // 
            this.m_labelSingleEndNegInput.AutoSize = true;
            this.m_labelSingleEndNegInput.Location = new System.Drawing.Point(6, 102);
            this.m_labelSingleEndNegInput.Name = "m_labelSingleEndNegInput";
            this.m_labelSingleEndNegInput.Size = new System.Drawing.Size(142, 13);
            this.m_labelSingleEndNegInput.TabIndex = 0;
            this.m_labelSingleEndNegInput.Text = "Single ended negative input:";
            // 
            // m_numVrefVal
            // 
            this.m_numVrefVal.DecimalPlaces = 3;
            this.m_numVrefVal.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.m_numVrefVal.Location = new System.Drawing.Point(154, 46);
            this.m_numVrefVal.Name = "m_numVrefVal";
            this.m_numVrefVal.Size = new System.Drawing.Size(63, 20);
            this.m_numVrefVal.TabIndex = 2;
            // 
            // m_labelVrefVal
            // 
            this.m_labelVrefVal.AutoSize = true;
            this.m_labelVrefVal.Location = new System.Drawing.Point(6, 48);
            this.m_labelVrefVal.Name = "m_labelVrefVal";
            this.m_labelVrefVal.Size = new System.Drawing.Size(74, 13);
            this.m_labelVrefVal.TabIndex = 0;
            this.m_labelVrefVal.Text = "Vref value (V):";
            // 
            // m_cbInputBufGain
            // 
            this.m_cbInputBufGain.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbInputBufGain.FormattingEnabled = true;
            this.m_cbInputBufGain.Location = new System.Drawing.Point(154, 72);
            this.m_cbInputBufGain.Name = "m_cbInputBufGain";
            this.m_cbInputBufGain.Size = new System.Drawing.Size(63, 21);
            this.m_cbInputBufGain.TabIndex = 3;
            this.m_cbInputBufGain.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelInputBufGain
            // 
            this.m_labelInputBufGain.AutoSize = true;
            this.m_labelInputBufGain.Location = new System.Drawing.Point(6, 75);
            this.m_labelInputBufGain.Name = "m_labelInputBufGain";
            this.m_labelInputBufGain.Size = new System.Drawing.Size(87, 13);
            this.m_labelInputBufGain.TabIndex = 0;
            this.m_labelInputBufGain.Text = "Input buffer gain:";
            // 
            // m_cbVrefSel
            // 
            this.m_cbVrefSel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbVrefSel.FormattingEnabled = true;
            this.m_cbVrefSel.Location = new System.Drawing.Point(154, 19);
            this.m_cbVrefSel.Name = "m_cbVrefSel";
            this.m_cbVrefSel.Size = new System.Drawing.Size(165, 21);
            this.m_cbVrefSel.TabIndex = 1;
            this.m_cbVrefSel.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelVrefSel
            // 
            this.m_labelVrefSel.AutoSize = true;
            this.m_labelVrefSel.Location = new System.Drawing.Point(6, 22);
            this.m_labelVrefSel.Name = "m_labelVrefSel";
            this.m_labelVrefSel.Size = new System.Drawing.Size(60, 13);
            this.m_labelVrefSel.TabIndex = 0;
            this.m_labelVrefSel.Text = "Vref select:";
            // 
            // m_groupBoxLimits
            // 
            this.m_groupBoxLimits.Controls.Add(this.m_cbCompareMode);
            this.m_groupBoxLimits.Controls.Add(this.m_labelCompareMode);
            this.m_groupBoxLimits.Controls.Add(this.m_numHighLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_labelHighLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_numLowLimit);
            this.m_groupBoxLimits.Controls.Add(this.m_labelLowLimit);
            this.m_groupBoxLimits.Location = new System.Drawing.Point(3, 291);
            this.m_groupBoxLimits.Name = "m_groupBoxLimits";
            this.m_groupBoxLimits.Size = new System.Drawing.Size(339, 73);
            this.m_groupBoxLimits.TabIndex = 6;
            this.m_groupBoxLimits.TabStop = false;
            this.m_groupBoxLimits.Text = "Interrupt limits";
            // 
            // m_cbCompareMode
            // 
            this.m_cbCompareMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCompareMode.FormattingEnabled = true;
            this.m_cbCompareMode.Location = new System.Drawing.Point(94, 45);
            this.m_cbCompareMode.Name = "m_cbCompareMode";
            this.m_cbCompareMode.Size = new System.Drawing.Size(240, 21);
            this.m_cbCompareMode.TabIndex = 3;
            this.m_cbCompareMode.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelCompareMode
            // 
            this.m_labelCompareMode.AutoSize = true;
            this.m_labelCompareMode.Location = new System.Drawing.Point(6, 48);
            this.m_labelCompareMode.Name = "m_labelCompareMode";
            this.m_labelCompareMode.Size = new System.Drawing.Size(81, 13);
            this.m_labelCompareMode.TabIndex = 0;
            this.m_labelCompareMode.Text = "Compare mode:";
            // 
            // m_numHighLimit
            // 
            this.m_numHighLimit.Hexadecimal = true;
            this.m_numHighLimit.Location = new System.Drawing.Point(262, 19);
            this.m_numHighLimit.Maximum = new decimal(new int[] {
            70000,
            0,
            0,
            0});
            this.m_numHighLimit.Name = "m_numHighLimit";
            this.m_numHighLimit.Size = new System.Drawing.Size(54, 20);
            this.m_numHighLimit.TabIndex = 2;
            // 
            // m_labelHighLimit
            // 
            this.m_labelHighLimit.AutoSize = true;
            this.m_labelHighLimit.Location = new System.Drawing.Point(178, 21);
            this.m_labelHighLimit.Name = "m_labelHighLimit";
            this.m_labelHighLimit.Size = new System.Drawing.Size(78, 13);
            this.m_labelHighLimit.TabIndex = 0;
            this.m_labelHighLimit.Text = "High limit (hex):";
            // 
            // m_numLowLimit
            // 
            this.m_numLowLimit.Hexadecimal = true;
            this.m_numLowLimit.Location = new System.Drawing.Point(94, 19);
            this.m_numLowLimit.Maximum = new decimal(new int[] {
            70000,
            0,
            0,
            0});
            this.m_numLowLimit.Name = "m_numLowLimit";
            this.m_numLowLimit.Size = new System.Drawing.Size(54, 20);
            this.m_numLowLimit.TabIndex = 1;
            // 
            // m_labelLowLimit
            // 
            this.m_labelLowLimit.AutoSize = true;
            this.m_labelLowLimit.Location = new System.Drawing.Point(6, 21);
            this.m_labelLowLimit.Name = "m_labelLowLimit";
            this.m_labelLowLimit.Size = new System.Drawing.Size(76, 13);
            this.m_labelLowLimit.TabIndex = 0;
            this.m_labelLowLimit.Text = "Low limit (hex):";
            // 
            // m_groupBoxResultDataFormat
            // 
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbSampleAveraged);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbAverageMode);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbAlterResolution);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelAlterResolution);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelAverageMode);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelSampleAveraged);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelDataFormatJustify);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbDataFormatJustify);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbSingleEndResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelSingleEndResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_cbDiffResultFormat);
            this.m_groupBoxResultDataFormat.Controls.Add(this.m_labelDiffResultFormat);
            this.m_groupBoxResultDataFormat.Location = new System.Drawing.Point(348, 104);
            this.m_groupBoxResultDataFormat.Name = "m_groupBoxResultDataFormat";
            this.m_groupBoxResultDataFormat.Size = new System.Drawing.Size(252, 181);
            this.m_groupBoxResultDataFormat.TabIndex = 5;
            this.m_groupBoxResultDataFormat.TabStop = false;
            this.m_groupBoxResultDataFormat.Text = "Result data format";
            // 
            // m_cbSampleAveraged
            // 
            this.m_cbSampleAveraged.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSampleAveraged.FormattingEnabled = true;
            this.m_cbSampleAveraged.Location = new System.Drawing.Point(146, 100);
            this.m_cbSampleAveraged.Name = "m_cbSampleAveraged";
            this.m_cbSampleAveraged.Size = new System.Drawing.Size(69, 21);
            this.m_cbSampleAveraged.TabIndex = 4;
            this.m_cbSampleAveraged.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbAverageMode
            // 
            this.m_cbAverageMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAverageMode.FormattingEnabled = true;
            this.m_cbAverageMode.Location = new System.Drawing.Point(146, 154);
            this.m_cbAverageMode.Name = "m_cbAverageMode";
            this.m_cbAverageMode.Size = new System.Drawing.Size(102, 21);
            this.m_cbAverageMode.TabIndex = 6;
            this.m_cbAverageMode.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbAlterResolution
            // 
            this.m_cbAlterResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbAlterResolution.FormattingEnabled = true;
            this.m_cbAlterResolution.Location = new System.Drawing.Point(146, 127);
            this.m_cbAlterResolution.Name = "m_cbAlterResolution";
            this.m_cbAlterResolution.Size = new System.Drawing.Size(69, 21);
            this.m_cbAlterResolution.TabIndex = 5;
            this.m_cbAlterResolution.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelAlterResolution
            // 
            this.m_labelAlterResolution.AutoSize = true;
            this.m_labelAlterResolution.Location = new System.Drawing.Point(6, 130);
            this.m_labelAlterResolution.Name = "m_labelAlterResolution";
            this.m_labelAlterResolution.Size = new System.Drawing.Size(125, 13);
            this.m_labelAlterResolution.TabIndex = 0;
            this.m_labelAlterResolution.Text = "Alternate resolution (bits):";
            // 
            // m_labelAverageMode
            // 
            this.m_labelAverageMode.AutoSize = true;
            this.m_labelAverageMode.Location = new System.Drawing.Point(6, 157);
            this.m_labelAverageMode.Name = "m_labelAverageMode";
            this.m_labelAverageMode.Size = new System.Drawing.Size(87, 13);
            this.m_labelAverageMode.TabIndex = 0;
            this.m_labelAverageMode.Text = "Averaging mode:";
            // 
            // m_labelSampleAveraged
            // 
            this.m_labelSampleAveraged.AutoSize = true;
            this.m_labelSampleAveraged.Location = new System.Drawing.Point(6, 103);
            this.m_labelSampleAveraged.Name = "m_labelSampleAveraged";
            this.m_labelSampleAveraged.Size = new System.Drawing.Size(98, 13);
            this.m_labelSampleAveraged.TabIndex = 0;
            this.m_labelSampleAveraged.Text = "Samples averaged:";
            // 
            // m_labelDataFormatJustify
            // 
            this.m_labelDataFormatJustify.AutoSize = true;
            this.m_labelDataFormatJustify.Location = new System.Drawing.Point(6, 76);
            this.m_labelDataFormatJustify.Name = "m_labelDataFormatJustify";
            this.m_labelDataFormatJustify.Size = new System.Drawing.Size(120, 13);
            this.m_labelDataFormatJustify.TabIndex = 0;
            this.m_labelDataFormatJustify.Text = "Data format justification:";
            // 
            // m_cbDataFormatJustify
            // 
            this.m_cbDataFormatJustify.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbDataFormatJustify.FormattingEnabled = true;
            this.m_cbDataFormatJustify.Location = new System.Drawing.Point(146, 73);
            this.m_cbDataFormatJustify.Name = "m_cbDataFormatJustify";
            this.m_cbDataFormatJustify.Size = new System.Drawing.Size(69, 21);
            this.m_cbDataFormatJustify.TabIndex = 3;
            this.m_cbDataFormatJustify.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_cbSingleEndResultFormat
            // 
            this.m_cbSingleEndResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbSingleEndResultFormat.FormattingEnabled = true;
            this.m_cbSingleEndResultFormat.Location = new System.Drawing.Point(146, 46);
            this.m_cbSingleEndResultFormat.Name = "m_cbSingleEndResultFormat";
            this.m_cbSingleEndResultFormat.Size = new System.Drawing.Size(69, 21);
            this.m_cbSingleEndResultFormat.TabIndex = 2;
            this.m_cbSingleEndResultFormat.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelSingleEndResultFormat
            // 
            this.m_labelSingleEndResultFormat.AutoSize = true;
            this.m_labelSingleEndResultFormat.Location = new System.Drawing.Point(6, 49);
            this.m_labelSingleEndResultFormat.Name = "m_labelSingleEndResultFormat";
            this.m_labelSingleEndResultFormat.Size = new System.Drawing.Size(132, 13);
            this.m_labelSingleEndResultFormat.TabIndex = 0;
            this.m_labelSingleEndResultFormat.Text = "Single ended result format:";
            // 
            // m_cbDiffResultFormat
            // 
            this.m_cbDiffResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbDiffResultFormat.FormattingEnabled = true;
            this.m_cbDiffResultFormat.Location = new System.Drawing.Point(146, 19);
            this.m_cbDiffResultFormat.Name = "m_cbDiffResultFormat";
            this.m_cbDiffResultFormat.Size = new System.Drawing.Size(69, 21);
            this.m_cbDiffResultFormat.TabIndex = 1;
            this.m_cbDiffResultFormat.SelectedIndexChanged += new System.EventHandler(this.cb_SelectedIndexChanged);
            // 
            // m_labelDiffResultFormat
            // 
            this.m_labelDiffResultFormat.AutoSize = true;
            this.m_labelDiffResultFormat.Location = new System.Drawing.Point(6, 22);
            this.m_labelDiffResultFormat.Name = "m_labelDiffResultFormat";
            this.m_labelDiffResultFormat.Size = new System.Drawing.Size(120, 13);
            this.m_labelDiffResultFormat.TabIndex = 0;
            this.m_labelDiffResultFormat.Text = "Differential result format:";
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_groupBoxResultDataFormat);
            this.Controls.Add(this.m_groupBoxLimits);
            this.Controls.Add(this.m_groupBoxInputRange);
            this.Controls.Add(this.m_groupBoxClkSrc);
            this.Controls.Add(this.m_groupBoxSampleMode);
            this.Controls.Add(this.m_groupBoxTiming);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(604, 370);
            this.m_groupBoxTiming.ResumeLayout(false);
            this.m_groupBoxTiming.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numClkFreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numScanRate)).EndInit();
            this.m_groupBoxSampleMode.ResumeLayout(false);
            this.m_groupBoxSampleMode.PerformLayout();
            this.m_groupBoxClkSrc.ResumeLayout(false);
            this.m_groupBoxClkSrc.PerformLayout();
            this.m_groupBoxInputRange.ResumeLayout(false);
            this.m_groupBoxInputRange.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numVrefVal)).EndInit();
            this.m_groupBoxLimits.ResumeLayout(false);
            this.m_groupBoxLimits.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numHighLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numLowLimit)).EndInit();
            this.m_groupBoxResultDataFormat.ResumeLayout(false);
            this.m_groupBoxResultDataFormat.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_groupBoxTiming;
        private System.Windows.Forms.NumericUpDown m_numScanRate;
        private System.Windows.Forms.RadioButton m_rbClkFreq;
        private System.Windows.Forms.RadioButton m_rbSampleRate;
        private System.Windows.Forms.GroupBox m_groupBoxSampleMode;
        private System.Windows.Forms.RadioButton m_rbHardwareSOC;
        private System.Windows.Forms.RadioButton m_rbFreeRun;
        private System.Windows.Forms.GroupBox m_groupBoxClkSrc;
        private System.Windows.Forms.RadioButton m_rbExternal;
        private System.Windows.Forms.RadioButton m_rbInternal;
        private System.Windows.Forms.GroupBox m_groupBoxInputRange;
        private System.Windows.Forms.ComboBox m_cbVrefSel;
        private System.Windows.Forms.Label m_labelVrefSel;
        private System.Windows.Forms.ComboBox m_cbInputBufGain;
        private System.Windows.Forms.Label m_labelInputBufGain;
        private System.Windows.Forms.NumericUpDown m_numVrefVal;
        private System.Windows.Forms.Label m_labelVrefVal;
        private System.Windows.Forms.ComboBox m_cbSingleEndNegInput;
        private System.Windows.Forms.Label m_labelSingleEndNegInput;
        private System.Windows.Forms.Label m_labelSingleEndModeRange;
        private System.Windows.Forms.Label m_labelDiffModeRange;
        private System.Windows.Forms.NumericUpDown m_numClkFreq;
        private System.Windows.Forms.Label m_labelSingleEndModeRangeValue;
        private System.Windows.Forms.Label m_labelDiffModeRangeValue;
        private System.Windows.Forms.GroupBox m_groupBoxLimits;
        private System.Windows.Forms.ComboBox m_cbCompareMode;
        private System.Windows.Forms.Label m_labelCompareMode;
        private System.Windows.Forms.NumericUpDown m_numHighLimit;
        private System.Windows.Forms.Label m_labelHighLimit;
        private System.Windows.Forms.NumericUpDown m_numLowLimit;
        private System.Windows.Forms.Label m_labelLowLimit;
        private System.Windows.Forms.GroupBox m_groupBoxResultDataFormat;
        private System.Windows.Forms.ComboBox m_cbSampleAveraged;
        private System.Windows.Forms.ComboBox m_cbAverageMode;
        private System.Windows.Forms.ComboBox m_cbAlterResolution;
        private System.Windows.Forms.Label m_labelAlterResolution;
        private System.Windows.Forms.Label m_labelAverageMode;
        private System.Windows.Forms.Label m_labelSampleAveraged;
        private System.Windows.Forms.Label m_labelDataFormatJustify;
        private System.Windows.Forms.ComboBox m_cbDataFormatJustify;
        private System.Windows.Forms.ComboBox m_cbSingleEndResultFormat;
        private System.Windows.Forms.Label m_labelSingleEndResultFormat;
        private System.Windows.Forms.ComboBox m_cbDiffResultFormat;
        private System.Windows.Forms.Label m_labelDiffResultFormat;
        private System.Windows.Forms.Label m_lblUnknownFreq;
        private System.Windows.Forms.Label m_lblUnknownRate;
        private System.Windows.Forms.Label m_lblActualSRText;
        private System.Windows.Forms.Label m_lblActualSampleRate;
        private System.Windows.Forms.Label m_lblUnknownActualRate;

    }
}
