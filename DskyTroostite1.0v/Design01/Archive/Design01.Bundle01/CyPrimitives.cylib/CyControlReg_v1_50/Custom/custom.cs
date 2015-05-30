/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyCustomizer.CyControlReg_v1_50;

namespace CyCustomizer.CyControlReg_v1_50
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const int PSOC3_ES3 = 3;
        public const int PSOC5_ES2 = 2;	    
        public const int FIRST_BITMODE_INDEX = 0;
        public const int LAST_BITMODE_INDEX = 7;
        public const int DEFAULT_NUMOUTPUT = 0;
        public const int PSOC_ES2 = 1;        
        public const int DIRECT_MODE = 0;
        public const int SYNC_MODE= 1;
        public const int PULSE_MODE = 3;

        #region ICyParamEditHook_v1 Members
        public ICyInstEdit_v1 m_Component = null;
        public CyBitFieldEditingControl m_bitFieldEdit = null;

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
          
            m_Component = edit;                     
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            m_bitFieldEdit = new CyBitFieldEditingControl(edit);
            
            CyParamExprDelegate ParamCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam comp)
            {
                // For right now it needs to atleast set a default BitField of the correct Length 
                if (comp.Name == CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS)
                {
                    int outputs = DEFAULT_NUMOUTPUT;
                    try
                    {
                        outputs = Convert.ToInt16(m_Component.GetCommittedParam(CyControlReg_v1_50.ControlRegParameters.NUMOUTPUTS).Value);
                    }
                    catch (Exception) { }

                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT0MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT1MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT2MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT3MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT4MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT5MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT6MODE, CyBitfieldControl.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_50.ControlRegParameters.BIT7MODE, CyBitfieldControl.DIRECTMODE);                                        
                }
            };
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_bitFieldEdit.UpdateFormFromParams(edit);
            };
            // TODO: hookup correctly to get expression view 
            editor.AddCustomPage("Configure", m_bitFieldEdit, new CyParamExprDelegate(ExprDelegate), "Basic", "Advanced");
            editor.AddDefaultPage("Built-in", "Built-in");
            DialogResult result = editor.ShowDialog();            
            editor.ParamExprCommittedDelegate = ParamCommitted;            
            return result;
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

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
           
            CyCustErr err = VerifyBitField(args);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
            
            for (int i = FIRST_BITMODE_INDEX; i <= LAST_BITMODE_INDEX; i++)
            {
                CyCompDevParam BitMode = args.InstQueryV1.GetCommittedParam(CyBitfieldControl.BIT + i.ToString() + CyBitfieldControl.MODE);
                CyCompDevParam ExternalReset = args.InstQueryV1.GetCommittedParam(ControlRegParameters.EXTERNALRESET);
                if ((Convert.ToInt32(BitMode.Value) == SYNC_MODE || Convert.ToInt32(BitMode.Value) == PULSE_MODE) && ExternalReset.Value == "true")
                {
                    CyCustErr error = VerifyReset(args);

                    if (error.IsOk == false)
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, error.Message);
                }
            }
        }

        CyCustErr VerifyBitField(ICyDRCProviderArgs_v1 drcQuery)
        {

            for (int i = FIRST_BITMODE_INDEX; i <= LAST_BITMODE_INDEX; i++)
            {
                Int16 device = PSOC_ES2;
                try
                {
                    device = Convert.ToInt16(drcQuery.DeviceQueryV1.SiliconRevision.ToString());
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
                CyCompDevParam BitMode = drcQuery.InstQueryV1.GetCommittedParam(CyBitfieldControl.BIT + i.ToString() + CyBitfieldControl.MODE);
                if(((drcQuery.DeviceQueryV1.SiliconRevision < PSOC3_ES3 && drcQuery.DeviceQueryV1.IsPSoC3 == true) || 
			       (drcQuery.DeviceQueryV1.SiliconRevision < PSOC5_ES2 && drcQuery.DeviceQueryV1.IsPSoC5 == true)))
                {
                    if (Convert.ToInt32(BitMode.Value) == SYNC_MODE || Convert.ToInt32(BitMode.Value) == PULSE_MODE)
                    {
                        return new CyCustErr(Properties.Resources.VerifyBitFieldParamErrorMsg);
                    }
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyReset(ICyDRCProviderArgs_v1 drcQuery)
        {
            Int16 device = PSOC_ES2;
            try
            {
                device = Convert.ToInt16(drcQuery.DeviceQueryV1.SiliconRevision.ToString());
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            if(((drcQuery.DeviceQueryV1.SiliconRevision < PSOC3_ES3 && drcQuery.DeviceQueryV1.IsPSoC3 == true) || 
			   (drcQuery.DeviceQueryV1.SiliconRevision < PSOC5_ES2 && drcQuery.DeviceQueryV1.IsPSoC5 == true)))
			{			
                return new CyCustErr(Properties.Resources.VerifyResetErrorMsg);
            }
            return CyCustErr.OK;
        }
        #endregion
    }

    //Create a new control to add to a tab
    public class CyBitFieldEditingControl : ICyParamEditingControl
    {
        CyBitfieldControl m_control;

        public CyBitFieldEditingControl(ICyInstEdit_v1 inst)
        {
            m_control = new CyBitfieldControl(inst);
            m_control.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return m_control; }
        }

        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            m_control.UpdateFormFromInst(inst);
        }
        
        public IEnumerable<CyCustErr> GetErrors()
        {
            return new CyCustErr[] { };    // return an empty array 
        }

        #endregion
    }
}
