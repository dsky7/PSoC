/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;

namespace QuadDec_v1_20
{
    class CyTab2 : UserControl, ICyParamEditingControl
    {
        private CyParameters m_params;
        private EventHandler m_checkHandler;

        public CyTab2(CyParameters newParams)
        {
            InitializeComponent();
            AttachEvents();

            m_params = newParams;
            this.Dock = DockStyle.Fill;

            UpdateFromParam();
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            return new CyCustErr[] { };
        }

        #endregion

        public void UpdateFromParam()
        {
            DetachEvents();
            SetCheckboxes();
            cyDiagram1.CounterResolution = m_params.CounterResolution;
            AttachEvents();
        }

        private void SetCheckboxes()
        {
            for (int i = 0; i < Controls.Count; i++)
            {
                if (Controls[i] is RadioButton)
                {
                    RadioButton currBox = (RadioButton)Controls[i];
                    currBox.Checked = (currBox.Name == "x" + m_params.CounterResolution.ToString() + "RB");
                }
            }
        }

        private byte GetCheckboxes()
        {
            byte result = 0;
            if (x1RB.Checked) { result = 1; }
            if (x2RB.Checked) { result = 2; }
            if (x4RB.Checked) { result = 4; }
            cyDiagram1.CounterResolution = result;
            return result;
        }

        private void AttachEvents()
        {
            if (m_checkHandler == null)
            {
                m_checkHandler = new EventHandler(xRB_CheckedChanged);
            }
            x1RB.CheckedChanged += m_checkHandler;
            x2RB.CheckedChanged += m_checkHandler;
            x4RB.CheckedChanged += m_checkHandler;
        }

        private void DetachEvents()
        {
            if (m_checkHandler != null)
            {
                x1RB.CheckedChanged -= m_checkHandler;
                x2RB.CheckedChanged -= m_checkHandler;
                x4RB.CheckedChanged -= m_checkHandler;
            }
        }

        private void xRB_CheckedChanged(object sender, EventArgs e)
        {
            m_params.CounterResolution = GetCheckboxes();
        }

        #region Auto-generated code

        private Label descriptionLabel;
        private RadioButton x1RB;
        private RadioButton x2RB;
        private RadioButton x4RB;
        private CyDiagram cyDiagram1;

        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyTab2));
            this.descriptionLabel = new System.Windows.Forms.Label();
            this.x1RB = new System.Windows.Forms.RadioButton();
            this.x2RB = new System.Windows.Forms.RadioButton();
            this.x4RB = new System.Windows.Forms.RadioButton();
            this.cyDiagram1 = new QuadDec_v1_20.CyDiagram();
            this.SuspendLayout();
            // 
            // descriptionLabel
            // 
            this.descriptionLabel.Location = new System.Drawing.Point(3, 3);
            this.descriptionLabel.Name = "descriptionLabel";
            this.descriptionLabel.Size = new System.Drawing.Size(475, 58);
            this.descriptionLabel.TabIndex = 1;
            this.descriptionLabel.Text = resources.GetString("descriptionLabel.Text");
            // 
            // x1RB
            // 
            this.x1RB.AutoSize = true;
            this.x1RB.Location = new System.Drawing.Point(6, 80);
            this.x1RB.Name = "x1RB";
            this.x1RB.Size = new System.Drawing.Size(40, 21);
            this.x1RB.TabIndex = 2;
            this.x1RB.TabStop = true;
            this.x1RB.Text = "1x";
            this.x1RB.UseVisualStyleBackColor = true;
            // 
            // x2RB
            // 
            this.x2RB.AutoSize = true;
            this.x2RB.Location = new System.Drawing.Point(64, 80);
            this.x2RB.Name = "x2RB";
            this.x2RB.Size = new System.Drawing.Size(40, 21);
            this.x2RB.TabIndex = 3;
            this.x2RB.TabStop = true;
            this.x2RB.Text = "2x";
            this.x2RB.UseVisualStyleBackColor = true;
            // 
            // x4RB
            // 
            this.x4RB.AutoSize = true;
            this.x4RB.Location = new System.Drawing.Point(122, 80);
            this.x4RB.Name = "x4RB";
            this.x4RB.Size = new System.Drawing.Size(40, 21);
            this.x4RB.TabIndex = 4;
            this.x4RB.TabStop = true;
            this.x4RB.Text = "4x";
            this.x4RB.UseVisualStyleBackColor = true;
            // 
            // cyDiagram1
            // 
            this.cyDiagram1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cyDiagram1.AutoSize = true;
            this.cyDiagram1.BackColor = System.Drawing.Color.White;
            this.cyDiagram1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.cyDiagram1.CounterResolution = ((byte)(4));
            this.cyDiagram1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.cyDiagram1.Location = new System.Drawing.Point(3, 109);
            this.cyDiagram1.Margin = new System.Windows.Forms.Padding(5);
            this.cyDiagram1.Name = "cyDiagram1";
            this.cyDiagram1.Size = new System.Drawing.Size(475, 196);
            this.cyDiagram1.TabIndex = 9;
            this.cyDiagram1.UseFiltering = false;
            this.cyDiagram1.UseIndex = false;
            // 
            // CyTab2
            // 
            this.AutoScroll = true;
            this.Controls.Add(this.cyDiagram1);
            this.Controls.Add(this.x4RB);
            this.Controls.Add(this.x2RB);
            this.Controls.Add(this.x1RB);
            this.Controls.Add(this.descriptionLabel);
            this.Name = "CyTab2";
            this.Size = new System.Drawing.Size(482, 309);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
    }   
}
