﻿using System;
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
        List<Item> m_itemList = new List<Item>();
        BindingSource bs = new BindingSource();
        EditorCommandList commandList = new EditorCommandList();
        //ToolKindsComboBox toolKinds;
        SaveItemDataList saveData;
        LoadItemDataList loadData;
        SelectDataFile selectModelData;         //モデルデータを選ぶ処理。
        SelectDataFile selectIconData;          //アイコンデータを選ぶ処理。
        public Maybe3DaysToDie_ToolEditor()
        {
            InitializeComponent();
            bs.DataSource = m_itemList;

            ItemList.DisplayMember = "itemName";
            ItemList.ValueMember = "itemName";
            ItemList.DataSource = bs;

            toolDataPanel1.commandList = commandList;
            toolDataPanel1.listBox = ItemList;

            //設定を行う。
            //toolKinds = new ToolKindsComboBox(ToolComboBox);
            saveData = new SaveItemDataList();
            loadData = new LoadItemDataList();
            //ファイル選択用の処理を構成する。
            selectModelData = new SelectDataFile(ModelFileSelectButton, ModelFilePathTextBox, "tkm", ItemTkmFileChangeCommand);
            selectIconData = new SelectDataFile(IconFileSelectButton, IconDataTextBox, "png", ItemIconFileChangeCommand);
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
                if (m_itemList.Remove((Item)item))
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
            m_itemList.Add(newTool);

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
                return;
            }
            //アイテムの情報を表示する。
            NameTextBox.Text = item.itemName;
            ModelFilePathTextBox.Text = item.tkmFile;
            IconDataTextBox.Text = item.iconData;

            //データタイプに応じて処理を分岐。
            if (typeof(ToolData) == item.GetType()) toolDataPanel1.DispToolData((ToolData)item);
        }
        #endregion

        #region アイテム共通の変更したときのコマンド。

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
        /// アイテムのモデルファイルを選択したとき。
        /// </summary>
        private void ItemTkmFileChangeCommand()
        {
            var item = ItemList.SelectedItem;
            if (item == null) return;
            Command.ChangeItemModel command = new Command.ChangeItemModel((Item)item, ModelFilePathTextBox.Text);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// アイテムのアイコンのファイルを選択したとき。
        /// </summary>
        private void ItemIconFileChangeCommand()
        {
            var item = ItemList.SelectedItem;
            if (item == null) return;
            Command.ChangeItemIcon command = new Command.ChangeItemIcon((Item)item, IconDataTextBox.Text);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }

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
            this.toolDataPanel1.ActiveControl = null;
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
            filePath = saveData.SaveJsonFile(m_itemList);
        }
        /// <summary>
        /// 上書き保存。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            filePath = saveData.SaveJsonFile(m_itemList, filePath);
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
                //コマンドリストをリセット。
                commandList.ResetCommandList();
                //アイテムのリストを読み込んだものに変更。
                m_itemList = list;
                bs.DataSource = m_itemList;
                //表記を変更。
                ItemList.SelectedItem = m_itemList[0];
                DispItemData(m_itemList[0]);
                bs.ResetBindings(false);
            }
            DeFocus();
        }
        #endregion ファイル保存関係。
    }
}
