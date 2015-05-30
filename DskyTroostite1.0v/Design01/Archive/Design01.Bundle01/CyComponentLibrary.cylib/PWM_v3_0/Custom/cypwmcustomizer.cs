/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace PWM_v3_0
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const string CONFIGURE_TAB_NAME = "Basic";
        public const string ADVANCED_TAB_NAME = "Advanced";

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            CyConfigureTab m_control = new CyConfigureTab(parameters);
            CyAdvancedTab m_controladv = new CyAdvancedTab(m_control, parameters);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            CyParamExprDelegate basicExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                m_control.UpdateFormFromParams();
                parameters.GlobalEditMode = true;
            };
            CyParamExprDelegate advExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                m_controladv.UpdateFormFromParams();
                parameters.GlobalEditMode = true;
            };
            editor.AddCustomPage(Resources.ConfigureTabDisplayName, m_control,
                                                   new CyParamExprDelegate(basicExprDelegate), CONFIGURE_TAB_NAME);
            editor.AddCustomPage(Resources.AdvancedTabDisplayName, m_controladv,
                                                   new CyParamExprDelegate(advExprDelegate), ADVANCED_TAB_NAME);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(m_control.UpdateClock));

            m_control.UpdateFormFromParams();
            m_controladv.UpdateFormFromParams();
            parameters.GlobalEditMode = true;

            DialogResult result = editor.ShowDialog();
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

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyCustErr err = VerifyImplementation(args.InstQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        CyCustErr VerifyImplementation(ICyInstQuery_v1 instQuery)
        {
            if (instQuery.DeviceQuery.IsPSoC4)
            {
                bool fixedFunction;
                bool.TryParse(instQuery.GetCommittedParam(CyParamNames.FIXED_FUNCTION).Expr, out fixedFunction);

                if (fixedFunction)
                    return new CyCustErr(Resources.ImplementationDrcError);
            }
            return CyCustErr.OK;
        }
        #endregion
    }
}
