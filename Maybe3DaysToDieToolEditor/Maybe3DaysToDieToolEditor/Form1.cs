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
        EditorCommandList commandList = new EditorCommandList();
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
        private void NameTextBox_Leave(object sender, EventArgs e)
        {
            var item = ((Item)ItemList.SelectedItem);
            if (item == null) return;
            Command.RenameItemCommand command = new Command.RenameItemCommand(item, NameTextBox.Text);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
                bs.ResetBindings(false);
            }
        }

        private void UnDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandUnDo();
            NameTextBox.Text = ((Item)ItemList.SelectedItem).itemName;
            bs.ResetBindings(false);
        }

        private void reDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandReDo();
            NameTextBox.Text = ((Item)ItemList.SelectedItem).itemName;
            bs.ResetBindings(false);
        }

        //フォーカスを外す。
        private void DeFocus()
        {
            this.ActiveControl = null;
        }

        private void MouseCapture(object sender, EventArgs e)
        {
            DeFocus();
        }
    }
}
