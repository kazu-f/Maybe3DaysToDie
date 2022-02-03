
namespace Maybe3DaysToDieToolEditor
{
    partial class FoodAndCurePanel
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
            this.FoodAndCureGroupBox = new System.Windows.Forms.GroupBox();
            this.StaminaNumeric = new System.Windows.Forms.NumericUpDown();
            this.StaminaLabel = new System.Windows.Forms.Label();
            this.FoodNumeric = new System.Windows.Forms.NumericUpDown();
            this.FoodLabel = new System.Windows.Forms.Label();
            this.WaterNumeric = new System.Windows.Forms.NumericUpDown();
            this.WaterLabel = new System.Windows.Forms.Label();
            this.HPNumeric = new System.Windows.Forms.NumericUpDown();
            this.HPLabel = new System.Windows.Forms.Label();
            this.FoodAndCureGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.StaminaNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FoodNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WaterNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HPNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // FoodAndCureGroupBox
            // 
            this.FoodAndCureGroupBox.Controls.Add(this.StaminaNumeric);
            this.FoodAndCureGroupBox.Controls.Add(this.StaminaLabel);
            this.FoodAndCureGroupBox.Controls.Add(this.FoodNumeric);
            this.FoodAndCureGroupBox.Controls.Add(this.FoodLabel);
            this.FoodAndCureGroupBox.Controls.Add(this.WaterNumeric);
            this.FoodAndCureGroupBox.Controls.Add(this.WaterLabel);
            this.FoodAndCureGroupBox.Controls.Add(this.HPNumeric);
            this.FoodAndCureGroupBox.Controls.Add(this.HPLabel);
            this.FoodAndCureGroupBox.Location = new System.Drawing.Point(0, 0);
            this.FoodAndCureGroupBox.Name = "FoodAndCureGroupBox";
            this.FoodAndCureGroupBox.Size = new System.Drawing.Size(820, 520);
            this.FoodAndCureGroupBox.TabIndex = 90;
            this.FoodAndCureGroupBox.TabStop = false;
            this.FoodAndCureGroupBox.Text = "EatAndCure";
            this.FoodAndCureGroupBox.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // StaminaNumeric
            // 
            this.StaminaNumeric.Location = new System.Drawing.Point(390, 105);
            this.StaminaNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.StaminaNumeric.Name = "StaminaNumeric";
            this.StaminaNumeric.Size = new System.Drawing.Size(120, 22);
            this.StaminaNumeric.TabIndex = 98;
            this.StaminaNumeric.ThousandsSeparator = true;
            this.StaminaNumeric.Leave += new System.EventHandler(this.StaminaNumericLeave);
            // 
            // StaminaLabel
            // 
            this.StaminaLabel.AutoSize = true;
            this.StaminaLabel.Location = new System.Drawing.Point(330, 105);
            this.StaminaLabel.Name = "StaminaLabel";
            this.StaminaLabel.Size = new System.Drawing.Size(49, 15);
            this.StaminaLabel.TabIndex = 97;
            this.StaminaLabel.Text = "スタミナ";
            // 
            // FoodNumeric
            // 
            this.FoodNumeric.Location = new System.Drawing.Point(120, 105);
            this.FoodNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.FoodNumeric.Name = "FoodNumeric";
            this.FoodNumeric.Size = new System.Drawing.Size(120, 22);
            this.FoodNumeric.TabIndex = 96;
            this.FoodNumeric.ThousandsSeparator = true;
            this.FoodNumeric.Leave += new System.EventHandler(this.FoodNumericLeave);
            // 
            // FoodLabel
            // 
            this.FoodLabel.AutoSize = true;
            this.FoodLabel.Location = new System.Drawing.Point(60, 105);
            this.FoodLabel.Name = "FoodLabel";
            this.FoodLabel.Size = new System.Drawing.Size(52, 15);
            this.FoodLabel.TabIndex = 95;
            this.FoodLabel.Text = "満腹度";
            // 
            // WaterNumeric
            // 
            this.WaterNumeric.Location = new System.Drawing.Point(390, 50);
            this.WaterNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.WaterNumeric.Name = "WaterNumeric";
            this.WaterNumeric.Size = new System.Drawing.Size(120, 22);
            this.WaterNumeric.TabIndex = 94;
            this.WaterNumeric.ThousandsSeparator = true;
            this.WaterNumeric.Leave += new System.EventHandler(this.WaterNumericLeave);
            // 
            // WaterLabel
            // 
            this.WaterLabel.AutoSize = true;
            this.WaterLabel.Location = new System.Drawing.Point(330, 50);
            this.WaterLabel.Name = "WaterLabel";
            this.WaterLabel.Size = new System.Drawing.Size(37, 15);
            this.WaterLabel.TabIndex = 93;
            this.WaterLabel.Text = "水分";
            // 
            // HPNumeric
            // 
            this.HPNumeric.Location = new System.Drawing.Point(120, 50);
            this.HPNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.HPNumeric.Name = "HPNumeric";
            this.HPNumeric.Size = new System.Drawing.Size(120, 22);
            this.HPNumeric.TabIndex = 92;
            this.HPNumeric.ThousandsSeparator = true;
            this.HPNumeric.Leave += new System.EventHandler(this.HPNumericLeave);
            // 
            // HPLabel
            // 
            this.HPLabel.AutoSize = true;
            this.HPLabel.Location = new System.Drawing.Point(60, 50);
            this.HPLabel.Name = "HPLabel";
            this.HPLabel.Size = new System.Drawing.Size(26, 15);
            this.HPLabel.TabIndex = 91;
            this.HPLabel.Text = "HP";
            // 
            // FoodAndCurePanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.FoodAndCureGroupBox);
            this.Name = "FoodAndCurePanel";
            this.Size = new System.Drawing.Size(820, 520);
            this.FoodAndCureGroupBox.ResumeLayout(false);
            this.FoodAndCureGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.StaminaNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FoodNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WaterNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HPNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox FoodAndCureGroupBox;
        private System.Windows.Forms.NumericUpDown HPNumeric;
        private System.Windows.Forms.Label HPLabel;
        private System.Windows.Forms.NumericUpDown WaterNumeric;
        private System.Windows.Forms.Label WaterLabel;
        private System.Windows.Forms.NumericUpDown FoodNumeric;
        private System.Windows.Forms.Label FoodLabel;
        private System.Windows.Forms.NumericUpDown StaminaNumeric;
        private System.Windows.Forms.Label StaminaLabel;
    }
}
