namespace Bootloadable_v1_20
{
    partial class CyDependenciesPage
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDependenciesPage));
            this.labelInfo = new System.Windows.Forms.Label();
            this.labelHexFile = new System.Windows.Forms.Label();
            this.textBoxHexFilePath = new System.Windows.Forms.TextBox();
            this.buttonBrowseHex = new System.Windows.Forms.Button();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.buttonBrowseElf = new System.Windows.Forms.Button();
            this.textBoxElfFilePath = new System.Windows.Forms.TextBox();
            this.labelElfFile = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // labelInfo
            // 
            this.labelInfo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.labelInfo.Location = new System.Drawing.Point(3, 9);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(326, 55);
            this.labelInfo.TabIndex = 2;
            this.labelInfo.Text = resources.GetString("labelInfo.Text");
            // 
            // labelHexFile
            // 
            this.labelHexFile.AutoSize = true;
            this.labelHexFile.Location = new System.Drawing.Point(3, 64);
            this.labelHexFile.Name = "labelHexFile";
            this.labelHexFile.Size = new System.Drawing.Size(102, 13);
            this.labelHexFile.TabIndex = 3;
            this.labelHexFile.Text = "Bootloader HEX file:";
            // 
            // textBoxHexFilePath
            // 
            this.textBoxHexFilePath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxHexFilePath.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.textBoxHexFilePath.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.textBoxHexFilePath.Location = new System.Drawing.Point(6, 80);
            this.textBoxHexFilePath.Name = "textBoxHexFilePath";
            this.textBoxHexFilePath.Size = new System.Drawing.Size(323, 20);
            this.textBoxHexFilePath.TabIndex = 5;
            this.textBoxHexFilePath.TextChanged += new System.EventHandler(this.textBoxHexFilePath_TextChanged);
            // 
            // buttonBrowseHex
            // 
            this.buttonBrowseHex.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonBrowseHex.Location = new System.Drawing.Point(252, 106);
            this.buttonBrowseHex.Name = "buttonBrowseHex";
            this.buttonBrowseHex.Size = new System.Drawing.Size(77, 23);
            this.buttonBrowseHex.TabIndex = 7;
            this.buttonBrowseHex.Text = "Browse...";
            this.buttonBrowseHex.UseVisualStyleBackColor = true;
            this.buttonBrowseHex.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // buttonBrowseElf
            // 
            this.buttonBrowseElf.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonBrowseElf.Location = new System.Drawing.Point(252, 173);
            this.buttonBrowseElf.Name = "buttonBrowseElf";
            this.buttonBrowseElf.Size = new System.Drawing.Size(77, 23);
            this.buttonBrowseElf.TabIndex = 10;
            this.buttonBrowseElf.Text = "Browse...";
            this.buttonBrowseElf.UseVisualStyleBackColor = true;
            this.buttonBrowseElf.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // textBoxElfFilePath
            // 
            this.textBoxElfFilePath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxElfFilePath.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.textBoxElfFilePath.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.textBoxElfFilePath.Location = new System.Drawing.Point(6, 147);
            this.textBoxElfFilePath.Name = "textBoxElfFilePath";
            this.textBoxElfFilePath.Size = new System.Drawing.Size(323, 20);
            this.textBoxElfFilePath.TabIndex = 9;
            this.textBoxElfFilePath.TextChanged += new System.EventHandler(this.textBoxElfFilePath_TextChanged);
            // 
            // labelElfFile
            // 
            this.labelElfFile.AutoSize = true;
            this.labelElfFile.Location = new System.Drawing.Point(3, 131);
            this.labelElfFile.Name = "labelElfFile";
            this.labelElfFile.Size = new System.Drawing.Size(99, 13);
            this.labelElfFile.TabIndex = 8;
            this.labelElfFile.Text = "Bootloader ELF file:";
            // 
            // CyDependenciesPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.buttonBrowseElf);
            this.Controls.Add(this.textBoxElfFilePath);
            this.Controls.Add(this.labelElfFile);
            this.Controls.Add(this.buttonBrowseHex);
            this.Controls.Add(this.textBoxHexFilePath);
            this.Controls.Add(this.labelHexFile);
            this.Controls.Add(this.labelInfo);
            this.Name = "CyDependenciesPage";
            this.Size = new System.Drawing.Size(352, 298);
            this.Load += new System.EventHandler(this.CyDependenciesPage_Load);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.Label labelHexFile;
        private System.Windows.Forms.TextBox textBoxHexFilePath;
        private System.Windows.Forms.Button buttonBrowseHex;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Button buttonBrowseElf;
        private System.Windows.Forms.TextBox textBoxElfFilePath;
        private System.Windows.Forms.Label labelElfFile;
    }
}
