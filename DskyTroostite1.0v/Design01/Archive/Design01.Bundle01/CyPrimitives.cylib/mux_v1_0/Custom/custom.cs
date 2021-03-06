/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

using Cypress.Semiconductor.CyDesigner.cy_logic_gate_customizer;

namespace Cypress.Semiconductor.CyDesigner.mux_v1_0
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        const string SELECTOR_BASE_NAME = "muxsel";
        const string OUTPUT_TERM_BASE_NAME = "outTerm";
        const string GENERATED_SHAPE = "SymbolShape";

        #region ICyVerilogCustomize_v1 Members

		// NB: Warp requires that only simple names be used in the always clause.
		//     Therefore, for now, we use the basenames in the sensitivity list.
		//     Yes, we might be sensitive to more than we should;
		//     but we're pushing for alpha-3,
		//     so something working now, albeit crude, is more important.
		//     Hopefully, Warp will synthesis things correctly.

        // Generate code snippet as follows
        //always @(a or b or c or d or selector) 
        //begin 
        //    case (s) 
        //      2'b00   : o = a; 
        //      2'b01   : o = b; 
        //      2'b10   : o = c; 
        //      2'b11   : o = d; 
        //    endcase 
        //end 

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

            CyCompDevParam numTerminals_param = instQuery.GetCommittedParam("NumInputTerminals");
            uint numTerminals = uint.Parse(numTerminals_param.Value);

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("TerminalWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            // Collect the signal segment names for each of the instance terminals
			//================================================================
			// NB: See comment at  top about needing simple names in sensitivity list.
			//================================================================
            List<string> inSigSegNames = new List<string>();
            List<string> inSigSegBaseNames = new List<string>();
            string outTermSigSegName = string.Empty;

            // Note: This works because the term names are generated by us in
            // CustomizeShapes(). The names are created as "term0", "term1" ... 
            // The case statements are netlisted in the same order
            foreach (string termName in GetOrderedInputNames(numTerminals, suffix))
            {
                string connectedTo;
                string sensitiveTo = null;
                
                if (termQuery.GetHasNoDrivers(termName))
                {
                    connectedTo = termQuery.GetTermDefaultVlogExpr(termName);
                } 
                else
                {
                    connectedTo = termQuery.GetTermSigSegName(termName);
                    sensitiveTo = termQuery.GetTermSigSegBaseName(termName);
                }
                
                inSigSegNames.Add(connectedTo);
                
                if (sensitiveTo != null)
                {
                    inSigSegBaseNames.Add(sensitiveTo);
                }
            }

            string outSigSegName = termQuery.GetTermSigSegName(OUTPUT_TERM_BASE_NAME + suffix);

            // Get selector terminal name and width
            string instanceName = instQuery.InstanceName;
            string inSelectorSigSegName = string.Empty;
            string inSelectorSigSegBaseName = string.Empty;
            string selectorTermName = string.Empty;
            uint selectorWidth = selectorWidth = CyBinaryStringGenerator.GetNumSelectorBits(numTerminals);

            selectorTermName = termQuery.GetTermName(SELECTOR_BASE_NAME);
            inSelectorSigSegName = termQuery.GetTermSigSegName(selectorTermName);
            inSelectorSigSegBaseName = termQuery.GetTermSigSegBaseName(selectorTermName);

            CyVerilogBuilder vBuilder = new CyVerilogBuilder();
            vBuilder.AddComment("-- Mux start --");
            vBuilder.AddIfGenerateStmt("1", instanceName);

            // Declare a temp register to hold the the selected value
            string tempRegName = CyVerilogBuilder.GetTmpName("tmp", instanceName, "reg");
            vBuilder.DeclareReg(tempRegName, suffix);

            string selector = inSelectorSigSegBaseName;

            List<string> sensitivity = new List<string>(inSigSegBaseNames);
            sensitivity.Add(selector);
            vBuilder.DefineAlways(sensitivity);

            vBuilder.BeginBlock();
            selector = inSelectorSigSegName;
            vBuilder.AddCaseStmt(selector);
            // This class generates the strings, "00", "01", "10", "11"
            CyBinaryStringGenerator gen = new CyBinaryStringGenerator((uint)inSigSegNames.Count);
            IEnumerator<string> binStrEnumerator = gen.GetBinaryStr().GetEnumerator();

            // Generates case stmt lines, example, 2'b00   : o = a;
            foreach (string s in inSigSegNames)
            {
                binStrEnumerator.MoveNext();

                string caseOption = string.Format("{0}'b{1}", selectorWidth, binStrEnumerator.Current);
                vBuilder.AddCaseStmtCase(caseOption, tempRegName, s);
            }

            vBuilder.AddEndCaseStmt();
            vBuilder.EndBlock(); // End of always

            vBuilder.AddAssignStatement(outSigSegName, tempRegName);
            vBuilder.AddEndIfStmt();
            vBuilder.AddComment("-- Mux end --");

            codeSnippet = vBuilder.VerilogString;

            return CyCustErr.OK;
        }

        private IEnumerable<string> GetOrderedInputNames(uint numTerminals, string suffix)
        {
            for (int index = 0; index < (int)numTerminals; index++)
            {
                yield return string.Format("term{0}{1}", index, suffix);
            }
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

            CyCompDevParam numTerminals_param = instQuery.GetCommittedParam("NumInputTerminals");
            uint numTerminals = uint.Parse(numTerminals_param.Value);
            CyBuilder helper = new CyBuilder(numTerminals, shapeEdit.UserBaseUnit);

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("TerminalWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            IEnumerable<string> termNames = GetOrderedInputNames(numTerminals, suffix);
            IEnumerator<string> nameEnum = termNames.GetEnumerator();

            // Input terminals
            int index = 0;
            foreach (float offset in helper.GetTerminalOffsets())
            {
                bool success = nameEnum.MoveNext();
                string termName = nameEnum.Current;
                termEdit.TerminalAdd(termName, CyCompDevTermDir.INPUT,
                    CyCompDevTermType.DIGITAL, new PointF(0f, offset), "1'b0", 0f, false);
                
                termEdit.SetMustConnectIfVisible(termName, false);
                
                // Move Annotations to correct pins
                if (index == 0)
                {
                    shapeEdit.ShapesMoveTo("lowest", new PointF(17.5f, offset - 2.3f));
                }
                shapeEdit.ShapesMoveTo("highest", new PointF(17.5f, offset - 3.5f));

                index++;
            }

            // Output Terminal
            termEdit.TerminalAdd(OUTPUT_TERM_BASE_NAME + suffix, CyCompDevTermDir.OUTPUT,
                CyCompDevTermType.DIGITAL, new PointF(36f, 0f),
                string.Empty, 0f, false);

            // Mux Shape
            if (numTerminals == 2)
            {
                // If the number of terminals are 2, we still build the shape
                // as if it were a 4 input mux.
                helper = new CyBuilder(4, shapeEdit.UserBaseUnit);
            }
            PointF topLeft = new PointF(6f, helper.TopY - 6f);
            PointF bottomLeft = new PointF(6f, helper.BottomY + 6f);
            PointF topRight = new PointF(30f, helper.TopY + 12f);
            PointF bottomRight = new PointF(30f, helper.BottomY - 12f);
            PointF selectorTermLocation = new PointF(18f, helper.BottomY + 6f);

            // Selector term extender line
            List<string> stExtLine = new List<string>();
            stExtLine.Add("term_extend_line");
            shapeEdit.CreatePolyline(stExtLine,
                new PointF(18f, helper.BottomY),
                new PointF(18f, helper.BottomY - 3f));
            shapeEdit.SetOutlineWidth(stExtLine[0], 0.25f);

            
            // Remove default bus width Slash
            shapeEdit.ShapesRemove("bus_slash");

            // Create Bus Width Slash
            List<string> selBusSlash = new List<string>();
            selBusSlash.Add("selector_bus_slash");
            shapeEdit.CreatePolyline(selBusSlash,
                new PointF(15f, helper.BottomY + 6f),
                new PointF(21f, helper.BottomY + 1.5f));
            shapeEdit.SetOutlineWidth(selBusSlash[0], 0f);

            // Move Bus Width Annotation
            shapeEdit.ShapesMoveTo("selectorBus", new PointF(27f, helper.BottomY));


            // Selector terminal
            uint numOfSelBits = CyBinaryStringGenerator.GetNumSelectorBits(numTerminals);
            string selectorTermName = SELECTOR_BASE_NAME + CyBuilder.GetTermSuffix(numOfSelBits);
            CyCustErr err = termEdit.TerminalAdd(selectorTermName, CyCompDevTermDir.INPUT,
                CyCompDevTermType.DIGITAL, selectorTermLocation, string.Empty, 270f, false);
            Debug.Assert(err.IsOk, "terminal add failed");

            // Mux trapeziod
            shapeEdit.CreatePolyline(shapeTags,
                topLeft, topRight, bottomRight, bottomLeft, topLeft);
            shapeEdit.ShapesConvertToClosed(shapeTags, shapeTags);

            shapeEdit.ShapesMoveBy("highest", new PointF(0f, 0f));
            shapeEdit.ShapesMoveBy("lowest", new PointF(0f, 0f));

            shapeEdit.BringToFront("lowest");
            shapeEdit.BringToFront("highest");
            shapeEdit.SendToBack(GENERATED_SHAPE);
            return CyCustErr.OK;
        }

        #endregion
    }
}
