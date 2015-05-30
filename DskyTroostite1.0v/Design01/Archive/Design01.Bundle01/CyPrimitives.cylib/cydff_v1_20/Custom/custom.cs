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

namespace Cypress.Semiconductor.CyDesigner.cydff_v1_20
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        const string GENERATED_SHAPE = "SymbolShape";
        const string RESET_VALUE = "0";
        const int APRESET = 1;
        const int ARESET = 2;        
        const int SPRESET = 3;
        const int SRESET = 4;

        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(
            ICyInstQuery_v1 instQuery,
            ICyTerminalQuery_v1 termQuery,
            out string codeSnippet)
        {
		    CyCustErr err;
            Debug.Assert(instQuery != null);
            if (instQuery == null)
            {
                codeSnippet = string.Empty;
                return new CyCustErr("Invalid instance query parameter");
            }

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
			
			CyCompDevParam MultiPresetReset_param = instQuery.GetCommittedParam("MultiPresetReset");
            bool multiPresetReset;
            err = MultiPresetReset_param.TryGetValueAs<bool>(out multiPresetReset);

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
            string myAPresetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "asyncPreset");
            string myAResetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "asyncReset");            
            string mySPresetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "syncPreset");
            string mySResetName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "syncReset");


            //declare a register to hold the value in the always block
            vGen.DeclareReg(tempRegName, suffix);

            List<string> SensitivityList = new List<string>();
            List<CyVerilogBuilder.EdgeTypeEnum> signalEdgeList = new List<CyVerilogBuilder.EdgeTypeEnum>();

            string apSigSegName = string.Empty;
            string arSigSegName = string.Empty;
            string spSigSegName = string.Empty;
            string srSigSegName = string.Empty;
            
            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset = int.Parse(presetOrReset_param.Value);
            bool needAR = false;
            bool needAP = false;
            bool needSP = false;            
            bool needSR = false;
            
            if (presetOrReset == APRESET)
            {
                needAP = true;
            } else if (presetOrReset == ARESET)
            {
                needAR = true;
            }else if (presetOrReset == SPRESET)
            {
                needSP = true;
            }else if (presetOrReset == SRESET)
            {
                needSR = true;
            }
            
            if (needAP)
            { 
			    if (multiPresetReset == true)
				{
				    apSigSegName = termQuery.GetTermSigSegScalarName("ap" + suffix);
				}
				else				
                    apSigSegName = termQuery.GetTermSigSegScalarName("ap");
                vGen.DeclareWire(myAPresetName, "");
                vGen.AddAssignStatement(myAPresetName, apSigSegName);
                apSigSegName = null;
                SensitivityList.Add(myAPresetName);
                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);				
            }

            if (needAR)
            {
			    if (multiPresetReset == true)
				{
				    arSigSegName = termQuery.GetTermSigSegScalarName("ar" + suffix);
				}
				else				
				    arSigSegName = termQuery.GetTermSigSegScalarName("ar");
				
                vGen.DeclareWire(myAResetName, "");
                vGen.AddAssignStatement(myAResetName, arSigSegName);
                arSigSegName = null;
                SensitivityList.Add(myAResetName);
                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);
            }

            if (needSR)
            {
			    if (multiPresetReset == true)
				{
				    srSigSegName = termQuery.GetTermSigSegScalarName("sr" + suffix);
				}
				else
                    srSigSegName = termQuery.GetTermSigSegScalarName("sr");
					
                vGen.DeclareWire(mySResetName, "");
                vGen.AddAssignStatement(mySResetName, srSigSegName);
                srSigSegName = null;
            }
            if (needSP)
            {
			     if (multiPresetReset == true)
				{
				    spSigSegName = termQuery.GetTermSigSegScalarName("sp" + suffix);
				}
				else   
                    spSigSegName = termQuery.GetTermSigSegScalarName("sp");
					
                vGen.DeclareWire(mySPresetName, "");
                vGen.AddAssignStatement(mySPresetName, spSigSegName);
                spSigSegName = null;
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
                vGen.AddIfStmt(myAResetName);
                vGen.AddStatement(tempRegName, RESET_VALUE);
                vGen.AddEndIfStmt();
            }

              if (needSR)
            {
                vGen.AddIfStmt(mySResetName);
                vGen.AddStatement(tempRegName, RESET_VALUE);
                vGen.AddEndIfStmt();
            }
			
            if (needAP)
            {
                if (needAR)
                    vGen.AddElseIfStmt(myAPresetName);
                else
                    vGen.AddIfStmt(myAPresetName);

                vGen.AddStatement(tempRegName, "~" + RESET_VALUE);
                vGen.AddEndIfStmt();
            }
            
			 if (needSP)
            {
                if (needSR)
                    vGen.AddElseIfStmt(mySPresetName);
                else
                    vGen.AddIfStmt(mySPresetName);

                vGen.AddStatement(tempRegName, "~" + RESET_VALUE);
                vGen.AddEndIfStmt();
            }
           
            if (needAP || needAR || needSR || needSP)
            {
                vGen.AddElseStmt();
            }

            vGen.AddStatement(tempRegName, dSigSegName);

           if (needAP || needAR || needSR || needSP)
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

            const int APRESET = 1;
            const int ARESET = 2;
            const int SPRESET = 3;
            const int SRESET = 4;
            
            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth;
            err = terminalWidth_param.TryGetValueAs<uint>(out terminalWidth);
            if (err.IsNotOk) return err;

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            string newDTermName = "d" + suffix;
            string newQTermName = "q" + suffix;

            CyCompDevParam MultiPresetReset_param = instQuery.GetCommittedParam("MultiPresetReset");
            bool multiPresetReset;
            err = MultiPresetReset_param.TryGetValueAs<bool>(out multiPresetReset);
            if (err.IsNotOk) return err;
                        
            string dTermName = termEdit.GetTermName("d");
            string qTermName = termEdit.GetTermName("q");
            string apTermName = termEdit.GetTermName("ap");
            string arTermName = termEdit.GetTermName("ar");
            string spTermName = termEdit.GetTermName("sp");
            string srTermName = termEdit.GetTermName("sr");
            
            termEdit.TerminalRename(dTermName, newDTermName);
            termEdit.TerminalRename(qTermName, newQTermName);

            if(multiPresetReset == true)
            {
                string newApTermName = "ap" + suffix;
                string newArTermName = "ar" + suffix;
                string newSpTermName = "sp" + suffix;
                string newSrTermName = "sr" + suffix;
                
                termEdit.TerminalRename(apTermName, newApTermName);
                termEdit.TerminalRename(arTermName, newArTermName);
                termEdit.TerminalRename(spTermName, newSpTermName);
                termEdit.TerminalRename(srTermName, newSrTermName);
            }            
            
            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset;
            err = presetOrReset_param.TryGetValueAs<int>(out presetOrReset);
            if (err.IsNotOk) return err;

            bool needAP = false;            
            bool needAR = false;
            bool needSP = false;            
            bool needSR = false;
            if (presetOrReset == APRESET)
            {
                needAP = true;
            } else if (presetOrReset == ARESET)
            {
                needAR = true;
            }else if (presetOrReset == SPRESET)
            {
                needSP = true;
            }else if (presetOrReset == SRESET)
            {
                needSR = true;
            }
                        
            termEdit.ChangeTerminalDefVerilogValue(apTermName, (needAP) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(arTermName, (needAR) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(spTermName, (needSP) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(srTermName, (needSR) ? string.Empty : "1'b0");
            
            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//

