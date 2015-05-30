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
using System.IO;
using System.IO.Compression;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace MDIO_Interface_v1_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // Basic tab parameters
        public const string OPERATION_MODE = "OperationMode";
        public const string DEVICE_ADDRESS = "DevAddress";
        public const string PHY_ADDRESS_MODE = "PhyAddressMode";
        public const string PHYSICAL_ADDRESS = "PhyAddress";
        public const string ENABLE_EXTERN_OE = "EnableExternOE";
        // Advanced tab parameters
        public const string REG_SPACE_PARAM = "RegSpace{0}";
        public const string NUM_REG_SPACE = "NumRegSpaces";
    }
    #endregion

    #region Parameters Ranges
    public class CyParamRanges
    {
        // Basic tab parameters
        public const byte PHYS_ADDRESS_MIN = 0;
        public const byte PHYS_ADDRESS_MAX = 31;
        // Advanced tab parameters
        public const ushort START_END_ADDRESS_MIN = 0x8000;
        public const ushort START_END_ADDRESS_MAX = 0xFFFF;
    }
    #endregion

    #region Component Enums
    public enum CyOperationModeType
    {
        [Description("Basic")]
        BASIC,
        [Description("Advanced")]
        ADVANCED
    }
    public enum CyPhysicalAddressType
    {
        [Description("Firmware")]
        FIRMWARE,
        [Description("Hardware")]
        HARDWARE
    }
    public enum CyMemoryType
    {
        [Description("SRAM")]
        SRAM,
        [Description("Flash")]
        FLASH
    }
    public enum CyDataWidthType
    {
        [Description("8 bit")]
        BIT_8,
        [Description("16 bit")]
        BIT_16
    }
    public enum CyDeviceAddressType
    {
        [Description("PMA/PMD")]
        PMA_PMD = 1,
        [Description("WIS")]
        WIS = 2,
        [Description("PCS")]
        PCS = 3,
        [Description("PHY XS")]
        PHY_XS = 4,
        [Description("DTE XS")]
        DTE_XS = 5
    }
    #endregion

    public class CyParameters
    {
        #region Variables declaration
        public ICyInstQuery_v1 m_inst;
        public ICyTabbedParamEditor m_editor;
        public CyBasicTab m_basicTab;
        public CyAdvancedTab m_advancedTab;
        public CyRegSpaceConfig m_regSpaceList;

        // Xml serialization parameters
        public XmlSerializer m_regSpaceSerializer;       // for single register space
        public XmlSerializer m_regSpaceConfigSerializer; // for all register spaces
        public XmlSerializerNamespaces m_customSerNamespace;

        public static readonly Color DISABLED_COLUMN_COLOR = SystemColors.ControlLight;
        public static readonly Color ENABLED_COLUMN_COLOR = Color.White;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;
        private bool m_isRegSpaceDefault = false;
        #endregion Variables declaration

        #region Class properties
        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        public bool IsRegSpaceDefault
        {
            get { return m_isRegSpaceDefault; }
            set { m_isRegSpaceDefault = value; }
        }

        public CyOperationModeType OperationMode
        {
            get { return GetValue<CyOperationModeType>(CyParamNames.OPERATION_MODE); }
            set { SetValue(CyParamNames.OPERATION_MODE, value); }
        }

        public CyPhysicalAddressType PhysicalAddressMode
        {
            get { return GetValue<CyPhysicalAddressType>(CyParamNames.PHY_ADDRESS_MODE); }
            set { SetValue(CyParamNames.PHY_ADDRESS_MODE, value); }
        }

        public byte? PhysicalAddress
        {
            get { return GetValue<byte>(CyParamNames.PHYSICAL_ADDRESS); }
            set { SetValue(CyParamNames.PHYSICAL_ADDRESS, value); }
        }

        public CyDeviceAddressType DeviceAddress
        {
            get { return GetValue<CyDeviceAddressType>(CyParamNames.DEVICE_ADDRESS); }
            set { SetValue(CyParamNames.DEVICE_ADDRESS, value); }
        }

        public bool EnableExternOE
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_EXTERN_OE); }
            set { SetValue(CyParamNames.ENABLE_EXTERN_OE, value); }
        }

        public byte NumRegSpace
        {
            get { return GetValue<byte>(CyParamNames.NUM_REG_SPACE); }
            set { SetValue(CyParamNames.NUM_REG_SPACE, value); }
        }
        #endregion

        #region Constructor(s)
        public CyParameters() { }
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
            // Create XML Serializer
            m_regSpaceSerializer = new XmlSerializer(typeof(CyRegSpace));
            m_regSpaceConfigSerializer = new XmlSerializer(typeof(CyRegSpaceConfig));
            m_customSerNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(CyParameters).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);
            // Get register spaces from parameters and initialize the objects
            m_regSpaceList = new CyRegSpaceConfig();
            LoadRegSpaceList();
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        // Gets register space parameter value
        private string GetRegSpaceParam(int index)
        {
            return GetValue<string>(string.Format(CyParamNames.REG_SPACE_PARAM, index + 1));
        }

        // Gets single register space
        private CyRegSpace GetRegSpace(int index)
        {
            string xmlData = GetRegSpaceParam(index);
            CyRegSpace regSpace = (CyRegSpace)Deserialize(xmlData, typeof(CyRegSpace), true);
            regSpace.InitGenericData(index);
            return regSpace;
        }

        // Load all register spaces from parameters or load default reg spaces if parameters are blank
        private void LoadRegSpaceList()
        {
            // Check if all are empty
            bool allRegSpacesEmpty = true;
            for (int index = 0; index < NumRegSpace; index++)
            {
                if (string.IsNullOrEmpty(GetRegSpaceParam(index)) == false)
                {
                    allRegSpacesEmpty = false;
                    break;
                }
            }
            if (allRegSpacesEmpty) // all register spaces are empty, so get default values
            {
                m_isRegSpaceDefault = true;
                m_regSpaceList = GetDefaultRegSpaces();
            }
            else                   // At least one register space is not empty, so get them from parameters
            {
                for (int index = 0; index < NumRegSpace; index++)
                {
                    m_regSpaceList.m_regSpaces.Add(GetRegSpace(index));
                }
            }
        }

        private CyRegSpaceConfig GetDefaultRegSpaces()
        {
            // Default values from CFP Register Allocation table of CFP MSA Management Interface Specification
            CyRegSpaceConfig regSpaceList = new CyRegSpaceConfig();
            regSpaceList.m_regSpaces.Add(new CyRegSpace(0, 0x8000, 0x81FF, CyDataWidthType.BIT_8));
            regSpaceList.m_regSpaces.Add(new CyRegSpace(1, 0x8400, 0x84FF, CyDataWidthType.BIT_8));
            regSpaceList.m_regSpaces.Add(new CyRegSpace(2, 0x8800, 0x88FF, CyDataWidthType.BIT_8));
            regSpaceList.m_regSpaces.Add(new CyRegSpace(3, 0xA000, 0xA07F, CyDataWidthType.BIT_16));
            regSpaceList.m_regSpaces.Add(new CyRegSpace(4, 0xA200, 0xA2FF, CyDataWidthType.BIT_16));
            regSpaceList.m_regSpaces.Add(new CyRegSpace(5, 0xA400, 0xA47F, CyDataWidthType.BIT_16));
            return regSpaceList;
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if ((m_inst is ICyInstEdit_v1) == false) return;
            if (m_bGlobalEditMode)
            {
                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }

        public void SetRegSpace(CyRegSpace regSpace)
        {
            if (m_bGlobalEditMode)
            {
                SetValue(string.Format(CyParamNames.REG_SPACE_PARAM, regSpace.m_paramIndex + 1),
                                       Serialize(regSpace, typeof(CyRegSpace), true));
                NumRegSpace = (byte)m_regSpaceList.m_regSpaces.Count;
            }
        }

        public void ClearRegSpaceParam(int regSpaceIndex)
        {
            if (m_bGlobalEditMode)
            {
                SetValue(string.Format(CyParamNames.REG_SPACE_PARAM, regSpaceIndex + 1), "");
                NumRegSpace = (byte)(m_regSpaceList.m_regSpaces.Count);
            }
        }
        #endregion

        #region Compression/Decompression
        private const int BUFFER_LENGHT_STORAGE_SIZE = 4;
        public static string CompressString(string text)
        {
            byte[] buffer = Encoding.UTF8.GetBytes(text);
            using (MemoryStream memoryStream = new MemoryStream())
            {
                using (System.IO.Compression.DeflateStream defStream = new System.IO.Compression.DeflateStream(
                    memoryStream, System.IO.Compression.CompressionMode.Compress, true))
                {
                    defStream.Write(buffer, 0, buffer.Length);
                }
                memoryStream.Position = 0;
                byte[] compressedData = new byte[memoryStream.Length];
                memoryStream.Read(compressedData, 0, compressedData.Length);

                byte[] destBuffer = new byte[compressedData.Length + BUFFER_LENGHT_STORAGE_SIZE];
                Buffer.BlockCopy(compressedData, 0, destBuffer, BUFFER_LENGHT_STORAGE_SIZE, compressedData.Length);
                Buffer.BlockCopy(BitConverter.GetBytes(buffer.Length), 0, destBuffer, 0, BUFFER_LENGHT_STORAGE_SIZE);

                return Convert.ToBase64String(destBuffer);
            }
        }

        public static string DecompressString(string compressedText)
        {
            using (MemoryStream memoryStream = new MemoryStream())
            {
                try
                {
                    byte[] binBuffer = Convert.FromBase64String(compressedText);
                    int dataLength = BitConverter.ToInt32(binBuffer, 0);
                    memoryStream.Write(binBuffer, BUFFER_LENGHT_STORAGE_SIZE,
                                                  binBuffer.Length - BUFFER_LENGHT_STORAGE_SIZE);

                    byte[] buffer = new byte[dataLength];

                    memoryStream.Position = 0;
                    using (System.IO.Compression.DeflateStream defStream = new System.IO.Compression.DeflateStream(
                        memoryStream, System.IO.Compression.CompressionMode.Decompress))
                    {
                        defStream.Read(buffer, 0, buffer.Length);
                    }

                    return Encoding.UTF8.GetString(buffer);
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.Assert(false, ex.Message);
                    return String.Empty;
                }
            }
        }
        #endregion

        #region XML Serialization
        public string Serialize(object obj, Type t, bool compressData)
        {
            StringBuilder sb = new StringBuilder();
            System.Xml.XmlWriter tw = System.Xml.XmlWriter.Create(sb);
            if (t == typeof(CyRegSpace))
            {
                m_regSpaceSerializer.Serialize(tw, obj, m_customSerNamespace);
            }
            else
            {
                m_regSpaceConfigSerializer.Serialize(tw, obj, m_customSerNamespace);
            }
            string res = sb.ToString();
            res = res.Replace(Environment.NewLine, " ");
            if (compressData)
            {
                res = CompressString(res);
            }
            return res;
        }

        public object Deserialize(string serializedXml, Type t, bool decompressData)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new Exception();
                if (decompressData)
                {
                    serializedXml = DecompressString(serializedXml);
                }

                // Read version information
                XmlReader tr = XmlReader.Create(new StringReader(serializedXml));
                // Remove header <?xml version="1.0" encoding="utf-16" ?> 
                tr.Read();
                tr.Read();
                // Go to first Node with attributes
                while (tr.HasAttributes == false)
                {
                    tr.Read();
                }
                // This version information will be used in future versions of component.
                string ver_info = tr.GetAttribute(0);
                if (t == typeof(CyRegSpace))
                {
                    res = m_regSpaceSerializer.Deserialize(tr);
                }
                else if (t == typeof(CyRegSpaceConfig))
                {
                    res = m_regSpaceConfigSerializer.Deserialize(tr);
                }
            }
            catch
            {
                res = Activator.CreateInstance(t);
                if (String.IsNullOrEmpty(serializedXml) == false)
                {
                    MessageBox.Show(Resources.SettingsIncorrectValues,
                        MessageBoxIcon.Warning.ToString(), MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            return res;
        }
        #endregion

        #region Convertation methods
        public static string CellToString(object cellValue)
        {
            string res = "";
            if (cellValue != null)
                res = cellValue.ToString();
            return res;
        }

        /// <summary>
        /// Converts decimal UInt16 value to hexadecimal string
        /// </summary>
        /// <param name="value">Value to convert</param>
        /// <returns>Hexadecimal string of the following format: 0x0000</returns>
        public static string ConvertDecToHex(UInt16 value)
        {
            return string.Format("0x{0}", value.ToString("X4"));
        }
        /// <summary>
        /// Converts decimal byte value to hexadecimal string
        /// </summary>
        /// <param name="value">Value to convert</param>
        /// <returns>Hexadecimal string of the following format: 0x00</returns>
        public static string ConvertDecToHex(byte value)
        {
            return string.Format("0x{0}", value.ToString("X2"));
        }

        public static string ConvertDecToHexWithoutPrefix(ushort? value)
        {
            string result = String.Empty;
            if (value.HasValue)
                result = value.Value.ToString("X4");
            return result;
        }
        public static string ConvertDecToHexWithoutPrefix(byte? value)
        {
            string result = String.Empty;
            if (value.HasValue)
                result = value.Value.ToString("X2");
            return result;
        }

        /// <summary>
        /// Converts hex value of 0xFF or FF type to UInt16
        /// </summary>
        /// <param name="value">Value of 0xFF or FF type</param>
        /// <param name="acceptPrefix">Indicates whether accept number with "0x" prefix</param>
        /// <returns>If successfully - converted value, otherwise null</returns>
        public static ushort? ConvertHexToDec(string value, bool acceptPrefix)
        {
            ushort? res;

            try
            {
                if (value.StartsWith("0x"))
                {
                    if (acceptPrefix)
                    {
                        value = value.Remove(0, 2);
                    }
                    else
                    {
                        return null;
                    }
                }

                res = Convert.ToUInt16(value, 16);
            }
            catch
            {
                res = null;
            }
            return res;
        }
        /// <summary>
        /// Converts hex value of 0xFF type to UInt16
        /// </summary>
        /// <param name="value">Value of 0xFF type</param>
        /// <returns>If successfully - converted value, otherwise null</returns>
        public static ushort? ConvertHexToDec(string value)
        {
            return ConvertHexToDec(value, true);
        }
        #endregion Convertation methods

        #region Export/Import functions
        public void Export(string fileName)
        {
            string xmlData = Serialize(m_regSpaceList, typeof(CyRegSpaceConfig), false);
            try
            {
                using (StreamWriter writer = new StreamWriter(fileName))
                {
                    writer.Write(xmlData);
                }
            }
            catch
            {
                MessageBox.Show(Resources.FileWriteError, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                   MessageBoxIcon.Error);
            }
        }

        public void Import(string fileName)
        {
            try
            {
                string xmlData;
                using (StreamReader sr = new StreamReader(fileName))
                {
                    xmlData = sr.ReadToEnd();
                }
                m_regSpaceList = (CyRegSpaceConfig)Deserialize(xmlData, typeof(CyRegSpaceConfig), false);
                int index = 0;
                foreach (CyRegSpace regSpace in m_regSpaceList.m_regSpaces)
                {
                    regSpace.InitGenericData(index++);
                }
            }
            catch
            {
                MessageBox.Show(Resources.FileReadError, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }
        #endregion
    }
}
