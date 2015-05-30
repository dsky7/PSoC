﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.269
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ThermistorCalc_v1_0 {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ThermistorCalc_v1_0.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabDisplayName {
            get {
                return ResourceManager.GetString("BuiltInTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        internal static string GeneralTabDisplayName {
            get {
                return ResourceManager.GetString("GeneralTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to LUT size based on range and accuracy chosen: {0}
        ///Calculation resolution selection applies to LUT implementation and not to Equation
        ///Ideal value for reference resistor is the value of thermistor resistance at mid temperature.
        /// </summary>
        internal static string InfoString {
            get {
                return ResourceManager.GetString("InfoString", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The selected combinations of temperatures and resistances do not produce a valid equation..
        /// </summary>
        internal static string LUTErrorDescription {
            get {
                return ResourceManager.GetString("LUTErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to LUT size must not exceed {0}. Increase calculation resolution or min temperature or decrease max temperature..
        /// </summary>
        internal static string LUTSizeValueError {
            get {
                return ResourceManager.GetString("LUTSizeValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The reference resistance value must be between {0} and {1}..
        /// </summary>
        internal static string ReferenceResistanceValueErrorDescription {
            get {
                return ResourceManager.GetString("ReferenceResistanceValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The resistance value must be between {0} and {1}..
        /// </summary>
        internal static string ResistanceValueError {
            get {
                return ResourceManager.GetString("ResistanceValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The temperature value must be between {0} and {1}..
        /// </summary>
        internal static string TemperatureValueError {
            get {
                return ResourceManager.GetString("TemperatureValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value of {0} {1} must be {2} than {3} {1} value..
        /// </summary>
        internal static string TermParamCompareError {
            get {
                return ResourceManager.GetString("TermParamCompareError", resourceCulture);
            }
        }
    }
}
