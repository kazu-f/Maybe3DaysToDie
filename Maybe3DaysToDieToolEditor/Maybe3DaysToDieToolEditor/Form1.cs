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
        string filePath = null;
        List<Item> itemList = new List<Item>();
        BindingSource bs = new BindingSource();
        EditorCommandList commandList = new EditorCommandList();
        ToolKindsComboBox toolKinds;
        SaveItemDataList saveData;
        LoadItemDataList loadData;
        public Maybe3DaysToDie_ToolEditor()
        {
            InitializeComponent();
            bs.DataSource = itemList;

            ItemList.DisplayMember = "itemName";
            ItemList.ValueMember = "itemName";
            ItemList.DataSource = bs;

            //設定を行う。
            toolKinds = new ToolKindsComboBox(ToolComboBox);
            saveData = new SaveItemDataList();
            loadData = new LoadItemDataList();
        }

        #region リスト操作の処理。
        /// <summary>
        /// リストからデータを削除する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var item = ItemList.SelectedItem;
            if (item == null) return;       //選択がなければ処理しない。
            //アイテムデータならばリストから削除。
            if (item is Item)
            {
                if (itemList.Remove((Item)item))
                {
                    var reDisp = ItemList.SelectedItem;
                    if (item is Item) DispItemData((Item)reDisp);

                    bs.ResetBindings(false);
                }
            }
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

        #endregion

        #region データを表示する処理。
        /// <summary>
        /// リストの選択が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
        {
            var item = ItemList.SelectedItem;
            //アイテムデータならばテキストボックスに表記。
            if (item is Item) DispItemData((Item)item);
        }

        /// <summary>
        /// アイテムの情報を表示する。
        /// </summary>
        /// <param name="item"></param>
        private void DispItemData(Item item)
        {
            if (item == null)
            {
                NameTextBox.Text = "";
                return;
            }
            NameTextBox.Text = item.itemName;
            //データタイプに応じて処理を分岐。
            if (typeof(ToolData) == item.GetType()) DispToolData((ToolData)item);
        }

        /// <summary>
        /// ツールデータを表示する。
        /// </summary>
        /// <param name="tool"></param>
        private void DispToolData(ToolData tool)
        {
            //ツールの情報を表示する。
            DamageNumeric.Value = tool.damage;
            DurableNumeric.Value = tool.durable;
            UseStaminaNumeric.Value = tool.useStamina;
            toolKinds.SelectValue(tool.tool);
        }
        #endregion

        #region 変更したときのコマンド。

        #region アイテム共通。
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
        #endregion

        #region ツールデータ。
        /// <summary>
        /// ツールダメージを変更したとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveDamageValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(DamageNumeric.Text,out value))
            {
                DamageNumeric.Text = DamageNumeric.Value.ToString();
            }

            var item = ItemList.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolDamage command = new Command.ChangeToolDamage((ToolData)item, (int)DamageNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
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

            var item = ItemList.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolDurable command = new Command.ChangeToolDurable((ToolData)item, (int)DurableNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// ツールのスタミナを変更。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeaveUseStaminaValue(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(UseStaminaNumeric.Text, out value))
            {
                UseStaminaNumeric.Text = DurableNumeric.Value.ToString();
            }

            var item = ItemList.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;

            Command.ChangeToolUseStamina command = new Command.ChangeToolUseStamina((ToolData)item, (int)UseStaminaNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// 適性ツールのコンボボックスが変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToolComboBox_SelectionChangeCommitted(object sender, EventArgs e)
        {
            var item = ItemList.SelectedItem;
            if (item == null) return;
            if (item.GetType() != typeof(ToolData)) return;
            Command.ChangeToolKinds command = new Command.ChangeToolKinds((ToolData)item, toolKinds.SelectedValue);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        #endregion

        #endregion

        #region UnDo、ReDo処理。
        /// <summary>
        /// UnDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UnDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandUnDo();
            var item = ItemList.SelectedItem;
            if (item != null)
            {
                //アイテムデータならばテキストボックスに表記。
                if (item is Item) DispItemData((Item)item);
                bs.ResetBindings(false);
            }
        }

        /// <summary>
        /// ReDo処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void reDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            commandList.CommandReDo();
            var item = ItemList.SelectedItem;
            if (item != null)
            {
                //アイテムデータならばテキストボックスに表記。
                if (item is Item) DispItemData((Item)item);
                bs.ResetBindings(false);
            }
        }
        #endregion

        //フォーカスを外す。
        private void DeFocus()
        {
            this.ActiveControl = null;
        }

        private void MouseCapture(object sender, EventArgs e)
        {
            DeFocus();
        }

        #region ファイル保存関係。
        /// <summary>
        /// 名前を付けて保存。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filePath = saveData.SaveJsonFile(itemList);
        }
        /// <summary>
        /// 上書き保存。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filePath = saveData.SaveJsonFile(itemList, filePath);
        }
        /// <summary>
        /// 読み込み。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenFileOToolStripMenuItem_Click(object sender, EventArgs e)
        {
            List<Item> list;
            filePath = loadData.LoadJsonFile(out list);
            if(list != null)
            {
                itemList = list;
                bs.DataSource = itemList;
                bs.ResetBindings(false);
            }
        }
        #endregion ファイル保存関係。

    }
}
