//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3603
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SPI_Slave_v2_10.Properties {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0")]
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("SPI_Slave_v2_10.Properties.Resources", typeof(Resources).Assembly);
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
        
        internal static string AdvancedTabTitle {
            get {
                return ResourceManager.GetString("AdvancedTabTitle", resourceCulture);
            }
        }
        
        internal static string BasicTabTitle {
            get {
                return ResourceManager.GetString("BasicTabTitle", resourceCulture);
            }
        }
        
        internal static string BuiltInTabTitle {
            get {
                return ResourceManager.GetString("BuiltInTabTitle", resourceCulture);
            }
        }

        internal static string FrequencyEPMsg
        {
            get
            {
                return ResourceManager.GetString("FrequencyEPMsg", resourceCulture);
            }
        }

        internal static string NumOfDataBitsEPMsg
        {
            get
            {
                return ResourceManager.GetString("NumOfDataBitsEPMsg", resourceCulture);
            }
        }

        internal static string RXBufferSizeEPMsg
        {
            get
            {
                return ResourceManager.GetString("RXBufferSizeEPMsg", resourceCulture);
            }
        }

        internal static string TXBufferSizeEPMsg
        {
            get
            {
                return ResourceManager.GetString("TXBufferSizeEPMsg", resourceCulture);
            }
        }

        internal static string DRCNumberOfDataBitsMsg
        {
            get
            {
                return ResourceManager.GetString("DRCNumberOfDataBitsMsg", resourceCulture);
            }
        }
    }
}
