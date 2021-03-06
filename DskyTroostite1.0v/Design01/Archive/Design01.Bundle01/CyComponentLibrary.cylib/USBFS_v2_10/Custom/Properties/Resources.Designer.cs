//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3620
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace USBFS_v2_10.Properties {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("USBFS_v2_10.Properties.Resources", typeof(Resources).Assembly);
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
        
        internal static System.Drawing.Bitmap imadd {
            get {
                object obj = ResourceManager.GetObject("imadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imcomponentadd {
            get {
                object obj = ResourceManager.GetObject("imcomponentadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imconfiguration {
            get {
                object obj = ResourceManager.GetObject("imconfiguration", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imdelete {
            get {
                object obj = ResourceManager.GetObject("imdelete", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imimport {
            get {
                object obj = ResourceManager.GetObject("imimport", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imsave {
            get {
                object obj = ResourceManager.GetObject("imsave", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imscript {
            get {
                object obj = ResourceManager.GetObject("imscript", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        internal static System.Drawing.Bitmap imscriptadd {
            get {
                object obj = ResourceManager.GetObject("imscriptadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Current configuration cannot support a bootloader. The following configurations should be used: (1) Endpoint Number: EP1, Direction: OUT, Transfer Type: INT, Max Packet Size: 64; (2) Endpoint Number: EP2, Direction: IN, Transfer Type: INT, Max Packet Size: 64..
        /// </summary>
        internal static string MSG_BOOTLOADER_SUPPORT {
            get {
                return ResourceManager.GetString("MSG_BOOTLOADER_SUPPORT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Selected endpoint memory management option &quot;{0}&quot; is not supported for current device. It is supported for PSoC3 Production silicon only..
        /// </summary>
        internal static string MSG_DRC_DMA_ERROR {
            get {
                return ResourceManager.GetString("MSG_DRC_DMA_ERROR", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Incorrect format of the Input Value..
        /// </summary>
        internal static string MSG_INCORRECT_VALUE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VALUE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input Value should be in range [0x{0:X}..0x{1:X}]..
        /// </summary>
        internal static string MSG_INCORRECT_VALUE_RANGE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VALUE_RANGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value {0} is too small for vendor-defined value. It will be automatically updated to 0xFF00..
        /// </summary>
        internal static string MSG_INCORRECT_VENDOR_VALUE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VENDOR_VALUE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Interface class will be changed to Undefined. Do you want to continue?.
        /// </summary>
        internal static string MSG_INTERFACE_CHANGE {
            get {
                return ResourceManager.GetString("MSG_INTERFACE_CHANGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to END_COLLECTION could not be added at the beginning of the report..
        /// </summary>
        internal static string MSG_RPT_WARNING_1 {
            get {
                return ResourceManager.GetString("MSG_RPT_WARNING_1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to load the Template..
        /// </summary>
        internal static string MSG_UNABLE_LOAD_TEMPLATE {
            get {
                return ResourceManager.GetString("MSG_UNABLE_LOAD_TEMPLATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to save the Template to the file..
        /// </summary>
        internal static string MSG_UNABLE_SAVE_TEMPLATE {
            get {
                return ResourceManager.GetString("MSG_UNABLE_SAVE_TEMPLATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Undefined HID Report for the HID Class Descriptor.
        ///To fix this problem you can: 
        ///(1) Configure the HID Class Descriptor to refer to a HID Report, or
        ///(2) Remove the HID Class Descriptor from the Configuration..
        /// </summary>
        internal static string MSG_UNDEFINED_HIDREPORT {
            get {
                return ResourceManager.GetString("MSG_UNDEFINED_HIDREPORT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Parameter {0} has incorrect value. The default value will be used..
        /// </summary>
        internal static string MSG_WRONG_PARAMETER {
            get {
                return ResourceManager.GetString("MSG_WRONG_PARAMETER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Advanced.
        /// </summary>
        internal static string PAGE_TITLE_ADV {
            get {
                return ResourceManager.GetString("PAGE_TITLE_ADV", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Audio Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_AUDIODESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_AUDIODESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string PAGE_TITLE_BUILTIN {
            get {
                return ResourceManager.GetString("PAGE_TITLE_BUILTIN", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to CDC Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_CDCDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_CDCDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Device Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_DEVDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_DEVDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HID Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_HIDDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_HIDDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to String Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_STRDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_STRDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Undefined HID Report for the HID Class Descriptor. To fix this problem you can: (1) Configure the HID Class Descriptor to refer to a HID Report, or( 2) Remove the HID Class Descriptor from the Configuration..
        /// </summary>
        internal static string String {
            get {
                return ResourceManager.GetString("String", resourceCulture);
            }
        }
    }
}
