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

namespace IDAC_P4_v1_0
{
    #region Component parameters names
    public class CyParamName
    {
        public const string POLARITY = "Polarity";
        public const string IDAC_VALUE = "IDACValue";
        public const string RESOLUTION = "Resolution";
        public const string IDAC_RANGE = "IDACRange";
    }
    #endregion

    #region Parameters ranges
    public class CyParamRange
    {
        public const double LOW_RANGE_COEFF = 1.2;
        public const double HIGH_RANGE_COEFF = 2.4;

        public const UInt16 IDAC_CURR_MIN = 0;
        public const double IDAC_CURR_LR_7_BIT_MAX = 152.4;
        public const double IDAC_CURR_HR_7_BIT_MAX = 304.8;
        public const double IDAC_CURR_LR_8_BIT_MAX = 306;
        public const double IDAC_CURR_HR_8_BIT_MAX = 612;

        public const UInt16 IDAC_CONV_MIN = 0;
        public const UInt16 IDAC_CONV_7_BIT_MAX = 127;
        public const UInt16 IDAC_CONV_8_BIT_MAX = 255;

        public const byte MAX_7BIT_VALUE = 127;
        public const byte MAX_8BIT_VALUE = 255;

        public const byte RESOLUTION_7 = 7;
        public const byte RESOLUTION_8 = 8;
    }
    #endregion

    #region Component enums
    public enum CyEPolarityType { Source, Sink }
    public enum CyEIDACRangeType { LowRange, HighRange }
    #endregion

    public class CyParameters
    {
        public ICyInstEdit_v1 m_inst;
        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediately overwrite parameters with the same values.
        public bool m_globalEditMode = false;

        #region Constructor(s)
        public CyParameters(ICyInstEdit_v1 inst)
        {
            m_inst = inst;
        }
        #endregion

        #region Class properties
        public CyEPolarityType Polarity
        {
            get
            {
                return GetValue<CyEPolarityType>(CyParamName.POLARITY);
            }
            set
            {
                SetValue(CyParamName.POLARITY, value);
            }
        }

        public byte IDACValue
        {
            get
            {
                return GetValue<byte>(CyParamName.IDAC_VALUE);
            }
            set
            {
                SetValue(CyParamName.IDAC_VALUE, value);
            }
        }

        public byte Resolution
        {
            get
            {
                return GetValue<byte>(CyParamName.RESOLUTION);
            }
            set
            {
                SetValue(CyParamName.RESOLUTION, value);
            }
        }

        public CyEIDACRangeType IDACRange
        {
            get
            {
                return GetValue<CyEIDACRangeType>(CyParamName.IDAC_RANGE);
            }
            set
            {
                SetValue(CyParamName.IDAC_RANGE, value);
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

        public double GetMaxCurrentValue()
        {
            double result;
            switch (Resolution)
            {
                case CyParamRange.RESOLUTION_7:
                    result = (IDACRange == CyEIDACRangeType.LowRange) ?
                        CyParamRange.IDAC_CURR_LR_7_BIT_MAX : CyParamRange.IDAC_CURR_HR_7_BIT_MAX;
                    break;
                case CyParamRange.RESOLUTION_8:
                    result = (IDACRange == CyEIDACRangeType.LowRange) ?
                        CyParamRange.IDAC_CURR_LR_8_BIT_MAX : CyParamRange.IDAC_CURR_HR_8_BIT_MAX;
                    break;
                default:
                    result = 0;
                    break;
            }
            return result;
        }

        public UInt16 GetMaxConvertedValue()
        {
            return (Resolution == CyParamRange.RESOLUTION_7) ?
                CyParamRange.IDAC_CONV_7_BIT_MAX : CyParamRange.IDAC_CONV_8_BIT_MAX;
        }

        public double GetRangeCoeff()
        {
            return (IDACRange == CyEIDACRangeType.LowRange) ?
                CyParamRange.LOW_RANGE_COEFF : CyParamRange.HIGH_RANGE_COEFF;
        }

        private UInt16 GetConvertedValue(double value)
        {
            return ((UInt16)Math.Round(value / GetRangeCoeff()));
        }
        public UInt16 GetCurrentRoundedValue()
        {
            return (UInt16)Math.Round(GetRangeCoeff() * IDACValue);
        }
        public string GetConvertedValue(string text)
        {
            double value = 0;
            double.TryParse(text, out value);
            return GetConvertedValue(value).ToString("X2");
        }

        public string GetCurrentValue(string text)
        {
            int value = 0;

            try
            {
                value = Convert.ToInt32(text, 16);
            }
            catch { }

            return (value * GetRangeCoeff()).ToString();
        }
        #endregion

        #region Setting parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (m_inst.SetParamExpr(paramName, valueToSet))
                {
                    m_inst.CommitParamExprs();
                }
            }
        }
        #endregion
    }
}
