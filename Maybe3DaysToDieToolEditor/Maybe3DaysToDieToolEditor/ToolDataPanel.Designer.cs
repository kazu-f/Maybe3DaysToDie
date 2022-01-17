
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
            this.ToolKindsLabel = new System.Windows.Forms.Label();
            this.UseStaminaNumeric = new System.Windows.Forms.NumericUpDown();
            this.UseStaminaLabel = new System.Windows.Forms.Label();
            this.DurableNumeric = new System.Windows.Forms.NumericUpDown();
            this.DurableLabel = new System.Windows.Forms.Label();
            this.DamageNumeric = new System.Windows.Forms.NumericUpDown();
            this.DamageLabel = new System.Windows.Forms.Label();
            this.ToolComboBox = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.UseStaminaNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DamageNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // ToolKindsLabel
            // 
            this.ToolKindsLabel.AutoSize = true;
            this.ToolKindsLabel.Location = new System.Drawing.Point(44, 87);
            this.ToolKindsLabel.Name = "ToolKindsLabel";
            this.ToolKindsLabel.Size = new System.Drawing.Size(72, 15);
            this.ToolKindsLabel.TabIndex = 15;
            this.ToolKindsLabel.Text = "適性ツール";
            // 
            // UseStaminaNumeric
            // 
            this.UseStaminaNumeric.Location = new System.Drawing.Point(782, 35);
            this.UseStaminaNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.UseStaminaNumeric.Name = "UseStaminaNumeric";
            this.UseStaminaNumeric.Size = new System.Drawing.Size(120, 22);
            this.UseStaminaNumeric.TabIndex = 13;
            this.UseStaminaNumeric.ThousandsSeparator = true;
            this.UseStaminaNumeric.Leave += new System.EventHandler(this.LeaveUseStaminaValue);
            // 
            // UseStaminaLabel
            // 
            this.UseStaminaLabel.AutoSize = true;
            this.UseStaminaLabel.Location = new System.Drawing.Point(724, 35);
            this.UseStaminaLabel.Name = "UseStaminaLabel";
            this.UseStaminaLabel.Size = new System.Drawing.Size(49, 15);
            this.UseStaminaLabel.TabIndex = 12;
            this.UseStaminaLabel.Text = "スタミナ";
            // 
            // DurableNumeric
            // 
            this.DurableNumeric.Location = new System.Drawing.Point(456, 33);
            this.DurableNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DurableNumeric.Name = "DurableNumeric";
            this.DurableNumeric.Size = new System.Drawing.Size(120, 22);
            this.DurableNumeric.TabIndex = 11;
            this.DurableNumeric.ThousandsSeparator = true;
            this.DurableNumeric.Leave += new System.EventHandler(this.LeaveDurableValue);
            // 
            // DurableLabel
            // 
            this.DurableLabel.AutoSize = true;
            this.DurableLabel.Location = new System.Drawing.Point(398, 35);
            this.DurableLabel.Name = "DurableLabel";
            this.DurableLabel.Size = new System.Drawing.Size(52, 15);
            this.DurableLabel.TabIndex = 10;
            this.DurableLabel.Text = "耐久力";
            // 
            // DamageNumeric
            // 
            this.DamageNumeric.Location = new System.Drawing.Point(122, 35);
            this.DamageNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DamageNumeric.Name = "DamageNumeric";
            this.DamageNumeric.Size = new System.Drawing.Size(120, 22);
            this.DamageNumeric.TabIndex = 9;
            this.DamageNumeric.ThousandsSeparator = true;
            this.DamageNumeric.Leave += new System.EventHandler(this.LeaveDamageValue);
            // 
            // DamageLabel
            // 
            this.DamageLabel.AutoSize = true;
            this.DamageLabel.Location = new System.Drawing.Point(64, 35);
            this.DamageLabel.Name = "DamageLabel";
            this.DamageLabel.Size = new System.Drawing.Size(52, 15);
            this.DamageLabel.TabIndex = 8;
            this.DamageLabel.Text = "攻撃力";
            // 
            // ToolComboBox
            // 
            this.ToolComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolComboBox.FormattingEnabled = true;
            this.ToolComboBox.Location = new System.Drawing.Point(122, 84);
            this.ToolComboBox.Name = "ToolComboBox";
            this.ToolComboBox.Size = new System.Drawing.Size(121, 23);
            this.ToolComboBox.TabIndex = 14;
            this.ToolComboBox.SelectedIndexChanged += new System.EventHandler(this.ToolComboBox_SelectionChangeCommitted);
            // 
            // ToolDataPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ToolKindsLabel);
            this.Controls.Add(this.ToolComboBox);
            this.Controls.Add(this.UseStaminaNumeric);
            this.Controls.Add(this.UseStaminaLabel);
            this.Controls.Add(this.DurableNumeric);
            this.Controls.Add(this.DurableLabel);
            this.Controls.Add(this.DamageNumeric);
            this.Controls.Add(this.DamageLabel);
            this.Name = "ToolDataPanel";
            this.Size = new System.Drawing.Size(1272, 668);
            ((System.ComponentModel.ISupportInitialize)(this.UseStaminaNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DamageNumeric)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label ToolKindsLabel;
        private System.Windows.Forms.NumericUpDown UseStaminaNumeric;
        private System.Windows.Forms.Label UseStaminaLabel;
        private System.Windows.Forms.NumericUpDown DurableNumeric;
        private System.Windows.Forms.Label DurableLabel;
        private System.Windows.Forms.NumericUpDown DamageNumeric;
        private System.Windows.Forms.Label DamageLabel;
        private System.Windows.Forms.ComboBox ToolComboBox;
    }
}
