/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;

namespace SegLCD_P4_v1_0
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        private const string PAGE_PARAM_BUILTIN = "Built-in";

        #region ICyParamEditHook_v1 Members

        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
                                                    ICyExpressMgr_v1 mgr)
        {
            CyLCDParameters parameters = new CyLCDParameters(edit);
            parameters.m_termQuery = termQuery;
            CyBasicConfiguration basicPage = new CyBasicConfiguration(parameters);
            CyHelpers helpersPage = new CyHelpers(parameters);
            CyCustomCharsEditor charsPage = new CyCustomCharsEditor(parameters);

            parameters.m_globalEditMode = true;
            CyParamExprDelegate paramCommitted = delegate { parameters.GetExprViewParams(); };
            
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_BASIC, basicPage, paramCommitted, basicPage.TabName);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_HELPERS, helpersPage, paramCommitted, 
                                 helpersPage.TabName);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_CUSTOMCHARS, charsPage, paramCommitted, 
                                 charsPage.TabName);
            editor.AddDefaultPage(Properties.Resources.PAGE_TITLE_BUILTIN, PAGE_PARAM_BUILTIN);
            
            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(parameters.UpdateClock));
            DialogResult result = editor.ShowDialog();
            return result;
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        #region ICyDRCProvider_v1 Members
        IEnumerable<CyDRCInfo_v1> ICyDRCProvider_v1.GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyLCDParameters parameters = new CyLCDParameters(args.InstQueryV1);

            // Check if clock value was changed
            if (parameters.LCDMode == CyLCDParameters.CyLCDModeType.HS)
            {
                double extClockNew =
                    CyLCDParameters.GetExternalClockInHz(args.TermQueryV1, CyLCDParameters.TERM_CLK_NAME);

                if ((extClockNew < 0) || (Math.Abs(parameters.ExternalClockHz - extClockNew) > CyLCDParameters.CLK_EPS))
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Properties.Resources.DRC_CLOCK_ERR);
                }
            }

            // Check if possible frame rate range is not empty
            string[] frameRateRange = parameters.UpdateFrameRateRange();

            if (frameRateRange.Length == 0)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, 
                    Properties.Resources.EMPTY_FRAMERATE_LIST);
            }
        }

        #endregion
    }
}
