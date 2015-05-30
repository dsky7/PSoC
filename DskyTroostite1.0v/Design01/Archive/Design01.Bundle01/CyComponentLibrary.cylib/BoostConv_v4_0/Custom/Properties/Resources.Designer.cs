﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.17929
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace BoostConv_v4_0.Properties {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("BoostConv_v4_0.Properties.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap boost {
            get {
                object obj = ResourceManager.GetObject("boost", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap boost_diodeless {
            get {
                object obj = ResourceManager.GetObject("boost_diodeless", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to External clock source option should be set to None for PSoC 5 LP..
        /// </summary>
        internal static string DRCClockSourcePSoC5LPLimit {
            get {
                return ResourceManager.GetString("DRCClockSourcePSoC5LPLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to PSoC 5 does not have support for the Boost Converter functionality, so this component (`$INSTANCE_NAME`) cannot be used with this silicon.
        /// </summary>
        internal static string DRCMessage_PSoC5Error {
            get {
                return ResourceManager.GetString("DRCMessage_PSoC5Error", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Current siliconrevision doesn&apos;t support external clock  source feature! Change target silicon revision or select &quot;None&quot; option for external clock source field in customizer..
        /// </summary>
        internal static string DRCMessage_RevisionError {
            get {
                return ResourceManager.GetString("DRCMessage_RevisionError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The switching frequency parameter has an incorrect value. Please open the customizer and fix the value..
        /// </summary>
        internal static string DRCMessageFrequencyError {
            get {
                return ResourceManager.GetString("DRCMessageFrequencyError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The switching frequency for PSoC 5 LP should be set to 400 kHz, because 32 kHz clock is incompatible with active boost mode..
        /// </summary>
        internal static string DRCSwitchingFreqPSoC5LPLimit {
            get {
                return ResourceManager.GetString("DRCSwitchingFreqPSoC5LPLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Output voltage is limited to 3.6V if input voltage range from 0.5V to 0.8V..
        /// </summary>
        internal static string InputVoltageErrorMessage {
            get {
                return ResourceManager.GetString("InputVoltageErrorMessage", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input voltage value must be between {0} and {1}..
        /// </summary>
        internal static string InputVoltageOutOfRange {
            get {
                return ResourceManager.GetString("InputVoltageOutOfRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap Symbol_Error {
            get {
                object obj = ResourceManager.GetObject("Symbol_Error", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Boost convertor configuration.
        /// </summary>
        internal static string TabConfig {
            get {
                return ResourceManager.GetString("TabConfig", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string TabNameBuildIn {
            get {
                return ResourceManager.GetString("TabNameBuildIn", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Output voltage is limited to 2 x input voltage at boost frequency of 2 MHz..
        /// </summary>
        internal static string VoltageErrorMessage2MHz {
            get {
                return ResourceManager.GetString("VoltageErrorMessage2MHz", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Output voltage is limited to 4 x input voltage at boost frequency of 400 kHz..
        /// </summary>
        internal static string VoltageErrorMessage400kHz {
            get {
                return ResourceManager.GetString("VoltageErrorMessage400kHz", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Minimum value of input voltage can not be less than {0} for PSoC 5LP device..
        /// </summary>
        internal static string VoltageErrorPSoC5LP {
            get {
                return ResourceManager.GetString("VoltageErrorPSoC5LP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Output voltage is equal to input voltage when Input voltage is greater than programmed output voltage..
        /// </summary>
        internal static string VoltageWarningMessage {
            get {
                return ResourceManager.GetString("VoltageWarningMessage", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap WarningHS {
            get {
                object obj = ResourceManager.GetObject("WarningHS", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
    }
}