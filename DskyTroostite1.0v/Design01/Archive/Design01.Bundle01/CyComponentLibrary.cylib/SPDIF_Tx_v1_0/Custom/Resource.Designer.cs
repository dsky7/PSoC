﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3620
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SPDIF_Tx_v1_0 {
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
    internal class Resource {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resource() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("SPDIF_Tx_v1_0.Resource", typeof(Resource).Assembly);
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
        internal static string BuiltInTabCaption {
            get {
                return ResourceManager.GetString("BuiltInTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channel 0 Status.
        /// </summary>
        internal static string Channel0StatusTabCaption {
            get {
                return ResourceManager.GetString("Channel0StatusTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channel 1 Status.
        /// </summary>
        internal static string Channel1StatusTabCaption {
            get {
                return ResourceManager.GetString("Channel1StatusTabCaption", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channel Number value must be between 0 and 15..
        /// </summary>
        internal static string EPChannelNumberError {
            get {
                return ResourceManager.GetString("EPChannelNumberError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Source Number value must be between 0 and 15..
        /// </summary>
        internal static string EPSourceNumberError {
            get {
                return ResourceManager.GetString("EPSourceNumberError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        internal static string GeneralTabCaption {
            get {
                return ResourceManager.GetString("GeneralTabCaption", resourceCulture);
            }
        }
    }
}