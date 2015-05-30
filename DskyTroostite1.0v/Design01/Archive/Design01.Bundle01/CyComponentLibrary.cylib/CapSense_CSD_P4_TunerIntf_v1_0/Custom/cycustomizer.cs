/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace CapSense_CSD_P4_TunerIntf_v1_0
{
    public class CyCustomizer : ICyAPICustomize_v1, ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public System.Windows.Forms.DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            parameters.m_term = termQuery;
            parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.m_editor = editor;

            #region Create tab pages

            CyI2CTab ezI2CTab = new CyI2CTab(parameters);
            #endregion

            #region Interaction between expression view and custom view

            CyParamExprDelegate ezI2CDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                ezI2CTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };
            #endregion

            #region Add tabs to the customizer
            editor.AddCustomPage(Resources.EZI2CBasicTabDisplayName, ezI2CTab, ezI2CDataChanged, ezI2CTab.TabName);

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            #endregion

            // Update all tabs

            ezI2CTab.UpdateUI();

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(parameters.UpdateDesigns);

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

        #region ICyAPICustomize_v1 members

        #region API Customizer File Constants and Variables
        const string EZBUF_I2C_FILE_PATTERN = "SCB_EZBUF_I2C";
        const string EZBUF_SPI_FILE_PATTERN = "SCB_EZBUF_SPI";
        const string EZBUF_FILE_PATTERN = "SCB_EZBUF_";
        const string UART_PATTERN = "SCB_UART";
        const string SPI_PATTERN = "SCB_SPI";
        const string SPI_UART_PATTERN = "SCB_SPI_UART";

        const string I2C_SLAVE_NAME = "SCB_I2C_SLAVE.c";
        const string I2C_MASTER_NAME = "SCB_I2C_MASTER.c";
        const string SCB_PINS_NAME = "SCB_PINS.h";
        const string SPI_INTERRUPTS_FILE_PATTERN = "SCB_SPI_UART_INT";


        List<CyAPICustomizer> m_ezBufFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_spiFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_uartFiles = new List<CyAPICustomizer>();
        #endregion

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> apiFiles = new List<CyAPICustomizer>(apis);

            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            CyParameters parameters = new CyParameters(query);
            if (apiFiles.Count > 0)
                paramDict = apiFiles[0].MacroDictionary;


            // Add #include
            StringBuilder builderInclude = new StringBuilder();
            string instName = query.GetCommittedParam("INSTANCE_NAME").Value;
            switch (parameters.SCBMode)
            {
                case CyESCBMode.EZBUF_I2C:
                case CyESCBMode.EZBUF_SPI:
                    for (int i = 0; i < m_ezBufFiles.Count; i++)
                    {
                        if (m_ezBufFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_ezBufFiles[i].OutputName));
                        }
                    }
                    break;
                default:
                    break;
            }
            paramDict.Add("IncludeDefines", builderInclude.ToString());


            // Replace macro dictionaries with paramDict
            foreach (CyAPICustomizer file in apiFiles)
            {
                file.MacroDictionary = paramDict;
            }

            return apiFiles;
        }

        private static string AddIncludeStr(string name)
        {
            return String.Format("#include \"{0}\"", name);
        }
        #endregion
    }
}
