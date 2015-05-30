/*******************************************************************************
* Copyright 2012-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Extensions.Gde;

namespace SMBusSlave_v3_0
{
    public static class CyDividerCalculator
    {
        private const int OVS_FACTOR = 16;
        private const int OVS_FACTOR_FF_BELOW_THRESHOLD = 32;

        private static byte GetOversampleRate(ushort dataRate)
        {
            return (byte)((dataRate <= CyParamRange.DATA_RATE_THRESHOLD) ? OVS_FACTOR_FF_BELOW_THRESHOLD : OVS_FACTOR);
        }

        public static byte GetDivider(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyParameters parameters = new CyParameters(query);

            double busClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation, 
                                                                       parameters.IsPSoC4);
            byte oversampleRate = GetOversampleRate(parameters.DataRate);
            double defaultClockDiv = busClockInKHz / (parameters.DataRate * oversampleRate);

            return (byte)defaultClockDiv;
        }
                
        public static string GetActualDataRateCalculatorLabel(CyParameters parameters, ICyTerminalQuery_v1 termQuery)
        {
            string labelText = string.Empty;

            // This clock depends on implementation - BusClock in FF and Internal in UDB
            double internalClockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, parameters.Implementation, 
                                                                            parameters.IsPSoC4);

            if (parameters.IsPSoC4)
            {
                if (CyClockReader.IsFrequencyknown(internalClockInKHz))
                {
                    double actualDataRate = internalClockInKHz / parameters.OvsFactor;
                    labelText = FormatActualDataRate(actualDataRate);
                }
                else
                {
                    labelText = Resources.UnknownActualDataRate;
                }
            }
            else if (parameters.Implementation == CyEImplementationType.I2C__UDB)
            {
                double clockFreq = parameters.UdbInternalClock ? internalClockInKHz : parameters.m_extClock;

                labelText = (clockFreq > 0) ? FormatActualDataRate(clockFreq / OVS_FACTOR) : 
                    Resources.UnknownActualDataRate;
            }
            else
            {
                if (CyClockReader.IsFrequencyknown(internalClockInKHz))
                {
                    // Actual Data Rate Calculation
                    try
                    {
                        byte divider = GetDivider(parameters.InstQuery, termQuery);
                        double oversampleRate = GetOversampleRate(parameters.DataRate);
                        double actualDataRate = internalClockInKHz/(divider*oversampleRate);

                        labelText = FormatActualDataRate(actualDataRate);
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

            parameters.GlobalEditMode = true;

            // FF calculation
            double clockInKHz = CyClockReader.GetInternalClockInKHz(termQuery,
                CyEImplementationType.I2C__FixedFunction, parameters.IsPSoC4);
            if (CyClockReader.IsFrequencyknown(clockInKHz))
            {
                double tclk = 1 / (clockInKHz / 1024);
                UInt16 div = Convert.ToUInt16(Math.Ceiling(parameters.TimeOutMs / tclk));
                parameters.TimeoutPeriodFF = (div > CyParamRange.FF_DIVIDER_MAX) ? CyParamRange.FF_DIVIDER_MAX : div;
            }

            // UDB calculation
            if (parameters.UdbInternalClock)
            {
                clockInKHz = CyClockReader.GetInternalClockInKHz(termQuery, 
                                CyEImplementationType.I2C__UDB, parameters.IsPSoC4);
            }
            else
            {
                clockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);
            }

            if (CyClockReader.IsFrequencyknown(clockInKHz))
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

        private static string FormatActualDataRate(double dataRateValue)
        {
            const string DATA_RATE_UNITS = "kbps";
            return string.Format("{0} {1}", Math.Round(dataRateValue, 2), DATA_RATE_UNITS);
        }
    }
}
