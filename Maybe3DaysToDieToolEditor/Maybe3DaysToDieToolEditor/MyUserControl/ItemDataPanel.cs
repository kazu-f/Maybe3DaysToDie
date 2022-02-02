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
                //ColectItemDropDownList.DataSource = _itemDataBS;
                //ColectItemDropDownList.DisplayMember = "itemName";
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

        #endregion

        private void activeControlNull(object sender, EventArgs e)
        {
            this.ParentForm.ActiveControl = null;
        }
    }
}
