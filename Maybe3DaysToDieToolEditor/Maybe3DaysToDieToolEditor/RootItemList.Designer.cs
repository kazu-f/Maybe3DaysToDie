
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
            this.InsideItemDel = new System.Windows.Forms.Button();
            this.InsideItemAddButton = new System.Windows.Forms.Button();
            this.probabilityNumeric = new System.Windows.Forms.NumericUpDown();
            this.labelProbability = new System.Windows.Forms.Label();
            this.ColectItemLabel = new System.Windows.Forms.Label();
            this.InsideItemDropDownList = new System.Windows.Forms.ComboBox();
            this.insideItemListBox = new System.Windows.Forms.ListBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.maxNumeric = new System.Windows.Forms.NumericUpDown();
            this.itemMaxLabel = new System.Windows.Forms.Label();
            this.minNumeric = new System.Windows.Forms.NumericUpDown();
            this.itemMinLabel = new System.Windows.Forms.Label();
            this.insideItemName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.probabilityNumeric)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxNumeric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.minNumeric)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.insideItemListBox);
            this.groupBox1.Controls.Add(this.InsideItemDel);
            this.groupBox1.Controls.Add(this.InsideItemAddButton);
            this.groupBox1.Controls.Add(this.ColectItemLabel);
            this.groupBox1.Controls.Add(this.InsideItemDropDownList);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(892, 487);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "RootInsideItem";
            // 
            // InsideItemDel
            // 
            this.InsideItemDel.Location = new System.Drawing.Point(782, 27);
            this.InsideItemDel.Name = "InsideItemDel";
            this.InsideItemDel.Size = new System.Drawing.Size(75, 38);
            this.InsideItemDel.TabIndex = 80;
            this.InsideItemDel.Text = "削除";
            this.InsideItemDel.UseVisualStyleBackColor = true;
            this.InsideItemDel.Click += new System.EventHandler(this.InsideItemDel_Click);
            // 
            // InsideItemAddButton
            // 
            this.InsideItemAddButton.Location = new System.Drawing.Point(670, 26);
            this.InsideItemAddButton.Name = "InsideItemAddButton";
            this.InsideItemAddButton.Size = new System.Drawing.Size(75, 39);
            this.InsideItemAddButton.TabIndex = 79;
            this.InsideItemAddButton.Text = "追加";
            this.InsideItemAddButton.UseVisualStyleBackColor = true;
            this.InsideItemAddButton.Click += new System.EventHandler(this.InsideItemAddButton_Click);
            // 
            // probabilityNumeric
            // 
            this.probabilityNumeric.Location = new System.Drawing.Point(94, 108);
            this.probabilityNumeric.Name = "probabilityNumeric";
            this.probabilityNumeric.Size = new System.Drawing.Size(120, 22);
            this.probabilityNumeric.TabIndex = 77;
            this.probabilityNumeric.ThousandsSeparator = true;
            // 
            // labelProbability
            // 
            this.labelProbability.AutoSize = true;
            this.labelProbability.Location = new System.Drawing.Point(34, 108);
            this.labelProbability.Name = "labelProbability";
            this.labelProbability.Size = new System.Drawing.Size(55, 15);
            this.labelProbability.TabIndex = 76;
            this.labelProbability.Text = "確率(%)";
            // 
            // ColectItemLabel
            // 
            this.ColectItemLabel.AutoSize = true;
            this.ColectItemLabel.Location = new System.Drawing.Point(229, 38);
            this.ColectItemLabel.Name = "ColectItemLabel";
            this.ColectItemLabel.Size = new System.Drawing.Size(82, 15);
            this.ColectItemLabel.TabIndex = 74;
            this.ColectItemLabel.Text = "採取アイテム";
            // 
            // InsideItemDropDownList
            // 
            this.InsideItemDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.InsideItemDropDownList.FormattingEnabled = true;
            this.InsideItemDropDownList.Location = new System.Drawing.Point(317, 35);
            this.InsideItemDropDownList.Name = "InsideItemDropDownList";
            this.InsideItemDropDownList.Size = new System.Drawing.Size(319, 23);
            this.InsideItemDropDownList.TabIndex = 75;
            // 
            // insideItemListBox
            // 
            this.insideItemListBox.FormattingEnabled = true;
            this.insideItemListBox.ItemHeight = 15;
            this.insideItemListBox.Location = new System.Drawing.Point(22, 26);
            this.insideItemListBox.Name = "insideItemListBox";
            this.insideItemListBox.Size = new System.Drawing.Size(157, 439);
            this.insideItemListBox.TabIndex = 81;
            this.insideItemListBox.SelectedIndexChanged += new System.EventHandler(this.insideItemListBox_SelectedIndexChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.insideItemName);
            this.groupBox2.Controls.Add(this.minNumeric);
            this.groupBox2.Controls.Add(this.itemMinLabel);
            this.groupBox2.Controls.Add(this.maxNumeric);
            this.groupBox2.Controls.Add(this.itemMaxLabel);
            this.groupBox2.Controls.Add(this.probabilityNumeric);
            this.groupBox2.Controls.Add(this.labelProbability);
            this.groupBox2.Location = new System.Drawing.Point(212, 91);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(658, 374);
            this.groupBox2.TabIndex = 82;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "InsideItemData";
            // 
            // maxNumeric
            // 
            this.maxNumeric.Location = new System.Drawing.Point(297, 108);
            this.maxNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.maxNumeric.Name = "maxNumeric";
            this.maxNumeric.Size = new System.Drawing.Size(120, 22);
            this.maxNumeric.TabIndex = 79;
            this.maxNumeric.ThousandsSeparator = true;
            // 
            // itemMaxLabel
            // 
            this.itemMaxLabel.AutoSize = true;
            this.itemMaxLabel.Location = new System.Drawing.Point(236, 110);
            this.itemMaxLabel.Name = "itemMaxLabel";
            this.itemMaxLabel.Size = new System.Drawing.Size(52, 15);
            this.itemMaxLabel.TabIndex = 78;
            this.itemMaxLabel.Text = "最大数";
            // 
            // minNumeric
            // 
            this.minNumeric.Location = new System.Drawing.Point(504, 110);
            this.minNumeric.Maximum = new decimal(new int[] {
            999,
            0,
            0,
            0});
            this.minNumeric.Name = "minNumeric";
            this.minNumeric.Size = new System.Drawing.Size(120, 22);
            this.minNumeric.TabIndex = 81;
            this.minNumeric.ThousandsSeparator = true;
            // 
            // itemMinLabel
            // 
            this.itemMinLabel.AutoSize = true;
            this.itemMinLabel.Location = new System.Drawing.Point(444, 110);
            this.itemMinLabel.Name = "itemMinLabel";
            this.itemMinLabel.Size = new System.Drawing.Size(52, 15);
            this.itemMinLabel.TabIndex = 80;
            this.itemMinLabel.Text = "最小数";
            // 
            // insideItemName
            // 
            this.insideItemName.Location = new System.Drawing.Point(114, 47);
            this.insideItemName.Name = "insideItemName";
            this.insideItemName.ReadOnly = true;
            this.insideItemName.Size = new System.Drawing.Size(510, 22);
            this.insideItemName.TabIndex = 82;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 15);
            this.label1.TabIndex = 83;
            this.label1.Text = "ItemName";
            // 
            // RootItemList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(917, 512);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "RootItemList";
            this.Text = "RootItemList";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.RootItemList_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.probabilityNumeric)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.maxNumeric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.minNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button InsideItemDel;
        private System.Windows.Forms.Button InsideItemAddButton;
        private System.Windows.Forms.NumericUpDown probabilityNumeric;
        private System.Windows.Forms.Label labelProbability;
        private System.Windows.Forms.Label ColectItemLabel;
        private System.Windows.Forms.ComboBox InsideItemDropDownList;
        private System.Windows.Forms.ListBox insideItemListBox;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.NumericUpDown minNumeric;
        private System.Windows.Forms.Label itemMinLabel;
        private System.Windows.Forms.NumericUpDown maxNumeric;
        private System.Windows.Forms.Label itemMaxLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox insideItemName;
    }
}