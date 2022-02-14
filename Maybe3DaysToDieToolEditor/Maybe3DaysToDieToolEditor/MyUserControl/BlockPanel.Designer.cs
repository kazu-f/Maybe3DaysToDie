
namespace Maybe3DaysToDieToolEditor
{
    partial class BlockPanel
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
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem(new string[] {
            "1:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem(new string[] {
            "2:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem(new string[] {
            "3:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem(new string[] {
            "4:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem5 = new System.Windows.Forms.ListViewItem(new string[] {
            "5:",
            "",
            "",
            ""}, -1);
            this.groupBoxBlock = new System.Windows.Forms.GroupBox();
            this.collectItemListView = new System.Windows.Forms.ListView();
            this.CollectItems = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ItemID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ItemName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ItemNum = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CollectItemDel = new System.Windows.Forms.Button();
            this.CollectItemAddButton = new System.Windows.Forms.Button();
            this.collectNumeric = new System.Windows.Forms.NumericUpDown();
            this.labelCollect = new System.Windows.Forms.Label();
            this.ColectItemLabel = new System.Windows.Forms.Label();
            this.ColectItemDropDownList = new System.Windows.Forms.ComboBox();
            this.DurableNumeric = new System.Windows.Forms.NumericUpDown();
            this.DurableLabel = new System.Windows.Forms.Label();
            this.ToolKindsLabel = new System.Windows.Forms.Label();
            this.ToolComboBox = new System.Windows.Forms.ComboBox();
            this.groupBoxBlock.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxBlock
            // 
            this.groupBoxBlock.Controls.Add(this.collectItemListView);
            this.groupBoxBlock.Controls.Add(this.CollectItemDel);
            this.groupBoxBlock.Controls.Add(this.CollectItemAddButton);
            this.groupBoxBlock.Controls.Add(this.collectNumeric);
            this.groupBoxBlock.Controls.Add(this.labelCollect);
            this.groupBoxBlock.Controls.Add(this.ColectItemLabel);
            this.groupBoxBlock.Controls.Add(this.ColectItemDropDownList);
            this.groupBoxBlock.Controls.Add(this.DurableNumeric);
            this.groupBoxBlock.Controls.Add(this.DurableLabel);
            this.groupBoxBlock.Controls.Add(this.ToolKindsLabel);
            this.groupBoxBlock.Controls.Add(this.ToolComboBox);
            this.groupBoxBlock.Location = new System.Drawing.Point(0, 0);
            this.groupBoxBlock.Name = "groupBoxBlock";
            this.groupBoxBlock.Size = new System.Drawing.Size(820, 520);
            this.groupBoxBlock.TabIndex = 62;
            this.groupBoxBlock.TabStop = false;
            this.groupBoxBlock.Text = "Block";
            this.groupBoxBlock.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // collectItemListView
            // 
            this.collectItemListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.CollectItems,
            this.ItemID,
            this.ItemName,
            this.ItemNum});
            this.collectItemListView.FullRowSelect = true;
            this.collectItemListView.HideSelection = false;
            this.collectItemListView.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1,
            listViewItem2,
            listViewItem3,
            listViewItem4,
            listViewItem5});
            this.collectItemListView.Location = new System.Drawing.Point(32, 303);
            this.collectItemListView.MultiSelect = false;
            this.collectItemListView.Name = "collectItemListView";
            this.collectItemListView.Size = new System.Drawing.Size(625, 200);
            this.collectItemListView.TabIndex = 72;
            this.collectItemListView.UseCompatibleStateImageBehavior = false;
            this.collectItemListView.View = System.Windows.Forms.View.Details;
            // 
            // CollectItems
            // 
            this.CollectItems.Text = "";
            this.CollectItems.Width = 40;
            // 
            // ItemID
            // 
            this.ItemID.Text = "ID";
            this.ItemID.Width = 50;
            // 
            // ItemName
            // 
            this.ItemName.Text = "Name";
            this.ItemName.Width = 300;
            // 
            // ItemNum
            // 
            this.ItemNum.Text = "Num";
            // 
            // CollectItemDel
            // 
            this.CollectItemDel.Location = new System.Drawing.Point(691, 348);
            this.CollectItemDel.Name = "CollectItemDel";
            this.CollectItemDel.Size = new System.Drawing.Size(75, 38);
            this.CollectItemDel.TabIndex = 74;
            this.CollectItemDel.Text = "削除";
            this.CollectItemDel.UseVisualStyleBackColor = true;
            this.CollectItemDel.Click += new System.EventHandler(this.CollectItemDel_Click);
            // 
            // CollectItemAddButton
            // 
            this.CollectItemAddButton.Location = new System.Drawing.Point(691, 303);
            this.CollectItemAddButton.Name = "CollectItemAddButton";
            this.CollectItemAddButton.Size = new System.Drawing.Size(75, 39);
            this.CollectItemAddButton.TabIndex = 73;
            this.CollectItemAddButton.Text = "追加";
            this.CollectItemAddButton.UseVisualStyleBackColor = true;
            this.CollectItemAddButton.Click += new System.EventHandler(this.CollectItemAddButton_Click);
            // 
            // collectNumeric
            // 
            this.collectNumeric.Location = new System.Drawing.Point(530, 256);
            this.collectNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.collectNumeric.Name = "collectNumeric";
            this.collectNumeric.Size = new System.Drawing.Size(120, 22);
            this.collectNumeric.TabIndex = 7071;
            this.collectNumeric.ThousandsSeparator = true;
            // 
            // labelCollect
            // 
            this.labelCollect.AutoSize = true;
            this.labelCollect.Location = new System.Drawing.Point(470, 256);
            this.labelCollect.Name = "labelCollect";
            this.labelCollect.Size = new System.Drawing.Size(52, 15);
            this.labelCollect.TabIndex = 70;
            this.labelCollect.Text = "採取量";
            // 
            // ColectItemLabel
            // 
            this.ColectItemLabel.AutoSize = true;
            this.ColectItemLabel.Location = new System.Drawing.Point(29, 258);
            this.ColectItemLabel.Name = "ColectItemLabel";
            this.ColectItemLabel.Size = new System.Drawing.Size(82, 15);
            this.ColectItemLabel.TabIndex = 68;
            this.ColectItemLabel.Text = "採取アイテム";
            // 
            // ColectItemDropDownList
            // 
            this.ColectItemDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ColectItemDropDownList.FormattingEnabled = true;
            this.ColectItemDropDownList.Location = new System.Drawing.Point(117, 255);
            this.ColectItemDropDownList.Name = "ColectItemDropDownList";
            this.ColectItemDropDownList.Size = new System.Drawing.Size(319, 23);
            this.ColectItemDropDownList.TabIndex = 69;
            // 
            // DurableNumeric
            // 
            this.DurableNumeric.Location = new System.Drawing.Point(120, 50);
            this.DurableNumeric.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.DurableNumeric.Name = "DurableNumeric";
            this.DurableNumeric.Size = new System.Drawing.Size(120, 22);
            this.DurableNumeric.TabIndex = 62;
            this.DurableNumeric.ThousandsSeparator = true;
            this.DurableNumeric.Leave += new System.EventHandler(this.LeaveDurableValue);
            // 
            // DurableLabel
            // 
            this.DurableLabel.AutoSize = true;
            this.DurableLabel.Location = new System.Drawing.Point(60, 50);
            this.DurableLabel.Name = "DurableLabel";
            this.DurableLabel.Size = new System.Drawing.Size(52, 15);
            this.DurableLabel.TabIndex = 61;
            this.DurableLabel.Text = "耐久力";
            // 
            // ToolKindsLabel
            // 
            this.ToolKindsLabel.AutoSize = true;
            this.ToolKindsLabel.Location = new System.Drawing.Point(291, 50);
            this.ToolKindsLabel.Name = "ToolKindsLabel";
            this.ToolKindsLabel.Size = new System.Drawing.Size(72, 15);
            this.ToolKindsLabel.TabIndex = 63;
            this.ToolKindsLabel.Text = "適性ツール";
            // 
            // ToolComboBox
            // 
            this.ToolComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ToolComboBox.FormattingEnabled = true;
            this.ToolComboBox.Location = new System.Drawing.Point(371, 50);
            this.ToolComboBox.Name = "ToolComboBox";
            this.ToolComboBox.Size = new System.Drawing.Size(121, 23);
            this.ToolComboBox.TabIndex = 64;
            this.ToolComboBox.SelectionChangeCommitted += new System.EventHandler(this.ToolComboBox_SelectionChangeCommitted);
            // 
            // BlockPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxBlock);
            this.Name = "BlockPanel";
            this.Size = new System.Drawing.Size(820, 520);
            this.groupBoxBlock.ResumeLayout(false);
            this.groupBoxBlock.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxBlock;
        private System.Windows.Forms.ListView collectItemListView;
        private System.Windows.Forms.ColumnHeader CollectItems;
        private System.Windows.Forms.ColumnHeader ItemID;
        private System.Windows.Forms.ColumnHeader ItemName;
        private System.Windows.Forms.ColumnHeader ItemNum;
        private System.Windows.Forms.Button CollectItemDel;
        private System.Windows.Forms.Button CollectItemAddButton;
        private System.Windows.Forms.NumericUpDown collectNumeric;
        private System.Windows.Forms.Label labelCollect;
        private System.Windows.Forms.Label ColectItemLabel;
        private System.Windows.Forms.ComboBox ColectItemDropDownList;
        private System.Windows.Forms.NumericUpDown DurableNumeric;
        private System.Windows.Forms.Label DurableLabel;
        private System.Windows.Forms.Label ToolKindsLabel;
        private System.Windows.Forms.ComboBox ToolComboBox;
    }
}
