namespace WindowsFormsApplication1
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.GetPlatformInfo = new System.Windows.Forms.Button();
            this.Clear = new System.Windows.Forms.Button();
            this.GetOSInfo = new System.Windows.Forms.Button();
            this.GetCurrInfo = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // GetPlatformInfo
            // 
            this.GetPlatformInfo.Location = new System.Drawing.Point(22, 29);
            this.GetPlatformInfo.Name = "GetPlatformInfo";
            this.GetPlatformInfo.Size = new System.Drawing.Size(88, 23);
            this.GetPlatformInfo.TabIndex = 0;
            this.GetPlatformInfo.Text = "GetPlatformInfo";
            this.GetPlatformInfo.UseVisualStyleBackColor = true;
            this.GetPlatformInfo.Click += new System.EventHandler(this.GetPlatformInfo_Click);
            // 
            // Clear
            // 
            this.Clear.Location = new System.Drawing.Point(22, 218);
            this.Clear.Name = "Clear";
            this.Clear.Size = new System.Drawing.Size(88, 23);
            this.Clear.TabIndex = 2;
            this.Clear.Text = "Clear";
            this.Clear.UseVisualStyleBackColor = true;
            this.Clear.Click += new System.EventHandler(this.Clear_Click);
            // 
            // GetOSInfo
            // 
            this.GetOSInfo.Location = new System.Drawing.Point(22, 77);
            this.GetOSInfo.Name = "GetOSInfo";
            this.GetOSInfo.Size = new System.Drawing.Size(88, 23);
            this.GetOSInfo.TabIndex = 3;
            this.GetOSInfo.Text = "GetOSInfo";
            this.GetOSInfo.UseVisualStyleBackColor = true;
            this.GetOSInfo.Click += new System.EventHandler(this.GetOSInfo_Click);
            // 
            // GetCurrInfo
            // 
            this.GetCurrInfo.Location = new System.Drawing.Point(22, 127);
            this.GetCurrInfo.Name = "GetCurrInfo";
            this.GetCurrInfo.Size = new System.Drawing.Size(88, 23);
            this.GetCurrInfo.TabIndex = 4;
            this.GetCurrInfo.Text = "GetCurrInfo";
            this.GetCurrInfo.UseVisualStyleBackColor = true;
            this.GetCurrInfo.Click += new System.EventHandler(this.GetCurrInfo_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.Location = new System.Drawing.Point(140, 29);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(152, 212);
            this.listBox1.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(317, 313);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.GetCurrInfo);
            this.Controls.Add(this.GetOSInfo);
            this.Controls.Add(this.Clear);
            this.Controls.Add(this.GetPlatformInfo);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button GetPlatformInfo;
        private System.Windows.Forms.Button Clear;
        private System.Windows.Forms.Button GetOSInfo;
        private System.Windows.Forms.Button GetCurrInfo;
        private System.Windows.Forms.ListBox listBox1;
    }
}

