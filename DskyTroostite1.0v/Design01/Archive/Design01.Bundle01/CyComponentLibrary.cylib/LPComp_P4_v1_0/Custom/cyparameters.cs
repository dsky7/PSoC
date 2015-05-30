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

namespace LPComp_P4_v1_0
{
    #region Component Parameters Names
    public static class CyParamNames
    {
        public const string P_HYSTERESIS = "Hysteresis";
        public const string P_SPEED = "Speed";
        public const string P_INTERRUPT = "Interrupt";
        public const string P_FILTER = "DigitalFilter";
    }
    #endregion

    #region Component Enums
    public enum CyFilterType
    {
        [Description("Disable")]
        LPC_DISABLE_DFLT,
        [Description("Enable")]
        LPC_ENABLE_DFLT
    }
    public enum CyHysteresisType
    {
        [Description("Enable")]
        LPC_ENABLE_HYST,
        [Description("Disable")]
        LPC_DISABLE_HYST
    }
    public enum CyInterruptType
    {
        [Description("Disabled")]
        LPC_INT_DISABLE,
        [Description("Rising edge")]
        LPC_INT_RISING,
        [Description("Falling edge")]
        LPC_INT_FALLING,
        [Description("Both edges")]
        LPC_INT_BOTH
    }
    public enum CySpeedType
    {
        [Description("Low Power")]
        LPC_LOW_SPEED = 2,
        [Description("Medium Power")]
        LPC_MED_SPEED = 0,
        [Description("High Power")]
        LPC_HIGH_SPEED = 1
    }
    #endregion

    public class CyParameters
    {
        public ICyInstQuery_v1 m_inst;
        public CyBasicTab m_basicTab;

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
        public CySpeedType Speed
        {
            get { return GetValue<CySpeedType>(CyParamNames.P_SPEED); }
            set { SetValue(CyParamNames.P_SPEED, value); }
        }
        public CyFilterType Filter
        {
            get { return GetValue<CyFilterType>(CyParamNames.P_FILTER); }
            set { SetValue(CyParamNames.P_FILTER, value); }
        }
        public CyInterruptType Interrupt
        {
            get { return GetValue<CyInterruptType>(CyParamNames.P_INTERRUPT); }
            set { SetValue(CyParamNames.P_INTERRUPT, value); }
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
