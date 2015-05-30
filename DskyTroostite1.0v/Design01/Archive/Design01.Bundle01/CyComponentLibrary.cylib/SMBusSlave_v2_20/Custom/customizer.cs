/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Drawing;

namespace SMBusSlave_v2_20
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyDRCProvider_v1
    {
        private CyParameters m_parameters;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_parameters = new CyParameters(edit, termQuery);
            m_parameters.m_inst = edit;
            m_parameters.m_globalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(m_parameters, termQuery);
            CyPmBusCmdsTab pmBusCmdsTab = new CyPmBusCmdsTab(m_parameters, editor);
            CyCustomCmdsTab customCmdsTab = new CyCustomCmdsTab(m_parameters, edit.DesignQuery.ApplicationType);
            CyI2cConfigTab i2cConfTab = new CyI2cConfigTab(m_parameters);

            CyParamExprDelegate generalDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                generalTab.UpdateUI();
            };
            CyParamExprDelegate i2CDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                i2cConfTab.UpdateUI();
            };

            // Add tabs to the customizer 
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, generalDataChanged, generalTab.TabName);
            editor.AddCustomPage(Resources.PMBusCmdsTabDisplayName, pmBusCmdsTab, null, pmBusCmdsTab.TabName);
            pmBusCmdsTab.SetPMBusCmdsTabVisibility(m_parameters.Mode);
            editor.AddCustomPage(Resources.CustomCmdsTabDisplayName, customCmdsTab, null, customCmdsTab.TabName);
            editor.AddCustomPage(Resources.I2cConfTabDisplayName, i2cConfTab, i2CDataChanged, i2cConfTab.TabName);

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(m_parameters.UpdateClock));

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            editor.UseBigEditor = true;

            generalTab.UpdateUI();
            i2cConfTab.UpdateUI();

            m_parameters.m_globalEditMode = true;

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

        #region ICyAPICustomize_v1 Members

        #region Defining constants
        private const string UINT8_TYPE = "uint8";
        private const string UINT16_TYPE = "uint16";
        private const string SPACE = " ";
        private const string TAB = "    ";
        private const string TAB_2 = TAB + TAB;
        private const string TAB_3 = TAB + TAB + TAB;
        private const string TAB_4 = TAB + TAB + TAB + TAB;
        private const string TAB_5 = TAB + TAB + TAB + TAB + TAB;
        private const string LOGIC_OR = " | ";
        private const string UINT8_TYPE_SPACE = UINT8_TYPE + SPACE;
        private const string UINT16_TYPE_SPACE = UINT16_TYPE + SPACE;
        private const string STRUCT_NAME = "REGS";
        private static readonly string NEW_LINE = Environment.NewLine;
        #endregion

        #region Private types
        private enum CyEFieldType
        {
            UInt8Type,
            UInt16Type
        }

        private struct CyStructField
        {
            public CyEFieldType m_fieldType;
            public int m_dim1;
            public int m_dim2;
        }
        #endregion

        #region Declaring private variables
        private string m_instName;
        private bool m_isPSoC3;
        // These arrays store information about structure elements size. Arrays are used to ensure 
        // that initializing is consistent with the sizes.
        // If element is not array [index, 0] && [index, 1] equal to 0
        // If element is one dimentional array [index, 0] equals to its size && [index, 1] equal to 0
        // If element is two dimentional array [index, 0] && [index, 1] equal to the array size respectively
        private CyStructField[] m_pmBusStructFields;
        private CyStructField[] m_smBusStructFields;
        private enum CyArrayType { NotArray, OneDimArray, TwoDimArray };
        // These variables indicate whether generate Read/Write functios prototype and implementation
        private bool m_createReadByteFunction = false;
        private bool m_createReadWordFunction = false;
        private bool m_createReadBlockFunction = false;
        private bool m_createWriteByteFunction = false;
        private bool m_createWriteWordFunction = false;
        private bool m_createWriteBlockFunction = false;
        private bool m_createPageOffsetHandler = false;
        #endregion

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            m_parameters = new CyParameters(query);
            m_instName = query.InstanceName;
            m_isPSoC3 = query.DeviceQuery.IsPSoC3;
            m_pmBusStructFields = new CyStructField[m_parameters.PmBusTable.Count];
            m_smBusStructFields = new CyStructField[m_parameters.CustomTable.Count];

            List<CyArrayType> pmBusGenerateAsArray = new List<CyArrayType>();
            List<CyArrayType> customGenerateAsArray = new List<CyArrayType>();
            List<CyArrayType> tempArray = new List<CyArrayType>();

            // Generate structure
            StringBuilder regStructure = new StringBuilder();
            if (query.DeviceQuery.IsPSoC5)
            {
                regStructure.AppendLine("#if defined (__ICCARM__)");
                regStructure.AppendLine("    typedef __packed struct");
                regStructure.AppendLine("#else");
                regStructure.AppendLine("    typedef struct __attribute__ ((packed))");
                regStructure.AppendLine("#endif /* (__ICCARM__) */");
            }
            else
            {
                regStructure.AppendLine("typedef struct");
            }

            regStructure.AppendLine("{");
            regStructure.AppendLine("    uint32 SMBUS_REGS_SIG;");

            string varStructure = string.Empty;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    regStructure.Append(GetStructureField(null, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, i, ref pmBusGenerateAsArray, ref m_pmBusStructFields));

                    varStructure += GetStructureField(m_instName, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, i, ref tempArray, ref m_pmBusStructFields);
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                regStructure.Append(GetStructureField(null,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name,
                    m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type,
                    i, ref customGenerateAsArray, ref m_smBusStructFields));

                varStructure += GetStructureField(m_instName,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name,
                    m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type,
                    i, ref tempArray, ref m_smBusStructFields);
            }
            regStructure.AppendLine("    uint16 FLASH_CRC;");
            regStructure.Append("} " + m_instName + "_" + STRUCT_NAME + ";");

            // Generate NUM_COMMANDS
            int numCommands = 0;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    if (m_parameters.PmBusTable[i].m_enable)
                        numCommands++;
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_enable)
                    numCommands++;
            }

            // Generate command codes defines
            string strCmdsDefines = string.Empty;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    if (m_parameters.PmBusTable[i].m_enable)
                        strCmdsDefines += GetCmdDefine(m_instName, m_parameters.PmBusTable[i].Name,
                            m_parameters.PmBusTable[i].m_code);
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_enable)
                    strCmdsDefines += GetCmdDefine(m_instName, m_parameters.CustomTable[i].m_name,
                        m_parameters.CustomTable[i].m_code);
            }

            // Generate CMD_TABLE_ENTRY array
            string strCmdTableEntryArray = "volatile " + m_instName + "_CMD_TABLE_ENTRY " + m_instName +
                "_commands[] = {" + NEW_LINE;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    string cmdPropStr = GetCmdTableEntryElement(m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].Type, m_parameters.PmBusTable[i].WriteConfig,
                        m_parameters.PmBusTable[i].ReadConfig, m_parameters.PmBusTable[i].m_paged,
                        m_parameters.PmBusTable[i].m_format, pmBusGenerateAsArray[i]);

                    strCmdTableEntryArray += cmdPropStr;
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                string cmdPropStr = GetCmdTableEntryElement(m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_name, m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_type, m_parameters.CustomTable[i].m_writeConfig,
                    m_parameters.CustomTable[i].m_readConfig, m_parameters.CustomTable[i].m_paged,
                    m_parameters.CustomTable[i].m_format, customGenerateAsArray[i]);
                strCmdTableEntryArray += cmdPropStr;
            }
            if (strCmdTableEntryArray.LastIndexOf(",") > 0)
                strCmdTableEntryArray = strCmdTableEntryArray.Remove(strCmdTableEntryArray.LastIndexOf(",")) +
                    NEW_LINE + "};";

            // Genrate Read/Write Handler cases
            string strWriteCases = string.Empty;
            string strReadCases = string.Empty;
            string strCustomWriteCases = string.Empty;
            string strCustomReadCases = string.Empty;

            GenerateReadWriteHandlerCases(ref strWriteCases, ref strReadCases);

            // Generate NULL struct
            string strNullStructure = "= {" + NEW_LINE +
                "    // SMBUS_REGS_SIG (Do not change!)" + NEW_LINE +
                TAB + "0x000055AAu,";

            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    strNullStructure += GetNullStructureField(i, m_parameters.PagedCommands,
                        m_parameters.PmBusTable[i].Name, m_parameters.PmBusTable[i].Size,
                        m_parameters.PmBusTable[i].m_paged, m_parameters.PmBusTable[i].m_enable,
                        m_parameters.PmBusTable[i].Type, m_pmBusStructFields);
                }
            }
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                strNullStructure += GetNullStructureField(i,
                    m_parameters.CustomTable[i].m_numPages.HasValue ?
                        m_parameters.CustomTable[i].m_numPages.Value : m_parameters.PagedCommands,
                    m_parameters.CustomTable[i].m_name, m_parameters.CustomTable[i].m_size,
                    m_parameters.CustomTable[i].m_paged, m_parameters.CustomTable[i].m_enable,
                    m_parameters.CustomTable[i].m_type, m_smBusStructFields);
            }
            strNullStructure += NEW_LINE + TAB + "// FLASH_CRC" + NEW_LINE + TAB + "0x0000u" + NEW_LINE
                + "}";

            // Generate cmdType array, which indicate whether command is of BLOCK or NON-BLOCK type
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(String.Format("static const uint8 CYCODE {0}_cmdType[] = {{", m_instName));
            bool isArrayEmpty = true;
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                foreach (CyPMBusTableRow item in m_parameters.PmBusTable)
                {
                    if (item.m_enable)
                    {
                        sb.AppendLine(GetCommandType(item.Size.Value, item.Type));
                        isArrayEmpty = false;
                    }
                }
            }
            foreach (CyCustomTableRow item in m_parameters.CustomTable)
            {
                if (item.m_enable)
                {
                    sb.AppendLine(GetCommandType(item.m_size.Value, item.m_type));
                    isArrayEmpty = false;
                }
            }
            if (isArrayEmpty)
            {
                sb.Length = sb.Length - 2; // remove last \r\n characters
                sb.AppendLine(" 0");       // initialize array with 0
            }
            else
            {
                sb.Length = sb.Length - 4; // remove last , \r\n characters
                sb.AppendLine();           // add new line since it was removed during erasing comma
            }
            sb.AppendLine("};");
            paramDict.Add("CmdTypeArray", RemoveLastNewLines(sb.ToString()));

            // Generate Read/Write functions prototypes
            sb.Length = 0; // clear and use StringBuilder again
            if (m_createReadByteFunction)
                sb.AppendFormat("static void {0}_ReadByte(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createReadWordFunction)
                sb.AppendFormat("static void {0}_ReadWord(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createReadBlockFunction)
                sb.AppendFormat("static void {0}_ReadBlock(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createWriteByteFunction)
                sb.AppendFormat("static void {0}_WriteByte(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createWriteWordFunction)
                sb.AppendFormat("static void {0}_WriteWord(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createWriteBlockFunction)
                sb.AppendFormat("static void {0}_WriteBlock(void) CYREENTRANT;{1}", m_instName, NEW_LINE);
            if (m_createPageOffsetHandler)
                sb.AppendFormat("static void {0}_PageOffsetHandler(uint8 maxPage) CYREENTRANT;", m_instName);
            paramDict.Add("ReadWriteFunctionsPrototypes", RemoveLastNewLines(sb.ToString()));

            // Generate Read/Write functions implementation
            sb.Length = 0;
            // Read functions
            if (m_createReadByteFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_ReadByte{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies one byte of data to I2C buffer.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_ReadByte(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendFormat("    {0}_buffer[0u] = {0}_cmdDataPtr[{0}_pageOffset];{1}", m_instName, NEW_LINE);
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            if (m_createReadWordFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_ReadWord{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies two bytes of data to I2C buffer.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_ReadWord(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendLine("    #if(CY_PSOC3)");
                sb.AppendFormat("        {0}_buffer[0u] = {0}_cmdDataPtr[{0}_pageOffset + 1u];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("        {0}_buffer[1u] = {0}_cmdDataPtr[{0}_pageOffset];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    #else");
                sb.AppendFormat("        {0}_buffer[0u] = {0}_cmdDataPtr[{0}_pageOffset];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("        {0}_buffer[1u] = {0}_cmdDataPtr[{0}_pageOffset + 1u];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    #endif /*(CY_PSOC3) */");
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            if (m_createReadBlockFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_ReadBlock{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies a block of data to I2C buffer.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_ReadBlock(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendLine("    uint8 i;");
                sb.AppendLine();
                sb.AppendFormat("    for(i = 0u; i < {0}_bufferSize; i++){1}", m_instName, NEW_LINE);
                sb.AppendLine("    {");
                sb.AppendFormat("        {0}_buffer[i] = {0}_cmdDataPtr[{0}_pageOffset + i];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    }");
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            // Write functions
            if (m_createWriteByteFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_WriteByte{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies one byte of data from I2C buffer to register store.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_WriteByte(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendFormat("    {0}_cmdDataPtr[{0}_pageOffset] = {0}_buffer[0u];{1}", m_instName, NEW_LINE);
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            if (m_createWriteWordFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_WriteWord{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies two bytes of data from I2C buffer to register store.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_WriteWord(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendLine("    #if(CY_PSOC3)");
                sb.AppendFormat("        {0}_cmdDataPtr[{0}_pageOffset + 1u] = {0}_buffer[0u];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("        {0}_cmdDataPtr[{0}_pageOffset] = {0}_buffer[1u];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    #else");
                sb.AppendFormat("        {0}_cmdDataPtr[{0}_pageOffset] = {0}_buffer[0u];{1}", m_instName, NEW_LINE);
                sb.AppendFormat("        {0}_cmdDataPtr[{0}_pageOffset + 1u] = {0}_buffer[1u];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    #endif /*(CY_PSOC3) */");
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            if (m_createWriteBlockFunction)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_WriteBlock{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Copies one block of data from I2C buffer to register store.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_WriteBlock(void) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendLine("    uint8 i;");
                sb.AppendLine();
                sb.AppendFormat("    for(i = 0u; i < {0}_bufferSize; i++){1}", m_instName, NEW_LINE);
                sb.AppendLine("    {");
                sb.AppendFormat("        {0}_cmdDataPtr[{0}_pageOffset + i] = {0}_buffer[i];{1}", m_instName, NEW_LINE);
                sb.AppendLine("    }");
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            if (m_createPageOffsetHandler)
            {
                sb.AppendLine("/*******************************************************************************");
                sb.AppendFormat("* Function Name: {0}_PageOffsetHandler{1}", m_instName, NEW_LINE);
                sb.AppendLine("********************************************************************************");
                sb.AppendLine("*");
                sb.AppendLine("* Summary:");
                sb.AppendLine("*  Verifies if current page is less then the maxPage(maximum page for specific ");
                sb.AppendLine("*  command), to prevent register store from possible corrutption. If current");
                sb.AppendLine("*  page is greater that maxPage the offset will be calculate to point to first ");
                sb.AppendLine("*  page of the command.");
                sb.AppendLine("*");
                sb.AppendLine("* Parameters:");
                sb.AppendLine("*  maxPage - Maximum page umber for command.");
                sb.AppendLine("*");
                sb.AppendLine("* Return:");
                sb.AppendLine("*  None");
                sb.AppendLine("*");
                sb.AppendLine("*******************************************************************************/");
                sb.AppendFormat("static void {0}_PageOffsetHandler(uint8 maxPage) CYREENTRANT{1}", m_instName, NEW_LINE);
                sb.AppendLine("{");
                sb.AppendFormat("    if(maxPage > {0}_cmdPage){1}", m_instName, NEW_LINE);
                sb.AppendLine("    {");
                sb.AppendFormat("        {0}_pageOffset = {0}_bufferSize * {0}_cmdPage;{1}", m_instName, NEW_LINE);
                sb.AppendLine("    }");
                sb.AppendLine("    else");
                sb.AppendLine("    {");
                sb.AppendFormat("        {0}_pageOffset = 0u;{1}", m_instName, NEW_LINE);
                sb.AppendLine("    }");
                sb.AppendLine("}");
                sb.AppendLine();
                sb.AppendLine();
            }
            paramDict.Add("ReadWriteFunctionsImplementation", RemoveLastNewLines(sb.ToString()));

            paramDict.Add("RegsStructElements", regStructure.ToString());
            paramDict.Add("StoreComponentAllVar", varStructure);
            paramDict.Add("NullStructure", strNullStructure);
            paramDict.Add("NumCommands", "(" + CyParameters.CellConvertHex(numCommands) + "u)");
            paramDict.Add("CommandsDefines", strCmdsDefines);
            paramDict.Add("CmdTableEntry", strCmdTableEntryArray);
            paramDict.Add("WriteHandlerCases", strWriteCases);
            paramDict.Add("ReadHandlerCases", strReadCases);

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }

        private string GetCommandType(byte size, CyECmdType type)
        {
            if (size > 0 && (type == CyECmdType.BlockProcessCall || type == CyECmdType.ReadWriteBlock))
            {
                return String.Format("    {0}_BLOCK_CMD, ", m_instName);
            }
            else
            {
                return String.Format("    {0}_NON_BLOCK_CMD, ", m_instName);
            }
        }

        private void GenerateReadWriteHandlerCases(ref string writeCases, ref string readCases)
        {
            // Write handler generation
            string caseHeader = string.Empty;
            string caseFooter = TAB + TAB_3 + "break;" + NEW_LINE + NEW_LINE;

            List<List<CyCustomTableRow>> groupedCommands = GetGroupedCommandsForSwitch();
            List<List<CyCustomTableRow>> readCommands = GetReadCommands(groupedCommands);
            List<List<CyCustomTableRow>> writeCommands = GetWriteCommands(groupedCommands);

            for (int i = 0; i < writeCommands.Count; i++)
            {
                List<CyCustomTableRow> list = new List<CyCustomTableRow>(writeCommands[i]);
                for (int j = 0; j < list.Count; j++)
                {
                    CyCustomTableRow item = list[j];
                    caseHeader = GetCaseHeader(item.m_name, String.IsNullOrEmpty(writeCases));
                    if (item.m_specific)
                    {
                        if (item.m_name == CyCustomTable.PAGE)
                        {
                            writeCases += caseHeader + GetWriteHandlerCaseBody_PageCmd() + caseFooter;
                        }
                        if (item.m_name == CyCustomTable.BOOTLOAD_WRITE)
                        {
                            writeCases +=
                                GetBootloaderCmdCaseHeader(item.m_name, String.IsNullOrEmpty(writeCases)) +
                                GetWriteHandlerCaseBody_BootloadWriteCmd() +
                                GetBootloaderCmdCaseFooter();
                        }
                    }
                    else
                    {
                        switch (item.m_type)
                        {
                            case CyECmdType.ReadWriteByte:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases,
                                        GetWriteByteCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.ReadWriteWord:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases,
                                        GetWriteWordCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.ReadWriteBlock:
                                writeCases = String.Concat(writeCases, caseHeader);
                                if (j == list.Count - 1)
                                    writeCases = String.Concat(writeCases,
                                        GetWriteBlockCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.BlockProcessCall:
                                if (item.m_name == CyPMBusTable.SMBALERT_MASK)
                                {
                                    writeCases = String.Concat(writeCases, caseHeader);
                                    if (j == list.Count - 1)
                                        writeCases = String.Concat(writeCases,
                                            GetWriteHandlerCaseBody_BlockProcessCall(item.m_paged,
                                            item.m_numPages));
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            // Read handler generation
            for (int i = 0; i < readCommands.Count; i++)
            {
                List<CyCustomTableRow> list = new List<CyCustomTableRow>(readCommands[i]);
                for (int j = 0; j < list.Count; j++)
                {
                    CyCustomTableRow item = list[j];
                    caseHeader = GetCaseHeader(item.m_name, String.IsNullOrEmpty(readCases));
                    if (item.m_specific)
                    {
                        if (item.m_name == CyCustomTable.BOOTLOAD_READ)
                        {
                            readCases +=
                                GetBootloaderCmdCaseHeader(item.m_name, String.IsNullOrEmpty(readCases)) +
                                GetReadHandlerCaseBody_BootloadReadCmd() +
                                GetBootloaderCmdCaseFooter();
                        }
                        if (item.m_name == CyCustomTable.QUERY)
                        {
                            readCases += caseHeader + GetReadHandlerCaseBody_QueryCmd() + caseFooter;
                        }
                        if (item.m_name == CyCustomTable.PAGE)
                        {
                            readCases += caseHeader + GetReadHandlerCaseBody_PageCmd() + caseFooter;
                        }
                    }
                    else
                    {
                        switch (item.m_type)
                        {
                            case CyECmdType.ReadWriteByte:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases,
                                        GetReadByteCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.ReadWriteWord:

                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases,
                                        GetReadWordCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.ReadWriteBlock:

                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases,
                                        GetReadBlockCall(item.m_paged, item.m_numPages));
                                break;
                            case CyECmdType.BlockProcessCall:
                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases,
                                        GetReadBlockProcessCall(item.m_paged,
                                        item.m_numPages));
                                break;
                            case CyECmdType.ProcessCall:

                                readCases = String.Concat(readCases, caseHeader);
                                if (j == list.Count - 1)
                                    readCases = String.Concat(readCases,
                                        GetReadHandlerCaseBody_ProcessCall(item.m_paged, item.m_numPages));
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            // Remove last new lines
            writeCases = RemoveLastNewLines(writeCases);
            readCases = RemoveLastNewLines(readCases);
        }

        private static string RemoveLastNewLines(string text)
        {
            while (text.LastIndexOf(NEW_LINE) == text.Length - NEW_LINE.Length)
            {
                text = text.Remove(text.LastIndexOf(NEW_LINE), NEW_LINE.Length);
            }
            return text;
        }

        private List<List<CyCustomTableRow>> GetGroupedCommandsForSwitch()
        {
            List<List<CyCustomTableRow>> groupedCommandsList = new List<List<CyCustomTableRow>>();

            // Separate arrays to paged and not paged
            List<CyCustomTableRow> pagedArrays = new List<CyCustomTableRow>();
            List<CyCustomTableRow> notPagedArrays = new List<CyCustomTableRow>();

            // Separate PMBus commands
            // Consider PMBus commands are not paged
            if (m_parameters.Mode == CyEModeSelType.PMBUS_SLAVE)
            {
                for (int i = 0; i < m_parameters.PmBusTable.Count; i++)
                {
                    notPagedArrays.Add(new CyCustomTableRow(m_parameters.PmBusTable[i]));
                }
            }

            // Separate custom commands
            for (int i = 0; i < m_parameters.CustomTable.Count; i++)
            {
                if (m_parameters.CustomTable[i].m_paged)
                {
                    pagedArrays.Add(m_parameters.CustomTable[i]);
                }
                else
                {
                    notPagedArrays.Add(m_parameters.CustomTable[i]);
                }
            }

            // Group paged commands
            while (pagedArrays.Count > 0)
            {
                List<CyCustomTableRow> tmp = new List<CyCustomTableRow>();
                for (int i = pagedArrays.Count - 1; i >= 0; i--)
                {
                    if (pagedArrays[i].m_type == pagedArrays[0].m_type &&
                        pagedArrays[i].m_paged == pagedArrays[0].m_paged &&
                        pagedArrays[i].m_numPages == pagedArrays[0].m_numPages)
                    {
                        tmp.Add(pagedArrays[i]);
                        pagedArrays.RemoveAt(i);
                    }
                }
                groupedCommandsList.Add(tmp);
            }

            // Group not paged commands
            while (notPagedArrays.Count > 0)
            {
                List<CyCustomTableRow> tmp = new List<CyCustomTableRow>();
                for (int i = notPagedArrays.Count - 1; i >= 0; i--)
                {
                    if (notPagedArrays[i].m_type == notPagedArrays[0].m_type)
                    {
                        tmp.Add(notPagedArrays[i]);
                        notPagedArrays.RemoveAt(i);
                    }
                }
                groupedCommandsList.Add(tmp);
            }

            // Find specific commands and move them to different group
            List<CyCustomTableRow> specificCommands = new List<CyCustomTableRow>();

            for (int i = groupedCommandsList.Count - 1; i >= 0; i--)
            {
                for (int j = groupedCommandsList[i].Count - 1; j >= 0; j--)
                {
                    CyCustomTableRow item = groupedCommandsList[i][j];
                    if (item.m_specific)
                    {
                        specificCommands.Add(item);
                        groupedCommandsList[i].RemoveAt(j);
                        if (groupedCommandsList[i].Count == 0)
                        {
                            groupedCommandsList.RemoveAt(i);
                        }
                    }
                }
            }
            // Insert group with specific commands at the begginning
            if (specificCommands.Count > 0)
            {
                groupedCommandsList.Insert(0, specificCommands);
            }

            //Erase disabled commands from groups
            int ii = 0;
            while (groupedCommandsList.Count > ii)
            {
                int jj = 0;
                while (groupedCommandsList[ii].Count > jj)
                {
                    if (groupedCommandsList[ii][jj].m_enable == false)
                    {
                        groupedCommandsList[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (groupedCommandsList[ii].Count == 0)
                    groupedCommandsList.RemoveAt(ii);
                else
                    ii++;
            }

            return groupedCommandsList;
        }

        private List<List<CyCustomTableRow>> GetDeepCopy(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> copy = new List<List<CyCustomTableRow>>();
            int copyIndex = 0;
            for (int i = 0; i < groupedCommands.Count; i++)
            {
                copy.Add(new List<CyCustomTableRow>());

                for (int j = 0; j < groupedCommands[i].Count; j++)
                {
                    copy[copyIndex].Add(groupedCommands[i][j]);
                }
                copyIndex++;
            }
            return copy;
        }

        private List<List<CyCustomTableRow>> GetReadCommands(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> readCommands = GetDeepCopy(groupedCommands);
            int ii = 0;
            while (readCommands.Count > ii)
            {
                int jj = 0;
                while (readCommands[ii].Count > jj)
                {
                    if (readCommands[ii][jj].m_readConfig == CyEReadWriteConfigType.None)
                    {
                        readCommands[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (readCommands[ii].Count == 0)
                    readCommands.RemoveAt(ii);
                else
                    ii++;
            }

            return readCommands;
        }

        private List<List<CyCustomTableRow>> GetWriteCommands(List<List<CyCustomTableRow>> groupedCommands)
        {
            List<List<CyCustomTableRow>> writeCommands = GetDeepCopy(groupedCommands);
            int ii = 0;
            while (writeCommands.Count > ii)
            {
                int jj = 0;
                while (writeCommands[ii].Count > jj)
                {
                    if (writeCommands[ii][jj].m_writeConfig == CyEReadWriteConfigType.None)
                    {
                        writeCommands[ii].RemoveAt(jj);
                    }
                    else
                        jj++;
                }

                if (writeCommands[ii].Count == 0)
                    writeCommands.RemoveAt(ii);
                else
                    ii++;
            }

            return writeCommands;
        }

        #region Write handler functions
        private string GetCaseHeader(string name, bool isFirstLine)
        {
            string caseLine = String.Concat("case ", m_instName, "_", name, ":", NEW_LINE);
            if (isFirstLine == false)
                caseLine = String.Concat(TAB_3, caseLine);
            return caseLine;
        }
        private string GetBootloaderCmdCaseHeader(string name, bool isFirstLine)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("{0}#if ({1}_IS_BOOTLOADER_OR_LOADABLE()){2}", isFirstLine ? "" : TAB_3, m_instName, NEW_LINE);
            sb.AppendFormat("{0}case {1}_{2}:{3}", TAB_3, m_instName, name, NEW_LINE);
            return sb.ToString();
        }

        private string GetBootloaderCmdCaseFooter()
        {
            return String.Format("{0}break;{2}{3}#endif /* ({1}_IS_BOOTLOADER_OR_LOADABLE()) */{2}", TAB_4, m_instName, NEW_LINE, TAB_3);
        }

        private string GetWriteHandlerCaseBody_PageCmd()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("{0}/* PAGE should only be stored if it is not greater then MAX PAGES{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}* or equal to ALL PAGES.{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}*/{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}if(({2}_buffer[0u] < {2}_MAX_PAGES) ||{1}", TAB_4, NEW_LINE, m_instName);
            sb.AppendFormat("{0}        ({2}_CMD_ALL_PAGES == {2}_buffer[0u])){1}", TAB_4, NEW_LINE, m_instName);
            sb.AppendFormat("{0}{{{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}    /* First byte in the buffer is a new page value */{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}    {2}_cmdPage = {2}_buffer[0u];{1}", TAB_4, NEW_LINE, m_instName);
            sb.AppendLine();
            sb.AppendFormat("{0}    /* Copy new page value into Operating Memory Register Store.{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}    * {2}_cmdDataPtr should point to correct location.{1}", TAB_4, NEW_LINE, m_instName);
            sb.AppendFormat("{0}    */{1}", TAB_4, NEW_LINE);
            sb.AppendFormat("{0}    {2}_cmdDataPtr[0u] = {2}_buffer[0u];{1}", TAB_4, NEW_LINE, m_instName);
            sb.AppendFormat("{0}}}{1}", TAB_4, NEW_LINE);
            return sb.ToString();
        }

        private string GetWriteHandlerCaseBody_BootloadWriteCmd()
        {
            return TAB_4 + "byteCount = " + m_instName + "_buffer[0u];" + NEW_LINE + NEW_LINE +
                TAB_4 + "if (" + m_instName + "_bufferIndex == (byteCount + 1u))" + NEW_LINE +
                TAB_4 + "{" + NEW_LINE +
                TAB_5 + "for (i = 0u; i < byteCount; i++)" + NEW_LINE +
                TAB_5 + "{" + NEW_LINE +
                TAB_5 + TAB + m_instName + "_btldrWriteBuf[i] = " + m_instName + "_buffer[i + 1u];" + NEW_LINE +
                TAB_5 + "}" + NEW_LINE +
                TAB_5 + m_instName + "_btldrStatus |= " + m_instName + "_BTLDR_WR_CMPT;" + NEW_LINE +
                TAB_5 + m_instName + "_btldrWrBufByteCount = byteCount;" + NEW_LINE +
                TAB_4 + "}" + NEW_LINE;
        }

        private string GetPageOffsetHandlerCall(byte? numPages)
        {
            m_createPageOffsetHandler = true;
            return String.Format("{3}{0}_PageOffsetHandler({1});{2}", m_instName, numPages.Value, NEW_LINE, TAB_4);
        }

        private string GetWriteByteCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createWriteByteFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_WriteByte();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }

        private string GetWriteWordCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createWriteWordFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_WriteWord();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }

        private string GetWriteHandlerCaseBody_BlockProcessCall(bool paged, byte? numPages)
        {
            return GetWriteWordCall(paged, numPages);
        }

        private string GetWriteBlockCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createWriteBlockFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_WriteBlock();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }
        #endregion

        #region Read handler functions
        private string GetReadHandlerCaseBody_PageCmd()
        {
            return TAB_4 + "/* Read back page value from Operating Memory Register Store." + NEW_LINE +
                TAB_4 + "* `$INSTANCE_NAME`_cmdDataPtr should point to correct location." + NEW_LINE +
                TAB_4 + "*/" + NEW_LINE +
                TAB_4 + m_instName + "_buffer[0u] = " + m_instName + "_cmdDataPtr[0u];" + NEW_LINE;
        }

        private string GetReadHandlerCaseBody_QueryCmd()
        {
            return TAB_4 + "/* Search for the command */" + NEW_LINE +
                TAB_4 + "tmpCmd = " + m_instName + "_SearchCommand(" + m_instName + "_buffer[1u]);" + NEW_LINE +
                NEW_LINE +
                TAB_4 + "if(" + m_instName + "_CMD_UNDEFINED != tmpCmd)" + NEW_LINE +
                TAB_4 + "{" + NEW_LINE +
                TAB_5 + "/* Update query data command code as we succeeded to find the command */" + NEW_LINE +
                TAB_5 + m_instName + "_queryCmd = " + m_instName + "_buffer[1u]" + ";" + NEW_LINE +
                NEW_LINE +
                TAB_5 + "/* Store command properties in variable to save time required for accessing" + NEW_LINE +
                TAB_5 + "* structure." + NEW_LINE +
                TAB_5 + "*/" + NEW_LINE +
                TAB_5 + "tmpProps = " + m_instName + "_commands[tmpCmd].cmdProp;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + "/* This will clear the previous QUERY data and set a flag that currently" + NEW_LINE +
                TAB_5 + "* investigated command is supported." + NEW_LINE +
                TAB_5 + "*/" + NEW_LINE +
                TAB_5 + "" + m_instName + "_queryData = " + m_instName + "_QRY_CMD_SUPPORTED;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + "if(0u != (tmpProps & " + m_instName + "_CMD_PROP_WRITE_MASK))" + NEW_LINE +
                TAB_5 + "{" + NEW_LINE +
                TAB_5 + TAB + m_instName + "_queryData |= " + m_instName + "_QRY_CMD_WR_SUPPORTED;" + NEW_LINE +
                TAB_5 + "}" + NEW_LINE +
                NEW_LINE +
                TAB_5 + "if(0u != (tmpProps & " + m_instName + "_CMD_PROP_READ_MASK))" + NEW_LINE +
                TAB_5 + "{" + NEW_LINE +
                TAB_5 + TAB + m_instName + "_queryData |= " + m_instName + "_QRY_CMD_RD_SUPPORTED;" + NEW_LINE +
                TAB_5 + "}" + NEW_LINE +
                TAB_5 + "/* Update command properties based on the data from customizer */" + NEW_LINE +
                TAB_5 + "switch (tmpProps & " + m_instName + "_CMD_PROP_FORMAT_MASK)" + NEW_LINE +
                TAB_5 + "{" + NEW_LINE +
                TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_NON_NUMERIC:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_NON_NUMERIC;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_LINEAR:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_LINEAR;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_SIGNED:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_SIGNED16;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_DIRECT:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_DIRECT;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_UNSIGNED:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_UNSIGNED8;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                NEW_LINE + TAB_5 + TAB + "case " + m_instName + "_CMD_PROP_FORMAT_VID_MODE:" + NEW_LINE +
                TAB_5 + TAB_2 + m_instName + "_queryData |= " + m_instName + "_QRY_FORMAT_VID_MODE;" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE +
                NEW_LINE +
                TAB_5 + TAB + "default:" + NEW_LINE +
                TAB_5 + TAB_2 + "/* Should never be here */" + NEW_LINE +
                TAB_5 + TAB_2 + "break;" + NEW_LINE + TAB_5 + "}" + NEW_LINE +
                NEW_LINE +
                TAB_5 + "/* Copy command code investigated into Operating Memory Register Store." + NEW_LINE +
                TAB_5 + "* `$INSTANCE_NAME`_cmdDataPtr should point to correct location." + NEW_LINE +
                TAB_5 + "*/" + NEW_LINE +
                TAB_5 + "" + m_instName + "_cmdDataPtr[0u] = " + m_instName + "_buffer[0u];" + NEW_LINE +
                TAB_5 + "" + m_instName + "_cmdDataPtr[1u] = " + m_instName + "_buffer[1u];" + NEW_LINE +
                NEW_LINE + TAB_5 + "/* Put gathered information about the command into I2C buffer" + NEW_LINE +
                TAB_5 + "* to send it to master." + NEW_LINE +
                TAB_5 + "*/" + NEW_LINE +
                TAB_5 + "" + m_instName + "_buffer[0u] = " + "1u;" + NEW_LINE +
                TAB_5 + "" + m_instName + "_buffer[1u] = " + m_instName + "_queryData;" + NEW_LINE +
                TAB_4 + "}" + NEW_LINE +
                TAB_4 + "else" + NEW_LINE +
                TAB_4 + "{" + NEW_LINE +
                TAB_5 + "/* Send zero as command isn't supported. */" + NEW_LINE +
                TAB_5 + m_instName + "_buffer[0u] = 1u;" + NEW_LINE +
                TAB_5 + m_instName + "_buffer[1u] = 0u;" + NEW_LINE +
                TAB_4 + "}" + NEW_LINE;
        }

        private string GetReadHandlerCaseBody_BootloadReadCmd()
        {
            return TAB_4 + "/* First byte of the buffer contains data size */" + NEW_LINE +
                TAB_4 + "for(i = 0u; i < " + m_instName + "_btldrRdBufByteCount; i++)" + NEW_LINE +
                TAB_4 + "{" + NEW_LINE +
                TAB_5 + m_instName + "_buffer[i] = " + m_instName + "_btldrReadBuf[i];" + NEW_LINE +
                TAB_4 + "}" + NEW_LINE + NEW_LINE +
                TAB_4 + m_instName + "_bufferSize = " + m_instName + "_btldrRdBufByteCount;" + NEW_LINE;
        }

        private string GetReadByteCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createReadByteFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_ReadByte();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }

        private string GetReadWordCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createReadWordFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_ReadWord();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }

        private string GetReadBlockCall(bool paged, byte? numPages)
        {
            string caseBody = String.Empty;
            m_createReadBlockFunction = true;
            if (paged && numPages.HasValue)
            {
                caseBody = GetPageOffsetHandlerCall(numPages);
            }
            return String.Concat(caseBody, String.Format("{2}{0}_ReadBlock();{1}{2}break;{1}{1}", m_instName, NEW_LINE, TAB_4));
        }

        private string GetReadBlockProcessCall(bool paged, byte? numPages)
        {
            return GetReadBlockCall(paged, numPages);
        }

        private string GetReadHandlerCaseBody_ProcessCall(bool paged, byte? numPages)
        {
            return GetReadWordCall(paged, numPages);
        }
        #endregion

        private string GetCmdTableEntryElement(bool enable, string name, byte? size, CyECmdType type,
            CyEReadWriteConfigType writeConfig, CyEReadWriteConfigType readConfig, bool paged, CyEFormatType format,
            CyArrayType generateAsArray)
        {
            string result = string.Empty;
            if (enable)
            {
                if (type == CyECmdType.BlockProcessCall || type == CyECmdType.ReadWriteBlock)
                    size++;
                bool isCmdBootloader = CyCustomTable.IsCmdBootloader(name);

                string cast = (type == CyECmdType.ReadWriteWord) ? "(uint8*) " : string.Empty;
                string arrayZeroElement = string.Empty;
                switch (generateAsArray)
                {
                    case CyArrayType.OneDimArray:
                        arrayZeroElement = "[0u]";
                        break;
                    case CyArrayType.TwoDimArray:
                        arrayZeroElement = "[0u][0u]";
                        break;
                    default:
                        break;
                }

                result += TAB + "{" + NEW_LINE + TAB_2 + m_instName + "_" + name + "," +
                    NEW_LINE + TAB_2 + (isCmdBootloader ? "0x80" : CyParameters.CellConvertHex(size)) + "u," +
                    NEW_LINE + TAB_2 + ((size == 0) ? "NULL" : (cast + "&" + m_instName +
                    (isCmdBootloader ? "_btldrWriteBuf[0u]" : "_regs" + "." + name + arrayZeroElement))) + "," +
                    NEW_LINE;

                string cmdPropStr = string.Empty;
                byte cmdPropValue = 0;
                switch (writeConfig)
                {
                    case CyEReadWriteConfigType.None:
                        cmdPropValue += 0x00;
                        break;
                    case CyEReadWriteConfigType.Manual:
                        cmdPropStr += m_instName + "_CMD_PROP_WRITE_MANUAL" + LOGIC_OR;
                        cmdPropValue += 0x01;
                        break;
                    case CyEReadWriteConfigType.Auto:
                        cmdPropStr += m_instName + "_CMD_PROP_WRITE_AUTO" + LOGIC_OR;
                        cmdPropValue += 0x02;
                        break;
                    default:
                        break;
                }
                switch (readConfig)
                {
                    case CyEReadWriteConfigType.None:
                        cmdPropValue += 0x00;
                        break;
                    case CyEReadWriteConfigType.Manual:
                        cmdPropStr += m_instName + "_CMD_PROP_READ_MANUAL" + LOGIC_OR;
                        cmdPropValue += 0x04;
                        break;
                    case CyEReadWriteConfigType.Auto:
                        cmdPropStr += m_instName + "_CMD_PROP_READ_AUTO" + LOGIC_OR;
                        cmdPropValue += 0x06;
                        break;
                    default:
                        break;
                }
                if (paged)
                {
                    cmdPropStr += m_instName + "_CMD_PROP_PAGE_INDEXED" + LOGIC_OR;
                    cmdPropValue += 0x10;
                }
                else
                {
                    cmdPropValue += 0x00;
                }
                switch (format)
                {
                    case CyEFormatType.NonNumeric:
                        cmdPropValue += 0x00;
                        break;
                    case CyEFormatType.Linear:
                        cmdPropStr += m_instName + "_CMD_PROP_FORMAT_LINEAR" + LOGIC_OR;
                        cmdPropValue += 0x10;
                        break;
                    case CyEFormatType.Signed:
                        cmdPropStr += m_instName + "_CMD_PROP_FORMAT_SIGNED" + LOGIC_OR;
                        cmdPropValue += 0x20;
                        break;
                    case CyEFormatType.Direct:
                        cmdPropStr += m_instName + "_CMD_PROP_FORMAT_DIRECT" + LOGIC_OR;
                        cmdPropValue += 0x40;
                        break;
                    case CyEFormatType.Unsigned:
                        cmdPropStr += m_instName + "_CMD_PROP_FORMAT_UNSIGNED" + LOGIC_OR;
                        cmdPropValue += 0x60;
                        break;
                    case CyEFormatType.VidMode:
                        cmdPropStr += m_instName + "_CMD_PROP_FORMAT_VID_MODE" + LOGIC_OR;
                        cmdPropValue += 0x80;
                        break;
                    default:
                        break;
                }

                if (cmdPropStr.EndsWith(LOGIC_OR))
                {
                    if (cmdPropStr.LastIndexOf(LOGIC_OR) > 0)
                        cmdPropStr = cmdPropStr.Remove(cmdPropStr.LastIndexOf(LOGIC_OR));
                }
                cmdPropStr = TAB_2 + cmdPropStr + NEW_LINE + TAB + "}," + NEW_LINE;
                if (cmdPropValue == 0)
                    cmdPropStr = "0x00";
                result += cmdPropStr;
            }
            return result;
        }

        private static string GetCmdDefine(string instanceName, string name, byte? code)
        {
            return "#define " + instanceName + "_" + name + "    (" + CyParameters.CellConvertHex(code) + "u)" +
                NEW_LINE;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="instName">Should be null for generation Reg structure and Instance name for 
        /// generation variable</param>
        /// <param name="pagedCommands"></param>
        /// <param name="name"></param>
        /// <param name="size"></param>
        /// <param name="paged"></param>
        /// <param name="enable"></param>
        /// <param name="index"></param>
        /// <param name="generateAsArray"></param>
        /// <returns></returns>
        private static string GetStructureField(string instName, byte pagedCommands, string name, byte? size,
            bool paged, bool enable, CyECmdType cmdType, int index, ref List<CyArrayType> generateAsArray,
            ref CyStructField[] structFields)
        {
            string result = string.Empty;

            string prefix8 = UINT8_TYPE_SPACE;
            string prefix16 = UINT16_TYPE_SPACE;
            string suffix = ";";
            if (instName != null)
            {
                prefix8 = string.Format("{0}_regs.", instName);
                prefix16 = prefix8;
                suffix = string.Empty;
            }

            generateAsArray.Add(new CyArrayType());
            if (enable && size != null)
            {

                switch (size)
                {
                    case 0:
                        SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, -1, -1);
                        break;
                    case 1:
                        if (name == CyCustomTable.QUERY)
                        {
                            result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                            generateAsArray[index] = CyArrayType.OneDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                        }
                        else if (cmdType == CyECmdType.ReadWriteByte)
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, 0);
                            }
                            else
                            {
                                result += prefix8 + name + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.NotArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, 0, 0);
                            }
                        }
                        else
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1).ToString() +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        result = TAB + result;
                        break;
                    case 2:
                        if (name == CyPMBusTable.SMBALERT_MASK) // SMBALERT_MASK is exception.
                        {
                            if (paged && pagedCommands > CyParamRange.PAGED_CMDS_MIN)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1).ToString() +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        else if (cmdType == CyECmdType.ReadWriteWord || cmdType == CyECmdType.ProcessCall)
                        {
                            if (paged)
                            {
                                result += prefix16 + name + "[" + pagedCommands + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt16Type, pagedCommands, 0);
                            }
                            else
                            {
                                result += prefix16 + name + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.NotArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt16Type, 0, 0);
                            }
                        }
                        else
                        {
                            if (paged)
                            {
                                result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1).ToString() +
                                    "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.TwoDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                            }
                            else
                            {
                                result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                                generateAsArray[index] = CyArrayType.OneDimArray;
                                SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                            }
                        }
                        result = TAB + result;
                        break;
                    default:
                        if (paged)
                        {
                            result += prefix8 + name + "[" + pagedCommands + "][" + (size + 1).ToString() +
                                "];" + NEW_LINE;
                            generateAsArray[index] = CyArrayType.TwoDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, pagedCommands, size.Value + 1);
                        }
                        else
                        {
                            result += prefix8 + name + "[" + (size + 1).ToString() + "]" + suffix + NEW_LINE;
                            generateAsArray[index] = CyArrayType.OneDimArray;
                            SaveStructElementSize(ref structFields, index, CyEFieldType.UInt8Type, size.Value + 1, 0);
                        }
                        result = TAB + result;
                        break;
                }
            }
            return result;
        }

        private static void SaveStructElementSize(ref CyStructField[] structFields, int index, CyEFieldType fieldType,
            int dim1, int dim2)
        {
            structFields[index].m_fieldType = fieldType;
            structFields[index].m_dim1 = dim1;
            structFields[index].m_dim2 = dim2;
        }

        private static string GetNullStructureField(int index, byte pagedCommands, string name, byte? size, bool paged,
            bool enable, CyECmdType cmdType, CyStructField[] structField)
        {
            string result = string.Empty;
            if (enable && size != null)
            {
                if (structField[index].m_dim1 == 0)
                {
                    result += NEW_LINE + TAB + "// " + name + NEW_LINE +
                        TAB + ((cmdType == CyECmdType.ReadWriteByte) ? "0x00u," : "0x0000u,");
                }
                else if (structField[index].m_dim2 == 0)
                {
                    result += NEW_LINE + TAB + "// " + name + NEW_LINE +
                              TAB + "{";
                    for (int i = 0; i < structField[index].m_dim1; i++)
                    {
                        result += ((structField[index].m_fieldType == CyEFieldType.UInt8Type) ? "0x00u, " : "0x0000u, ");
                    }
                    result = result.TrimEnd(new char[] { ',', ' ' });
                    result += "},";
                }
                else if (structField[index].m_dim1 > 0)
                {
                    result += NEW_LINE + TAB + "// " + name + NEW_LINE;
                    for (int i = 0; i < structField[index].m_dim1; i++)
                    {
                        result += ((i == 0) ? TAB + "{" : SPACE) + "{";
                        for (int j = 0; j < (structField[index].m_dim2); j++)
                        {
                            result += ((structField[index].m_fieldType == CyEFieldType.UInt8Type) ? "0x00u, " : "0x0000u, ");
                        }
                        result = result.TrimEnd(new char[] { ',', ' ' });
                        result += (i < pagedCommands - 1) ? "}," : "}},";
                    }
                }
            }
            return result;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            m_parameters = new CyParameters(args.InstQueryV1);

            if (m_parameters.CheckPmBusTableNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, string.Format(
                    Resources.DrcNullValuesError, Resources.PMBusCmdsTabDisplayName));
            }
            if (m_parameters.CheckCustomTableNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, string.Format(
                    Resources.DrcNullValuesError, Resources.CustomCmdsTabDisplayName));
            }
            if (m_parameters.CheckImplementationWithSilicon() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Resources.ImplementationWithSiliconValidator);
            }
            if (m_parameters.CheckBootloaderCommands() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.BootloadCommandNotEnabled);
            }
        }
        #endregion
    }
}
