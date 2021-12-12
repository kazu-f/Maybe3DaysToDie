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
        ToolKindsComboBox toolKinds;
        public Maybe3DaysToDie_ToolEditor()
        {
            InitializeComponent();
            bs.DataSource = itemList;

            ItemList.DisplayMember = "itemName";
            ItemList.ValueMember = "itemName";
            ItemList.DataSource = bs;

            //設定を行う。
            toolKinds = new ToolKindsComboBox(ToolComboBox);
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
            var item = ItemList.SelectedItem;
            //アイテムデータならばテキストボックスに表記。
            if(item is Item)NameTextBox.Text = ((Item)ItemList.SelectedItem).itemName;
            //データタイプに応じて処理を分岐。
            if (typeof(ToolData) == item.GetType()) SelectToolData((ToolData)item);
        }

        /// <summary>
        /// ツールデータが選択されたとき。
        /// </summary>
        /// <param name="tool"></param>
        private void SelectToolData(ToolData tool)
        {
            //ツールの情報を表示する。
            DamageNumeric.Value = tool.damage;
            DurableNumeric.Value = tool.durable;
            UseStaminaNumeric.Value = tool.useStamina;
            toolKinds.SelectValue(tool.tool);
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

        /// <summary>
        /// UnDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UnDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandUnDo();
            NameTextBox.Text = ((Item)ItemList.SelectedItem).itemName;
            bs.ResetBindings(false);
        }

        /// <summary>
        /// ReDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
