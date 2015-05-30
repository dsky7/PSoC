/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace I2C_LCD_v1_0
{
    [Serializable]
    public class CyCommandRow
    {
        [XmlElement("CommandSize")]
        public byte? m_cmdSize;
        [XmlElement("DataSize")]
        public byte? m_dataSize;
        [XmlElement("CmdByte1")]
        public byte? m_cmdByte1;
        [XmlElement("CmdByte2")]
        public byte? m_cmdByte2;
        [XmlElement("CmdByte3")]
        public byte? m_cmdByte3;
        [XmlElement("CmdByte4")]
        public byte? m_cmdByte4;

        #region Constructor(s)
        public CyCommandRow() { }
        public CyCommandRow(byte? cmdSize, byte? dataSize, byte? cmdByte1, byte? cmdByte2, byte? cmdByte3,
            byte? cmdByte4)
        {
            this.m_cmdSize = cmdSize;
            this.m_dataSize = dataSize;
            this.m_cmdByte1 = cmdByte1;
            this.m_cmdByte2 = cmdByte2;
            this.m_cmdByte3 = cmdByte3;
            this.m_cmdByte4 = cmdByte4;
        }
        #endregion
    }

    [Serializable]
    public class CyRequiredCommandRow : CyCommandRow
    {
        [XmlIgnore]
        public string m_cmdDescription;
        [XmlIgnore]
        public bool m_isDataSizeReadOnly = true;
        [XmlIgnore]
        public string m_cmdName;

        #region Constructor(s)
        public CyRequiredCommandRow() { }
        public CyRequiredCommandRow(byte? cmdSize, byte? dataSize, bool isDataSizeReadOnly,
            byte? cmdByte1, byte? cmdByte2, byte? cmdByte3, byte? cmdByte4, string cmdName, string cmdDescription)
            : base(cmdSize, dataSize, cmdByte1, cmdByte2, cmdByte3, cmdByte4)
        {
            this.m_isDataSizeReadOnly = isDataSizeReadOnly;
            this.m_cmdDescription = cmdDescription;
            this.m_cmdName = cmdName;
        }
        #endregion
    }

    [Serializable]
    public class CyCustomCommandRow : CyCommandRow
    {
        [XmlElement("Enable")]
        public bool m_enable;
        [XmlElement("APIName")]
        public string m_apiName;

        #region Constructor(s)
        public CyCustomCommandRow() { }
        public CyCustomCommandRow(bool enable, byte? cmdSize, byte? dataSize, byte? cmdByte1, byte? cmdByte2, byte?
            cmdByte3, byte? cmdByte4, string apiName)
            : base(cmdSize, dataSize, cmdByte1, cmdByte2, cmdByte3, cmdByte4)
        {
            this.m_enable = enable;
            this.m_apiName = apiName;
        }
        #endregion
    }
}
