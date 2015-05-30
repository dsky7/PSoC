/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SMBusSlave_v2_20
{
    public static class CyDividerCalculator
    {
        private static byte GetOversampleRate(ushort dataRate)
        {
            return (byte)((dataRate <= CyParamRange.DATA_RATE_THRESHOLD) ? 32 : 16);
        }

        public static byte GetPSoC3AndPSoC5LPDivider(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters parameters = new CyParameters(query);

            double busClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation);
            byte oversampleRate = GetOversampleRate(parameters.DataRate);

            double defaultClockDiv = (double)(busClockInKHz / (parameters.DataRate * oversampleRate));

            return (byte)defaultClockDiv;
        }

        public static byte GetPSoC5ADivider(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters parameters = new CyParameters(query);

            double busClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation);
            byte oversampleRate = GetOversampleRate(parameters.DataRate);

            // Value for saving power of Divide Factor
            int power = 0;

            // Create possible Baud Rate values
            List<double> baudRate = new List<double>();
            baudRate.Add(busClockInKHz / (1 * oversampleRate));
            baudRate.Add(busClockInKHz / (2 * oversampleRate));
            baudRate.Add(busClockInKHz / (4 * oversampleRate));
            baudRate.Add(busClockInKHz / (8 * oversampleRate));
            baudRate.Add(busClockInKHz / (16 * oversampleRate));
            baudRate.Add(busClockInKHz / (32 * oversampleRate));
            baudRate.Add(busClockInKHz / (64 * oversampleRate));

            // Find most close value (greater or equal) to Data Rate
            for (int i = baudRate.Count - 1; i >= 0; i--)
            {
                if (baudRate[i] >= parameters.DataRate)
                {
                    power = i;
                    break;
                }
            }

            return (byte)power;
        }

        public static string GetActualDataRateCalculatorLabel(CyParameters parameters, ICyTerminalQuery_v1 termQuery)
        {
            string labelText = string.Empty;
            string dataRateUnits = " kbps";

            // This clock depends on implementation - BusClock in FF and Internal in UDB
            double internalClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation);

            if (parameters.Implementation == CyEImplementationType.I2C__UDB)
            {
                double clockFreq = parameters.UdbInternalClock ? internalClockInKHz : parameters.m_extClock;

                // Actual Data Rate Calculation
                try
                {
                    labelText = (clockFreq > 0) ? string.Format(Math.Round((clockFreq / 16), 2).ToString() + " {0}",
                        dataRateUnits) : labelText = Resources.UnknownActualDataRate;
                }
                catch (Exception)
                {
                    labelText = Resources.UnknownActualDataRate;
                }
            }
            else
            {
                if (internalClockInKHz > 0)
                {
                    // Actual Data Rate Calculation
                    try
                    {
                        byte divider = 0;

                        if (parameters.IsPSoC5A) // PSoC5A
                        {
                            divider = (byte)Math.Pow(2, CyDividerCalculator.GetPSoC5ADivider(parameters.m_inst,
                                termQuery));
                        }
                        else // PSoC3 and PSoC5LP
                        {
                            divider = CyDividerCalculator.GetPSoC3AndPSoC5LPDivider(parameters.m_inst, termQuery);
                        }

                        double oversampleRate = (parameters.DataRate <= 50) ? 32 : 16;
                        labelText = string.Format(Math.Round(
                            (internalClockInKHz / (divider * oversampleRate)), 2).ToString() + " {0}", dataRateUnits);
                    }
                    catch (Exception)
                    {
                        labelText = Resources.UnknownActualDataRate;
                    }
                }
                else
                {
                    labelText = Resources.UnknownActualDataRate;
                }
            }
            return labelText;
        }

        public static void CalculateTimeout(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters parameters = new CyParameters(query);

            parameters.m_globalEditMode = true;

            // FF calculation
            double clockInKHz = CyClockReader.GetInternalClockInKHz(termQuery,
                CyEImplementationType.I2C__FixedFunction);
            if (clockInKHz > 0)
            {
                double tclk = 1 / (clockInKHz / 1024);
                UInt16 div = Convert.ToUInt16(Math.Ceiling(parameters.TimeOutMs / tclk));
                parameters.TimeoutPeriodFF = (div > CyParamRange.FF_DIVIDER_MAX) ? CyParamRange.FF_DIVIDER_MAX : div;
            }

            // UDB calculation
            if (parameters.UdbInternalClock)
            {
                clockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, CyEImplementationType.I2C__UDB);
            }
            else
            {
                clockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);
            }

            if (clockInKHz > 0)
            {
                double count = parameters.TimeOutMs * clockInKHz;
                if (count <= Math.Pow(2, 16))
                {
                    count--;
                    parameters.TimeoutPeriodUDB = Convert.ToUInt16(Math.Ceiling(count));
                    parameters.PrescalerEnabled = false;
                }
                else
                {
                    parameters.PrescalerEnabled = true;
                    UInt16 prescalerPeriod = 1;
                    while ((count / prescalerPeriod) >= Math.Pow(2, 16))
                    {
                        prescalerPeriod++;
                        if (prescalerPeriod == 256)
                            break;
                    }
                    parameters.TimeoutPeriodUDB = Convert.ToUInt16(Math.Ceiling(count / prescalerPeriod));
                    parameters.TimeoutPeriodUDB--;
                    prescalerPeriod--;
                    parameters.PrescalerPeriod = Convert.ToByte(prescalerPeriod);
                }
            }
        }
    }
}
