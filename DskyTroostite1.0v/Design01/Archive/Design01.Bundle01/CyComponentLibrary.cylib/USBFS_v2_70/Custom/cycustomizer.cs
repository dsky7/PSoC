/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;
 
namespace USBFS_v2_70
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyBootLoaderSupport, ICyDRCProvider_v1
    {
        public const string PAPAM_TAB_NAME_DEVICE = "Device";
        public const string PAPAM_TAB_NAME_STRING = "String";
        public const string PAPAM_TAB_NAME_HID = "Hid";
        public const string PAPAM_TAB_NAME_AUDIO = "Audio";
        public const string PAPAM_TAB_NAME_MIDI = "Midi";
        public const string PAPAM_TAB_NAME_CDC = "CDC";
        public const string PAPAM_TAB_NAME_ADVANCED = "Advanced";
        public const string PAPAM_TAB_BUILTIN = "Built-in";

        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyUSBFSParameters parameters = new CyUSBFSParameters(edit);
            CyCDCDescriptorPage cdcPage = new CyCDCDescriptorPage(parameters);
            CyMidiDescriptorPage midiPage = new CyMidiDescriptorPage(parameters);
            CyAdvancedPage advPage = new CyAdvancedPage(parameters);
            CyParamExprDelegate ParamCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                if (param.TabName == PAPAM_TAB_NAME_ADVANCED)
                {
                    advPage.InitFields();
                }
                else if (param.TabName == PAPAM_TAB_NAME_CDC)
                {
                    cdcPage.InitAdditionalCheckBoxes();
                }
                else if (param.TabName == PAPAM_TAB_NAME_MIDI)
                {
                    midiPage.InitAdditionalCheckBoxes();
                }
                parameters.GlobalEditMode = true;
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_DEVDESC,
                                 new CyDeviceDescriptorPage(parameters), ParamCommitted,  PAPAM_TAB_NAME_DEVICE);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_STRDESC,
                                 new CyStringDescriptorPage(parameters), ParamCommitted, PAPAM_TAB_NAME_STRING);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_HIDDESC, new CyHidDescriptorPage(parameters),
                                 ParamCommitted, PAPAM_TAB_NAME_HID);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_AUDIODESC,
                                 new CyAudioDescriptorPage(parameters), ParamCommitted, PAPAM_TAB_NAME_AUDIO);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_MIDIDESC, 
                                 midiPage, ParamCommitted, PAPAM_TAB_NAME_MIDI);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_CDCDESC, cdcPage, ParamCommitted, PAPAM_TAB_NAME_CDC);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_ADV, advPage, ParamCommitted, PAPAM_TAB_NAME_ADVANCED);
            editor.AddDefaultPage(Properties.Resources.PAGE_TITLE_BUILTIN, PAPAM_TAB_BUILTIN);

            parameters.GlobalEditMode = true;
            DialogResult result = editor.ShowDialog();
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

        #region ICyBootLoaderSupport Members

        /// <summary>
        /// The bootloader requires that the communication component is configured for
        /// both transfer in and out of the PSoC device. This method lets the implementing
        /// component inform PSoC Creator if it is currently configured to handle input and
        /// output.
        /// <param name="query">The ICyInstQuery for the relevant instance of the component.</param>
        /// </summary>
        public CyCustErr IsBootloaderReady(ICyInstQuery_v1 query)
        {
			CyCustErr supportBootloader = CyCustErr.OK;

            CyCompDevParam param = query.GetCommittedParam(CyUSBFSParameters.PARAM_DEVICEDESCRIPTORS);
            //Extract parameters
            CyUSBFSParameters parameters = new CyUSBFSParameters(query);
            if (parameters.CheckBootloaderReady() == false)
                supportBootloader = new CyCustErr(Properties.Resources.MSG_BOOTLOADER_SUPPORT);
			return supportBootloader;
		}
		
		#endregion

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            //Extract parameters
            CyUSBFSParameters parameters = new CyUSBFSParameters(args.InstQueryV1);           
            string selOption;
            if (!parameters.CheckSiliconRevisionForDMA(args.DeviceQueryV1, out selOption))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                              String.Format(Properties.Resources.MSG_DRC_DMA_ERROR, selOption));
            }

            #region DRCs for endpoints

            // 1. Generate error in DRC when MaxPacketSize is greater then 512 and EMM is not "DMA w/AutomaticMM".
            if (!parameters.CheckEPMaxPacketSize(parameters.m_deviceTree.m_nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.ERR_EP_MAXPACKETSIZE);
            }

            // 2. Generate DRC error when total sum of the MaxPacketSize for all EPs in one Device is greater then 512 
            // when EMM is not "DMA w/AutomaticMM".
            if (!parameters.CheckSumEPMaxPacketSize(parameters.m_deviceTree.m_nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.MSG_DRC_EP_SUM_MANUAL);
            }

            // 3. Generate DRC error when total ISO EPs sum is greater then 1100 (this is bandwith limitation).
            if (!parameters.CheckSumEPMaxPacketSizeAll(parameters.m_deviceTree.m_nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.MSG_DRC_EP_SUM_AUTO);
            }

            // 4. Generate DRC error when Bulk EP MaxPacketSize is not from the list {8, 16, 32, 64}.
            if (!parameters.CheckEPBulkMaxPacketSize(parameters.m_deviceTree.m_nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.MSG_BULK_MAXPACKETSIZE);
            }

            #endregion DRCs for endpoints
        }
    }
}
