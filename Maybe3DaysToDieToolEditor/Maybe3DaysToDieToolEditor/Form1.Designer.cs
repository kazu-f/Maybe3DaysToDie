
namespace Maybe3DaysToDieToolEditor
{
    partial class Maybe3DaysToDie_ToolEditor
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

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.FileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CreateNewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenFileOToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.FiletoolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.SaveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SaveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EditorEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.UnDoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reDoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CommandStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.CutOutXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CopyCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PastVToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EditortoolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.AddToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MaterialDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PlaceObjDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DeleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ItemList = new System.Windows.Forms.ListBox();
            this.ModelFileSelectButton = new System.Windows.Forms.Button();
            this.ModelFilePathTextBox = new System.Windows.Forms.TextBox();
            this.ModelDataLabel = new System.Windows.Forms.Label();
            this.NameTextBox = new System.Windows.Forms.TextBox();
            this.ItemGroupBox = new System.Windows.Forms.GroupBox();
            this.MaxItemStackNumeric = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.ItemIDDispLabel = new System.Windows.Forms.Label();
            this.ItemIDLabel = new System.Windows.Forms.Label();
            this.IconFileSelectButton = new System.Windows.Forms.Button();
            this.ItemNameLabel = new System.Windows.Forms.Label();
            this.IconDataTextBox = new System.Windows.Forms.TextBox();
            this.IconDataLabel = new System.Windows.Forms.Label();
            this.toolDataBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.FoodAndCureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.placementObjectPanel1 = new Maybe3DaysToDieToolEditor.PlacementObjectPanel();
            this.toolDataPanel1 = new Maybe3DaysToDieToolEditor.ToolDataPanel();
            this.foodAndCurePanel1 = new Maybe3DaysToDieToolEditor.FoodAndCurePanel();
            this.menuStrip1.SuspendLayout();
            this.ItemGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MaxItemStackNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.toolDataBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileToolStripMenuItem,
            this.EditorEToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1482, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // FileToolStripMenuItem
            // 
            this.FileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CreateNewToolStripMenuItem,
            this.OpenFileOToolStripMenuItem,
            this.FiletoolStripSeparator1,
            this.SaveToolStripMenuItem,
            this.SaveAsToolStripMenuItem});
            this.FileToolStripMenuItem.Name = "FileToolStripMenuItem";
            this.FileToolStripMenuItem.Size = new System.Drawing.Size(82, 24);
            this.FileToolStripMenuItem.Text = "ファイル(&F)";
            // 
            // CreateNewToolStripMenuItem
            // 
            this.CreateNewToolStripMenuItem.Name = "CreateNewToolStripMenuItem";
            this.CreateNewToolStripMenuItem.Size = new System.Drawing.Size(231, 26);
            this.CreateNewToolStripMenuItem.Text = "新規作成(&N)";
            // 
            // OpenFileOToolStripMenuItem
            // 
            this.OpenFileOToolStripMenuItem.Name = "OpenFileOToolStripMenuItem";
            this.OpenFileOToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.OpenFileOToolStripMenuItem.Size = new System.Drawing.Size(231, 26);
            this.OpenFileOToolStripMenuItem.Text = "開く(&O)...";
            this.OpenFileOToolStripMenuItem.Click += new System.EventHandler(this.OpenFileOToolStripMenuItem_Click);
            // 
            // FiletoolStripSeparator1
            // 
            this.FiletoolStripSeparator1.Name = "FiletoolStripSeparator1";
            this.FiletoolStripSeparator1.Size = new System.Drawing.Size(228, 6);
            // 
            // SaveToolStripMenuItem
            // 
            this.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem";
            this.SaveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.SaveToolStripMenuItem.Size = new System.Drawing.Size(231, 26);
            this.SaveToolStripMenuItem.Text = "上書き保存(&S)";
            this.SaveToolStripMenuItem.Click += new System.EventHandler(this.SaveToolStripMenuItem_Click);
            // 
            // SaveAsToolStripMenuItem
            // 
            this.SaveAsToolStripMenuItem.Name = "SaveAsToolStripMenuItem";
            this.SaveAsToolStripMenuItem.Size = new System.Drawing.Size(231, 26);
            this.SaveAsToolStripMenuItem.Text = "名前を付けて保存(&A)...";
            this.SaveAsToolStripMenuItem.Click += new System.EventHandler(this.SaveAsToolStripMenuItem_Click);
            // 
            // EditorEToolStripMenuItem
            // 
            this.EditorEToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.UnDoToolStripMenuItem,
            this.reDoToolStripMenuItem,
            this.CommandStripSeparator1,
            this.CutOutXToolStripMenuItem,
            this.CopyCToolStripMenuItem,
            this.PastVToolStripMenuItem,
            this.EditortoolStripSeparator1,
            this.AddToolStripMenuItem1,
            this.DeleteToolStripMenuItem});
            this.EditorEToolStripMenuItem.Name = "EditorEToolStripMenuItem";
            this.EditorEToolStripMenuItem.Size = new System.Drawing.Size(71, 24);
            this.EditorEToolStripMenuItem.Text = "編集(&E)";
            // 
            // UnDoToolStripMenuItem
            // 
            this.UnDoToolStripMenuItem.Name = "UnDoToolStripMenuItem";
            this.UnDoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.UnDoToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.UnDoToolStripMenuItem.Text = "元に戻す";
            this.UnDoToolStripMenuItem.Click += new System.EventHandler(this.UnDoToolStripMenuItem_Click);
            // 
            // reDoToolStripMenuItem
            // 
            this.reDoToolStripMenuItem.Name = "reDoToolStripMenuItem";
            this.reDoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.reDoToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.reDoToolStripMenuItem.Text = "やり直す";
            this.reDoToolStripMenuItem.Click += new System.EventHandler(this.reDoToolStripMenuItem_Click);
            // 
            // CommandStripSeparator1
            // 
            this.CommandStripSeparator1.Name = "CommandStripSeparator1";
            this.CommandStripSeparator1.Size = new System.Drawing.Size(210, 6);
            // 
            // CutOutXToolStripMenuItem
            // 
            this.CutOutXToolStripMenuItem.Name = "CutOutXToolStripMenuItem";
            this.CutOutXToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.CutOutXToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.CutOutXToolStripMenuItem.Text = "切り取り(&T)";
            // 
            // CopyCToolStripMenuItem
            // 
            this.CopyCToolStripMenuItem.Name = "CopyCToolStripMenuItem";
            this.CopyCToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.CopyCToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.CopyCToolStripMenuItem.Text = "コピー(&Y)";
            // 
            // PastVToolStripMenuItem
            // 
            this.PastVToolStripMenuItem.Name = "PastVToolStripMenuItem";
            this.PastVToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.PastVToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.PastVToolStripMenuItem.Text = "貼り付け(&P)";
            // 
            // EditortoolStripSeparator1
            // 
            this.EditortoolStripSeparator1.Name = "EditortoolStripSeparator1";
            this.EditortoolStripSeparator1.Size = new System.Drawing.Size(210, 6);
            // 
            // AddToolStripMenuItem1
            // 
            this.AddToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolDataToolStripMenuItem,
            this.MaterialDataToolStripMenuItem,
            this.PlaceObjDataToolStripMenuItem,
            this.FoodAndCureToolStripMenuItem});
            this.AddToolStripMenuItem1.Name = "AddToolStripMenuItem1";
            this.AddToolStripMenuItem1.Size = new System.Drawing.Size(213, 26);
            this.AddToolStripMenuItem1.Text = "追加";
            // 
            // ToolDataToolStripMenuItem
            // 
            this.ToolDataToolStripMenuItem.Name = "ToolDataToolStripMenuItem";
            this.ToolDataToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.ToolDataToolStripMenuItem.Text = "ツール";
            this.ToolDataToolStripMenuItem.Click += new System.EventHandler(this.ToolDataToolStripMenuItem_Click);
            // 
            // MaterialDataToolStripMenuItem
            // 
            this.MaterialDataToolStripMenuItem.Name = "MaterialDataToolStripMenuItem";
            this.MaterialDataToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.MaterialDataToolStripMenuItem.Text = "素材";
            // 
            // PlaceObjDataToolStripMenuItem
            // 
            this.PlaceObjDataToolStripMenuItem.Name = "PlaceObjDataToolStripMenuItem";
            this.PlaceObjDataToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.PlaceObjDataToolStripMenuItem.Text = "設置物";
            this.PlaceObjDataToolStripMenuItem.Click += new System.EventHandler(this.PlaceObjDataToolStripMenuItem_Click);
            // 
            // DeleteToolStripMenuItem
            // 
            this.DeleteToolStripMenuItem.Name = "DeleteToolStripMenuItem";
            this.DeleteToolStripMenuItem.Size = new System.Drawing.Size(213, 26);
            this.DeleteToolStripMenuItem.Text = "削除";
            this.DeleteToolStripMenuItem.Click += new System.EventHandler(this.DeleteToolStripMenuItem_Click);
            // 
            // ItemList
            // 
            this.ItemList.FormattingEnabled = true;
            this.ItemList.ItemHeight = 15;
            this.ItemList.Location = new System.Drawing.Point(12, 33);
            this.ItemList.Name = "ItemList";
            this.ItemList.Size = new System.Drawing.Size(180, 799);
            this.ItemList.TabIndex = 1;
            this.ItemList.SelectedIndexChanged += new System.EventHandler(this.ItemList_SelectedIndexChanged);
            // 
            // ModelFileSelectButton
            // 
            this.ModelFileSelectButton.Location = new System.Drawing.Point(849, 53);
            this.ModelFileSelectButton.Name = "ModelFileSelectButton";
            this.ModelFileSelectButton.Size = new System.Drawing.Size(102, 23);
            this.ModelFileSelectButton.TabIndex = 7;
            this.ModelFileSelectButton.Text = "ファイル選択";
            this.ModelFileSelectButton.UseVisualStyleBackColor = true;
            // 
            // ModelFilePathTextBox
            // 
            this.ModelFilePathTextBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ModelFilePathTextBox.Location = new System.Drawing.Point(129, 53);
            this.ModelFilePathTextBox.Name = "ModelFilePathTextBox";
            this.ModelFilePathTextBox.ReadOnly = true;
            this.ModelFilePathTextBox.Size = new System.Drawing.Size(703, 22);
            this.ModelFilePathTextBox.TabIndex = 6;
            // 
            // ModelDataLabel
            // 
            this.ModelDataLabel.AutoSize = true;
            this.ModelDataLabel.Location = new System.Drawing.Point(34, 57);
            this.ModelDataLabel.Name = "ModelDataLabel";
            this.ModelDataLabel.Size = new System.Drawing.Size(73, 15);
            this.ModelDataLabel.TabIndex = 5;
            this.ModelDataLabel.Text = "ModelData";
            // 
            // NameTextBox
            // 
            this.NameTextBox.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.NameTextBox.Location = new System.Drawing.Point(129, 25);
            this.NameTextBox.Name = "NameTextBox";
            this.NameTextBox.Size = new System.Drawing.Size(412, 22);
            this.NameTextBox.TabIndex = 4;
            this.NameTextBox.Leave += new System.EventHandler(this.NameTextBox_Leave);
            // 
            // ItemGroupBox
            // 
            this.ItemGroupBox.Controls.Add(this.MaxItemStackNumeric);
            this.ItemGroupBox.Controls.Add(this.label1);
            this.ItemGroupBox.Controls.Add(this.ItemIDDispLabel);
            this.ItemGroupBox.Controls.Add(this.ItemIDLabel);
            this.ItemGroupBox.Controls.Add(this.IconFileSelectButton);
            this.ItemGroupBox.Controls.Add(this.ModelFileSelectButton);
            this.ItemGroupBox.Controls.Add(this.ItemNameLabel);
            this.ItemGroupBox.Controls.Add(this.IconDataTextBox);
            this.ItemGroupBox.Controls.Add(this.ModelFilePathTextBox);
            this.ItemGroupBox.Controls.Add(this.IconDataLabel);
            this.ItemGroupBox.Controls.Add(this.NameTextBox);
            this.ItemGroupBox.Controls.Add(this.ModelDataLabel);
            this.ItemGroupBox.Location = new System.Drawing.Point(199, 33);
            this.ItemGroupBox.Name = "ItemGroupBox";
            this.ItemGroupBox.Size = new System.Drawing.Size(1271, 125);
            this.ItemGroupBox.TabIndex = 2;
            this.ItemGroupBox.TabStop = false;
            this.ItemGroupBox.Text = "ItemData";
            this.ItemGroupBox.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // MaxItemStackNumeric
            // 
            this.MaxItemStackNumeric.Location = new System.Drawing.Point(1084, 54);
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
            this.MaxItemStackNumeric.TabIndex = 14;
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
            this.label1.Location = new System.Drawing.Point(978, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 15);
            this.label1.TabIndex = 13;
            this.label1.Text = "ItemStackNum";
            // 
            // ItemIDDispLabel
            // 
            this.ItemIDDispLabel.Location = new System.Drawing.Point(1084, 24);
            this.ItemIDDispLabel.Name = "ItemIDDispLabel";
            this.ItemIDDispLabel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ItemIDDispLabel.Size = new System.Drawing.Size(100, 23);
            this.ItemIDDispLabel.TabIndex = 12;
            this.ItemIDDispLabel.Text = "0";
            this.ItemIDDispLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // ItemIDLabel
            // 
            this.ItemIDLabel.AutoSize = true;
            this.ItemIDLabel.Location = new System.Drawing.Point(1057, 28);
            this.ItemIDLabel.Name = "ItemIDLabel";
            this.ItemIDLabel.Size = new System.Drawing.Size(21, 15);
            this.ItemIDLabel.TabIndex = 11;
            this.ItemIDLabel.Text = "ID";
            // 
            // IconFileSelectButton
            // 
            this.IconFileSelectButton.Location = new System.Drawing.Point(849, 81);
            this.IconFileSelectButton.Name = "IconFileSelectButton";
            this.IconFileSelectButton.Size = new System.Drawing.Size(102, 23);
            this.IconFileSelectButton.TabIndex = 10;
            this.IconFileSelectButton.Text = "ファイル選択";
            this.IconFileSelectButton.UseVisualStyleBackColor = true;
            // 
            // ItemNameLabel
            // 
            this.ItemNameLabel.AutoSize = true;
            this.ItemNameLabel.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.ItemNameLabel.Location = new System.Drawing.Point(35, 28);
            this.ItemNameLabel.Name = "ItemNameLabel";
            this.ItemNameLabel.Size = new System.Drawing.Size(71, 15);
            this.ItemNameLabel.TabIndex = 3;
            this.ItemNameLabel.Text = "ItemName";
            this.ItemNameLabel.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // IconDataTextBox
            // 
            this.IconDataTextBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.IconDataTextBox.Location = new System.Drawing.Point(129, 81);
            this.IconDataTextBox.Name = "IconDataTextBox";
            this.IconDataTextBox.ReadOnly = true;
            this.IconDataTextBox.Size = new System.Drawing.Size(703, 22);
            this.IconDataTextBox.TabIndex = 9;
            // 
            // IconDataLabel
            // 
            this.IconDataLabel.AutoSize = true;
            this.IconDataLabel.Location = new System.Drawing.Point(34, 85);
            this.IconDataLabel.Name = "IconDataLabel";
            this.IconDataLabel.Size = new System.Drawing.Size(64, 15);
            this.IconDataLabel.TabIndex = 8;
            this.IconDataLabel.Text = "IconData";
            // 
            // FoodAndCureToolStripMenuItem
            // 
            this.FoodAndCureToolStripMenuItem.Name = "FoodAndCureToolStripMenuItem";
            this.FoodAndCureToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.FoodAndCureToolStripMenuItem.Text = "食料等";
            this.FoodAndCureToolStripMenuItem.Click += new System.EventHandler(this.FoodAndCureToolStripMenuItem_Click);
            // 
            // placementObjectPanel1
            // 
            this.placementObjectPanel1.Location = new System.Drawing.Point(198, 312);
            this.placementObjectPanel1.Name = "placementObjectPanel1";
            this.placementObjectPanel1.Size = new System.Drawing.Size(1272, 520);
            this.placementObjectPanel1.TabIndex = 5;
            // 
            // toolDataPanel1
            // 
            this.toolDataPanel1.Location = new System.Drawing.Point(198, 312);
            this.toolDataPanel1.Name = "toolDataPanel1";
            this.toolDataPanel1.Size = new System.Drawing.Size(1272, 520);
            this.toolDataPanel1.TabIndex = 4;
            this.toolDataPanel1.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // foodAndCurePanel1
            // 
            this.foodAndCurePanel1.Location = new System.Drawing.Point(198, 312);
            this.foodAndCurePanel1.Name = "foodAndCurePanel1";
            this.foodAndCurePanel1.Size = new System.Drawing.Size(1272, 520);
            this.foodAndCurePanel1.TabIndex = 6;
            this.foodAndCurePanel1.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // Maybe3DaysToDie_ToolEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1482, 853);
            this.Controls.Add(this.foodAndCurePanel1);
            this.Controls.Add(this.placementObjectPanel1);
            this.Controls.Add(this.toolDataPanel1);
            this.Controls.Add(this.ItemGroupBox);
            this.Controls.Add(this.ItemList);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Maybe3DaysToDie_ToolEditor";
            this.Text = "Maybe3DaysToDie_ToolEditor";
            this.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ItemGroupBox.ResumeLayout(false);
            this.ItemGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MaxItemStackNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.toolDataBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        //メニューの一覧。
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem FileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SaveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SaveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator FiletoolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem CreateNewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem OpenFileOToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem EditorEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem CopyCToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PastVToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem CutOutXToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator EditortoolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem AddToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem ToolDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MaterialDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PlaceObjDataToolStripMenuItem;
        private System.Windows.Forms.BindingSource toolDataBindingSource;
        private System.Windows.Forms.ListBox ItemList;
        private System.Windows.Forms.TextBox NameTextBox;
        private System.Windows.Forms.GroupBox ItemGroupBox;
        private System.Windows.Forms.Label ItemNameLabel;
        private System.Windows.Forms.ToolStripMenuItem UnDoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reDoToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator CommandStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem DeleteToolStripMenuItem;
        private System.Windows.Forms.Button ModelFileSelectButton;
        private System.Windows.Forms.TextBox ModelFilePathTextBox;
        private System.Windows.Forms.Label ModelDataLabel;
        private System.Windows.Forms.Button IconFileSelectButton;
        private System.Windows.Forms.TextBox IconDataTextBox;
        private System.Windows.Forms.Label IconDataLabel;
        private ToolDataPanel toolDataPanel1;
        private System.Windows.Forms.Label ItemIDDispLabel;
        private System.Windows.Forms.Label ItemIDLabel;
        private PlacementObjectPanel placementObjectPanel1;
        private System.Windows.Forms.NumericUpDown MaxItemStackNumeric;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripMenuItem FoodAndCureToolStripMenuItem;
        private FoodAndCurePanel foodAndCurePanel1;
    }
}

