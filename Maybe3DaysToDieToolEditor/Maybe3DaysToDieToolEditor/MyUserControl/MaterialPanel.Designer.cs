
namespace Maybe3DaysToDieToolEditor
{
    partial class MaterialPanel
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
            this.MaterialPanelGroupBox = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // MaterialPanelGroupBox
            // 
            this.MaterialPanelGroupBox.Location = new System.Drawing.Point(0, 0);
            this.MaterialPanelGroupBox.Name = "MaterialPanelGroupBox";
            this.MaterialPanelGroupBox.Size = new System.Drawing.Size(820, 520);
            this.MaterialPanelGroupBox.TabIndex = 0;
            this.MaterialPanelGroupBox.TabStop = false;
            this.MaterialPanelGroupBox.Text = "Material";
            // 
            // MaterialPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.MaterialPanelGroupBox);
            this.Name = "MaterialPanel";
            this.Size = new System.Drawing.Size(820, 520);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox MaterialPanelGroupBox;
    }
}
