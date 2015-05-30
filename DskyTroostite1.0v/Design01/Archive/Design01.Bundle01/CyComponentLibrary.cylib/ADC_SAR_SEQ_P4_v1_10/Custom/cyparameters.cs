/*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;
using System.Drawing;
using System.Xml.Serialization;
using System.Xml;
using System.IO;
using System.Diagnostics;

namespace ADC_SAR_SEQ_P4_v1_10
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // General Tab
        public const string ADJUST_TYPE = "AdcAdjust";
        public const string CLOCK_FREQUENCY = "AdcClockFrequency";
        public const string CLOCK_SOURCE_TYPE = "AdcClock";
        public const string SAMPLE_MODE_TYPE = "AdcSampleMode";

        public const string VREF_SELECT_TYPE = "AdcVrefSelect";
        public const string VREF_VALUE = "AdcVrefVoltage_mV";
        public const string INPUT_BUFFER_GAIN = "AdcInputBufGain";
        public const string SINGLE_ENDED_NEGATIVE_INPUT = "AdcSingleEndedNegativeInput";

        public const string DIFFERENTIAL_RESULT_FORMAT = "AdcDifferentialResultFormat";
        public const string SINGLE_ENDED_RESULT_FORMAT = "AdcSingleResultFormat";
        public const string DATA_FORMAT_JUSTIFICATION = "AdcDataFormatJustification";
        public const string SAMPLES_AVERAGED = "AdcAvgSamplesNum";
        public const string AVERAGING_MODE = "AdcAvgMode";
        public const string ALTERNATE_RESOLUTION = "AdcAlternateResolution";

        public const string LOW_LIMIT = "AdcLowLimit";
        public const string HIGH_LIMIT = "AdcHighLimit";
        public const string COMPARE_MODE = "AdcCompareMode";

        // Channels Tab
        public const string A_CLOCK = "AdcAClock";
        public const string B_CLOCK = "AdcBClock";
        public const string C_CLOCK = "AdcCClock";
        public const string D_CLOCK = "AdcDClock";

        public const string SEQUENCED_CHANNELS = "AdcSequencedChannels";
        public const string CHANNELS_CONFIG_TABLE = "SeqChannelsConfigTable";
        public const string CHANNELS_ENABLE_CONFIG = "AdcChannelsEnConf";
        public const string CHANNELS_MODE_CONFIG = "AdcChannelsModeConf";
        public const string INJ_CHANNEL_ENABLED = "AdcInjChannelEnabled";
        public const string SARMUX_CHANNELS_CONFIG = "AdcSarMuxChannelConfig";
        public const string ADC_HAS_SE_INPUT = "AdcSymbolHasSingleEndedInputChannel";
        public const string ADC_MAX_RESOLUTION = "AdcMaxResolution";
    }
    #endregion

    #region Parameters ranges
    public class CyParamRanges
    {
        public const byte NUM_MIN_CHANNELS = 1;
        public const byte NUM_MAX_CHANNELS_PSOC4A = 8;
        public const byte NUM_MAX_CHANNELS = 16;
        public const UInt32 MIN_CLOCK_FREQ_MHZ = 1;
        public const UInt32 MAX_CLOCK_FREQ_NOT_BYPASSED_KHZ = 3000;
        public const UInt32 MAX_CLOCK_FREQ_CY8C41_HZ = 14508000;
        public const UInt32 MAX_CLOCK_FREQ_MHZ = 18;
        public const UInt32 UNIT_MEGA = 1000000;
        public const UInt32 MIN_CLOCK_FREQ_HZ = MIN_CLOCK_FREQ_MHZ * UNIT_MEGA;
        public const UInt32 MAX_CLOCK_FREQ_HZ = MAX_CLOCK_FREQ_MHZ * UNIT_MEGA;
        public const UInt16 ADC_CLOCK_MIN_VALUE = 4;
        public const UInt16 ADC_CLOCK_MAX_VALUE = 1027;
        public const UInt16 COMP_LIMIT_MIN_VALUE = 0;
        public const UInt16 COMP_LIMIT_MAX_VALUE = UInt16.MaxValue;
        public const double VREF_MIN_VALUE = 0.01;

        // minimum pulse width value = 1/18Mhz = 55.55ns / 2 = 27.77ns - some margin (~+-4% CDT 91247) = 25.5ns.
        public const double MINIMUM_PULSE_WIDTH = 25.5;
    }
    #endregion

    #region Component Enums
    public enum CyESarAdcClockSrc { External = 0, Internal = 1 };
    public enum CyESampleMode { FreeRunning = 0, HardwareSOC = 1 };
    public enum CyEAdjust { ScanRate = 0, ClockFreq = 1 };

    public enum CyEVRefSelect
    {
        VDDA_2 = 0,
        VDDA = 1,
        Internal1024 = 2,
        Internal1024Bypassed = 3,
        InternalVref = 4,
        InternalVrefBypassed = 5,
        VDDA_2Bypassed = 6,
        ExternalVref = 7
    }

    public enum CyEInputBufferGain
    {
        Disabled = 0,
        One = 1,
        Two = 2,
        Four = 3,
        Eight = 4,
        Sixteen = 5
    }

    public enum CyESingleEndedNegativeInput
    {
        Vss = 0,
        Vref = 1,
        Other = 2
    }

    public enum CyEResolution
    {
        [Description("12")]
        Twelve,
        [Description("ALT")]
        Alternative
    }

    public enum CyEMode
    {
        [Description("Diff")]
        Diff,
        [Description("Single")]
        Single
    }

    public enum CyEAcquisionTime
    {
        [Description("4 clks")]
        FourClocks,
        [Description("A clks")]
        AClocks,
        [Description("B clks")]
        BClocks,
        [Description("C clks")]
        CClocks,
        [Description("D clks")]
        DClocks
    }

    public enum CyEResultFormat
    {
        FSigned = 1,
        FUnsigned = 0
    }

    public enum CyEFormatJustify
    {
        Right = 0,
        Left = 1
    }

    public enum CyESamplesAveraged
    {
        Rate2 = 0,
        Rate4 = 1,
        Rate8 = 2,
        Rate16 = 3,
        Rate32 = 4,
        Rate64 = 5,
        Rate128 = 6,
        Rate256 = 7
    }

    public enum CyEAverageMode
    {
        Accumulate = 0,
        FixedResolution = 1
    }

    public enum CyEAlternateResolution
    {
        Res8 = 0,
        Res10 = 1
    }

    public enum CyECompareMode
    {
        Mode0 = 0,
        Mode1 = 1,
        Mode2 = 2,
        Mode3 = 3,
        Mode4 = 4
    }
    #endregion

    public class CyParameters
    {
        private static readonly string[] SECONDS_PREFIXES = new string[]
        {
            "",  // seconds
            "m", // milliseconds
            "u", // microseconds
            "n"  // nanoseconds
        };

        private const double DEFAULT_VDDA = 5.0;

        public readonly Color DISABLED_COLUMN_COLOR = SystemColors.ControlLight;
        public const double DEFAULT_INTERNAL_VREF = 1.024;
        public const int CLOCKS_PER_SAMPLE = 18;
        public const decimal FREQ_KHZ_INCREMENT = CLOCKS_PER_SAMPLE / 1000M;
        public const string PSOC4A_ARCH_FAMILY = "PSoC4A";
        public const string PART_NUMBER_CY8C41 = "CY8C41";

        public const double EPS = 1E-6;

        public ICyInstQuery_v1 m_inst;
        public ICyTerminalQuery_v1 m_termQuery;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        // References to tabs used in the customizer
        public CyGeneralTab m_generalTab;
        public CyChannelsTab m_channelsTab;

        // Tables used by the customizer
        public CyChannelsConfigTable m_channelsConfTable = null;

        // Xml serialization parameters
        public XmlSerializer m_serializerCyChannelsConfigTable;

        public XmlSerializerNamespaces m_customSerNamespace;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 termQuery)
        {
            m_inst = inst;
            m_termQuery = termQuery;
            m_channelsConfTable = new CyChannelsConfigTable();

            // Create XML Serializer
            m_serializerCyChannelsConfigTable = new XmlSerializer(typeof(CyChannelsConfigTable));

            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            //Get tables
            GetChannelsConfigTable();
        }
        #endregion

        #region Class Properties
        #region General tab properties
        public UInt32 ClockFrequency
        {
            get { return GetValue<UInt32>(CyParamNames.CLOCK_FREQUENCY); }
            set { SetValue(CyParamNames.CLOCK_FREQUENCY, value); }
        }

        public double ClockFrequencyKHz
        {
            get { return ClockFrequency / 1000.0; }
            set { ClockFrequency = (UInt32)Math.Round(value * 1000.0, 3); }
        }

        public CyESarAdcClockSrc ClockSourceType
        {
            get { return GetValue<CyESarAdcClockSrc>(CyParamNames.CLOCK_SOURCE_TYPE); }
            set { SetValue(CyParamNames.CLOCK_SOURCE_TYPE, value); }
        }

        public CyESampleMode SampleModeType
        {
            get { return GetValue<CyESampleMode>(CyParamNames.SAMPLE_MODE_TYPE); }
            set { SetValue(CyParamNames.SAMPLE_MODE_TYPE, value); }
        }

        public CyEAdjust AdjustType
        {
            get { return GetValue<CyEAdjust>(CyParamNames.ADJUST_TYPE); }
            set { SetValue(CyParamNames.ADJUST_TYPE, value); }
        }

        public CyEVRefSelect VrefSelect
        {
            get { return GetValue<CyEVRefSelect>(CyParamNames.VREF_SELECT_TYPE); }
            set { SetValue(CyParamNames.VREF_SELECT_TYPE, value); }
        }

        public double VrefValue
        {
            get { return GetValue<UInt32>(CyParamNames.VREF_VALUE) / 1000.0 ; }
            set { SetValue(CyParamNames.VREF_VALUE, (UInt32)(value * 1000.0)); }
        }

        public CyEResultFormat DifferentialResultFormat
        {
            get { return GetValue<CyEResultFormat>(CyParamNames.DIFFERENTIAL_RESULT_FORMAT); }
            set { SetValue(CyParamNames.DIFFERENTIAL_RESULT_FORMAT, value); }
        }

        public CyEResultFormat SingleEndedResultFormat
        {
            get { return GetValue<CyEResultFormat>(CyParamNames.SINGLE_ENDED_RESULT_FORMAT); }
            set { SetValue(CyParamNames.SINGLE_ENDED_RESULT_FORMAT, value); }
        }

        public CyEFormatJustify DataFormatJustification
        {
            get { return GetValue<CyEFormatJustify>(CyParamNames.DATA_FORMAT_JUSTIFICATION); }
            set { SetValue(CyParamNames.DATA_FORMAT_JUSTIFICATION, value); }
        }

        public CyESamplesAveraged SamplesAveraged
        {
            get { return GetValue<CyESamplesAveraged>(CyParamNames.SAMPLES_AVERAGED); }
            set { SetValue(CyParamNames.SAMPLES_AVERAGED, value); }
        }

        public CyEAverageMode AveragingMode
        {
            get { return GetValue<CyEAverageMode>(CyParamNames.AVERAGING_MODE); }
            set { SetValue(CyParamNames.AVERAGING_MODE, value); }
        }

        public CyEAlternateResolution AlternateResolution
        {
            get { return GetValue<CyEAlternateResolution>(CyParamNames.ALTERNATE_RESOLUTION); }
            set { SetValue(CyParamNames.ALTERNATE_RESOLUTION, value); }
        }

        public CyEInputBufferGain InputBufferGain
        {
            get { return GetValue<CyEInputBufferGain>(CyParamNames.INPUT_BUFFER_GAIN); }
            set { SetValue(CyParamNames.INPUT_BUFFER_GAIN, value); }
        }

        public CyESingleEndedNegativeInput SingleEndedNegativeInput
        {
            get { return GetValue<CyESingleEndedNegativeInput>(CyParamNames.SINGLE_ENDED_NEGATIVE_INPUT); }
            set { SetValue(CyParamNames.SINGLE_ENDED_NEGATIVE_INPUT, value); }
        }

        public UInt16 LowLimit
        {
            get { return GetValue<UInt16>(CyParamNames.LOW_LIMIT); }
            set { SetValue(CyParamNames.LOW_LIMIT, value); }
        }

        public UInt16 HighLimit
        {
            get { return GetValue<UInt16>(CyParamNames.HIGH_LIMIT); }
            set { SetValue(CyParamNames.HIGH_LIMIT, value); }
        }

        public CyECompareMode CompareMode
        {
            get { return GetValue<CyECompareMode>(CyParamNames.COMPARE_MODE); }
            set { SetValue(CyParamNames.COMPARE_MODE, value); }
        }
        #endregion

        #region Channels tab properties
        public UInt16 AClock
        {
            get { return GetValue<UInt16>(CyParamNames.A_CLOCK); }
            set { SetValue(CyParamNames.A_CLOCK, value); }
        }

        public UInt16 BClock
        {
            get { return GetValue<UInt16>(CyParamNames.B_CLOCK); }
            set { SetValue(CyParamNames.B_CLOCK, value); }
        }

        public UInt16 CClock
        {
            get { return GetValue<UInt16>(CyParamNames.C_CLOCK); }
            set { SetValue(CyParamNames.C_CLOCK, value); }
        }

        public UInt16 DClock
        {
            get { return GetValue<UInt16>(CyParamNames.D_CLOCK); }
            set { SetValue(CyParamNames.D_CLOCK, value); }
        }

        public byte SequencedChannels
        {
            get { return GetValue<byte>(CyParamNames.SEQUENCED_CHANNELS); }
            set { SetValue(CyParamNames.SEQUENCED_CHANNELS, value); }
        }

        public CyChannelsConfigTable ChannelsConfigTable
        {
            get { return m_channelsConfTable; }
            set { m_channelsConfTable = value; }
        }
        #endregion

        #region Auxiliary properties
        public bool IsPSoC4A
        {
            get { return m_inst.DeviceQuery.IsPSoC4 && m_inst.DeviceQuery.ArchFamilyMember == PSOC4A_ARCH_FAMILY; }
        }

        public bool IsCY8C41
        {
            get
            {
                return m_inst.DeviceQuery.PartNumberAvailable &&
                       m_inst.DeviceQuery.PartNumber.StartsWith(PART_NUMBER_CY8C41);
            }
        }

        public byte NumMaxChannels
        {
            get { return IsPSoC4A ? CyParamRanges.NUM_MAX_CHANNELS_PSOC4A : CyParamRanges.NUM_MAX_CHANNELS; }
        }

        public byte NumberMuxLinesUsed
        {
            get
            {
                byte numChannels = 0;

                for (byte i = 1; i <= SequencedChannels; i++)
                {
                    numChannels += (byte)(ChannelsConfigTable[i].m_mode == CyEMode.Diff ? (2 + numChannels % 2) : 1);
                }

                return numChannels;
            }
        }

        public bool InjectionChannelEnabled
        {
            get { return GetValue<bool>(CyParamNames.INJ_CHANNEL_ENABLED); }
            set { SetValue(CyParamNames.INJ_CHANNEL_ENABLED, value); }
        }

        public double VDDA
        {
            get
            {
                double vdda = DEFAULT_VDDA;

                try
                {
                    vdda = m_inst.VoltageQuery.VDDA;
                }
                catch
                { }

                return vdda;
            }
        }

        public UInt32 ClocksPerSample
        {
            get
            {
                UInt32 clocks = 0;

                for (int i = 1; i <= SequencedChannels; i++)
                {
                    CyChannelsConfigTableRow channel = ChannelsConfigTable[i];
                    if (channel.m_enabled == true)
                    {
                        UInt32 resolution = GetResolution(channel.m_resolution);
                        UInt32 avg = (channel.m_averaged) ? AveragedSamples : 1;
                        clocks += (UInt32)((1 + GetAcquisionClocks(channel.m_acqTime) + 1 + resolution) * avg);
                    }
                }

                return clocks;
            }
        }

        public UInt32 AveragedSamples
        {
            get
            {
                UInt32 result = 1;

                switch (SamplesAveraged)
                {
                    case CyESamplesAveraged.Rate2:
                        result = 2;
                        break;
                    case CyESamplesAveraged.Rate4:
                        result = 4;
                        break;
                    case CyESamplesAveraged.Rate8:
                        result = 8;
                        break;
                    case CyESamplesAveraged.Rate16:
                        result = 16;
                        break;
                    case CyESamplesAveraged.Rate32:
                        result = 32;
                        break;
                    case CyESamplesAveraged.Rate64:
                        result = 64;
                        break;
                    case CyESamplesAveraged.Rate128:
                        result = 128;
                        break;
                    case CyESamplesAveraged.Rate256:
                        result = 256;
                        break;
                }

                return result;
            }
        }

        public double ReferenceVoltageValue
        {
            get
            {
                double voltageValue;
                switch (VrefSelect)
                {
                    case CyEVRefSelect.Internal1024:
                    case CyEVRefSelect.Internal1024Bypassed:
                        voltageValue = CyParameters.DEFAULT_INTERNAL_VREF;
                        break;
                    case CyEVRefSelect.VDDA_2:
                    case CyEVRefSelect.VDDA_2Bypassed:
                        voltageValue = (VDDA / 2);
                        break;
                    case CyEVRefSelect.VDDA:
                        voltageValue = VDDA;
                        break;
                    case CyEVRefSelect.ExternalVref:
                        voltageValue = VrefValue;
                        break;
                    default:
                        voltageValue = VrefValue;
                        break;
                }

                return voltageValue;
            }
        }

        public double NominalClockFrequencyHz
        {
            get
            {
                return CyClock.GetClockFrequencyHz(m_termQuery, ClockSourceType == CyESarAdcClockSrc.Internal);
            }
        }

        public bool HasSingleEndedInput
        {
            get { return GetValue<bool>(CyParamNames.ADC_HAS_SE_INPUT); }
            set { SetValue(CyParamNames.ADC_HAS_SE_INPUT, value); }
        }

        public UInt16 ChannelsEnableConfig
        {
            set { SetValue(CyParamNames.CHANNELS_ENABLE_CONFIG, value); }
        }

        public UInt32 ChannelsModeConfig
        {
            set { SetValue(CyParamNames.CHANNELS_MODE_CONFIG, value); }
        }

        public string SarMuxChannelsConfig
        {
            set { SetValue(CyParamNames.SARMUX_CHANNELS_CONFIG, value); }
        }

        public byte MaxResolutionUsed
        {
            get { return GetValue<byte>(CyParamNames.ADC_MAX_RESOLUTION); }
            set { SetValue(CyParamNames.ADC_MAX_RESOLUTION, value); }
        }
        #endregion
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion

        #region Set auxiliary data from table
        public void SetAuxiliaryData()
        {
            InjectionChannelEnabled = ChannelsConfigTable[CyChannelsConfigTable.INJ_CHANNEL_INDEX].m_enabled;

            UInt16 channelsEnConf = 0;
            UInt32 channelsModeConf = 0;
            string strModeConf = string.Empty;
            UInt16 channelsEnMask = 1;
            UInt32 channelsModeMask = 2;

            for (int i = 1; i <= SequencedChannels; i++)
            {
                if (ChannelsConfigTable[i].m_enabled)
                {
                    channelsEnConf |= channelsEnMask;
                }
                if (ChannelsConfigTable[i].m_mode == CyEMode.Diff)
                {
                    channelsModeConf |= channelsModeMask;
                    strModeConf = strModeConf + "1";
                }
                else
                {
                    strModeConf = strModeConf + "0";
                }

                channelsEnMask <<= 1;
                channelsModeMask <<= 1;
            }

            // Proceed injection channel
            if (InjectionChannelEnabled)
            {
                if (ChannelsConfigTable[CyChannelsConfigTable.INJ_CHANNEL_INDEX].m_mode == CyEMode.Diff)
                {
                    channelsModeConf |= 1;
                    strModeConf = strModeConf + "1";
                }
                else
                {
                    strModeConf = strModeConf + "0";
                }
            }

            ChannelsEnableConfig = channelsEnConf;
            ChannelsModeConfig = channelsModeConf;
            SarMuxChannelsConfig = strModeConf;
            UpdateVnegVisibleParam();
        }

        public void UpdateVnegVisibleParam()
        {
            bool vnegVisible = false;

            if (SingleEndedNegativeInput == CyESingleEndedNegativeInput.Other)
            {
                for (int i = 0; i <= SequencedChannels; i++)
                {
                    // Check if current channel is single ended. If current is injection channel and it is disabled,
                    // skip checking
                    if ((i != CyChannelsConfigTable.INJ_CHANNEL_INDEX || ChannelsConfigTable[i].m_enabled) &&
                        (ChannelsConfigTable[i].m_mode == CyEMode.Single))
                    {
                        vnegVisible = true;
                        break;
                    }
                }
            }
            HasSingleEndedInput = vnegVisible;
        }

        public void UpdateMaxResolutionUsed()
        {
            byte maxRes = 0;

            for (int i = 0; i <= SequencedChannels; i++)
            {
                if (i == CyChannelsConfigTable.INJ_CHANNEL_INDEX && InjectionChannelEnabled == false)
                {
                    continue;
                }
                if (GetResolution(ChannelsConfigTable[i].m_resolution) > maxRes)
                {
                    maxRes = GetResolution(ChannelsConfigTable[i].m_resolution);
                }
            }

            MaxResolutionUsed = maxRes;
        }
        #endregion

        #region Additional service functions
        public int TableRowIndex(int dataGridRow)
        {
            return (dataGridRow == SequencedChannels) ? 0 : dataGridRow + 1;
        }

        public UInt16 GetAcquisionClocks(CyEAcquisionTime acqTime)
        {
            UInt16 result = 0;

            switch (acqTime)
            {
                case CyEAcquisionTime.AClocks:
                    result = AClock;
                    break;
                case CyEAcquisionTime.BClocks:
                    result = BClock;
                    break;
                case CyEAcquisionTime.CClocks:
                    result = CClock;
                    break;
                case CyEAcquisionTime.DClocks:
                    result = DClock;
                    break;
                default:
                    result = AClock;
                    break;
            }

            return result;
        }

        public double GetAcquisionTime(CyEAcquisionTime acqTime)
        {
            return GetAcquisionClocks(acqTime) / (double)ClockFrequency;
        }

        public byte GetResolution(CyEResolution resolution)
        {
            byte res = 0;
            switch (resolution)
            {
                case CyEResolution.Twelve:
                    res = 12;
                    break;
                case CyEResolution.Alternative:
                    res = (byte)(AlternateResolution == CyEAlternateResolution.Res10 ? 10 : 8);
                    break;
            }
            return res;
        }

        public double GetConversionTime(int channelNumber)
        {
            if (ClockFrequency > 0)
            {
                CyChannelsConfigTableRow channel = ChannelsConfigTable[channelNumber];
                double resolution = GetResolution(channel.m_resolution);
                double convTime = 1 + GetAcquisionClocks(channel.m_acqTime) + 1 + resolution;

                if (ChannelsConfigTable[channelNumber].m_averaged == true)
                {
                    convTime *= AveragedSamples;
                }

                return convTime / ClockFrequency;
            }

            return 0.0;
        }

        public static string GetNormalizedString(double value)
        {
            double res = value;

            for (int i = 0; i < SECONDS_PREFIXES.Length; i++)
            {
                if (Math.Truncate(res) > 0)
                {
                    return string.Format("{0:0.##} {1}s", res, SECONDS_PREFIXES[i]);
                }
                res *= 1000;
            }

            return string.Empty;
        }

        public UInt32 GetSampleRate(double clockFrequencyHz)
        {
            return (UInt32)(clockFrequencyHz / ClocksPerSample);
        }

        public string GetRefVoltageValueError()
        {
            string errorMsg = string.Empty;
            if ((ReferenceVoltageValue < CyParamRanges.VREF_MIN_VALUE) || (ReferenceVoltageValue > VDDA))
            {
                errorMsg = string.Format(Resources.VrefValueErrorDescription, CyParamRanges.VREF_MIN_VALUE, VDDA);
            }

            return errorMsg;
        }

        public string GetClockFrequencyError(double frequencyInHz)
        {
            string errMsg = string.Empty;

            if (CyClock.IsFrequencyKnown(frequencyInHz) == false)
                return errMsg;

            double maxFrequencyHz = GetMaxFrequencyHz();
 
            if (frequencyInHz + CyParameters.EPS <= CyParamRanges.MIN_CLOCK_FREQ_HZ ||
                frequencyInHz - CyParameters.EPS >= maxFrequencyHz)
            {
                errMsg = string.Format(Resources.ClockFrequencyErrorMsg,
                    CyParamRanges.MIN_CLOCK_FREQ_MHZ, (maxFrequencyHz / CyParamRanges.UNIT_MEGA));

                if (IsReferenceNotBypassed() && (frequencyInHz - CyParameters.EPS >= maxFrequencyHz))
                {
                    errMsg = string.Format(Resources.InvalidReferenceErrorMsg,
                    GetValueDescription(CyParamNames.VREF_SELECT_TYPE, VrefSelect),
                    CyParamRanges.MAX_CLOCK_FREQ_NOT_BYPASSED_KHZ);
                }
            }
            return errMsg;
        }

        /// <summary>
        /// Returns maximum frequency depending on device part number
        /// </summary>
        /// <returns></returns>
        public double GetMaxFrequencyHz()
        {
            double maxFrequencyHz = CyParamRanges.MAX_CLOCK_FREQ_HZ;
            if (IsCY8C41)
            {
                maxFrequencyHz = CyParamRanges.MAX_CLOCK_FREQ_CY8C41_HZ;
            }
            if (IsReferenceNotBypassed())
            {
                maxFrequencyHz = CyParamRanges.MAX_CLOCK_FREQ_NOT_BYPASSED_KHZ * 1000;
            }
            return maxFrequencyHz;
        }

        public bool IsReferenceNotBypassed()
        {
            return ((VrefSelect == CyEVRefSelect.Internal1024) ||
                    (VrefSelect == CyEVRefSelect.InternalVref) ||
                    (VrefSelect == CyEVRefSelect.VDDA_2));
        }

        public bool CheckChannelsEnabled()
        {
            foreach (CyChannelsConfigTableRow channel in m_channelsConfTable.m_channelsConfigTable)
            {
                if (channel.m_enabled)
                {
                    return true;
                }
            }
            return m_channelsConfTable.m_channelsConfigTable.Count == 0;
        }
        #endregion

        #region Getting/Setting parameters with XML Data
        public void GetChannelsConfigTable()
        {
            string xmlData = GetValue<string>(CyParamNames.CHANNELS_CONFIG_TABLE);
            CyChannelsConfigTable package = (CyChannelsConfigTable)Deserialize(xmlData, typeof(CyChannelsConfigTable),
                SequencedChannels + 1);
            // For compatibility with version 1_0, reassign acqTime values "Four clocks" to "A clocks"
            for (int i = 0; i < package.m_channelsConfigTable.Count; i++)
            {
                if (package.m_channelsConfigTable[i].m_acqTime == CyEAcquisionTime.FourClocks)
                {
                    package.m_channelsConfigTable[i].m_acqTime = CyEAcquisionTime.AClocks;
                }
            }
            ChannelsConfigTable = new CyChannelsConfigTable(package.m_channelsConfigTable);
        }

        public void SetChannelsConfigTable()
        {
            if (m_bGlobalEditMode)
            {
                CyChannelsConfigTable package = new CyChannelsConfigTable();
                package.m_channelsConfigTable = new List<CyChannelsConfigTableRow>(ChannelsConfigTable.ToArray());
                package.m_channelsConfigTable.RemoveRange(SequencedChannels + 1, package.m_channelsConfigTable.Count -
                    SequencedChannels - 1);

                SetValue(CyParamNames.CHANNELS_CONFIG_TABLE, Serialize(package));

                SetAuxiliaryData();
            }
        }
        #endregion

        #region XML Serialization
        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            m_serializerCyChannelsConfigTable.Serialize(tw, obj, m_customSerNamespace);

            string res = sb.ToString();
            res = res.Replace("\r\n", " ");
            return res;
        }

        public object Deserialize(string serializedXml, Type t, int numOfDefaultRows)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();

                //Read version information
                XmlReader tr = XmlReader.Create(new StringReader(serializedXml));
                //Remove header <?xml version="1.0" encoding="utf-16" ?> 
                tr.Read();
                tr.Read();
                //Go to first Node with attributes
                while (tr.HasAttributes == false)
                {
                    tr.Read();
                }
                string ver_info = tr.GetAttribute(0);

                res = m_serializerCyChannelsConfigTable.Deserialize(tr);
            }
            catch
            {
                res = Activator.CreateInstance(t);
                ((ICyTable)res).InitializeTable(numOfDefaultRows);

                if (String.IsNullOrEmpty(serializedXml) == false)
                {
                    MessageBox.Show(Resources.SettingsIncorrectValues,
                        MessageBoxIcon.Warning.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            return res;
        }
        #endregion

        #region DataGridView
        public static void InitializeDataGrid(DataGridView dgv)
        {
            // Initialize data grid view
            dgv.EditMode = DataGridViewEditMode.EditOnEnter;

            // Prevent data grid from sorting
            foreach (DataGridViewColumn item in dgv.Columns)
                item.SortMode = DataGridViewColumnSortMode.NotSortable;
            dgv.AllowUserToOrderColumns = false;
            dgv.AllowUserToDeleteRows = false;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToResizeColumns = false;
            dgv.AllowUserToResizeRows = false;
            dgv.MultiSelect = false;

            dgv.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.DisableResizing;
        }

        public static void SetReadOnlyState(DataGridViewColumn dgvColumn)
        {
            dgvColumn.CellTemplate.Style.BackColor = SystemColors.ControlLight;
            dgvColumn.ReadOnly = true;
        }
        #endregion

        #region Nullable operations
        public static bool ParseNullableBool(object val)
        {
            bool res = false;
            try
            {
                res = Convert.ToBoolean(val);
            }
            catch { }
            return res;
        }
        #endregion

        #region Get descriptions list
        public string[] GetEnumDescriptions(string paramName)
        {
            return new List<string>(m_inst.GetPossibleEnumValues(paramName)).ToArray();
        }

        public string GetValueDescription(string paramName, object value)
        {
            return m_inst.ResolveEnumIdToDisplay(paramName, value.ToString());
        }

        public T GetEnumValue<T>(string paramName, string displayText)
        {
            T enumValue;
            string enumItemName = m_inst.ResolveEnumDisplayToId(paramName, displayText);

            try
            {
                enumValue = (T)Enum.Parse(typeof(T), enumItemName);
            }
            catch
            {
                enumValue = default(T);
            }

            return enumValue;
        }
        #endregion
    }
}
