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
    public partial class BlockPanel : UserControl
    {
        public DeFocusCommand deFocus = null;

        public EditorCommandList commandList { private get; set; } = null;
        public ListBox listBox { private get; set; } = null;
        ToolKindsComboBox toolKinds;
        private BindingSource _itemDataBS = null;   //アイテムデータのバインディングソース。

        public BindingSource ItemDataBS
        {
            set
            {
                _itemDataBS = value;
                ColectItemDropDownList.DataSource = _itemDataBS;
                ColectItemDropDownList.DisplayMember = "itemName";
            }
        }            //アイテムデータのバインディングソース。

        public BlockPanel()
        {
            InitializeComponent();
            //設定を行う。
            toolKinds = new ToolKindsComboBox(ToolComboBox);
        }

        /// <summary>
        /// 設置物のデータを表示する。
        /// </summary>
        /// <param name="obj"></param>
        public void DispBlock(Block obj)
        {
            DurableNumeric.Value = obj.durable;
            toolKinds.SelectValue(obj.tool);
            DispListView(obj);
        }

        private void DispListView(Block obj)
        {
            //リストを一旦空にする。
            for (int i = 0; i < collectItemListView.Items.Count; i++)
            {
                var listData = collectItemListView.Items[i];
                listData.SubItems[0].Text = (i + 1) + ":";
                for (int j = 1; j < collectItemListView.Columns.Count; j++)
                {
                    listData.SubItems[j].Text = "";
                }
            }

            //リストにデータを表示する。
            for (int i = 0; i < obj.collectItemList.Count; i++)
            {
                var listData = collectItemListView.Items[i];
                var item = obj.collectItemList[i];
                listData.SubItems[1].Text = item.ItemID.ToString();
                listData.SubItems[2].Text = item.ItemName;
                listData.SubItems[3].Text = item.collectNum.ToString();
            }
        }

        #region 設置物のデータの変更コマンド。


        /// <summary>
        /// ツールの耐久を変更。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveDurableValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(DurableNumeric.Text, out value))
            {
                DurableNumeric.Text = DurableNumeric.Value.ToString();
            }

            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(Block)) return;

            Command.ChangeBlockDurable command = new Command.ChangeBlockDurable((Block)item, (int)DurableNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
            DispBlock((Block)item);
        }

        /// <summary>
        /// 採取アイテムを追加するボタンが押された。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CollectItemAddButton_Click(object sender, EventArgs e)
        {
            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(Block)) return;

            if (ColectItemDropDownList.SelectedItem is Item)
            {
                var block = (Block)item;
                //登録できるアイテムの上限に来ているかどうか。
                if (collectItemListView.Items.Count > block.collectItemList.Count)
                {
                    CollectItem collect = new CollectItem((Item)ColectItemDropDownList.SelectedItem, (int)collectNumeric.Value);
                    //place.collectItemList.Add(collect);
                    Command.AddBlockCollectItem command = new Command.AddBlockCollectItem(block, collect);
                    //変更があればコマンドリストに追加。
                    if (command.IsChanged())
                    {
                        commandList.AddCommand(command);
                    }

                    DispBlock(block);
                }
                else
                {
                    MessageBox.Show(
                        "登録できるアイテムの種類の上限です。",
                        "エラー",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                        );
                }
            }
        }
        /// <summary>
        /// 採取アイテムの削除ボタンが押されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CollectItemDel_Click(object sender, EventArgs e)
        {
            var collectItem = collectItemListView.SelectedItems;
            string No = collectItem[0].Text;
            No = No.Remove(No.LastIndexOf(":"));
            int index = int.MaxValue;
            if (int.TryParse(No, out index))
            {
                index--;        //配列アクセスだから表示上の数値 - 1
                var item = listBox.SelectedItem;
                if (item.GetType() == typeof(Block))
                {
                    var block = (Block)item;

                    //インデックスがリストよりも小さい。
                    if (block.collectItemList.Count > index)
                    {
                        //リストから削除するコマンド。
                        Command.RemoveBlockCollectItem command = new Command.RemoveBlockCollectItem(block, index);

                        if (command.IsChanged())
                        {
                            commandList.AddCommand(command);
                        }
                    }

                    DispBlock(block);
                }
            }

        }

        /// <summary>
        /// ツールが変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToolComboBox_SelectionChangeCommitted(object sender, EventArgs e)
        {
            if (listBox == null) return;
            var item = listBox.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(Block)) return;
            Command.ChangeBlockKinds command = new Command.ChangeBlockKinds((Block)item, toolKinds.SelectedValue);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }

        }

        #endregion

        private void activeControlNull(object sender, EventArgs e)
        {
            deFocus();
        }
    }
}
