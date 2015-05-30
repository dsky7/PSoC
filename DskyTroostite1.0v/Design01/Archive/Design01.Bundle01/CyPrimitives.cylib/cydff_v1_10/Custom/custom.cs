/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

using Cypress.Semiconductor.CyDesigner.cy_logic_gate_customizer;

namespace Cypress.Semiconductor.CyDesigner.cydff_v1_10
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        const string GENERATED_SHAPE = "SymbolShape";
        const string RESET_VALUE = "0";
        const int PRESET = 1;
        const int RESET = 2;

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

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            CyVerilogBuilder vGen = new CyVerilogBuilder();
            vGen.AddComment("-- DFF Start --");

            List<string> parameters = new List<string>();

            string dTermName = "d" + suffix;
            string dSigSegName = termQuery.GetTermSigSegName(dTermName);

            string qTermName = "q" + suffix;
            string qSigSegName = termQuery.GetTermSigSegName(qTermName);
                
            int termWidth = termQuery.GetTermSigSegWidth(dTermName);

            string tempRegName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "reg");
			string myClockName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "clk");
			string myPresetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "preset");
			string myResetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "reset");

            //declare a register to hold the value in the always block
            vGen.DeclareReg(tempRegName, suffix);

            List<string> SensitivityList = new List<string>();
            List<CyVerilogBuilder.EdgeTypeEnum> signalEdgeList = new List<CyVerilogBuilder.EdgeTypeEnum>();

            string apSigSegName = string.Empty;
            string arSigSegName = string.Empty;

            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset = int.Parse(presetOrReset_param.Value);
            bool needAR = false;
            bool needAP = false;
            
            if (presetOrReset == PRESET)
            {
                needAP = true;
            } else if (presetOrReset == RESET)
            {
                needAR = true;
            }
            
            if (needAP)
            {
                apSigSegName = termQuery.GetTermSigSegScalarName("ap");
				vGen.DeclareWire(myPresetName, "");
				vGen.AddAssignStatement(myPresetName, apSigSegName);
				apSigSegName = null;
                SensitivityList.Add(myPresetName);
                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);
            }

            if (needAR)
            {
                arSigSegName = termQuery.GetTermSigSegScalarName("ar");
				vGen.DeclareWire(myResetName, "");
				vGen.AddAssignStatement(myResetName, arSigSegName);
				arSigSegName = null;
                SensitivityList.Add(myResetName);
                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);
            }

            string clkSigSegName = termQuery.GetTermSigSegScalarName("clk");
			vGen.DeclareWire(myClockName, "");
			vGen.AddAssignStatement(myClockName, clkSigSegName);
			clkSigSegName = null;
			SensitivityList.Add(myClockName);
			signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);

            vGen.DefineAlways(SensitivityList, signalEdgeList);
            vGen.BeginBlock();

            if (needAR)
            {
                vGen.AddIfStmt(myResetName);
                vGen.AddStatement(tempRegName, RESET_VALUE);
                vGen.AddEndIfStmt();
            }

            if (needAP)
            {
                if (needAR)
                    vGen.AddElseIfStmt(myPresetName);
                else
					vGen.AddIfStmt(myPresetName);

                vGen.AddStatement(tempRegName, "~" + RESET_VALUE);
                vGen.AddEndIfStmt();
            }

           
            if (needAP || needAR)
            {
                vGen.AddElseStmt();
            }

            vGen.AddStatement(tempRegName, dSigSegName);

            if (needAP || needAR)
            {
                vGen.AddEndIfStmt();
            }

            vGen.EndBlock();
            vGen.AddAssignStatement(qSigSegName, tempRegName);

            vGen.AddComment("-- DFF End --");
            codeSnippet = vGen.VerilogString;

            return CyCustErr.OK;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery, 
            ICySymbolShapeEdit_v1 shapeEdit, 
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            const int PRESET = 1;
            const int RESET = 2;
            
            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth;
            err = terminalWidth_param.TryGetValueAs<uint>(out terminalWidth);
            if (err.IsNotOk) return err;

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            string newDTermName = "d" + suffix;
            string newQTermName = "q" + suffix;

            string dTermName = termEdit.GetTermName("d");
            string qTermName = termEdit.GetTermName("q");
            string apTermName = termEdit.GetTermName("ap");
            string arTermName = termEdit.GetTermName("ar");

            termEdit.TerminalRename(dTermName, newDTermName);
            termEdit.TerminalRename(qTermName, newQTermName);

            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset;
            err = presetOrReset_param.TryGetValueAs<int>(out presetOrReset);
            if (err.IsNotOk) return err;

            bool needAP = false;            
            bool needAR = false;
            if (presetOrReset == PRESET)
            {
                needAP = true;
            } else if (presetOrReset == RESET)
            {
                needAR = true;
            }

            termEdit.ChangeTerminalDefVerilogValue(apTermName, (needAP) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(arTermName, (needAR) ? string.Empty : "1'b0");

            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//
