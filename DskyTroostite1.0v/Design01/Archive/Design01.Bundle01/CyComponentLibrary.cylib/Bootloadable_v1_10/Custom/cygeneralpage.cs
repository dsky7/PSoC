/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Text.RegularExpressions;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace Bootloadable_v1_10
{
    public partial class CyGeneralPage : CyEditingWrapperControl
    {
        const uint MIN_VAL = 0;
        const uint MAX_VAL_16 = UInt16.MaxValue;
        const uint MAX_VAL_32 = UInt32.MaxValue;
        const string MAX_VAL_16_STR = "0xFFFF";
        const string MAX_VAL_32_STR = "0xFFFFFFFF";
        const string HEX_PREFIX = "0x";

        public CyGeneralPage()
        {
            InitializeComponent();
        }

        public CyGeneralPage(CyParameters parameters)
        {
            InitializeComponent();
            m_parameters = parameters;
            InitFields();
        }

        public void InitFields()
        {
            textBoxAppVersion.Text = HEX_PREFIX + m_parameters.AppVersion.ToString("X4");
            textBoxAppID.Text = HEX_PREFIX + m_parameters.AppID.ToString("X4");
            textBoxAppCustomID.Text = HEX_PREFIX + m_parameters.AppCustomID.ToString("X8");

            textBoxPlacementAddress.Text = HEX_PREFIX + m_parameters.PlacementAddress.ToString("X8");
            checkBoxAutoImage.Checked = !m_parameters.AutoPlacement;

            VerifyPlacementAddress();
        }

        private void checkBoxAutoImage_CheckedChanged(object sender, EventArgs e)
        {
            textBoxPlacementAddress.Enabled = checkBoxAutoImage.Checked;
            labelPlacementAddress.Enabled = textBoxPlacementAddress.Enabled;
            m_parameters.AutoPlacement = !checkBoxAutoImage.Checked;

            // Remove error for textBoxPlacementAddress if it's disabled
            if (textBoxPlacementAddress.Enabled)
                textBoxHex_Validated(textBoxPlacementAddress, EventArgs.Empty);
            else
                errProvider.SetError(textBoxPlacementAddress, "");
        }

        private void textBoxHex_Validated(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            uint val;
            if (!IsHex(tb.Text))
            {
                errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBFormat,
                                     (tb == textBoxAppCustomID) || (tb == textBoxPlacementAddress) ? 4 : 2));
            }
            else if ((tb == textBoxAppVersion) || (tb == textBoxAppID))
            {
                if (TryParseHex(tb.Text, out val))
                {
                    if (!CheckRange(val, MIN_VAL, MAX_VAL_16))
                    {
                        errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange,
                                                               MIN_VAL, MAX_VAL_16_STR));
                    }
                    else
                    {
                        ApplyTBValue(tb);
                    }
                }
                else
                {
                    errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange, MIN_VAL, MAX_VAL_16_STR));
                }
            }
            else if ((tb == textBoxAppCustomID) || (tb == textBoxPlacementAddress))
            {
                if (TryParseHex(tb.Text, out val))
                {
                    if (!CheckRange(val, MIN_VAL, MAX_VAL_32))
                    {
                        errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange,
                                                               MIN_VAL, MAX_VAL_32_STR));
                    }
                    else
                    {
                        ApplyTBValue(tb);

                        if (tb == textBoxPlacementAddress)
                        {
                            VerifyPlacementAddress();
                        }
                    }
                }
                else
                {
                    errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange, MIN_VAL, MAX_VAL_32_STR));
                }
            }
        }

        // Check if Placement Address is a multiple of FlashRowLength
        private void VerifyPlacementAddress()
        {
            if ((m_parameters.AutoPlacement == false) && 
                (m_parameters.PlacementAddress % m_parameters.FlashRowLength != 0))
            {
                errProvider.SetError(textBoxPlacementAddress, String.Format(Properties.Resources.ErrPlacementAddress,
                                     m_parameters.FlashRowLength));
            }
            else
            {
                errProvider.SetError(textBoxPlacementAddress, "");
            }
        }

        private void ApplyTBValue(TextBox tb)
        {
            uint val;
            errProvider.SetError(tb, "");
            TryParseHex(tb.Text, out val);
            if (tb == textBoxAppVersion)
                m_parameters.AppVersion = (UInt16)val;
            else if (tb == textBoxAppID)
                m_parameters.AppID = (UInt16)val;
            else if (tb == textBoxAppCustomID)
                m_parameters.AppCustomID = (UInt32)val;
            else if (tb == textBoxPlacementAddress)
                m_parameters.PlacementAddress = (UInt32)val;
        }

        public static bool TryParseHex(string value, out uint res)
        {
            bool success = false;
            res = 0;
            try
            {
                res = Convert.ToUInt32(value.Replace(HEX_PREFIX, ""), 16);
                success = true;
            }
            catch
            {
            }
            return success;
        }

        public static bool IsHex(string value)
        {
            Regex hexTemplate = new Regex("^(0x)?[0-9a-fA-F]{1,}$");
            return hexTemplate.IsMatch(value);
        }

        public static bool CheckRange(uint value, uint min, uint max)
        {
            return ((value >= min) && (value <= max));
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            errorList.AddRange(base.GetErrors());
            if (!String.IsNullOrEmpty(errProvider.GetError(textBoxAppVersion)) ||
                !String.IsNullOrEmpty(errProvider.GetError(textBoxAppID)) ||
                !String.IsNullOrEmpty(errProvider.GetError(textBoxAppCustomID)) ||
                (!String.IsNullOrEmpty(errProvider.GetError(textBoxPlacementAddress)) && 
                 (m_parameters.AutoPlacement == false)))
            {
                errorList.Add(new CyCustErr(Properties.Resources.ErrTBWrongValue));
            }

            return errorList.ToArray();
        }
    }
}
