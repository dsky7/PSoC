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

namespace Comp_P4_v1_0
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
            InitializeComponent();

            rbHysteresisDisable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbHysteresisEnable.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbPolarityInv.CheckedChanged += new EventHandler(rb_CheckedChanged);
            rbPolarityNonInv.CheckedChanged += new EventHandler(rb_CheckedChanged);
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
            rbHysteresisEnable.Checked = (m_params.Hysteresis == CyHysteresisType.CMP_ENABLE_HYST);
            rbHysteresisDisable.Checked = !rbHysteresisEnable.Checked;

            rbPolarityInv.Checked = (m_params.Polarity == CyPolarityType.CMP_INVERTING);
            rbPolarityNonInv.Checked = !rbPolarityInv.Checked;

            rbSpeedSlow.Checked = (m_params.Power == CyPowerType.CMP_LOW_POWER);
            rbSpeedMedium.Checked = (m_params.Power == CyPowerType.CMP_MED_POWER);
            rbSpeedHigh.Checked = (m_params.Power == CyPowerType.CMP_HIGH_POWER);
        }

        void RedrawGraphs()
        {
            m_graph.m_hysteresis = m_params.Hysteresis;
            m_graph.m_polarity = m_params.Polarity;
            m_graph.m_power = m_params.Power;
            m_graph.m_imageSize = pbGraph.Size;
            m_graph.UpdateGraph();
            pbGraph.Image = m_graph.m_bmp;

            m_symbol.m_hysteresis = m_params.Hysteresis;
            m_symbol.m_polarity = m_params.Polarity;
            m_symbol.m_power = m_params.Power;
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
                m_params.Hysteresis = CyHysteresisType.CMP_ENABLE_HYST;
            else if (rb == rbHysteresisDisable)
                m_params.Hysteresis = CyHysteresisType.CMP_DISABLE_HYST;
            else if (rb == rbPolarityInv)
                m_params.Polarity = CyPolarityType.CMP_INVERTING;
            else if (rb == rbPolarityNonInv)
                m_params.Polarity = CyPolarityType.CMP_NON_INVERTING;

            else if (rb == rbSpeedSlow)
                m_params.Power = CyPowerType.CMP_LOW_POWER;
            else if (rb == rbSpeedMedium)
                m_params.Power = CyPowerType.CMP_MED_POWER;
            else if (rb == rbSpeedHigh)
                m_params.Power = CyPowerType.CMP_HIGH_POWER;

            RedrawGraphs();

        }
        #endregion Event handlers

    }
}
