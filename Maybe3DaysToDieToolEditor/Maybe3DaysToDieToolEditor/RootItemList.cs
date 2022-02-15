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
        public Maybe3DaysToDie_ToolEditor parentForm = null;
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

        public void ResetBindingData()
        {
            m_insideBS.ResetBindings(false);
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

        /// <summary>
        /// ルート内部データを追加する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InsideItemAddButton_Click(object sender, EventArgs e)
        {
            var select = InsideItemDropDownList.SelectedItem;

            if (select == null) return;
            if (!(select is Item)) return;

            InsideItem insideItem = new InsideItem((Item)select);

            Command.AddInsideItem command = new Command.AddInsideItem(currentPlaceObj, insideItem);

            if(command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
            m_insideBS.ResetBindings(false);
        }
        /// <summary>
        /// ルート内部データを消す処理。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InsideItemDel_Click(object sender, EventArgs e)
        {
            var select = insideItemListBox.SelectedItem;

            if (select == null) return;
            if (!(select is InsideItem)) return;

            Command.RemoveInsideItem command = new Command.RemoveInsideItem(currentPlaceObj, (InsideItem)select);

            if (command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
            m_insideBS.ResetBindings(false);
        }

        /// <summary>
        /// 確率を操作する。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void probabilityNumeric_Leave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(probabilityNumeric.Text, out value))
            {
                probabilityNumeric.Text = probabilityNumeric.Value.ToString();
            }

            var select = insideItemListBox.SelectedItem;

            if (select == null) return;
            if (!(select is InsideItem)) return;

            var inside = (InsideItem)select;

            Command.ChangeInsideProbility command = new Command.ChangeInsideProbility(inside, (int)probabilityNumeric.Value);

            if (command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
        }

        private void maxNumeric_Leave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(maxNumeric.Text, out value))
            {
                maxNumeric.Text = maxNumeric.Value.ToString();
            }

            var select = insideItemListBox.SelectedItem;

            if (select == null) return;
            if (!(select is InsideItem)) return;

            var inside = (InsideItem)select;

            Command.ChangeInsideMaxNum command = new Command.ChangeInsideMaxNum(inside, (int)maxNumeric.Value);

            if (command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
        }

        private void minNumeric_Leave(object sender, EventArgs e)
        {
            //テキストを戻す。
            int value = 0;
            if (!int.TryParse(minNumeric.Text, out value))
            {
                minNumeric.Text = minNumeric.Value.ToString();
            }

            var select = insideItemListBox.SelectedItem;

            if (select == null) return;
            if (!(select is InsideItem)) return;

            var inside = (InsideItem)select;

            Command.ChangeInsideMinNum command = new Command.ChangeInsideMinNum(inside, (int)minNumeric.Value);

            if (command.IsChanged())
            {
                m_commandList.AddCommand(command);
            }
        }
        #endregion

        private void RootItemList_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void activeControlNull(object sender, EventArgs e)
        {
            this.ActiveControl = null;
        }

        private void UnDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            parentForm.UnDoToolStripMenuItem_Click(sender, e);
            m_insideBS.ResetBindings(false);

            var select = insideItemListBox.SelectedItem;
            if (select == null) return;

            if (select.GetType() == typeof(InsideItem))
            {
                DispInsideItemData((InsideItem)select);
            }
        }

        private void ReDoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            parentForm.reDoToolStripMenuItem_Click(sender, e);

            m_insideBS.ResetBindings(false);

            var select = insideItemListBox.SelectedItem;
            if (select == null) return;

            if (select.GetType() == typeof(InsideItem))
            {
                DispInsideItemData((InsideItem)select);
            }
        }
    }
}
