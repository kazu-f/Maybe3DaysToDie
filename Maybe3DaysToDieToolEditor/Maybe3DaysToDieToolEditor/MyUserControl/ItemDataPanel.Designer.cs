
namespace Maybe3DaysToDieToolEditor
{
    partial class ItemDataPanel
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
            this.ItemDataGroupBox = new System.Windows.Forms.GroupBox();
            this.MaxItemStackNumeric = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.ItemIDDispLabel = new System.Windows.Forms.Label();
            this.ItemIDLabel = new System.Windows.Forms.Label();
            this.IconFileSelectButton = new System.Windows.Forms.Button();
            this.ModelFileSelectButton = new System.Windows.Forms.Button();
            this.ItemNameLabel = new System.Windows.Forms.Label();
            this.IconDataTextBox = new System.Windows.Forms.TextBox();
            this.ModelFilePathTextBox = new System.Windows.Forms.TextBox();
            this.IconDataLabel = new System.Windows.Forms.Label();
            this.NameTextBox = new System.Windows.Forms.TextBox();
            this.ModelDataLabel = new System.Windows.Forms.Label();
            this.ItemDataGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MaxItemStackNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // ItemDataGroupBox
            // 
            this.ItemDataGroupBox.Controls.Add(this.MaxItemStackNumeric);
            this.ItemDataGroupBox.Controls.Add(this.label1);
            this.ItemDataGroupBox.Controls.Add(this.ItemIDDispLabel);
            this.ItemDataGroupBox.Controls.Add(this.ItemIDLabel);
            this.ItemDataGroupBox.Controls.Add(this.IconFileSelectButton);
            this.ItemDataGroupBox.Controls.Add(this.ModelFileSelectButton);
            this.ItemDataGroupBox.Controls.Add(this.ItemNameLabel);
            this.ItemDataGroupBox.Controls.Add(this.IconDataTextBox);
            this.ItemDataGroupBox.Controls.Add(this.ModelFilePathTextBox);
            this.ItemDataGroupBox.Controls.Add(this.IconDataLabel);
            this.ItemDataGroupBox.Controls.Add(this.NameTextBox);
            this.ItemDataGroupBox.Controls.Add(this.ModelDataLabel);
            this.ItemDataGroupBox.Location = new System.Drawing.Point(0, 0);
            this.ItemDataGroupBox.Name = "ItemDataGroupBox";
            this.ItemDataGroupBox.Size = new System.Drawing.Size(1270, 270);
            this.ItemDataGroupBox.TabIndex = 0;
            this.ItemDataGroupBox.TabStop = false;
            this.ItemDataGroupBox.Text = "ItemData";
            this.ItemDataGroupBox.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // MaxItemStackNumeric
            // 
            this.MaxItemStackNumeric.Location = new System.Drawing.Point(1082, 64);
            this.MaxItemStackNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.MaxItemStackNumeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.MaxItemStackNumeric.Name = "MaxItemStackNumeric";
            this.MaxItemStackNumeric.Size = new System.Drawing.Size(120, 22);
            this.MaxItemStackNumeric.TabIndex = 12;
            this.MaxItemStackNumeric.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.MaxItemStackNumeric.Leave += new System.EventHandler(this.ItemStackNumeric_Leave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(976, 66);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 15);
            this.label1.TabIndex = 11;
            this.label1.Text = "ItemStackNum";
            // 
            // ItemIDDispLabel
            // 
            this.ItemIDDispLabel.Location = new System.Drawing.Point(1082, 34);
            this.ItemIDDispLabel.Name = "ItemIDDispLabel";
            this.ItemIDDispLabel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ItemIDDispLabel.Size = new System.Drawing.Size(100, 23);
            this.ItemIDDispLabel.TabIndex = 10;
            this.ItemIDDispLabel.Text = "0";
            this.ItemIDDispLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // ItemIDLabel
            // 
            this.ItemIDLabel.AutoSize = true;
            this.ItemIDLabel.Location = new System.Drawing.Point(1055, 38);
            this.ItemIDLabel.Name = "ItemIDLabel";
            this.ItemIDLabel.Size = new System.Drawing.Size(21, 15);
            this.ItemIDLabel.TabIndex = 9;
            this.ItemIDLabel.Text = "ID";
            // 
            // IconFileSelectButton
            // 
            this.IconFileSelectButton.Location = new System.Drawing.Point(847, 91);
            this.IconFileSelectButton.Name = "IconFileSelectButton";
            this.IconFileSelectButton.Size = new System.Drawing.Size(102, 23);
            this.IconFileSelectButton.TabIndex = 8;
            this.IconFileSelectButton.Text = "ファイル選択";
            this.IconFileSelectButton.UseVisualStyleBackColor = true;
            // 
            // ModelFileSelectButton
            // 
            this.ModelFileSelectButton.Location = new System.Drawing.Point(847, 63);
            this.ModelFileSelectButton.Name = "ModelFileSelectButton";
            this.ModelFileSelectButton.Size = new System.Drawing.Size(102, 23);
            this.ModelFileSelectButton.TabIndex = 5;
            this.ModelFileSelectButton.Text = "ファイル選択";
            this.ModelFileSelectButton.UseVisualStyleBackColor = true;
            // 
            // ItemNameLabel
            // 
            this.ItemNameLabel.AutoSize = true;
            this.ItemNameLabel.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.ItemNameLabel.Location = new System.Drawing.Point(33, 38);
            this.ItemNameLabel.Name = "ItemNameLabel";
            this.ItemNameLabel.Size = new System.Drawing.Size(71, 15);
            this.ItemNameLabel.TabIndex = 1;
            this.ItemNameLabel.Text = "ItemName";
            // 
            // IconDataTextBox
            // 
            this.IconDataTextBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.IconDataTextBox.Location = new System.Drawing.Point(127, 91);
            this.IconDataTextBox.Name = "IconDataTextBox";
            this.IconDataTextBox.ReadOnly = true;
            this.IconDataTextBox.Size = new System.Drawing.Size(703, 22);
            this.IconDataTextBox.TabIndex = 7;
            // 
            // ModelFilePathTextBox
            // 
            this.ModelFilePathTextBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ModelFilePathTextBox.Location = new System.Drawing.Point(127, 63);
            this.ModelFilePathTextBox.Name = "ModelFilePathTextBox";
            this.ModelFilePathTextBox.ReadOnly = true;
            this.ModelFilePathTextBox.Size = new System.Drawing.Size(703, 22);
            this.ModelFilePathTextBox.TabIndex = 4;
            // 
            // IconDataLabel
            // 
            this.IconDataLabel.AutoSize = true;
            this.IconDataLabel.Location = new System.Drawing.Point(32, 95);
            this.IconDataLabel.Name = "IconDataLabel";
            this.IconDataLabel.Size = new System.Drawing.Size(64, 15);
            this.IconDataLabel.TabIndex = 6;
            this.IconDataLabel.Text = "IconData";
            // 
            // NameTextBox
            // 
            this.NameTextBox.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.NameTextBox.Location = new System.Drawing.Point(127, 35);
            this.NameTextBox.Name = "NameTextBox";
            this.NameTextBox.Size = new System.Drawing.Size(412, 22);
            this.NameTextBox.TabIndex = 2;
            this.NameTextBox.Leave += new System.EventHandler(this.NameTextBox_Leave);
            // 
            // ModelDataLabel
            // 
            this.ModelDataLabel.AutoSize = true;
            this.ModelDataLabel.Location = new System.Drawing.Point(32, 67);
            this.ModelDataLabel.Name = "ModelDataLabel";
            this.ModelDataLabel.Size = new System.Drawing.Size(73, 15);
            this.ModelDataLabel.TabIndex = 3;
            this.ModelDataLabel.Text = "ModelData";
            // 
            // ItemDataPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ItemDataGroupBox);
            this.Name = "ItemDataPanel";
            this.Size = new System.Drawing.Size(1270, 270);
            this.ItemDataGroupBox.ResumeLayout(false);
            this.ItemDataGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MaxItemStackNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox ItemDataGroupBox;
        private System.Windows.Forms.NumericUpDown MaxItemStackNumeric;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label ItemIDDispLabel;
        private System.Windows.Forms.Label ItemIDLabel;
        private System.Windows.Forms.Button IconFileSelectButton;
        private System.Windows.Forms.Button ModelFileSelectButton;
        private System.Windows.Forms.Label ItemNameLabel;
        private System.Windows.Forms.TextBox IconDataTextBox;
        private System.Windows.Forms.TextBox ModelFilePathTextBox;
        private System.Windows.Forms.Label IconDataLabel;
        private System.Windows.Forms.TextBox NameTextBox;
        private System.Windows.Forms.Label ModelDataLabel;
    }
}
