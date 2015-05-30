/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Reflection;

namespace Comp_P4_v1_0
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string P_HYSTERESIS = "Hysteresis";
        public const string P_POLARITY = "Polarity";
        public const string P_POWER = "Power";
    }
    #endregion

    #region Component Enums
    public enum CyPolarityType
    {
        [Description("Non-inverting")]
        CMP_NON_INVERTING,
        [Description("Inverting")]
        CMP_INVERTING
    }
    public enum CyHysteresisType
    {
        [Description("Disable")]
        CMP_DISABLE_HYST,
        [Description("Enable")]
        CMP_ENABLE_HYST
    }
    public enum CyPowerType
    {
        [Description("None")]
        NONE = 0, // This value is not used and was added according to the best practices
        [Description("Low Power")]
        CMP_LOW_POWER = 1,
        [Description("Medium Power")]
        CMP_MED_POWER = 2,
        [Description("High Power")]
        CMP_HIGH_POWER = 3
    }
    #endregion

    public class CyParameters
    {
        public ICyInstQuery_v1 m_inst;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
        }

        public CyParameters() { }

        #endregion

        #region Class properties
        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        public CyHysteresisType Hysteresis
        {
            get { return GetValue<CyHysteresisType>(CyParamNames.P_HYSTERESIS); }
            set { SetValue(CyParamNames.P_HYSTERESIS, value); }
        }
        public CyPowerType Power
        {
            get { return GetValue<CyPowerType>(CyParamNames.P_POWER); }
            set { SetValue(CyParamNames.P_POWER, value); }
        }
        public CyPolarityType Polarity
        {
            get { return GetValue<CyPolarityType>(CyParamNames.P_POLARITY); }
            set { SetValue(CyParamNames.P_POLARITY, value); }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
            {
                if (m_inst != null && m_inst is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 edit = m_inst as ICyInstEdit_v1;
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                        valueToSet += "u";
                    if (edit.SetParamExpr(paramName, valueToSet))
                    {
                        edit.CommitParamExprs();
                    }
                }
            }
        }
        #endregion
    }
}
