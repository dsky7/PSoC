/*******************************************************************************
* Copyright 2011-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace ADC_SAR_SEQ_P4_v1_0
{
    partial class CyChannelsTab
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            this.m_groupBoxAcqTimes = new System.Windows.Forms.GroupBox();
            this.m_labelAcqTimeDValue = new System.Windows.Forms.Label();
            this.m_labelAcqTimeCValue = new System.Windows.Forms.Label();
            this.m_labelAcqTimeBValue = new System.Windows.Forms.Label();
            this.m_labelAcqTimeAValue = new System.Windows.Forms.Label();
            this.m_labelAcqTimeD = new System.Windows.Forms.Label();
            this.m_labelAcqTimeC = new System.Windows.Forms.Label();
            this.m_numUpDownAcqTimeD = new System.Windows.Forms.NumericUpDown();
            this.m_numUpDownAcqTimeC = new System.Windows.Forms.NumericUpDown();
            this.m_numUpDownAcqTimeB = new System.Windows.Forms.NumericUpDown();
            this.m_labelAcqTimeB = new System.Windows.Forms.Label();
            this.m_numUpDownAcqTimeA = new System.Windows.Forms.NumericUpDown();
            this.m_labelAcqTimeA = new System.Windows.Forms.Label();
            this.m_numUpDownSeqChannels = new System.Windows.Forms.NumericUpDown();
            this.m_dgvChannelsConfig = new System.Windows.Forms.DataGridView();
            this.m_labelSeqChannels = new System.Windows.Forms.Label();
            this.colChannel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colChannelEnable = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.colResolution = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colAveraged = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.colAcqTime = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.colConvTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colLimitDetect = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.colSaturation = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.m_groupBoxAcqTimes.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeC)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownSeqChannels)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvChannelsConfig)).BeginInit();
            this.SuspendLayout();
            // 
            // m_groupBoxAcqTimes
            // 
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeDValue);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeCValue);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeBValue);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeAValue);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeD);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeC);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_numUpDownAcqTimeD);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_numUpDownAcqTimeC);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_numUpDownAcqTimeB);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeB);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_numUpDownAcqTimeA);
            this.m_groupBoxAcqTimes.Controls.Add(this.m_labelAcqTimeA);
            this.m_groupBoxAcqTimes.Location = new System.Drawing.Point(3, 3);
            this.m_groupBoxAcqTimes.Name = "m_groupBoxAcqTimes";
            this.m_groupBoxAcqTimes.Size = new System.Drawing.Size(231, 129);
            this.m_groupBoxAcqTimes.TabIndex = 0;
            this.m_groupBoxAcqTimes.TabStop = false;
            this.m_groupBoxAcqTimes.Text = "Acquisition times (ADC clocks)";
            // 
            // m_labelAcqTimeDValue
            // 
            this.m_labelAcqTimeDValue.AutoSize = true;
            this.m_labelAcqTimeDValue.Location = new System.Drawing.Point(125, 99);
            this.m_labelAcqTimeDValue.Name = "m_labelAcqTimeDValue";
            this.m_labelAcqTimeDValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelAcqTimeDValue.TabIndex = 0;
            // 
            // m_labelAcqTimeCValue
            // 
            this.m_labelAcqTimeCValue.AutoSize = true;
            this.m_labelAcqTimeCValue.Location = new System.Drawing.Point(125, 74);
            this.m_labelAcqTimeCValue.Name = "m_labelAcqTimeCValue";
            this.m_labelAcqTimeCValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelAcqTimeCValue.TabIndex = 0;
            // 
            // m_labelAcqTimeBValue
            // 
            this.m_labelAcqTimeBValue.AutoSize = true;
            this.m_labelAcqTimeBValue.Location = new System.Drawing.Point(125, 48);
            this.m_labelAcqTimeBValue.Name = "m_labelAcqTimeBValue";
            this.m_labelAcqTimeBValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelAcqTimeBValue.TabIndex = 0;
            // 
            // m_labelAcqTimeAValue
            // 
            this.m_labelAcqTimeAValue.AutoSize = true;
            this.m_labelAcqTimeAValue.Location = new System.Drawing.Point(125, 22);
            this.m_labelAcqTimeAValue.Name = "m_labelAcqTimeAValue";
            this.m_labelAcqTimeAValue.Size = new System.Drawing.Size(0, 13);
            this.m_labelAcqTimeAValue.TabIndex = 0;
            // 
            // m_labelAcqTimeD
            // 
            this.m_labelAcqTimeD.AutoSize = true;
            this.m_labelAcqTimeD.Location = new System.Drawing.Point(6, 99);
            this.m_labelAcqTimeD.Name = "m_labelAcqTimeD";
            this.m_labelAcqTimeD.Size = new System.Drawing.Size(40, 13);
            this.m_labelAcqTimeD.TabIndex = 0;
            this.m_labelAcqTimeD.Text = "D clks:";
            // 
            // m_labelAcqTimeC
            // 
            this.m_labelAcqTimeC.AutoSize = true;
            this.m_labelAcqTimeC.Location = new System.Drawing.Point(6, 74);
            this.m_labelAcqTimeC.Name = "m_labelAcqTimeC";
            this.m_labelAcqTimeC.Size = new System.Drawing.Size(39, 13);
            this.m_labelAcqTimeC.TabIndex = 0;
            this.m_labelAcqTimeC.Text = "C clks:";
            // 
            // m_numUpDownAcqTimeD
            // 
            this.m_numUpDownAcqTimeD.Location = new System.Drawing.Point(51, 97);
            this.m_numUpDownAcqTimeD.Name = "m_numUpDownAcqTimeD";
            this.m_numUpDownAcqTimeD.Size = new System.Drawing.Size(53, 20);
            this.m_numUpDownAcqTimeD.TabIndex = 4;
            // 
            // m_numUpDownAcqTimeC
            // 
            this.m_numUpDownAcqTimeC.Location = new System.Drawing.Point(51, 72);
            this.m_numUpDownAcqTimeC.Name = "m_numUpDownAcqTimeC";
            this.m_numUpDownAcqTimeC.Size = new System.Drawing.Size(53, 20);
            this.m_numUpDownAcqTimeC.TabIndex = 3;
            // 
            // m_numUpDownAcqTimeB
            // 
            this.m_numUpDownAcqTimeB.Location = new System.Drawing.Point(51, 46);
            this.m_numUpDownAcqTimeB.Name = "m_numUpDownAcqTimeB";
            this.m_numUpDownAcqTimeB.Size = new System.Drawing.Size(53, 20);
            this.m_numUpDownAcqTimeB.TabIndex = 2;
            // 
            // m_labelAcqTimeB
            // 
            this.m_labelAcqTimeB.AutoSize = true;
            this.m_labelAcqTimeB.Location = new System.Drawing.Point(6, 48);
            this.m_labelAcqTimeB.Name = "m_labelAcqTimeB";
            this.m_labelAcqTimeB.Size = new System.Drawing.Size(39, 13);
            this.m_labelAcqTimeB.TabIndex = 0;
            this.m_labelAcqTimeB.Text = "B clks:";
            // 
            // m_numUpDownAcqTimeA
            // 
            this.m_numUpDownAcqTimeA.Location = new System.Drawing.Point(51, 20);
            this.m_numUpDownAcqTimeA.Name = "m_numUpDownAcqTimeA";
            this.m_numUpDownAcqTimeA.Size = new System.Drawing.Size(53, 20);
            this.m_numUpDownAcqTimeA.TabIndex = 1;
            // 
            // m_labelAcqTimeA
            // 
            this.m_labelAcqTimeA.AutoSize = true;
            this.m_labelAcqTimeA.Location = new System.Drawing.Point(6, 22);
            this.m_labelAcqTimeA.Name = "m_labelAcqTimeA";
            this.m_labelAcqTimeA.Size = new System.Drawing.Size(39, 13);
            this.m_labelAcqTimeA.TabIndex = 0;
            this.m_labelAcqTimeA.Text = "A clks:";
            // 
            // m_numUpDownSeqChannels
            // 
            this.m_numUpDownSeqChannels.Location = new System.Drawing.Point(120, 138);
            this.m_numUpDownSeqChannels.Name = "m_numUpDownSeqChannels";
            this.m_numUpDownSeqChannels.Size = new System.Drawing.Size(37, 20);
            this.m_numUpDownSeqChannels.TabIndex = 1;
            // 
            // m_dgvChannelsConfig
            // 
            this.m_dgvChannelsConfig.AllowUserToAddRows = false;
            this.m_dgvChannelsConfig.AllowUserToDeleteRows = false;
            this.m_dgvChannelsConfig.AllowUserToResizeColumns = false;
            this.m_dgvChannelsConfig.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvChannelsConfig.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.m_dgvChannelsConfig.ColumnHeadersHeight = 39;
            this.m_dgvChannelsConfig.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.m_dgvChannelsConfig.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colChannel,
            this.colChannelEnable,
            this.colResolution,
            this.colMode,
            this.colAveraged,
            this.colAcqTime,
            this.colConvTime,
            this.colLimitDetect,
            this.colSaturation});
            this.m_dgvChannelsConfig.Location = new System.Drawing.Point(3, 164);
            this.m_dgvChannelsConfig.Name = "m_dgvChannelsConfig";
            this.m_dgvChannelsConfig.RowHeadersVisible = false;
            this.m_dgvChannelsConfig.RowHeadersWidth = 20;
            this.m_dgvChannelsConfig.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.m_dgvChannelsConfig.Size = new System.Drawing.Size(581, 58);
            this.m_dgvChannelsConfig.TabIndex = 2;
            // 
            // m_labelSeqChannels
            // 
            this.m_labelSeqChannels.AutoSize = true;
            this.m_labelSeqChannels.Location = new System.Drawing.Point(3, 140);
            this.m_labelSeqChannels.Name = "m_labelSeqChannels";
            this.m_labelSeqChannels.Size = new System.Drawing.Size(111, 13);
            this.m_labelSeqChannels.TabIndex = 0;
            this.m_labelSeqChannels.Text = "Sequenced channels:";
            // 
            // colChannel
            // 
            this.colChannel.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.colChannel.DefaultCellStyle = dataGridViewCellStyle2;
            this.colChannel.HeaderText = "Channel";
            this.colChannel.Name = "colChannel";
            this.colChannel.ReadOnly = true;
            this.colChannel.Width = 58;
            // 
            // colChannelEnable
            // 
            this.colChannelEnable.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.colChannelEnable.HeaderText = "Enable";
            this.colChannelEnable.Name = "colChannelEnable";
            this.colChannelEnable.Width = 50;
            // 
            // colResolution
            // 
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.colResolution.DefaultCellStyle = dataGridViewCellStyle3;
            this.colResolution.HeaderText = "Resolution";
            this.colResolution.Name = "colResolution";
            this.colResolution.Width = 73;
            // 
            // colMode
            // 
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.colMode.DefaultCellStyle = dataGridViewCellStyle4;
            this.colMode.HeaderText = "Mode";
            this.colMode.Name = "colMode";
            this.colMode.Width = 74;
            // 
            // colAveraged
            // 
            this.colAveraged.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.colAveraged.HeaderText = "AVG";
            this.colAveraged.Name = "colAveraged";
            this.colAveraged.Width = 39;
            // 
            // colAcqTime
            // 
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            this.colAcqTime.DefaultCellStyle = dataGridViewCellStyle5;
            this.colAcqTime.HeaderText = "Acq time";
            this.colAcqTime.Name = "colAcqTime";
            this.colAcqTime.Width = 72;
            // 
            // colConvTime
            // 
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.colConvTime.DefaultCellStyle = dataGridViewCellStyle6;
            this.colConvTime.HeaderText = "Conversion time";
            this.colConvTime.Name = "colConvTime";
            this.colConvTime.ReadOnly = true;
            this.colConvTime.Width = 78;
            // 
            // colLimitDetect
            // 
            this.colLimitDetect.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.colLimitDetect.HeaderText = "Limit detect";
            this.colLimitDetect.Name = "colLimitDetect";
            this.colLimitDetect.Width = 60;
            // 
            // colSaturation
            // 
            this.colSaturation.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.colSaturation.HeaderText = "Saturation";
            this.colSaturation.Name = "colSaturation";
            this.colSaturation.Width = 74;
            // 
            // CyChannelsTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_dgvChannelsConfig);
            this.Controls.Add(this.m_numUpDownSeqChannels);
            this.Controls.Add(this.m_labelSeqChannels);
            this.Controls.Add(this.m_groupBoxAcqTimes);
            this.Name = "CyChannelsTab";
            this.Size = new System.Drawing.Size(594, 227);
            this.m_groupBoxAcqTimes.ResumeLayout(false);
            this.m_groupBoxAcqTimes.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeC)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownAcqTimeA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numUpDownSeqChannels)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvChannelsConfig)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox m_groupBoxAcqTimes;
        private System.Windows.Forms.Label m_labelAcqTimeD;
        private System.Windows.Forms.Label m_labelAcqTimeC;
        private System.Windows.Forms.NumericUpDown m_numUpDownAcqTimeD;
        private System.Windows.Forms.NumericUpDown m_numUpDownAcqTimeC;
        private System.Windows.Forms.NumericUpDown m_numUpDownAcqTimeB;
        private System.Windows.Forms.Label m_labelAcqTimeB;
        private System.Windows.Forms.NumericUpDown m_numUpDownAcqTimeA;
        private System.Windows.Forms.Label m_labelAcqTimeA;
        private System.Windows.Forms.Label m_labelAcqTimeDValue;
        private System.Windows.Forms.Label m_labelAcqTimeCValue;
        private System.Windows.Forms.Label m_labelAcqTimeBValue;
        private System.Windows.Forms.Label m_labelAcqTimeAValue;
        private System.Windows.Forms.NumericUpDown m_numUpDownSeqChannels;
        private System.Windows.Forms.DataGridView m_dgvChannelsConfig;
        private System.Windows.Forms.Label m_labelSeqChannels;
        private System.Windows.Forms.DataGridViewTextBoxColumn colChannel;
        private System.Windows.Forms.DataGridViewCheckBoxColumn colChannelEnable;
        private System.Windows.Forms.DataGridViewComboBoxColumn colResolution;
        private System.Windows.Forms.DataGridViewComboBoxColumn colMode;
        private System.Windows.Forms.DataGridViewCheckBoxColumn colAveraged;
        private System.Windows.Forms.DataGridViewComboBoxColumn colAcqTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn colConvTime;
        private System.Windows.Forms.DataGridViewCheckBoxColumn colLimitDetect;
        private System.Windows.Forms.DataGridViewCheckBoxColumn colSaturation;
    }
}
