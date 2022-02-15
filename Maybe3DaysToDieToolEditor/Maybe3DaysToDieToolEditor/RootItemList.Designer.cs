
namespace Maybe3DaysToDieToolEditor
{
    partial class RootItemList
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CollectItemDel = new System.Windows.Forms.Button();
            this.CollectItemAddButton = new System.Windows.Forms.Button();
            this.collectNumeric = new System.Windows.Forms.NumericUpDown();
            this.labelCollect = new System.Windows.Forms.Label();
            this.ColectItemLabel = new System.Windows.Forms.Label();
            this.ColectItemDropDownList = new System.Windows.Forms.ComboBox();
            this.insideItemListBox = new System.Windows.Forms.ListBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.insideItemListBox);
            this.groupBox1.Controls.Add(this.CollectItemDel);
            this.groupBox1.Controls.Add(this.CollectItemAddButton);
            this.groupBox1.Controls.Add(this.ColectItemLabel);
            this.groupBox1.Controls.Add(this.ColectItemDropDownList);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(892, 487);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "RootInsideItem";
            // 
            // CollectItemDel
            // 
            this.CollectItemDel.Location = new System.Drawing.Point(760, 27);
            this.CollectItemDel.Name = "CollectItemDel";
            this.CollectItemDel.Size = new System.Drawing.Size(75, 38);
            this.CollectItemDel.TabIndex = 80;
            this.CollectItemDel.Text = "削除";
            this.CollectItemDel.UseVisualStyleBackColor = true;
            // 
            // CollectItemAddButton
            // 
            this.CollectItemAddButton.Location = new System.Drawing.Point(636, 26);
            this.CollectItemAddButton.Name = "CollectItemAddButton";
            this.CollectItemAddButton.Size = new System.Drawing.Size(75, 39);
            this.CollectItemAddButton.TabIndex = 79;
            this.CollectItemAddButton.Text = "追加";
            this.CollectItemAddButton.UseVisualStyleBackColor = true;
            // 
            // collectNumeric
            // 
            this.collectNumeric.Location = new System.Drawing.Point(95, 37);
            this.collectNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.collectNumeric.Name = "collectNumeric";
            this.collectNumeric.Size = new System.Drawing.Size(120, 22);
            this.collectNumeric.TabIndex = 77;
            this.collectNumeric.ThousandsSeparator = true;
            // 
            // labelCollect
            // 
            this.labelCollect.AutoSize = true;
            this.labelCollect.Location = new System.Drawing.Point(35, 37);
            this.labelCollect.Name = "labelCollect";
            this.labelCollect.Size = new System.Drawing.Size(52, 15);
            this.labelCollect.TabIndex = 76;
            this.labelCollect.Text = "採取量";
            // 
            // ColectItemLabel
            // 
            this.ColectItemLabel.AutoSize = true;
            this.ColectItemLabel.Location = new System.Drawing.Point(176, 38);
            this.ColectItemLabel.Name = "ColectItemLabel";
            this.ColectItemLabel.Size = new System.Drawing.Size(82, 15);
            this.ColectItemLabel.TabIndex = 74;
            this.ColectItemLabel.Text = "採取アイテム";
            // 
            // ColectItemDropDownList
            // 
            this.ColectItemDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ColectItemDropDownList.FormattingEnabled = true;
            this.ColectItemDropDownList.Location = new System.Drawing.Point(264, 35);
            this.ColectItemDropDownList.Name = "ColectItemDropDownList";
            this.ColectItemDropDownList.Size = new System.Drawing.Size(319, 23);
            this.ColectItemDropDownList.TabIndex = 75;
            // 
            // insideItemListBox
            // 
            this.insideItemListBox.FormattingEnabled = true;
            this.insideItemListBox.ItemHeight = 15;
            this.insideItemListBox.Location = new System.Drawing.Point(22, 26);
            this.insideItemListBox.Name = "insideItemListBox";
            this.insideItemListBox.Size = new System.Drawing.Size(120, 439);
            this.insideItemListBox.TabIndex = 81;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.collectNumeric);
            this.groupBox2.Controls.Add(this.labelCollect);
            this.groupBox2.Location = new System.Drawing.Point(179, 91);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(691, 374);
            this.groupBox2.TabIndex = 82;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "InsideItemData";
            // 
            // RootItemList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(917, 512);
            this.Controls.Add(this.groupBox1);
            this.Name = "RootItemList";
            this.Text = "RootItemList";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.collectNumeric)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button CollectItemDel;
        private System.Windows.Forms.Button CollectItemAddButton;
        private System.Windows.Forms.NumericUpDown collectNumeric;
        private System.Windows.Forms.Label labelCollect;
        private System.Windows.Forms.Label ColectItemLabel;
        private System.Windows.Forms.ComboBox ColectItemDropDownList;
        private System.Windows.Forms.ListBox insideItemListBox;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}