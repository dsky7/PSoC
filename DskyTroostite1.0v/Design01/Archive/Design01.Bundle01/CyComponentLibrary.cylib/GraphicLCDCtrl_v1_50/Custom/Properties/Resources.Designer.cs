﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3603
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace GraphicLCDCtrl_v1_50.Properties {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("GraphicLCDCtrl_v1_50.Properties.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to HorizActiveRegion value must be between 4 and 1024.
        /// </summary>
        internal static string EPHActiveRegionMsg1 {
            get {
                return ResourceManager.GetString("EPHActiveRegionMsg1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HorizActiveRegion must be a multiple of 4.
        /// </summary>
        internal static string EPHActiveRegionMsg2 {
            get {
                return ResourceManager.GetString("EPHActiveRegionMsg2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HorizBackPorch value must be set between 6 and 256.
        /// </summary>
        internal static string EPHBackPorchMsg {
            get {
                return ResourceManager.GetString("EPHBackPorchMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HorizFrontPorch value must be between 1 and 256.
        /// </summary>
        internal static string EPHFrontPorchMsg {
            get {
                return ResourceManager.GetString("EPHFrontPorchMsg", resourceCulture);
            }
        }

        // Horizontal Timing Messages
        /// <summary>
        ///   Looks up a localized string similar to HorizSyncWidth value must be between 1 and 256.
        /// </summary>
        internal static string EPHSyncWidthMsg {
            get {
                return ResourceManager.GetString("EPHSyncWidthMsg", resourceCulture);
            }
        }

        // Vertical Timing Messages
        internal static string EPVActiveRegionMsg1
        {
            get
            {
                return ResourceManager.GetString("EPVActiveRegionMsg1", resourceCulture);
            }
        }

        internal static string EPVActiveRegionMsg2
        {
            get
            {
                return ResourceManager.GetString("EPVActiveRegionMsg2", resourceCulture);
            }
        }

        internal static string EPVBackPorchMsg
        {
            get
            {
                return ResourceManager.GetString("EPVBackPorchMsg", resourceCulture);
            }
        }

        internal static string EPVFrontPorchMsg
        {
            get
            {
                return ResourceManager.GetString("EPVFrontPorchMsg", resourceCulture);
            }
        }

        internal static string EPVSyncWidthMsg
        {
            get
            {
                return ResourceManager.GetString("EPVSyncWidthMsg", resourceCulture);
            }
        }

        internal static string BasicTabCaption
        {
            get
            {
                return ResourceManager.GetString("BasicTabCaption", resourceCulture);
            }
        }

        internal static string BuiltInTabCaption
        {
            get
            {
                return ResourceManager.GetString("BuiltInTabCaption", resourceCulture);
            }
        }
    }
}
