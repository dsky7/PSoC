﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.1433
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace BoostConv_v1_50.Properties {
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
    public class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("BoostConv_v1_50.Properties.Resources", typeof(Resources).Assembly);
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
        public static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        public static System.Drawing.Bitmap boost {
            get {
                object obj = ResourceManager.GetObject("boost", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        public static System.Drawing.Bitmap boost_diodeless {
            get {
                object obj = ResourceManager.GetObject("boost_diodeless", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Current Silicon Revision doesn&apos;t support External Clock  source feature! Please change target silicon revision or select None option for External clock source field in customizer!.
        /// </summary>
        public static string DRCMessage_RevisionError {
            get {
                return ResourceManager.GetString("DRCMessage_RevisionError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Boost convertor configuration.
        /// </summary>
        public static string TabConfig {
            get {
                return ResourceManager.GetString("TabConfig", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        public static string TabNameBuildIn {
            get {
                return ResourceManager.GetString("TabNameBuildIn", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Output Voltage is equel to Input voltage when Input voltage &gt; Programmed Output Voltage.
        /// </summary>
        public static string VoltageWarningMessage {
            get {
                return ResourceManager.GetString("VoltageWarningMessage", resourceCulture);
            }
        }
    }
}
