﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.261
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace EZI2C_v1_70 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("EZI2C_v1_70.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Basic Configuration.
        /// </summary>
        internal static string BasicTabCaption {
            get {
                return ResourceManager.GetString("BasicTabCaption", resourceCulture);
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
        ///   Looks up a localized string similar to Data rate must be between 50 kbps and 1 Mbps..
        /// </summary>
        internal static string BusSpeedEP {
            get {
                return ResourceManager.GetString("BusSpeedEP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to If the &quot;Pin connections&quot; parameter is set to &apos;I2C0&apos; or &apos;I2C1&apos; the component&apos;s pins should be connected to the corresponding port..
        /// </summary>
        internal static string DRCI2CBusPortError {
            get {
                return ResourceManager.GetString("DRCI2CBusPortError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The &quot;Enable wakeup from Sleep Mode&quot; option is not supported by PSoC 5 devices..
        /// </summary>
        internal static string DRCRevisionError {
            get {
                return ResourceManager.GetString("DRCRevisionError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Enable wakeup from Sleep Mode option is not available when Number of Addresses option set to 2 and Pin Connections option set to Any. Disable Enable wakeup from Sleep Mode option or set Number of Addresses option set to 1 and Pin Connections option to I2C0 or I2C1..
        /// </summary>
        internal static string EnableWakupDRC {
            get {
                return ResourceManager.GetString("EnableWakupDRC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Enable wakeup from Sleep Mode option is not available when Number of Addresses option set to 2 and Pin Connections option set to Any..
        /// </summary>
        internal static string EnableWakupEP {
            get {
                return ResourceManager.GetString("EnableWakupEP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Number of Addresses option must be set to 1 to make Enable wakeup from Sleep Mode option become available. Set Number of Addresses option to 1 or disable Enable wakeup from Sleep Mode option and set Pin Connections option to Any..
        /// </summary>
        internal static string NumberOfAddressesDRC1 {
            get {
                return ResourceManager.GetString("NumberOfAddressesDRC1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Number of Addresses option must be set to 1 to make Enable wakeup from Sleep Mode option become available..
        /// </summary>
        internal static string NumberOfAddressesEP1 {
            get {
                return ResourceManager.GetString("NumberOfAddressesEP1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Pin Connections option must be set to I2C0 or I2C1 pins pair, if Enable wakeup from Sleep Mode option is enabled. Note that device pins assignment is not controlled by this option..
        /// </summary>
        internal static string PinConnectionsDRC1 {
            get {
                return ResourceManager.GetString("PinConnectionsDRC1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Pin Connections option must be set to I2C0 or I2C1 pins pair, if Enable wakeup from Sleep Mode option is enabled..
        /// </summary>
        internal static string PinConnectionsEP1 {
            get {
                return ResourceManager.GetString("PinConnectionsEP1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Pin Connections option must be set to Any, if Enable wakeup from Sleep Mode option is disabled..
        /// </summary>
        internal static string PinConnectionsEPAndDRC2 {
            get {
                return ResourceManager.GetString("PinConnectionsEPAndDRC2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Pin Connections option must be set to Any, as &quot;Enable wakeup from Sleep Mode&quot; option is not supported by PSoC 5 devices..
        /// </summary>
        internal static string PinConnectionsPSoC5AEP {
            get {
                return ResourceManager.GetString("PinConnectionsPSoC5AEP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Primary slave and Secondary slave addresses cannot be equal..
        /// </summary>
        internal static string PrimarySecondaryEqualEP {
            get {
                return ResourceManager.GetString("PrimarySecondaryEqualEP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Primary slave address must be between 0 and 127..
        /// </summary>
        internal static string PrimarySlaveAddressEP {
            get {
                return ResourceManager.GetString("PrimarySlaveAddressEP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Secondary slave address must be between 0 and 127..
        /// </summary>
        internal static string SecondarySlaveAddressEP {
            get {
                return ResourceManager.GetString("SecondarySlaveAddressEP", resourceCulture);
            }
        }
    }
}