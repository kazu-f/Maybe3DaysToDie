
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
            this.CutOutXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CopyCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PastVToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EditortoolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.AddToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MaterialDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PlaceObjDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ItemList = new System.Windows.Forms.ListBox();
            this.toolDataBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.ToolGroupBox = new System.Windows.Forms.GroupBox();
            this.NameTextBox = new System.Windows.Forms.TextBox();
            this.ItemGroupBox = new System.Windows.Forms.GroupBox();
            this.ItemNameLabel = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.toolDataBindingSource)).BeginInit();
            this.ItemGroupBox.SuspendLayout();
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
            // 
            // SaveAsToolStripMenuItem
            // 
            this.SaveAsToolStripMenuItem.Name = "SaveAsToolStripMenuItem";
            this.SaveAsToolStripMenuItem.Size = new System.Drawing.Size(231, 26);
            this.SaveAsToolStripMenuItem.Text = "名前を付けて保存(&A)...";
            // 
            // EditorEToolStripMenuItem
            // 
            this.EditorEToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.CutOutXToolStripMenuItem,
            this.CopyCToolStripMenuItem,
            this.PastVToolStripMenuItem,
            this.EditortoolStripSeparator1,
            this.AddToolStripMenuItem1});
            this.EditorEToolStripMenuItem.Name = "EditorEToolStripMenuItem";
            this.EditorEToolStripMenuItem.Size = new System.Drawing.Size(71, 24);
            this.EditorEToolStripMenuItem.Text = "編集(&E)";
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
            this.PlaceObjDataToolStripMenuItem});
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
            // ToolGroupBox
            // 
            this.ToolGroupBox.Location = new System.Drawing.Point(198, 98);
            this.ToolGroupBox.Name = "ToolGroupBox";
            this.ToolGroupBox.Size = new System.Drawing.Size(1272, 734);
            this.ToolGroupBox.TabIndex = 2;
            this.ToolGroupBox.TabStop = false;
            this.ToolGroupBox.Text = "ToolData";
            // 
            // NameTextBox
            // 
            this.NameTextBox.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.NameTextBox.Location = new System.Drawing.Point(173, 21);
            this.NameTextBox.Name = "NameTextBox";
            this.NameTextBox.Size = new System.Drawing.Size(412, 27);
            this.NameTextBox.TabIndex = 0;
            this.NameTextBox.TextChanged += new System.EventHandler(this.NameTextBox_TextChanged);
            // 
            // ItemGroupBox
            // 
            this.ItemGroupBox.Controls.Add(this.ItemNameLabel);
            this.ItemGroupBox.Controls.Add(this.NameTextBox);
            this.ItemGroupBox.Location = new System.Drawing.Point(199, 33);
            this.ItemGroupBox.Name = "ItemGroupBox";
            this.ItemGroupBox.Size = new System.Drawing.Size(1271, 59);
            this.ItemGroupBox.TabIndex = 3;
            this.ItemGroupBox.TabStop = false;
            this.ItemGroupBox.Text = "ItemData";
            // 
            // ItemNameLabel
            // 
            this.ItemNameLabel.AutoSize = true;
            this.ItemNameLabel.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.ItemNameLabel.Location = new System.Drawing.Point(51, 24);
            this.ItemNameLabel.Name = "ItemNameLabel";
            this.ItemNameLabel.Size = new System.Drawing.Size(102, 20);
            this.ItemNameLabel.TabIndex = 1;
            this.ItemNameLabel.Text = "ItemName";
            // 
            // Maybe3DaysToDie_ToolEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1482, 853);
            this.Controls.Add(this.ItemGroupBox);
            this.Controls.Add(this.ToolGroupBox);
            this.Controls.Add(this.ItemList);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Maybe3DaysToDie_ToolEditor";
            this.Text = "Maybe3DaysToDie_ToolEditor";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.toolDataBindingSource)).EndInit();
            this.ItemGroupBox.ResumeLayout(false);
            this.ItemGroupBox.PerformLayout();
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
        private System.Windows.Forms.GroupBox ToolGroupBox;
        private System.Windows.Forms.TextBox NameTextBox;
        private System.Windows.Forms.GroupBox ItemGroupBox;
        private System.Windows.Forms.Label ItemNameLabel;
    }
}

