﻿/*******************************************************************************
* Copyright 2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace EMIF_v1_0
{
    #region Symbol Parameter Names
    public class CyParamNames
    {
        public const string EMIF_ADDR = "EMIF_Addr";
        public const string EMIF_DATA = "EMIF_Data";
        public const string EMIF_MEMSPEED = "EMIF_MemSpeed";
        public const string EMIF_MODE = "EMIF_Mode";
    }
    #endregion

    #region Parameter ranges
    public class CyParamRange
    {
        public const byte MEMORY_SPEED_MIN = 5;
        public const byte MEMORY_SPEED_MAX = 200;
    }
    #endregion

    #region Symbol Types
    public enum CyEDataWidth { Data8 = 8, Data16 = 16 };
    public enum CyESRAMMode { Asynch, Synch, Custom };
    public enum CyEAddrWidth { Address8 = 8, Address16 = 16, Address24 = 24 };
    #endregion

    public class CyEMIFParameters
    {
        #region Declaring public variables
        public ICyInstEdit_v1 m_inst;
        /// <summary>
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediatly overwrite parameters with the same values.
        /// </summary>
        public bool m_globalEditMode = false;
        public CyEMIFBasicTab m_basicTab = null;
        #endregion

        #region Constructor(s)
        public CyEMIFParameters(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termQuery)
        {
            this.m_inst = inst;
        }
        #endregion

        #region Basic tab properties
        public CyESRAMMode Mode
        {
            get
            {
                return GetValue<CyESRAMMode>(CyParamNames.EMIF_MODE);
            }
            set
            {
                SetParameter(CyParamNames.EMIF_MODE, value);
            }
        }

        public CyEAddrWidth AddressWidth
        {
            get
            {
                return GetValue<CyEAddrWidth>(CyParamNames.EMIF_ADDR);
            }
            set
            {
                SetParameter(CyParamNames.EMIF_ADDR, value);
            }
        }

        public CyEDataWidth DataWidth
        {
            get
            {
                return GetValue<CyEDataWidth>(CyParamNames.EMIF_DATA);
            }
            set
            {
                SetParameter(CyParamNames.EMIF_DATA, value);
            }
        }

        public byte MemorySpeed
        {
            get
            {
                return GetValue<byte>(CyParamNames.EMIF_MEMSPEED);
            }
            set
            {
                SetParameter(CyParamNames.EMIF_MEMSPEED, value);
            }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        public void LoadParameters()
        {
            m_globalEditMode = false;
            m_basicTab.UpdateUI();
            m_globalEditMode = true;
        }
        #endregion

        #region Setting Parameters
        public void SetParameter<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                m_inst.SetParamExpr(paramName, value.ToString());
                m_inst.CommitParamExprs();
            }
        }
        #endregion
    }
}
