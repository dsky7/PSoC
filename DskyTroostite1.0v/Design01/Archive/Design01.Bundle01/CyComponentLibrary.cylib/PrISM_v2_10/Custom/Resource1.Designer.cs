//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.1433
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace PrISM_v2_10 {
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
    public class Resource1 {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resource1() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("PrISM_v2_10.Resource1", typeof(Resource1).Assembly);
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
        
        /// <summary>
        ///   Looks up a localized string similar to Invalid format for input data. Please, enter comma-separated values..
        /// </summary>
        public static string LFSR_FORMAT {
            get {
                return ResourceManager.GetString("LFSR_FORMAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to LFSR items could not be greater than Resolution..
        /// </summary>
        public static string LFSR_ITEM_LIMIT {
            get {
                return ResourceManager.GetString("LFSR_ITEM_LIMIT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Seed value for current Resolution must be in range (0, {0}]..
        /// </summary>
        public static string SEED_VALUE_LIMIT {
            get {
                return ResourceManager.GetString("SEED_VALUE_LIMIT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        public static string TAB_NAME_BUILT_IN {
            get {
                return ResourceManager.GetString("TAB_NAME_BUILT_IN", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        public static string TAB_NAME_GENERAL {
            get {
                return ResourceManager.GetString("TAB_NAME_GENERAL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be between {0} and {1}.
        /// </summary>
        public static string VALUE_LIMIT {
            get {
                return ResourceManager.GetString("VALUE_LIMIT", resourceCulture);
            }
        }
    }
}
