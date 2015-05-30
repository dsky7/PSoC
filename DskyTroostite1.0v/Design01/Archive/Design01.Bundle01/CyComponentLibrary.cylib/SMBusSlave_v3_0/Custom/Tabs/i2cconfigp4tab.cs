using System;
using System.Windows.Forms;

namespace SMBusSlave_v3_0
{
    public partial class CyI2cConfigP4Tab : CyTabWrapper
    {
        #region CyTabWrapper members
        public override string TabName
        {
            get
            {
                return "I2C Configuration P4";
            }
        }
        #endregion

        #region Constructor(s)
        public CyI2cConfigP4Tab(CyParameters parameters)
            : base(parameters)
        {            
            InitializeComponent();
            m_params.I2cConfigP4Tab = this;

            numOvsFactor.Minimum = CyParamRange.I2C_OVS_FACTOR_NOMEDFILTER_MIN;
            numOvsFactor.Maximum = CyParamRange.I2C_OVS_FACTOR_MAX;
            numOvsFactor.TextChanged += numOvsFactor_TextChanged;
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            numOvsFactor.Value = m_params.OvsFactor;
            chbClockFromTerminal.Checked = m_params.ClockFromTerm;
            chbMedianFilter.Checked = m_params.EnableMedianFilter;
            ValidateOvsFactor();
        }
        #endregion Update UI

        #region Validation
        private void ValidateOvsFactor()
        {
            byte ovsFactorValue;
            string errorMessage = String.Format(Resources.OvsFactorRangeError,
                CyParamRange.GetI2COvsFactorMinimum(m_params.EnableMedianFilter), CyParamRange.I2C_OVS_FACTOR_MAX);

            if (byte.TryParse(numOvsFactor.Text, out ovsFactorValue))
            {
                if (ovsFactorValue < CyParamRange.GetI2COvsFactorMinimum(m_params.EnableMedianFilter) ||
                    ovsFactorValue > CyParamRange.I2C_OVS_FACTOR_MAX)
                {
                    m_errorProvider.SetError(numOvsFactor, errorMessage);
                }
                else
                {
                    m_errorProvider.SetError(numOvsFactor, String.Empty);
                }
            }
            else
            {
                m_errorProvider.SetError(numOvsFactor, errorMessage);
            }
        }
        #endregion Validation

        #region Event handlers
        private void chbClockFromTerminal_CheckedChanged(object sender, EventArgs e)
        {
            m_params.ClockFromTerm = chbClockFromTerminal.Checked;
        }

        private void chbMedianFilter_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableMedianFilter = chbMedianFilter.Checked;
            ValidateOvsFactor();
        }

        void numOvsFactor_TextChanged(object sender, EventArgs e)
        {
            byte ovsFactorValue;
            if (byte.TryParse(numOvsFactor.Text, out ovsFactorValue))
            {
                m_params.OvsFactor = ovsFactorValue;
            }
            ValidateOvsFactor();
        }
        #endregion Event handlers
    }
}
