/*******************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;

namespace CapSense_CSD_P4_TunerIntf_v1_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string EZBUFI2C_COLIDE_BEHAVIOR = "EzBufI2cWaitStatesEnable";
        public const string EZBUFI2C_DATA_RATE = "EzBufI2cDataRate";
        public const string EZBUFI2C_OVERSAMPLING = "EzBufI2cOvsFactor";
        public const string EZI2C_OPERATION_MODE = "EzBufI2cOperationMode";
        public const string EZBUFI2C_CLOCK_FROM_TERMINAL = "EzBufI2cClockFromTerm";
        public const string EZBUFI2C_ENABLE_MEDIAN_FILTER = "EzBufI2cMedianFilterEnable";
        public const string EZBUFI2C_IS_SLAVE_ADDRESS_HEX = "EzBufI2cIsSlaveAddressHex";
        public const string EZBUFI2C_IS_SLAVE_ADDRESS_MASK_HEX = "EzBufI2cIsSlaveAddressMaskHex";
        public const string EZBUFI2C_POST_WAKEUP_BEHAVIOR = "EzBufI2cWakeAction";
        public const string EZBUFI2C_SLAVE_ADDRESS = "EzBufI2cSlaveAddress";
        public const string EZBUFI2C_SLAVE_ADDRESS_MASK = "EzBufI2cSlaveAddressMask";
        public const string EZBUFI2C_ENABLE_WAKEUP = "EzBufI2cWakeEnable";

        public const string EZBUFI2C_INTERRUPT_MODE = "EzBufI2cInterruptMode";
        public const string EZBUFI2C_INTERRUPT_WAKE = "EzBufI2cIntrWake";
        public const string EZBUFI2C_INTERRUPT_STOP = "EzBufI2cIntrStop";
        public const string EZBUFI2C_INTERRUPT_WRITE_STOP = "EzBufI2cIntrWriteStop";
        public const string EZBUFI2C_INTERRUPT_RX_BLOCKED = "EzBufI2cIntrRxBlocked";
        public const string EZBUFI2C_INTERRUPT_TX_BLOCKED = "EzBufI2cIntrTxBlocked";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const UInt16 I2C_DATA_RATE_MIN = 1;
        public const UInt16 I2C_DATA_RATE_MAX = 1000;

        public const byte I2C_OVS_FACTOR_MAX = 32;

        public const byte I2C_OVS_FACTOR_MEDFILTER_MIN = 14;
        public const byte I2C_OVS_FACTOR_NOMEDFILTER_MIN = 12;

        public const byte I2C_SLAVE_ADDRESS_MIN = 8;
        public const byte I2C_SLAVE_ADDRESS_MAX = 120;

        public const byte I2C_SLAVE_ADDRESS_MASK_MIN = 0;
        public const byte I2C_SLAVE_ADDRESS_MASK_MAX = 254;
    }
    #endregion

    #region Component Enums
    public enum CyEEZOperationalMode
    {
        [Description("Internally clocked")]
        INTERNALLY_CLOCKED,
        [Description("Externally clocked")]
        EXTERNALY_CLOCKED
    };
    public enum CyEEZColideBehavior { WAIT_STATES = 1, NO_WAIT_STATES = 0 };
    public enum CyEI2CPostWakeupOperationType { ADDRESS_ACK, ADDRESS_NACK }
    #endregion

    public partial class CyParameters
    {
        #region Class properties
        public byte EZBufI2C_MinimumOversampling
        {
            get
            {
                return EZBufI2C_EnableMedianFilter ? CyParamRanges.I2C_OVS_FACTOR_MEDFILTER_MIN :
                    CyParamRanges.I2C_OVS_FACTOR_NOMEDFILTER_MIN;
            }
        }

        #region I2C Basic tab properties
        public bool EZBufI2C_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_CLOCK_FROM_TERMINAL); }
            set { SetValue(CyParamNames.EZBUFI2C_CLOCK_FROM_TERMINAL, value); }
        }

        public UInt16 EZBufI2C_DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.EZBUFI2C_DATA_RATE); }
            set { SetValue(CyParamNames.EZBUFI2C_DATA_RATE, value); }
        }

        public byte EZBufI2C_OversamplingFactor
        {
            get { return GetValue<byte>(CyParamNames.EZBUFI2C_OVERSAMPLING); }
            set { SetValue(CyParamNames.EZBUFI2C_OVERSAMPLING, value); }
        }

        public CyEEZColideBehavior EZBufI2C_CollideBehavior
        {
            get { return GetValue<CyEEZColideBehavior>(CyParamNames.EZBUFI2C_COLIDE_BEHAVIOR); }
            set { SetValue(CyParamNames.EZBUFI2C_COLIDE_BEHAVIOR, value); }
        }

        public bool EZBufI2C_EnableMedianFilter
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_ENABLE_MEDIAN_FILTER); }
            set { SetValue(CyParamNames.EZBUFI2C_ENABLE_MEDIAN_FILTER, value); }
        }

        public bool EZBufI2C_EnableWakeupFromSleep
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_ENABLE_WAKEUP); }
            set { SetValue(CyParamNames.EZBUFI2C_ENABLE_WAKEUP, value); }
        }

        public CyEI2CPostWakeupOperationType EZBufI2C_PostWakeupBehavior
        {
            get { return GetValue<CyEI2CPostWakeupOperationType>(CyParamNames.EZBUFI2C_POST_WAKEUP_BEHAVIOR); }
            set { SetValue(CyParamNames.EZBUFI2C_POST_WAKEUP_BEHAVIOR, value); }
        }

        public byte EZBufI2C_SlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.EZBUFI2C_SLAVE_ADDRESS); }
            set { SetValue(CyParamNames.EZBUFI2C_SLAVE_ADDRESS, value); }
        }

        public byte EZBufI2C_SlaveAddressMask
        {
            get { return GetValue<byte>(CyParamNames.EZBUFI2C_SLAVE_ADDRESS_MASK); }
            set { SetValue(CyParamNames.EZBUFI2C_SLAVE_ADDRESS_MASK, value); }
        }

        public bool EZBufI2C_IsSlaveAddressHex
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_IS_SLAVE_ADDRESS_HEX); }
            set { SetValue(CyParamNames.EZBUFI2C_IS_SLAVE_ADDRESS_HEX, value); }
        }

        public bool EZBufI2C_IsSlaveAddressMaskHex
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_IS_SLAVE_ADDRESS_MASK_HEX); }
            set { SetValue(CyParamNames.EZBUFI2C_IS_SLAVE_ADDRESS_MASK_HEX, value); }
        }
        #endregion

        #region I2C Advanced tab properties
        public CyEInterruptModeType EZBufI2C_InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.EZBUFI2C_INTERRUPT_MODE); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_MODE, value); }
        }

        public bool EZBufI2C_InterruptEZWake
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_INTERRUPT_WAKE); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_WAKE, value); }
        }

        public bool EZBufI2C_InterruptEZStop
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_INTERRUPT_STOP); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_STOP, value); }
        }

        public bool EZBufI2C_InterruptEZWriteStop
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_INTERRUPT_WRITE_STOP); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_WRITE_STOP, value); }
        }

        public bool EZBufI2C_InterruptEZRxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_INTERRUPT_RX_BLOCKED); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_RX_BLOCKED, value); }
        }

        public bool EZBufI2C_InterruptEZTxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZBUFI2C_INTERRUPT_TX_BLOCKED); }
            set { SetValue(CyParamNames.EZBUFI2C_INTERRUPT_TX_BLOCKED, value); }
        }
        #endregion
        #endregion
    }
}
