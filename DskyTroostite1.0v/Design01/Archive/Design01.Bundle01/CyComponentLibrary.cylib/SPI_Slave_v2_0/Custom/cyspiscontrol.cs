/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SPI_Slave_v2_0
{
    public partial class CySPIMControl : UserControl, ICyParamEditingControl
    {
        private CySPIMParameters m_params;

        #region Constants
        // Image constants
        public const int PB_SPIMTEXT_WIDTH = 40;
        public const int PB_EXTENTS_BORDER = 5;
        public const int PB_POLYGON_WIDTH = 4;
        public const int NUM_WAVEFORMS = 5;

        // Unit constants
        public const int POW6 = 1000000;
        public const int POW3 = 1000;
        #endregion

        #region Constructor(s)
        public CySPIMControl(CySPIMParameters inst)
        {
            InitializeComponent();

            inst.m_basicTab = this;
            this.Dock = DockStyle.Fill;
            m_params = inst;

            // Set the SPIM Mode Combo Box from Enums
            cbMode.DataSource = m_params.m_modeList;

            // Set Bidirect Mode ComboBox
            cbDataLines.Items.Add(CyBidirectMode.MISO_MOSI);
            cbDataLines.Items.Add(CyBidirectMode.BI_DIRECTIONAL);

            // Set ShiftDir Combo Box from Enums
            cbShiftDir.DataSource = m_params.m_shiftDirectionList;

            // Event Handlers declaration
            numDataBits.TextChanged += new EventHandler(numDataBits_TextChanged);
            numBitRateHertz.TextChanged += new EventHandler(numBitRateHertz_TextChanged);

            // NumericsUpDown Settings
            numDataBits.Minimum = 0;
            numDataBits.Maximum = 16;
            numBitRateHertz.Minimum = 0;
            numBitRateHertz.Maximum = int.MaxValue;

            // Set bitrate units
            cbBitRateHertz.SelectedIndex = (m_params.DesiredBitRate > POW6) ? 1 : 0;
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string paramName in m_params.m_inst.GetParamNames())
            {
                CyCompDevParam param = m_params.m_inst.GetCommittedParam(paramName);
                if (param.TabName.Equals(CyCustomizer.BASIC_TABNAME))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
        }
        #endregion

        #region Assigning parameters values to controls
        public void GetParams()
        {
            // Mode
            switch (m_params.Mode)
            {
                case E_SPI_MODES.Mode_00:
                    cbMode.SelectedIndex = 0;
                    break;
                case E_SPI_MODES.Mode_01:
                    cbMode.SelectedIndex = 1;
                    break;
                case E_SPI_MODES.Mode_10:
                    cbMode.SelectedIndex = 2;
                    break;
                case E_SPI_MODES.Mode_11:
                    cbMode.SelectedIndex = 3;
                    break;
                default:
                    break;
            }

            // BidirectMode
            cbDataLines.SelectedItem = m_params.BidirectMode ? CyBidirectMode.BI_DIRECTIONAL
                : CyBidirectMode.MISO_MOSI;

            // NumberOfDataBits
            numDataBits.Text = m_params.NumberOfDataBits.Value.ToString();

            // ShiftDir
            cbShiftDir.SelectedItem = CyEnumConverter.GetEnumDesc(m_params.ShiftDir);

            // DesiredBitRate
            SetBitRateAvailability();
            decimal freq = m_params.DesiredBitRate.Value / ((cbBitRateHertz.SelectedIndex == 0) ? POW3 : POW6);
            numBitRateHertz.Text = freq.ToString();
        }
        #endregion

        #region Assigning controls values to parameters
        private void SetMode()
        {
            switch (cbMode.SelectedIndex)
            {
                case 0:
                    m_params.Mode = E_SPI_MODES.Mode_00;
                    break;
                case 1:
                    m_params.Mode = E_SPI_MODES.Mode_01;
                    break;
                case 2:
                    m_params.Mode = E_SPI_MODES.Mode_10;
                    break;
                case 3:
                    m_params.Mode = E_SPI_MODES.Mode_11;
                    break;
                default:
                    break;
            }
            m_params.SetParams(CyParamNames.MODE);
        }

        private void SetBidirectMode()
        {
            switch (cbDataLines.Text)
            {
                case CyBidirectMode.BI_DIRECTIONAL:
                    m_params.BidirectMode = true;
                    break;
                case CyBidirectMode.MISO_MOSI:
                    m_params.BidirectMode = false;
                    break;
                default:
                    break;
            }
            m_params.SetParams(CyParamNames.BIDIRECT_MODE);
        }

        private void SetNumberOfDataBits()
        {
            try
            {
                m_params.NumberOfDataBits = byte.Parse(numDataBits.Text);
            }
            catch (Exception)
            {
                m_params.NumberOfDataBits = null;
            }
            m_params.SetParams(CyParamNames.NUMBER_OF_DATA_BITS);
        }

        private void SetShiftDir()
        {
            m_params.ShiftDir = (E_B_SPI_MASTER_SHIFT_DIRECTION)CyEnumConverter.GetEnumValue(
                cbShiftDir.Text, typeof(E_B_SPI_MASTER_SHIFT_DIRECTION));
            m_params.SetParams(CyParamNames.SHIFT_DIR);
        }

        private void SetDesiredBitRate()
        {
            if (m_params.m_basicTab.Visible && m_params.m_bGlobalEditMode)
            {
                decimal val = 0;
                decimal freq = 0;
                if (decimal.TryParse(numBitRateHertz.Text, out val))
                {
                    try
                    {
                    freq = val * ((cbBitRateHertz.SelectedIndex == 0) ? POW3 : POW6);
                    m_params.DesiredBitRate = (decimal)freq;
                }
                    catch 
                    {
                        m_params.DesiredBitRate = null;
                    }
                }
                else
                {
                    m_params.DesiredBitRate = null;
                }
                    m_params.SetParams(CyParamNames.DESIRED_BIT_RATE);
                }
            }
        #endregion

        #region Bitrate Settings
        public void SetBitRateAvailability()
        {
            if (m_params.ClockInternal)
            {
                cbBitRateHertz.Enabled = true;
                cbBitRateHertz.Visible = true;
                numBitRateHertz.Enabled = true;
                numBitRateHertz.Visible = true;
                lblCalculatedBitRate.Visible = false;
                SetBitrateValue();
            }
            else
            {
                cbBitRateHertz.Enabled = false;
                cbBitRateHertz.Visible = false;
                numBitRateHertz.Enabled = false;
                numBitRateHertz.Visible = false;
                lblCalculatedBitRate.Visible = true;
                SetBitrateValue();
                lblCalculatedBitRate.Text = "1/2 Input Clock Frequency";
            }
        }

        public void SetBitrateValue()
        {
            decimal bitrate = m_params.DesiredBitRate.Value;
            if (bitrate > POW6)
            {
                SetBitRateDecimalPlaces(bitrate, POW6);
                numBitRateHertz.Value = Convert.ToDecimal(bitrate / POW6);
                cbBitRateHertz.SelectedIndex = 1;
            }
            else
            {
                SetBitRateDecimalPlaces(bitrate, POW3);
                numBitRateHertz.Value = Convert.ToDecimal(bitrate / POW3);
                cbBitRateHertz.SelectedIndex = 0;
            }
        }

        private void SetBitRateDecimalPlaces(decimal bitrate, decimal denominator)
        {
            decimal bitrateDevided = Convert.ToDecimal(bitrate / denominator);
            string textBitrate = bitrateDevided.ToString();
            if (textBitrate.Contains("."))
            {
                int start = textBitrate.LastIndexOf(".");
                numBitRateHertz.DecimalPlaces = textBitrate.Substring(start + 1).Length;
            }
        }
        #endregion

        #region Event Handlers
        private void CySPIMControl_Load(object sender, EventArgs e)
        {
            UpdateDrawing();
        }

        private void numDataBits_TextChanged(object sender, EventArgs e)
        {
            SetNumberOfDataBits();
            if (NumUpDownValidated(sender))
            {
                UpdateDrawing();
            }
        }

        private void cbMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetMode();
            UpdateDrawing();
        }

        private void cbDataLines_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetBidirectMode();
        }

        private void cbShiftDir_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetShiftDir();
            UpdateDrawing();
        }

        private void numBitRateHertz_TextChanged(object sender, EventArgs e)
        {
            NumUpDownValidated(sender);
                SetDesiredBitRate();
        }

        private void cbBitRateHertz_SelectedIndexChanged(object sender, EventArgs e)
        {
            NumUpDownValidated(sender);
                SetDesiredBitRate();
        }

        private void numBitRateHertz_Leave(object sender, EventArgs e)
        {
            char[] charsToTrim = { '0' };
            if (numBitRateHertz.Text.Contains("."))
                numBitRateHertz.Text = numBitRateHertz.Text.TrimEnd(charsToTrim);
        }

        private bool NumUpDownValidated(object sender)
        {
            decimal value = 0;
            decimal multiplier = 0;
            decimal min = 0;
            decimal max = 0;
            string message = "";
            bool result = false;
            string numericText = string.Empty;

            if (sender == cbBitRateHertz) sender = numBitRateHertz;
            numericText = ((CyNumericUpDown)sender).Text;
            if (sender == numBitRateHertz)
            {
                min = CyParamRange.FREQUENCY_MIN;
                max = CyParamRange.FREQUENCY_MAX;
                message = Properties.Resources.FrequencyEPMsg;
                multiplier = ((cbBitRateHertz.SelectedIndex == 0) ? POW3 : POW6);
            }
            else if (sender == numDataBits)
            {
                min = CyParamRange.NUM_BITS_MIN;
                max = CyParamRange.NUM_BITS_MAX;
                message = string.Format(Properties.Resources.NumOfDataBitsEPMsg, min, max);
                multiplier = 1;
                if (numericText.EndsWith(".") || numericText.EndsWith(","))
                {
                    ep_Errors.SetError((CyNumericUpDown)sender, string.Format(message));
                    return result;
                }
            }
            if (decimal.TryParse(numericText, out value))
            {
                try
                {
                    value *= multiplier;
                }
                catch {}
                if (value < min || value > max)
                {
                    ep_Errors.SetError((CyNumericUpDown)sender, string.Format(message));
                }
                else
                {
                    ep_Errors.SetError((CyNumericUpDown)sender, "");
                    result = true;
                }
            }
            else
            { ep_Errors.SetError((CyNumericUpDown)sender, string.Format(message)); }
            return result;
        }
        #endregion

        #region Form Drawing
        public void UpdateDrawing()
        {
            if ((pbDrawing.Width == 0) || (pbDrawing.Height == 0))
                return;
            Image waveform = new Bitmap(pbDrawing.Width, pbDrawing.Height);
            Graphics wfg;
            wfg = Graphics.FromImage(waveform);
            wfg.Clear(Color.White);
            SolidBrush blkbrush = new SolidBrush(Color.Black);

            float extentsleft = PB_EXTENTS_BORDER + PB_SPIMTEXT_WIDTH;
            float extentsright = pbDrawing.Width - PB_EXTENTS_BORDER;
            float padding = (extentsright - extentsleft) / 70;
            float startleft = extentsleft + padding;
            float endright = extentsright - padding;
            float startright = startleft + (endright - startleft) / 2;

            // Setup the right, left and center indicators
            Pen extentspen = new Pen(blkbrush);
            extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            // Draw the Left Extents Line
            wfg.DrawLine(extentspen, extentsleft, PB_EXTENTS_BORDER,
                extentsleft, pbDrawing.Height - PB_EXTENTS_BORDER);
            // Draw the Right Extents Line
            wfg.DrawLine(extentspen, extentsright, PB_EXTENTS_BORDER,
                extentsright, pbDrawing.Height - PB_EXTENTS_BORDER);

            extentspen.Dispose();

            // Setup and draw all of the waveforms
            int numwaveforms = NUM_WAVEFORMS;
            string[] wfnames = new string[NUM_WAVEFORMS];

            wfnames[0] = "SS";
            wfnames[1] = "SCLK";
            wfnames[2] = "MOSI";
            wfnames[3] = "MISO";
            wfnames[4] = "Sample";

            Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);

            // Each waveform's height is dependent upon the drawing size minus a top and bottom border 
            // and the top period waveform which is the size of two polygon widths, and an bottom 
            // ticker tape of 2 polygon widths
            float wfheight = (pbDrawing.Height - (2 * PB_EXTENTS_BORDER) - (4 * PB_POLYGON_WIDTH)) / numwaveforms;
            // Fill in All Waveform Names
            for (int i = 0; i < numwaveforms; i++)
            {
                PointF pt = new PointF(extentsleft - wfg.MeasureString(wfnames[i], perfont).Width - PB_EXTENTS_BORDER,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 2) -
                    (wfg.MeasureString(wfnames[i], perfont).Height / 2));
                wfg.DrawString(wfnames[i], perfont, blkbrush, pt);
            }

            // Draw Waveforms
            int numsegments = 2 + (Convert.ToInt16(m_params.NumberOfDataBits) * 2) + 3;

            for (int i = 0; i < numwaveforms; i++)
            {
                float HighY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 8);
                float LowY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * (i + 1));
                float segwidth = (extentsright - extentsleft) / numsegments;
                List<float> segsx = new List<float>();
                for (int x = 0; x < numsegments; x++)
                {
                    segsx.Add(extentsleft + (x * segwidth));
                }
                SolidBrush wfbrush = new SolidBrush(Color.Blue);
                Pen wfPen = new Pen(wfbrush);
                int NumDataBits = Convert.ToInt16(m_params.NumberOfDataBits);
                string val = null;
                bool ShiftDir = (Convert.ToInt16(m_params.ShiftDir) == 0) ? false : true;
                int j = 0;
                bool mode = ((Convert.ToInt16(m_params.Mode) == 0) ||
                    (Convert.ToInt16(m_params.Mode) == 1)) ? true : false;
                bool starthigh = ((Convert.ToInt16(m_params.Mode) == 0) ||
                    (Convert.ToInt16(m_params.Mode) == 2)) ? false : true;
                switch (wfnames[i])
                {
                    case "SS":
                        wfg.DrawLine(wfPen, segsx[0], HighY, segsx[2], HighY);
                        wfg.DrawLine(wfPen, segsx[2], HighY, segsx[2], LowY);
                        wfg.DrawLine(wfPen, segsx[2], LowY, segsx[numsegments - 2], LowY);
                        wfg.DrawLine(wfPen, segsx[numsegments - 2], LowY, segsx[numsegments - 2], HighY);
                        wfg.DrawLine(wfPen, segsx[numsegments - 2], HighY, segsx[numsegments - 1], HighY);
                        break;
                    case "MOSI":
                    case "MISO":
                        if (mode)
                        {
                            // Draw Bus to First Transition Point
                            wfg.DrawLine(wfPen, segsx[0], HighY, segsx[2] - 2, HighY);
                            wfg.DrawLine(wfPen, segsx[0], LowY, segsx[2] - 2, LowY);
                            // Draw Transition
                            wfg.DrawLine(wfPen, segsx[2] - 2, HighY, segsx[2] + 2, LowY);
                            wfg.DrawLine(wfPen, segsx[2] - 2, LowY, segsx[2] + 2, HighY);
                            for (j = 0; j < (NumDataBits * 2); )
                            {
                                // Draw Bus to Transition Point
                                wfg.DrawLine(wfPen, segsx[2 + j] + 2, HighY, segsx[2 + (j + 2)] - 2, HighY);
                                wfg.DrawLine(wfPen, segsx[2 + j] + 2, LowY, segsx[2 + (j + 2)] - 2, LowY);

                                // Draw Transition
                                wfg.DrawLine(wfPen, segsx[2 + (j + 2)] - 2, HighY, segsx[2 + (j + 2)] + 2, LowY);
                                wfg.DrawLine(wfPen, segsx[2 + (j + 2)] - 2, LowY, segsx[2 + (j + 2)] + 2, HighY);

                                if (ShiftDir)
                                    val = String.Format("D{0}", j / 2);
                                else
                                    val = String.Format("D{0}", NumDataBits - (j / 2) - 1);

                                SizeF strsize = wfg.MeasureString(val, perfont);
                                float centerx = segsx[2 + j] + segwidth;
                                wfg.DrawString(val, perfont, new SolidBrush(Color.Black),
                                                new RectangleF(centerx - (strsize.Width / 2f), HighY + ((wfheight) / 2f)
                                                    - (strsize.Height / 2f), strsize.Width, strsize.Height));
                                j += 2;
                            }
                            // Draw Bus to Transition Point
                            wfg.DrawLine(wfPen, segsx[2 + j] + 2, LowY, segsx[2 + (j + 2)], LowY);
                            wfg.DrawLine(wfPen, segsx[2 + j] + 2, HighY, segsx[2 + (j + 2)], HighY);
                        }
                        else
                        {
                            // Draw Bus to First Transition Point
                            wfg.DrawLine(wfPen, segsx[0], HighY, segsx[3] - 2, HighY);
                            wfg.DrawLine(wfPen, segsx[0], LowY, segsx[3] - 2, LowY);
                            // Draw Transition
                            wfg.DrawLine(wfPen, segsx[3] - 2, HighY, segsx[3] + 2, LowY);
                            wfg.DrawLine(wfPen, segsx[3] - 2, LowY, segsx[3] + 2, HighY);
                            for (j = 0; j < (NumDataBits * 2); )
                            {
                                // Draw Bus to Transition Point
                                wfg.DrawLine(wfPen, segsx[3 + j] + 2, HighY, segsx[3 + (j + 2)] - 2, HighY);
                                wfg.DrawLine(wfPen, segsx[3 + j] + 2, LowY, segsx[3 + (j + 2)] - 2, LowY);

                                // Draw Transition
                                wfg.DrawLine(wfPen, segsx[3 + (j + 2)] - 2, HighY, segsx[3 + (j + 2)] + 2, LowY);
                                wfg.DrawLine(wfPen, segsx[3 + (j + 2)] - 2, LowY, segsx[3 + (j + 2)] + 2, HighY);

                                if (ShiftDir)
                                    val = String.Format("D{0}", j / 2);
                                else
                                    val = String.Format("D{0}", NumDataBits - (j / 2) - 1);

                                SizeF strsize = wfg.MeasureString(val, perfont);
                                float centerx = segsx[3 + j] + segwidth;
                                wfg.DrawString(val, perfont, new SolidBrush(Color.Black),
                                                new RectangleF(centerx - (strsize.Width / 2f), HighY + ((wfheight) / 2f)
                                                    - (strsize.Height / 2f), strsize.Width, strsize.Height));
                                j += 2;
                            }
                            // Draw Bus to Transition Point
                            wfg.DrawLine(wfPen, segsx[3 + j] + 2, LowY, segsx[3 + (j + 1)], LowY);
                            wfg.DrawLine(wfPen, segsx[3 + j] + 2, HighY, segsx[3 + (j + 1)], HighY);
                        }
                        break;
                    case "SCLK":

                        wfg.DrawLine(wfPen, segsx[0], starthigh ? HighY : LowY, segsx[3], starthigh ? HighY : LowY);
                        wfg.DrawLine(wfPen, segsx[3], starthigh ? HighY : LowY, segsx[3], starthigh ? HighY : LowY);
                        for (j = 0; j < (NumDataBits * 2); )
                        {
                            wfg.DrawLine(wfPen, segsx[3 + j], starthigh ? HighY : LowY,
                                segsx[3 + j], starthigh ? LowY : HighY);
                            wfg.DrawLine(wfPen, segsx[3 + j++], starthigh ? LowY : HighY,
                                segsx[3 + j], starthigh ? LowY : HighY);
                            wfg.DrawLine(wfPen, segsx[3 + j], starthigh ? LowY : HighY,
                                segsx[3 + j], starthigh ? HighY : LowY);
                            wfg.DrawLine(wfPen, segsx[3 + j++], starthigh ? HighY : LowY,
                                segsx[3 + j], starthigh ? HighY : LowY);
                        }
                        wfg.DrawLine(wfPen, segsx[3 + j++], starthigh ? HighY : LowY,
                            segsx[3 + j], starthigh ? HighY : LowY);
                        break;
                    case "Sample":
                        if (mode)
                        {
                            wfg.DrawLine(wfPen, segsx[0], LowY, segsx[3] - 2, LowY);    //Go to first edge 
                            for (j = 0; j < (NumDataBits * 2); )
                            {
                                wfg.DrawLine(wfPen, segsx[3 + j] - 2, LowY, segsx[3 + j] - 2, HighY);
                                wfg.DrawLine(wfPen, segsx[3 + j] - 2, HighY, segsx[3 + j] + 2, HighY);
                                wfg.DrawLine(wfPen, segsx[3 + j] + 2, HighY, segsx[3 + j] + 2, LowY);
                                wfg.DrawLine(wfPen, segsx[3 + j] + 2, LowY, segsx[3 + (j + 2)] - 2, LowY);
                                j += 2;
                            }
                            wfg.DrawLine(wfPen, segsx[3 + j] - 2, LowY, segsx[3 + (j + 1)], LowY);
                        }
                        else
                        {
                            wfg.DrawLine(wfPen, segsx[0], LowY, segsx[4] - 2, LowY);    //Go to first edge 
                            for (j = 0; j < (NumDataBits * 2); )
                            {
                                wfg.DrawLine(wfPen, segsx[4 + j] - 2, LowY, segsx[4 + j] - 2, HighY);
                                wfg.DrawLine(wfPen, segsx[4 + j] - 2, HighY, segsx[4 + j] + 2, HighY);
                                wfg.DrawLine(wfPen, segsx[4 + j] + 2, HighY, segsx[4 + j] + 2, LowY);
                                wfg.DrawLine(wfPen, segsx[4 + j] + 2, LowY, segsx[4 + (j + 2)] - 2, LowY);
                                j += 2;
                            }
                            wfg.DrawLine(wfPen, segsx[4 + j] - 2, LowY, segsx[4 + j], LowY);
                        }
                        break;
                    case "Interrupt":
                        break;
                }
            }
            wfg.Dispose();
            pbDrawing.Image = waveform;
        }
        #endregion

        #region Control Overrided Methods
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Enter)
            {
                SendKeys.Send("{TAB}");
                return true;
            }
            else
                return base.ProcessCmdKey(ref msg, keyData);
        }
        #endregion
    }

    #region Override NumericUpDown Class
    public class CyNumericUpDown : NumericUpDown
    {
        private bool m_allowNegative;

        public CyNumericUpDown()
        {
            this.AllowNegative = false;
        }

        public bool AllowNegative
        {
            get { return m_allowNegative; }
            set { m_allowNegative = value; }
        }

        public override void UpButton()
        {
            decimal x;
            if (decimal.TryParse(this.Text, out x))
            {
                x = x + this.Increment;
                this.Text = x.ToString();
            }
        }

        public override void DownButton()
        {
            decimal x;
            if (decimal.TryParse(this.Text, out x))
            {
                if (m_allowNegative)
                {
                    x = x - this.Increment;
                    this.Text = x.ToString();
                }
                else
                {
                    if ((x - this.Increment) >= 0)
                    {
                        x = x - this.Increment;
                        this.Text = x.ToString();
                    }
                }
            }
        }

        protected override void UpdateEditText()
        {
            // NOTHING TO DO HERE
        }
    }
    #endregion

    public class CyBidirectMode
    {
        public const string MISO_MOSI = "MOSI + MISO";
        public const string BI_DIRECTIONAL = "Bi-Directional";
    }
}
