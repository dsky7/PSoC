// ========================================
//
// Copyright Cypress Semiconductor Corporation, 2009
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF CYPRESS.
//
// Use of this file is governed
// by the license agreement included in the file
//
//     <install>/license/license.txt
//
// where <install> is the Cypress software
// installation root directory path.
//
// ========================================

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace StaticSegLCD_v1_30
{
    partial class M_APIGenerator
    {
        #region Write7SegDisp
        void Write7SegDigit_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            //writer_h.WriteLine("#ifndef " + m_instanceName + "_7SEG");
            writer_h.WriteLine("#define " + m_instanceName + "_7SEG");
            writer_h.WriteLine("void " + m_instanceName + "_Write7SegDigit_" + index + "(uint8 digit, uint8 position);");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_Write7SegDigit_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 4-bit Hex digit in the range of");
            writer.WriteLine("*  0-9 and A-F 7 segment display. The user must have defined what");
            writer.WriteLine("*  portion of the displays segments make up the 7 segment display");
            writer.WriteLine("*  portion in the component wizard. Multiple, separate 7 segment");
            writer.WriteLine("*  displays can be created in the frame buffer and are addressed");
            writer.WriteLine("*  through the index (n) in the function name. Function/s only included");
            writer.WriteLine("*  if component 7 segment wizard defines the 7 segment option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  digit : unsigned integer value in the range of 0 to 15 to");
            writer.WriteLine("*  be displayed as a hexadecimal digit. ");
            writer.WriteLine("*  position : Position of the digit as counted right to left");
            writer.WriteLine("*  starting at 0 on the right. If the defined display does not");
            writer.WriteLine("*  contain a digit in the position then the digit will not be");
            writer.WriteLine("*  displayed");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");

            writer.WriteLine("void " + m_instanceName + "_Write7SegDigit_" + index + "(uint8 digit, uint8 position)");
            writer.WriteLine("{");
            writer.WriteLine("    uint8 i, Val;");
            writer.WriteLine("");
            writer.WriteLine("    if(digit <= 16)  /* Do nothing: digit = digit */ ;");
            writer.WriteLine("");
            writer.WriteLine("    else if(digit <= 0x39)");
            writer.WriteLine("        digit -= 0x30;");
            writer.WriteLine("    else if(digit <= 0x47)");
            writer.WriteLine("        digit -= 0x37;");
            writer.WriteLine("    else");
            writer.WriteLine("        digit = 8;");
            writer.WriteLine("");
			writer.WriteLine("    position = position % " + m_instanceName + "_DigitNum_" + index + ";");
			writer.WriteLine("    position = " + m_instanceName + "_DigitNum_" + index + " - position - 1;");
            writer.WriteLine("    for (i = 0; i < 7; i++)");
            writer.WriteLine("    {");
            writer.WriteLine("        Val = ((" + m_instanceName + "_7SegDigits[digit] >> i) & 0x01); ");
            writer.WriteLine("        " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[position][i], Val);");
            writer.WriteLine("    }");
            writer.WriteLine("}");
        }

        void Write7SegNumber_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            writer_h.WriteLine("void " + m_instanceName + "_Write7SegNumber_" + index + "(uint16 Value, uint8 position, uint8 mode);");
            //writer_h.WriteLine("#endif /* " + m_instanceName + "_7SEG */");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_Write7SegNumber_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays a 16-bit integer value on a 1 to 5");
            writer.WriteLine("*  digit 7 segment display. The user must have defined what portion of");
            writer.WriteLine("*  the displays segments make up the 7 segment display portion In");
            writer.WriteLine("*  the wizard. Multiple, separate 7 segment displays can be created in");
            writer.WriteLine("*  the frame buffer and are addressed through the index (n) in the");
            writer.WriteLine("*  function name. Function/s only included if component 7 segment");
            writer.WriteLine("*  wizard defines the 7 segment option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  Value : unsigned integer value to be displayed.");
            writer.WriteLine("*  position : Position of the least significant digit as");
            writer.WriteLine("*  counted right to left starting at 0 on the right. If the defined");
            writer.WriteLine("*  display contains fewer digits then the Value requires for");
            writer.WriteLine("*  display for the most significant digit/s will not be displayed");
            writer.WriteLine("*  mode : 0=no leading 0s are displayed, 1= leading 0s are  displayed.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_Write7SegNumber_" + index + "(uint16 Value, uint8 position, uint8 mode)");
            writer.WriteLine("{ ");
            writer.WriteLine("    int8 i, Num;");
            writer.WriteLine("");
            writer.WriteLine("    if (Value == 0)");
            writer.WriteLine("    {");
            writer.WriteLine("        if (mode == 0) " + m_instanceName + "_Write7SegDigit_" + index + "(0, position);");
            writer.WriteLine("        else");
            writer.WriteLine("        {");
            writer.WriteLine("            for (i = position; i < " + m_instanceName + "_DigitNum_" + index + "; i++) " + m_instanceName + "_Write7SegDigit_" + index + "(0,i); 	     ");
            writer.WriteLine("        }");
            writer.WriteLine("    }");
            writer.WriteLine("    else");
            writer.WriteLine("    {");
            writer.WriteLine("        for (i = position; i <= " + m_instanceName + "_DigitNum_" + index + "; i++)");
            writer.WriteLine("        {");
            writer.WriteLine("            Num = Value % 10;");
            writer.WriteLine("            " + m_instanceName + "_Write7SegDigit_" + index + "(Num, i);");
            writer.WriteLine("            Value = (Value - Num)/10; ");
            writer.WriteLine("            if ((Value == 0) && (mode == 0)) break;");
            writer.WriteLine("        }");
            writer.WriteLine("    }");
            writer.WriteLine("}");

        }
        #endregion

        #region PutChar14SegDisp
        void PutChar14seg_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            //writer_h.WriteLine("#ifndef " + m_instanceName + "_14SEG");
            writer_h.WriteLine("#define " + m_instanceName + "_14SEG");
            writer_h.WriteLine("#define ALPHANUMERIC");
            writer_h.WriteLine("void " + m_instanceName + "_PutChar14Seg_" + index + "(uint8 character, uint8 position);");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_PutChar14Seg_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 8-bit char on an array of");
            writer.WriteLine("*  alphanumeric character displays. The user must have defined what");
            writer.WriteLine("*  portion of the displays segments make up the alphanumeric display");
            writer.WriteLine("*  portion in the wizard. Multiple, separate alphanumeric displays can");
            writer.WriteLine("*  be created in the frame buffer and are addressed through the index");
            writer.WriteLine("*  (n) in the function name. Function/s only included if component");
            writer.WriteLine("*  alphanumeric wizard defines the alphanumeric option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  character : Character.");
            writer.WriteLine("*  position : Position of the character as counted left to");
            writer.WriteLine("*  right starting at 0 on the left. If the position is outside the");
            writer.WriteLine("*  display range, the character will not be displayed.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_PutChar14Seg_" + index + "(uint8 character, uint8 position)");
            writer.WriteLine("{");
            writer.WriteLine("    uint8 i, Val;");
            writer.WriteLine("");
            writer.WriteLine("    for (i = 0; i < 14; i++)");
            writer.WriteLine("    {");
            writer.WriteLine("        Val = ((uint8)(" + m_instanceName + "_14SegChars[character] >> i) & 0x01); ");
            writer.WriteLine("        " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[position][i], Val);	 ");
            writer.WriteLine("    }   ");
            writer.WriteLine("}");
        }
        void WriteString14seg_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            writer_h.WriteLine("void " + m_instanceName + "_WriteString14Seg_" + index + "(uint8* character, uint8 position);");
            //writer_h.WriteLine("#endif /* " + m_instanceName + "_14SEG */");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_WriteString14Seg_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 8-bit null terminated");
            writer.WriteLine("*  character string on an array of alphanumeric character displays.");
            writer.WriteLine("*  The user must have defined what portion of the displays segments");
            writer.WriteLine("*  make up the alphanumeric display portion in the wizard. Multiple,");
            writer.WriteLine("*  separate alphanumeric displays can be created in the frame buffer");
            writer.WriteLine("*  and are addressed through the index (n) in the function name.");
            writer.WriteLine("*  Function/s only included if component alphanumeric wizard defines");
            writer.WriteLine("*  the alphanumeric option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  character : Pointer to the null terminated character string.");
            writer.WriteLine("*  position : The Position of the first character as counted left");
            writer.WriteLine("*  to right starting at 0 on the left. If the defined display contains");
            writer.WriteLine("*  fewer characters then the string requires for display, the");
            writer.WriteLine("*  extra characters will not be displayed.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_WriteString14Seg_" + index + "(uint8* character, uint8 position)");
            writer.WriteLine("{");
            writer.WriteLine("    uint8 c, i;");
            writer.WriteLine("    i = 0;");
            writer.WriteLine("");
            writer.WriteLine("    while ((character[i] != 0) && ((position + i) != " + m_instanceName + "_DigitNum_" + index + "))");
            writer.WriteLine("    {");
            writer.WriteLine("        c = character[i];");
            writer.WriteLine("        " + m_instanceName + "_PutChar14Seg_" + index + "(c, position+i);");
            writer.WriteLine("        i++;");
            writer.WriteLine("    }");
            writer.WriteLine("}");
        }
        #endregion

        #region PutChar16segDisp
        void PutChar16seg_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            //writer_h.WriteLine("#ifndef " + m_instanceName + "_16SEG");
            writer_h.WriteLine("#define " + m_instanceName + "_16SEG");
            writer_h.WriteLine("#define ALPHANUMERIC");
            writer_h.WriteLine("void " + m_instanceName + "_PutChar16Seg_" + index + "(uint8 character, uint8 position);");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_PutChar16Seg_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 8-bit char on an array of");
            writer.WriteLine("*  alphanumeric character displays. The user must have defined what");
            writer.WriteLine("*  portion of the displays segments make up the alphanumeric display");
            writer.WriteLine("*  portion in the wizard. Multiple, separate alphanumeric displays can");
            writer.WriteLine("*  be created in the frame buffer and are addressed through the index");
            writer.WriteLine("*  (n) in the function name. Function/s only included if component");
            writer.WriteLine("*  alphanumeric wizard defines the alphanumeric option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  character : Character.");
            writer.WriteLine("*  position : Position of the character as counted left to");
            writer.WriteLine("*  right starting at 0 on the left. If the position is outside the");
            writer.WriteLine("*  display range, the character will not be displayed.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  (void)");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_PutChar16Seg_" + index + "(uint8 character, uint8 position)");
            writer.WriteLine("{");
            writer.WriteLine("    uint8 i, Val;");
            writer.WriteLine("");
            writer.WriteLine("    for (i = 0; i < 16; i++)");
            writer.WriteLine("    {");
            writer.WriteLine("        Val = ((uint8)(" + m_instanceName + "_16SegChars[character] >> i) & 0x01); ");
            writer.WriteLine("        " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[position][i], Val); ");
            writer.WriteLine("    }");
            writer.WriteLine("}");
        }
        void WriteString16seg_n(ref TextWriter writer, ref TextWriter writer_h, int index)
        {
            writer_h.WriteLine("void " + m_instanceName + "_WriteString16Seg_" + index + "(uint8* character, uint8 position);");
            //writer_h.WriteLine("#endif /* " + m_instanceName + "_16SEG */");

            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_WriteString16Seg_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 8-bit null terminated");
            writer.WriteLine("*  character string on an array of alphanumeric character displays.");
            writer.WriteLine("*  The user must have defined what portion of the displays segments");
            writer.WriteLine("*  make up the alphanumeric display portion in the wizard. Multiple,");
            writer.WriteLine("*  separate alphanumeric displays can be created in the frame buffer");
            writer.WriteLine("*  nand are addressed through the index (n) in the function name.");
            writer.WriteLine("*  Function/s only included if component alphanumeric wizard defines");
            writer.WriteLine("*  the alphanumeric option.");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  character : Pointer to the null terminated character string.");
            writer.WriteLine("*  position : The Position of the first character as counted left");
            writer.WriteLine("*  to right starting at 0 on the left. If the defined display contains");
            writer.WriteLine("*  fewer characters then the string requires for display, the");
            writer.WriteLine("*  extra characters will not be displayed.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_WriteString16Seg_" + index + "(uint8* character, uint8 position)");
            writer.WriteLine("{");
            writer.WriteLine("    uint8 c, i;");
            writer.WriteLine("    i = 0;");
            writer.WriteLine("");
            writer.WriteLine("    while ((character[i] != 0) && ((position + i) != " + m_instanceName + "_DigitNum_" + index + "))");
            writer.WriteLine("    {");
            writer.WriteLine("        c = character[i];");
            writer.WriteLine("        " + m_instanceName + "_PutChar16Seg_" + index + "(c, position+i);");
            writer.WriteLine("        i++;");
            writer.WriteLine("    }");
            writer.WriteLine("}");
            
        }
        #endregion

        #region WriteBargraph_n
        void WriteBargraph_n(ref TextWriter writer, ref TextWriter writer_h, int index, int maxNumber)
        {
            writer_h.WriteLine("void " + m_instanceName + "_WriteBargraph_" + index + "(uint16 location, int8 mode);");
            writer.WriteLine("");
            writer.WriteLine("");
            writer.WriteLine("/*******************************************************************************");
            writer.WriteLine("* Function Name: " + m_instanceName + "_WriteBargraph_" + index + "");
            writer.WriteLine("********************************************************************************");
            writer.WriteLine("* Summary:");
            writer.WriteLine("*  This function displays an 8-bit integer");
            writer.WriteLine("*  Location on a 1 to 255 segment bar-graph (numbered left to right).");
            writer.WriteLine("*  The bar graph may be any user defined size between 1 and 255");
            writer.WriteLine("*  segments. A bar graph may also be created in a circle to display");
            writer.WriteLine("*  rotary position. The user defines what portion of the displays");
            writer.WriteLine("*  segments make up the bar-graph portion. Multiple, separate bargraph");
            writer.WriteLine("*  displays can be created in the frame buffer and are");
            writer.WriteLine("*  addressed through the index (n) in the function name. Function/s");
            writer.WriteLine("*  only included if component bar-graph wizard defines the 7 segment");
            writer.WriteLine("*  option");
            writer.WriteLine("*");
            writer.WriteLine("* Parameters:  ");
            writer.WriteLine("*  location : unsigned integer location to be displayed. 0 - all");
            writer.WriteLine("*  bar-graph elements off. Max Value = the number of");
            writer.WriteLine("*  segments in the bar-graph. Locations greater then the");
            writer.WriteLine("*  number of segments in the bar-graph will be limited to the");
            writer.WriteLine("*  number of segments physically provided.");
            writer.WriteLine("*  mode : 0 - only the location segment is turned on, 1=The              ");
            writer.WriteLine("*  location segment all segments to the left are turned on, -");
            writer.WriteLine("*  1 - the location segment and all segments to the right are");
            writer.WriteLine("*  turned on. 2-10 display the location segment and 2-254");
            writer.WriteLine("*  segments to the right to create wide indicators.");
            writer.WriteLine("*");
            writer.WriteLine("* Return: ");
            writer.WriteLine("*  void");
            writer.WriteLine("*");
            writer.WriteLine("* Theory: ");
            writer.WriteLine("*");
            writer.WriteLine("* Side Effects:");
            writer.WriteLine("*");
            writer.WriteLine("*******************************************************************************/");
            writer.WriteLine("void " + m_instanceName + "_WriteBargraph_" + index + "(uint16 location, int8 mode)");
            writer.WriteLine("{");
            writer.WriteLine("    int8 i;");
            writer.WriteLine("    uint16 MaxValue = " + maxNumber + ";");
            writer.WriteLine("");
			writer.WriteLine("    if (location != 0)");
			writer.WriteLine("    {");
            writer.WriteLine("        switch (mode)");
            writer.WriteLine("        {");
            writer.WriteLine("            case -1:");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 0:");
            writer.WriteLine("                " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[location][0], 1);");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 1:");
            writer.WriteLine("                for (i = location; i >= 1; i--) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 2:");
            writer.WriteLine("                if (location + 1 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 1;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 3:");
            writer.WriteLine("                if (location + 2 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 2;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 4:");
            writer.WriteLine("                if (location + 3 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 3;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 5:");
            writer.WriteLine("                if (location + 4 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 4;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 6:");
            writer.WriteLine("                if (location + 5 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 5;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 7:");
            writer.WriteLine("                if (location + 6 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 6;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 8:");
            writer.WriteLine("                if (location + 7 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 7;");
            writer.WriteLine("                }");
            writer.WriteLine("                for(i = location;i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 9:");
            writer.WriteLine("                if (location + 8 < MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 8;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i <= MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            case 10:");
            writer.WriteLine("                if (location + 9 <= MaxValue) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    MaxValue = location + 9;");
            writer.WriteLine("                }");
            writer.WriteLine("                for (i = location; i < MaxValue; i++) ");
            writer.WriteLine("                {");
            writer.WriteLine("                    " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 1);");
            writer.WriteLine("                }");
            writer.WriteLine("            break;");
            writer.WriteLine("            default:");
            writer.WriteLine("            break;");
            writer.WriteLine("        }");
			writer.WriteLine("    }");
            writer.WriteLine("    else ");
            writer.WriteLine("        for (i = 0; i <= MaxValue; i++) ");
            writer.WriteLine("        {");
            writer.WriteLine("            " + m_instanceName + "_WRITE_PIXEL(" + m_instanceName + "_Disp" + index + "[i][0], 0);");
            writer.WriteLine("        }");
            writer.WriteLine("}");
        }

        #endregion

    }
}
