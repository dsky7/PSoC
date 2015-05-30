/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;

namespace MDIO_Interface_v1_10
{
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyShapeCustomize_v1
    {
        public const string GENERAL_TAB_NAME = "General";
        public const string ADVANCED_TAB_NAME = "Advanced";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            parameters.m_editor = editor;
            CyBasicTab basicTab = new CyBasicTab(parameters);
            CyAdvancedTab advancedTab = new CyAdvancedTab(parameters);
            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                if (param.TabName == basicTab.TabName)
                {
                    basicTab.UpdateUI();
                }
                else if (param.TabName == advancedTab.TabName)
                {
                    advancedTab.UpdateUIFromExprView();
                }
                parameters.GlobalEditMode = true;
            };
            editor.AddCustomPage(Resources.GeneralTabDisplayName, basicTab, exprDelegate, basicTab.TabName);
            editor.AddCustomPage(Resources.AdvancedTabDisplayName, advancedTab, exprDelegate, advancedTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            basicTab.UpdateUI();
            parameters.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        const byte MAX_LINE_LENGTH = 120;
        const string REGISTER_PAGE_NAME = "registerPage";
        const string REGISTER_CONFIG_NAME = "registerConfig";
        bool m_isPSoC5;
        string m_instanceName;
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;
            m_isPSoC5 = query.DeviceQuery.IsPSoC5;
            CyParameters parameters = new CyParameters(query);
            m_instanceName = parameters.InstanceName;

            // Do not generate *_REG.c and *_REG.h files in basic mode
            if (parameters.OperationMode == CyOperationModeType.BASIC)
            {
                for (int i = customizers.Count - 1; i >= 0; i--)
                {
                    if (customizers[i].OutputName.ToLower().EndsWith((m_instanceName + "_REG.c").ToLower()) ||
                        customizers[i].OutputName.ToLower().EndsWith((m_instanceName + "_REG.h").ToLower()))
                    {
                        customizers.RemoveAt(i);
                    }
                }
            }

            // Temporary objects for collecting data
            List<List<byte>> bitCollection = new List<List<byte>>();
            List<StringBuilder> sbl = new List<StringBuilder>();

            // Generate data width define
            // Generate memory type define
            foreach (CyRegSpace item in parameters.m_regSpaceList.m_regSpaces)
            {
                bitCollection.Add(new List<byte>());
                bitCollection[0].Add((byte)(item.DataWidth == CyDataWidthType.BIT_8 ? 0 : 1));
                bitCollection.Add(new List<byte>());
                bitCollection[1].Add((byte)(item.MemoryType == CyMemoryType.FLASH ? 0 : 1));
                bitCollection.Add(new List<byte>());
                bitCollection[2].Add((byte)(item.ConfigType == CyMemoryType.FLASH ? 0 : 1));
            }
            paramDict.Add("DataWidth", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(bitCollection[0])), "u"));
            paramDict.Add("MemoryType", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(bitCollection[1])), "u"));
            paramDict.Add("ConfigType", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(bitCollection[2])), "u"));

            // Generate defines with register space name
            // Generate defines with start address
            // Generate defines with end address
            sbl.Add(new StringBuilder());
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbl[0].AppendLine(string.Format("    /* Register space {0} definition */", regSpaceIndex + 1));
                sbl[0].AppendLine(string.Format("    #define {0}_{1}_IDX ({2}u)", m_instanceName, regSpace.Name,
                    regSpaceIndex + 1));
                sbl.Add(new StringBuilder());
                sbl[0].AppendLine(string.Format("    #define {0}_{1}_START ({2}u)", m_instanceName, regSpace.Name,
                    CyParameters.ConvertDecToHex(regSpace.StartAddress.Value)));
                sbl.Add(new StringBuilder());
                sbl[0].AppendLine(string.Format("    #define {0}_{1}_END ({2}u)", m_instanceName, regSpace.Name,
                    CyParameters.ConvertDecToHex(regSpace.EndAddress.Value)));
                sbl[0].AppendLine(string.Format("    #define {0}_{1}_PTR {2}", m_instanceName, regSpace.Name,
                    String.Format("{0}_{1}_{2}", m_instanceName, REGISTER_PAGE_NAME, regSpaceIndex + 1)));
                sbl[0].AppendLine(string.Format("    #define {0}_{1}_CONFIG_PTR {2}", m_instanceName, regSpace.Name,
                    String.Format("{0}_{1}_{2}", m_instanceName, REGISTER_CONFIG_NAME, regSpaceIndex + 1)));
                sbl[0].AppendLine();
            }
            paramDict.Add("RegSpaceInfo", sbl[0].ToString());

            // Generate register page size
            sbl[0].Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbl[0].AppendLine(string.Format("#define {0} ({1}u)", GetRegisterPageSizeDefine(m_instanceName,
                    regSpaceIndex), regSpace.AddressConfig.Count));
            }
            paramDict.Add("RegPagesSize", sbl[0].ToString());

            // Generate register page declarations
            sbl[0].Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbl[0].AppendLine(GetRegisterPageDeclaration(regSpaceIndex, regSpace, true));
            }
            // Generate register configuration declarations
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbl[0].AppendLine(string.Format("/* Page {0} register configuration */", regSpaceIndex + 1));
                sbl[0].AppendLine(string.Format("extern {0}{1}_REG_CONFIG_STRUCT {2}{1}_{3}_{4}[{5}];",
                    regSpace.ConfigType == CyMemoryType.FLASH ? "const " : string.Empty,
                    m_instanceName,
                    regSpace.ConfigType == CyMemoryType.FLASH ? "CYCODE " : string.Empty,
                    REGISTER_CONFIG_NAME,
                    regSpaceIndex + 1,
                    GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
            }
            paramDict.Add("RegisterDeclaration", sbl[0].ToString());

            // Generate register page array
            sbl.Add(new StringBuilder());
            sbl[1].Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbl[0].Length = 0;
                // Check if all init values equal to zero
                bool allZeros = true;
                if (regSpace.MemoryType == CyMemoryType.SRAM)
                {
                    for (int addressIndex = 0; addressIndex < regSpace.AddressConfig.Count; addressIndex++)
                    {
                        if (regSpace.AddressConfig[addressIndex].InitValue != 0)
                        {
                            allZeros = false;
                            break;
                        }
                    }
                }
                // All init values equal to 0. Initialization is not necessary, create declaration only
                if (allZeros && regSpace.MemoryType == CyMemoryType.SRAM)
                {
                    if (regSpaceIndex > 0)
                    {
                        sbl[1].AppendLine();
                    }
                    sbl[1].AppendLine(GetRegisterPageDeclaration(regSpaceIndex, regSpace));
                }
                else // some of elements contain values different from 0. Array must be initialized
                {
                    int elementsPerLine = regSpace.DataWidth == CyDataWidthType.BIT_8 ? 16 : 12;
                    for (int addrIndex = 0; addrIndex < regSpace.AddressConfig.Count; addrIndex++)
                    {
                        UInt16 initValue = regSpace.AddressConfig[addrIndex].InitValue.Value;
                        if (m_isPSoC5 && (regSpace.DataWidth == CyDataWidthType.BIT_16))
                        {
                            initValue = SwapBytes(initValue);
                        }
                        if ((addrIndex % elementsPerLine) == 0)
                        {
                            sbl[0].AppendLine();
                            sbl[0].Append("    ");
                        }
                        string str = (regSpace.DataWidth == CyDataWidthType.BIT_16) ?
                            CyParameters.ConvertDecToHex(initValue) : CyParameters.ConvertDecToHex((byte)initValue);
                        sbl[0].Append(string.Concat(str,
                                                   (addrIndex < regSpace.AddressConfig.Count - 1) ? "u, " : "u"));
                    }
                    if (regSpaceIndex > 0)
                    {
                        sbl[1].AppendLine();
                    }
                    sbl[1].AppendLine(string.Format("/* Page {0} register data */", regSpaceIndex + 1));
                    sbl[1].AppendLine(string.Format("{0}uint{1} {2}{3}_{4}_{5}[{6}] ={7}{{{8}{7}}};",
                        regSpace.MemoryType == CyMemoryType.FLASH ? "const " : string.Empty,
                        regSpace.m_dataWidth == CyDataWidthType.BIT_8 ? 8 : 16,
                        regSpace.MemoryType == CyMemoryType.FLASH ? "CYCODE " : string.Empty,
                        m_instanceName,
                        REGISTER_PAGE_NAME,
                        regSpaceIndex + 1,
                        GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex),
                        Environment.NewLine,
                        sbl[0]));
                }
            }
            paramDict.Add("RegisterTable", sbl[1].ToString());

            // Registers configuration (all table values except init value)
            sbl[0].Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                // Register configuration header
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                if (regSpaceIndex > 0)
                {
                    sbl[0].AppendLine();
                }
                sbl[0].AppendLine(string.Format("/* Page {0} register configuration */", regSpaceIndex + 1));
                sbl[0].AppendLine(string.Format("{0}{1}_REG_CONFIG_STRUCT {2}{1}_{3}_{4}[{5}] =",
                    regSpace.ConfigType == CyMemoryType.FLASH ? "const " : string.Empty,
                    m_instanceName,
                    regSpace.ConfigType == CyMemoryType.FLASH ? "CYCODE " : string.Empty,
                    REGISTER_CONFIG_NAME,
                    regSpaceIndex + 1,
                    GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
                sbl[0].Append("{");
                // Register configuration elements
                for (int addrConfigIdx = 0; addrConfigIdx < regSpace.AddressConfig.Count; addrConfigIdx++)
                {
                    if ((addrConfigIdx % 4) == 0)
                    {
                        sbl[0].AppendLine();
                        sbl[0].Append("    ");
                    }
                    sbl[0].Append(string.Format("{{{0}u, {1}u, {2}u}}{3} ",
                        // Mask
                        (regSpace.MemoryType == CyMemoryType.FLASH) ? "0x0000" : GetMask(regSpace, addrConfigIdx),
                        // Control values
                        (regSpace.MemoryType == CyMemoryType.FLASH) ? "0x00" :
                                  CyParameters.ConvertDecToHex(GetCtlRegValue(regSpace.AddressConfig[addrConfigIdx],
                                                                              parameters.EnableAuxBits)),
                        // Reserved byte
                        0,
                        // Comma between array elements
                        (addrConfigIdx < regSpace.AddressConfig.Count - 1) ? "," : ""));
                }
                // Register configuration footer
                sbl[0].AppendLine();
                sbl[0].Append("};");
            }
            paramDict.Add("RegisterConfigurations", sbl[0].ToString());

            // Info list of all register spaces
            sbl[0].Length = 0;
            sbl[0].AppendLine(string.Format("const uint16 * const CYCODE {0}_pageInfoPtr[{0}_PAGE_INFO_SIZE] =",
                                                                   m_instanceName));
            sbl[0].AppendLine("{");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                sbl[0].AppendLine(string.Format("    (const uint16 *) {0}_{1}_{2}, (const uint16 *) {0}_{3}_{2}{4}",
                    m_instanceName,
                    REGISTER_PAGE_NAME,
                    regSpaceIndex + 1,
                    REGISTER_CONFIG_NAME,
                    (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1) ? "," : ""));
            }
            //sbl[0].AppendLine();
            sbl[0].Append("};");
            paramDict.Add("PageInfoList", sbl[0].ToString());

            // Start addresses of register spaces array
            sbl[0].Length = 0;
            sbl[0].AppendLine("    /* Start addresses of register spaces */");
            sbl[0].AppendLine(string.Format("    static uint16 {0}_pageStartAddr[{0}_NUMBER_OF_PAGES] =",
                m_instanceName));
            sbl[0].AppendLine("    {");
            sbl[0].Append("        ");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                if (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1)
                {
                    sbl[0].Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].StartAddress.Value), "u, "));
                }
                else
                {
                    sbl[0].Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].StartAddress.Value), "u"));
                }
            }
            sbl[0].AppendLine();
            sbl[0].Append("    };");
            paramDict.Add("StartAddresses", sbl[0].ToString());

            // End addresses of register spaces array
            sbl[0].Length = 0;
            sbl[0].AppendLine("    /* End addresses of register spaces */");
            sbl[0].AppendLine(string.Format("    static uint16 {0}_pageEndAddr[{0}_NUMBER_OF_PAGES] =",
                m_instanceName));
            sbl[0].AppendLine("    {");
            sbl[0].Append("        ");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                if (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1)
                {
                    sbl[0].Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].EndAddress.Value), "u, "));
                }
                else
                {
                    sbl[0].Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].EndAddress.Value), "u"));
                }
            }
            sbl[0].AppendLine();
            sbl[0].Append("    };");
            paramDict.Add("EndAddresses", sbl[0].ToString());

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }
            return customizers;
        }

        private string GetMask(CyRegSpace regSpace, int addrConfigIdx)
        {
            string result;
            if (regSpace.DataWidth == CyDataWidthType.BIT_8)
            {
                UInt16 mergedBytes;
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, true);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value << 8);
                }
                result = CyParameters.ConvertDecToHex(mergedBytes);
            }
            else
            {
                result = CyParameters.ConvertDecToHex(regSpace.AddressConfig[addrConfigIdx].Mask.Value);
            }
            return result;
        }

        private string GetRegisterPageDeclaration(int regSpaceIndex, CyRegSpace regSpace)
        {
            return GetRegisterPageDeclaration(regSpaceIndex, regSpace, false);
        }
        private string GetRegisterPageDeclaration(int regSpaceIndex, CyRegSpace regSpace, bool addExtern)
        {
            string result = string.Format("/* Page {0} register data */", regSpaceIndex + 1);
            result = string.Concat(result, Environment.NewLine, string.Format("{0}{1}uint{2} {3}{4}_{5}_{6}[{7}];",
                addExtern ? "extern " : string.Empty,
                regSpace.MemoryType == CyMemoryType.FLASH ? "const " : string.Empty,
                regSpace.m_dataWidth == CyDataWidthType.BIT_8 ? 8 : 16,
                regSpace.MemoryType == CyMemoryType.FLASH ? "CYCODE " : string.Empty,
                m_instanceName,
                REGISTER_PAGE_NAME,
                regSpaceIndex + 1,
                GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
            return result;
        }

        private UInt16 GetMergedMasks(CyRegSpace regSpace, int addrConfigIdx)
        {
            UInt16 mergedBytes;
            if (m_isPSoC5)
            {
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, true);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value << 8);
                }
            }
            else
            {
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, false);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value);
                }
            }
            return mergedBytes;
        }

        /// <summary>
        /// Gets byte value where 7-4 bits are Aux bits and 3-0 bits are ClearOnRead, WriteOnly, TriggerOnWrite and
        /// TriggerOnRead respectively
        /// </summary>
        /// <param name="regAddress">Register space configuration table</param>
        /// <returns>Byte value where 7-4 bits are 0 and 3-0 bits are ClearOnRead, WriteOnly, TriggerOnWrite and
        /// TriggerOnRead respectively</returns>
        private static byte GetCtlRegValue(CyRegAddress regAddress, bool enableAuxBits)
        {
            byte auxBits = enableAuxBits ? regAddress.AuxBits.Value : (byte)0;

            List<byte> bitCollection = new List<byte>(new byte[] {
                (byte)(regAddress.TriggerOnRead ? 1 : 0),
                (byte)(regAddress.TriggerOnWrite ? 1 : 0),
                (byte)(regAddress.WriteOnly ? 1 : 0),
                (byte)(regAddress.ClearOnRead ? 1 : 0),
                (byte)((auxBits & CyRegAddress.AUX_BIT_4_MASK) > 0 ? 1 : 0),
                (byte)((auxBits & CyRegAddress.AUX_BIT_5_MASK) > 0 ? 1 : 0),
                (byte)((auxBits & CyRegAddress.AUX_BIT_6_MASK) > 0 ? 1 : 0),
                (byte)((auxBits & CyRegAddress.AUX_BIT_7_MASK) > 0 ? 1 : 0),
            });
            return ConvertByteArrayToByte(bitCollection);
        }

        private static string GetRegisterPageSizeDefine(string instanceName, int regSpaceIndex)
        {
            return string.Format("{0}_REG_PAGE_{1}_SIZE", instanceName, regSpaceIndex + 1);
        }

        private static byte ConvertByteArrayToByte(List<byte> inputArray)
        {
            byte theByte = 0;
            for (int i = inputArray.Count - 1; i >= 0; i--)
            {
                if (inputArray[i] == 1) theByte |= 0x01;
                if (i > 0) theByte <<= 1;
            }
            return theByte;
        }

        /// <summary>
        /// Swaps LSB and MSB of UInt16 value
        /// </summary>
        /// <param name="value">Value that has to be swaped</param>
        /// <returns>Swaped value</returns>
        public static UInt16 SwapBytes(UInt16 value)
        {
            return (UInt16)(((0xFF00 & value) >> 8) | ((0x00FF & value) << 8));
        }

        /// <summary>
        /// Merges less significant byte of the value1 with the less significant byte of the value2
        /// </summary>
        /// <param name="value1">Value 1 which less significant byte has to be merged</param>
        /// <param name="value2">Value 2 which less significant byte has to be merged</param>
        /// <param name="shiftLeft">If true than LSBs of the value1 and value2 will be merged in order v1+v2, 
        /// otherwise in order v2+v1.</param>
        /// <returns>Merged less significant bytes of the value1 and value2 in order that set the 
        /// shiftLeft argument</returns>
        public static UInt16 MergeBytes(UInt16 value1, UInt16 value2, bool shiftLeft)
        {
            return (shiftLeft) ? (UInt16)(((0x00FF & value1) << 8) | (0x00FF & value2)) :
                (UInt16)(((0x00FF & value1)) | (0x00FF & value2) << 8);
        }
        #endregion

        #region ICyShapeCustomize_v1 Members
        const string EN_PAGE_BUS_NAME = "en_page";
        const string TERM_PATERN = "{0}[{1}:1]";
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyParameters parameters = new CyParameters();
            parameters.m_query = instQuery;
            CyCustErr err = termEdit.TerminalRename(termEdit.GetTermName(EN_PAGE_BUS_NAME), string.Format(
                TERM_PATERN, EN_PAGE_BUS_NAME, parameters.NumRegSpace));
            if (err.IsNotOK) return err;
            return CyCustErr.OK;
        }
        #endregion
    }
}
