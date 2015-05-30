﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.269
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace UART_v2_30 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("UART_v2_30.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Advanced.
        /// </summary>
        internal static string AdvancedTabCaption {
            get {
                return ResourceManager.GetString("AdvancedTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be less than or equal to 4000000..
        /// </summary>
        internal static string BitsPerSecErrMsg {
            get {
                return ResourceManager.GetString("BitsPerSecErrMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UART RX buffer size less than {0} is not supported by bootloader..
        /// </summary>
        internal static string BootloaderSupportBufferSizeFailError {
            get {
                return ResourceManager.GetString("BootloaderSupportBufferSizeFailError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UART mode is not supported by bootloader..
        /// </summary>
        internal static string BootloaderSupportModeFailError {
            get {
                return ResourceManager.GetString("BootloaderSupportModeFailError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be less than 16..
        /// </summary>
        internal static string BreakSignalErrMsg {
            get {
                return ResourceManager.GetString("BreakSignalErrMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabCaption {
            get {
                return ResourceManager.GetString("BuiltInTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Configure.
        /// </summary>
        internal static string ConfigureTabCaption {
            get {
                return ResourceManager.GetString("ConfigureTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Data bits 9 should be selected when Mark/Space parity type is used..
        /// </summary>
        internal static string DataBitsMsg {
            get {
                return ResourceManager.GetString("DataBitsMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Error Setting Parameter {0} with value {1}\n\nErrors:\n{2}.
        /// </summary>
        internal static string ErrorSettingParamMsg {
            get {
                return ResourceManager.GetString("ErrorSettingParamMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Error Setting Parameter.
        /// </summary>
        internal static string ErrorSettingParamTitle {
            get {
                return ResourceManager.GetString("ErrorSettingParamTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to 1/{0} Input Clock Frequency.
        /// </summary>
        internal static string ExternalClockMsg {
            get {
                return ResourceManager.GetString("ExternalClockMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to 1/{0} Input Clock Frequency ({1} {2}).
        /// </summary>
        internal static string ExternalClockParamMsg {
            get {
                return ResourceManager.GetString("ExternalClockParamMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to RX Buffer Size must be in range between {0} and {1}.
        /// </summary>
        internal static string InvalidRXBufferSize {
            get {
                return ResourceManager.GetString("InvalidRXBufferSize", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to TX Buffer Size must be in range between {0} and {1}.
        /// </summary>
        internal static string InvalidTXBufferSize {
            get {
                return ResourceManager.GetString("InvalidTXBufferSize", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to TX Buffer Size must be equal to {0}.
        /// </summary>
        internal static string InvalidTXBufferSizeHalfDuplex {
            get {
                return ResourceManager.GetString("InvalidTXBufferSizeHalfDuplex", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be in range [{0}, {1}]..
        /// </summary>
        internal static string InvalidValueRangeMsg {
            get {
                return ResourceManager.GetString("InvalidValueRangeMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Mark/Space parity type should be selected when 9 Data bits are used..
        /// </summary>
        internal static string MarkSpaceParityMsg {
            get {
                return ResourceManager.GetString("MarkSpaceParityMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be equal 8 or 16..
        /// </summary>
        internal static string OverSamplingRateErrMsg {
            get {
                return ResourceManager.GetString("OverSamplingRateErrMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to SOURCE FREQ = {0} {1}.
        /// </summary>
        internal static string SourceFreqMsg {
            get {
                return ResourceManager.GetString("SourceFreqMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UNKNOWN SOURCE FREQ.
        /// </summary>
        internal static string UnknownSourceFreqMsg {
            get {
                return ResourceManager.GetString("UnknownSourceFreqMsg", resourceCulture);
            }
        }
    }
}
