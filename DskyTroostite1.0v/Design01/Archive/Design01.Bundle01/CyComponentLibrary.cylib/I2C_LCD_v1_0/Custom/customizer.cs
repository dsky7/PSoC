/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;

namespace I2C_LCD_v1_0
{
    [CyCompDevCustomizer]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const string GENERAL_TAB_NAME = "General";
        public const string CUSTOM_COMMANDS_TAB_NAME = "Custom Commands";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = instEdit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            CyParameters parameters = new CyParameters(instEdit);
            CyGeneralTab generalTab = new CyGeneralTab(parameters);
            CyCustomCommandsTab custCmdTab = new CyCustomCommandsTab(parameters);
            CyParamExprDelegate genExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.m_globalEditMode = false;
                generalTab.InitializeUI();
                parameters.m_globalEditMode = true;
            };
            CyParamExprDelegate custExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                custCmdTab.UpdateUI(false);
            };
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, genExprDelegate, generalTab.TabName);
            editor.AddCustomPage(Resources.CustomCmdTabDisplayName, custCmdTab, custExprDelegate, custCmdTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            generalTab.InitializeUI();
            custCmdTab.UpdateUI();
            parameters.m_globalEditMode = true;
            return editor.ShowDialog();
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);
            if (parameters.CheckRequiredCommandsNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcRequiredNullValues);
            }
            if (parameters.CheckCustomCommandsNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcCustomNullValues);
            }
        }
        #endregion
    }
}
