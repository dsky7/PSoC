/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;

namespace PWM_v2_40
{
    public class CyPWMParameters
    {
        public const string FIXED_FUNCTION = "FixedFunction";

        public CyCompDevParam m_captureMode = null;
        public CyCompDevParam m_compareStatusEdgeSense = null;
        public CyCompDevParam m_compareType1 = null;
        public CyCompDevParam m_compareType2 = null;
        public CyCompDevParam m_compareValue1 = null;
        public CyCompDevParam m_compareValue2 = null;
        public CyCompDevParam m_deadBand = null;
        public CyCompDevParam m_deadTime = null;
        public CyCompDevParam m_ditherOffset = null;
        public CyCompDevParam m_enableMode = null;
        public CyCompDevParam m_fixedFunction = null;
        public CyCompDevParam m_interruptOnCMP1 = null;
        public CyCompDevParam m_interruptOnCMP2 = null;
        public CyCompDevParam m_interruptOnKill = null;
        public CyCompDevParam m_interruptOnTC = null;
        public CyCompDevParam m_killMode = null;
        public CyCompDevParam m_minimumKillTime = null;
        public CyCompDevParam m_period = null;
        public CyCompDevParam m_pwmMode = null;
        public CyCompDevParam m_resolution = null;
        public CyCompDevParam m_runMode = null;
        public CyCompDevParam m_triggerMode = null;
        public CyCompDevParam m_useInterrupt = null;

        public CyPWMParameters(ICyInstEdit_v1 inst)
        {
            GetParams(inst);
        }

        private void GetParams(ICyInstEdit_v1 inst)
        {
            m_captureMode = inst.GetCommittedParam("CaptureMode");
            m_compareStatusEdgeSense = inst.GetCommittedParam("CompareStatusEdgeSense");
            m_compareType1 = inst.GetCommittedParam("CompareType1");
            m_compareType2 = inst.GetCommittedParam("CompareType2");
            m_compareValue1 = inst.GetCommittedParam("CompareValue1");
            m_compareValue2 = inst.GetCommittedParam("CompareValue2");
            m_deadBand = inst.GetCommittedParam("DeadBand");
            m_deadTime = inst.GetCommittedParam("DeadTime");
            m_ditherOffset = inst.GetCommittedParam("DitherOffset");
            m_enableMode = inst.GetCommittedParam("EnableMode");
            m_fixedFunction = inst.GetCommittedParam(FIXED_FUNCTION);
            m_interruptOnKill = inst.GetCommittedParam("InterruptOnKill");
            m_interruptOnCMP1 = inst.GetCommittedParam("InterruptOnCMP1");
            m_interruptOnCMP2 = inst.GetCommittedParam("InterruptOnCMP2");
            m_interruptOnTC = inst.GetCommittedParam("InterruptOnTC");
            m_killMode = inst.GetCommittedParam("KillMode");
            m_minimumKillTime = inst.GetCommittedParam("MinimumKillTime");
            m_period = inst.GetCommittedParam("Period");
            m_pwmMode = inst.GetCommittedParam("PWMMode");
            m_resolution = inst.GetCommittedParam("Resolution");
            m_runMode = inst.GetCommittedParam("RunMode");
            m_triggerMode = inst.GetCommittedParam("TriggerMode");
            m_useInterrupt = inst.GetCommittedParam("UseInterrupt");
        }
    }
}
