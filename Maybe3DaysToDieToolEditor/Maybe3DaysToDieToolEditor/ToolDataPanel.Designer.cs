
namespace Maybe3DaysToDieToolEditor
{
    partial class ToolDataPanel
    {
        /// <summary> 
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region コンポーネント デザイナーで生成されたコード

        /// <summary> 
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を 
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxToolData = new System.Windows.Forms.GroupBox();
            this.ToolKindsLabel = new System.Windows.Forms.Label();
            this.ToolComboBox = new System.Windows.Forms.ComboBox();
            this.UseStaminaNumeric = new System.Windows.Forms.NumericUpDown();
            this.UseStaminaLabel = new System.Windows.Forms.Label();
            this.DurableNumeric = new System.Windows.Forms.NumericUpDown();
            this.DurableLabel = new System.Windows.Forms.Label();
            this.DamageNumeric = new System.Windows.Forms.NumericUpDown();
            this.DamageLabel = new System.Windows.Forms.Label();
            this.groupBoxToolData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UseStaminaNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DamageNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxToolData
            // 
            this.groupBoxToolData.Controls.Add(this.ToolKindsLabel);
            this.groupBoxToolData.Controls.Add(this.ToolComboBox);
            this.groupBoxToolData.Controls.Add(this.UseStaminaNumeric);
            this.groupBoxToolData.Controls.Add(this.UseStaminaLabel);
            this.groupBoxToolData.Controls.Add(this.DurableNumeric);
            this.groupBoxToolData.Controls.Add(this.DurableLabel);
            this.groupBoxToolData.Controls.Add(this.DamageNumeric);
            this.groupBoxToolData.Controls.Add(this.DamageLabel);
            this.groupBoxToolData.Location = new System.Drawing.Point(0, 0);
            this.groupBoxToolData.Name = "groupBoxToolData";
            this.groupBoxToolData.Size = new System.Drawing.Size(1272, 668);
            this.groupBoxToolData.TabIndex = 16;
            this.groupBoxToolData.TabStop = false;
            this.groupBoxToolData.Text = "ToolData";
            this.groupBoxToolData.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // ToolKindsLabel
            // 
            this.ToolKindsLabel.AutoSize = true;
            this.ToolKindsLabel.Location = new System.Drawing.Point(40, 99);
            this.ToolKindsLabel.Name = "ToolKindsLabel";
            this.ToolKindsLabel.Size = new System.Drawing.Size(72, 15);
            this.ToolKindsLabel.TabIndex = 23;
            this.ToolKindsLabel.Text = "適性ツール";
            // 
            // ToolComboBox
            // 
            this.ToolComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolComboBox.FormattingEnabled = true;
            this.ToolComboBox.Location = new System.Drawing.Point(118, 96);
            this.ToolComboBox.Name = "ToolComboBox";
            this.ToolComboBox.Size = new System.Drawing.Size(121, 23);
            this.ToolComboBox.TabIndex = 22;
            // 
            // UseStaminaNumeric
            // 
            this.UseStaminaNumeric.Location = new System.Drawing.Point(778, 47);
            this.UseStaminaNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.UseStaminaNumeric.Name = "UseStaminaNumeric";
            this.UseStaminaNumeric.Size = new System.Drawing.Size(120, 22);
            this.UseStaminaNumeric.TabIndex = 21;
            this.UseStaminaNumeric.ThousandsSeparator = true;
            // 
            // UseStaminaLabel
            // 
            this.UseStaminaLabel.AutoSize = true;
            this.UseStaminaLabel.Location = new System.Drawing.Point(720, 47);
            this.UseStaminaLabel.Name = "UseStaminaLabel";
            this.UseStaminaLabel.Size = new System.Drawing.Size(49, 15);
            this.UseStaminaLabel.TabIndex = 20;
            this.UseStaminaLabel.Text = "スタミナ";
            // 
            // DurableNumeric
            // 
            this.DurableNumeric.Location = new System.Drawing.Point(452, 45);
            this.DurableNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DurableNumeric.Name = "DurableNumeric";
            this.DurableNumeric.Size = new System.Drawing.Size(120, 22);
            this.DurableNumeric.TabIndex = 19;
            this.DurableNumeric.ThousandsSeparator = true;
            // 
            // DurableLabel
            // 
            this.DurableLabel.AutoSize = true;
            this.DurableLabel.Location = new System.Drawing.Point(394, 47);
            this.DurableLabel.Name = "DurableLabel";
            this.DurableLabel.Size = new System.Drawing.Size(52, 15);
            this.DurableLabel.TabIndex = 18;
            this.DurableLabel.Text = "耐久力";
            // 
            // DamageNumeric
            // 
            this.DamageNumeric.Location = new System.Drawing.Point(118, 47);
            this.DamageNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DamageNumeric.Name = "DamageNumeric";
            this.DamageNumeric.Size = new System.Drawing.Size(120, 22);
            this.DamageNumeric.TabIndex = 17;
            this.DamageNumeric.ThousandsSeparator = true;
            // 
            // DamageLabel
            // 
            this.DamageLabel.AutoSize = true;
            this.DamageLabel.Location = new System.Drawing.Point(60, 47);
            this.DamageLabel.Name = "DamageLabel";
            this.DamageLabel.Size = new System.Drawing.Size(52, 15);
            this.DamageLabel.TabIndex = 16;
            this.DamageLabel.Text = "攻撃力";
            // 
            // ToolDataPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxToolData);
            this.Name = "ToolDataPanel";
            this.Size = new System.Drawing.Size(1272, 668);
            this.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            this.groupBoxToolData.ResumeLayout(false);
            this.groupBoxToolData.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UseStaminaNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DamageNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxToolData;
        private System.Windows.Forms.Label ToolKindsLabel;
        private System.Windows.Forms.ComboBox ToolComboBox;
        private System.Windows.Forms.NumericUpDown UseStaminaNumeric;
        private System.Windows.Forms.Label UseStaminaLabel;
        private System.Windows.Forms.NumericUpDown DurableNumeric;
        private System.Windows.Forms.Label DurableLabel;
        private System.Windows.Forms.NumericUpDown DamageNumeric;
        private System.Windows.Forms.Label DamageLabel;
    }
}
