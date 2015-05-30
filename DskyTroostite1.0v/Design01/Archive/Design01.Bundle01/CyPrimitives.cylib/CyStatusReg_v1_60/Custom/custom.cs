/*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyCustomizer.CyStatusReg_v1_60;

namespace CyCustomizer.CyStatusReg_v1_60
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1
    {

        #region ICyParamEditHook_v1 Members
        public ICyInstEdit_v1 m_Component = null;
        public CyBitFieldEditingControl m_bitFieldEdit = null;

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_Component = edit;
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            m_bitFieldEdit = new CyBitFieldEditingControl(edit);

            CyParamExprDelegate ParamCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam comp)
            {
                //For right now it needs to atleast set a default BitField of the correct Length
                if (comp.Name == CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS)
                {
                    int inputs = CyBitfieldControl.DEFAULT_NUMINPUT;
                    try
                    {
                        inputs = Convert.ToInt16(m_Component.GetCommittedParam(CyStatusReg_v1_60.StatusRegParameters.NUMINPUTS).Value);
                    }
                    catch (Exception) { }
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT0MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT1MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT2MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT3MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT4MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT5MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT6MODE, CyBitfieldControl.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_60.StatusRegParameters.BIT7MODE, CyBitfieldControl.TRANSPARENT);
                }
            };
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_bitFieldEdit.UpdateFormFromParams(edit);
            };
            //TODO: hookup correctly to get expression view
            editor.AddCustomPage("Configure", m_bitFieldEdit, new CyParamExprDelegate(ExprDelegate), "Basic", "Advanced");
            editor.AddDefaultPage("Built-in", "Built-in");
            DialogResult result = editor.ShowDialog();
            editor.ParamExprCommittedDelegate = ParamCommitted;
            return result;
        }

        public bool EditParamsOnDrop
        {
            get { return false; }   
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        
        #endregion

    }




    //Create a new control to add to a tab
    public class CyBitFieldEditingControl : ICyParamEditingControl
    {
        CyBitfieldControl m_control;

        public CyBitFieldEditingControl(ICyInstEdit_v1 inst)
        {
            m_control = new CyBitfieldControl(inst);
            m_control.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return m_control; }
        }

        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            m_control.UpdateFormFromInst(inst);
        }
        
        public IEnumerable<CyCustErr> GetErrors()
        {
            return new CyCustErr[] { };    //return an empty array
        }

        #endregion
    }
}
