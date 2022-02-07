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
    public partial class ItemDataPanel : UserControl
    {
        #region 定数類。
        public enum EnMaxStackNum
        {
            enStack_Tool = 1,
            enStack_Food = 30,
            enStack_Place = 999,
            enStack_Material = 999
        }

        public delegate void UpdateBSMethod();
        #endregion

        public ListBox listBox { private get; set; } = null;
        public BindingSource listBoxBS = null;
        public BindingSource _itemDataBS = null;
        public EditorCommandList commandList = null;
        public UpdateBSMethod updateBSMethod = null;

        SelectDataFile selectModelData;         //モデルデータを選ぶ処理。
        SelectDataFile selectIconData;          //アイコンデータを選ぶ処理。


        public BindingSource ItemDataBS
        {
            set
            {
                _itemDataBS = value;
                CraftMaterialItemDropDownList.DataSource = _itemDataBS;
                CraftMaterialItemDropDownList.DisplayMember = "itemName";
            }
        }            //アイテムデータのバインディングソース。

        public ItemDataPanel()
        {
            InitializeComponent();

            selectModelData = new SelectDataFile(ModelFileSelectButton, ModelFilePathTextBox, "tkm", ItemTkmFileChangeCommand);
            selectIconData = new SelectDataFile(IconFileSelectButton, IconDataTextBox, "png", ItemIconFileChangeCommand);
        }

        /// <summary>
        /// アイテムの基礎情報を表示する。
        /// </summary>
        /// <param name="item">アイテムデータ。</param>
        public void DispItemData(Item item)
        {
            //データタイプに応じてスタック最大値を設定し直す。
            if (typeof(ToolData) == item.GetType())
            {
                MaxItemStackNumeric.Maximum = (int)EnMaxStackNum.enStack_Tool;
            }
            else if (typeof(PlacementObject) == item.GetType())
            {
                MaxItemStackNumeric.Maximum = (int)EnMaxStackNum.enStack_Place;
            }
            else if (typeof(FoodAndCure) == item.GetType())
            {
                MaxItemStackNumeric.Maximum = (int)EnMaxStackNum.enStack_Food;
            }
            //アイテムのデータを表示する。
            NameTextBox.Text = item.itemName;
            ModelFilePathTextBox.Text = item.tkmFile;
            IconDataTextBox.Text = item.iconData;
            ItemIDDispLabel.Text = item.itemID.ToString();
            MaxItemStackNumeric.Value = item.itemStackNum;
            DispListView(item);
        }
        private void DispListView(Item item)
        {
            //リストを一旦空にする。
            for (int i = 0; i < craftItemListView.Items.Count; i++)
            {
                var listData = craftItemListView.Items[i];
                listData.SubItems[0].Text = (i + 1) + ":";
                for (int j = 1; j < craftItemListView.Columns.Count; j++)
                {
                    listData.SubItems[j].Text = "";
                }
            }

            //リストにデータを表示する。
            for (int i = 0; i < item.itemCraftMaterials.Count; i++)
            {
                var listData = craftItemListView.Items[i];
                var craftMaterial = item.itemCraftMaterials[i];
                listData.SubItems[1].Text = craftMaterial.ItemID.ToString();
                listData.SubItems[2].Text = craftMaterial.ItemName;
                listData.SubItems[3].Text = craftMaterial.craftItemNum.ToString();
            }
        }

        #region  アイテムのデータ変更のコマンド。

        /// <summary>
        /// テキストボックスの中が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NameTextBox_Leave(object sender, EventArgs e)
        {
            var item = ((Item)listBox.SelectedItem);
            if (item == null) return;
            if (NameTextBox.Text == "") return;
            Command.RenameItemCommand command = new Command.RenameItemCommand(item, NameTextBox.Text);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
                updateBSMethod();
            }
        }
        /// <summary>
        /// アイテムのスタック数が変更されたとき。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ItemStackNumeric_Leave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(MaxItemStackNumeric.Text, out value))
            {
                MaxItemStackNumeric.Text = MaxItemStackNumeric.Value.ToString();
            }

            var item = ((Item)listBox.SelectedItem);
            if (item == null) return;
            Command.ItemStackChangeCommand command = new Command.ItemStackChangeCommand(item, (int)MaxItemStackNumeric.Value);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }

        /// <summary>
        /// アイテムのモデルファイルを選択したとき。
        /// </summary>
        private void ItemTkmFileChangeCommand()
        {
            var item = listBox.SelectedItem;
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
            var item = listBox.SelectedItem;
            if (item == null) return;
            Command.ChangeItemIcon command = new Command.ChangeItemIcon((Item)item, IconDataTextBox.Text);
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
        }
        /// <summary>
        /// クラフト素材を追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CraftMaterialItemAddButton_Click(object sender, EventArgs e)
        {
            var select = listBox.SelectedItem;
            if (select == null) return;
            if (!(select is Item)) return;

            if (CraftMaterialItemDropDownList.SelectedItem is Item)
            {
                var item = (Item)select;
                //登録できるアイテムの上限に来ているかどうか。
                if (craftItemListView.Items.Count > item.itemCraftMaterials.Count)
                {
                    ItemCraftMaterial craftMat = new ItemCraftMaterial((Item)CraftMaterialItemDropDownList.SelectedItem, (int)CraftMaterialNumeric.Value);
                    //place.collectItemList.Add(collect);
                    Command.AddCraftMaterialItem command = new Command.AddCraftMaterialItem(item, craftMat);
                    //変更があればコマンドリストに追加。
                    if (command.IsChanged())
                    {
                        commandList.AddCommand(command);
                    }

                    DispItemData(item);
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
        /// クラフト素材を削除する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CraftMaterialItemDelButton_Click(object sender, EventArgs e)
        {
            var craftMat = craftItemListView.SelectedItems;
            string No = craftMat[0].Text;
            No = No.Remove(No.LastIndexOf(":"));
            int index = int.MaxValue;
            if (int.TryParse(No, out index))
            {
                index--;        //配列アクセスだから表示上の数値 - 1
                var select = listBox.SelectedItem;
                if ((select is Item))
                {
                    var item = (Item)select;

                    //インデックスがリストよりも小さい。
                    if (item.itemCraftMaterials.Count > index)
                    {
                        //リストから削除するコマンド。
                        Command.RemoveCraftMaterialItem command = new Command.RemoveCraftMaterialItem(item, index);

                        if (command.IsChanged())
                        {
                            commandList.AddCommand(command);
                        }
                    }

                    DispItemData(item);
                }
            }

        }
        #endregion  //アイテムのデータを変更する処理。

        private void activeControlNull(object sender, EventArgs e)
        {
            this.ParentForm.ActiveControl = null;
        }

    }
}
