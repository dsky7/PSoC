/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.ComponentModel;

namespace MDIO_Interface_v1_0
{
    static class CyEnumConverter
    {
        /// <summary>
        /// Converts enum description to value
        /// </summary>
        /// <param name="value"></param>
        /// <param name="_enumType"></param>
        /// <returns></returns>
        public static object GetEnumValue(object value, Type _enumType)
        {
            object result;
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value.ToString() == (string)dna.Description))
                    return Enum.Parse(_enumType, fi.Name);
            }
            try
            {
                result = Enum.Parse(_enumType, value.ToString());
            }
            catch (Exception)
            {
                result = null;
            }
            return result;
        }

        /// <summary>
        /// Converts enum value to description
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string GetEnumDesc(object value)
        {
            DescriptionAttribute dna;
            try
            {
                Type _enumType = value.GetType();
                FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
                dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));
            }
            catch (Exception)
            {
                dna = null;
            }

            if (dna != null)
                return dna.Description;
            else
                return null;
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
    }
}
