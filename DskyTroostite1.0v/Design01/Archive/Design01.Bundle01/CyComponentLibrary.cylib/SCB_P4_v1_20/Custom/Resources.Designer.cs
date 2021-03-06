﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace SCB_P4_v1_20 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("SCB_P4_v1_20.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Actual baud rate (bps): {0}.
        /// </summary>
        internal static string ActualBaudRateDisplayFormat {
            get {
                return ResourceManager.GetString("ActualBaudRateDisplayFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Actual bit rate (kbps): {0}.
        /// </summary>
        internal static string ActualBitRateDisplayFormat {
            get {
                return ResourceManager.GetString("ActualBitRateDisplayFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Actual data rate (kbps): {0}.
        /// </summary>
        internal static string ActualDataRateDisplayFormat {
            get {
                return ResourceManager.GetString("ActualDataRateDisplayFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The baud rate value must be 115200, 57600, 38400, 19200, 9600, 2400 or 1200 kbps when the IrDA mode is selected..
        /// </summary>
        internal static string BaudRateIrDAValueError {
            get {
                return ResourceManager.GetString("BaudRateIrDAValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The baud rate must be between {0} and {1} bps..
        /// </summary>
        internal static string BaudRateValueError {
            get {
                return ResourceManager.GetString("BaudRateValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The current SCB mode is not supported by the bootloader..
        /// </summary>
        internal static string BootloaderSupportModeFailError {
            get {
                return ResourceManager.GetString("BootloaderSupportModeFailError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabDisplayName {
            get {
                return ResourceManager.GetString("BuiltInTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UNKNOWN.
        /// </summary>
        internal static string ClockDisplayUnknown {
            get {
                return ResourceManager.GetString("ClockDisplayUnknown", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The clock value must be between {0} and {1}..
        /// </summary>
        internal static string ClockValueError {
            get {
                return ResourceManager.GetString("ClockValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The data rate value must be between {0} and {1} kbps for the selected device..
        /// </summary>
        internal static string DataRateDeviceError {
            get {
                return ResourceManager.GetString("DataRateDeviceError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The data rate value must be between {0} and {1} kbps..
        /// </summary>
        internal static string DataRateValueError {
            get {
                return ResourceManager.GetString("DataRateValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The data rate value must be between {0} and {1} kbps when clock stretching is disabled..
        /// </summary>
        internal static string DataRateValueErrorNonClockStretching {
            get {
                return ResourceManager.GetString("DataRateValueErrorNonClockStretching", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Median filter is not applicable if wakeup from the sleep mode option is enabled for the selected device..
        /// </summary>
        internal static string ErrMsgMedianFilter {
            get {
                return ResourceManager.GetString("ErrMsgMedianFilter", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Wakeup from the sleep mode is not supported if clock stretching is disabled for the selected device..
        /// </summary>
        internal static string ErrMsgWakeUpFromSleep {
            get {
                return ResourceManager.GetString("ErrMsgWakeUpFromSleep", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between 3 and 16 when median filter is disabled and late MISO sample is enabled..
        /// </summary>
        internal static string ErrorMsgMedDisMiso {
            get {
                return ResourceManager.GetString("ErrorMsgMedDisMiso", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between 6 and 16 when the median filter and late MISO sample are disabled..
        /// </summary>
        internal static string ErrorMsgMedDisMisoDis {
            get {
                return ResourceManager.GetString("ErrorMsgMedDisMisoDis", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between 4 and 16 when the median filter and late MISO sample are enabled..
        /// </summary>
        internal static string ErrorMsgMedMiso {
            get {
                return ResourceManager.GetString("ErrorMsgMedMiso", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between 8 and 16 when the median filter is enabled and late MISO sample is disabled..
        /// </summary>
        internal static string ErrorMsgMedMisoDis {
            get {
                return ResourceManager.GetString("ErrorMsgMedMisoDis", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value must be between {0} and {1}..
        /// </summary>
        internal static string ErrorValueLimit {
            get {
                return ResourceManager.GetString("ErrorValueLimit", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value must be between {0} and maximum available memory in device..
        /// </summary>
        internal static string ErrorValueLimitBufferSize {
            get {
                return ResourceManager.GetString("ErrorValueLimitBufferSize", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The EZI2C slave address must be between {0} and {1}. Other addresses are not allowed by the I2C spec..
        /// </summary>
        internal static string EZI2CSlaveAddressError {
            get {
                return ResourceManager.GetString("EZI2CSlaveAddressError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The primary slave address and Secondary slave address must not be equal..
        /// </summary>
        internal static string EZI2CSlaveAddressesEqualError {
            get {
                return ResourceManager.GetString("EZI2CSlaveAddressesEqualError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to EZI2C.
        /// </summary>
        internal static string EZI2CTabDisplayName {
            get {
                return ResourceManager.GetString("EZI2CTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Configuration.
        /// </summary>
        internal static string GeneralTabDisplayName {
            get {
                return ResourceManager.GetString("GeneralTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The HFCLK is undefined or has been changed. Open {0} the configuration dialog to update Data Rate..
        /// </summary>
        internal static string HclkError {
            get {
                return ResourceManager.GetString("HclkError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The HFCLK is undefined or has been changed. Open {0} the configuration dialog to update Data Rate..
        /// </summary>
        internal static string HclkError1 {
            get {
                return ResourceManager.GetString("HclkError1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The I2C instance &apos;{0}&apos; is not configured as Slave or Multi-Master-Slave, but has been chosen as the bootloader IO component..
        /// </summary>
        internal static string I2CNotContainSlave {
            get {
                return ResourceManager.GetString("I2CNotContainSlave", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The I2C slave address must be between {0} and {1}. Other addresses are not allowed by the I2C spec..
        /// </summary>
        internal static string I2CSlaveAddressError {
            get {
                return ResourceManager.GetString("I2CSlaveAddressError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The 2C slave address mask must be between {0} and {1}..
        /// </summary>
        internal static string I2CSlaveAddressMaskError {
            get {
                return ResourceManager.GetString("I2CSlaveAddressMaskError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to I2C.
        /// </summary>
        internal static string I2CTabDisplayName {
            get {
                return ResourceManager.GetString("I2CTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap Motorola_00 {
            get {
                object obj = ResourceManager.GetObject("Motorola_00", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between {0} and {1} when the median filter is disabled..
        /// </summary>
        internal static string OvsFactorFilterDisabledError {
            get {
                return ResourceManager.GetString("OvsFactorFilterDisabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between {0} and {1} when the median filter is enabled..
        /// </summary>
        internal static string OvsFactorFilterEnabledError {
            get {
                return ResourceManager.GetString("OvsFactorFilterEnabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor high must be at least {0} when the median filter is disabled..
        /// </summary>
        internal static string OvsHighFilterDisabledError {
            get {
                return ResourceManager.GetString("OvsHighFilterDisabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor high must be at least {0} when the median filter is enabled..
        /// </summary>
        internal static string OvsHighFilterEnabledError {
            get {
                return ResourceManager.GetString("OvsHighFilterEnabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The sum of the oversampling factor low and high must be equal to the oversampling factor value.
        /// </summary>
        internal static string OvsHighOutOfRangeError {
            get {
                return ResourceManager.GetString("OvsHighOutOfRangeError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor low must be at least {0} when the median filter is disabled..
        /// </summary>
        internal static string OvsLowFilterDisabledError {
            get {
                return ResourceManager.GetString("OvsLowFilterDisabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor low must be at least {0} when the median filter is enabled..
        /// </summary>
        internal static string OvsLowFilterEnabledError {
            get {
                return ResourceManager.GetString("OvsLowFilterEnabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The sum of the oversampling factor low and high must be equal to the oversampling factor value.
        /// </summary>
        internal static string OvsLowOutOfRangeError {
            get {
                return ResourceManager.GetString("OvsLowOutOfRangeError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to SCB.
        /// </summary>
        internal static string SCBTabDisplayName {
            get {
                return ResourceManager.GetString("SCBTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0} mode is not available for the selected device. Select another SCB mode..
        /// </summary>
        internal static string SFModeError {
            get {
                return ResourceManager.GetString("SFModeError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The SPI and UART mode are not available for the selected device. Launch the SCB configuration dialog and remove the SPI pins or disable the UART RX wake option on the SCB tab..
        /// </summary>
        internal static string SFSettingsDRCError {
            get {
                return ResourceManager.GetString("SFSettingsDRCError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The {0} option is not available for the selected device..
        /// </summary>
        internal static string SFSettingsError {
            get {
                return ResourceManager.GetString("SFSettingsError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value of the slave address mask bit1 must be one when wakeup from the sleep mode option is enabled for the selected device..
        /// </summary>
        internal static string SlaveAddressMaskBitOneError {
            get {
                return ResourceManager.GetString("SlaveAddressMaskBitOneError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value of the slave address mask must be even..
        /// </summary>
        internal static string SlaveAddressMaskOddError {
            get {
                return ResourceManager.GetString("SlaveAddressMaskOddError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value of the slave address must be even when wakeup the from sleep mode option is enabled for the selected device..
        /// </summary>
        internal static string SlaveAddressOddError {
            get {
                return ResourceManager.GetString("SlaveAddressOddError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to SPI Advanced.
        /// </summary>
        internal static string SPIAdvancedTabDisplayName {
            get {
                return ResourceManager.GetString("SPIAdvancedTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to SPI Basic.
        /// </summary>
        internal static string SPIBasicTabDisplayName {
            get {
                return ResourceManager.GetString("SPIBasicTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap SymbolInformation {
            get {
                object obj = ResourceManager.GetObject("SymbolInformation", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Calculated THi = {0} ns less than tHigh = {1} ns defined by I2C spec for fSCL = {2} KHz. Increase the oversampling factor high..
        /// </summary>
        internal static string THiError {
            get {
                return ResourceManager.GetString("THiError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Calculated TLo = {0} ns less than tLow = {1} ns defined by I2C spec for fSCL = {2} KHz. Increase the oversampling factor low..
        /// </summary>
        internal static string TLoError {
            get {
                return ResourceManager.GetString("TLoError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value must be between {0} and {1}..
        /// </summary>
        internal static string UARTAddressFormatError {
            get {
                return ResourceManager.GetString("UARTAddressFormatError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UART Advanced.
        /// </summary>
        internal static string UARTAdvancedTabDisplayName {
            get {
                return ResourceManager.GetString("UARTAdvancedTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The buffer size value has an invalid format..
        /// </summary>
        internal static string UARTBufferSizeValueFormatError {
            get {
                return ResourceManager.GetString("UARTBufferSizeValueFormatError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to UART Basic.
        /// </summary>
        internal static string UARTConfigTabDisplayName {
            get {
                return ResourceManager.GetString("UARTConfigTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The selected mode does not support the {0} value. Set a different data bits value..
        /// </summary>
        internal static string UARTDataBitsValueError {
            get {
                return ResourceManager.GetString("UARTDataBitsValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The oversampling factor must be between {0} and {1}..
        /// </summary>
        internal static string UARTOvsFactorError {
            get {
                return ResourceManager.GetString("UARTOvsFactorError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The UART RX buffer size must be between {0} and the maximum memory size in the system..
        /// </summary>
        internal static string UARTRXBufferSizeError {
            get {
                return ResourceManager.GetString("UARTRXBufferSizeError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to When the SmartCard mode is selected, the stop bits value should be 2..
        /// </summary>
        internal static string UARTStopBitsSmartCardError {
            get {
                return ResourceManager.GetString("UARTStopBitsSmartCardError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The UART TX buffer size must be between {0} and the maximum memory size in the system..
        /// </summary>
        internal static string UARTTXBufferSizeError {
            get {
                return ResourceManager.GetString("UARTTXBufferSizeError", resourceCulture);
            }
        }
    }
}
