
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
            this.ColectItemLabel = new System.Windows.Forms.Label();
            this.ColectItemDropDownList = new System.Windows.Forms.ComboBox();
            this.DurableNumeric = new System.Windows.Forms.NumericUpDown();
            this.DurableLabel = new System.Windows.Forms.Label();
            this.ToolKindsLabel = new System.Windows.Forms.Label();
            this.ToolComboBox = new System.Windows.Forms.ComboBox();
            this.collectNumeric = new System.Windows.Forms.NumericUpDown();
            this.labelCollect = new System.Windows.Forms.Label();
            this.listView1 = new System.Windows.Forms.ListView();
            this.ItemID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ItemName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CollectNum = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CollectItemAddButton = new System.Windows.Forms.Button();
            this.CollectItemDel = new System.Windows.Forms.Button();
            this.groupBoxPlacementObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxPlacementObject
            // 
            this.groupBoxPlacementObject.Controls.Add(this.CollectItemDel);
            this.groupBoxPlacementObject.Controls.Add(this.CollectItemAddButton);
            this.groupBoxPlacementObject.Controls.Add(this.listView1);
            this.groupBoxPlacementObject.Controls.Add(this.collectNumeric);
            this.groupBoxPlacementObject.Controls.Add(this.labelCollect);
            this.groupBoxPlacementObject.Controls.Add(this.ColectItemLabel);
            this.groupBoxPlacementObject.Controls.Add(this.ColectItemDropDownList);
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
            this.groupBoxPlacementObject.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // ColectItemLabel
            // 
            this.ColectItemLabel.AutoSize = true;
            this.ColectItemLabel.Location = new System.Drawing.Point(29, 162);
            this.ColectItemLabel.Name = "ColectItemLabel";
            this.ColectItemLabel.Size = new System.Drawing.Size(82, 15);
            this.ColectItemLabel.TabIndex = 29;
            this.ColectItemLabel.Text = "採取アイテム";
            // 
            // ColectItemDropDownList
            // 
            this.ColectItemDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ColectItemDropDownList.FormattingEnabled = true;
            this.ColectItemDropDownList.Location = new System.Drawing.Point(117, 159);
            this.ColectItemDropDownList.Name = "ColectItemDropDownList";
            this.ColectItemDropDownList.Size = new System.Drawing.Size(540, 23);
            this.ColectItemDropDownList.TabIndex = 28;
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
            this.DurableNumeric.Leave += new System.EventHandler(this.LeaveDurableValue);
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
            // collectNumeric
            // 
            this.collectNumeric.Location = new System.Drawing.Point(822, 160);
            this.collectNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.collectNumeric.Name = "collectNumeric";
            this.collectNumeric.Size = new System.Drawing.Size(120, 22);
            this.collectNumeric.TabIndex = 31;
            this.collectNumeric.ThousandsSeparator = true;
            // 
            // labelCollect
            // 
            this.labelCollect.AutoSize = true;
            this.labelCollect.Location = new System.Drawing.Point(764, 162);
            this.labelCollect.Name = "labelCollect";
            this.labelCollect.Size = new System.Drawing.Size(52, 15);
            this.labelCollect.TabIndex = 30;
            this.labelCollect.Text = "採取量";
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ItemID,
            this.ItemName,
            this.CollectNum});
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(32, 207);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(625, 196);
            this.listView1.TabIndex = 32;
            this.listView1.UseCompatibleStateImageBehavior = false;
            // 
            // ItemID
            // 
            this.ItemID.Text = "ItemID";
            this.ItemID.Width = 5;
            // 
            // ItemName
            // 
            this.ItemName.Text = "ItemName";
            this.ItemName.Width = 20;
            // 
            // CollectNum
            // 
            this.CollectNum.Text = "CollectNum";
            this.CollectNum.Width = 5;
            // 
            // CollectItemAddButton
            // 
            this.CollectItemAddButton.Location = new System.Drawing.Point(691, 223);
            this.CollectItemAddButton.Name = "CollectItemAddButton";
            this.CollectItemAddButton.Size = new System.Drawing.Size(75, 23);
            this.CollectItemAddButton.TabIndex = 33;
            this.CollectItemAddButton.Text = "追加";
            this.CollectItemAddButton.UseVisualStyleBackColor = true;
            this.CollectItemAddButton.Click += new System.EventHandler(this.CollectItemAddButton_Click);
            // 
            // CollectItemDel
            // 
            this.CollectItemDel.Location = new System.Drawing.Point(691, 252);
            this.CollectItemDel.Name = "CollectItemDel";
            this.CollectItemDel.Size = new System.Drawing.Size(75, 23);
            this.CollectItemDel.TabIndex = 33;
            this.CollectItemDel.Text = "削除";
            this.CollectItemDel.UseVisualStyleBackColor = true;
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
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxPlacementObject;
        private System.Windows.Forms.Label ToolKindsLabel;
        private System.Windows.Forms.ComboBox ToolComboBox;
        private System.Windows.Forms.NumericUpDown DurableNumeric;
        private System.Windows.Forms.Label DurableLabel;
        private System.Windows.Forms.ComboBox ColectItemDropDownList;
        private System.Windows.Forms.Label ColectItemLabel;
        private System.Windows.Forms.NumericUpDown collectNumeric;
        private System.Windows.Forms.Label labelCollect;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader ItemID;
        private System.Windows.Forms.ColumnHeader ItemName;
        private System.Windows.Forms.ColumnHeader CollectNum;
        private System.Windows.Forms.Button CollectItemDel;
        private System.Windows.Forms.Button CollectItemAddButton;
    }
}
