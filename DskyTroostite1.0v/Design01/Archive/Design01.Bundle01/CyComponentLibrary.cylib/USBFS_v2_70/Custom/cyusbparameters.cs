/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;

namespace USBFS_v2_70
{
    public partial class CyUSBFSParameters
    {
        public enum CyMemoryManagement
        {
            [XmlEnum("MANUAL")]
            EP_Manual,
            [XmlEnum("DMA_MANUAL_MEMORY")]
            EP_DMAmanual,
            [XmlEnum("DMA_AUTOMATIC_MEMORY")]
            EP_DMAauto
        } ;

        public enum CyMemoryAllocation
        {
            [XmlEnum("STATIC")]
            MA_Static,
            [XmlEnum("DYNAMIC")]
            MA_Dynamic
        } ;

        #region Const
        public const int SERIAL_STRING_INDEX = 0x80;
        public const int MSOS_STRING_INDEX = 0xEE;

        public const string TYPE_TREE_NODE = "System.Windows.Forms.TreeNode";
        public const string MSOS_STRING = "MSFT100";

        public const string PARAM_DEVICEDESCRIPTORS = "DeviceDescriptors";
        public const string PARAM_STRINGDESCRIPTORS = "StringDescriptors";
        public const string PARAM_HIDREPORTDESCRIPTORS = "HIDReportDescriptors";
        public const string PARAM_AUDIODESCRIPTORS = "AudioDescriptors";
        public const string PARAM_MIDIDESCRIPTORS = "MidiDescriptors";
        public const string PARAM_CDCDESCRIPTORS = "CDCDescriptors";
        public const string PARAM_EXTERNCLS = "extern_cls";
        public const string PARAM_EXTERNVND = "extern_vnd";
        public const string PARAM_OUTSOF = "out_sof";
        public const string PARAM_MONVBUS = "mon_vbus";
        public const string PARAM_EXTERNVBUS = "extern_vbus";
        public const string PARAM_MAXINTERFACES = "max_interfaces_num";
        public const string PARAM_ENABLECDCAPI = "EnableCDCApi";
        public const string PARAM_ENABLEMIDIAPI = "EnableMidiApi";
        public const string PARAM_ENDPOINTMM = "endpointMM";
        public const string PARAM_ENDPOINTMA = "endpointMA";
        public const string PARAM_JACKCOUNT = "extJackCount";
        public const string PARAM_MODE = "Mode";
        public const string PARAM_VID = "Vid";
        public const string PARAM_PID = "Pid";

        public const string NODEKEY_DEVICE = "Device";
        public const string NODEKEY_STRING = "String";
        public const string NODEKEY_AUDIO = "Audio";
        public const string NODEKEY_MIDI = "Midi";
        public const string NODEKEY_CDC = "CDC";
        public const string NODEKEY_SPECIALSTRING = "SpecialString";
        public const string NODEKEY_HIDREPORT = "HIDReport";
        public const string NODEKEY_INTERFACE = "Interface";
        public const string NODEKEY_USBDESCRIPTOR = "USBDescriptor";
        public const string NODEKEY_MSOS_STRING = "EE";
        public const string NODEKEY_STRING_SERIAL = "Serial";
        public const string NODEKEY_STRING_LANGID = "LANGID";

        public const string TEMPLATE_DIR = 
            "..\\psoc\\content\\cycomponentlibrary\\CyComponentLibrary.cylib\\USBFS_v2_70\\Custom\\template";

        public Dictionary<string, string> HID_REPORT_TEMPLATE_LIST = new Dictionary<string, string>();
        private static string[,] HID_REPORT_TEMPLATE_LIST_STR = {
                          { "3ButtonMouse", "3-Button Mouse" }, 
                          { "5ButtonJoystick", "5-Button Joystick" }, 
                          { "keyboard", "Keyboard" },
                          { "GenericHID_8byte", "8-Byte Generic HID"},
                          { "GenericHID_64byte", "64-Byte Generic HID"}};
        #endregion Const

        #region Fields

        private readonly ICyInstEdit_v1 m_instEdit;
        public readonly ICyInstQuery_v1 m_instQuery;

        private bool m_globalEditMode = false;
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public List<string> m_emptyFields; // Used to store information about fields that user should fill 
                                           //before closing the customizer

        public CyDescriptorTree m_deviceTree;
        public CyDescriptorTree m_stringTree;
        public CyDescriptorTree m_hidReportTree;
        public CyDescriptorTree m_audioTree;
        public CyDescriptorTree m_midiTree;
        public CyDescriptorTree m_cdcTree;

        // Xml serialization parameters
        public XmlSerializer m_serializer;
        public XmlSerializerNamespaces m_customSerNamespace;

        private bool[] m_usedEp = new bool[9];
        private byte m_extJackCount;


        public string SerializedDeviceDesc
        {
            get { return GetValue<string>(PARAM_DEVICEDESCRIPTORS); }
            set { SetValue(PARAM_DEVICEDESCRIPTORS, value); }
        }

        public string SerializedStringDesc
        {
            get { return GetValue<string>(PARAM_STRINGDESCRIPTORS); }
            set { SetValue(PARAM_STRINGDESCRIPTORS, value); }
        }

        public string SerializedHIDReportDesc
        {
            get { return GetValue<string>(PARAM_HIDREPORTDESCRIPTORS); }
            set { SetValue(PARAM_HIDREPORTDESCRIPTORS, value); }
        }

        public string SerializedAudioDesc
        {
            get { return GetValue<string>(PARAM_AUDIODESCRIPTORS); }
            set { SetValue(PARAM_AUDIODESCRIPTORS, value); }
        }

        public string SerializedMidiDesc
        {
            get { return GetValue<string>(PARAM_MIDIDESCRIPTORS); }
            set { SetValue(PARAM_MIDIDESCRIPTORS, value); }
        }

        public string SerializedCDCDesc
        {
            get { return GetValue<string>(PARAM_CDCDESCRIPTORS); }
            set { SetValue(PARAM_CDCDESCRIPTORS, value); }
        }

        public byte MaxInterfaces
        {
            get { return GetValue<byte>(PARAM_MAXINTERFACES); }
            set { SetValue(PARAM_MAXINTERFACES, value); }
        }

        public void SetExtJackCount(byte value)
        {
            m_extJackCount = value;
            SetValue(PARAM_JACKCOUNT, Mode ? m_extJackCount : (byte)0 ); 
        }

        public bool Mode
        {
            get { return GetValue<bool>(PARAM_MODE); }
            set 
            { 
                SetValue(PARAM_MODE, value);
                SetExtJackCount(m_extJackCount);
            }
        }

        public bool EnableCDCApi
        {
            get { return GetValue<bool>(PARAM_ENABLECDCAPI); }
            set { SetValue(PARAM_ENABLECDCAPI, value); }
        }

        public bool EnableMIDIApi
        {
            get { return GetValue<bool>(PARAM_ENABLEMIDIAPI); }
            set { SetValue(PARAM_ENABLEMIDIAPI, value); }
        }

        public bool Extern_cls
        {
            get { return GetValue<bool>(PARAM_EXTERNCLS); }
            set { SetValue(PARAM_EXTERNCLS, value);  }
        }

        public bool Extern_vnd
        {
            get { return GetValue<bool>(PARAM_EXTERNVND); }
            set { SetValue(PARAM_EXTERNVND, value); }
        }

        public bool Out_sof
        {
            get { return GetValue<bool>(PARAM_OUTSOF); }
            set { SetValue(PARAM_OUTSOF, value); }
        }

        public bool Mon_vbus
        {
            get { return GetValue<bool>(PARAM_MONVBUS); }
            set { SetValue(PARAM_MONVBUS, value); }
        }

        public bool Extern_vbus
        {
            get { return GetValue<bool>(PARAM_EXTERNVBUS); }
            set { SetValue(PARAM_EXTERNVBUS, value); }
        }

        public CyMemoryManagement EPMemoryMgmt
        {
            get { return GetValue<CyMemoryManagement>(PARAM_ENDPOINTMM); }
            set { SetValue(PARAM_ENDPOINTMM, value); }
        }

        public CyMemoryAllocation EPMemoryAlloc
        {
            get { return GetValue<CyMemoryAllocation>(PARAM_ENDPOINTMA); }
            set { SetValue(PARAM_ENDPOINTMA, value); }
        }

        public string Vid
        {
            get { return GetValue<string>(PARAM_VID); }
            set { SetValue(PARAM_VID, value); }
        }

        public string Pid
        {
            get { return GetValue<string>(PARAM_PID); }
            set { SetValue(PARAM_PID, value); }
        }

        #endregion Fields

        #region Constructors

        public CyUSBFSParameters()
        {
            // Create XML Serializer
            m_serializer = new XmlSerializer(typeof(CyDescriptorTree));
            m_customSerNamespace = new XmlSerializerNamespaces();
            Type classType = typeof(CyUSBFSParameters);
            string curNamespace = classType.Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("CustomizerVersion", version);

            // Init dictionary that contains list of HID report templates and display names of these templates
            HID_REPORT_TEMPLATE_LIST.Clear();
            for (int i = 0; i < HID_REPORT_TEMPLATE_LIST_STR.GetLength(0); i++)
            {
                HID_REPORT_TEMPLATE_LIST.Add(HID_REPORT_TEMPLATE_LIST_STR[i,0], HID_REPORT_TEMPLATE_LIST_STR[i,1]);
            }

            m_deviceTree = new CyDescriptorTree();
            m_stringTree = new CyDescriptorTree();
            m_hidReportTree = new CyDescriptorTree();
            m_audioTree = new CyDescriptorTree();
            m_midiTree = new CyDescriptorTree();
            m_cdcTree = new CyDescriptorTree();
            m_emptyFields = new List<string>();
        }

        public CyUSBFSParameters(ICyInstQuery_v1 instQuery)
            : this()
        {
            m_instQuery = instQuery;
            m_instEdit = null;
            DeserializeDescriptors();
        }

        public CyUSBFSParameters(ICyInstEdit_v1 instEdit)
            : this()
        {
            m_instQuery = instEdit;
            m_instEdit = instEdit;
            DeserializeDescriptors();
        }

        #endregion Constructors

        #region GetValue
        private T GetValue<T>(string paramName)
        {
            CyCompDevParam prm = m_instQuery.GetCommittedParam(paramName);
            T value = default(T);
            CyCustErr err = CyCustErr.OK;
            if (typeof(T).BaseType == typeof(Enum))
            {
                err = prm.TryGetValueAs<T>(out value);
                if ((err == null) || (err.IsOK == false) || (Enum.IsDefined(typeof(T), value) == false))
                {
                    value = (T)Enum.GetValues(typeof(T)).GetValue(0);
                    err = CyCustErr.OK;
                }
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
        #endregion GetValue

        #region SetValue
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
                if (m_instEdit != null)
                {
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                        valueToSet += "u";
                    if (m_instEdit.SetParamExpr(paramName, valueToSet))
                    {
                        m_instEdit.CommitParamExprs();
                    }
                }
        }

        public void SetParam_rm_ep_isr()
        {
            bool alwaysTrue = true; // for rm_dma params
                
            if (EPMemoryMgmt != CyMemoryManagement.EP_Manual)
                alwaysTrue = false;
                
            for (int i = 1; i < m_usedEp.Length; i++)
            {
                string param_rm_ep_isr = "rm_ep_isr_" + i;
                string param_rm_dma = "rm_dma_" + i;
                if (m_usedEp[i] == true)
                {
                    SetValue(param_rm_ep_isr, false);
                    SetValue(param_rm_dma, alwaysTrue); // if alwaysTrue=false then False
                }
                else
                {
                    SetValue(param_rm_ep_isr, true);
                    SetValue(param_rm_dma, true);
                }
            }
        }

        public void SetCdcVidPid(CyDescriptorNode node, string vid, string pid)
        {
            if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                CyInterfaceDescriptor interfaceDesc = (CyInterfaceDescriptor)node.m_value;
                if (interfaceDesc.bInterfaceClass == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC)
                {
                    Vid = vid;
                    Pid = pid;
                }
            }
            else
            {
                if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.DEVICE))
                {
                    CyDeviceDescriptor deviceDesc = (CyDeviceDescriptor)node.m_value;
                    vid = deviceDesc.idVendor.ToString("X4");
                    pid = deviceDesc.idProduct.ToString("X4");
                }

                for (int i = node.m_nodes.Count-1; i >= 0; i--)
                {
                    SetCdcVidPid(node.m_nodes[i], vid, pid);
                }
            }
        }
        #endregion SetValue

        #region Save tree descriptor
        public void ParamDeviceTreeChanged()
        {
            SerializedDeviceDesc = ParamTreeChanged(m_deviceTree);
        }

        public void ParamStringTreeChanged()
        {

            if (m_deviceTree.m_nodes.Count > 0)
                RecalcDescriptors(m_deviceTree.m_nodes[0]);
            SerializedStringDesc = ParamTreeChanged(m_stringTree);

        }

        public void ParamHIDReportTreeChanged()
        {
            SerializedHIDReportDesc = ParamTreeChanged(m_hidReportTree);
        }

        public void ParamAudioTreeChanged()
        {
            SerializedAudioDesc = ParamTreeChanged(m_audioTree);
            ParamDeviceTreeChanged();
        }

        public void ParamMidiTreeChanged()
        {
            SerializedMidiDesc = ParamTreeChanged(m_midiTree);
            ParamDeviceTreeChanged();
        }

        public void ParamCDCTreeChanged()
        {
            SerializedCDCDesc = ParamTreeChanged(m_cdcTree);
            ParamDeviceTreeChanged();
        }

        private string ParamTreeChanged(CyDescriptorTree tree)
        {
            if (tree.m_nodes.Count > 0)
                RecalcDescriptors(tree.m_nodes[0]);
            return SerializeDescriptorTree(tree);
        }
        #endregion Save tree descriptor

        #region Parameters serialization
        public string SerializeDescriptorTree(CyDescriptorTree tree)
        {
            string serializedXml = "";
            using (StringWriter sw = new StringWriter())
            {
                m_serializer.Serialize(sw, tree, m_customSerNamespace);
                serializedXml = sw.ToString().Replace(Environment.NewLine, " ");
            }
            return serializedXml;
        }

        public static CyDescriptorTree DeserializeDescriptorTree(string serializedXml, XmlSerializer s)
        {
            CyDescriptorTree tree = (CyDescriptorTree)s.Deserialize(new StringReader(serializedXml));
            return tree;
        }

        public void DeserializeDescriptors()
        {
            // Deserialize Device Tree
            if (!string.IsNullOrEmpty(SerializedDeviceDesc))
            {
                try
                {
                    m_deviceTree = DeserializeDescriptorTree(SerializedDeviceDesc, m_serializer);
                    CheckOldFormatCompability(m_deviceTree);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_DEVICEDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(true, false, false, false, false, false);
                }
            }
            else
            {
                InitDescriptors(true, false, false, false, false, false);
            }
            // Deserialize String Tree
            if (!string.IsNullOrEmpty(SerializedStringDesc))
            {
                try
                {
                    m_stringTree = DeserializeDescriptorTree(SerializedStringDesc, m_serializer);
                    CheckStringOldFormatCompability(m_stringTree);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_STRINGDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, true, false, false, false, false);
                }
            }
            else
            {
                InitDescriptors(false, true, false, false, false, false);
            }
            // Deserialize HID Report Tree
            if (!string.IsNullOrEmpty(SerializedHIDReportDesc))
            {
                try
                {
                    m_hidReportTree = DeserializeDescriptorTree(SerializedHIDReportDesc, m_serializer);
                    RestoreHIDReportUsageList();
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_HIDREPORTDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, true, false, false, false);
                }
            }
            else
            {
                InitDescriptors(false, false, true, false, false, false);
            }
            // Deserialize Audio Tree
            if (!string.IsNullOrEmpty(SerializedAudioDesc))
            {
                try
                {
                    m_audioTree = DeserializeDescriptorTree(SerializedAudioDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_AUDIODESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, true, false, false);
                }
            }
            else
            {
                InitDescriptors(false, false, false, true, false, false);
            }

            // Deserialize Midi Tree
            if (!string.IsNullOrEmpty(SerializedMidiDesc))
            {
                try
                {
                    m_midiTree = DeserializeDescriptorTree(SerializedMidiDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_MIDIDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, false, false, true);
                }
            }
            else
            {
                InitDescriptors(false, false, false, false, false, true);
            }

            if (!string.IsNullOrEmpty(SerializedCDCDesc))
            {
                try
                {
                    m_cdcTree = DeserializeDescriptorTree(SerializedCDCDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_CDCDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, false, true, false);
                }
            }
            else
            {
                InitDescriptors(false, false, false, false, true, false);
            }

            // Check if Device tree has audio, midi or cdc interfaces and if so, merge them with audio or cdc interfaces
            // to make one object
            for (int i = 0; i < m_deviceTree.m_nodes[0].m_nodes.Count; i++) //device level
                for (int j = 0; j < m_deviceTree.m_nodes[0].m_nodes[i].m_nodes.Count; j++) // configuration level
                    // alternate level
                    for (int k = 0; k < m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes.Count; k++)
                        // interface level
                        for (int m = 0; m < Math.Min(1, m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].
                                                                            m_nodes[k].m_nodes.Count); m++)
                        {
                            // audio / midi
                            if (m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[m].m_value is
                                CyAudioInterfaceDescriptor)
                            {
                                // audio tree
                                for (int l = 0; l < m_audioTree.m_nodes[0].m_nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].Key ==
                                       m_audioTree.m_nodes[0].m_nodes[l].Key)
                                    {
                                        m_audioTree.m_nodes[0].m_nodes.RemoveAt(l);
                                        m_audioTree.m_nodes[0].m_nodes.Insert(l,
                                                                              m_deviceTree.m_nodes[0].m_nodes[i].
                                                                                  m_nodes[j].m_nodes[k]);
                                        break;
                                    }
                                }

                                // midi tree
                                for (int l = 0; l < m_midiTree.m_nodes[0].m_nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].Key ==
                                       m_midiTree.m_nodes[0].m_nodes[l].Key)
                                    {
                                        m_midiTree.m_nodes[0].m_nodes.RemoveAt(l);
                                        m_midiTree.m_nodes[0].m_nodes.Insert(l,
                                                                              m_deviceTree.m_nodes[0].m_nodes[i].
                                                                                  m_nodes[j].m_nodes[k]);
                                        break;
                                    }
                                }
                            }

                            // cdc
                            else if (m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[m].m_value is
                                     CyCDCInterfaceDescriptor)
                            {
                                for (int l = 0; l < m_cdcTree.m_nodes[0].m_nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].Key ==
                                       m_cdcTree.m_nodes[0].m_nodes[l].Key)
                                    {
                                        m_cdcTree.m_nodes[0].m_nodes.RemoveAt(l);
                                        m_cdcTree.m_nodes[0].m_nodes.Insert(l, m_deviceTree.m_nodes[0].m_nodes[i].
                                                                                  m_nodes[j].m_nodes[k]);
                                        break;
                                    }
                                }
                            }
                        }

            // Reassing Endpoint memory allocation value for compatibility with previous versions
            if (m_deviceTree.m_nodes[0].m_nodes.Count > 0)
            {
                CyDeviceDescriptor node = (CyDeviceDescriptor)m_deviceTree.m_nodes[0].m_nodes[0].m_value;
                if (node.bMemoryMgmt != 0)
                {
                    node.bMemoryMgmt = 0;
                }
                if (node.bMemoryAlloc != 0)
                {
                    try
                    {
                        EPMemoryAlloc = (CyMemoryAllocation)node.bMemoryAlloc;
                    }
                    catch { Debug.Assert(false); }
                    node.bMemoryAlloc = 0;
                }
            }
        }
        #endregion Parameters serialization

        #region Manipulations with String descriptors

        /// <summary>
        /// Finds the index of the string that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the string descriptor</param>
        /// <param name="parameters">Reference to the Parameters</param>
        /// <returns>Unique index of the string</returns>
        public static uint SaveStringDescriptor(ComboBox comboBox, CyUSBFSParameters parameters)
        {
            CyStringDescriptor strDesc = null;
            uint strIndex = 0;

            if (comboBox.Text == "") return strIndex;

            if ((comboBox.SelectedIndex < 0) && (comboBox.Text != ""))
            {
                //Search for string in pre-defined array
                bool predefined = false;
                List<CyStringDescriptor> strList = parameters.GetStringDescList();
                for (int i = 0; i < strList.Count; i++)
                {
                    if (comboBox.Text == strList[i].ToString())
                    {
                        predefined = true;
                        strDesc = strList[i];
                        break;
                    }
                }
                if (!predefined)
                {
                    strDesc = CreateNewStringDescriptor(comboBox.Text, parameters);
                    parameters.ParamStringTreeChanged();
                }
            }
            else
            {
                strDesc = (CyStringDescriptor)comboBox.Items[comboBox.SelectedIndex];
            }

            //General USBDescriptor-based index
            strIndex = GetStringDescriptorIndex(strDesc, parameters);

            return strIndex;
        }

        public static CyStringDescriptor CreateNewStringDescriptor(string strValue, CyUSBFSParameters parameters)
        {
            CyDescriptorNode newNode = parameters.m_stringTree.AddNode(NODEKEY_STRING);
            ((CyStringDescriptor)newNode.m_value).bString = strValue;
            return (CyStringDescriptor)newNode.m_value;
        }

        /// <summary>
        /// This function returns a general USBDescriptor-based index of the String Descriptor.
        /// </summary>
        /// <param name="strDesc"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        public static uint GetStringDescriptorIndex(CyStringDescriptor strDesc, CyUSBFSParameters parameters)
        {
            uint strIndex = 0;
            string strConfigKey = parameters.m_stringTree.GetKeyByNode(strDesc);
            if (strConfigKey != "")
            {
                strIndex = CyDescriptorNode.GetDescriptorIndex(strConfigKey);
            }
            return strIndex;
        }

        /// <summary>
        /// Gets the Serial String descriptor node from the m_stringTree
        /// </summary>
        /// <returns></returns>
        public CyStringDescriptor GetSerialDescriptor()
        {
            CyStringDescriptor res = null;
            if ((m_stringTree != null) &&
                (m_stringTree.m_nodes.Count > 1) &&
                (m_stringTree.m_nodes[1].m_nodes.Count > 0))
            {
                res = (CyStringDescriptor)m_stringTree.m_nodes[1].m_nodes[0].m_value;
            }
            return res;
        }

        public List<CyStringDescriptor> GetStringDescList()
        {
            List<CyStringDescriptor> strList = new List<CyStringDescriptor>();
            for (int i = 1; i < m_stringTree.m_nodes[0].m_nodes.Count; i++)
            {
                CyStringDescriptor strDesc =
                                        (CyStringDescriptor)m_stringTree.m_nodes[0].m_nodes[i].m_value;
                if (strDesc.bString != null)
                {
                    strList.Add(strDesc);
                }
            }
            return strList;
        }

        public List<string> GetStringsList()
        {
            List<CyStringDescriptor> strDescList = GetStringDescList();
            List<string> strList = new List<string>();
            for (int i = 0; i < strDescList.Count; i++)
            {
                strList.Add(strDescList[i].bString);
            }
            return strList;
        }

        public uint SaveStringDescriptor(string value)
        {
            CyStringDescriptor strDesc = null;
            uint strIndex = 0;

            if (value == "") return strIndex;

            //Search for string in predefined array
            bool predefined = false;
            List<CyStringDescriptor> strDescList = GetStringDescList();
            for (int i = 0; i < strDescList.Count; i++)
            {
                if (strDescList[i].bString == value)
                {
                    predefined = true;
                    strDesc = strDescList[i];
                    break;
                }
            }

            if (!predefined)
            {
                strDesc = CreateNewStringDescriptor(value, this);
                ParamStringTreeChanged();
            }

            //General USBDescriptor-based index
            strIndex = GetStringDescriptorIndex(strDesc, this);
            return strIndex;
        }

        /// <summary>
        /// Finds the index of the special string that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the special string descriptor</param>
        /// <param name="type">Reference to the Parameters</param>
        /// <param name="parameters"></param>
        /// <returns>Unique index of the string</returns>
        public static byte SaveSpecialStringDescriptor(ComboBox comboBox, string type, CyUSBFSParameters parameters)
        {
            string strConfigKey = type;
            byte strIndex = 0;
            if ((comboBox.SelectedIndex < 0) && (comboBox.Text != ""))
            {
                CyDescriptorNode newNode;
                if (type == NODEKEY_STRING_SERIAL)
                {
                    newNode = parameters.m_stringTree.GetNodeByKey(strConfigKey);
                    ((CyStringDescriptor)newNode.m_value).bString = comboBox.Text;
                }
                strIndex = Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(strConfigKey));
            }
            else if (comboBox.SelectedIndex >= 0)
            {
                strIndex = Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(strConfigKey));
            }
            return strIndex;
        }


        #endregion Manipulations with String descriptors

        #region Public Static functions

        /// <summary>
        /// Finds the index of the report that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the report</param>
        /// <param name="parameters">Reference to the Parameters</param>
        /// <returns>Unique index of the report</returns>
        public static uint SaveReportDescriptor(ComboBox comboBox, CyUSBFSParameters parameters)
        {
            CyHIDReportDescriptor reportDesc = null;
            string strConfigKey;
            uint strIndex = 0;

            if (comboBox.Text == "") return strIndex;


            reportDesc = (CyHIDReportDescriptor)comboBox.Items[comboBox.SelectedIndex];

            strConfigKey = parameters.m_hidReportTree.GetKeyByNode(reportDesc);
            if (strConfigKey != "")
            {
                strIndex = CyDescriptorNode.GetDescriptorIndex(strConfigKey);
            }
            return strIndex;
        }

        /// <summary>
        /// Determines if the string is a comment (empty sting or starts with "//").
        /// Used in HID reports.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static bool StringIsComment(string str)
        {
            bool res = false;
            if ((str.TrimStart(' ') == "") || str.TrimStart(' ').StartsWith("//"))
            {
                res = true;
            }
            return res;
        }

        public static Int64 ConvertByteArrayToInt(List<byte> byteList, bool isUnsigned)
        {
            Int64 val = 0;
            bool isNegative = false;
            if (byteList.Count > 0)
            {
                if (!isUnsigned && byteList[byteList.Count - 1] > Math.Pow(2, 7))
                    isNegative = true;
                for (int i = byteList.Count; i < 8; i++)
                {
                    if (!isNegative) byteList.Add(0);
                    else byteList.Add(0xFF);
                }
                val = BitConverter.ToInt64(byteList.ToArray(), 0);
            }
            return val;
        }

        public static List<byte> ConvertIntToByteArray(Int64 val, bool isUnsigned)
        {
            List<byte> byteList = new List<byte>(BitConverter.GetBytes(val));
            //Remove extra bytes
            if (val >= 0)
            {
                while ((byteList[byteList.Count - 1] == 0) && (byteList.Count > 1))
                    byteList.RemoveAt(byteList.Count - 1);
            }
            else
            {
                while ((byteList[byteList.Count - 1] == 0xFF) && (byteList.Count > 1))
                    byteList.RemoveAt(byteList.Count - 1);
            }
            //For numbers such as 128(0x80) (with a significant high byte) add one more byte.
            if (!isUnsigned && Math.Abs(val) >= Math.Pow(2, (byteList.Count * 8 - 1)))
            {
                if (val >= 0) byteList.Add(0);
                else byteList.Add(0xFF);
            }
            // If value has 3 bytes, add 4th byte
            if (byteList.Count == 3)
            {
                if (val >= 0) byteList.Add(0);
                else byteList.Add(0xFF);
            }
            return byteList;
        }

        public static List<byte> ConvertInt3ToByteArray(Int64 val)
        {
            List<byte> byteList = ConvertIntToByteArray(val, false);
            while (byteList.Count < 3)
            {
                byteList.Add(0);
            }
            if (byteList.Count > 3)
                byteList.RemoveRange(3, byteList.Count - 3);
            return byteList;
        }

        public static bool CheckIntValue(string str, bool hex)
        {
            bool res;
            Int64 val;
            if (!hex)
            {
                res = Int64.TryParse(str, out val);
            }
            else
            {
                if (str.StartsWith("0x"))
                    str = str.Remove(0, 2);
                res = Int64.TryParse(str, NumberStyles.HexNumber, Application.CurrentCulture.NumberFormat, out val);
            }
            return res;
        }

        public static bool CheckIntRange(int val, int min, int max)
        {
            bool res = ((val >= min) && (val <= max)) ? true : false;
            return res;
        }

        public static void ChangeArrayLength(List<byte> arr, int len)
        {
            if (arr.Count < len)
            {
                int count = arr.Count;
                for (int i = 0; i < len - count; i++)
                    arr.Add(0);
            }
            else if (arr.Count > len)
                arr.RemoveRange(len, arr.Count - len);
        }

        public static int GetEPTransferType(CyEndpointDescriptor epDesc)
        {
            return (epDesc.bmAttributes & 0x03);
        }
        #endregion Public Static functions

        #region Public functions

        /// <summary>
        /// Fills Device, String and HIDReport trees with the default nodes.
        /// </summary>
        /// <param name="device">Apply to the m_deviceTree or no</param>
        /// <param name="str">Apply to the m_stringTree or no</param>
        /// <param name="hidReport">Apply to the m_hidReportTree or no</param>
        public void InitDescriptors(bool device, bool str, bool hidReport, bool audio, bool cdc, bool midi)
        {
            if (device)
            {
                if (m_deviceTree.m_nodes.Count > 0)
                    ParamDeviceTreeChanged();
                m_deviceTree.m_nodes.Clear();
                m_deviceTree.AddNode(NODEKEY_DEVICE);
            }
            if (str)
            {
                if (m_stringTree.m_nodes.Count > 0)
                    ParamStringTreeChanged();
                m_stringTree.m_nodes.Clear();
                m_stringTree.m_nodes.Clear();
                m_stringTree.AddNode(NODEKEY_STRING);
                m_stringTree.AddNode(NODEKEY_SPECIALSTRING);
            }
            if (hidReport)
            {
                if (m_hidReportTree.m_nodes.Count > 0)
                    ParamHIDReportTreeChanged();
                m_hidReportTree.m_nodes.Clear();
                m_hidReportTree.AddNode(NODEKEY_HIDREPORT);
            }
            if (audio)
            {
                if (m_audioTree.m_nodes.Count > 0)
                    ParamAudioTreeChanged();
                m_audioTree.m_nodes.Clear();
                m_audioTree.AddNode(NODEKEY_AUDIO);
            }
            if (cdc)
            {
                if (m_cdcTree.m_nodes.Count > 0)
                    ParamCDCTreeChanged();
                m_cdcTree.m_nodes.Clear();
                m_cdcTree.AddNode(NODEKEY_CDC);
            }
            if (midi)
            {
                if (m_midiTree.m_nodes.Count > 0)
                    ParamMidiTreeChanged();
                m_midiTree.m_nodes.Clear();
                m_midiTree.AddNode(NODEKEY_MIDI);
            }
        }

        /// <summary>
        /// Performs neccessary calculations in the descriptors when editing of descriptors is finished: 
        /// Removes unused controls;
        /// Sets string indexes;
        /// Updates interface numbers;
        /// Other.
        /// </summary>
        /// <param name="node"></param>
        public void RecalcDescriptors(CyDescriptorNode node)
        {
            if (node.Key == NODEKEY_DEVICE)
            {
                //Clean m_emptyFields array
                m_emptyFields.Clear();

                // Reset m_usedEp array 
                for (int i = 0; i < m_usedEp.Length; i++)
                {
                    m_usedEp[i] = false;
                }

                //Reset m_max_interfaces
                MaxInterfaces = 0;
                SetExtJackCount(0);
            }

            for (int i = 0; i < node.m_nodes.Count; i++)
            {
                CyDescriptorNode node_child = node.m_nodes[i];
                if (node_child.m_value != null)
                {
                    switch (node_child.m_value.bDescriptorType)
                    {
                        case CyUSBDescriptorType.DEVICE:
                            CyDeviceDescriptor deviceDescriptor = (CyDeviceDescriptor) node_child.m_value;
                            deviceDescriptor.bNumConfigurations = (byte) node_child.m_nodes.Count;
                            deviceDescriptor.iManufacturer = GetStringLocalIndex(deviceDescriptor.iwManufacturer);
                            deviceDescriptor.iProduct = GetStringLocalIndex(deviceDescriptor.iwProduct);
                            deviceDescriptor.sManufacturer = GetStringDescTextByIndex(deviceDescriptor.iwManufacturer);
                            deviceDescriptor.sProduct = GetStringDescTextByIndex(deviceDescriptor.iwProduct);
                            deviceDescriptor.sSerialNumber = (GetSerialDescriptor()).bString;
                            break;
                        case CyUSBDescriptorType.CONFIGURATION:
                            CyConfigDescriptor configDescriptor = (CyConfigDescriptor) node_child.m_value;
                            configDescriptor.bNumInterfaces = GetInterfaceCount(node_child);

                            // Calculate max_interfaces 
                            if (configDescriptor.bNumInterfaces > MaxInterfaces)
                            {
                                MaxInterfaces = configDescriptor.bNumInterfaces;
                            }
                            // Calculate bConfigurationValue
                            int configIndex = node.m_nodes.IndexOf(node_child);
                            if (configIndex >= 0)
                                configDescriptor.bConfigurationValue = (byte) configIndex;
                            else
                                configDescriptor.bConfigurationValue = 0;

                            configDescriptor.iConfiguration = GetStringLocalIndex(configDescriptor.iwConfiguration);
                            configDescriptor.sConfiguration = 
                                GetStringDescTextByIndex(configDescriptor.iwConfiguration);
                            // Calculate the total length
                            ushort totalLength = configDescriptor.bLength;
                            for (int j = 0; j < node_child.m_nodes.Count; j++)
                            {
                                CyDescriptorNode node_in_config = node_child.m_nodes[j];
                                totalLength += node_in_config.m_value.bLength;
                                for (int k = 0; k < node_in_config.m_nodes.Count; k++)
                                {
                                    CyDescriptorNode node_in_interfaces = node_in_config.m_nodes[k];
                                    totalLength += node_in_interfaces.m_value.bLength;
                                    for (int l = 0; l < node_in_interfaces.m_nodes.Count; l++)
                                    {
                                        CyDescriptorNode node_in_interface = node_in_interfaces.m_nodes[l];
                                        totalLength += node_in_interface.m_value.bLength;
                                        for (int m = 0; m < node_in_interface.m_nodes.Count; m++)
                                        {
                                            CyDescriptorNode node_in_endpoint = node_in_interface.m_nodes[m];
                                            totalLength += node_in_endpoint.m_value.bLength;
                                        }
                                    }
                                }
                            }
                            configDescriptor.wTotalLength = totalLength;
                            break;
                        case CyUSBDescriptorType.INTERFACE:
                            CyInterfaceDescriptor interfaceDescriptor = (CyInterfaceDescriptor)node_child.m_value;
                            //Calculate the number of Endpoints
                            byte numEndpt = 0;
                            for (int j = 0; j < node_child.m_nodes.Count; j++)
                            {
                                CyDescriptorNode node_endpt = node_child.m_nodes[j];
                                if (node_endpt.m_value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                                    numEndpt++;
                            }
                            //Calculate the number of External MIDI IN Jack, OUT Jack
                            if ((interfaceDescriptor.bInterfaceClass == 
                                 (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO) &&
                                (interfaceDescriptor.bInterfaceSubClass == 
                                 (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING))
                            {
                                byte numExtMidiIN = 0;
                                byte numExtMidiOUT = 0;
                                for (int j = 0; j < node_child.m_nodes.Count; j++)
                                {
                                    CyDescriptorNode node_jack = node_child.m_nodes[j];
                                    if (node_jack.m_value is CyMSInJackDescriptor)
                                    {
                                        if (((CyMSInJackDescriptor)node_jack.m_value).bJackType == 
                                              CyUSBOtherTypes.CyJackTypes.EXTERNAL)
                                            numExtMidiIN++;
                                    }
                                    else if (node_jack.m_value is CyMSOutJackDescriptor)
                                    {
                                        if (((CyMSOutJackDescriptor)node_jack.m_value).bJackType == 
                                              CyUSBOtherTypes.CyJackTypes.EXTERNAL)
                                            numExtMidiOUT++;
                                    }
                                }
                                SetExtJackCount(Math.Max(m_extJackCount, Math.Max(numExtMidiIN, numExtMidiOUT)));
                            }
                            interfaceDescriptor.bNumEndpoints = numEndpt;
                            interfaceDescriptor.iInterface = GetStringLocalIndex(interfaceDescriptor.iwInterface);
                            interfaceDescriptor.sInterface = GetStringDescTextByIndex(interfaceDescriptor.iwInterface);
                            // Set Interface Protocol for Audio 2.0
                            if (interfaceDescriptor.bInterfaceClass == 
                                 (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO) 
                            {
                                bool isAudio20 = false;
                                for (int j = 0; j < node_child.m_nodes.Count; j++)
                                {
                                    CyDescriptorNode node_cs = node_child.m_nodes[j];
                                    if ((node_cs.m_value.GetType()).ToString().EndsWith("_v2"))
                                    {
                                        isAudio20 = true;
                                        break;
                                    }
                                }
                                interfaceDescriptor.bInterfaceProtocol = isAudio20 ?
                                    (byte)CyUSBOtherTypes.CyAudioInterfaceProtocolCodes.IP_VERSION_02_00 : 
                                    (byte)CyUSBOtherTypes.CyAudioInterfaceProtocolCodes.INTERFACE_PROTOCOL_UNDEFINED;
                            }
                            
                            break;
                        case CyUSBDescriptorType.HID:
                            CyHIDDescriptor hidDescriptor = (CyHIDDescriptor)node_child.m_value;
                            hidDescriptor.bNumDescriptors = 1;
                            hidDescriptor.bReportIndex = GetHIDReportLocalIndex(hidDescriptor.wReportIndex);

                            // Calculate wDescriptorLength
                            string reportKey = CyDescriptorNode.GetKeyByIndex(hidDescriptor.wReportIndex);
                            CyDescriptorNode nodeHIDReport = m_hidReportTree.GetNodeByKey(reportKey);
                            if (nodeHIDReport != null)
                            {
                                hidDescriptor.wDescriptorLength = 
                                                                ((CyHIDReportDescriptor)nodeHIDReport.m_value).wLength;
                            }
                            else
                            {
                                hidDescriptor.wReportIndex = 0;
                            }

                            if ((hidDescriptor.wReportIndex == 0) && (!m_emptyFields.Contains(node_child.Key)))
                                m_emptyFields.Add(node_child.Key);
                            break;
                        case CyUSBDescriptorType.ENDPOINT:
                            CyEndpointDescriptor endpointDescriptor = (CyEndpointDescriptor)node_child.m_value;
                            byte endpointNum = (byte)(endpointDescriptor.bEndpointAddress & 0x0F);
                            if (endpointNum < m_usedEp.Length)
                                m_usedEp[endpointNum] = true;
                            break;
                        case CyUSBDescriptorType.HID_REPORT:
                            CyHIDReportDescriptor hidRptDescriptor = (CyHIDReportDescriptor)node_child.m_value;
                            ushort rptSize = 0;
                            for (int j = 0; j < node_child.m_nodes.Count; j++)
                            {
                                CyDescriptorNode node_in_report = node_child.m_nodes[j];
                                rptSize += ((CyHIDReportItemDescriptor)node_in_report.m_value).Item.GetItemSize();
                            }
                            hidRptDescriptor.wLength = rptSize;
                            break;
                        case CyUSBDescriptorType.AUDIO:
                            // String indexes
                            try
                            {
                                Type nodeType = node_child.m_value.GetType();
                                FieldInfo[] fi = nodeType.GetFields();
                                for (int j = 0; j < fi.Length; j++)
                                {
                                    if (fi[j].Name.StartsWith("iw"))
                                    {
                                        uint val = (uint) fi[j].GetValue(node_child.m_value);
                                        string propName = fi[j].Name.Remove(0, 2).Insert(0, "i");
                                        PropertyInfo pi = nodeType.GetProperty(propName);
                                        if (pi != null)
                                            pi.SetValue(node_child.m_value, GetStringLocalIndex(val), null);
                                    }
                                }
                            }
                            catch (Exception ex)
                            {
                                Debug.Assert(false, ex.ToString());
                            }
                            node_child.m_value.UpdateLength();

                            // Calculate the total length of CyACHeaderDescriptor
                            if ((node_child.m_value is CyACHeaderDescriptor) || 
                                (node_child.m_value is CyACHeaderDescriptor_v2) ||
                                (node_child.m_value is CyMSHeaderDescriptor))
                            {
                                ushort totalLengthAudio = 0;
                                for (int j = 0; j < node.m_nodes.Count; j++)
                                {
                                    CyDescriptorNode node_audio = node.m_nodes[j];
                                    if (node_audio.m_value.bDescriptorType == CyUSBDescriptorType.AUDIO)
                                    {
                                        node_audio.m_value.UpdateLength();
                                        totalLengthAudio += node_audio.m_value.bLength;
                                    }
                                }
                                if (node_child.m_value is CyACHeaderDescriptor)
                                {
                                    CyACHeaderDescriptor acHeaderDesc = (CyACHeaderDescriptor) node_child.m_value;
                                    acHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                                else if (node_child.m_value is CyACHeaderDescriptor_v2)
                                {
                                    CyACHeaderDescriptor_v2 acHeaderDesc = (CyACHeaderDescriptor_v2)node_child.m_value;
                                    acHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                                else if (node_child.m_value is CyMSHeaderDescriptor)
                                {
                                    CyMSHeaderDescriptor msHeaderDesc = (CyMSHeaderDescriptor)node_child.m_value;
                                    msHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                            }

                            break;
                    }
                }
                RecalcDescriptors(node_child);
            }
        }

        /// <summary>
        /// Calculates the total packet size of the Configuration Descriptor.
        /// </summary>
        /// <param name="configNode">The Configuration Descriptor</param>
        /// <returns>Total packet size</returns>
        public ushort GetSumPacketSize(CyDescriptorNode configNode)
        {
            ushort totalSize = 0;
            for (int i = 0; i < configNode.m_nodes.Count; i++)
                for (int j = 0; j < configNode.m_nodes[i].m_nodes.Count; j++)
                {
                    CyDescriptorNode node_in_interface = configNode.m_nodes[i].m_nodes[j];
                
                    if (node_in_interface.m_value is CyEndpointDescriptor)
                    {
                        totalSize += ((CyEndpointDescriptor)node_in_interface.m_value).wMaxPacketSize;
                    }
                }
            return totalSize;
        }

        public bool CheckBootloaderReady()
        {
            bool res = false;
            // Parse device tree for all Interface descriptors and check if exists any one that has 
            // at least two endpoints: one In(EP2, MaxPktSize=64) and one Out(EP1, MaxPktSize=64).
            for (int i = 0; i < m_deviceTree.m_nodes[0].m_nodes.Count; i++)//device level
            {
                for (int j = 0; j < m_deviceTree.m_nodes[0].m_nodes[i].m_nodes.Count; j++) // configuration level
                {
                    // alternate level
                    for (int k = 0; k < m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes.Count; k++) 
                    {
                        // interface level
                        for (int m = 0; m < m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].m_nodes.Count; m++)
                        {
                            CyDescriptorNode node = m_deviceTree.m_nodes[0].m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[m];
                            CyInterfaceDescriptor desc = (CyInterfaceDescriptor) node.m_value;
                            
                            bool foundIN = false;
                            bool foundOUT = false;
                            for (int l = 0; l < node.m_nodes.Count; l++)
                            {
                                if (node.m_nodes[l].m_value is CyEndpointDescriptor)
                                {
                                    CyEndpointDescriptor endptDesc = (CyEndpointDescriptor) node.m_nodes[l].m_value;
                                    if ((endptDesc.EndpointNum == CyUSBOtherTypes.CyEndptNumbers.EP1) &&
                                        (endptDesc.Direction == CyUSBOtherTypes.CyEndptDirections.OUT) &&
                                        (endptDesc.TransferType ==
                                                    CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT) &&
                                        (endptDesc.wMaxPacketSize == CyEndpointDescriptor.MAX_PACKET_SIZE_GEN))
                                    {
                                        foundOUT = true;
                                    }
                                    else if ((endptDesc.EndpointNum == CyUSBOtherTypes.CyEndptNumbers.EP2) &&
                                             (endptDesc.Direction == CyUSBOtherTypes.CyEndptDirections.IN) &&
                                             (endptDesc.TransferType ==
                                                    CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT) &&
                                             (endptDesc.wMaxPacketSize == CyEndpointDescriptor.MAX_PACKET_SIZE_GEN))
                                    {
                                        foundIN = true;
                                    }
                                }
                            }
                            if (foundIN && foundOUT)
                            {
                                res = true;
                                break;
                            }
                        }
                        if (res) break;
                    }
                    if (res) break;
                }
                if (res) break;
            }
            return res;
        }

        public bool CheckSiliconRevisionForDMA(ICyDeviceQuery_v1 deviceQuery, out string selOption)
        {
            bool res = true;
            bool supportDMA = true;
            selOption = "";

            if (!supportDMA)
            {
                if (EPMemoryMgmt == CyMemoryManagement.EP_DMAauto)
                {
                    res = false;
                    selOption = "DMA w/Automatic Memory Mgmt";
                }
            }
            return res;
        }

        public void SetNodesISerialNumber()
        {
            bool m_showSerial = (GetSerialDescriptor()).bUsed;
            if (!m_showSerial)
            {
                // Set Serial Number in DeviceDescriptor to zero
                try
                {
                    for (int i = 0; i < m_deviceTree.m_nodes[0].m_nodes.Count; i++)
                    {
                        ((CyDeviceDescriptor)m_deviceTree.m_nodes[0].m_nodes[i].m_value).iSerialNumber = 0;
                    }
                }
                catch (Exception)
                {
                    Debug.Assert(false);
                }
            }
            else
            {
                for (int i = 0; i < m_deviceTree.m_nodes[0].m_nodes.Count; i++)
                {
                    ((CyDeviceDescriptor)m_deviceTree.m_nodes[0].m_nodes[i].m_value).iSerialNumber =
                       Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(CyUSBFSParameters.NODEKEY_STRING_SERIAL));
                }
            }
        }

        /// <summary>
        /// Generate error when Endpoint MaxPacketSize is greater then 512 and EMM is not "DMA w/AutomaticMM".
        /// </summary>
        public bool CheckEPMaxPacketSize(CyDescriptorNode node)
        {
            bool res = true;

            if (EPMemoryMgmt == CyMemoryManagement.EP_DMAauto) 
                return true;
            
            if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                CyEndpointDescriptor desc = (CyEndpointDescriptor)node.m_value;
                if (desc.wMaxPacketSize > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    res &= CheckEPMaxPacketSize(node.m_nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when  total sum of the MaxPacketSize for all EPs in one Device is greater then 512 
        /// when EMM is not "DMA w/AutomaticMM".
        /// </summary>
        public bool CheckSumEPMaxPacketSize(CyDescriptorNode node)
        {
            bool res = true;

            if (EPMemoryMgmt == CyMemoryManagement.EP_DMAauto)
                return true;

            if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                int sum = 0;
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    if (node.m_nodes[i].m_value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                    {
                        CyEndpointDescriptor desc = (CyEndpointDescriptor)node.m_nodes[i].m_value;
                        sum += desc.wMaxPacketSize;
                    }
                }
                if (sum > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    res &= CheckSumEPMaxPacketSize(node.m_nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when  total sum of the MaxPacketSize for all EPs in one Device is greater then 1100. 
        /// </summary>
        public bool CheckSumEPMaxPacketSizeAll(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                int sum = 0;
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    if (node.m_nodes[i].m_value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                    {
                        CyEndpointDescriptor desc = (CyEndpointDescriptor)node.m_nodes[i].m_value;
                        sum += desc.wMaxPacketSize;
                    }
                }
                if (sum > CyEndpointDescriptor.MAX_PACKET_SIZE_SUM_DEVICE)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    res &= CheckSumEPMaxPacketSizeAll(node.m_nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Bulk Endpoint MaxPacketSize is not from the list {8, 16, 32, 64}.
        /// </summary>
        public bool CheckEPBulkMaxPacketSize(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.m_value != null) && (node.m_value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                CyEndpointDescriptor desc = (CyEndpointDescriptor)node.m_value;
                if ((desc.TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK) &&
                    (CyEndpointDescriptor.PossibleMaxPacketValues.Contains(desc.wMaxPacketSize) == false))
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.m_nodes.Count; i++)
                {
                    res &= CheckEPBulkMaxPacketSize(node.m_nodes[i]);
                }
            }
            return res;
        }

        #endregion Public functions

        #region Private functions

        /// <summary>
        /// Returns the index of the String Descriptor in the array of String Descriptors. 
        /// This index is used in API generation.
        /// </summary>
        /// <param name="keyIndex">Unique internal index</param>
        /// <returns>Index that is used in API generation</returns>
        private byte GetStringLocalIndex(uint keyIndex)
        {
            byte localIndex = 0;
            if (keyIndex > 0)
            {
                for (byte i = 0; i < m_stringTree.m_nodes[0].m_nodes.Count; i++)
                {
                    if (CyDescriptorNode.GetDescriptorIndex(m_stringTree.m_nodes[0].m_nodes[i].Key) == keyIndex)
                    {
                        localIndex = i;
                        break;
                    }
                }
            }
            return localIndex;
        }

        private string GetStringDescTextByIndex(uint keyIndex)
        {
            string res = null;
            if (keyIndex > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(keyIndex);
                CyDescriptorNode node = m_stringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    res = ((CyStringDescriptor)node.m_value).bString;
                }
            }
            return res;
        }

        /// <summary>
        /// Returns the index of the HID Report Descriptor in the array of HID Report Descriptors. 
        /// This index is used in API generation.
        /// </summary>
        /// <param name="keyIndex">Unique internal index</param>
        /// <returns>Index that is used in API generation</returns>
        private byte GetHIDReportLocalIndex(uint keyIndex)
        {
            byte localIndex = 0;
            if (keyIndex > 0)
            {
                for (byte i = 0; i < m_hidReportTree.m_nodes[0].m_nodes.Count; i++)
                {
                    if (CyDescriptorNode.GetDescriptorIndex(m_hidReportTree.m_nodes[0].m_nodes[i].Key) == keyIndex)
                    {
                        localIndex = (byte) (i + 1);
                        break;
                    }
                }
            }
            return localIndex;
        }

        /// <summary>
        /// Calculates the number of interfaces in Configuration descriptor
        /// </summary>
        /// <param name="configNode"></param>
        /// <returns></returns>
        public static byte GetInterfaceCount(CyDescriptorNode configNode)
        {
            byte count = 0;
            for (int j = 0; j < configNode.m_nodes.Count; j++)
            {
                if (configNode.m_nodes[j].m_value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
                    count++;
            };
            return count;
        }

        /// <summary>
        /// For compability with the previous versions, checks 
        /// the presence of the ALTERNATE node in the Device Descriptor tree.
        /// </summary>
        /// <param name="dTree">Device Descriptor tree</param>
        private void CheckOldFormatCompability(CyDescriptorTree dTree)
        {
            bool oldFormat = false;
            for (int i = 0; i < dTree.m_nodes.Count; i++) // Level 1
                for (int j = 0; j < dTree.m_nodes[i].m_nodes.Count; j++) // Level 2 - Device
                    for (int k = 0; k < dTree.m_nodes[i].m_nodes[j].m_nodes.Count; k++) // Level 3 - Configuration
                        for (int m = 0; m < dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes.Count; m++) // Level 4 - Int.
                        {
                            CyDescriptorNode node = dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[m];
                            if ((node.m_value.bDescriptorType != CyUSBDescriptorType.ALTERNATE) &&
                                (node.m_value.bDescriptorType != CyUSBDescriptorType.INTERFACE_ASSOCIATION))
                            {
                                oldFormat = true;
                            }
                        }
            //If the tree is in old format, add a node layer
            if (oldFormat)
            {
                for (int i = 0; i < dTree.m_nodes.Count; i++) // Level 1
                    for (int j = 0; j < dTree.m_nodes[i].m_nodes.Count; j++) // Level 2 - Device
                        for (int k = 0; k < dTree.m_nodes[i].m_nodes[j].m_nodes.Count; k++) // Level 3 - Configuration
                        {
                            // Search for interface numbers
                            List<byte> interfaceNums = new List<byte>();
                            for (int m = 0; m < dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes.Count; m++)
                                // Level 4 - Interface
                            {
                                CyDescriptorNode node = dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[m];
                                byte interfaceNum = ((CyInterfaceDescriptor) node.m_value).bInterfaceNumber;
                                if (!interfaceNums.Contains(interfaceNum))
                                    interfaceNums.Add(interfaceNum);
                            }
                            interfaceNums.Sort();

                            // Add interfaces to tree and attach alternate to them
                            for (int m = 0; m < interfaceNums.Count; m++)
                            {
                                CyDescriptorNode newNode = dTree.AddNode(dTree.m_nodes[i].m_nodes[j].m_nodes[k].Key);
                                newNode.m_nodes.Clear();
                                for (int n = 0; n < dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes.Count; n++)
                                {
                                    CyDescriptorNode interfaceNode = dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes[n];
                                    if ((interfaceNode.m_value.bDescriptorType == CyUSBDescriptorType.INTERFACE) &&
                                        (((CyInterfaceDescriptor) interfaceNode.m_value).bInterfaceNumber ==
                                         interfaceNums[m]))
                                    {
                                        dTree.m_nodes[i].m_nodes[j].m_nodes[k].m_nodes.Remove(interfaceNode);
                                        newNode.m_nodes.Add(interfaceNode);
                                        n--;
                                    }
                                }
                            }
                        }
            }
        }

        /// <summary>
        /// For compability with the previous versions, checks
        /// if MS OS String Descriptor has the constant value. 
        /// </summary>
        /// <param name="sTree">String Descriptor tree</param>
        private void CheckStringOldFormatCompability(CyDescriptorTree sTree)
        {
            // Check if MS OS String Descriptor has its default value
            ((CyStringDescriptor) sTree.m_nodes[1].m_nodes[1].m_value).bString = CyUSBFSParameters.MSOS_STRING;
        }

        /// <summary>
        /// For compatibility with previous versions, assigns correct 
        /// usage values list to USAGE HID report items.
        /// </summary>
        private void RestoreHIDReportUsageList()
        {
            for (int i = 0; i < m_hidReportTree.m_nodes[0].m_nodes.Count; i++)
			{
                UInt16 lastUsagePage = 0;
                for (int j = 0; j < m_hidReportTree.m_nodes[0].m_nodes[i].m_nodes.Count; j++)
                {
                    try
                    {
                        CyHidReportItem item =
                            ((CyHIDReportItemDescriptor)m_hidReportTree.m_nodes[0].m_nodes[i].m_nodes[j].m_value).Item;
                        if ((item.Name == CyHidReportItem.RPTITEM_USAGE_PAGE) && (item.m_value.Count == 2))
                        {
                            lastUsagePage = item.m_value[1];
                        }
                        if ((item.Name == CyHidReportItem.RPTITEM_USAGE) && 
                            (item.m_valuesList.Count == CyHIDReportItemTables.ValuesGenericDesktopPage.Length/2))
                        {
                            CyHidDescriptorPage.SetListForItem(item, lastUsagePage);
                        }
                    }
                    catch
                    {
                        Debug.Assert(false);
                    }
                }
			}
        }

        /// <summary>
        /// Generates the list of strings available in the drop down list in property grid. 
        /// The list needs to be updated each time when string descriptors are changed
        /// </summary>
        public void RefreshStringsDropDownList()
        {
            CyStringDescConverter.m_strDescList = GetStringsList();
        }

        private static string GetTemplateFileExt(CyUSBDescriptorType kind, bool open)
        {
            string ext = String.Empty;
            switch (kind)
            {
                case CyUSBDescriptorType.DEVICE:
                    ext = "Device Descriptor Template Files (*.dev.xml)|*.dev.xml|";
                    break;
                case CyUSBDescriptorType.CONFIGURATION:
                    ext = "Configuration Descriptor Template Files (*.cfg.xml)|*.cfg.xml|";
                    break;
                case CyUSBDescriptorType.INTERFACE:
                    ext = "Interface Descriptor Template Files (*.inf.xml)|*.inf.xml|";
                    break;
                case CyUSBDescriptorType.HID_REPORT:
                    ext = "HID Template Files (*.hid.xml)|*.hid.xml|";
                    if (open)
                        ext += "HID Descriptor Tool (*.hid, *.dat, *.h)|*.hid;*.dat;*.h|";
                    break;
                case CyUSBDescriptorType.AUDIO:
                    ext = "Audio Interface Descriptor Template Files (*.audio.xml)|*.audio.xml|";
                    break;
                case CyUSBDescriptorType.MIDI:
                    ext = "MIDI Interface Descriptor Template Files (*.midi.xml)|*.midi.xml|";
                    break;
                case CyUSBDescriptorType.CDC:
                    ext = "CDC Interface Descriptor Template Files (*.cdc.xml)|*.cdc.xml|";
                    break;
                case CyUSBDescriptorType.ALL:
                    ext = "Descriptor Tree Template Files (*.root.xml)|*.root.xml|";
                    break;
            }
            return ext;
        }
  
        private static string GetTemplateDir()
        {
            DirectoryInfo di = new DirectoryInfo(TEMPLATE_DIR);
            return di.FullName;
        }

        public List<string> GetHIDTemplateFilesList()
        {
            List<string> files = new List<string>();
            string appDir = Application.StartupPath;
            string templatePath = Path.Combine(appDir, TEMPLATE_DIR);
            if (Directory.Exists(templatePath))
            {
                string[] filePaths = Directory.GetFiles(templatePath, "*.hid.xml", SearchOption.AllDirectories);
                files.AddRange(filePaths);
            }
            return files;
        }

        #endregion Private functions
    }

    //=================================================================================================================
    /// <summary>
    /// Describes a kind of Settings Panel for the HID Report Item.
    /// </summary>
    [XmlType("HIDReportItemKind")]
    public enum CyHidReportItemKind
    {
        [XmlEnum("Bits"), Description("Bits")]
        BITS,
        [XmlEnum("List"), Description("List")]
        LIST,
        [XmlEnum("Int"), Description("Int")]
        INT,
        [XmlEnum("Unit"), Description("Unit")]
        UNIT,
        [XmlEnum("None"), Description("None")]
        NONE,
        [XmlEnum("Custom"), Description("Custom")]
        CUSTOM
    } ;

    //=================================================================================================================

    #region CyCustomToolStripColors class
    /// <summary>
    /// CyCustomToolStripColors class is used to define colors for the toolStripMenu 
    /// </summary>
    internal class CyCustomToolStripColors : ProfessionalColorTable
    {
        public override Color ToolStripGradientBegin
        {
            get { return SystemColors.Control; }
        }

        public override Color ToolStripGradientMiddle
        {
            get { return SystemColors.Control; }
        }

        public override Color ToolStripGradientEnd
        {
            get { return SystemColors.ControlDark; }
        }

        public override Color ToolStripBorder
        {
            get { return SystemColors.ControlDark; }
        }

        public override Color ToolStripPanelGradientEnd
        {
            get { return SystemColors.ControlDark; }
        }
    }

    #endregion CyCustomToolStripColors class


    static class CyEnumTool
    {
        /// <summary>
        /// Converts enum description to value
        /// </summary>
        /// <param name="value"></param>
        /// <param name="_enumType"></param>
        /// <returns></returns>
        public static object GetEnumValue(object value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value.ToString() == (string)dna.Description))
                    return Enum.Parse(_enumType, fi.Name);
            }
            return Enum.Parse(_enumType, value.ToString());
        }

        /// <summary>
        /// Converts enum value to description
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string GetEnumDesc(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }

        /// <summary>
        /// Gets all enum descriptions
        /// </summary>
        /// <param name="_enumType"></param>
        /// <returns></returns>
        public static string[] GetEnumDescList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetEnumDesc(item));
            }
            return res.ToArray();
        }

        public static void ChangeBrowsableAttributeValue(object sender, string propertyName, bool newValue)
        {
            try
            {
                PropertyDescriptor descriptor = TypeDescriptor.GetProperties(sender.GetType())[propertyName];
                BrowsableAttribute attribute = (BrowsableAttribute)
                                              descriptor.Attributes[typeof(BrowsableAttribute)];
                FieldInfo fieldToChange = attribute.GetType().GetField("browsable",
                                                 System.Reflection.BindingFlags.NonPublic |
                                                 System.Reflection.BindingFlags.Instance);
                fieldToChange.SetValue(attribute, newValue);
            }
            catch
            {
                Debug.Assert(false);
            }
        }
    }
    //=================================================================================================================

}
