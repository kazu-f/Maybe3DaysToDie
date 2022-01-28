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
    public partial class PlacementObjectPanel : UserControl
    {
        public EditorCommandList commandList { private get; set; } = null;
        public ListBox listBox { private get; set; } = null;
        ToolKindsComboBox toolKinds;
        private BindingSource _itemDataBS = null;   //アイテムデータのバインディングソース。

        public BindingSource ItemDataBS{
            set 
            {
                _itemDataBS = value;
                ColectItemDropDownList.DataSource = _itemDataBS;
                ColectItemDropDownList.DisplayMember = "itemName";
            }
        }            //アイテムデータのバインディングソース。

        public PlacementObjectPanel()
        {
            InitializeComponent();
            //設定を行う。
            toolKinds = new ToolKindsComboBox(ToolComboBox);
        }

        /// <summary>
        /// 設置物のデータを表示する。
        /// </summary>
        /// <param name="obj"></param>
        public void DispPlacementObject(PlacementObject obj)
        {
            DurableNumeric.Value = obj.durable;
            toolKinds.SelectValue(obj.tool);
            DispListView(obj);
        }

        private void DispListView(PlacementObject obj)
        {
            for(int i = 0;i<obj.collectItemList.Count;i++)
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
            if (item.GetType() != typeof(PlacementObject)) return;

            Command.ChangePlacementObjectDurable command = new Command.ChangePlacementObjectDurable((PlacementObject)item, (int)DurableNumeric.Value);
            //変更があればコマンドリストに追加。
            if (command.IsChanged())
            {
                commandList.AddCommand(command);
            }
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
            if (item.GetType() != typeof(PlacementObject)) return;

            if (ColectItemDropDownList.SelectedItem is Item)
            {
                CollectItem collect = new CollectItem((Item)ColectItemDropDownList.SelectedItem, (int)collectNumeric.Value);
                var place = (PlacementObject)item;
                place.collectItemList.Add(collect);

                DispListView(place);
            }
            
        }
        #endregion

        private void activeControlNull(object sender, EventArgs e)
        {
            this.ParentForm.ActiveControl = null;
        }

    }
}
