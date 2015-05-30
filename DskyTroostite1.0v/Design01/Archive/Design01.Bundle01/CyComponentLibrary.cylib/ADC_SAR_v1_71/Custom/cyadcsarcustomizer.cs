/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;

namespace ADC_SAR_v1_71
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const string CONFIGURE_TAB_NAME = "Configure";
        // minimum pulse width value = 1/14Mhz = 71.43ns / 2 = 35.71ns - some margin (~+-4% CDT 91247) = 33ns.
        private const double MINIMUM_PULSE_WIDTH = 33;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CySARADCParameters parameters = new CySARADCParameters(edit, termQuery);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.LoadParameters();
            };

            editor.AddCustomPage(Resources.ConfigureTabCaption, new CySARADCControl(parameters, edit.DeviceQuery),
                ExprDelegate, CONFIGURE_TAB_NAME);
            editor.AddDefaultPage(Resources.BuiltInTabCaption, "Built-in");

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(parameters.UpdateClock));

            parameters.LoadParameters();
            parameters.m_globalEditMode = true;
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            string refVoltage = args.InstQueryV1.GetCommittedParam(CyParamNames.REF_VOLTAGE).Value;

            CyCustErr err = VerifyInternalClock(args.InstQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyVoltage(args.InstQueryV1, refVoltage);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyReference(args.InstQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyExternalClock(args.TermQueryV1, args.InstQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        CyCustErr VerifyInternalClock(ICyInstQuery_v1 instQuery)
        {
            string instanceName = instQuery.GetCommittedParam("INSTANCE_NAME").Value;
            string adcClock = instQuery.GetCommittedParam(CyParamNames.ADC_CLOCK).Expr;
            double internalClockValue = 0;

            if (adcClock == CyEAdcClockSrcType.Internal.ToString())
            {
                internalClockValue = CyClockReader.GetInternalClockInMHz(instQuery.DesignQuery, instanceName
                    + CyClockReader.INTERNAL_CLK);

                if (internalClockValue >= 0)
                {
                    // Ten to the six power for converting Hz to MHz
                    const int POW6 = 1000000;
                    // Converting clock name to clock ID for accuracy getting function
                    string clockID = CyClockReader.GetClockID(instQuery.DesignQuery, instanceName
                        + CyClockReader.INTERNAL_CLK);
                    // Get accuracy prcent with negative sign
                    double plusAccuracyPercent = instQuery.DesignQuery.GetClockPlusAccuracyPercent(clockID);
                    // Get accuracy prcent with plus sign
                    double minusAccuracyPercent = instQuery.DesignQuery.GetClockMinusAccuracyPercent(clockID);
                    // Minimum clock value with plus accuracy percent
                    double minClockPlusAccuracy = CyParamRange.CLOCK_FREQ_MIN_HZ + (CyParamRange.CLOCK_FREQ_MIN_HZ
                        * plusAccuracyPercent / 100);
                    // Maximum clock value with negative accuracy percent
                    double maxClockMinusAccuracy = CyParamRange.CLOCK_FREQ_MAX_HZ - (CyParamRange.CLOCK_FREQ_MAX_HZ
                        * minusAccuracyPercent / 100);

                    if (internalClockValue < minClockPlusAccuracy || internalClockValue > maxClockMinusAccuracy)
                    {
                        return new CyCustErr(string.Format(Resources.DRCInternalClockFreqMsg,
                            CyParamRange.CLOCK_FREQ_MIN_MHZ, plusAccuracyPercent, minClockPlusAccuracy / POW6,
                            CyParamRange.CLOCK_FREQ_MAX_MHZ, minusAccuracyPercent, maxClockMinusAccuracy / POW6));
                    }
                    else
                    {
                        double masterClockValue = CyClockReader.GetInternalClockInMHz(instQuery.DesignQuery,
                            CyClockReader.MASTER_CLK);
                        double x = masterClockValue / internalClockValue;
                        double y;
                        if (x == 1)
                        {
                            y = (1 / (masterClockValue / POW6) * ((x / 2))) * 1000;
                        }
                        else
                        {
                            y = (1 / (masterClockValue / POW6) * (Math.Floor(x / 2))) * 1000;
                        }
                        if (y < MINIMUM_PULSE_WIDTH)
                            return new CyCustErr(string.Format(Resources.DRCMinimumPulseWidthMsg, MINIMUM_PULSE_WIDTH));
                        else
                            return CyCustErr.OK;
                    }
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyExternalClock(ICyTerminalQuery_v1 termQuery, ICyInstQuery_v1 instQuery)
        {
            string clockSource = instQuery.GetCommittedParam(CyParamNames.ADC_CLOCK).Expr;

            if (clockSource == CyEAdcClockSrcType.External.ToString())
            {
                double externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery, CyClockReader.EXTERNAL_CLK);
                if (externalClockInKHz > 0)
                {
                    if (externalClockInKHz < CyParamRange.CLOCK_FREQ_MIN_KHZ ||
                        externalClockInKHz > CyParamRange.CLOCK_FREQ_MAX_KHZ)
                    {
                        return new CyCustErr(string.Format(Resources.ClockFrequencyErrorMsg,
                            CyParamRange.CLOCK_FREQ_MIN_MHZ, CyParamRange.CLOCK_FREQ_MAX_MHZ));
                    }
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyVoltage(ICyInstQuery_v1 instQuery, string refVoltage)
        {
            double voltageReference = 0;
            double vdda = 0;
            double.TryParse(refVoltage, out voltageReference);
            try
            {
                vdda = Convert.ToDouble(Math.Round(instQuery.VoltageQuery.VDDA, 4));
            }
            catch
            {
                vdda = 0;
            }
            if (vdda > 0)
            {
                double maxVoltage;
                string message;
                // External voltage reference should be limited to Vdda/2 for "Vssa to Vdda(Single)" 
                // and "0.0 +/- Vdda/2(Differential)" input ranges

                CyEAdcRefType reference;
                instQuery.GetCommittedParam(CyParamNames.ADC_REFERENCE).TryGetValueAs<CyEAdcRefType>(out reference);
                CyEAdcInputRangeType inputRange;
                instQuery.GetCommittedParam(CyParamNames.ADC_INPUT_RANGE).TryGetValueAs<CyEAdcInputRangeType>(
                    out inputRange);

                if (reference == CyEAdcRefType.Ext_Ref && (inputRange == CyEAdcInputRangeType.Vssa_to_Vdda ||
                    inputRange == CyEAdcInputRangeType.Vneg_Vdda_2_Diff))
                {
                    maxVoltage = vdda / 2;
                    message = Resources.VoltageReferenceErrorMsgVddaDiv2;
                }
                else
                {
                    maxVoltage = vdda;
                    message = Resources.VoltageReferenceErrorMsg;
                }

                if (voltageReference < CyParamRange.REF_VOLTAGE_MIN || voltageReference > maxVoltage)
                {
                    return new CyCustErr(message, CyParamRange.REF_VOLTAGE_MIN, maxVoltage);
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyReference(ICyInstQuery_v1 instQuery)
        {
            CyEAdcRefType reference;
            instQuery.GetCommittedParam(CyParamNames.ADC_REFERENCE).TryGetValueAs<CyEAdcRefType>(out reference);
            CyEAdcClockSrcType clockSource;
            instQuery.GetCommittedParam(CyParamNames.ADC_CLOCK).TryGetValueAs<CyEAdcClockSrcType>(out clockSource);
            uint sampleRate;
            instQuery.GetCommittedParam(CyParamNames.SAMPLE_RATE).TryGetValueAs<uint>(out sampleRate);

            if (reference == CyEAdcRefType.Int_Ref_Not_Bypassed && clockSource == CyEAdcClockSrcType.Internal &&
                sampleRate > CyParamRange.CONVERSION_RATE_INT_VREF_MAX)
                return new CyCustErr(Resources.InvalidReferenceErrorMsg);
            else
                return CyCustErr.OK;
        }
        #endregion
    }
}
