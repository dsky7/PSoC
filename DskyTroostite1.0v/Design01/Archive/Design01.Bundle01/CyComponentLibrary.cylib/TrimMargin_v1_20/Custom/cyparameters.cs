/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Reflection;
using System.Drawing;
using System.Diagnostics;

namespace TrimMargin_v1_20
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string NUM_CONVERTERS = "NumConverters";
        public const string PWM_RESOLUTION = "PWMResolution";
        public const string VOLTAGES_TABLE = "VoltagesTable";
        public const string HARDWARE_TABLE = "HardwareTable";
        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Parameters Ranges
    public class CyParamRanges
    {
        // Basic tab parameters
        public const byte NUM_CONVERTERS_MIN = 1;
        public const byte NUM_CONVERTERS_MAX = 24;
        public const byte PWM_RESOLUTION_MIN = 8;
        public const byte PWM_RESOLUTION_MAX = 10;

        // Voltages tab parameters
        public const double VOLTAGE_MIN = 0.01;
        public const double VOLTAGE_MAX = 12.00;
        public const double MARGIN_LOW_PERCENT_MIN = -100;
        public const double MARGIN_LOW_PERCENT_MAX = 0;
        public const double MARGIN_HIGH_PERCENT_MIN = 0;
        public const double MARGIN_HIGH_PERCENT_MAX = 100;

        // Harware tab parameters
        public const double VDDIO_MIN = 1.8;
        public const double VDDIO_MAX = 5.5;

        public const double CONTROL_VOLTAGE_MIN = 0.01;
        public const double CONTROL_VOLTAGE_MAX = 12.0;

        public const double RESISTOR_MIN = 0.1;
        public const double RESISTOR_MAX = 10000;

        public const double MAX_RIPPLE_MIN = 0.1;
        public const double MAX_RIPPLE_MAX = 100;

        public const double NUM_CONVERTERS_WITH_PWM_RESOLUTION_MAX = 12;
        public const double PWM_RESOLUTION_WITH_NUM_CONVERTERS_MIN = 8;
    }
    #endregion

    #region Component Enums
    public enum CyPWMPolarityType
    {
        [Description("Positive")]
        Positive = 0,
        [Description("Negative")]
        Negative = 1
    }
    #endregion

    public class CyParameters
    {
        [XmlIgnore]
        public static DataGridViewCellStyle DGDisabledStyle;
        [XmlIgnore]
        public static DataGridViewCellStyle DGEnabledStyle;
        [XmlIgnore]
        public static List<string> VoltagesHeader_v2_0 = new List<string>();
        [XmlIgnore]
        public static List<string> VoltagesHeader_v1_0 = new List<string>(
            new string[] {
            "Power converter number", "Power converter name", "Nominal voltage (V)",
            "Trim/margin range Min voltage (V)", "Trim/margin range Max voltage (V)", "Margin low (%)",
            "Margin high (%)", "Margin low (V)", "Margin high (V)"
        });
        [XmlIgnore]
        public static List<string> HardwareHeader_v2_0 = new List<string>();
        [XmlIgnore]
        public static List<string> HardwareHeader_v1_0 = new List<string>( new string[] {
        "Power converter number","Power converter name","Nominal voltage (V)","Polarity","PWM output pin Vddio (V)",
        "Vadj voltage at Vnom (V)","R1 (kOhm)","R2 (kOhm)","Calculated  R3 + R4 (kOhm)","Actual R3 (kOhm)",
        "Actual R4 (kOhm)","Max Ripple on Vadj (mV)","Calculated C1 (uF)","Trim/Margin resolution (mV)"
        });

        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to display names
        [XmlIgnore]
        public Dictionary<object, string> m_displayNameDict = new Dictionary<object, string>();

        [XmlIgnore]
        private Dictionary<string, object> m_restoredParameters = new Dictionary<string, object>();

        [XmlIgnore]
        public ICyInstQuery_v1 m_inst;
        [XmlIgnore]
        public ICyTerminalQuery_v1 m_term;
        [XmlIgnore]
        public CyVoltagesTab m_voltagesTab;
        [XmlIgnore]
        public CyHardwareTab m_hardwareTab;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        private List<CyVoltagesTableRow> m_voltagesTable;
        private List<CyHardwareTableRow> m_hardwareTable;
        private bool m_isVoltagesTableDefault = false;

        // Xml serialization parameters
        private XmlSerializer m_serializerVoltages;
        private XmlSerializer m_serializerHardware;
        private XmlSerializer m_serializerParameters;
        private XmlSerializerNamespaces m_customSerNamespace;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;

            // Create XML Serializer
            m_serializerVoltages = new XmlSerializer(typeof(CyVoltagesTable));
            m_serializerHardware = new XmlSerializer(typeof(CyHardwareTable));
            m_serializerParameters = new XmlSerializer(typeof(CyParameters));
            m_customSerNamespace = new XmlSerializerNamespaces();
            Type classType = typeof(CyParameters);
            string curNamespace = classType.Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            GetVoltagesTable();
            GetHardwareTable();
        }

        public CyParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 termQuery)
            : this(inst)
        {
            m_term = termQuery;
        }

        public CyParameters() { }

        #endregion

        #region Class properties
        [XmlIgnore]
        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        [XmlIgnore]
        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        public byte NumConverters
        {
            get { return GetValue<byte>(CyParamNames.NUM_CONVERTERS); }
            set { SetValue(CyParamNames.NUM_CONVERTERS, value); }
        }

        public byte PWMResolution
        {
            get { return GetValue<byte>(CyParamNames.PWM_RESOLUTION); }
            set { SetValue(CyParamNames.PWM_RESOLUTION, value); }
        }

        public List<CyVoltagesTableRow> VoltagesTable
        {
            get { return m_voltagesTable; }
            set { m_voltagesTable = value; }
        }
        public List<CyHardwareTableRow> HardwareTable
        {
            get { return m_hardwareTable; }
            set { m_hardwareTable = value; }
        }

        [XmlIgnore]
        public bool IsVoltagesTableDefault
        {
            get { return m_isVoltagesTableDefault; }
            set { m_isVoltagesTableDefault = value; }
        }
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

        public void GetVoltagesTable()
        {
            string xmlData = GetValue<string>(CyParamNames.VOLTAGES_TABLE);
            string version = "";

            CyVoltagesTable package = (CyVoltagesTable)Deserialize(xmlData, typeof(CyVoltagesTable), ref version,
                this.NumConverters);

            // Compatibility with versions older 1_20
            CyComponentVersion ver1_20 = new CyComponentVersion(1, 20);
            CyComponentVersion xmlVersion = new CyComponentVersion(version);
            if (xmlVersion.IsValid && xmlVersion.CompareToVersion(ver1_20) < 0)
            {
                MigrateVoltagesTable(package);
            }

            m_voltagesTable = package.m_voltagesTable;
        }

        public void GetHardwareTable()
        {
            string xmlData = GetValue<string>(CyParamNames.HARDWARE_TABLE);
            string version = "";
            
            CyHardwareTable package = (CyHardwareTable)Deserialize(xmlData, typeof(CyHardwareTable), ref version,
                this.NumConverters);

            // Compatibility with versions older 1_20
            CyComponentVersion ver1_20 = new CyComponentVersion(1, 20);
            CyComponentVersion xmlVersion = new CyComponentVersion(version);
            if (xmlVersion.IsValid && xmlVersion.CompareToVersion(ver1_20) < 0)
            {
                MigrateHardwareTable(package);
            }
            
            m_hardwareTable = package.m_hardwareTable;
        }

        public void MigrateVoltagesTable(CyVoltagesTable package)
        {
            for (int i = 0; i < package.m_voltagesTable.Count; i++)
            {
                CyVoltagesTableRow row = package.m_voltagesTable[i];
                if (row.m_startupVoltage == null)
                {
                    row.m_startupVoltage = row.m_nominalVoltage;
                }
            }
        }

        public void MigrateHardwareTable(CyHardwareTable package)
        {
            for (int i = 0; i < package.m_hardwareTable.Count; i++)
            {
                CyHardwareTableRow row = package.m_hardwareTable[i];
                if (row.m_c1 == null)
                {
                    row.m_c1 = CyHardwareTable.C1_DEFAULT;
                }
            }
        }
        #endregion

        #region Import or paste rows
        public bool Import(Control parent, string fileContent, bool pasteMode)
        {
            if (parent is CyVoltagesTab)
            {
                List<CyVoltagesTableRow> importedTable = CyImportExport.ImportVoltagesTable(NumConverters,
                    VoltagesHeader_v2_0, fileContent, pasteMode);

                int firstPasteRow = -1;
                int lastPasteRow = -1;
                if (importedTable != null)
                {
                    if (pasteMode)
                    {
                        firstPasteRow = m_voltagesTab.DataGridFirstSelectedRow;
                        lastPasteRow = GetLastPasteRow(importedTable.Count, firstPasteRow, NumConverters);

                        int j = 0;
                        for (int i = firstPasteRow; i < lastPasteRow; i++)
                        {
                            VoltagesTable[i] = importedTable[j];
                            j++;
                        }
                    }
                    else
                    {
                        VoltagesTable = new List<CyVoltagesTableRow>(importedTable);
                    }
                    m_voltagesTab.UpdateUIFromTable();
                    m_hardwareTab.UpdateUIFromTable();
                    SetVoltagesTable();
                    SetHardwareTable();
                    m_voltagesTab.ValidateAllTable();
                    m_voltagesTab.SelectDataGridViewRows(firstPasteRow, lastPasteRow - 1);
                }
                else return false;
            }

            if (parent is CyHardwareTab)
            {
                List<CyHardwareTableRow> importedTable = CyImportExport.ImportHardwareTable(NumConverters,
                    HardwareHeader_v2_0, fileContent, pasteMode);

                int firstPasteRow = -1;
                int lastPasteRow = -1;
                if (importedTable != null)
                {
                    if (pasteMode)
                    {
                        firstPasteRow = m_hardwareTab.DataGridFirstSelectedRow;
                        lastPasteRow = GetLastPasteRow(importedTable.Count, firstPasteRow, NumConverters);

                        int j = 0;
                        for (int i = firstPasteRow; i < lastPasteRow; i++)
                        {
                            HardwareTable[i] = importedTable[j];
                            j++;
                        }
                    }
                    else
                    {
                        HardwareTable = new List<CyHardwareTableRow>(importedTable);
                    }
                    m_hardwareTab.UpdateUIFromTable();
                    SetHardwareTable();
                    m_hardwareTab.ValidateAllTable();
                    m_hardwareTab.SelectDataGridViewRows(firstPasteRow, lastPasteRow - 1);
                }
                else return false;
            }

            return true;
        }

        private int GetLastPasteRow(int importRowCount, int datagridActiveRowIndex, int gridRowsCount)
        {
            int lastPasteRow;
            if (importRowCount > (gridRowsCount - datagridActiveRowIndex))
            {
                lastPasteRow = datagridActiveRowIndex + (gridRowsCount - datagridActiveRowIndex);
            }
            else
            {
                lastPasteRow = datagridActiveRowIndex + importRowCount;
            }
            return lastPasteRow;
        }
        #endregion

        #region Nullable double operations
        public static double? ParseNullableDouble(string val)
        {
            double? res = null;
            double parsed = 0;
            if (double.TryParse(val, out parsed))
            {
                res = parsed;
            }
            return res;
        }
        public static string NullableDoubleToString(double? val)
        {
            return NullableDoubleToString(val, 2);
        }
        public static string NullableDoubleToString(double? val, byte precision)
        {
            string res = "";
            string strPrecision;

            strPrecision = (precision <= 0) ? strPrecision = string.Empty : strPrecision = "f" + precision.ToString();

            if (val.HasValue)
                res = val.Value.ToString(strPrecision);
            return res;
        }
        public static string CellToString(object cellValue)
        {
            string res = "";
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
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
            // Saving data after deserialization
            if ((m_bGlobalEditMode == false) && (m_inst == null))
            {
                if (m_restoredParameters.ContainsKey(paramName))
                {
                    Debug.Assert(false);
                    return;
                }
                m_restoredParameters.Add(paramName, value);
            }
        }

        public void SetVoltagesTable()
        {
            CyVoltagesTable package = new CyVoltagesTable();
            package.m_voltagesTable = new List<CyVoltagesTableRow>(m_voltagesTable);
            if ((package.m_voltagesTable.Count - NumConverters) > 0)
            {
                package.m_voltagesTable.RemoveRange(NumConverters, package.m_voltagesTable.Count - NumConverters);
            }
            SetValue(CyParamNames.VOLTAGES_TABLE, Serialize(package));
        }

        public void SetHardwareTable()
        {
            CyHardwareTable package = new CyHardwareTable();
            package.m_hardwareTable = new List<CyHardwareTableRow>(m_hardwareTable);
            if ((package.m_hardwareTable.Count - NumConverters) > 0)
            {
                package.m_hardwareTable.RemoveRange(NumConverters, package.m_hardwareTable.Count - NumConverters);
            }
            SetValue(CyParamNames.HARDWARE_TABLE, Serialize(package));
        }

        public void RestoreParameters(Dictionary<string, object> restoreList)
        {
            foreach (string param_name in restoreList.Keys)
            {
                SetValue<object>(param_name, restoreList[param_name]);
            }
        }
        #endregion

        #region XML Serialization
        public void LoadAllParametersFromFile(string fileContent)
        {
            string version = "";            
            CyParameters imported = (CyParameters)Deserialize(fileContent, typeof(CyParameters), ref version, 0);

            if (imported == null)
            {
                MessageBox.Show(Resources.LoadCondigErrorMsg, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
            else
            {
                try
                {            
                    bool prevGlobalEditMode = m_bGlobalEditMode;
                    m_bGlobalEditMode = true;

                    RestoreParameters(imported.m_restoredParameters);

                    this.VoltagesTable = imported.VoltagesTable;
                    this.HardwareTable = imported.HardwareTable;

                    SetVoltagesTable();
                    SetHardwareTable();

                    //GetVoltagesTable();
                    //GetHardwareTable();

                    m_bGlobalEditMode = false;

                    m_voltagesTab.UpdateUI();
                    m_voltagesTab.UpdateUIFromTable();

                    m_hardwareTab.UpdateUI();
                    m_hardwareTab.UpdateUIFromTable();

                    m_bGlobalEditMode = prevGlobalEditMode;
                }
                catch
                {
                    m_bGlobalEditMode = true;
                    MessageBox.Show(Resources.LoadCondigParamsErrorMsg,
                          Resources.MsgErrorTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        XmlSerializer GetSerializer(Type type)
        {
            if (type == typeof(CyHardwareTable))
                return m_serializerHardware;
            else if (type == typeof(CyVoltagesTable))
                return m_serializerVoltages;
            else if (type == typeof(CyParameters))
                return m_serializerParameters;
            return null;
        }

        public string Serialize(object obj)
        {
            StringBuilder sb = new StringBuilder();

            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            GetSerializer(obj.GetType()).Serialize(tw, obj, m_customSerNamespace);

            string res = sb.ToString();
            res = res.Replace("\r\n", " ");
            return res;
        }

        public object Deserialize(string serializedXml, Type t, ref string version, byte numOfDefaultRows)
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
                //This version information will be used in future versions of Voltage Fault Detector component.
                version = tr.GetAttribute(0);

                res = GetSerializer(t).Deserialize(tr);
                SetTableDefault(t, false);
            }
            catch
            {
                res = Activator.CreateInstance(t);

                if (res is ICyIntTable)
                {
                    ((ICyIntTable)res).InitializeTable(numOfDefaultRows);
                    SetTableDefault(t, true);

                    if (String.IsNullOrEmpty(serializedXml) == false)
                    {
                        MessageBox.Show(Resources.SettingsIncorrectValues,
                            Resources.MsgWarningTitle, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                else
                    res = null;
            }
            return res;
        }
        #endregion

        #region DataGridView
        void SetTableDefault(Type t, bool isDefault)
        {
            if (t == typeof(CyVoltagesTable))
                m_isVoltagesTableDefault = isDefault;
        }

        public static string IsValueInRange(double? currCellValue, object cellValue, double min, double max,
            string errorMessage)
        {
            string res = string.Empty;
            string message = string.Empty;
            try
            {
                message = string.Format(errorMessage, min, max);

                if ((currCellValue.HasValue) && (currCellValue < min || currCellValue > max))
                    throw new Exception();
                else if ((currCellValue == null) && (IsCellEmpty(cellValue) == false))
                    throw new Exception();
            }
            catch (Exception)
            {
                res = message;
            }
            return res;
        }

        private static bool IsCellEmpty(object val)
        {
            return (val == null) || ((val != null) && (String.IsNullOrEmpty(val.ToString())));
        }

        const double EPS = 0.000001;
        public static string ValueNotGreaterThan(double? value, double? compareTo, string message)
        {
            string res = string.Empty;
            if (value.HasValue)
            {
                if (compareTo.HasValue && (value > compareTo + EPS))
                    res = message;
            }
            return res;
        }

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
            dgv.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.DisableResizing;
        }
        public static void UpdateDGVHeight(DataGridView dgv)
        {
            if (dgv.Rows.Count > 0)
            {
                int height = 2 + dgv.ColumnHeadersHeight + dgv.Rows[0].Height * dgv.Rows.Count;
                dgv.Height = height;
            }
        }

        public bool CheckVoltagesTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < NumConverters; i++)
            {
                if ((VoltagesTable[i].m_nominalVoltage == null) ||
                    (VoltagesTable[i].m_minVoltage == null) ||
                    (VoltagesTable[i].m_maxVoltage == null) ||
                    (VoltagesTable[i].m_startupVoltage == null) ||
                    (VoltagesTable[i].MarginLow == null) ||
                    (VoltagesTable[i].MarginHigh == null))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public bool CheckHardwareTableNullValues()
        {
            bool isOk = true;
            for (int i = 0; i < NumConverters; i++)
            {
                if ((HardwareTable[i].m_controlVoltage == null) ||
                    (HardwareTable[i].m_maxRipple == null) ||
                    (HardwareTable[i].m_r1 == null) ||
                    (HardwareTable[i].m_r2 == null) ||
                    (HardwareTable[i].m_r3 == null) ||
                    (HardwareTable[i].m_vddio == null) ||
                    (HardwareTable[i].m_r4 == null))
                {
                    isOk = false;
                    break;
                }
            }
            return isOk;
        }

        public static void SetCellReadOnlyState(DataGridView dgv, int row, int col, bool readOnly)
        {
            dgv[col, row].Style = readOnly ? DGDisabledStyle : DGEnabledStyle;
            dgv[col, row].ReadOnly = readOnly;
        }
        public static List<string> GetColNames(DataGridView dgv)
        {
            List<string> colNames = new List<string>();
            for (int i = 0; i < dgv.ColumnCount; i++)
            {
                colNames.Add(dgv.Columns[i].HeaderText);
            }
            return colNames;
        }
        #endregion

        #region Value Calculation

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static double? GetInternalClock(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = new List<CyClockData>();

            clkdata = termQuery.GetClockData("clock", 0);

            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                }
            }
            return null;
        }

        public void CalculateTableValues(int index)
        {
            CyHardwareTableRow row = m_hardwareTable[index];
            double? calcR3, calcR4;
            GetCalculatedR3R4(index, out calcR3, out calcR4);
            row.m_calcR3 = calcR3;
            row.m_calcR4 = calcR4;
            row.m_calcC1 = GetCalculatedC1(index);
            row.m_calcResolution = GetCalculatedTrimResolution(index);
            row.m_calcVRipple = GetCalculatedVRipple(index);
            row.m_calcR2 = GetCalculatedR2real(index);
            row.m_nominalPWM = (UInt16?)GetCalculatedPWMNominal(index);
        }

        public void GetCalculatedR3R4(int rowIndex, out double? calcR3, out double? calcR4)
        {
            calcR3 = null;
            calcR4 = null;
            try
            {
                CyHardwareTableRow row = m_hardwareTable[rowIndex];
                if (row.m_r1 != null && row.m_r2 != null && row.m_controlVoltage != null &&
                    m_voltagesTable[rowIndex].m_maxVoltage != null)
                {
                    double r1 = (double)row.m_r1 * 1000;
                    double vadj = (double)row.m_controlVoltage;
                    double? r2 = GetCalculatedR2real(rowIndex) * 1000;
                    double? maxVoltage = (double)m_voltagesTable[rowIndex].m_maxVoltage;
                    double? calcR3PlusR4 = ((vadj * r1 * r2) / ((maxVoltage * r2) - vadj * (r1 + r2))) / 1000.0;

                    calcR4 = calcR3PlusR4 / 11;
                    calcR3 = calcR3PlusR4 - calcR4;

                    calcR3 = GetClosestR((double)calcR3);
                    calcR4 = GetClosestR((double)calcR4);
                }
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
                calcR3 = null;
                calcR4 = null;
            }
        }

        public double? GetCalculatedC1(int rowIndex)
        {
            double? calcC1 = null;
            double? fPWMOut = GetPWMFrequency();
            try
            {
                CyHardwareTableRow row = m_hardwareTable[rowIndex];
                if (fPWMOut != null && row.m_maxRipple != null && row.m_r4 != null && row.m_vddio != null)
                {
                    double mripple = (double)row.m_maxRipple / 1000;
                    double r4 = (double)row.m_r4 * 1000;

                    calcC1 = row.m_vddio / (2 * Math.PI * r4 * fPWMOut * mripple);
                    calcC1 *= 1000000;
                }
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return calcC1;
        }

        public double? GetCalculatedTrimResolution(int rowIndex)
        {
            double? trimRes = null;
            try
            {
                CyHardwareTableRow row = m_hardwareTable[rowIndex];
                if (row.m_r1 != null && row.m_r3 != null && row.m_r4 != null && row.m_controlVoltage != null
                 && row.m_vddio != null && VoltagesTable[rowIndex].m_nominalVoltage != null)
                {
                    double vAdj = (double)row.m_controlVoltage;
                    double vPwm = (double)row.m_vddio;
                    double vNom = (double)VoltagesTable[rowIndex].m_nominalVoltage;
                    double r2Real = ((vNom - vAdj) == 0) ?
                        (double)row.m_r2 :
                        (double)(vAdj * row.m_r1 / Math.Abs(vNom - vAdj));
                    double vMax = (double)(vAdj * row.m_r1 /
                        (r2Real * (row.m_r3 + row.m_r4) / (r2Real + row.m_r3 + row.m_r4))
                        + vAdj);
                    double countsNom = (Math.Pow(2.0, (double)PWMResolution) - 1) * vAdj / vPwm;
                    trimRes = (vMax - vNom) * 1000.0 / countsNom;
                }
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return trimRes;
        }

        public double? GetCalculatedVRipple(int rowIndex)
        {
            double? calcVRipple = null;
            double? fPWMOut = GetPWMFrequency();
            try
            {
                CyHardwareTableRow row = m_hardwareTable[rowIndex];
                if (fPWMOut != null && row.m_r4 != null && row.m_c1 != null && row.m_vddio != null)
                {
                    calcVRipple = (double)row.m_vddio /
                        (2 * Math.PI * ((double)row.m_r4 * 1000) * fPWMOut * ((double)row.m_c1 / 1000000));

                    calcVRipple *= 1000;
                }
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return calcVRipple;
        }

        public double? GetCalculatedR2real(int row)
        {
            // R2real = VADJ * R1 / (VNOM - VADJ)
            double? r2real = null;
            try
            {
                if ((VoltagesTable[row].m_nominalVoltage - HardwareTable[row].m_controlVoltage) == 0)
                {
                    r2real = (double)HardwareTable[row].m_r2;
                }
                else
                {
                    r2real = (double)(HardwareTable[row].m_controlVoltage * HardwareTable[row].m_r1 /
                                     (VoltagesTable[row].m_nominalVoltage - HardwareTable[row].m_controlVoltage));
                }
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return r2real;
        }

        public double? GetCalculatedPWMNominal(int row)
        {
            double? pwmNominal = null;
            try
            {
                pwmNominal = ((Math.Pow(2, (int)PWMResolution) - 1) *
                             HardwareTable[row].m_controlVoltage / HardwareTable[row].m_vddio);
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return pwmNominal;
        }

        private double GetClosestR(double r)
        {
            double result = 0;

            double logR = Math.Log(r, 10);
            int logRint = (int)logR;
            double diff = 96 * (logR - logRint);
            int roundDiff = (int)Math.Round(diff);

            double expr1 = roundDiff;
            if (diff - roundDiff < 0)
            {
                expr1 -= 1;
            }

            if (r > (CalcExpressionClosestR(logRint, expr1) + CalcExpressionClosestR(logRint, expr1 + 1))/2.0)
            {
                expr1 += 1;
            }
            result = CalcExpressionClosestR(logRint, expr1);

            return result;
        }
        private double CalcExpressionClosestR(int logRint, double x)
        {
            return (int)(0.5 + 100 * Math.Pow(10, x / 96.0)) * Math.Pow(10, logRint - 2);
        }

        public double? GetCalculatedVMax(int converterIdx)
        {
            double? res = null;
            try
            {
                double? vNom = VoltagesTable[converterIdx].m_nominalVoltage;
                double? resolution = GetCalculatedTrimResolution(converterIdx);
                double? pwmNom = GetCalculatedPWMNominal(converterIdx);

                // Vmax = Vnom + PWMnominal * TrimResolution
                res = vNom + pwmNom * resolution / 1000;
            }
            catch { }
            return res;
        }

        public double? GetCalculatedVMin(int converterIdx)
        {
            double? res = null;
            try
            {
                double? vNom = VoltagesTable[converterIdx].m_nominalVoltage;
                double? resolution = GetCalculatedTrimResolution(converterIdx);
                double? pwmNom = GetCalculatedPWMNominal(converterIdx);

                // Vmin = Vnom - TrimResolution * (2^PWMResolution-1) - PWMNominal
                res = vNom - (resolution / 1000 * (Math.Pow(2, PWMResolution) - 1 - pwmNom));

                if (res < 0) res = 0;
            }
            catch { }
            return res;
        }

        public double? GetPWMFrequency()
        {
            double? pwmFreq = null;
            double? clockFr = GetInternalClock(m_term);
            try
            {
                pwmFreq = (double)clockFr / Math.Pow(2, (int)PWMResolution);
            }
            catch
            {
                // If any value in expression equals null, the resulting value should be also null
            }
            return pwmFreq;
        }
        #endregion
    }

    public class CyComponentVersion
    {
        public int MajorVersion;
        public int MinorVersion;
        public readonly bool IsValid;

        public CyComponentVersion(int majorVersion, int minorVersion)
        {
            MajorVersion = majorVersion;
            MinorVersion = minorVersion;
            IsValid = true;
        }

        public CyComponentVersion(string versionStr)
        {
            IsValid = false;
            if (versionStr.Length >= 3)
            {
                string[] numbers = versionStr.Split('_');
                if (numbers.Length == 2)
                {
                    int major, minor;
                    if (Int32.TryParse(numbers[0], out major) && Int32.TryParse(numbers[1], out minor))
                    {
                        MajorVersion = major;
                        MinorVersion = minor;
                        IsValid = true;
                    }
                }
            }
        }

        public int CompareToVersion(CyComponentVersion version2)
        {
            const int LOWER = -1;
            const int EQUAL = 0;
            const int GREATER = 1;
            if (MajorVersion == version2.MajorVersion && MinorVersion == version2.MinorVersion)
            {
                return EQUAL;
            }
            if (MajorVersion > version2.MajorVersion ||
                (MajorVersion == version2.MajorVersion && MinorVersion > version2.MinorVersion))
            {
                return GREATER;
            }
            return LOWER;
        }
    }
}
