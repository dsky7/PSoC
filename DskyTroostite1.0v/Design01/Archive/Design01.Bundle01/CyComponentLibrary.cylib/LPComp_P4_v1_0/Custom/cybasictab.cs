/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace LPComp_P4_v1_0
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        CyImage m_symbol;
        CyImage m_graph;

        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructor(s)
        public CyBasicTab(CyParameters param)
            : base(param)
        {
            m_params.m_basicTab = this;

            InitializeComponent();

            rbHysteresisDisable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbHysteresisEnable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptDisabled.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptRising.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptFalling.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbInterruptBoth.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbFilterDisable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbFilterEnable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedSlow.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedMedium.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbSpeedHigh.CheckedChanged += new EventHandler(rb_CheckedChanged);

            m_symbol = new CyImage();
            m_graph = new CyImage();
            RedrawGraphs();

        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            rbHysteresisEnable.Checked = (m_params.Hysteresis == CyHysteresisType.LPC_ENABLE_HYST);
            rbHysteresisDisable.Checked = !rbHysteresisEnable.Checked;

            rbFilterDisable.Checked = (m_params.Filter == CyFilterType.LPC_DISABLE_DFLT);
            rbFilterEnable.Checked = !rbFilterDisable.Checked;

            rbInterruptDisabled.Checked = (m_params.Interrupt == CyInterruptType.LPC_INT_DISABLE);
            rbInterruptRising.Checked = (m_params.Interrupt == CyInterruptType.LPC_INT_RISING);
            rbInterruptFalling.Checked = (m_params.Interrupt == CyInterruptType.LPC_INT_FALLING);
            rbInterruptBoth.Checked = (m_params.Interrupt == CyInterruptType.LPC_INT_BOTH);

            rbSpeedSlow.Checked = (m_params.Speed == CySpeedType.LPC_LOW_SPEED);
            rbSpeedMedium.Checked = (m_params.Speed == CySpeedType.LPC_MED_SPEED);
            rbSpeedHigh.Checked = (m_params.Speed == CySpeedType.LPC_HIGH_SPEED);
        }

        void RedrawGraphs()
        {
            m_graph.m_hysteresis = m_params.Hysteresis;
            m_graph.m_interrupt = m_params.Interrupt;
            m_graph.m_power = m_params.Speed;
            m_graph.m_imageSize = pbGraph.Size;
            m_graph.UpdateGraph();
            pbGraph.Image = m_graph.m_bmp;

            m_symbol.m_hysteresis = m_params.Hysteresis;
            m_symbol.m_interrupt = m_params.Interrupt;
            m_symbol.m_power = m_params.Speed;
            m_symbol.m_imageSize = pbSymbol.Size;
            m_symbol.UpdateSymbol();
            pbSymbol.Image = m_symbol.m_bmp;
        }
        #endregion

        #region Event handlers
        void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false)
                return;

            else if (rb == rbHysteresisEnable)
                m_params.Hysteresis = CyHysteresisType.LPC_ENABLE_HYST;
            else if (rb == rbHysteresisDisable)
                m_params.Hysteresis = CyHysteresisType.LPC_DISABLE_HYST;

            else if (rb == rbInterruptDisabled)
                m_params.Interrupt = CyInterruptType.LPC_INT_DISABLE;
            else if (rb == rbInterruptRising)
                m_params.Interrupt = CyInterruptType.LPC_INT_RISING;
            else if (rb == rbInterruptFalling)
                m_params.Interrupt = CyInterruptType.LPC_INT_FALLING;
            else if (rb == rbInterruptBoth)
                m_params.Interrupt = CyInterruptType.LPC_INT_BOTH;

            else if (rb == rbFilterDisable)
                m_params.Filter = CyFilterType.LPC_DISABLE_DFLT;
            else if (rb == rbFilterEnable)
                m_params.Filter = CyFilterType.LPC_ENABLE_DFLT;

            else if (rb == rbSpeedSlow)
                m_params.Speed = CySpeedType.LPC_LOW_SPEED;
            else if (rb == rbSpeedMedium)
                m_params.Speed = CySpeedType.LPC_MED_SPEED;
            else if (rb == rbSpeedHigh)
                m_params.Speed = CySpeedType.LPC_HIGH_SPEED;

            RedrawGraphs();

        }
        #endregion Event handlers

    }
}
