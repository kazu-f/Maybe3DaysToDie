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
    public partial class RootItemList : Form
    {
        private EditorCommandList m_commandList;
        private BindingSource m_insideBS = new BindingSource();
        private BindingSource itemDataList;
        public PlacementObject placementObject {
            set {
                currentPlaceObj = value;
                m_insideBS.DataSource = currentPlaceObj.insideItemData;
                insideItemListBox.DisplayMember = "ItemName";
                insideItemListBox.ValueMember = "ItemName";
                m_insideBS.ResetBindings(false);
            }
        }

        public PlacementObject currentPlaceObj { private get; set; } = null;

        public RootItemList(EditorCommandList commandList,BindingSource bindingSource)
        {
            m_commandList = commandList;
            itemDataList = bindingSource;
            InitializeComponent();

            insideItemListBox.DisplayMember = "ItemName";
            insideItemListBox.ValueMember = "ItemName";
            insideItemListBox.DataSource = m_insideBS;

            InsideItemDropDownList.DataSource = itemDataList;
            InsideItemDropDownList.DisplayMember = "itemName";
        }

        private void DispInsideItemData(InsideItem insideItem)
        {
            insideItemName.Text = insideItem.ItemName;
            InsideItemDropDownList.SelectedIndex = insideItem.ItemID;
            probabilityNumeric.Value = insideItem.probability;
            maxNumeric.Value = insideItem.maxNum;
            minNumeric.Value = insideItem.minNum;
        }

        private void insideItemListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var select = insideItemListBox.SelectedItem;
            if (select == null) return;

            if(select.GetType() == typeof(InsideItem))
            {
                DispInsideItemData((InsideItem)select);
            }
        }

        #region //ルート内部のアイテムデータを変更する。

        private void InsideItemAddButton_Click(object sender, EventArgs e)
        {
            var select = InsideItemDropDownList.SelectedItem;

            if (!(select is Item)) return;

            InsideItem insideItem = new InsideItem((Item)select);

            Command.AddInsideItem command = new Command.AddInsideItem(currentPlaceObj, insideItem);

            if(command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
            m_insideBS.ResetBindings(false);
        }

        private void InsideItemDel_Click(object sender, EventArgs e)
        {
            var select = insideItemListBox.SelectedItem;

            if (!(select is Item)) return;

            InsideItem insideItem = new InsideItem((Item)select);

            Command.RemoveInsideItem command = new Command.RemoveInsideItem(currentPlaceObj, insideItem);

            if (command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
            m_insideBS.ResetBindings(false);
        }

        #endregion

        private void RootItemList_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

    }
}
