/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Collections;
using System.Text;

namespace I2C_LCD_v1_10
{
    partial class CyCustomizer : ICyAPICustomize_v1
    {
        private const string INDX_POSTFIX = "IDX";
        private const string DATA_LEN_POSTFIX = "DATA_LEN";

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(
            ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;
            CyParameters parameters = new CyParameters(query);

            if (parameters.UseCmdPattern == false)
            {
                parameters.RequiredCommands.Insert(0, new CyRequiredCommandRow(0, 0, true, 0x00, 0x00, 0x00, 0x00,
                    CyParameters.WRITE_DATA_NAME, Resources.CmdDescWritingDataPattern));
            }

            #region Generate CmdPatt array
            StringBuilder sb = new StringBuilder();
            int rowCount = parameters.RequiredCommands.Count + GetEnabledCustomCommandsCount(parameters);
            int colCount = GetMaxCommandSize(parameters) + 1;
            string rowFormat = string.Empty;
            switch (colCount)
            {
                case 2:
                    rowFormat = "    {{{0}u, {1}u}},";
                    break;
                case 3:
                    rowFormat = "    {{{0}u, {1}u, {2}u}},";
                    break;
                case 4:
                    rowFormat = "    {{{0}u, {1}u, {2}u, {3}u}},";
                    break;
                case 5:
                    rowFormat = "    {{{0}u, {1}u, {2}u, {3}u, {4}u}},";
                    break;
                default:
                    break;
            }
            sb.AppendLine(string.Format("static const uint8 CYCODE {0}_cmdPatt[{1}u][{2}u] =",
                                        query.InstanceName, rowCount, colCount));
            sb.AppendLine("{");
            for (int i = 0; i < parameters.RequiredCommands.Count; i++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[i];
                sb.AppendLine(string.Format("    /* {0} */", command.m_cmdDescription));
                sb.AppendLine(string.Format(rowFormat,
                    CyParameters.ConvertDecToHex(command.m_cmdSize.Value),
                    (command.m_cmdByte1.HasValue) ? CyParameters.ConvertDecToHex(command.m_cmdByte1.Value) : "0x00",
                    (command.m_cmdByte2.HasValue) ? CyParameters.ConvertDecToHex(command.m_cmdByte2.Value) : "0x00",
                    (command.m_cmdByte3.HasValue) ? CyParameters.ConvertDecToHex(command.m_cmdByte3.Value) : "0x00",
                    (command.m_cmdByte4.HasValue) ? CyParameters.ConvertDecToHex(command.m_cmdByte4.Value) : "0x00"));
            }
            if (parameters.CustomCommands.Count == 0)
            {
                sb.Remove(sb.Length - 3, 1); // Remove last separator if Custom Commands table is empty
            }

            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[i];
                bool rowAdded = false;
                if (command.m_enable)
                {
                    sb.AppendLine(string.Format("    /* {0} */", "Custom command"));
                    sb.AppendLine(string.Format(rowFormat,
                        CyParameters.ConvertDecToHex(command.m_cmdSize.Value),
                        (command.m_cmdByte1.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.m_cmdByte1.Value) : "0x00",
                        (command.m_cmdByte2.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.m_cmdByte2.Value) : "0x00",
                        (command.m_cmdByte3.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.m_cmdByte3.Value) : "0x00",
                        (command.m_cmdByte4.HasValue) ?
                                            CyParameters.ConvertDecToHex(command.m_cmdByte4.Value) : "0x00"));
                    rowAdded = true;
                }
                if (i == (parameters.CustomCommands.Count - 1) && rowAdded)
                {
                    sb.Remove(sb.Length - 3, 1); // Remove last separator in array
                }
            }
            sb.Append("};");
            paramDict.Add("CmdPattArray", sb.ToString());
            #endregion Generate CmdPatt array

            #region Generate LEN defines
            sb.Length = 0;
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                if (command.m_cmdDescription == Resources.CmdDescSetCursorPosition ||
                    command.m_cmdDescription == Resources.CmdDescLoadCustomCharacter)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                    query.InstanceName,
                    command.m_cmdName.ToUpper(),
                    DATA_LEN_POSTFIX,
                    CyParameters.ConvertDecToHex(command.m_dataSize.Value)));
                }
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_enable && command.m_dataSize > 0)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                    query.InstanceName,
                    command.m_apiName.ToUpper(),
                    DATA_LEN_POSTFIX,
                    CyParameters.ConvertDecToHex(command.m_dataSize.Value)));
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("LenDefines", sb.ToString());
            #endregion Generate LEN defines

            #region Generate INDX defines
            sb.Length = 0;
            int usedCommandCount = parameters.RequiredCommands.Count;
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                        query.InstanceName,
                        command.m_cmdName.ToUpper(),
                        INDX_POSTFIX,
                        CyParameters.ConvertDecToHex((byte)(cmdIndex))));
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_enable)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}_{2} ({3}u)",
                        query.InstanceName,
                        command.m_apiName.ToUpper(),
                        INDX_POSTFIX,
                        CyParameters.ConvertDecToHex((UInt16)(parameters.RequiredCommands.Count + cmdIndex))));
                    usedCommandCount++;
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("IndexDefines", sb.ToString());
            paramDict.Add("UsedCommandCount", String.Format("{0}u", usedCommandCount));
            #endregion Generate INDX defines

            #region Generate Command defines
            sb.Length = 0;
            for (int cmdIndex = 0; cmdIndex < parameters.RequiredCommands.Count; cmdIndex++)
            {
                CyRequiredCommandRow command = parameters.RequiredCommands[cmdIndex];
                if (command.m_cmdByte2.HasValue == false)
                    command.m_cmdByte2 = 0;
                sb.AppendLine(string.Format("#define {0}_{1} ({2}u)",
                        query.InstanceName,
                        command.m_cmdName.ToUpper(),
                        CyParameters.ConvertDecToHex(command.m_cmdByte2.Value)));
            }
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_cmdByte2.HasValue == false)
                    command.m_cmdByte2 = 0;
                sb.AppendLine(string.Format("#define {0}_{1} ({2}u)",
                        query.InstanceName,
                        command.m_apiName.ToUpper(),
                        CyParameters.ConvertDecToHex(command.m_cmdByte2.Value)));
            }
            RemoveLastCharacter(sb);
            paramDict.Add("CommandDefines", sb.ToString());
            #endregion Generate Command defines

            #region Generate Handle Custom Command defines
            sb.Length = 0;
            // Generate commands with size 0
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_enable && command.m_dataSize == 0)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}() {0}_WriteControl({0}_{2})",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper()));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr) {0}_AddrWriteControl(addr, {0}_{2})",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper()));
                }
            }
            // Generate commands with size 1
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_enable && command.m_dataSize == 1)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}(cmdByte) \\{3}        {0}_HandleOneByteCommand({0}_{2}, cmdByte)",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper(),
                    Environment.NewLine));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr, cmdByte) \\{3}        {0}_AddrHandleOneByteCommand(addr, {0}_{2}, cmdByte)",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper(),
                    Environment.NewLine));
                }
            }
            // Generate commands with size > 1
            for (int cmdIndex = 0; cmdIndex < parameters.CustomCommands.Count; cmdIndex++)
            {
                CyCustomCommandRow command = parameters.CustomCommands[cmdIndex];
                if (command.m_enable && command.m_dataSize > 1)
                {
                    sb.AppendLine(string.Format("#define {0}_{1}(cmdData) \\{3}        {0}_HandleCustomCommand({0}_{2}, {0}_{2}_{4}, cmdData)",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper(),
                    Environment.NewLine,
                    DATA_LEN_POSTFIX));
                    sb.AppendLine(string.Format("#define {0}_Addr{1}(addr, cmdData) \\{3}        {0}_AddrHandleCustomCommand(addr, {0}_{2}, {0}_{2}_{4}, cmdData)",
                    query.InstanceName,
                    command.m_apiName,
                    command.m_apiName.ToUpper(),
                    Environment.NewLine,
                    DATA_LEN_POSTFIX));
                }
            }
            RemoveLastCharacter(sb);
            paramDict.Add("HandleCustomCmdDefines", sb.ToString());
            #endregion

            #region Generate Custom Font array
            sb.Length = 0;
            sb.AppendLine(String.Format("uint8 const CYCODE {0}_customFonts[64u] =", query.InstanceName));
            sb.AppendLine("{");
            switch (parameters.CustomCharacterSet)
            {
                case CyECustomCharacterSet.Horizontal:
                    sb.Append(GetHorizontalBargraph());
                    break;
                case CyECustomCharacterSet.Vertical:
                    sb.Append(GetVerticalBargraph());
                    break;
                case CyECustomCharacterSet.UserDefined:
                    for (int i = 0; i < CyParamRanges.CUSTOM_CHAR_NUM; i++)
                    {
                        string[] charColumns = new string[CyParamRanges.CUSTOM_CHAR_NUM];
                        charColumns = parameters.GetCustomChar(i).Split(',');
                        for (int j = 0; j < charColumns.Length; j++)
                        {
                            if ((j % 8) == 0)
                            {
                                if (i > 0) // do not insert new line before first line
                                {
                                    sb.AppendLine();
                                }
                                sb.Append("    ");
                            }
                            sb.Append(String.Format("0x0{0}u{1}",
                                      charColumns[j],
                                      ((i == CyParamRanges.CUSTOM_CHAR_NUM - 1) &&  // add comma for not last elements
                                      (j == charColumns.Length - 1)) ? "" : ", "));
                        }
                    }
                    break;
                default:
                    sb.Length = 0;
                    break;
            }
            if (sb.Length > 0)
            {
                sb.AppendLine();
                sb.Append("};");
            }
            paramDict.Add("CustomFontsArray", sb.ToString());
            #endregion

            paramDict.Add("CharSetValue", string.Concat(CyParameters.ConvertDecToHex(
                (byte)parameters.CustomCharacterSet), "u"));

            // Replace macro dictionaries with paramDict
            for (int i = 0; i < customizers.Count; i++)
            {
                CyAPICustomizer api = customizers[i];
                api.MacroDictionary = paramDict;
            }

            return customizers;
        }

        private static void RemoveLastCharacter(StringBuilder sb)
        {
            if (sb.Length > 0) sb.Length = sb.Length - 2;
        }

        private static int GetMaxCommandSize(CyParameters parameters)
        {
            int maxCommandSize = 0;
            for (int i = 0; i < parameters.RequiredCommands.Count; i++)
            {
                if (parameters.RequiredCommands[i].m_cmdSize > maxCommandSize)
                    maxCommandSize = parameters.RequiredCommands[i].m_cmdSize.Value;
            }
            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                if (parameters.CustomCommands[i].m_enable && (parameters.CustomCommands[i].m_cmdSize > maxCommandSize))
                    maxCommandSize = parameters.CustomCommands[i].m_cmdSize.Value;
            }
            return maxCommandSize;
        }

        private static int GetEnabledCustomCommandsCount(CyParameters parameters)
        {
            int custCmdCount = 0;
            for (int i = 0; i < parameters.CustomCommands.Count; i++)
            {
                if (parameters.CustomCommands[i].m_enable)
                {
                    custCmdCount++;
                }
            }
            return custCmdCount;
        }

        #region Hard Coded Bargraph Character Values
        private string GetVerticalBargraph()
        {
            StringBuilder sb = new StringBuilder();
            // Character LCD_1_CUSTOM_0   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu,");
            // Character LCD_1_CUSTOM_1   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_2    
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_3   
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_4    
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_5    
            sb.AppendLine("    0x00u, 0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_6    
            sb.AppendLine("    0x00u, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_7    
            sb.Append("    0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu");
            return sb.ToString();
        }

        private string GetHorizontalBargraph()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,");
            // Character LCD_1_CUSTOM_1     
            sb.AppendLine("    0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u, 0x10u,");
            // Character LCD_1_CUSTOM_2     
            sb.AppendLine("    0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u, 0x18u,");
            // Character LCD_1_CUSTOM_3     
            sb.AppendLine("    0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu, 0x1Cu,");
            // Character LCD_1_CUSTOM_4     
            sb.AppendLine("    0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu, 0x1Eu,");
            // Character LCD_1_CUSTOM_5     
            sb.AppendLine("    0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu, 0x1Fu,");
            // Character LCD_1_CUSTOM_6     
            sb.AppendLine("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,");
            // Character LCD_1_CUSTOM_7     
            sb.Append("    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u");
            return sb.ToString();
        }
        #endregion
    }
}
