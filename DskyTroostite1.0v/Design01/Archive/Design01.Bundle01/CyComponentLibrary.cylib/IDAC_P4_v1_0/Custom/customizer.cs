/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace IDAC_P4_v1_0
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab page
            CyConfigureTab configureTab = new CyConfigureTab(parameters);

            CyParamExprDelegate dataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.m_globalEditMode = false;
                configureTab.UpdateUI();
                parameters.m_globalEditMode = true;
            };

            // Add tabs to the customizer 
            editor.AddCustomPage(Resources.ConfigureTabDisplayName, configureTab, dataChanged, configureTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            configureTab.UpdateUI();

            parameters.m_globalEditMode = true;

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
}
