/*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.IO;
using CyDesigner.Extensions.Gde;

namespace SegDisplay_v1_0
{
    partial class CyAPIGenerator
    {
        #region Header

        private readonly string m_instanceName;

        public CyAPIGenerator(string instanceName)
        {
            m_instanceName = instanceName;
        }
        #endregion

        #region Header Data
        public void CollectApiHeader(ICyAPICustomizeArgs_v2 args, ref List<CyHelperInfo> HelpersConfig, 
                                    ref Dictionary<string, string> paramDict, int pNumCommonLines, int pNumSegmentLines)
        {
            int index = 0;
            using (TextWriter writerCVariables = new StringWriter(), writerHPixelDef = new StringWriter())
            {
                //GANG
                string gang;
                paramDict.TryGetValue(CyLCDParameters.PARAM_GANG, out gang);
                if (Convert.ToBoolean(Convert.ToInt32(gang)))
                {
                    StringBuilder defStr =
                        new StringBuilder(string.Format("const uint16 CYCODE {0}_gCommons[{1}] = {{", m_instanceName,
                                                        pNumCommonLines));
                    for (int i = 0; i < pNumCommonLines; i++)
                    {
                        defStr.AppendFormat("{0}_GCom{1}, ", m_instanceName, i);
                    }
                    defStr = new StringBuilder(defStr.ToString().TrimEnd(' ', ','));
                    defStr.Append("};");
                    defStr = StringLineBreaking(defStr.ToString());
                    writerCVariables.WriteLine(defStr);
                    writerCVariables.WriteLine("");

                    writerHPixelDef.WriteLine("#define {0}_GANG", m_instanceName);
                    for (int i = 0; i < pNumCommonLines; i++)
                    {
                        int comIndex = i;
                        writerHPixelDef.WriteLine(
                            "#define {0}_GCom{1}    {2}_FIND_PIXEL({3}_GCom__LCD_COM_PORT__{4},  " +
                            "{5}_GCom__LCD_COM_PIN__{6},  {7})", m_instanceName, comIndex, m_instanceName,
                            m_instanceName,
                            comIndex, m_instanceName, comIndex, comIndex);
                    }
                }

                for (int i = 0; i < HelpersConfig.Count; i++)
                {
                    CyHelperInfo hi = HelpersConfig[i];
                    if (hi.Kind != CyHelperKind.EMPTY)
                    {
                        writerCVariables.WriteLine("uint8 const CYCODE {0}_digitNum_{1} = {2};", m_instanceName, index,
                                                   hi.SymbolsCount);
                        WriteHeaderArray(writerCVariables, hi, index);
                        index++;
                    }
                }

                // Array of commons
                writerCVariables.WriteLine("");
                StringBuilder commons = new StringBuilder();
                for (int i = 0; i < pNumCommonLines; i++)
                    commons.AppendFormat("{0}_Com{1}, ", m_instanceName, i);
                commons = new StringBuilder(commons.ToString().TrimEnd(' ', ','));
                commons =
                    new StringBuilder(string.Format("const uint16 CYCODE {0}_commons[{1}] = {{{2}}};", m_instanceName,
                                                    pNumCommonLines, commons));
                writerCVariables.WriteLine(StringLineBreaking(commons.ToString()));

                writerHPixelDef.WriteLine("");

                //Common Generation Sample
                for (int i = 0; i < pNumCommonLines; i++)
                {
                    int comIndex = i;
                    writerHPixelDef.WriteLine("#define {0}_COM{1}_PORT            {2}_Com__LCD_COM_PORT__{3}",
                                              m_instanceName, comIndex, m_instanceName, comIndex);
                    writerHPixelDef.WriteLine("#define {0}_COM{1}_PIN            {2}_Com__LCD_COM_PIN__{3}",
                                              m_instanceName,
                                              comIndex, m_instanceName, comIndex);
                }
                writerHPixelDef.WriteLine("");

                for (int i = 0; i < pNumCommonLines; i++)
                {
                    int comIndex = i;
                    writerHPixelDef.WriteLine(
                        "#define {0}_Com{1}            {2}_FIND_PIXEL({3}_COM{4}_PORT,  {5}_COM{6}_PIN,  {7})",
                        m_instanceName, comIndex, m_instanceName, m_instanceName, comIndex, m_instanceName, comIndex,
                        comIndex);

                }
                writerHPixelDef.WriteLine("");

                //Segmet Generation Sample
                for (int i = 0; i < pNumSegmentLines; i++)
                {
                    int segIndex = i;
                    writerHPixelDef.WriteLine("#define {0}_SEG{1}_PORT            {2}_Seg__LCD_SEG_PORT__{3}",
                                              m_instanceName, segIndex, m_instanceName, segIndex);
                    writerHPixelDef.WriteLine("#define {0}_SEG{1}_PIN            {2}_Seg__LCD_SEG_PIN__{3}",
                                              m_instanceName,
                                              segIndex, m_instanceName, segIndex);
                }
                writerHPixelDef.WriteLine("");

                List<Point> usedComSeg = new List<Point>();
                for (int i = 0; i < HelpersConfig.Count; i++)
                {
                    CyHelperInfo hi = HelpersConfig[i];
                    if (hi.Kind == CyHelperKind.EMPTY) continue;

                    for (int j = 0; j < hi.m_helpSegInfo.Count; j++)
                    {
                        CyHelperSegmentInfo si = hi.m_helpSegInfo[j];

                        // Define only assigned pixels
                        if ((si.Common >= 0) && (si.Segment >= 0))
                        {
                            writerHPixelDef.WriteLine(
                                "#define {0}            {1}_FIND_PIXEL({2}_SEG{3}_PORT,  {4}_SEG{5}_PIN,  {6})", si.Name,
                                m_instanceName, m_instanceName, si.Segment, m_instanceName, si.Segment, si.Common);
                            usedComSeg.Add(new Point(si.Common, si.Segment));
                        }
                    }
                }
                writerHPixelDef.WriteLine("");
                //Add pixels of Empty helper that weren't added before
                for (int i = 0; i < HelpersConfig[0].m_helpSegInfo.Count; i++)
                {
                    CyHelperSegmentInfo si = HelpersConfig[0].m_helpSegInfo[i];

                    if (!usedComSeg.Contains(new Point(si.Common, si.Segment)))
                    {
                        writerHPixelDef.WriteLine(
                            "#define {0}            {1}_FIND_PIXEL({2}_SEG{3}_PORT,  {4}_SEG{5}_PIN,  {6})", si.Name,
                            m_instanceName, m_instanceName, si.Segment, m_instanceName, si.Segment, si.Common);
                    }
                }

                //Add not connected define
                writerHPixelDef.WriteLine();
                writerHPixelDef.WriteLine("#define " + m_instanceName + "_NOT_CON            0xFFFFu");

                // cyfitter defines
                writerHPixelDef.WriteLine();
                writerCVariables.WriteLine();
                GenerateDmaProtoTds(writerCVariables, writerHPixelDef, m_instanceName,
                                    CyCustomizer.GROUP_NAME + "__PORT_GROUP", args.APIFitterQuery);

                paramDict.Add("writerCVariables", writerCVariables.ToString());
                paramDict.Add("writerHPixelDef", writerHPixelDef.ToString());
            }
            SetPinParams(paramDict, pNumCommonLines, pNumSegmentLines);
        }

        private void SetPinParams(Dictionary<string, string> paramDict, int comNum, int segNum)
        {
            // Defines for SetDriveMode function ($pinAPIFuncDec)
            string strGang;
            paramDict.TryGetValue(CyLCDParameters.PARAM_GANG, out strGang);
            bool gang = Convert.ToBoolean(Convert.ToInt32(strGang));
            using (TextWriter writerPins = new StringWriter())
            {
                writerPins.WriteLine(GenerateSetDriveMode(segNum, "Seg"));
                writerPins.WriteLine(GenerateSetDriveMode(comNum, "Com"));
                if (gang)
                    writerPins.WriteLine(GenerateSetDriveMode(comNum, "GCom"));
                paramDict.Add("pinAPIFuncDec", writerPins.ToString());
            }
            // $pinConstDef
            using (TextWriter writerPins = new StringWriter())
            {
                writerPins.Write(GeneratePortDefs(segNum, "Seg"));
                writerPins.Write(GeneratePortDefs(comNum, "Com"));
                if (gang)
                    writerPins.Write(GeneratePortDefs(comNum, "GCom"));
                paramDict.Add("pinConstDef", writerPins.ToString());
            }
        }

        /// <summary>
        /// Breaks up string into lines with max length 120.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        private static StringBuilder StringLineBreaking(string str)
        {
            const int MAX_LEN = 120;
            int index = MAX_LEN;
            StringBuilder strBuild = new StringBuilder(str);
            while (index < strBuild.Length)
            {
                while ((strBuild[index] != ' ') && (index > 0))
                    index--;
                if (index > 0)
                {
                    // Add "\r\n" at the place of the line breaking
                    strBuild.Insert(index + 1, Environment.NewLine);
                    // Remove ' '
                    strBuild.Remove(index, 1);
                    // Add 
                    index += MAX_LEN + 2;
                }
            }
            return strBuild;
        }

        #endregion

        #region Core
        public void CollectApiCore(ICyInstQuery_v1 inst, ref List<CyHelperInfo> HelpersConfig,
                                   ref Dictionary<string, string> paramDict, int pNumCommonLines, int pNumSegmentLines)
        {
            #region FuncDeclarations
            using (TextWriter writerHFuncDeclarations = new StringWriter(), writerCFunctions = new StringWriter())
            {
                //first one is blank
                for (int i = 1; i < HelpersConfig.Count; i++)
                {
                    int p = i - 1;
                    switch (HelpersConfig[i].Kind)
                    {
                        case CyHelperKind.SEGMENT_7:
                            Write7SegDigit_n(writerCFunctions, writerHFuncDeclarations, p);
                            Write7SegNumber_n(writerCFunctions, writerHFuncDeclarations, p);
                            break;
                        case CyHelperKind.SEGMENT_14:
                            PutChar14seg_n(writerCFunctions, writerHFuncDeclarations, p);
                            WriteString14seg_n(writerCFunctions, writerHFuncDeclarations, p);
                            break;
                        case CyHelperKind.SEGMENT_16:
                            PutChar16seg_n(writerCFunctions, writerHFuncDeclarations, p);
                            WriteString16seg_n(writerCFunctions, writerHFuncDeclarations, p);
                            break;
                        case CyHelperKind.BAR:
                            WriteBargraph_n(writerCFunctions, writerHFuncDeclarations, p,
                                            HelpersConfig[i].SymbolsCount);
                            break;
                        case CyHelperKind.MATRIX:
                            PutCharDotMatrix_n(writerCFunctions, writerHFuncDeclarations, p);
                            WriteStringDotMatrix_n(writerCFunctions, writerHFuncDeclarations, p);
                            break;
                        default:
                            break;
                    }
                }
                paramDict.Add("writerCFunctions", writerCFunctions.ToString());
                paramDict.Add("writerHFuncDeclarations", writerHFuncDeclarations.ToString());
            }

            #endregion

        }
        #endregion

        #region Functions

        string HelperSegToArrString(CyHelperInfo hi)
        {
            StringBuilder str = new StringBuilder();
            string[,] p = new string[hi.SymbolsCount, hi.SegmentCount];

            for (int i = 0; i < hi.m_helpSegInfo.Count; i++)
            {
                CyHelperSegmentInfo hsi = hi.m_helpSegInfo[i];
                if ((hsi.Segment >= 0) && (hsi.Common >= 0))
                    p[hsi.m_digitNum, hsi.m_relativePos] = hsi.Name;
                else
                {
                    p[hsi.m_digitNum, hsi.m_relativePos] = string.Format("{0}_NOT_CON", m_instanceName);
                }
            }
            for (int i = 0; i < hi.SymbolsCount; i++)
            {
                str.Append("{");
                for (int j = 0; j < hi.SegmentCount; j++)
                {
                    str.Append(p[i, j]);
                    if (j != hi.SegmentCount - 1) str.Append(", ");
                }
                str.Append("}");
                if (i != hi.SymbolsCount - 1) str.Append(", ");
            }
            return str.ToString();


        }

        void WriteHeaderArray(TextWriter writer, CyHelperInfo hi, int index)
        {
            string str = HelperSegToArrString(hi);
            if (hi.Kind != CyHelperKind.BAR)
            {
                str = string.Format("uint16 const CYCODE {0}_disp{1}[{2}][{3}] = {{{4}}};", m_instanceName, index,
                                    hi.SymbolsCount, hi.SegmentCount, str);
                str = StringLineBreaking(str).ToString();
                writer.WriteLine(str);
            }
            else
            {
                str = string.Format("const uint16 CYCODE {0}_disp{1}[{2}][{3}] = {{{{0}}, {4}}};", m_instanceName, 
                                    index, (hi.SymbolsCount + 1), hi.SegmentCount, str);
                str = StringLineBreaking(str).ToString();
                writer.WriteLine(str);
            }
        }

        #region Cyfitter declarations
        private void GenerateDmaProtoTds(TextWriter writerC, TextWriter writerH, string instName, string name,
                                           ICyAPIFitterQuery_v2 fitQuery)
        {
            string[] portNumStrList = fitQuery.GetFitterAPIEntry(name)
                .Trim(new char[] { '"' }).Split(new char[] { ',' });
            int[] portNums = Array.ConvertAll<string, int>(portNumStrList, Convert.ToInt32);
            int prevPort = Int32.MinValue;
            List<CyPortRange> ranges = new List<CyPortRange>();
            StringBuilder sb = new StringBuilder();
            StringBuilder headerSb = new StringBuilder();

            headerSb.AppendFormat("/* DMA_PROTO_GROUP_NAME={0} */", CyCustomizer.GROUP_NAME).AppendLine();
            headerSb.AppendFormat(
@"struct {0}_DMA_TD_PROTO_ENTRY
{{
	uint8 offset;	/* offset of the first register in this TD */
	uint8 length;	/* length of the register block in this TD */
}};

", instName);

            foreach (int port in portNums)
            {
                if (port == prevPort + 1)
                    ranges[ranges.Count - 1].m_count++;
                else
                    ranges.Add(new CyPortRange(port, 1));
                prevPort = port;
            }

            // Remove __PORT_GROUP, add _DMA_TD_PROTO_BLOCK
            string baseName = name.Substring(0, name.Length - 12);
            string decl = string.Format(
                "const struct {0}_DMA_TD_PROTO_ENTRY CYCODE {0}_{1}_DMA_TD_PROTO_BLOCK[{2}]",
                instName, baseName, ranges.Count);
            headerSb.AppendFormat("#define {0}_{1}_DMA_TD_PROTO_COUNT {2}", instName, baseName, ranges.Count).
                                                                                                        AppendLine();
            sb.AppendLine("/* DMA_PROTO_TD_DEF=*/");
            sb.AppendLine(decl + " =");
            sb.AppendLine("{");

            foreach (CyPortRange range in ranges)
            {
                sb.AppendFormat("    {{{0}, {1}}},", range.m_start, range.m_count).AppendLine();
            }

            sb.AppendLine("};");

            writerC.WriteLine(sb.ToString());
            writerH.WriteLine(headerSb.ToString());

        }

        private class CyPortRange
        {
            public int m_start;
            public int m_count;
            public CyPortRange(int start, int count)
            {
                m_start = start;
                m_count = count;
            }
        }
        #endregion Cyfitter declarations

        #region SetDriveMode declarations

        private string GeneratePortDefs(int num, string prefix)
        {
            StringBuilder str = new StringBuilder();
            for (int i = 0; i < num; i++)
            {
                string defStr = String.Format("{0}_{1}__{2}__PC", m_instanceName, prefix, i);
                str.AppendFormat("#define {0}_{1}Port_{2}            {3}", m_instanceName, prefix, i, defStr).
                    AppendLine();
            }
            return str.ToString();
        }

        private string GenerateSetDriveMode(int num, string prefix)
        {
            StringBuilder str = new StringBuilder();
            string funcName = string.Format("{0}_{1}Port_SetDriveMode", m_instanceName, prefix);
            str.AppendLine("/*******************************************************************************");
            str.AppendFormat("* Function Name: {0}", funcName).AppendLine();
            str.AppendLine("********************************************************************************");
            str.AppendLine("* Summary:");
            str.AppendLine("*  Change the drive mode on the pins of the port.");
            str.AppendLine("*");
            str.AppendLine("* Parameters:");
            str.AppendLine("*  mode: Changes the pins to this drive mode.");
            str.AppendLine("*");
            str.AppendLine("* Return:");
            str.AppendLine("*  void");
            str.AppendLine("*");
            str.AppendLine("*******************************************************************************/");
            str.AppendFormat("void {0}(uint8 mode)", funcName).AppendLine();
            str.AppendLine("{");

            for (int i = 0; i < num; i++)
            {
                str.AppendFormat("    CyPins_SetPinDriveMode({0}_{1}Port_{2}, mode);", m_instanceName, prefix, i).
                AppendLine();
            }
            str.AppendLine("}");
            return str.ToString();
        }

        #endregion SetDriveMode declarations

        #endregion
    }
}
