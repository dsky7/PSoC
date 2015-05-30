/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Bootloader_v1_20
{
    public class CyParameters
    {
        #region Const
        public const string PARAM_WAIT_TIME = "waitForCommandTime";
        public const string PARAM_WAIT_ENABLE = "waitForCommand";
        public const string PARAM_PACKET_CHECKSUM_TYPE = "packetChecksumCrc";
        public const string PARAM_VERSION = "bootloaderAppVersion";
        public const string PARAM_FAST_VALIDATION = "fastAppValidation";
        public const string PARAM_FAST_BR_VALIDATION = "bootloaderAppValidation";
        public const string PARAM_CMD_FLASHSIZE = "cmdGetFlashSizeAvail";
        public const string PARAM_CMD_ERASEROW = "cmdEraseRowAvail";
        public const string PARAM_CMD_VERIFYROW = "cmdVerifyRowAvail";
        public const string PARAM_CMD_SENDDATA = "cmdSendDataAvail";
        public const string PARAM_CMD_SYNCBOOTLOADER = "cmdSyncBootloaderAvail";
        public const string PARAM_CMD_GETAPPSTATUS = "cmdGetAppStatusAvail";
        public const string PARAM_CMD_GETMETADATA = "cmdGetMetadataAvail";
        public const string PARAM_MULTI_APP = "multiAppBootloader";
        public const string PARAM_IO_COMPONENT = "ioComponent";

        public const string CUSTOM_INTERFACE = "Custom interface";

        public const UInt16 MAX_WAIT_TIME = 25500;
        #endregion Const

        #region Properties, Fields
        public byte WaitTime
        {
            get { return GetValue<byte>(PARAM_WAIT_TIME); }
            set { SetValue(PARAM_WAIT_TIME, value); }
        }
        public bool WaitEnable
        {
            get { return GetValue<bool>(PARAM_WAIT_ENABLE); }
            set { SetValue(PARAM_WAIT_ENABLE, value); }
        }
        public bool PacketChecksumType
        {
            get { return GetValue<bool>(PARAM_PACKET_CHECKSUM_TYPE); }
            set { SetValue(PARAM_PACKET_CHECKSUM_TYPE, value); }
        }
        public UInt16 Version
        {
            get { return GetValue<UInt16>(PARAM_VERSION); }
            set { SetValue(PARAM_VERSION, value); }
        }
        public bool FastValidation
        {
            get { return GetValue<bool>(PARAM_FAST_VALIDATION); }
            set { SetValue(PARAM_FAST_VALIDATION, value); }
        }
        public bool FastBrValidation
        {
            get { return GetValue<bool>(PARAM_FAST_BR_VALIDATION); }
            set { SetValue(PARAM_FAST_BR_VALIDATION, value); }
        }
        public bool CmdFlashSize
        {
            get { return GetValue<bool>(PARAM_CMD_FLASHSIZE); }
            set { SetValue(PARAM_CMD_FLASHSIZE, value); }
        }
        public bool CmdEraseRow
        {
            get { return GetValue<bool>(PARAM_CMD_ERASEROW); }
            set { SetValue(PARAM_CMD_ERASEROW, value); }
        }
        public bool CmdVerifyRow
        {
            get { return GetValue<bool>(PARAM_CMD_VERIFYROW); }
            set { SetValue(PARAM_CMD_VERIFYROW, value); }
        }
        public bool CmdSendData
        {
            get { return GetValue<bool>(PARAM_CMD_SENDDATA); }
            set { SetValue(PARAM_CMD_SENDDATA, value); }
        }
        public bool CmdSyncBootloader
        {
            get { return GetValue<bool>(PARAM_CMD_SYNCBOOTLOADER); }
            set { SetValue(PARAM_CMD_SYNCBOOTLOADER, value); }
        }
        public bool CmdGetAppStatus
        {
            get { return GetValue<bool>(PARAM_CMD_GETAPPSTATUS); }
            set { SetValue(PARAM_CMD_GETAPPSTATUS, value); }
        }
        public bool CmdGetMetadata
        {
            get { return GetValue<bool>(PARAM_CMD_GETMETADATA); }
            set { SetValue(PARAM_CMD_GETMETADATA, value); }
        }
        public bool MultiAppBootloader
        {
            get { return GetValue<bool>(PARAM_MULTI_APP); }
            set { SetValue(PARAM_MULTI_APP, value); }
        }
        public string IOComponent
        {
            get
            {
                string val = GetValue<string>(PARAM_IO_COMPONENT);
                if (val.ToLower() == CUSTOM_INTERFACE.ToLower())
                    val = CUSTOM_INTERFACE;
                return val;
            }
            set
            {
                if (value == CUSTOM_INTERFACE)
                    value = value.Replace("i", "I");
                SetValue(PARAM_IO_COMPONENT, value);
            }
        }

        public readonly ICyInstQuery_v1 m_inst;
        public bool m_globalEditMode = false;

        public List<string> m_ioComponentList;
        #endregion Properties, Fields

        #region Common
        public CyParameters()
        {
        }

        public CyParameters(ICyInstQuery_v1 inst)
            : this()
        {
            m_inst = inst;
            m_ioComponentList = new List<string>();
        }

        private T GetValue<T>(string paramName)
        {
            return GetValue<T>(m_inst.GetCommittedParam(paramName));
        }

        public static T GetValue<T>(CyCompDevParam prm)
        {
            T value = default(T);
            CyCustErr err;
            if (typeof(T).BaseType == typeof(Enum))
            {
                int res;
                err = prm.TryGetValueAs<int>(out res);
                try
                {
                    value = (T)Enum.ToObject(value.GetType(), res);
                }
                catch { value = default(T); }
            }
            else
                err = prm.TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }

        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
                if (m_inst != null && m_inst is ICyInstEdit_v1)
                {
                    ICyInstEdit_v1 edit = m_inst as ICyInstEdit_v1;
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value.GetType().BaseType == typeof(Enum))
                        valueToSet = Convert.ToInt32(value).ToString();
                    if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                        valueToSet += "u";
                    if (edit.SetParamExpr(paramName, valueToSet))
                    {
                        edit.CommitParamExprs();
                    }
                }
        }
        #endregion Common

        #region Compare App type
        public bool CompareAppType()
        {
            bool match = true;
            try
            {
                if ((m_inst.DesignQuery.ApplicationType == CyApplicationType_v1.Bootloader) ||
                    (m_inst.DesignQuery.ApplicationType == CyApplicationType_v1.MultiAppBootloader))
                {
                    bool multiAppProject =
                        (m_inst.DesignQuery.ApplicationType == CyApplicationType_v1.MultiAppBootloader);
                    match = (MultiAppBootloader == multiAppProject);
                }
            }
            catch
            {
                Debug.Assert(false);
            }
            return match;
        }
        #endregion
    }
}
