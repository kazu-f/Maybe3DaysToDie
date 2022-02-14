
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
            this.PlaceObjDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TerrainToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.FoodAndCureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MaterialDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DeleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ItemList = new System.Windows.Forms.ListBox();
            this.toolDataBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.BlockToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.terrainPanel1 = new Maybe3DaysToDieToolEditor.TerrainPanel();
            this.materialPanel1 = new Maybe3DaysToDieToolEditor.MaterialPanel();
            this.itemDataPanel1 = new Maybe3DaysToDieToolEditor.ItemDataPanel();
            this.foodAndCurePanel1 = new Maybe3DaysToDieToolEditor.FoodAndCurePanel();
            this.placementObjectPanel1 = new Maybe3DaysToDieToolEditor.PlacementObjectPanel();
            this.toolDataPanel1 = new Maybe3DaysToDieToolEditor.ToolDataPanel();
            this.blockPanel1 = new Maybe3DaysToDieToolEditor.BlockPanel();
            this.menuStrip1.SuspendLayout();
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
            this.PlaceObjDataToolStripMenuItem,
            this.BlockToolStripMenuItem,
            this.TerrainToolStripMenuItem,
            this.FoodAndCureToolStripMenuItem,
            this.MaterialDataToolStripMenuItem});
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
            // PlaceObjDataToolStripMenuItem
            // 
            this.PlaceObjDataToolStripMenuItem.Name = "PlaceObjDataToolStripMenuItem";
            this.PlaceObjDataToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.PlaceObjDataToolStripMenuItem.Text = "設置物";
            this.PlaceObjDataToolStripMenuItem.Click += new System.EventHandler(this.PlaceObjDataToolStripMenuItem_Click);
            // 
            // TerrainToolStripMenuItem
            // 
            this.TerrainToolStripMenuItem.Name = "TerrainToolStripMenuItem";
            this.TerrainToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.TerrainToolStripMenuItem.Text = "地形";
            this.TerrainToolStripMenuItem.Click += new System.EventHandler(this.TerrainToolStripMenuItem_Click);
            // 
            // FoodAndCureToolStripMenuItem
            // 
            this.FoodAndCureToolStripMenuItem.Name = "FoodAndCureToolStripMenuItem";
            this.FoodAndCureToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.FoodAndCureToolStripMenuItem.Text = "食料等";
            this.FoodAndCureToolStripMenuItem.Click += new System.EventHandler(this.FoodAndCureToolStripMenuItem_Click);
            // 
            // MaterialDataToolStripMenuItem
            // 
            this.MaterialDataToolStripMenuItem.Name = "MaterialDataToolStripMenuItem";
            this.MaterialDataToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.MaterialDataToolStripMenuItem.Text = "素材";
            this.MaterialDataToolStripMenuItem.Click += new System.EventHandler(this.MaterialDataToolStripMenuItem_Click);
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
            this.ItemList.Location = new System.Drawing.Point(12, 30);
            this.ItemList.Name = "ItemList";
            this.ItemList.Size = new System.Drawing.Size(180, 799);
            this.ItemList.TabIndex = 1;
            this.ItemList.SelectedIndexChanged += new System.EventHandler(this.ItemList_SelectedIndexChanged);
            // 
            // BlockToolStripMenuItem
            // 
            this.BlockToolStripMenuItem.Name = "BlockToolStripMenuItem";
            this.BlockToolStripMenuItem.Size = new System.Drawing.Size(137, 26);
            this.BlockToolStripMenuItem.Text = "ブロック";
            this.BlockToolStripMenuItem.Click += new System.EventHandler(this.BlockToolStripMenuItem_Click);
            // 
            // terrainPanel1
            // 
            this.terrainPanel1.Location = new System.Drawing.Point(200, 320);
            this.terrainPanel1.Name = "terrainPanel1";
            this.terrainPanel1.Size = new System.Drawing.Size(820, 520);
            this.terrainPanel1.TabIndex = 8;
            // 
            // materialPanel1
            // 
            this.materialPanel1.Location = new System.Drawing.Point(199, 320);
            this.materialPanel1.Name = "materialPanel1";
            this.materialPanel1.Size = new System.Drawing.Size(820, 520);
            this.materialPanel1.TabIndex = 7;
            // 
            // itemDataPanel1
            // 
            this.itemDataPanel1.Location = new System.Drawing.Point(200, 32);
            this.itemDataPanel1.Name = "itemDataPanel1";
            this.itemDataPanel1.Size = new System.Drawing.Size(1270, 270);
            this.itemDataPanel1.TabIndex = 2;
            this.itemDataPanel1.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // foodAndCurePanel1
            // 
            this.foodAndCurePanel1.Location = new System.Drawing.Point(200, 320);
            this.foodAndCurePanel1.Name = "foodAndCurePanel1";
            this.foodAndCurePanel1.Size = new System.Drawing.Size(820, 520);
            this.foodAndCurePanel1.TabIndex = 6;
            this.foodAndCurePanel1.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // placementObjectPanel1
            // 
            this.placementObjectPanel1.Location = new System.Drawing.Point(200, 320);
            this.placementObjectPanel1.Name = "placementObjectPanel1";
            this.placementObjectPanel1.Size = new System.Drawing.Size(820, 520);
            this.placementObjectPanel1.TabIndex = 5;
            // 
            // toolDataPanel1
            // 
            this.toolDataPanel1.Location = new System.Drawing.Point(200, 320);
            this.toolDataPanel1.Name = "toolDataPanel1";
            this.toolDataPanel1.Size = new System.Drawing.Size(820, 520);
            this.toolDataPanel1.TabIndex = 4;
            this.toolDataPanel1.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            // 
            // blockPanel1
            // 
            this.blockPanel1.Location = new System.Drawing.Point(199, 320);
            this.blockPanel1.Name = "blockPanel1";
            this.blockPanel1.Size = new System.Drawing.Size(820, 520);
            this.blockPanel1.TabIndex = 9;
            // 
            // Maybe3DaysToDie_ToolEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1482, 853);
            this.Controls.Add(this.blockPanel1);
            this.Controls.Add(this.terrainPanel1);
            this.Controls.Add(this.materialPanel1);
            this.Controls.Add(this.itemDataPanel1);
            this.Controls.Add(this.foodAndCurePanel1);
            this.Controls.Add(this.placementObjectPanel1);
            this.Controls.Add(this.toolDataPanel1);
            this.Controls.Add(this.ItemList);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Maybe3DaysToDie_ToolEditor";
            this.Text = "Maybe3DaysToDie_ToolEditor";
            this.MouseCaptureChanged += new System.EventHandler(this.MouseCapture);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
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
        private System.Windows.Forms.ToolStripMenuItem UnDoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reDoToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator CommandStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem DeleteToolStripMenuItem;
        private ToolDataPanel toolDataPanel1;
        private PlacementObjectPanel placementObjectPanel1;
        private System.Windows.Forms.ToolStripMenuItem FoodAndCureToolStripMenuItem;
        private FoodAndCurePanel foodAndCurePanel1;
        private ItemDataPanel itemDataPanel1;
        private MaterialPanel materialPanel1;
        private TerrainPanel terrainPanel1;
        private System.Windows.Forms.ToolStripMenuItem TerrainToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BlockToolStripMenuItem;
        private BlockPanel blockPanel1;
    }
}

