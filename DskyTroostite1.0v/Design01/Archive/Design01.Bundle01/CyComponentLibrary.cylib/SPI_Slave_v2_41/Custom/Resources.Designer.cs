//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.269
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SPI_Slave_v2_41 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("SPI_Slave_v2_41.Resources", typeof(Resources).Assembly);
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
        internal static string AdvancedTabTitle {
            get {
                return ResourceManager.GetString("AdvancedTabTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Configure.
        /// </summary>
        internal static string BasicTabTitle {
            get {
                return ResourceManager.GetString("BasicTabTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabTitle {
            get {
                return ResourceManager.GetString("BuiltInTabTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Only {0} to {1} DataBits value is supported in current version. Please select DataBits value from this range..
        /// </summary>
        internal static string DRCNumberOfDataBitsMsg {
            get {
                return ResourceManager.GetString("DRCNumberOfDataBitsMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to BitRate value must be between 1 bps and 33 Mbps..
        /// </summary>
        internal static string FrequencyEPMsg {
            get {
                return ResourceManager.GetString("FrequencyEPMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Number Of Data Bits must be between {0} and {1}..
        /// </summary>
        internal static string NumOfDataBitsEPMsg {
            get {
                return ResourceManager.GetString("NumOfDataBitsEPMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Rx Buffer Size must be between {0} and {1}..
        /// </summary>
        internal static string RXBufferSizeEPMsg {
            get {
                return ResourceManager.GetString("RXBufferSizeEPMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Rx Buffer Size ({0}-bit words):.
        /// </summary>
        internal static string RxBufferSizeLabelText {
            get {
                return ResourceManager.GetString("RxBufferSizeLabelText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Rx Buffer Size (unknown):.
        /// </summary>
        internal static string RxBufferSizeLabelUnknownText {
            get {
                return ResourceManager.GetString("RxBufferSizeLabelUnknownText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Tx Buffer Size must be between {0} and {1}..
        /// </summary>
        internal static string TXBufferSizeEPMsg {
            get {
                return ResourceManager.GetString("TXBufferSizeEPMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Tx Buffer Size ({0}-bit words):.
        /// </summary>
        internal static string TxBufferSizeLabelText {
            get {
                return ResourceManager.GetString("TxBufferSizeLabelText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Tx Buffer Size (unknown):.
        /// </summary>
        internal static string TxBufferSizeLabelUnknownText {
            get {
                return ResourceManager.GetString("TxBufferSizeLabelUnknownText", resourceCulture);
            }
        }
    }
}