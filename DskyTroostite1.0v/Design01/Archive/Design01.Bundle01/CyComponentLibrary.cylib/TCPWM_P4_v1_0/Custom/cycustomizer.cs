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
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Scc;


namespace TCPWM_P4_v1_0
{
    [CyCompDevCustomizer]
    public partial class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
              ICyExpressMgr_v1 mgr)
        {            
            CyParameters prms = new CyParameters(edit);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            prms.m_editor = editor;

            CyConfigTab configTab = new CyConfigTab(prms);
            CyTCPWMTab tcpwmTab = new CyTCPWMTab(prms);
            CyTimerCounterTab tcTab = new CyTimerCounterTab(prms);
            CyPWMTab pwmTab = new CyPWMTab(prms);
            CyQuadDecTab quaddecTab = new CyQuadDecTab(prms);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                prms.m_globalEditMode = false;
                prms.UpdateTabVisibility();
                prms.m_globalEditMode = true;
            };

            editor.AddCustomPage(Resources.TabNameConfig, configTab, exprDelegate, configTab.TabName);
            editor.AddCustomPage(Resources.TabNameTCPWM, tcpwmTab, exprDelegate, tcpwmTab.TabName);
            editor.AddCustomPage(Resources.TabNameTC, tcTab, exprDelegate, tcTab.TabName);
            editor.AddCustomPage(Resources.TabNamePWM, pwmTab, exprDelegate, pwmTab.TabName);
            editor.AddCustomPage(Resources.TabNameQuadDec, quaddecTab, exprDelegate, quaddecTab.TabName);
            editor.AddDefaultPage(Resources.TabBuiltIn, "Built-in");

            editor.UseBigEditor = true;
            prms.m_globalEditMode = true;
            prms.UpdateTabVisibility();
            return editor.ShowDialog();
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

    #region Wrapper for Tabs
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_prms = null;

        public virtual string TabName
        {
            get { return "Empty"; }
        }

        public CyEditingWrapperControl() { }

        public CyEditingWrapperControl(CyParameters prms)
        {
            m_prms = prms;
            this.AutoScroll = true;
            this.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string paramName in m_prms.m_edit.GetParamNames())
            {
                CyCompDevParam param = m_prms.m_edit.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
        }
        #endregion
    }
    #endregion
}
