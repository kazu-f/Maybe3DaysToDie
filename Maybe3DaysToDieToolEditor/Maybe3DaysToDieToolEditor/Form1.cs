using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maybe3DaysToDieToolEditor
{
    public partial class Maybe3DaysToDie_ToolEditor : Form
    {
        BindingList<Item> itemList = new BindingList<Item>();
        BindingSource bs = new BindingSource();
        public Maybe3DaysToDie_ToolEditor()
        {
            InitializeComponent();
            bs.DataSource = itemList;

            ItemList.DisplayMember = "itemName";
            ItemList.ValueMember = "itemName";
            ItemList.DataSource = bs;
        }

        /// <summary>
        /// リストに新しいツールデータを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToolDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var newTool = new ToolData { itemName = "ToolData" };
            itemList.Add(newTool);

            bs.ResetBindings(false);
        }

        /// <summary>
        /// リストの選択が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
        {
            NameTextBox.Text = ((Item)ItemList.SelectedItem).itemName;
        }

        /// <summary>
        /// テキストボックスの中が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NameTextBox_TextChanged(object sender, EventArgs e)
        {
            ((Item)ItemList.SelectedItem).itemName = NameTextBox.Text;
            bs.ResetBindings(false);
        }
    }
}
