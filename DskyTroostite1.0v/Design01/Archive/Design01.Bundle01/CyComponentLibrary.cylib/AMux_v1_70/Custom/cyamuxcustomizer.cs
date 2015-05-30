/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using System.Diagnostics;
using System.Drawing;
using CyDesigner.Extensions.Gde;

namespace AMux_v1_70
{
    [CyCompDevCustomizer()]
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {

        private enum AmuxCodeType
        {
            Single,
            Differential_A,
            Differential_B
        }

        const string OUTPUT_A_TERM_BASE_NAME = "AoutTerm";
        const string OUTPUT_B_TERM_BASE_NAME = "BoutTerm";
        const string GENERATED_SHAPE = "SymbolShape";
        const string INPUT_A_TERM_BASE_NAME = "AinTerm";
        const string INPUT_B_TERM_BASE_NAME = "BinTerm";
        const string AMUX_PRIM_NAME = "cy_psoc3_amux_v1_0";

        const uint SINGLE_MUX = 1;
        const uint DIFFERENTIAL_MUX = 2;
		
        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(
            ICyInstQuery_v1 instQuery,
            ICyTerminalQuery_v1 termQuery,
            out string codeSnippet)
        {
            Debug.Assert(instQuery != null);
            if (instQuery == null)
            {
                codeSnippet = string.Empty;
                return new CyCustErr("Invalid instance query parameter");
            }

            // Get parameters
            CyCompDevParam numTerminals_param = instQuery.GetCommittedParam("Channels");
            uint numTerminals = uint.Parse(numTerminals_param.Value);

            CyCompDevParam ChannelWidth_param = instQuery.GetCommittedParam("MuxType");
            uint channelWidth = uint.Parse(ChannelWidth_param.Value);

            CyCompDevParam OneActive_param = instQuery.GetCommittedParam("AtMostOneActive");
            int oneActive = bool.Parse(OneActive_param.Value) ? 1 : 0;
			
			CyCompDevParam isolation_param = instQuery.GetCommittedParam("Isolation");
            uint isolation = uint.Parse(isolation_param.Value);

            string instanceName = instQuery.InstanceName;

            CyVerilogBuilder vBuilder = new CyVerilogBuilder();
            vBuilder.AddComment("-- AMux " + instanceName + " start -- ***");

            AmuxCodeType type = channelWidth == DIFFERENTIAL_MUX ? AmuxCodeType.Differential_A : AmuxCodeType.Single;

            // Build Mux A verilog code
            WriteAmuxCode(vBuilder, termQuery, instanceName, type, numTerminals, oneActive, isolation);

            if (channelWidth == DIFFERENTIAL_MUX)
            {
                // Build Mux B verilog code
                WriteAmuxCode(vBuilder, termQuery, instanceName, AmuxCodeType.Differential_B, numTerminals, oneActive, isolation);
            }

            vBuilder.AddComment("-- AMux " + instanceName + " end --");
            codeSnippet = vBuilder.VerilogString;

            return CyCustErr.OK;
        }

        private void WriteAmuxCode(
            CyVerilogBuilder vBuilder, 
            ICyTerminalQuery_v1 termQuery, 
            string instanceName, 
            AmuxCodeType type, 
            uint numTerminals, 
            int oneActive,
			uint isolation)
        {
            string muxSuffix;

            switch (type)
            {
                default:
                case AmuxCodeType.Single:
                    muxSuffix = string.Empty;
                    break;
                case AmuxCodeType.Differential_A:
                    muxSuffix = "_CYAMUXSIDE_A";
                    break;
                case AmuxCodeType.Differential_B:
                    muxSuffix = "_CYAMUXSIDE_B";
                    break;

            }

            string inputTermBaseName = type == AmuxCodeType.Differential_B 
                ? INPUT_B_TERM_BASE_NAME 
                : INPUT_A_TERM_BASE_NAME;

            string outputTermBaseName = type == AmuxCodeType.Differential_B 
                ? OUTPUT_B_TERM_BASE_NAME 
                : OUTPUT_A_TERM_BASE_NAME;

            // Collect the signal segment names for each of the instance terminals
            List<string> inSigSegNames = new List<string>();

            // Note: This works because the term names are generated by us in
            // CustomizeShapes(). 
            for (int index = 0; index < numTerminals; index++)
            {
                inSigSegNames.Add(termQuery.GetTermSigSegScalarName(GetTermName(inputTermBaseName, index)));
            }

            string outSigSegName = termQuery.GetTermSigSegScalarName(outputTermBaseName);

            if (type == AmuxCodeType.Differential_B)
            {
                vBuilder.WriteLine("");
                vBuilder.AddComment("-- Mux B --");
            }
            else
            {
                vBuilder.AddComment("-- Mux A --");
            }
            vBuilder.WriteLine("");
            vBuilder.WriteLine(AMUX_PRIM_NAME + " " + instanceName + muxSuffix + "(");
            vBuilder.IncreaseIndent();
            vBuilder.WriteLine(".muxin({");
            vBuilder.IncreaseIndent();
            // Add the signal names for the muxin input
            for (int i = (inSigSegNames.Count - 1); i >= 0; i--)
            {
                if (i > 0)
                {
                    vBuilder.WriteLine(inSigSegNames[i] + ",");
                }
                else
                {
                    vBuilder.WriteLine(inSigSegNames[i]);
                }
            }
            vBuilder.WriteLine("}),");
            vBuilder.DecreaseIndent();
            vBuilder.WriteLine(".vout(" + outSigSegName + ")");
            vBuilder.WriteLine(");");
            vBuilder.DecreaseIndent();
            vBuilder.WriteLine("");

            vBuilder.DefineParam(instanceName + muxSuffix, "muxin_width", numTerminals.ToString());
            vBuilder.DefineParam(instanceName + muxSuffix, "init_mux_sel", numTerminals.ToString() + "'h0");
            vBuilder.DefineParam(instanceName + muxSuffix, "one_active", oneActive.ToString());
            vBuilder.DefineParam(instanceName + muxSuffix, "connect_mode", isolation.ToString());
			vBuilder.WriteLine("");
        }

        private string GetTermName(string baseName, int index)
        {
            return baseName + index;
        }

        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            shapeEdit.ShapesRemove("dummyTerminal");
            shapeEdit.ShapesRemove("symbolName");
            shapeEdit.ShapesRemove("preview_shape");
            termEdit.RemoveAllTerminals();

            // Add term shapes
            List<string> shapeTags = new List<string>();
            shapeTags.Add(GENERATED_SHAPE);

            // Read Parameters
            CyCompDevParam numTerminals_param = instQuery.GetCommittedParam("Channels");
            uint numTerminals = uint.Parse(numTerminals_param.Value);

            CyCompDevParam ChannelWidth_param = instQuery.GetCommittedParam("MuxType");
            uint channelWidth = uint.Parse(ChannelWidth_param.Value);

            // Place Input terminals
            float pinSpace = (channelWidth == SINGLE_MUX) ? 12f : 18f;
            float pinOffset = ((numTerminals % 2) == 0f) ? 
                (((numTerminals / 2f) * -(pinSpace)) + 6f) : (((numTerminals + 1) / 2f) * -(pinSpace) + 12f);

            for (int index = 0; index < numTerminals; index++)
            {
                float pinY = (index*pinSpace) + pinOffset;

                if (channelWidth == SINGLE_MUX)
                {
                    string termName = GetTermName(INPUT_A_TERM_BASE_NAME, index);
                    termEdit.TerminalAdd(termName, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG,
                                         new PointF(0f, pinY), string.Empty, 0f, false);
                }
                else
                {
                    string termNameA = GetTermName(INPUT_A_TERM_BASE_NAME, index);
                    termEdit.TerminalAdd(termNameA, CyCompDevTermDir.INOUT,
                                         CyCompDevTermType.ANALOG, new PointF(0f, pinY), string.Empty, 0f, false);

                    string termNameB = GetTermName(INPUT_B_TERM_BASE_NAME, index);
                    termEdit.TerminalAdd(termNameB, CyCompDevTermDir.INOUT,
                                         CyCompDevTermType.ANALOG, new PointF(0f, pinY + 6f), string.Empty, 0f, false);
                }
            }

            // Place Output Terminal/s
            if (channelWidth == SINGLE_MUX)              // Single ended Mux
            {
                termEdit.TerminalAdd(OUTPUT_A_TERM_BASE_NAME, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG,
                                     new PointF(30f, 0f), string.Empty, 180f, false);
            }
            else                                         // Differential Mux
            {
                termEdit.TerminalAdd(OUTPUT_A_TERM_BASE_NAME, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG,
                                     new PointF(30f, -6f), string.Empty, 180f, false);

                termEdit.TerminalAdd(OUTPUT_B_TERM_BASE_NAME, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG,
                                     new PointF(30f, 6f), string.Empty, 180f, false);
            }

            // Single terminal mux needs to be drawn seperately. 
            if (numTerminals == 1) return DrawSingleTermAmux(channelWidth, shapeEdit, shapeTags);

            // Generate trapezoid points
            float topY = pinOffset - 6f;
            float bottomY = ((numTerminals - 1) * pinSpace) + pinOffset + 12f;
            if (channelWidth == SINGLE_MUX)
            {
                PointF topLeft = new PointF(6f, topY - 6f);
                PointF bottomLeft = new PointF(6f, bottomY);
                PointF topRight = new PointF(24f, topY + 6f);
                PointF bottomRight = new PointF(24f, bottomY - 12f);
                shapeEdit.CreatePolyline(shapeTags, topLeft, topRight, bottomRight, bottomLeft, topLeft);
            }
            else
            {
                PointF topLeft = new PointF(6f, topY - 6f);
                PointF bottomLeft = new PointF(6f, bottomY + 6f);
                PointF topRight = new PointF(24f, topY + 6f);
                PointF bottomRight = new PointF(24f, bottomY - 6f);
                shapeEdit.CreatePolyline(shapeTags, topLeft, topRight, bottomRight, bottomLeft, topLeft);
            }

            // Draw Mux trapeziod 
            shapeEdit.ShapesConvertToClosed(shapeTags, shapeTags);
            shapeEdit.SetFillColor(shapeTags[shapeTags.Count - 1], Color.Gainsboro);
            shapeEdit.SetOutlineWidth(shapeTags[shapeTags.Count - 1], 1F);

            shapeEdit.ShapesMoveTo("theInstanceName", new PointF(30f, (topY - 18f)));
            shapeEdit.ShapesMoveTo("theMinChannel", new PointF(15f, ((numTerminals) * -(pinSpace / 2)) + 2f));

            float maxAdjust = (channelWidth == SINGLE_MUX) ? 11f : 17f;
            if (numTerminals <= 10)
            {
                shapeEdit.ShapesMoveTo("theMaxChannel", new PointF(15f, ((numTerminals) * (pinSpace / 2)) - maxAdjust));
            }
            else
            {
                shapeEdit.ShapesMoveTo("theMaxChannel", new PointF(19f, ((numTerminals) * (pinSpace / 2)) - maxAdjust));
            }
            shapeEdit.BringToFront("theMaxChannel");
            shapeEdit.BringToFront("theMinChannel");
            return CyCustErr.OK;
        }

        CyCustErr DrawSingleTermAmux(uint channelWidth, ICySymbolShapeEdit_v1 shapeEdit, List<string> shapeTags)
        {
            const float LEFT = 6f;
            const float RIGHT = 24f;

            float leftTop, leftBottom, rightTop, rightBottom, instantNameY, maxChannelY;
            if (channelWidth == SINGLE_MUX)
            {
                leftTop = -18f;
                leftBottom = 18f;
                rightTop = -6f;
                rightBottom = 6f;
                instantNameY = -30f;
                maxChannelY = -4f;
            }
            else
            {
                leftTop = -24f;
                leftBottom = 24f;
                rightTop = -12f;
                rightBottom = 12f;
                instantNameY = -36f;
                maxChannelY = -8f;
            }

            PointF topLeft = new PointF(LEFT, leftTop);
            PointF bottomLeft = new PointF(LEFT, leftBottom);
            PointF topRight = new PointF(RIGHT, rightTop);
            PointF bottomRight = new PointF(RIGHT, rightBottom);
            shapeEdit.CreatePolyline(shapeTags, topLeft, topRight, bottomRight, bottomLeft, topLeft);

            // Draw Mux trapeziod 
            shapeEdit.ShapesConvertToClosed(shapeTags, shapeTags);
            shapeEdit.SetFillColor(shapeTags[shapeTags.Count - 1], Color.Gainsboro);
            shapeEdit.SetOutlineWidth(shapeTags[shapeTags.Count - 1], 1F);

            shapeEdit.ShapesMoveTo("theInstanceName", new PointF(30f, instantNameY));
            shapeEdit.ShapesMoveTo("theMaxChannel", new PointF(15f, maxChannelY));
            shapeEdit.BringToFront("theMaxChannel");
            shapeEdit.ShapesRemove("theMinChannel");

            return CyCustErr.OK;
        }

        #endregion
    }
}
