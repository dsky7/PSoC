//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.544
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace FanController_v2_30 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("FanController_v2_30.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Basic.
        /// </summary>
        internal static string BasicTab {
            get {
                return ResourceManager.GetString("BasicTab", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTab {
            get {
                return ResourceManager.GetString("BuiltInTab", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value out of range for {0} [{1} to {2}].
        /// </summary>
        internal static string ErrorDrcValueRange {
            get {
                return ResourceManager.GetString("ErrorDrcValueRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Duty Cycle B must be greater than Duty Cycle A..
        /// </summary>
        internal static string ErrorDutyMaxLimit {
            get {
                return ResourceManager.GetString("ErrorDutyMaxLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Duty Cycle A must be less than Duty Cycle B..
        /// </summary>
        internal static string ErrorDutyMinLimit {
            get {
                return ResourceManager.GetString("ErrorDutyMinLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to MaxDuty{0} value must be greater than MinDuty{0} value..
        /// </summary>
        internal static string ErrorDutyVal {
            get {
                return ResourceManager.GetString("ErrorDutyVal", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Field cannot be empty..
        /// </summary>
        internal static string ErrorEmptyField {
            get {
                return ResourceManager.GetString("ErrorEmptyField", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to There are empty fields on the Fans tab..
        /// </summary>
        internal static string ErrorEmptyFieldsOnFans {
            get {
                return ResourceManager.GetString("ErrorEmptyFieldsOnFans", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to There are errors in datapoints table in row number {0}..
        /// </summary>
        internal static string ErrorFanNumberDPTRow {
            get {
                return ResourceManager.GetString("ErrorFanNumberDPTRow", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Incorrect value.
        /// </summary>
        internal static string ErrorIncorrectValue {
            get {
                return ResourceManager.GetString("ErrorIncorrectValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Initial RPM must be less than RPM B and greater than RPM A..
        /// </summary>
        internal static string ErrorInitialRPMLimit {
            get {
                return ResourceManager.GetString("ErrorInitialRPMLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to RPM B must be greater than RPM A..
        /// </summary>
        internal static string ErrorRPMMaxLimit {
            get {
                return ResourceManager.GetString("ErrorRPMMaxLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to RPM A must be less than RPM B..
        /// </summary>
        internal static string ErrorRPMMinLimit {
            get {
                return ResourceManager.GetString("ErrorRPMMinLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to MaxRPM{0} value must be greater than MinRPM{0} value..
        /// </summary>
        internal static string ErrorRPMVal {
            get {
                return ResourceManager.GetString("ErrorRPMVal", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be between {0} and {1}..
        /// </summary>
        internal static string ErrorValueLimit {
            get {
                return ResourceManager.GetString("ErrorValueLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Fans.
        /// </summary>
        internal static string FansTab {
            get {
                return ResourceManager.GetString("FansTab", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Maximum number of fans is {0} in 10-bit closed loop mode.
        /// </summary>
        internal static string MsgMaxFan10bClosedLoop {
            get {
                return ResourceManager.GetString("MsgMaxFan10bClosedLoop", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Maximum number of fans is {0} in 8-bit closed loop mode.
        /// </summary>
        internal static string MsgMaxFan8bClosedLoop {
            get {
                return ResourceManager.GetString("MsgMaxFan8bClosedLoop", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Maximum number of fans is {0}..
        /// </summary>
        internal static string MsgMaxFanLoop {
            get {
                return ResourceManager.GetString("MsgMaxFanLoop", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Bank number.
        /// </summary>
        internal static string TxtBankNumber {
            get {
                return ResourceManager.GetString("TxtBankNumber", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ({0} fans/bank).
        /// </summary>
        internal static string TxtFanBank {
            get {
                return ResourceManager.GetString("TxtFanBank", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Fan number.
        /// </summary>
        internal static string TxtFanNumber {
            get {
                return ResourceManager.GetString("TxtFanNumber", resourceCulture);
            }
        }
    }
}
