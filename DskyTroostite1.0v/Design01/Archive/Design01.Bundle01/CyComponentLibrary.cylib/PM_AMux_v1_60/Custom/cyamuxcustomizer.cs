/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using System.Diagnostics;
using System.Drawing;
using CyDesigner.Extensions.Gde;

namespace PM_AMux_v1_60
{
    [CyCompDevCustomizer()]
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {

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
            string outASigSegName = string.Empty;
            string outBSigSegName = string.Empty;

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
            uint ChannelWidth = uint.Parse(ChannelWidth_param.Value);

            string mux_A_suffix = string.Empty;
            string mux_B_suffix = string.Empty;

            if (ChannelWidth == DIFFERENTIAL_MUX)
            {
                mux_A_suffix = "_CYAMUXSIDE_A";
                mux_B_suffix = "_CYAMUXSIDE_B";
            }

            // Collect the signal segment names for each of the instance terminals
            List<string> inASigSegNames = new List<string>();
            List<string> inBSigSegNames = new List<string>();


            // Note: This works because the term names are generated by us in
            // CustomizeShapes(). 
            for (int index = 0; index < numTerminals; index++)
            {
                inASigSegNames.Add(termQuery.GetTermSigSegScalarName(GetTermName(INPUT_A_TERM_BASE_NAME, index)));
            }
            outASigSegName = termQuery.GetTermSigSegScalarName(OUTPUT_A_TERM_BASE_NAME);

            // Check if this is a differential mux
            if (ChannelWidth == DIFFERENTIAL_MUX)
            {
                for (int index = 0; index < numTerminals; index++)
                {
                    inBSigSegNames.Add(termQuery.GetTermSigSegScalarName(GetTermName(INPUT_B_TERM_BASE_NAME, index)));
                }
                outBSigSegName = termQuery.GetTermSigSegScalarName(OUTPUT_B_TERM_BASE_NAME);
            }

            string instanceName = instQuery.InstanceName;

            CyVerilogBuilder vBuilder = new CyVerilogBuilder();
            vBuilder.AddComment("-- AMux " + instanceName + " start -- ***");

            // Build first Mux A verilog code
            vBuilder.AddComment("-- Mux A --");
            vBuilder.WriteLine("");
            vBuilder.WriteLine(AMUX_PRIM_NAME + " " + instanceName + mux_A_suffix + "(");
            vBuilder.IncreaseIndent();
            vBuilder.WriteLine(".muxin({");
            vBuilder.IncreaseIndent();
            // Add the signal names for the muxin input
            for (int i = (inASigSegNames.Count - 1) ; i >= 0; i--)
            {
                if (i > 0)
                {
                    vBuilder.WriteLine(inASigSegNames[i] + ",");
                }
                else
                {
                    vBuilder.WriteLine(inASigSegNames[i]);
                }
            }
            vBuilder.WriteLine("}),");
            vBuilder.DecreaseIndent();
            vBuilder.WriteLine(".vout(" + outASigSegName + ")");
            vBuilder.WriteLine(");");
            vBuilder.DecreaseIndent(); 
            vBuilder.WriteLine("");

            vBuilder.DefineParam(instanceName + mux_A_suffix, "muxin_width", numTerminals.ToString());
            vBuilder.DefineParam(instanceName + mux_A_suffix, "init_mux_sel", numTerminals.ToString() + "'h0");
            vBuilder.DefineParam(instanceName + mux_A_suffix, "one_active", "0");
            vBuilder.WriteLine("");

            if (ChannelWidth == DIFFERENTIAL_MUX)
            {
                // Build  Mux B verilog code
                vBuilder.WriteLine("");
                vBuilder.AddComment("-- Mux B --");
                vBuilder.WriteLine("");
                vBuilder.WriteLine(AMUX_PRIM_NAME + " " + instanceName + mux_B_suffix + "(");
                vBuilder.IncreaseIndent();
                vBuilder.WriteLine(".muxin({");
                vBuilder.IncreaseIndent();
                // Add the signal names for the muxin input
                for (int i = (inBSigSegNames.Count - 1); i >= 0; i--)
                {
                    if (i > 0)
                    {
                        vBuilder.WriteLine(inBSigSegNames[i] + ",");
                    }
                    else
                    {
                        vBuilder.WriteLine(inBSigSegNames[i]);
                    }
                }
                vBuilder.WriteLine("}),");
                vBuilder.DecreaseIndent();
                vBuilder.WriteLine(".vout(" + outBSigSegName + ")");
                vBuilder.WriteLine(");");
                vBuilder.DecreaseIndent();
                vBuilder.WriteLine("");

                vBuilder.DefineParam(instanceName + mux_B_suffix, "muxin_width", numTerminals.ToString());
                vBuilder.DefineParam(instanceName + mux_B_suffix, "init_mux_sel", numTerminals.ToString() + "'h0");
                vBuilder.DefineParam(instanceName + mux_B_suffix, "one_active", "0");
                vBuilder.WriteLine("");

            }
            vBuilder.AddComment("-- AMux " + instanceName + " end --");
            codeSnippet = vBuilder.VerilogString;

            return CyCustErr.OK;
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
            // We leave the symbol as it is for symbol preview
            if (instQuery.IsPreviewCanvas)
                return CyCustErr.OK;

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
            CyBuilder helper = new CyBuilder(numTerminals); 

            CyCompDevParam ChannelWidth_param = instQuery.GetCommittedParam("MuxType");
            uint ChannelWidth = uint.Parse(ChannelWidth_param.Value);

            // Place Input terminals
            int index = 0;
            float pinY;
            float pinSpace = (ChannelWidth == SINGLE_MUX) ? 12f : 18f;
            float pinOffset = ((numTerminals % 2) == 0f) ? (((numTerminals / 2f) * -(pinSpace)) + 6f) : 
                                                           (((numTerminals + 1) / 2f) * -(pinSpace) + 12f);
            foreach (float offset in helper.GetTerminalOffsets())
            {
                pinY = (index * pinSpace) + pinOffset;
                if (ChannelWidth == SINGLE_MUX)
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
                                         CyCompDevTermType.ANALOG, new PointF(0f, pinY+6f), string.Empty, 0f, false);

                }
                index++;
            }

            // Place Output Terminal/s
            if (ChannelWidth == SINGLE_MUX)              // Single ended Mux
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


            // Generate trapezoid points
            float topY = pinOffset - 6f;
            float bottomY = ((numTerminals-1) * pinSpace) + pinOffset + 12f; 
            if (ChannelWidth == SINGLE_MUX)
            {
                PointF topLeft = new PointF(6f, topY - 6f);
                PointF bottomLeft = new PointF(6f, bottomY );
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
            shapeEdit.ShapesMoveTo("theMinChannel", new PointF(15f, ((numTerminals) * -(pinSpace/2)) + 2f));

            float maxAdjust = (ChannelWidth == SINGLE_MUX) ? 11f : 17f;
            if (numTerminals <= 10)
            {
                shapeEdit.ShapesMoveTo("theMaxChannel", new PointF(15f, ((numTerminals) * (pinSpace/2)) - maxAdjust));
            }
            else
            {
                shapeEdit.ShapesMoveTo("theMaxChannel", new PointF(19f, ((numTerminals) * (pinSpace/2)) - maxAdjust));
            }
            shapeEdit.BringToFront("theMaxChannel");
            shapeEdit.BringToFront("theMinChannel");
            return CyCustErr.OK;
        }

        #endregion
    }
}
