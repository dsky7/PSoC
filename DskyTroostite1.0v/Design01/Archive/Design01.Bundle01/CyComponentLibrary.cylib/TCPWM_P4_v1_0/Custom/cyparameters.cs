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
using CyDesigner.Extensions.Scc;
using System.Reflection;
using System.Diagnostics;


namespace TCPWM_P4_v1_0
{
    #region Enums
    public enum CyTriggerMode
    {
        [Description("Rising edge")]
        TRIG_RISING = 0,
        [Description("Falling edge")]
        TRIG_FALLING = 1,
        [Description("Either edge")]
        TRIG_BOTH = 2,
        [Description("Level")]
        TRIG_LEVEL = 3
    }
    public enum CySwapEnable
    {
        SWAP_DISABLE = 0,
        SWAP_ENABLE = 1
    }
    public enum CyTriggerMask
    {
        CMD_CAPTURE = 0,
        CMD_RELOAD = 1,
        CMD_STOP = 2,
        CMD_START = 3
    }
    public enum CyCounterMode
    {
        [Description("Up")]
        COUNT_UP = 0,
        [Description("Down")]
        COUNT_DOWN = 1,
        [Description("Up/Down 0")]
        COUNT_UPDOWN0 = 2,
        [Description("Up/Down 1")]
        COUNT_UPDOWN1 = 3
    }
    public enum CyInterruptMask
    {
        INTR_MASK_NONE = 0,
        INTR_MASK_TC = 1,
        INTR_MASK_CC_MATCH = 2,
        INTR_MASK_TC_CC = 3

    }
    public enum CyCompCapMode
    {
        [Description("Capture")]
        Capture = 2,
        [Description("Compare")]
        Compare = 0
    }
    public enum CyRunMode
    {
        [Description("Continuous")]
        Continuous = 0,
        [Description("One shot")]
        OneShot = 1
    }
    public enum CyTCPWMConfig
    {
        [Description("Unconfigured")]
        UNCONFIG = 8,
        [Description("Timer / Counter")]
        TIMER = 1,
        [Description("QuadDec")]
        QUAD = 3,
        [Description("PWM")]
        PWM_SEL = 7
    }
    public enum CyPWMMode
    {
        [Description("PWM")]
        PWM = 4,
        [Description("PWM with dead time insertion")]
        PWM_DT = 5,
        [Description("Pseudo random PWM")]
        PWM_PR = 6
    }
    public enum CyPWMEvent
    {
        [Description("Asynchronous")]
        ASYNCH = 0,
        [Description("Synchronous")]
        SYNCH = 1
    }
    public enum CyPWMInvert
    {
        [Description("Direct output")]
        DIRECT = 0,
        [Description("Inverse output")]
        INVERSE = 1
    }
    public enum CyPWMAlign
    {
        [Description("Left align")]
        LEFT = 0,
        [Description("Right align")]
        RIGHT = 1,
        [Description("Center align")]
        CENTER = 2,
        [Description("Asymmetric align")]
        ASYMMETRIC = 3
    }
    public enum CyPWMStop
    {
        [Description("Don't stop on kill")]
        DONT_STOP = 0,
        [Description("Stop on kill")]
        STOP = 1
    }
    public enum CyQuadMode
    {
        [Description("1x")]
        X1 = 0,
        [Description("2x")]
        X2 = 1,
        [Description("4x")]
        X4 = 2
    }
    #endregion Enums

    public class CyParameters
    {
        public ICyInstQuery_v1 m_edit;
        public ICyTabbedParamEditor m_editor;
        public bool m_globalEditMode = false;

        public CyTCPWMTab m_tcpwmTab;
        public CyTimerCounterTab m_tcTab;
        public CyPWMTab m_pwmTab;
        public CyQuadDecTab m_quaddecTab;

        #region Param names
        //General
        const string P_TCPWMCONFIG = "TCPWMConfig";
        const string P_CAPTUREMODE = "TCCaptureMode";
        const string P_CAPTUREPRESENT = "CapturePresent";
        const string P_COUNTMODE = "CountMode";
        const string P_COUNTPRESENT = "CountPresent";
        const string P_RELOADMODE = "ReloadMode";
        const string P_RELOADPRESENT = "ReloadPresent";
        const string P_STARTMODE = "StartMode";
        const string P_STARTPRESENT = "StartPresent";
        const string P_STOPMODE = "StopMode";
        const string P_STOPPRESENT = "StopPresent";
        const string P_COMPARE1 = "Compare";
        const string P_COMPARE2 = "CompareBuf";
        const string P_COMPARE_SWAP = "CompareSwap";
        const string P_PERIOD1 = "Period";
        const string P_PERIOD2 = "PWMPeriodBuf";
        const string P_PERIOD_SWAP = "PWMPeriodSwap";
        const string P_INTERRUPT_MASK = "InterruptMask";
        const string P_PRESCALER = "Prescaler";
        const string P_RUNMODE = "RunMode";

        // TimerCounter
        const string P_COMPCAPMODE = "TCCompCapMode";
        const string P_COUNTINGMODES = "TCCountingModes";

        // PWM
        const string P_PWMMODE = "PWMMode";
        const string P_PWMDEADTIMECYCLE = "PWMDeadTimeCycle";
        const string P_PWMKILLEVENT = "PWMKillEvent";
        const string P_PWMSTOPEVENT = "PWMStopEvent";
        const string P_PWMOUTINVERT = "PWMLineSignal";
        const string P_PWMOUTCCINVERT = "PWMLinenSignal";
        const string P_PWMSETALIGN = "PWMSetAlign";
        const string P_SWITCHMODE = "PWMSwitchMode";
        const string P_SWITCHPRESENT = "PWMSwitchPresent";

        // QuadDec
        const string P_QUADENCODINGMODES = "QuadEncodingModes";
        const string P_INDEXMODE = "QuadIndexMode";
        const string P_INDEXPRESENT = "QuadIndexPresent";
        const string P_PHIAMODE = "QuadPhiAMode";
        const string P_PHIBMODE = "QuadPhiBMode";

        // Prefixes
        const string PREFIX_TCPWM = "TCPWM";
        const string PREFIX_TC = "TC";
        const string PREFIX_PWM = "PWM";
        const string PREFIX_QUADDEC = "Quad"; 
        #endregion Param names

        public const string HEX_PREFIX = "0x";
        public static object[] PRESCALER_ITEMS_LIST = new object[] {
            "1x", "2x", "4x", "8x", "16x", "32x", "64x", "128x" };

        public static UInt16[] COMPARE_RANGE = new UInt16[2] { 0, 65535 };
        public static UInt16[] DEADTIME_RANGE = new UInt16[2] { 0, 255 };

        #region Properties

        #region General
        public CyTCPWMConfig TCPWMConfig
        {
            get { return GetValue<CyTCPWMConfig>(P_TCPWMCONFIG); }
            set { SetValue(P_TCPWMCONFIG, value); }
        }

        #region Table
        public CyTriggerMode CaptureMode
        {
            get { return GetValue<CyTriggerMode>(P_CAPTUREMODE); }
            set { SetValue(P_CAPTUREMODE, value); }
        }

        public bool CapturePresent
        {
            get { return GetValue<bool>(GetPrefix() + P_CAPTUREPRESENT); }
            set { SetValue(GetPrefix() + P_CAPTUREPRESENT, value); }
        }

        public CyTriggerMode CountMode
        {
            get { return GetValue<CyTriggerMode>(GetPrefix() + P_COUNTMODE); }
            set { SetValue(GetPrefix() + P_COUNTMODE, value);}
        }

        public bool CountPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_COUNTPRESENT); }
            set { SetValue(GetPrefix() + P_COUNTPRESENT, value); }
        }

        public CyTriggerMode ReloadMode
        {
            get { return GetValue<CyTriggerMode>(GetPrefix() + P_RELOADMODE); }
            set { SetValue(GetPrefix() + P_RELOADMODE, value); }
        }

        public bool ReloadPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_RELOADPRESENT); }
            set { SetValue(GetPrefix() + P_RELOADPRESENT, value); }
        }

        public CyTriggerMode StartMode
        {
            get { return GetValue<CyTriggerMode>(GetPrefix() + P_STARTMODE); }
            set { SetValue(GetPrefix() + P_STARTMODE, value); }
        }

        public bool StartPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_STARTPRESENT); }
            set { SetValue(GetPrefix() + P_STARTPRESENT, value); }
        }

        public CyTriggerMode StopMode
        {
            get { return GetValue<CyTriggerMode>(GetPrefix() + P_STOPMODE); }
            set { SetValue(GetPrefix() + P_STOPMODE, value); }
        }

        public bool StopPresent
        {
            get { return GetValue<bool>(GetPrefix() + P_STOPPRESENT); }
            set { SetValue(GetPrefix() + P_STOPPRESENT, value); }
        }
        #endregion Table

        #region Compare / Period
        public uint Compare1
        {
            get { return GetValue<uint>(GetPrefix() + P_COMPARE1); }
            set
            {
                SetValue(GetPrefix() + P_COMPARE1, value);
            }
        }

        public uint Compare2
        {
            get { return GetValue<uint>(GetPrefix() + P_COMPARE2); }
            set { SetValue(GetPrefix() + P_COMPARE2, value); }
        }

        public CySwapEnable CompareSwap
        {
            get { return GetValue<CySwapEnable>(GetPrefix() + P_COMPARE_SWAP); }
            set { SetValue(GetPrefix() + P_COMPARE_SWAP, value); }
        }

        public uint Period1
        {
            get { return GetValue<uint>(GetPrefix() + P_PERIOD1); }
            set { SetValue(GetPrefix() + P_PERIOD1, value); }
        }

        public uint Period2
        {
            get { return GetValue<uint>(P_PERIOD2); }
            set { SetValue(P_PERIOD2, value); }
        }

        public CySwapEnable PeriodSwap
        {
            get { return GetValue<CySwapEnable>(P_PERIOD_SWAP); }
            set { SetValue(P_PERIOD_SWAP, value); }
        }
        #endregion Compare / Period

        public CyInterruptMask InterruptMask
        {
            get { return GetValue<CyInterruptMask>(GetPrefix() + P_INTERRUPT_MASK); }
            set  { SetValue(GetPrefix() + P_INTERRUPT_MASK, value); }
        }

        public uint Prescaler
        {
            get { return GetValue<uint>(GetPrefix() + P_PRESCALER); }
            set { SetValue(GetPrefix() + P_PRESCALER, value); }
        }
        #endregion General

        #region TC
        // TimerCounter
        public CyCompCapMode CompCapMode
        {
            get { return GetValue<CyCompCapMode>(P_COMPCAPMODE); }
            set { SetValue(P_COMPCAPMODE, value); }
        }

        public CyCounterMode CountingModes
        {
            get { return GetValue<CyCounterMode>(P_COUNTINGMODES); }
            set { SetValue(P_COUNTINGMODES, value); }
        }

        public CyRunMode RunMode
        {
            get { return GetValue<CyRunMode>(GetPrefix() + P_RUNMODE); }
            set { SetValue(GetPrefix() + P_RUNMODE, value); }
        }
        #endregion TC

        #region PWM
        // PWM
        public CyPWMMode PWMMode
        {
            get { return GetValue<CyPWMMode>(P_PWMMODE); }
            set { SetValue(P_PWMMODE, value); }
        }

        public uint PWMDeadTimeCycle
        {
            get { return GetValue<uint>(P_PWMDEADTIMECYCLE); }
            set { SetValue(P_PWMDEADTIMECYCLE, value); }
        }

        public CyPWMEvent PWMKillEvent
        {
            get { return GetValue<CyPWMEvent>(P_PWMKILLEVENT); }
            set { SetValue(P_PWMKILLEVENT, value); }
        }

        public CyPWMStop PWMStopEvent
        {
            get { return GetValue<CyPWMStop>(P_PWMSTOPEVENT); }
            set { SetValue(P_PWMSTOPEVENT, value); }
        }

        public CyPWMInvert PWMOutInvert
        {
            get { return GetValue<CyPWMInvert>(P_PWMOUTINVERT); }
            set { SetValue(P_PWMOUTINVERT, value); }
        }

        public CyPWMInvert PWMOutCCInvert
        {
            get { return GetValue<CyPWMInvert>(P_PWMOUTCCINVERT); }
            set { SetValue(P_PWMOUTCCINVERT, value); }
        }

        public CyPWMAlign PWMSetAlign
        {
            get { return GetValue<CyPWMAlign>(P_PWMSETALIGN); }
            set { SetValue(P_PWMSETALIGN, value); }
        }

        public CyTriggerMode SwitchMode
        {
            get { return GetValue<CyTriggerMode>(P_SWITCHMODE); }
            set { SetValue(P_SWITCHMODE, value); }
        }

        public bool SwitchPresent
        {
            get { return GetValue<bool>(P_SWITCHPRESENT); }
            set { SetValue(P_SWITCHPRESENT, value); }
        }
        #endregion PWM

        #region QuadDec
        public CyQuadMode QuadEncodingModes
        {
            get { return GetValue<CyQuadMode>(P_QUADENCODINGMODES); }
            set { SetValue(P_QUADENCODINGMODES, value); }
        }

        public CyTriggerMode IndexMode
        {
            get { return GetValue<CyTriggerMode>(P_INDEXMODE); }
            set { SetValue(P_INDEXMODE, value); }
        }

        public bool IndexPresent
        {
            get { return GetValue<bool>(P_INDEXPRESENT); }
            set { SetValue(P_INDEXPRESENT, value); }
        }

        public CyTriggerMode PhiAMode
        {
            get { return GetValue<CyTriggerMode>(P_PHIAMODE); }
            set { SetValue(P_PHIAMODE, value); }
        }

        public CyTriggerMode PhiBMode
        {
            get { return GetValue<CyTriggerMode>(P_PHIBMODE); }
            set { SetValue(P_PHIBMODE, value); }
        }
        #endregion QuadDec

        #endregion Properties

        #region Constructor
        public CyParameters(ICyInstQuery_v1 edit)
        {
            m_edit = edit;
        }
        #endregion Constructor

        #region Common
        private T GetValue<T>(string paramName)
        {
            return GetValue<T>(m_edit.GetCommittedParam(paramName));
        }

        public static T GetValue<T>(CyCompDevParam prm)
        {
            T value = default(T);
            CyCustErr err = CyCustErr.OK;
            if (typeof(T).BaseType == typeof(Enum))
            {
                err = prm.TryGetValueAs<T>(out value);
                if ((err == null) || (err.IsOK == false) || (Enum.IsDefined(typeof(T), value) == false))
                {
                    value = (T)Enum.GetValues(typeof(T)).GetValue(0);
                    err = CyCustErr.OK;
                }
            }
            else
                err = prm.TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
                if (m_edit != null && m_edit is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 edit = m_edit as ICyInstEdit_v1;
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                        valueToSet += "u";
                    if (edit.SetParamExpr(paramName, valueToSet))
                    {
                        edit.CommitParamExprs();
                    }
                }
        }
        #endregion Common

        #region Service functions
        /// <summary>
        /// Returns a prefix of parameters names for each TCPWM mode
        /// </summary>
        /// <returns></returns>
        private string GetPrefix()
        {
            string prefix = "";
            switch (TCPWMConfig)
            {
                case CyTCPWMConfig.UNCONFIG:
                    prefix = PREFIX_TCPWM;
                    break;
                case CyTCPWMConfig.TIMER:
                    prefix = PREFIX_TC;
                    break;
                case CyTCPWMConfig.QUAD:
                    prefix = PREFIX_QUADDEC;
                    break;
                case CyTCPWMConfig.PWM_SEL:
                    prefix = PREFIX_PWM;
                    break;
                default:
                    break;
            }
            return prefix;
        }

        // combobox
        public static void FillComboFromEnum(ComboBox cb, Type enumType)
        {
            cb.Items.Clear();
            cb.Items.AddRange(GetDescriptionList(enumType));
        }
        public static void SetComboValue(ComboBox cb, object value)
        {
            string descr = GetDescription(value);
            if (cb.Items.Contains(descr))
                cb.SelectedItem = descr;
        }
        // datagridview
        public static void SetComboCellValue(DataGridViewComboBoxCell comboCell, object value)
        {
            string descr = GetDescription(value);
            if (comboCell.Items.Contains(descr))
                comboCell.Value = descr;
        }

        public void DisableRow(DataGridViewRow row, bool disable)
        {
            row.ReadOnly = disable;
            if (disable)
            {
                DataGridViewCellStyle style = new DataGridViewCellStyle();
                style.ForeColor = SystemColors.GrayText;
                style.BackColor = SystemColors.Control;
                row.DefaultCellStyle = style;
            }
            else
            {
                row.DefaultCellStyle = null;
            }
        }
        // Enumerations
        public static string[] GetDescriptionList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetDescription(item));
            }
            return res.ToArray();
        }
        static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }
        public static T GetEnum<T>(string value)
        {
            return (T)GetEnum(value, typeof(T));
        }
        /// <summary>
        /// Convert enum description string to enum value
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static object GetEnum(string value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value == dna.Description))
                {
                    object res = Enum.Parse(_enumType, fi.Name);
                    return res;
                }

            }

            return Enum.Parse(_enumType, value);
        }
        // Hexadecimal convertations
        public static int HexToInt(string hexString)
        {
            int result = -1;
            try
            {
                result = Convert.ToInt32(hexString, 16);
            }
            catch (Exception) { }
            return result;
        }

        public static string IntToHex(int intValue)
        {
            return (HEX_PREFIX + intValue.ToString("X"));
        }

        public static bool IsHex(string inputValue)
        {
            // Check if string starts with "0x"
            bool isHex = inputValue.StartsWith(CyParameters.HEX_PREFIX);
            // Try to convert hex string to int 
            isHex &= (HexToInt(inputValue) >= 0);
            return isHex;
        }

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static string GetInternalClock(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = new List<CyClockData>();

            clkdata = termQuery.GetClockData("or_1", "term1", 0);

            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return string.Format(Resources.ClockDisplay, clkdata[0].Frequency, clkdata[0].Unit);
                }
            }
            return Resources.ClockUnknown;
        }

        /// <summary>
        /// Show/hide tabs depending on the TCPWM Mode
        /// </summary>
        public void UpdateTabVisibility()
        {
            if ((m_editor == null) || (m_tcTab == null) || (m_pwmTab == null) || (m_quaddecTab == null))
                return;

            m_editor.ShowCustomPage(Resources.TabNameTCPWM);
            m_editor.ShowCustomPage(Resources.TabNameTC);
            m_editor.ShowCustomPage(Resources.TabNamePWM);
            m_editor.ShowCustomPage(Resources.TabNameQuadDec);

            switch (TCPWMConfig)
            {
                case CyTCPWMConfig.UNCONFIG:
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_tcpwmTab.UpdateFormFromParams();
                    break;
                case CyTCPWMConfig.TIMER:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_tcTab.UpdateFormFromParams();
                    break;
                case CyTCPWMConfig.QUAD:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNamePWM);
                    m_quaddecTab.UpdateFormFromParams();
                    break;
                case CyTCPWMConfig.PWM_SEL:
                    m_editor.HideCustomPage(Resources.TabNameTCPWM);
                    m_editor.HideCustomPage(Resources.TabNameTC);
                    m_editor.HideCustomPage(Resources.TabNameQuadDec);
                    m_pwmTab.UpdateFormFromParams();
                    break;
                default:
                    break;
            }
        }

        #endregion Service functions
    }
}