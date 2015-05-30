/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace OpAmp_P4_v1_0
{
    #region Component parameters names
    public class CyParamName
    {
        public const string MODE = "Mode";
        public const string OUTPUT_CURRENT = "OutputCurrent";
        public const string POWER = "Power";
        public const string COMPENSATION = "Compensation";
    }
    #endregion

    #region Component enums
    public enum CyEModeType { OPAMP, FOLLOWER }
    public enum CyEPowerType { OPAMP_LOW_POWER = 1, OPAMP_MED_POWER = 2, OPAMP_HIGH_POWER = 3 }
    public enum CyEOutputType { OPAMP_STANDARD_1MA, OPAMP_HIGH_10MA }
    public enum CyECompensationType { HighSpeed = 1, Balanced = 2, HighStability = 3 }
    #endregion

    public class CyParameters
    {
        public ICyInstEdit_v1 m_inst;
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        #region Constructor(s)
        public CyParameters(ICyInstEdit_v1 inst)
        {
            m_inst = inst;
        }
        #endregion

        #region Class properties
        public CyEModeType Mode
        {
            get
            {
                return GetValue<CyEModeType>(CyParamName.MODE);
            }
            set
            {
                SetValue(CyParamName.MODE, value);
            }
        }

        public CyEPowerType Power
        {
            get
            {
                return GetValue<CyEPowerType>(CyParamName.POWER);
            }
            set
            {
                SetValue(CyParamName.POWER, value);
            }
        }

        public CyEOutputType OutputCurrent
        {
            get
            {
                return GetValue<CyEOutputType>(CyParamName.OUTPUT_CURRENT);
            }
            set
            {
                SetValue(CyParamName.OUTPUT_CURRENT, value);
            }
        }

        public CyECompensationType Compensation
        {
            get
            {
                return GetValue<CyECompensationType>(CyParamName.COMPENSATION);
            }
            set
            {
                SetValue(CyParamName.COMPENSATION, value);
            }
        }
        #endregion

        #region Getting parameters
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

        #region Setting parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion
    }
}
