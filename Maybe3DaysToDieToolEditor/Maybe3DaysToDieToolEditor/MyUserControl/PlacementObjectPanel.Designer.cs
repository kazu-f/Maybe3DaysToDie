
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
            System.Windows.Forms.ListViewItem listViewItem11 = new System.Windows.Forms.ListViewItem(new string[] {
            "1:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem12 = new System.Windows.Forms.ListViewItem(new string[] {
            "2:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem13 = new System.Windows.Forms.ListViewItem(new string[] {
            "3:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem14 = new System.Windows.Forms.ListViewItem(new string[] {
            "4:",
            "",
            "",
            ""}, -1);
            System.Windows.Forms.ListViewItem listViewItem15 = new System.Windows.Forms.ListViewItem(new string[] {
            "5:",
            "",
            "",
            ""}, -1);
            this.groupBoxPlacementObject = new System.Windows.Forms.GroupBox();
            this.ObjTypeLabel = new System.Windows.Forms.Label();
            this.objTypeComboBox = new System.Windows.Forms.ComboBox();
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
            this.OpenInsideDataButton = new System.Windows.Forms.Button();
            this.groupBoxPlacementObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxPlacementObject
            // 
            this.groupBoxPlacementObject.Controls.Add(this.OpenInsideDataButton);
            this.groupBoxPlacementObject.Controls.Add(this.ObjTypeLabel);
            this.groupBoxPlacementObject.Controls.Add(this.objTypeComboBox);
            this.groupBoxPlacementObject.Controls.Add(this.collectItemListView);
            this.groupBoxPlacementObject.Controls.Add(this.CollectItemDel);
            this.groupBoxPlacementObject.Controls.Add(this.CollectItemAddButton);
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
            this.groupBoxPlacementObject.Size = new System.Drawing.Size(820, 520);
            this.groupBoxPlacementObject.TabIndex = 60;
            this.groupBoxPlacementObject.TabStop = false;
            this.groupBoxPlacementObject.Text = "PlacementObject";
            this.groupBoxPlacementObject.MouseCaptureChanged += new System.EventHandler(this.activeControlNull);
            // 
            // ObjTypeLabel
            // 
            this.ObjTypeLabel.AutoSize = true;
            this.ObjTypeLabel.Location = new System.Drawing.Point(72, 104);
            this.ObjTypeLabel.Name = "ObjTypeLabel";
            this.ObjTypeLabel.Size = new System.Drawing.Size(39, 15);
            this.ObjTypeLabel.TabIndex = 65;
            this.ObjTypeLabel.Text = "タイプ";
            // 
            // objTypeComboBox
            // 
            this.objTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.objTypeComboBox.FormattingEnabled = true;
            this.objTypeComboBox.Location = new System.Drawing.Point(117, 101);
            this.objTypeComboBox.Name = "objTypeComboBox";
            this.objTypeComboBox.Size = new System.Drawing.Size(121, 23);
            this.objTypeComboBox.TabIndex = 66;
            this.objTypeComboBox.SelectionChangeCommitted += new System.EventHandler(this.objTypeComboBox_SelectionChangeCommitted);
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
            listViewItem11,
            listViewItem12,
            listViewItem13,
            listViewItem14,
            listViewItem15});
            this.collectItemListView.Location = new System.Drawing.Point(32, 303);
            this.collectItemListView.MultiSelect = false;
            this.collectItemListView.Name = "collectItemListView";
            this.collectItemListView.Size = new System.Drawing.Size(625, 200);
            this.collectItemListView.TabIndex = 71;
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
            this.CollectItemDel.TabIndex = 73;
            this.CollectItemDel.Text = "削除";
            this.CollectItemDel.UseVisualStyleBackColor = true;
            this.CollectItemDel.Click += new System.EventHandler(this.CollectItemDel_Click);
            // 
            // CollectItemAddButton
            // 
            this.CollectItemAddButton.Location = new System.Drawing.Point(691, 303);
            this.CollectItemAddButton.Name = "CollectItemAddButton";
            this.CollectItemAddButton.Size = new System.Drawing.Size(75, 39);
            this.CollectItemAddButton.TabIndex = 72;
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
            this.collectNumeric.TabIndex = 70;
            this.collectNumeric.ThousandsSeparator = true;
            // 
            // labelCollect
            // 
            this.labelCollect.AutoSize = true;
            this.labelCollect.Location = new System.Drawing.Point(470, 256);
            this.labelCollect.Name = "labelCollect";
            this.labelCollect.Size = new System.Drawing.Size(52, 15);
            this.labelCollect.TabIndex = 69;
            this.labelCollect.Text = "採取量";
            // 
            // ColectItemLabel
            // 
            this.ColectItemLabel.AutoSize = true;
            this.ColectItemLabel.Location = new System.Drawing.Point(29, 258);
            this.ColectItemLabel.Name = "ColectItemLabel";
            this.ColectItemLabel.Size = new System.Drawing.Size(82, 15);
            this.ColectItemLabel.TabIndex = 67;
            this.ColectItemLabel.Text = "採取アイテム";
            // 
            // ColectItemDropDownList
            // 
            this.ColectItemDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ColectItemDropDownList.FormattingEnabled = true;
            this.ColectItemDropDownList.Location = new System.Drawing.Point(117, 255);
            this.ColectItemDropDownList.Name = "ColectItemDropDownList";
            this.ColectItemDropDownList.Size = new System.Drawing.Size(319, 23);
            this.ColectItemDropDownList.TabIndex = 68;
            // 
            // DurableNumeric
            // 
            this.DurableNumeric.Location = new System.Drawing.Point(117, 48);
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
            // OpenInsideDataButton
            // 
            this.OpenInsideDataButton.Location = new System.Drawing.Point(294, 101);
            this.OpenInsideDataButton.Name = "OpenInsideDataButton";
            this.OpenInsideDataButton.Size = new System.Drawing.Size(115, 23);
            this.OpenInsideDataButton.TabIndex = 74;
            this.OpenInsideDataButton.Text = "ルートデータ編集";
            this.OpenInsideDataButton.UseVisualStyleBackColor = true;
            this.OpenInsideDataButton.Click += new System.EventHandler(this.OpenInsideDataButton_Click);
            // 
            // PlacementObjectPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxPlacementObject);
            this.Name = "PlacementObjectPanel";
            this.Size = new System.Drawing.Size(820, 520);
            this.groupBoxPlacementObject.ResumeLayout(false);
            this.groupBoxPlacementObject.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DurableNumeric)).EndInit();
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
        private System.Windows.Forms.Button CollectItemDel;
        private System.Windows.Forms.Button CollectItemAddButton;
        private System.Windows.Forms.ListView collectItemListView;
        private System.Windows.Forms.ColumnHeader ItemID;
        private System.Windows.Forms.ColumnHeader ItemName;
        private System.Windows.Forms.ColumnHeader ItemNum;
        private System.Windows.Forms.ColumnHeader CollectItems;
        private System.Windows.Forms.ComboBox objTypeComboBox;
        private System.Windows.Forms.Label ObjTypeLabel;
        private System.Windows.Forms.Button OpenInsideDataButton;
    }
}
