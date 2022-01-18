
namespace Maybe3DaysToDieToolEditor
{
    partial class PlacementObjectPanel
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
            this.groupBoxPlacementObject = new System.Windows.Forms.GroupBox();
            this.ToolKindsLabel = new System.Windows.Forms.Label();
            this.ToolComboBox = new System.Windows.Forms.ComboBox();
            this.DurableNumeric = new System.Windows.Forms.NumericUpDown();
            this.DurableLabel = new System.Windows.Forms.Label();
            this.groupBoxPlacementObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxPlacementObject
            // 
            this.groupBoxPlacementObject.Controls.Add(this.DurableNumeric);
            this.groupBoxPlacementObject.Controls.Add(this.DurableLabel);
            this.groupBoxPlacementObject.Controls.Add(this.ToolKindsLabel);
            this.groupBoxPlacementObject.Controls.Add(this.ToolComboBox);
            this.groupBoxPlacementObject.Location = new System.Drawing.Point(0, 0);
            this.groupBoxPlacementObject.Name = "groupBoxPlacementObject";
            this.groupBoxPlacementObject.Size = new System.Drawing.Size(1272, 520);
            this.groupBoxPlacementObject.TabIndex = 0;
            this.groupBoxPlacementObject.TabStop = false;
            this.groupBoxPlacementObject.Text = "PlacementObject";
            // 
            // ToolKindsLabel
            // 
            this.ToolKindsLabel.AutoSize = true;
            this.ToolKindsLabel.Location = new System.Drawing.Point(40, 99);
            this.ToolKindsLabel.Name = "ToolKindsLabel";
            this.ToolKindsLabel.Size = new System.Drawing.Size(72, 15);
            this.ToolKindsLabel.TabIndex = 25;
            this.ToolKindsLabel.Text = "適性ツール";
            // 
            // ToolComboBox
            // 
            this.ToolComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolComboBox.FormattingEnabled = true;
            this.ToolComboBox.Location = new System.Drawing.Point(118, 96);
            this.ToolComboBox.Name = "ToolComboBox";
            this.ToolComboBox.Size = new System.Drawing.Size(121, 23);
            this.ToolComboBox.TabIndex = 24;
            // 
            // DurableNumeric
            // 
            this.DurableNumeric.Location = new System.Drawing.Point(118, 47);
            this.DurableNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DurableNumeric.Name = "DurableNumeric";
            this.DurableNumeric.Size = new System.Drawing.Size(120, 22);
            this.DurableNumeric.TabIndex = 27;
            this.DurableNumeric.ThousandsSeparator = true;
            // 
            // DurableLabel
            // 
            this.DurableLabel.AutoSize = true;
            this.DurableLabel.Location = new System.Drawing.Point(60, 49);
            this.DurableLabel.Name = "DurableLabel";
            this.DurableLabel.Size = new System.Drawing.Size(52, 15);
            this.DurableLabel.TabIndex = 26;
            this.DurableLabel.Text = "耐久力";
            // 
            // PlacementObjectPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxPlacementObject);
            this.Name = "PlacementObjectPanel";
            this.Size = new System.Drawing.Size(1272, 520);
            this.groupBoxPlacementObject.ResumeLayout(false);
            this.groupBoxPlacementObject.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxPlacementObject;
        private System.Windows.Forms.Label ToolKindsLabel;
        private System.Windows.Forms.ComboBox ToolComboBox;
        private System.Windows.Forms.NumericUpDown DurableNumeric;
        private System.Windows.Forms.Label DurableLabel;
    }
}
